#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)<(b) ? (a) : (b))

int *tournamentSort(int *vetor, int k);
void set_leaves(int *tree, int *vetor, int k);
int build_tree(int *tree, int last_indice, int pai);

void print(int *vetor, int tam);

int main(){

	int tam, geracaoVetor;
	scanf("%d %d", &tam, &geracaoVetor);

	int *vetor = (int*) malloc(tam*sizeof(int));
	//int *vetor_ord = (int*) malloc(n*sizeof(int));

	for (int i=0; i<tam; i++){
		if (geracaoVetor == 0) //aleatório
			vetor[i] = rand() % 1000;
		else if (geracaoVetor == 1) //ordenado
			vetor[i] = i;
		else if (geracaoVetor == 2) //invertido
			vetor[i] = tam - i;
		else if (geracaoVetor == 3 && i<=tam/2) //primeira metade ordenada e o restante aleatório
			vetor[i] = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleatório
			vetor[i] = (rand() % 1000) + i;
	}

	print(vetor, tam);

	tournamentSort(vetor, tam);
	printf("\nordenado vadia\n");
	print(vetor, tam);

	free(vetor);
}

int *tournamentSort(int *vetor, int k){
	
	int tree_tam = 2*k;
	int *tree = malloc(tree_tam*sizeof(int));

	int tam_vetor_ord = 0;
	int raiz = 1;

	set_leaves(tree, vetor, k);
	build_tree(tree, tree_tam-1, raiz);

	vetor[tam_vetor_ord] = tree[1];
	tam_vetor_ord++;

	while(tam_vetor_ord <= k){
		int first_leaf = k;
		int i = 1;

		while(i < first_leaf){
			if (tree[i] == tree[2*i]) i = 2*i;
			if (tree[i] == tree[2*i+1]) i = (2*i)+1;
		}

		tree[i] = -1;

		while (i>1){
			int pai = (int) i/2;
			int f_child = 2*pai;
			int s_child = 2*pai+1;

			if (tree[f_child] > tree[s_child]){
				tree[pai] = tree[f_child];
			} else {
				tree[pai] = tree[s_child];
			}
			i = pai;
		}

		vetor[tam_vetor_ord] = tree[1];
		tam_vetor_ord++;
	}

	free(tree);
	return vetor;
}

void set_leaves(int *tree, int *vetor, int k){
	for (int i=k; i<2*k; i++){
		tree[i] = vetor[i-k];
		tree[i-k] = -1;
	}
}

int build_tree(int *tree, int last_indice, int pai){
	int left = 2*pai;
	int right = 2*pai + 1;

	if (left >= last_indice && right > last_indice) return tree[pai]; 
	tree[pai] = MAX(build_tree(tree, last_indice, left), build_tree(tree, last_indice, right));
	return tree[pai];
}

void print(int *vetor, int tam){
	printf("(");
	for (int j = 0; j < tam; j++){
		printf("%d, ", vetor[j]);
	}
	printf("\b\b)\n");
}