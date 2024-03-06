#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimeVetor(int* vetor, int tamanhoVetor){
	if (tamanhoVetor <= 100){
		int i;
		for (i=0; i<tamanhoVetor; i++)
			printf("%i ", vetor[i]);
	}
	printf("\n");
}

int* insertionSort(int* vetor, int tamanho);

int main(int argc, char* argv[]){
	int geracaoVetor = atoi(argv[1]);
	int tamanhoVetor = atoi(argv[2]);
	clock_t inicio, final;
	
	//geração dos elementos
	int *vetor = malloc(tamanhoVetor * sizeof(int));
	srand(time(NULL));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		if (geracaoVetor == 0) //aleatório
			vetor[i] = rand() % 1000;
		else if (geracaoVetor == 1) //ordenado
			vetor[i] = i;
		else if (geracaoVetor == 2) //invertido
			vetor[i] = tamanhoVetor - i;
		else if (geracaoVetor == 3 && i<=tamanhoVetor/2) //primeira metade ordenada e o restante aleatório
			vetor[i] = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleatório
			vetor[i] = (rand() % 1000) + i;
	}
	
	printf("Insertion Gerado: \n");
	imprimeVetor(vetor, tamanhoVetor);
	
	inicio = clock();
	vetor = insertionSort(vetor, tamanhoVetor);
	final = clock();
	
	printf("\nInsertion Ordenado: \n");
	imprimeVetor(vetor, tamanhoVetor);
	printf("Tempo de ordenacao Insertion: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetor);

	return 0;	
}

/*
	Ideia Geral:
		- Percorre um conjunto de elementos da esquerda para a direita 
			e à medida que avança vai deixando os elementos à esquerda ordenados, 
			ou seja, o elemento é "inserido" em sua posição.
		- Exemplo:
			[| 5 8 7 13 20 22 85 1 4 9] (elementos à esquerda de "|" estão ordenados)
			[5 | 8 7 13 20 22 85 1 4 9]
			[5 8 | 7 13 20 22 85 1 4 9] (troca 7 por 8)
			[5 7 | 8 13 20 22 85 1 4 9]
			[5 7 8 | 13 20 22 85 1 4 9]
			...
			[5 7 8 13 20 22 85 | 1 4 9] (movendo o valor 1)
				[5 7 8 13 20 22   | 85 4 9]
				[5 7 8 13 20   22 | 85 4 9]
				[  5 7 8 13 20 22 | 85 4 9]
				[1 5 7 8 13 20 22 | 85 4 9]
				[1 5 7 8 13 20 22 85 | 4 9]
			...
			[1 4 5 7 8 9 13 20 22 85 |]
		
		- Características:
			- Eficiente para ordenar um número pequeno de elementos.
			- Abordagem incremental.
			- Altamente dependente da ordem dos valores na entrada, 
				sendo bom para ordenados e parcialmente ordenados.
			- Melhor caso: sequência previamente ordenada.
			- Pior caso: sequência previamente ordenada de forma inversa.
*/

int* insertionSort(int* vetor, int tamanho){
	int j; //indica o elemento atual
	for(j = 1; j < tamanho; j++){//o elemento na posição 0 não precisa analisar
		int chave = vetor[j];
		int i = j - 1; //armazenar a posição de análise (anterior ao j até o início do vetor)
		
		//início && valor atual é maior que a chave de análise
		while (i >= 0 && vetor[i] > chave){
			vetor[i+1] = vetor[i];
			i--;
		}
		vetor[i+1] = chave; //posiciona a chave na posição correta
		//imprimeVetor(vetor, tamanho);
	}
	
	return vetor;
}

/*
	Exercícios:
	OK 1) Implemente o Insertion Sort para ordenar de forma decrescente.
	OK 2) Considere a ordenação de n números armazenados em um vetor, localizando o primeiro menor 
		elemento e permutando com o elemento contido na primeira posição. Em seguida, determine 
		o segundo menor elemento e permute com o elemento contido na segunda posição. 
		Continue assim para todos os elementos. (Selection Sort)
	3) Pesquise e implemente o Shell Sort, uma versão modificada do Insertion Sort.
	
	Referências:
		- Cormen, capítulo 2.
		- Ascencio, capítulo 2.
		- Tenembaum, capítulo 6.
		- Sedgewick, capítulo 2.
		- Wengrow, capítulo 6.
*/