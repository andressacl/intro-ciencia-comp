#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//algoritmo padrão:

int *gerar_vetor(int qtd, int min, int max){
	srand(time(NULL));
	int *vetor_gerado = (int*) malloc(qtd*sizeof(int));
	vetor_gerado[0] = min;
	printf("%i ", vetor_gerado[0]);

	for (int i = 1; i < qtd; i++){ //gera valores aleatórios entre minino e maximo
		//rand() % (20 - 11 + 1) + 11
		vetor_gerado[i] = rand() % (max-min+1) + min; //sem ordenação
		//vetor_gerado[i] = rand() % (max-min+1) + min + vetor_gerado[i-1]; //com ordenação 
		printf("%i ", vetor_gerado[i]);
	}
	return vetor_gerado;

}

int buscaSequencial_iterativa(int* vetor, int tamanho, int chave);
int buscaSequencial_recursiva(int* vetor, int tamanho, int chave);
int buscaSequencial_iterativa_ordenada(int*vetor, int tamanho, int chave);
int buscaSequencial_recursiva_ordenada(int* vetor, int tamanho, int chave);

void mover_para_a_frente(int *vetor, int pos);
void transpor(int *vetor, int pos);

int main(int argc, char* argv[]){
	int qtd = atoi(argv[1]);
	int min = atoi(argv[2]);
	int max = atoi(argv[3]);

	int *vetor = gerar_vetor(qtd, min, max);

	int chave;
	printf("\nDigite a chave a ser buscada: ");
	scanf("%i", &chave);

	clock_t inicio = clock();
	int pos = buscaSequencial_iterativa(vetor, qtd, chave);
	//int pos = buscaSequencial_iterativa_ordenada(vetor, qtd, chave);
	//int pos = buscaSequencial_recursiva(vetor, qtd, chave);
	//int pos = buscaSequencial_recursiva_ordenada(vetor, qtd, chave);
	clock_t fim = clock();

	double tempo = (fim - inicio)/(double)CLOCKS_PER_SEC;
	printf("Tempo de busca: %lf s\n", tempo);

	if (pos >= 0){
		printf("Chave encontrada na posição %i", pos);
	} else{
		printf("Chave não encontrada");
	}

	printf("\nVetor: ");
	for(int i=0;i<qtd;i++){
		printf("%i ", vetor[i]);
	}

	free(vetor);
}

/*
A = atribuição e aritmetica
C = comparação
F = retorno/acesso função
V = acesso a elem. de vetor
*/

/*int buscaSequencial_iterativa(int* vetor, int tamanho, int chave){
	for (int i = 0; i<tamanho;i++){ // (A+C) + (C+2A)*n [nao encontrado] ou (A+C) + (C+2A)(n-1) [enc. na ultima pos.]
									// (C) + (C)*n ou (C)+ (C)*(n-1)						
		if (chave == vetor[i]) return i; // (V+C)*n
										 // C*n
	}									// F (um só) -> 1
	return -1;
} //-> 5n + 3 ou 5n (cons. sucesso)
  // Considerando só C -> 2C*n -> 2n (O(n)) 

  */

int buscaSequencial_iterativa(int* vetor, int tamanho, int chave){
	for (int i = 0; i<tamanho;i++){ 					
		if (chave == vetor[i]) {
			transpor(vetor, i);
			return i;
		}
	}
	return -1;
}

int buscaSequencial_iterativa_ordenada(int*vetor, int tamanho, int chave){
	for (int i=0; i<tamanho; i++){
		if (chave < vetor[i]) return -1;
		if (chave == vetor[i]) return i;
		return -1;
	}
}

int buscaSequencial_recursiva(int *vetor, int tamanho, int chave){
	if (vetor[tamanho-1] == chave) return tamanho-1; // V+A+C
	if (tamanho==0) return -1;							//C
	return (buscaSequencial_recursiva(vetor, tamanho-1, chave)); //F
}

int buscaSequencial_recursiva_ordenada(int *vetor, int tamanho, int chave){
	if (vetor[tamanho-1] == chave) return tamanho-1; // V+A+C
	if (tamanho==0 || vetor[tamanho-1] < chave) return -1;							//C
	return (buscaSequencial_recursiva(vetor, tamanho-1, chave)); //F
}

void mover_para_a_frente(int *vetor, int pos){
	int aux = vetor[pos];
	for (int i=pos-1; i>=0;i--){
		vetor[i+1] = vetor[i];
	}
	vetor[0]=aux;
}	

void transpor(int *vetor, int pos){
	int aux = vetor[pos];
	vetor[pos]=vetor[pos-1];
	vetor[pos-1]=aux;
}

/*
Considerando somente comparações:
	f(n)= 2+f(n-1)
	f(n-1)= 2 + [2+f(n-2)] = 4+f(n-2)
	f(n-2) = 4+[2+f(n-3)]
	...
	f(n-k)=2*k+[f(n-k)] mas f(n-k)=f(1)=1 -> k=n-1 ->f(n-k)=2(n-1)+1=2n-2+1=>2n-1

	f(n)=2*n-1 => O(n)

*/

/*
	Exercícios:
	OK 1) Refaça a contagem da versão iterativa considerando somente comparações (2n)
	OK 2) Modifique a Busca Sequencial para casos em que o vetor já esteja ordenado, 
			acrescentando uma validação para interrromper a busca.
	OK 3) Modifique a Busca Sequencial para incorporar o Método mover-para-frente. 
			Esta metodologia consiste em reduzir o tempo de busca realocando o item encontrado 
			para o início da lista/vetor para uma próxima busca. Assim, elementos mais 
			frequentementes buscados estarão no início e os menos frequentes estarão no final. 
			O elemento de retorno deve ser colocado no início e todos os demais (início até 
			sua posição vaga são realocados).
	OK 4) Modifique a Busca Sequencial para incorporar o Método da transposição. 
		Esta metodologia consiste em reduzir o tempo de busca realocando o item encontrado 
		em uma posição anterior à sua original, movendo seu antecessor para a posição vaga.
		
	Referências:
		- Tenembaum, capítulo 7.
		- Ascencio, capítulo 2.
*/
