#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BASE 256
#define SHIFT 8

typedef struct{
	int key;
	int value;
	//outros atributos
} Record;

void imprimeVetor(Record* vetor, int tamanhoVetor, int shift){
	if (tamanhoVetor <= 100){
		int i;
		for (i=0; i<tamanhoVetor; i++)
			if (shift >= 0)
				printf("key[%i] - value %i - shift %i\n", vetor[i].key, vetor[i].value, 
					(vetor[i].key >> shift) & BASE-1);
			else
				printf("key[%i] - value %i \n", vetor[i].key, vetor[i].value);
	}
	printf("\n");
}

void radixSortCounting(Record* vetor, int tamanho);

int main(int argc, char* argv[]){
	int geracaoVetor = atoi(argv[1]);
	int tamanhoVetor = atoi(argv[2]);
	clock_t inicio, final;
	
	//geração dos elementos
	Record* vetor = (Record*) malloc(tamanhoVetor * sizeof(Record));
	srand(time(NULL));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		if (geracaoVetor == 0) //aleatório
			vetor[i].key = rand() % 500000;
		else if (geracaoVetor == 1) //ordenado
			vetor[i].key = i;
		else if (geracaoVetor == 2) //invertido
			vetor[i].key = tamanhoVetor - i;
		else if (geracaoVetor == 3 && i<=tamanhoVetor/2) //primeira metade ordenada e o restante aleatório
			vetor[i].key = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleatório
			vetor[i].key = (rand() % 1000) + i;
		vetor[i].value = -(rand() % 50);
	}
	
	printf("Radix Gerado: \n");
	imprimeVetor(vetor, tamanhoVetor, -1);
	
	inicio = clock();
	radixSortCounting(vetor, tamanhoVetor);
	final = clock();
	
	printf("Radix Ordenado: \n"); 
	imprimeVetor(vetor, tamanhoVetor, -1);
	printf("Tempo de ordenacao Radix: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetor);

	return 0;	
}

/*
	Ideia Geral:
	- divide a chave em partes segundo uma base (8, 10, 256, ...)
	- para cada parte aplica CountingSort ou BucketSort

	Exemplo: [70 9 25 105 472 371 290 230 41 36 99 101 76 6] -> 14 elementos
	- para bucket ou counting teríamos (472 - 6 + 1 = 467) chaves, ou seja, 
		467 filas ou espaços em um vetor de contagem
	- assim, n=14 e k=467; idealmente, queremos k<=n
	- com radix, o tamanho de "k" passa a ser o valor da base que escolhemos
	- a ideia é fazer alinhamentos considerando dígitos menos significativos para os mais 
		significativos, executando Bucket ou Counting "d" vezes

	Executando: [070 009 025 105 472 371 290 230 041 036 099 101 076 006] para a base 10
	- considerar somente o dígito menos significativo (unidade):  
		[070 290 230 371 041 101 472 025 105 036 076 006 009 099] -> com Counting ou Bucket O(n+10)
	- considerar somente o segundo dígito menos significativo (dezena):  
		[101 105 006 009 025 230 036 041 070 371 472 076 290 099] -> com Counting ou Bucket O(n+10)
	- considerar somente o terceiro dígito menos significativo (centena):  
		[006 009 025 036 041 070 076 099 101 105 230 290 371 472] -> com Counting ou Bucket O(n+10)

	Complexidade:
		1) Counting Sort: O(n+k)
		2) Radix Sort: O(d(n+k))
	Neste exemplo:
		1) Counting Sort: O(14+467) = 481
		2) Radix Sort: O(3(14+10)) = 72
		
	Na prática é muito comum utilizar 256 como base, pois:
	- inteiros geralmente possuem 32 bits, gerando 4 partições de 8 bits (1 byte) -> 4 iterações
	- cada partição varia de 0 a 255, ou seja, 1 dígito!
	- extremos, base 2^1 (32 partições de 1 bit), executa-se 32 vezes
	- extremos, base 2^32 (1 partição de 32 bits), executa-se 1 vez -> Counting e Bucket originais!
	- bases que não sejam 2^i são complexas de implementar:
		- inteiros de 32 bits e base 32 (2^5 - 5 bits) -> 7 iterações
		- inteiros de 32 bits e base 16 (2^4 - 4 bits) -> 8 iterações
		- inteiros de 32 bits e base 25 --> quantos bits???
		
	base 256 - 2^8 = 8 bits
	00010010111011101111011110111101
	
	00010010 | 11101110 | 11110111 | 10111101
	
	base 128 - 2^7 = 7 bits
	0001 | 0010111 | 0111011 | 1101111 | 0111101
*/

