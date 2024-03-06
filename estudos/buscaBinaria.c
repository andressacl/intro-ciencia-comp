#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*		
	- Busca Binária:
		- Mais eficiente que a Busca Sequencial por reduzir o espaço de busca;
		- Divide o conjunto de entrada atual em duas metades sucessivamente, 
			comparando a chave com o elemento central ou realizando a busca novamente;
		- Requer que o conjunto de dados esteja ordenado.
		- Aplicável em estruturas como vetor, pois utiliza os índices durante a busca 
			por serem inteiros positivos.
*/

int* fernandoSort(int* vetor, int tamanho){
	int j;
	for(j = 1; j < tamanho; j++){
		int chave = vetor[j];
		int i = j - 1;
		while (i >= 0 && vetor[i] > chave){
			vetor[i+1] = vetor[i];
			i--;
		}
		vetor[i+1] = chave;
		
		int k;
		for (k=0; k<tamanho; k++) printf("%i ", vetor[k]);
		printf("- analise posicao %i\n", j);
	}
	printf("Vetor Ordenado!!\n\n");
	return vetor;
}

int buscaBinaria_recursiva(int* vetor, int posicaoInicial, int posicaoFinal, int chave);
int buscaBinaria_iterativa(int* vetor, int posicaoInicial, int posicaoFinal, int chave);

int main(void){
	//geração dos elementos
	int tamanhoVetor = 10;
	int *vetor = malloc(tamanhoVetor * sizeof(int));
	srand(time(NULL));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		vetor[i] = rand() % 1000;
		printf("%i ", vetor[i]);
	}
	vetor = fernandoSort(vetor, tamanhoVetor);
	
	//leitura do elemento de busca
	int chave;
	printf("\nDigite a chave a ser buscada no vetor: ");
	scanf("%d", &chave);

	//busca do elemento desejado
	//int posicao = buscaBinaria_recursiva(vetor, 0, tamanhoVetor-1, chave);
	int posicao = buscaBinaria_iterativa(vetor, 0, tamanhoVetor-1, chave);
	
	//resultado
	printf("A chave %i esta na posicao %i\n", chave, posicao);
	free(vetor);
	
	return 0;	
}

/*
	Descrição: 
		- busca binária realiza a divisão do vetor em partes (metades) baseando-se 
			no cálculo do elemento central
		- especifica um espaço de busca, ou seja, regiões reduzidas como entrada da função
	Parâmetros:
		- int* vetor: vetor de entrada
		- int posicaoInicial: posição do primeiro elemento do vetor
		- int posicaoFinal: posicação do último elemento do vetor
		- int chave: elemento a ser buscado		
	Retorno:
		- int (posicao): posição do elemento buscado
	Requisitos:
		- o vetor deve estar ordenado
*/

int buscaBinaria_recursiva(int* vetor, int posicaoInicial, int posicaoFinal, int chave){
	if (posicaoInicial > posicaoFinal) //valor não encontrado
		return -1;

	int centro = (int)((posicaoInicial+posicaoFinal)/2);
	printf("valor inicial %i; valor final %i; valor central %i; inicio %i; final %i; centro %i\n", 
		vetor[posicaoInicial], vetor[posicaoFinal], vetor[centro], posicaoInicial, posicaoFinal, centro);
	
	if (chave == vetor[centro]) //valor encontrado
		return centro; 
	 
	if (chave < vetor[centro]) //se existir, primeira metade
		return buscaBinaria_recursiva(vetor, posicaoInicial, centro-1, chave);
	
	return buscaBinaria_recursiva(vetor, centro+1, posicaoFinal, chave); 

	/*
		Quantas comparações (operação mais importante na busca)? 4 comparações
			f(n) = 4 + f(n/2^1)					//4.1 + f(n/2^1)
				 = 4 + [4 + f(n/2^2)]			//4.2 + f(n/2^2)
			     = 4 + [4 + [4 + f(n/2^3)]]]	//4.3 + f(n/2^3)
			....
			     = 4.k + f(n/2^k)

		Matematicamente, nós temos que n/2^k = 1 --> n = 2^k --> k = log2(n)
			f(n) = 4.log2(n) + 1
	*/	
}

/*
	Descrição: busca binária realiza a divisão do vetor em partes (metades) baseando-se 
		no cálculo do elemento central
		- requisito: o vetor precisa estar ordenado
		- especifica um espaço de busca, ou seja, regiões reduzidas como entrada da função
	Parâmetros:
		- int* vetor: vetor de entrada
		- int posicaoInicial: posição do primeiro elemento do vetor
		- int posicaoFinal: posicação do último elemento do vetor
		- int chave: elemento a ser buscado
	Retorno:
		- int (posicao): posição do elemento buscado
*/
int buscaBinaria_iterativa(int* vetor, int posicaoInicial, int posicaoFinal, int chave){
	while(posicaoInicial <= posicaoFinal){ //log n
		int centro = (int)((posicaoInicial+posicaoFinal)/2);
		printf("valor inicial %i; valor final %i; valor central %i; inicio %i; final %i; centro %i\n", 
			vetor[posicaoInicial], vetor[posicaoFinal], vetor[centro], posicaoInicial, posicaoFinal, centro);
	
		if (chave == vetor[centro]) 
			return centro; //valor encontrado 
		if (chave < vetor[centro]) //se o número existir estará na primeira metade
			posicaoFinal = centro - 1;
		if (chave > vetor[centro]) //se o número existir estará na segunda metade
			posicaoInicial = centro + 1;
	}
	return -1;//valor não encontrado
}

/*
	- Considerando: 
		Busca Sequencial (Bs)
		Busca Binaria (Bb)
	- Então: Bs(n) < Bb(log n) + T(?)

	O diferencial é a quantidade de vezes que eu faço a busca!!! (k)
		Bs(n).k > Bb(log n).k + T(?) 
	--> quando k é "pequeno" é mais vantajoso usar Busca Sequencial
	--> quando k é "grande" é mais vantajoso usar Busca Binária

	Observação:
	- Precisamos estudar o cenário por completo!!!
	- Quando olhamos os métodos separadamente, sabemos que Busca Binária é menos complexa
	- Quando incluimos a ordenação, a Busca Sequencial passa a ser menos complexa
	- Quando vamos executar este cenário k vezes, depende do valor de k

	Exemplo:
		f(n) = n + 3
		g(n) = n + 4
		Qual é melhor? f(n)
			-> n = 1 -> f(1) = 4; g(1) = 5 --- 20%
			-> n = 100000 -> f(100000) = 100003; g(100000) = 100004 -- 0.000..%
*/


/*
	Exercícios:
	OK  1) Melhore o código disponibilizado da Busca Binária Recursiva. 
		Defina a nova função de recorrência.
	2) Encontre o melhor e pior caso para a Busca Binária, assim como o caso médio.
	3) Execute as implementações da Busca Sequencial e Binária para diferentes tamanhos de entrada. 
		Crie um gráfico que mostre o tempo de execução.
	4) Considerando a mesma ideia do exercício 3, crie um gráfico em termos da função 
		de recorrência.
	5) Implemente uma função de busca que possua chaves no formato de caracteres.
		
	Referências:
		- Tenembaum, capítulo 7.
		- Ascencio, capítulo 2.
*/