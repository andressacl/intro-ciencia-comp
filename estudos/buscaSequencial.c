#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	- Algoritmo: 
		- uma sequência de passos lógicos;
		- é correto se, e somente se, para toda instância de entrada a saída é correta
		- diferentes soluções podem ser implementadas, cada uma com sua complexidade
		- uma solução perfeita, pode não ser a "melhor solução" (soluções aproximadas)
	
	- Como calcular a eficiência de um algoritmo (baseado no tamanho da entrada):
		- tempo de execução: mesma máquina e no mesmo estado
		- contagem de passos:
			- operações aritméticas e atribuições;
			- comparações;
			- resolver um ponteiro ou acesso às indexações;
			- acesso e retorno às funções.
		
	- Vamos fixar estes conceitos por meio da Busca Sequencial e Busca Binária:
		- requisito básico para motores de busca na internet, base de dados, etc
	
	- Métodos de Busca:
		- Considerando uma chave e um conjunto de elementos, um método de busca objetiva 
			encontrar a localização correta da chave neste conjunto, se ela existir.
		- Formalmente:
			- Um algoritmo de busca é aquele que aceita um argumento "a" e tenta encontrar 
				o registro cuja chave seja "a". O algoritmo pode retornar o registro inteiro 
				ou um ponteiro para este registro. Se o registro não for encontrado retorna-se 
				um registro ou ponteiro nulo.
		- É aplicável a diferentes contextos.
		- Consiste em uma estrutura de armazenamento e uma heurística de busca:
			- A estrutura de armazenamento pode ser um vetor, uma lista encadeada, uma árvore 
				ou um grafo.
			- Métodos de busca são adequados para determinados tipos de estruturas 
				de armazenamento.
		- Quando a estrutura está totalmente na Memória RAM utilizamos Métodos Internos.
		- Quando a estrutura está majoritariamente no Disco utilizamos Métodos Externos.
		
	- Busca Sequencial:
		- Algoritmo mais simples, basicamente sem nenhuma estratégia mais elaborada;
		- Percorre o conjunto de elementos comparando a chave com o conteúdo atual do conjunto;
		- Retorna a localização do elemento se ele existir;
		- Problemático para cenários com repetição de chaves;
		- Aplicável em vetores e listas encadeadas.
*/

/*
	Descrição: gera valores aleatórios para um vetor de tamanho quantidade com valores 
		entre minimo e maximo
	Parâmetros:
		- int qtdade: tamanho do vetor a ser gerado
		- int minimo: valor minimo que pode ser gerado
		- int maximo: valor maximo que pode ser gerado
	Retorno:
		- int* vetorGerado: vetor de tamanho qtdade preenchido pela função
	Observações:
		- vetor não tem controle de ordenação e pode ter valores repetidos.
*/

int* gerarVetor(int qtdade, int minimo, int maximo){
	//srand(time)

	int* vetorGerado = malloc(qtdade * sizeof(int));
	vetorGerado[0] = minimo;
	printf("%i ", vetorGerado[0]);

	int i;
	for (i = 1; i < qtdade; i++){ //gera valores aleatórios entre minino e maximo
		//rand() % (20 - 11 + 1) + 11
		//vetorGerado[i] = rand() % (maximo-minimo+1) + minimo; //sem ordenação
		vetorGerado[i] = rand() % (maximo-minimo+1) + minimo + vetorGerado[i-1]; //com ordenação 
		printf("%i ", vetorGerado[i]);
	}
	
	return vetorGerado;
}

int buscaSequencial_iterativa(int* vetor, int tamanho, int chave);
int buscaSequencial_recursiva(int* vetor, int tamanho, int chave);

int main(int argc, char* argv[]){
	//lendo parâmetros iniciais
	int qtdade = atoi(argv[1]);
	int minimo = atoi(argv[2]);
	int maximo = atoi(argv[3]);
	
	//gerando o vetor de dados
	int* vetor = gerarVetor(qtdade, minimo, maximo);
	
	//buscando um valor informado
	int chave;
	printf("\nDigite a chave a ser buscada: ");
	scanf("%i", &chave);
	
	clock_t inicio = clock();
	int posicao = buscaSequencial_iterativa(vetor, qtdade, chave);
	//int posicao = buscaSequencial_recursiva(vetor, qtdade, chave);
	clock_t final = clock();
	double tempo = (final-inicio)/(double)CLOCKS_PER_SEC;
	printf("Tempo de busca: %lf s\n", tempo);
	
	//informando a saída ao usuário
	if (posicao >= 0 )
		printf("Valor encontrado na posicao %i\n", posicao);
	else
		printf("Valor nao encontrado\n");
	
	//desalocando o vetor dinâmico
	free(vetor);
	return 0;
}

