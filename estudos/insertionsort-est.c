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
int* insertionSort_dec(int* vetor, int tamanho);
int *selection_sort(int *vetor, int tamanho);

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
	printf("\n-------------------\n");
	
	inicio = clock();
	vetor = selection_sort(vetor, tamanhoVetor);
	final = clock();
	
	printf("\nInsertion Ordenado: \n");
	imprimeVetor(vetor, tamanhoVetor);
	printf("Tempo de ordenacao Insertion: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetor);

	return 0;	
}


int* insertionSort(int* vetor, int tamanho){
	int chave, j;

	for (int i = 1; i < tamanho; i++){
		j = i-1;
		chave = vetor[i];

		while(chave < vetor[j] && j >= 0){
			vetor[j+1] = vetor[j];
			imprimeVetor(vetor, tamanho);
			j--;
		}
		vetor[j+1] = chave;
		imprimeVetor(vetor, tamanho);
	}

	return vetor;
}

int* insertionSort_dec(int* vetor, int tamanho){
	int chave, j;

	for (int i = 1; i < tamanho; i++){
		j = i-1;
		chave = vetor[i];

		while(chave > vetor[j] && j >= 0){
			vetor[j+1] = vetor[j];
			imprimeVetor(vetor, tamanho);
			j--;
		}
		vetor[j+1] = chave;
		imprimeVetor(vetor, tamanho);
	}

	return vetor;
}

int *selection_sort(int *vetor, int tamanho){
	imprimeVetor(vetor, tamanho);
	
	for (int j = 0; j < tamanho-1; j++){
		int menor = vetor[j];
		int ind = j;

		for (int i = j+1; i < tamanho; i++){
			if (vetor[i] < menor){
				menor = vetor[i];
				ind = i;
			}
		}
		vetor[ind] = vetor[j];
		vetor[j] = menor;
		imprimeVetor(vetor, tamanho);
	}
	return vetor;


}