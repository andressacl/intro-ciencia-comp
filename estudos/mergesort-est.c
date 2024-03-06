#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimeVetor(int* vetor, int inicio, int fim){
	if (fim-inicio <= 100){
		int i;
		for (i=inicio; i <= fim; i++)
			printf("%i ", vetor[i]);
	}
	printf("\n");
}

void imprimeVetor2(int* vetor, int tamanhoVetor){
	if (tamanhoVetor <= 100){
		int i;
		for (i=0; i<tamanhoVetor; i++)
			printf("%i ", vetor[i]);
	}
	printf("\n");
}


void mergeSort(int* vetor, int inicio, int fim);
void intercala(int* vetor, int inicio, int centro, int fim);
int* insertionSort(int* vetor, int inicio, int centro, int fim);

int main(int argc, char* argv[]){
	int geracaoVetor = atoi(argv[1]);
	int tamanhoVetor = atoi(argv[2])+1;
	clock_t inicio, final;
	
	//geração dos elementos
	int *vetor = malloc(tamanhoVetor * sizeof(int));
	srand(time(NULL));
	
	int i;
	//vetor[0] = -1;
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

	printf("Merge Gerado: ");
	imprimeVetor(vetor, 0, tamanhoVetor-1);
	printf("\n---------------------\n");
	
	inicio = clock();
	mergeSort(vetor, 0, tamanhoVetor-1);
	final = clock();
	

	printf("\n---------------------\n");
	printf("Merge Ordenado: "); 
	imprimeVetor(vetor, 0, tamanhoVetor-1);
	printf("Tempo de ordenacao Merge: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetor);
	
	return 0;	
}

void mergeSort(int* vetor, int inicio, int fim){
	imprimeVetor(vetor, inicio, fim);

	if (inicio >= fim) return; //caso base

	int centro = (int) (inicio+fim)/2;
	mergeSort(vetor, inicio, centro);
	mergeSort(vetor, centro+1, fim);

	//intercala(vetor, inicio, centro, fim);
	vetor = insertionSort(vetor, inicio, centro, fim);
	printf("Intercala: "); imprimeVetor(vetor, inicio, fim);
}

void intercala(int* vetor, int inicio, int centro, int fim){
	int *vetor_aux = (int*) malloc(sizeof(int)*(fim+1-inicio));

	int i = inicio;
	int j = centro+1;
	int k = 0;

	while(i <= centro && j <= fim){
		if (vetor[i] <= vetor[j]){
			vetor_aux[k] = vetor[i];
			i++;
		} else {
			vetor_aux[k] = vetor[j];
			j++;
		}

		k++;
	}

	while (i <= centro){
		vetor_aux[k] = vetor[i];
		k++;
		i++;
	}

	while (j <= fim){
		vetor_aux[k] = vetor[j];
		k++;
		j++;
	}

	for(i = inicio, k = 0; i <= fim; i++, k++) 
		vetor[i] = vetor_aux[k];

	free(vetor_aux);
}

int* insertionSort(int* vetor, int inicio, int centro, int fim){
	int chave, j;

	for (int i = inicio+1; i <= fim; i++){
		j = i-1;
		chave = vetor[i];

		while(chave < vetor[j] && j >= 0){
			vetor[j+1] = vetor[j];
			//imprimeVetor2(vetor, tamanho);
			j--;
		}
		vetor[j+1] = chave;
		//imprimeVetor2(vetor, tamanho);
	}

	return vetor;
}