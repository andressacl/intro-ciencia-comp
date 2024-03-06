#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//algoritmo padrão:

int *gerar_vetor(int qtd){
	srand(time(NULL));
	int *vetor_gerado = (int*) malloc(qtd*sizeof(int));

	for (int i = 0; i < qtd; i++){
		vetor_gerado[i] = rand() % 100; //sem ordenação
		printf("%i ", vetor_gerado[i]);
	}
	return vetor_gerado;

}

void print_vetor(int *vetor, int tam){
	for(int i=0;i<tam;i++){
		printf("%i ", vetor[i]);
	}
	printf("\n");
}

int *ordenar(int *vetor, int tam){

	if (tam == 1) return vetor;

	int ult_ind = tam-1;
	int ind_maior = 0;
	int maior = vetor[ind_maior];
	for (int i = 0; i < tam; i++){
		if (vetor[i] > maior){
			maior = vetor[i];
			ind_maior = i;
		}
	}

	vetor[ind_maior] = vetor[ult_ind];
	vetor[ult_ind] = maior;

	return ordenar(vetor, tam-1);
}

int buscaBinaria(int *vetor, int posInicial, int posFinal, int chave){
	int centro = (int) (posFinal+posInicial)/2;
	if (posFinal < posInicial) return -1;
	if (chave == vetor[centro]) return centro;
	if (chave < vetor[centro]) return buscaBinaria(vetor, posInicial, centro-1, chave);
	if (chave > vetor[centro]) return buscaBinaria(vetor, centro+1, posFinal, chave);
}

int main(int argc, char* argv[]){
	int qtd = atoi(argv[1]);
	int *vetor = gerar_vetor(qtd);

	vetor = ordenar(vetor, qtd);

	printf("\n");
	print_vetor(vetor, qtd);

	int chave;
	scanf("%i", &chave);

	printf("Buscando chave %d\n", chave);

	int pos = buscaBinaria(vetor, 0, qtd-1, chave);
	printf("Chave na posição %d\n", pos);
	
	free(vetor);
}