/*
	Descrição: 
		- código pequeno; 
		- basicamente é uma busca por força bruta; 
		- fazendo a busca sem nenhuma estratégia mais elaborada
	Parâmetros:
		- int* vetor: conjunto de dados de busca
		- int tamanho: tamanho do vetor de busca
		- int chave: valor a ser buscado
	Retorno:
		- int (posicao): localização do elemento buscado
	Contagem de operações:
		- (A) atribuição e aritméticas
		- (C) comparação
		- (V) acesso ao vetor
		- (F) acesso ou retorno de função
	Nós consideramos que todas as operações levam aproximadamente o tempo de execução
	Quando nós temos fluxos exclusivos, considera-se o pior caso!!!
	
	De termos gerais, a busca Sequencial é totalmente dependente do tamanho "n"
		- quanto mais n aumenta, maior é a quantidade de operações realizadas
	- Qual é o melhor caso? o número buscado é o primeiro
	- Qual é o pior caso? o número buscado não existe
*/

int buscaSequencial_iterativa(int* vetor, int tamanho, int chave){
	int i;
	for (i = 0; i < tamanho; i++)	//1 vez (A + C); outras vezes (2A + C).(n - 1)
		if (vetor[i] == chave)		//n(V + C) 
			return i;				//F
	return -1;						//F (não é executada) -> descartar
	//i++ <==> i = i + 1 (soma e atribuição) = 2A
	
	/*
		Contagem de operações:
		f(n) = A + C + (2A + C).(n - 1) + n(V + C) + F	
		f(n) = A + C + 2An - 2A + Cn - C + Vn + Cn + F
		
		se A = C = V = F = 1
		f(n) = 1 + 1 + 2n - 2 + n - 1 + n + n + 1
		f(n) = 5n

		n = 1: vamos ter 5 operações
		n = 2: vamos ter 10 operações
		
		Função de eficiência: f(n) = 5n
			- Melhor caso (elemento na primeira posição): f(1) = 5.1 = 5
			- Pior caso (elemento na última posição): f(n) = 5n
			- Caso médio (elemento na posição n/2): f(n) = 5(n/2)
	*/
}

/*
	Descrição: 
		- percorre todo o vetor para tentar encontrar o elemento desejado
	Parâmetros:
		- int* vetor: dado de entrada
		- int tamanho: indica a parte do vetor a ser percorrida
		- int chave: elemento a ser buscado
	Retorno:
		- int (posicao): posição do elemento buscado
*/

int buscaSequencial_recursiva(int* vetor, int tamanho, int chave){
	if (vetor[tamanho-1] == chave) return tamanho-1; //valor encontrado
	if (tamanho == 0) return -1; //valor não encontrado; chegamos ao final do vetor
	return buscaSequencial_recursiva(vetor, tamanho-1, chave); //ainda não encontramos o valor
	
	/*
		Função de recorrência (considerando somente comparações):
			(1 vez): f(n) = 2 + f(n-1)
			(2 vez): f(n) = 2 + [2 + f(n-2)] = 4 + f(n-2)
			(3 vez): f(n) = 4 + [2 + f(n-3)] = 6 + f(n-3)
			(k vez): f(n) = 2.k + f(n-k)
		
			f(1) = 1 então n - k = 1, assim: k = n – 1
			voltando: f(n) = 2.(n-1) + f(1)
						   = 2n – 2 + 1 = 2n -1
	*/
}

/*
	Exercícios:
	1) Refaça a contagem da versão iterativa considerando somente comparações
	2) Modifique a Busca Sequencial para casos em que o vetor já esteja ordenado, 
		acrescentando uma validação para interrromper a busca.
	3) Modifique a Busca Sequencial para incorporar o Método mover-para-frente. 
		Esta metodologia consiste em reduzir o tempo de busca realocando o item encontrado 
		para o início da lista/vetor para uma próxima busca. Assim, elementos mais 
		frequentementes buscados estarão no início e os menos frequentes estarão no final. 
		O elemento de retorno deve ser colocado no início e todos os demais (início até 
		sua posição vaga são realocados).
	4) Modifique a Busca Sequencial para incorporar o Método da transposição. 
		Esta metodologia consiste em reduzir o tempo de busca realocando o item encontrado 
		em uma posição anterior à sua original, movendo seu antecessor para a posição vaga.
		
	Referências:
		- Tenembaum, capítulo 7.
		- Ascencio, capítulo 2.
*/