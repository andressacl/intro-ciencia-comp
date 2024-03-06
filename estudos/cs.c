#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	int key;
	int value;
	//outros atributos
} Record;

void imprimeVetor(Record* vetor, int tamanhoVetor){
	if (tamanhoVetor <= 100){
		int i;
		for (i=0; i<tamanhoVetor; i++)
			printf("chave [%i] valor %i\n", vetor[i].key, vetor[i].value);
	}
	printf("\n");
}

void countingSort(Record* vetor, int tamanho);

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
			vetor[i].key = rand() % 1000;
		else if (geracaoVetor == 1) //ordenado
			vetor[i].key = i;
		else if (geracaoVetor == 2) //invertido
			vetor[i].key = tamanhoVetor - i;
		else if (geracaoVetor == 3 && i<=tamanhoVetor/2) //primeira metade ordenada e o restante aleatório
			vetor[i].key = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleatório
			vetor[i].key = (rand() % 1000) + i;
		vetor[i].value = -(rand() % 1000);
	}
	
	printf("Counting Gerado:\n");
	imprimeVetor(vetor, tamanhoVetor);
	
	inicio = clock();
	countingSort(vetor, tamanhoVetor);
	final = clock();
	
	printf("Counting Ordenado:\n"); 
	imprimeVetor(vetor, tamanhoVetor);
	printf("Tempo de ordenacao Counting: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetor);

	return 0;	
}

/*
	Ideia Geral:
		- De forma geral, os melhores algoritmos de comparação são n.log(n)
		- Para melhorar isso temos que focar no problema e não nos algoritmos!
		- Counting Sort é fundamentado em contagens e não comparações
		- O ganho na complexidade f(n) < n.log(n) vem com o custo adicional 
			de alocação de memória auxiliar.
		- Já provou que não é possível vencer a complexidade n.log(n) sem o uso de memória extra
	
	Exemplo com structs: [1 5 0 0 5 1 2 5 3 1] - keys
		- 1) Cópia completa dos dados originais.
		- 2) Alocação de memória (referência das chaves a serem ordenadas):
			2.1) Percorrer as chaves e verificar o mínimo e máximo (mínimo = 0; máximo = 5)
			2.2) Criação de um vetor adicional de contagem (tamanho 6, ou seja, de 0 a 5): 
				[0 0 0 0 0 0]
			2.3) Percorrer o vetor de contagem com o somatório por chave:
				[2 3 1 1 0 3]
		- 3) Contagem acumulada de frequências (chaves discretas)
				[0 2 5 6 7 7]
		- 4) Posicionamento de chaves (forma ordenada)
			                        i    
			- vetor de cópia [1 5 0 0 5 1 2 5 3 1]

	original			  contagem acumulada
 0 1 2 3 4 5 6 7 8 9      0 1 2 3 4 5
[1 5 0 0 5 1 2 5 3 1]	 [0 2 5 6 7 7]  - chave 1 para a posição 2; posiciona e soma posição;
[1 5 1 0 5 1 2 5 3 1]	 [0 3 5 6 7 7]  - chave 5 para a posição 7; posiciona e soma posição;
[1 5 1 0 5 1 2 5 3 1]	 [0 3 5 6 7 8]  - chave 0 para a posição 0; posiciona e soma posição;
[0 5 1 0 5 1 2 5 3 1]	 [1 3 5 6 7 8]  - chave 0 para a posição 1; posiciona e soma posição;
[0 0 1 0 5 1 2 5 5 1]	 [2 3 5 6 7 8]  - chave 5 para a posição 8; posiciona e soma posição;
[0 0 1 1 5 1 2 5 5 1]	 [2 3 5 6 7 9]  - chave 1 para a posição 3; posiciona e soma posição;
[0 0 1 1 5 2 2 5 5 1]	 [2 4 5 6 7 9]  - chave 2 para a posição 5; posiciona e soma posição;
[0 0 1 1 5 2 2 5 5 1]	 [2 4 6 6 7 9]  - chave 5 para a posição 9; posiciona e soma posição;
[0 0 1 1 5 2 2 5 5 5]	 [2 4 6 6 7 10] - chave 3 para a posição 6; posiciona e soma posição;
[0 0 1 1 5 2 3 5 5 5]	 [2 4 6 7 7 10] - chave 1 para a posição 4; posiciona e soma posição;
[0 0 1 1 1 2 3 5 5 5]	 [2 5 6 7 7 10] - fim
	
	Observação:
	- a ordem relativa dos elementos de uma mesma chave é mantida (algoritmo estável)
	- requer dois vetores auxiliares: um de tamanho n e outro de tamanho k
	- a função de eficiência é totalmente dependente da quantidade de chaves (k)
	- se todas as chaves são diferentes e sequenciais, então k=n
	- é necessário adaptações para os casos em que temos chaves negativas ou que não comece em 0.
	- se as chaves são números decimais é preciso aplicar um processo de discretização.
*/

