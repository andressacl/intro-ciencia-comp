#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lista.h"

static void lista_print_resultado_torneio(Lista *lista);

struct lista_st {
	Aluno **alunos;
	int tam;
};

Lista *lista_create(int capacity){
	Lista *new_lista = (Lista*) calloc(1, sizeof(Lista));

	new_lista->alunos = (Aluno**) calloc(capacity, sizeof(Aluno*));
	new_lista->tam = 0;

	return new_lista;
}

/*A função para registrar elementos não checa se a capacidade
da lista foi atingida por conta da forma com a qual o código da
Main está escrito: nunca se ultrapassa a capacidade da lista.*/
void lista_register_element(Lista *lista, Aluno *aluno){
	lista->alunos[lista->tam] = aluno;
	lista->tam++;
}

int lista_tam(Lista *lista){
	return lista->tam;
}

Aluno **lista_elements(Lista *lista){
	return lista->alunos;
}

/*
A função torneioGeralSort() é a principal da implementação do
algoritmo de ordenação. Ela atua da seguinte maneira: cria-se
uma árvore a partir da lista utilizando as funções e suas descrições 
contidas no TAD de árvore. A partir disso, build_tree() realiza o primeiro
torneio. O primeiro elemento da lista então aponta para a raiz da árvore,
que contém o vencedor deste torneio. Em sequência, encontra-se a folha 
cujo aluno foi o vencedor do primeiro torneio e altera-se-o para apontar
para o elemento inválido da árvore. Um novo torneio é realizado (organiza-se 
a árvore) e o próximo índice da lista aponta para o segundo ganhador, agora
na raiz. Esse processo se repete até que todos os elementos estejam ordenados
(atinge-se o número de elementos da lista). Por fim, desaloca-se a árvore
e os resultados são impressos de acordo com a formatação específica do torneio.

A complexidade das funções principais é analisada em suas descrições, no TAD
árvore. Porém, vemos que build_arvore() é chamada 1 vez e arvore() é
chamada n-1 vezes, de forma que podemos inferir que o torneio atua 
com complexidade O(nlog(n)) (considerando comparações). Também,
para achar o elemento removido, é necessário percorrer da raiz até
as folhas fazendo 1 comparação, ou seja, este processo também é log(n), 
o que não altera a análise anterior.
*/
Lista *torneioGeralSort(Lista *lista){
	int k = lista->tam;
	int tam_lista_ord = 0;
	
	Arvore *tree = arvore_create(lista->alunos, k);
	build_arvore(tree);

	lista->alunos[tam_lista_ord] = raiz(tree);
	tam_lista_ord++;

	while(tam_lista_ord < k){
		int first_leaf = k;
		int i = 1;

		while(i < first_leaf){
			if (arvore_get_element(tree, i) == arvore_get_element(tree, 2*i)){
				i = 2*i;
			} else {
				i = 2*i+1;
			}
		}

		arvore_point_null(tree, i); //Aponta para o elemento inválido
		organize_arvore(tree, i);

		lista->alunos[tam_lista_ord] = raiz(tree);
		tam_lista_ord++;
	}

	arvore_delete(&tree);

	lista_print_resultado_torneio(lista);
	return lista;
}

/*
Função auxiliar para o desenvolvimento do código.
*/
void lista_print(Lista *lista){
	for (int i = 0; i < lista->tam; i++){
		aluno_print(lista->alunos[i]);
	}
} 

/*
Função que faz a formatação para os resultados do torneio.
*/
static void lista_print_resultado_torneio(Lista *lista){

	printf("Maior media: %.3f\n", aluno_av(lista->alunos[0]));

	int i = 0;

	while (i < lista->tam-1){
		if (aluno_desempate(lista->alunos[i+1]) > 0){
			printf("%d. %s - desempate: nota %d\n", 
					i+1, 
					aluno_name(lista->alunos[i]), 
					aluno_desempate(lista->alunos[i+1]));
		} else {
			printf("%d. %s - media\n", i+1, aluno_name(lista->alunos[i]));
		}
		i++;
	}
	printf("%d. %s\n", i+1, aluno_name(lista->alunos[i]));
} 

/*
Função para desalocar espaços da lista. Como é sempre cheia e 
no final está com elementos diferentes em cada posição, basta
deletar o aluno apontado por cada índice.
*/
void lista_delete(Lista **lista_ref){
	Lista *lista = *lista_ref;

	for (int i = 0; i < lista->tam; i++){
		aluno_delete(&(lista->alunos[i]));
	}
	
	lista->tam = 0;
	free(lista->alunos);
	free(lista);
	*lista_ref = NULL;
}