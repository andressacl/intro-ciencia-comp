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

int* bubbleSort_iterativo(int* vetor, int tamanho);
int* bubbleSort_recursivo(int* vetor, int tamanho, int i);

int main(int argc, char* argv[]){
	int geracaoVetor = atoi(argv[1]);
	int tamanhoVetor = atoi(argv[2]);
	clock_t inicio, final;
	
	//gera��o dos elementos
	int *vetor = malloc(tamanhoVetor * sizeof(int));
	srand(time(NULL));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		if (geracaoVetor == 0) //aleat�rio
			vetor[i] = rand() % 1000;
		else if (geracaoVetor == 1) //ordenado
			vetor[i] = i;
		else if (geracaoVetor == 2) //invertido
			vetor[i] = tamanhoVetor - i;
		else if (geracaoVetor == 3 && i<=tamanhoVetor/2) //primeira metade ordenada e o restante aleat�rio
			vetor[i] = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleat�rio
			vetor[i] = (rand() % 1000) + i;
	}

	printf("Bubble Gerado: \n");
	imprimeVetor(vetor, tamanhoVetor);
	
	inicio = clock();
	bubbleSort_iterativo(vetor, tamanhoVetor);
	final = clock();
	
	printf("\nBubble Ordenado: \n"); 
	imprimeVetor(vetor, tamanhoVetor);
	printf("Tempo de ordenacao Bubble: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetor);
	
	return 0;	
}

/*
	Otimiza��es em rela��o � vers�o original:
		- condi��o de parada segundo FOR: tamanho-1-i (para interromper compara��es desnecess�rias)
		- vari�vel trocou: quando trocou permanece 0 indica que o vetor j� est� ordenado
*/

int* bubbleSort_iterativo(int* vetor, int tamanho){
	int i, j, trocou;
	for(i = 0; i < tamanho-1; i++){ 
		trocou = 0;
		for(j = 0; j < tamanho-1-i; j++){
			if (vetor[j] > vetor[j+1]){
				int aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
				trocou = 1;
			}
		}
		if (trocou == 0)
			break;
	}
	
	return vetor;
}	

/*	
	Contagem de opera��es (vers�o iterativa):
	- Primeiro for: (n-1) --> (considerar que o trocou sempre ir� ocorrer (pior caso)
	- Segundo for: 
		1a.(n-1-0) = n-1; 
		2a.(n-1-1) = n-2; 
		3a.(n-1-2) = n-3; 
		...
		ka.(n-1-(n-2)) = 1 (k vez ser� a posi��o 1, ou seja, n-2 menor valor de i) ent�o
		
		somatorio (n-i-1) de i=0 at� n-2 ou 
		somatorio (n-k) de k=1 at� n-1
	
	Por meio de Progress�o Aritm�tica: ((n�mero de termos*(primeiro termo+ultimo termo))/2
		f(n) = ((n-1).((n-1)+1))/2 = ((n-1).(n))/2 = (n.n - n)/2
		
	Exerc�cio:
	1) Se considermos todas as compara��es:
	- Primeiro for: (n-1)
	- Segundo for: 
		1a.(n-1-0) = (n-1).2 = 2n-2; 
		2a.(n-1-1) = (n-2).2 = 2n-4; 
		3a.(n-1-2) = (n-3).2 = 2n-6;
	continuar....
*/

int* bubbleSort_recursivo(int* vetor, int tamanho, int i){
	if (i >= tamanho - 1) return vetor;

	int j;
	for(j = 0; j < tamanho-1-i; j++){
		if (vetor[j] > vetor[j+1]){
			int aux = vetor[j];
			vetor[j] = vetor[j+1];
			vetor[j+1] = aux;		
		}
	}
	return bubbleSort_recursivo(vetor, tamanho, i+1);
}

/*	
	Contagem de opera��es (vers�o recursiva):
	f(n) = c.(n-1) + f(n-1) 								-> primeira execu��o
	f(n) = c.(n-1) + c.(n-2) + f(n-2)						-> segunda execu��o
	f(n) = c.(n-1) + c.(n-2) + c.(n-3) + f(n-3)				-> terceira execu��o
	f(n) = c.(n-1) + c.(n-2) + c.(n-3) + ... c.(n-k) + f(1)	-> execu��o total
	f(1) = 1                                            	-> vetor de tamanho = 1 (caso base)

	f(n) = somat�rio (c.(n-i)) + f(n-k) de i=1 at� k	-> recorr�ncia gen�rica
	com o caso base: f(1) = 1 -> f(1) = f(n-k) ent�o n-k = 1 -> k = n-1
	
	retomando:
	f(n) = somat�rio (c.(n-i)) + 1 de i=1 at� n-1
	f(n) = c.somat�rio (n-i) + 1 de i=1 at� n-1
	
	Por meio de Progress�o Aritm�tica: ((n�mero de termos*(primeiro termo+ultimo termo))/2
	f(n) = ((n-1).((n-1)+(n-(n-1))))/2 = c[(n.n - n)/2] + 1
*/

/*
	Refer�ncias:
		- Ascencio, cap�tulo 2.
		- Tenembaum, cap�tulo 6.
		- Wengrow, cap�tulo 4.
*/