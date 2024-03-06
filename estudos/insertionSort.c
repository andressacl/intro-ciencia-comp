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

int* insertionSort(int* vetor, int tamanho){
	int j;
	for(j = 1; j < tamanho; j++){ //n-1
		int chave = vetor[j];
		int i = j - 1;
		
		while (i >= 0 && vetor[i] > chave){
			vetor[i+1] = vetor[i];
			i--;
		}
		vetor[i+1] = chave; 
		//imprimeVetor(vetor, tamanho);
	}
	
	return vetor;
	
	/*
	Complexidade:
		- For: (n-1)
		- While: 
			(i = 0) 1a. (2); 
			(i = 1) 2a. (3);
			(i = 2) 3a. (4);
			...
			(i = n-1) ka. (n);  --> mover todas as posições
		- caso base: (vetor ordenado de tamanho 1): 1
		
		f(n) = somatorio (i+1) de i=0 até n-1 ou
		f(n) = (somatorio (i))-1 de i=1 até n

		Por meio de Progressão Aritmética: ((número de termos*(primeiro termo+ultimo termo))/2
		f(n) = (n.(1+n))/2 - 1
		f(n) = (n^2 + n)/2 - 1
	*/
}

/*
	Referências:
		- Cormen, capítulo 2.
		- Ascencio, capítulo 2.
		- Tenembaum, capítulo 6.
		- Sedgewick, capítulo 2.
		- Wengrow, capítulo 6.
*/