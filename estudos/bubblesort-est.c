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

int *vetor_copy(int* vetor_original, int tamanho){
	int *vetor_copia = malloc(tamanho * sizeof(int));
	for(int i=0;i<tamanho;i++){
		vetor_copia[i] = vetor_original[i];
	}
	return vetor_copia;
}

int* bubbleSort_iterativo(int* vetor, int tamanho);
int* bubbleSort_iterativo_melhorado(int* vetor, int tamanho);
int* bubbleSort_recursivo(int* vetor, int tamanho);
int *bubbleSort_iterativo_reverso(int *vetor, int tamanho);

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

	printf("Bubble Gerado: \n");
	imprimeVetor(vetor, tamanhoVetor);

	printf("\n--------------------\n");
	int *vetor2 = vetor_copy(vetor, tamanhoVetor);
	int *vetor3 = vetor_copy(vetor, tamanhoVetor);
	int *vetor4 = vetor_copy(vetor, tamanhoVetor);
	
	inicio = clock();
	bubbleSort_iterativo(vetor, tamanhoVetor);
	final = clock();
	
	printf("\nBubble Ordenado: \n"); 
	imprimeVetor(vetor, tamanhoVetor);
	printf("Tempo de ordenacao Bubble: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);

	printf("\n----------------\n");

	inicio = clock();
	bubbleSort_iterativo_melhorado(vetor2, tamanhoVetor);
	final = clock();
	
	printf("\nBubble Ordenado Melhorado: \n"); 
	imprimeVetor(vetor2, tamanhoVetor);
	printf("Tempo de ordenacao Bubble Melhorado: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);

	printf("\n----------------\n");

	inicio = clock();
	bubbleSort_recursivo(vetor3, tamanhoVetor);
	final = clock();
	
	printf("\nBubble Ordenado Recursivo: \n"); 
	imprimeVetor(vetor3, tamanhoVetor);
	printf("Tempo de ordenacao Bubble Recursivo: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);

	printf("\n----------------\n");

	inicio = clock();
	bubbleSort_iterativo_reverso(vetor4, tamanhoVetor);
	final = clock();
	
	printf("\nBubble Ordenado Invertido: \n"); 
	imprimeVetor(vetor4, tamanhoVetor);
	printf("Tempo de ordenacao Bubble Invertido: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);

	free(vetor);
	free(vetor2);
	free(vetor3);
	free(vetor4);
	
	return 0;	
}

int *bubbleSort_iterativo(int *vetor, int tamanho){
	int aux;

	for (int j = 0; j < tamanho-1; j++){
		for (int i=0; i < tamanho-1-j; i++){
			if (vetor[i] > vetor[i+1]){
				aux = vetor[i+1];
				vetor[i+1] = vetor[i];
				vetor[i] = aux;
			}
		}
		imprimeVetor(vetor, tamanho);
	}

	return vetor;
}

int *bubbleSort_iterativo_reverso(int *vetor, int tamanho){
	int aux, trocou;

	for(int j = 0; j < tamanho-1; j++){
		trocou = 0;
		for (int i = tamanho-1; i >= 1+j; i--){
			if (vetor[i] < vetor[i-1]){
				aux = vetor[i-1];
				vetor[i-1]= vetor[i];
				vetor[i] = aux;
				trocou++;
			}
		}
		imprimeVetor(vetor, tamanho);
		if (trocou == 0) break;
	}
	return vetor;
}

int *bubbleSort_iterativo_melhorado(int *vetor, int tamanho){
	int aux, trocou;

	for (int j = 0; j < tamanho; j++){
		trocou = 0;

		for (int i=1; i < tamanho-j; i++){
			if (vetor[i-1] > vetor[i]){
				aux = vetor[i-1];
				vetor[i-1] = vetor[i];
				vetor[i] = aux;
				trocou++;
			}
		}

		imprimeVetor(vetor, tamanho);
		if (trocou == 0) break;
	}
	return vetor;
}

int *bubbleSort_recursivo(int* vetor, int tamanho){
	imprimeVetor(vetor, tamanho);
	if (tamanho == 1) return vetor;


	int aux;

	for (int i=1; i < tamanho; i++){
			if (vetor[i-1] > vetor[i]){
				aux = vetor[i-1];
				vetor[i-1] = vetor[i];
				vetor[i] = aux;
			}
	}
	return bubbleSort_recursivo(vetor, tamanho-1);
}

/*
	- Características:
		- Melhor caso: vetor previamente ordenado (impede as trocas)
		- Pior caso: vetor previamente ordenado inversamente (if será executado sempre)
		
	- Exercícios:
	OK  1) Implemente o BubbleSort de forma invertida, ou seja, garanta que o elemento ordenado	
		seja o menor
	OK  2) Execute e compare os diversos cenários para o Bubble (ordenado, inversamente ordenado,
		aleatório e parcialmente ordenado)

		Bubble normal: desempenho mediano no aleatório, ruim no ordenado, mediano no invertido
		e ruim no parcialmente ordenado (em comparação com os outros) -> comparações desnecessarias
		Bubble recursivo: ruim em memória, mediano no aleatório, ruim no ordenado, mediano no invertido,
		ruim no parcialmente (empata com o normal, geralmente)
		Bubble melhorado: geralmente melhor no aleatório, melhor no ordenado, mesma coisa q outros no 
		invertido, melhor no ordenado no começo
		Bubble melhorado invertido: mesma coisa do acima

		-> notas: no pior caso, todas as comprações devem ser feitas e tempo é quase igual
		as melhorias auxiliam os casos médios e o melhor caso, o que é vantajoso pois geralmente
		temos um caso médio
*/