#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int *sort(int *vetor, int tamanho){
	int j;
	for (j=1; j <tamanho;j++){
		int chave = vetor[j];
		int i = j-1;
		while (i>=0 && vetor[i]>chave){
			vetor[i+1]=vetor[i];
			i--;
		}
		vetor[i+1]=chave;
	}
	return vetor;
}

int buscaBinaria_recursiva(int* vetor, int posicaoInicial, int posicaoFinal, int chave);
int buscaBinaria_iterativa(int* vetor, int posicaoInicial, int posicaoFinal, int chave);

int main(void){
	
	int N[9] = {10, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
	

	for (int k =0; k<9; k++){
		printf("-------------------------------\n");
		printf("Tamanho da entrada: %i\n", N[k]);
		int tamanhoVetor = N[k];
		int *vetor = (int*)malloc(tamanhoVetor*sizeof(int));
		srand(time(NULL));

		int i;
		for (i=0; i<tamanhoVetor; i++){
			vetor[i] = rand() % 100000;
		}
		vetor = sort(vetor, tamanhoVetor);

		
		/*for (i=0; i<tamanhoVetor; i++){
			printf("%i ", vetor[i]);
		}*/

		int chave = 777;
		//printf("\nDigite a chave a ser buscada no vetor: ");
		//scanf("%d", &chave);

		clock_t inicio = clock();
		//busca do elemento desejado
		int posicao = buscaBinaria_recursiva(vetor, 0, tamanhoVetor-1, chave);
		//int posicao = buscaBinaria_iterativa(vetor, 0, tamanhoVetor-1, chave);
		clock_t final = clock();
		double tempo = (final-inicio)/(double)CLOCKS_PER_SEC;
		printf("Tempo de busca: %lf s\n", tempo);
		
		//resultado
		printf("A chave %i esta na posicao %i\n", chave, posicao);
		free(vetor);

	}
	
	return 0;	
}

int buscaBinaria_recursiva(int* vetor, int posicaoInicial, int posicaoFinal, int chave){
	if (posicaoFinal < posicaoInicial) return -1;

	int centro = (int) ((posicaoFinal + posicaoInicial)/2);
	
	if (chave == vetor[centro]) return centro;
	if (chave < vetor[centro]) return buscaBinaria_recursiva(vetor, posicaoInicial, centro-1, chave);
	return buscaBinaria_recursiva(vetor, centro+1, posicaoFinal, chave);
}


int buscaBinaria_iterativa(int* vetor, int posicaoInicial, int posicaoFinal, int chave){
	while (posicaoInicial <= posicaoFinal){
		int centro = (int) ((posicaoFinal + posicaoInicial)/2);

		if (chave == vetor[centro]) return centro;
		if (chave < vetor[centro]){
			posicaoFinal = centro - 1;
		}
		if (chave > vetor[centro]){
			posicaoInicial = centro +1;
		}
	}
	return -1;
}


/*
	Exercícios:
	OK 1) Melhore o código disponibilizado da Busca Binária Recursiva. 
		Defina a nova função de recorrência.
	OK 2) Encontre o melhor e pior caso para a Busca Binária, assim como o caso médio.
	3) Execute as implementações da Busca Sequencial e Binária para diferentes tamanhos de entrada. 
		Crie um gráfico que mostre o tempo de execução.
	4) Considerando a mesma ideia do exercício 3, crie um gráfico em termos da função 
		de recorrência.
	->>>> 5) Implemente uma função de busca que possua chaves no formato de caracteres.
		
	Referências:
		- Tenembaum, capítulo 7.
		- Ascencio, capítulo 2.
*/  