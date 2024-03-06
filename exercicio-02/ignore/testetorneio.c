#include <stdio.h>
#include <stdlib.h>

#define TAM 4
#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)<(b) ? (a) : (b))

void torneio_sort(int *vetor);
void torneio(int *vetor, int inicio, int fim);

int main(){
	int vetor[TAM] = {8, 10, 9, 7};
	int vetor_ordenado[TAM];

	torneio_sort(vetor);
}

void torneio_sort(int *vetor){
	int aux[2*TAM];

	for (int i = 0; i < TAM; i++){
		aux[i] = -1;
		aux[TAM+i] = vetor[i];
	} // -1 -1 -1 -1 8 10 9 7

	int *pos;
	int i = 0;
	int tam_ord =0;

	while (tam_ord < TAM){
		torneio(aux, TAM, 2*TAM-1);
		//aux[pos] = -1;
		vetor[i] = aux[1];
		i++;
		tam_ord++;

		for (int i = 0; i < TAM; i++){
			aux[i] = -1;
		} 
	}

	
	for (int j = 0; j < TAM; j++){
		printf("%d, ", vetor[j]);
	}
}

void torneio(int *vetor, int inicio, int fim){

	if (inicio <= 1) return;

	if (fim == inicio) return;
	if ((fim-inicio) == 1) {
		if (vetor[inicio] > vetor[fim]){
			vetor[(int) inicio/2] = vetor[inicio];
			//if (inicio > TAM){
			//	pos = inicio;
			//}

		} else {
			vetor[(int) inicio/2] = vetor[fim];
			//if (fim > TAM){
		//		pos = fim;
		//	}
		}
		return;
	}

	int centro = (int)(inicio+fim)/2;

	torneio(vetor, inicio, centro);
	torneio(vetor, centro+1, fim);

	int inicio_novo = (int) inicio/2;

	torneio(vetor, inicio_novo, inicio);
}