#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* bubbleSort(int* vetor, int tamanho){
	int i, j;
	for(i = 0; i < tamanho-1; i++){
		for(j = 0; j < tamanho-1; j++){
			if (vetor[j] > vetor[j+1]){
				int aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;		
			}
		}
	}
	
	return vetor;
}

int* insertionSort(int* vetor, int tamanho){
	int j;
	for(j = 1; j < tamanho; j++){
		int chave = vetor[j];
		int i = j - 1;
		while (i >= 0 && vetor[i] > chave){
			vetor[i+1] = vetor[i];
			i--;
		}
		vetor[i+1] = chave;
	}
	
	return vetor;
}

void intercala(int* vetor, int inicio, int centro, int fim){
	int* vetorAux = (int*)malloc(sizeof(int) * (fim-inicio)+1);

	int i = inicio;
	int j = centro+1;
	int k = 0;

	while(i <= centro && j <= fim){
		if (vetor[i] <= vetor[j]){
			vetorAux[k] = vetor[i];
			i++;
		}
		else{
			vetorAux[k] = vetor[j];
			j++;
		}
		k++;
	}

	while(i <= centro){
		vetorAux[k] = vetor[i];
		i++;
		k++;
	}

	while(j <= fim){
		vetorAux[k] = vetor[j];
		j++;
		k++;
	}

	for(i = inicio, k = 0; i <= fim; i++,k++)
		vetor[i] = vetorAux[k];
	free(vetorAux);
}

void mergeSort(int* vetor, int inicio, int fim){
	if (fim <= inicio) return; 
	
	int centro = (int)((inicio+fim)/2.0);
	mergeSort(vetor, inicio, centro);
	mergeSort(vetor, centro+1, fim);

	intercala(vetor, inicio, centro, fim);
}

int main(int argc, char* argv[]){
	int geracaoVetor = atoi(argv[1]);
	int tamanhoVetor = atoi(argv[2]);
	clock_t inicio, final;
	
	int *vetorInsertion = malloc(tamanhoVetor * sizeof(int));
	int *vetorMerge = malloc(tamanhoVetor * sizeof(int));
	int *vetorBubble = malloc(tamanhoVetor * sizeof(int));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		if (geracaoVetor == 0) //aleatório
			vetorInsertion[i] = rand() % 1000000;
		else if (geracaoVetor == 1) //ordenado
			vetorInsertion[i] = i;
		else if (geracaoVetor == 2) //invertido
			vetorInsertion[i] = tamanhoVetor - i;
		else if (geracaoVetor == 3 && i<=tamanhoVetor/2) //primeira metade ordenada e o restante aleatório
			vetorInsertion[i] = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleatório
			vetorInsertion[i] = (rand() % 1000) + i;
		vetorMerge[i] = vetorInsertion[i];
		vetorBubble[i] = vetorInsertion[i];
	}
	
	inicio = clock();
	bubbleSort(vetorBubble, tamanhoVetor);
	final = clock();
	printf("Tempo de ordenacao Bubble: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetorBubble);
	
	inicio = clock();
	vetorInsertion = insertionSort(vetorInsertion, tamanhoVetor);
	final = clock();
	printf("Tempo de ordenacao Insertion: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetorInsertion);

	inicio = clock();
	mergeSort(vetorMerge, 0, tamanhoVetor-1);
	final = clock();
	printf("Tempo de ordenacao Merge: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetorMerge);

	
	
	return 0;	
}

/*
	Aleatório:
	n 			Bubble		Insertion		Merge
	10000		 0,265625s	0,062500s	 0,000000s
	100000		29,265625s	6,609375s	 0,015625s
	
	Ordenado:
	n 			Bubble		Insertion		Merge
	10000		 0,109375s	0,00000s	 0,000000s
	100000		10,890625s	0,00000s	 0,015625s

	Inversamente:
	n 			Bubble		Insertion		Merge
	10000		 0,171875s	 0,109375s	 0,000000s
	100000		21,390625s	13,281250s	 0,000000s

	Parcialmente:
	n 			Bubble		Insertion		Merge
	10000		 0,109375s	0,000000s	 0,000000s
	100000		10,625000s	0,031250s    0,015625s
	
	Bubble:
		- independentemente da entrada, todas as comparações serão executadas
		- ordenado tem o tempo reduzido somente pela ausência das trocas
	Insertion:
		- inversamente é claramente a pior execução, enquanto o ordenado é o melhor sempre
		- o melhor caso é comparável ao MergeSort
	Merge:
		- em relação aos três métodos é o melhor de forma geral
*/