void countingSort(Record* vetor, int tamanho){
	//1) Cópia completa dos dados originais.
	Record* vetorAux = (Record*) malloc(tamanho * sizeof(Record));
	
	//2.1) Percorrer as chaves e verificar o mínimo e máximo
	int max, min;
	max = min = vetor[0].key;
	
	int i = 0;
	for(i = 0; i<tamanho; i++){
		if (vetor[i].key > max) max = vetor[i].key;
		if (vetor[i].key < min) min = vetor[i].key;
		vetorAux[i] = vetor[i];
	}
	printf("Minimo %i. Maximo %i\n\n", min, max);

	//2.2) Criação de um vetor adicional de contagem [0 - 5] -> 6 posições [5-0+1]
	int* vetorContagem = (int*) calloc(max-min+1, sizeof(int));
	
	//2.3) Percorrer o vetor de contagem com o somatório por chave
	// [2, 5, 7] -> [1 0 0 1 0 1] 
	for(i = 0; i<tamanho; i++){
		int posicaoKey = vetor[i].key - min; //ajuste (- min)
		vetorContagem[posicaoKey]++;
	}
	
	//3) contagem acumulada das chaves [1 0 0 1 0 1] -> [0 1 1 1 2 2]
	int total = 0;
	for(i = 0; i<=(max-min); i++){
		int contagemAnterior = vetorContagem[i];
		vetorContagem[i] = total;
		total = total + contagemAnterior;
	}
	
	//4) percorrer o vetor de contagem e produzir posicionamento correto
	for(i = 0; i<tamanho; i++){
		int posicaoOrdenada = vetorContagem[vetorAux[i].key - min];
		vetor[posicaoOrdenada] = vetorAux[i];
		vetorContagem[vetorAux[i].key - min]++;
	}
	
	free(vetorContagem);
	free(vetorAux);
}

/*
	Complexidade:
		1) Cópia completa dos dados originais: 0
		2.1) Percorrer as chaves e verificar o mínimo e máximo:	n
		2.2) Criação de um vetor adicional de contagem:	0
		2.3) Percorrer o vetor de contagem com o somatório por chave: n
		3) Contagem acumulada de frequências (chaves discretas): k
		4) Posicionamento de chaves (forma ordenada): n
	Então: 
		f(n) = 3n + k, ou seja, O(n+k)
	Se o k é pequeno, o maior fator contribuinte é n; o inverso também é verdadeiro
		- n = 1000 e k variando de 1 a 100 (k=100) então, temos 3*1000 + 100 = 3100 operações
		- n = 1000 e k variando de 1 a 10000 (k = 10000), temos 3*1000 + 10000 = 13000 operações
		- n = 1000 e k variando de 1 a 1000 (k=1000), temos 3*1000 + 1000 = 4000 operações
		- n = 2 e k = 1MI [1 ..... 1]
	Conclusões:
		- Consequentemente, a amplitude das chaves é determinante para a complexidade!!
		- Idealmente queremos k <= n. Se isso for verdadeiro, temos O(n)
		- Se k > n, a tendência é chegarmos a O(n^2) e ir piorando a complexidade
*/

/*
	Exercícios:
	1) Com a implementação disponibilizada, verifique qual tipo de arranjo inicial oferece o 
		melhor e o pior cenário (aleatório, ordenado, não ordenado ou parcialmente ordenado). 
		Sua análise pode ser generalizada para qualquer tamanho de entrada?
	2) Implementar uma rotina com repetição de chaves e executar o mesmo experimento 1.
	3) Crie um arquivo texto que contenha 10 registros de clientes contendo (nome, email, salario).
	   Cada cliente será associado a um código gerado aleatoriamente entre 0 e 100.
	   Então, para cada cliente lido, liste-o diretamente à primeira posição do vetor disponível.
	   Após todo o processo de inserção, ordene o vetor utilizando CountingSort.
	   
	Referências:
		- Cormen, capítulo 8.
*/