void radixSortCounting(Record* vetor, int tamanho){
	//alocação dos vetores e vetor de cópia
	//não precisamos percorrer o vetor para encontrar o mínimo e máximo!
	int contagem[BASE] = {0};
	int acumulada[BASE];
	Record* copia = (Record*) malloc(tamanho * sizeof(Record));

	//particionar a chave em dígitos seguindo a base, utilizando a base = 256

	//primeira iteração com 32 bits (precisamos do bit 0 ao 7)
	//qqqqqqqqwwwwwwwweeeeeeeerrrrrrrr (entrada)
	//                        &&&&&&&& (operador bit-a-bit)
	//00000000000000000000000011111111 (modificador = 255)
	//000000000000000000000000rrrrrrrr (saída)  -> 0 a 255

	//segunda iteração com 32 bits (precisamos do bit 8 ao 15)
	//qqqqqqqqwwwwwwwweeeeeeeerrrrrrrr (entrada)
	//00000000qqqqqqqqwwwwwwwweeeeeeee (deslocamento 8) >>
	//                        &&&&&&&& (operador bit-a-bit)
	//00000000000000000000000011111111 (modificador = 255)
	//000000000000000000000000eeeeeeee (saída)

	//terceira iteração com 32 bits (precisamos do bit 16 ao 23)
	//qqqqqqqqwwwwwwwweeeeeeeerrrrrrrr (entrada)
	//0000000000000000qqqqqqqqwwwwwwww (deslocamento 16)
	//                        &&&&&&&& (operador bit-a-bit)
	//00000000000000000000000011111111 (modificador = 255)
	//000000000000000000000000wwwwwwww (saída)

	int i, shift;
	for (shift = 0; shift <= 32-SHIFT; shift += SHIFT){ //controle do radix
		//Counting Sort: contagem + cópia
		for (i = 0; i < tamanho; i++){
			short k = (vetor[i].key >> shift) & BASE-1;
			contagem[k]++;
			copia[i] = vetor[i];
		}

		//Counting Sort: contagem acumulada
		acumulada[0] = 0;
		for (i = 1; i < BASE; i++){
			acumulada[i] = acumulada[i-1] + contagem[i-1];
			contagem[i-1] = 0; //zerando a posição para a próxima iteração do Radix
		}

		//Counting Sort: posicionar os elementos
		for (i = 0; i < tamanho; i++){
			short k = (copia[i].key >> shift) & BASE-1;
			vetor[acumulada[k]] = copia[i];
			acumulada[k]++;
		}
		
		printf("Final da iteracao %i: \n", (int)(shift/8)+1);
		imprimeVetor(vetor, tamanho, shift);
	}

	free(copia);
}

/*
	amplitude de 10; n = 1000 -> Counting
	amplitude de 10000; n = 1000 -> Radix 
	
	Assim, no RadixSort:
	- o tamanho de k (base) é fixo para Counting ou Bucket
	- o tamanho da base indica quantas iterações serão necessárias para o Radix:
		- inteiros de 32 bits e base 256 (2^8 - 8 bits) -> 4 iterações
		- inteiros de 32 bits e base 128 (2^7 - 7 bits) -> 5 iterações
		- inteiros de 32 bits e base 64 (2^6 - 6 bits) -> 6 iterações
		- inteiros de 32 bits e base 32 (2^5 - 5 bits) -> 7 iterações
		- inteiros de 32 bits e base 16 (2^4 - 4 bits) -> 8 iterações
		- inteiros de 32 bits e base 8 (2^3 - 3 bits) -> 11 iterações
		- inteiros de 32 bits e base 4 (2^2 - 2 bits) -> 16 iterações
		- inteiros de 32 bits e base 2 (2^1 - 1 bit) -> 32 iterações
	- com entradas pequenas, Radix não é favorável, pois tem todo o controle das partições
	- se a amplitude das chaves for pequena, Radix também não é favorável (Counting ou Bucket!!)
	- Radix é ideal para entradas grandes e chaves esparsadas
	- a vantagem do Radix é a desvantagem do Counting e Bucket; e o contrário também!

	Métodos lineares são preferíveis aos métodos comparativos?
	- Embora métodos lineares (Counting, Bucket e Radix) executem menos instruções, 
		eles podem ter tempo maior de execução (alocação de memória)
	- Tudo depende da implementação, máquina utilizada e dados de entrada
	- Máquinas com pouca memória devem priorizar métodos in-place.
*/

/*
	Exercícios:
	1) Com a implementação disponibilizada, modifique a base do RadixSort para 2, 64 e 128. 
		Compare os testes de execução em relação à base 256 para n = 100000. 
		Qual base possibilita a melhor performance?
	2) Implemente o RadixSort que é fundamentado no BucketSort.
	3) Teste o Radix Sort gerando 100 chaves contidas nos seguintes intervalos: 
		a) [0 a 50]; b[0, 5000]. Compare o texto de execução e memória necessária destes 
		cenários do RadixSort com o CountingSort e BucketSort. Utilize a base 256.
	
	Referências:
		- Cormen, capítulo 8.
*/