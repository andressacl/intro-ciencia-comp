#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Arvore.h"

static void set_nodes(Arvore *arvore, Aluno **lista_alunos);

/*
A struct de arvore possui os mesmos componentes que uma lista,
mas optou-se por mantê-las separadas pois posssuem métodos
muito diferentes e representam estruturas diferentes, apesar
de possuir representação similar do ponto de vista de 
alocação de memória.
*/
struct arvore_st {
	Aluno **data;
	int tam;
};


/*
A função arvore_create() cria uma árvore adaptada ao contexto
do problema: com 2*número de elementos da lista base, colocando
estes nas folhas da árvore e fazendo todos os outros elementos 
da árvore serem nulos (através da função set_nodes).
*/
Arvore *arvore_create(Aluno **lista_alunos, int tam){
	Arvore *new_arvore = (Arvore*) calloc(1, sizeof(Arvore));

	new_arvore->tam = 2*tam;
	new_arvore->data = (Aluno**) calloc(new_arvore->tam, sizeof(Aluno*));
	
	set_nodes(new_arvore, lista_alunos);

	return new_arvore;
}

/*
A função set_leaves() inicializa a árvore colocando nas folhas
os elementos da lista base e fazendo o resto da árvore apontar
para um elemento inválido (cabe notar que, como o índice 0 nunca
é utilizado, se quisermos acessar o elemento nulo para deletar
ou fazer outros índices apontarem para ele, basta acessar 
arvore->data[0]).
*/
static void set_nodes(Arvore *arvore, Aluno **lista_alunos){
	int k = arvore->tam/2;
	Aluno *aluno_invalido_p = aluno_create_invalid();

	for (int i = k; i < 2*k; i++){
		arvore->data[i] = lista_alunos[i-k]; 
		arvore->data[i-k] = aluno_invalido_p;
	}
}

Aluno *raiz(Arvore *arvore){
	return arvore->data[1];
}

Aluno *arvore_get_element(Arvore *arvore, int element){
	return arvore->data[element];
}

/*
Função auxiliar do algoritmo de ordenação que faz um índice
qualquer da árvore apontar para o elemento nulo.
*/
void arvore_point_null(Arvore *arvore, int indice){
	arvore->data[indice] = arvore->data[0];
}


/*
As funções organize_arvore() e build_arvore() são auxiliares do
algoritmo de ordenação contido em Lista.c. Como são métodos da
árvore, estão declarados aqui.
*/

/*
A função organize_arvore() atua similarmente ao max_heapify() do
heap sort, porém atua no contexto do torneio sort: ela "arruma"
no máximo uma violação da ordem da árvore, percorrendo-a de 
baixo para cima. Dado um elemento que não seja a raiz, a função
pega seu nó "irmão" e os compara, subindo o maior para o índice
pai e chamando a função para o índice pai, que competirá com seu
irmão e assim, até chegar na raiz. Esta função é chamada para, 
no máximo, log(n) nós, que é a altura da árvore e nela é feita
duas comparações. A função ganhador() pode demandar mais comparações
dependendo do caso de empate de médias dos alunos. No entanto, a função
ganhador() não depende do número de nós percorridos pela organize_arvore(), 
apenas pode variar por conta dos alunos diferentes comparados. 
*/
void organize_arvore(Arvore *arvore, int i){
	int pai = (int) i/2;
	int l_child = 2*pai;
	int r_child = 2*pai+1;
	int ganhador_p;

	if (pai < 1) return;

	if (ganhador(arvore->data[l_child], arvore->data[r_child]) 
		== arvore->data[l_child]) {
		ganhador_p = l_child;
	} else {
		ganhador_p = r_child;
	}

	arvore->data[pai] = arvore->data[ganhador_p];
	organize_arvore(arvore, pai);
}

/*
A função build_arvore() é chamada para construir (1 vez apenas no 
algoritmo) a árvore substituindo os valores inválidos por resultados
do primeiro torneio. Ela atua chamando a função organize_arvore()
para os nós, construindo, assim, a árvore de baixo para cima. Desta forma,
ela chama n-2 vezes esta função, que é chamada recursivamente, no máximo,
log(n) vezes.
*/
void build_arvore(Arvore *arvore){
	for (int i = arvore->tam-1; i > 1; i--){
		organize_arvore(arvore, i);
	}
}

/*
Função auxiliar utilizada durante o desenvolvimento do código para
visualizar a estrutura.
*/
void arvore_print(Arvore *arvore){
	for (int i = 0; i < arvore->tam; i++){
		if(arvore->data[i] != NULL){
			aluno_print(arvore->data[i]);
		}
	}
} 

/*
Na função para desalocar a árvore, devido à forma com a qual
todas as estruturas foram implementadas, é necessário apenas
deletar o aluno inválido que se manteve apontado pelo elemento 
0 da árvore. No final do torneio, a árvore ainda guarda referência
para o último colocado, mas, como este é colocado na lista, sua 
referência não é perdida.
*/
void arvore_delete(Arvore **arvore_ref){
	Arvore *arvore = *arvore_ref;

	aluno_delete(&arvore->data[0]);

	arvore->tam = 0;
	free(arvore->data);
	free(arvore);
	*arvore_ref = NULL;
}