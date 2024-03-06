#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lista.h"

static void lista_print_resultado_torneio(Lista *lista);

struct lista_st {
	Aluno **alunos;
	int n_elementos;
	int capacity;
};

Lista *lista_create(int capacity){
	Lista *new_lista = (Lista*) calloc(1, sizeof(Lista));

	new_lista->alunos = (Aluno**) calloc(capacity, sizeof(Aluno*));
	new_lista->n_elementos = 0;
	new_lista->capacity = capacity;

	return new_lista;
}

/*A função para registrar elementos não checa se a capacidade
da lista foi atingida por conta da forma com a qual o código da
Main está escrito: nunca se ultrapassa a capacidade da lista.*/
void lista_register_element(Lista *lista, Aluno *aluno){
	lista->alunos[lista->n_elementos] = aluno;
	lista->n_elementos++;
}

static void set_leaves(Aluno **tree, Lista *lista){
	int k = lista->n_elementos;
	Aluno *aluno_invalido_p = aluno_create_invalid();

	for (int i = k; i < 2*k; i++){
		tree[i] = lista->alunos[i-k];
		tree[i-k] = aluno_invalido_p;
	}
}

// static organize_tree(Aluno **tree, int pai, int last_indice){
// 	int l_child = 2*pai;
// 	int r_child = 2*pai+1;
// 	int ganhador;

// 	if (l_child <= last_indice && ganhador(tree[l_child], tree[pai]) == tree[l_child]){
// 		ganhador = l_child;
// 	} else {
// 		ganhador = pai;
// 	}

// 	if (r_child <= last_indice && 
// 		ganhador(tree[r_child], tree[ganhador]) == tree[r_child]){
// 		ganhador = r_child;
// 	}

// 	if (ganhador != pai){
// 		Aluno *aux = tree[pai];
// 		tree[pai] = tree[ganhador];
// 		tree[ganhador] = aux;
// 		organize_tree(tree, ganhador);
// 	}
// }

static void organize_tree(Aluno **tree, int last_element, int i){
	int pai = (int) i/2;
	int l_child = 2*pai;
	int r_child = 2*pai+1;
	int ganhador_p;

	if (pai < 1) return;

	if (ganhador(tree[l_child], tree[r_child]) == tree[l_child]){
		ganhador_p = l_child;
	} else {
		ganhador_p = r_child;
	}

	tree[pai] = tree[ganhador_p];
	
	organize_tree(tree, last_element, pai);
}

static void build_tree(Aluno **tree, int last_element){
	//int last_parent = last_element/2;
	for (int i = last_element; i > 0; i --){
		organize_tree(tree, last_element, i);
	}
}

// static Aluno *build_tree(Aluno **tree, int last_indice, int pai){
// 	int left = 2*pai;
// 	int right = 2*pai + 1;

// 	if (left > last_indice && right > last_indice) return tree[pai];

// 	tree[pai] = ganhador(build_tree(tree, last_indice, left), 
// 		                 build_tree(tree, last_indice, right));

// 	return tree[pai];
// }

// static Aluno *build_tree_rec(Aluno **tree, int last_indice){
// 	for (int i = (int) last_indice/2; i >= 1; i--){
// 		organize_tree(tree, i);
// 	}
// }

Lista *torneioGeralSort(Lista *lista){
	int k = lista->n_elementos;
	
	int tree_tam = 2*k;
	Aluno **tree = (Aluno**) calloc(tree_tam, sizeof(Aluno*));

	int tam_lista_ord = 0;
	int raiz = 1;

	set_leaves(tree, lista);
	//build_tree(tree, tree_tam-1, raiz);
	build_tree(tree, tree_tam-1);

	lista->alunos[tam_lista_ord] = tree[raiz];
	tam_lista_ord++;

	while(tam_lista_ord < k){
		int first_leaf = k;
		int i = 1;

		while(i < first_leaf){
			if (tree[i] == tree[2*i]){
				i = 2*i;
			} else {
				i = 2*i+1;
			}
		}

		tree[i] = tree[0]; //aponta para o elemento inválido

		// while (i>1){
		// 	int pai = (int) i/2;
		// 	int f_child = 2*pai;
		// 	int s_child = 2*pai+1;

		// 	if (ganhador(tree[f_child], tree[s_child]) == tree[f_child]){ //tree[f_child] > tree[s_child]
		// 		tree[pai] = tree[f_child];
		// 	} else {
		// 		tree[pai] = tree[s_child];
		// 	}
		// 	i = pai;
		// }

		organize_tree(tree, tree_tam-1, i);

		lista->alunos[tam_lista_ord] = tree[raiz];
		tam_lista_ord++;
	}

	aluno_delete(&tree[0]);
	free(tree);

	lista_print_resultado_torneio(lista);
	return lista;
}

// Lista *torneioSort(Lista *lista){
// 	int k = lista->n_elementos;

// 	int tree_tam = 2*k;
// 	Aluno **tree = (Aluno**) calloc(tree_tam, sizeof(Aluno*));

// 	int tam_lista_ord = 0;
// 	int raiz = 1;

// 	set_leaves(tree, lista);
// 	build_tree_rec(tree, tree_tam-1, raiz);

// 	lista->alunos[tam_lista_ord] = tree[raiz];
// 	tam_lista_ord++;

// 	while (tam_lista_ord < k){
// 		int first_leaf = k;
// 		int i = 1;

// 		while(i < first_leaf){
// 			if (tree[i] == tree[2*i]){
// 				i = 2*i;
// 			} else {
// 				i = 2*i+1;
// 			}
// 		}
// 		tree[i] = tree[0];

// 		organize_tree(tree, raiz);
// 	}

// }

void lista_print(Lista *lista){
	for (int i = 0; i < lista->n_elementos; i++){
		aluno_print(lista->alunos[i]);
	}
} 

static void lista_print_resultado_torneio(Lista *lista){

	printf("Maior media: %.3f\n", aluno_av(lista->alunos[0]));

	int i = 0;

	while (i < lista->n_elementos-1){
		if (aluno_desempate(lista->alunos[i]) > 0){
			printf("%d. %s - desempate: nota %d\n", 
					i+1, 
					aluno_name(lista->alunos[i]), 
					aluno_desempate(lista->alunos[i]));
		} else {
			printf("%d. %s - media\n", i+1, aluno_name(lista->alunos[i]));
		}
		i++;
	}
	printf("%d. %s\n", i+1, aluno_name(lista->alunos[i]));
} 

void lista_delete(Lista **lista_ref){
	Lista *lista = *lista_ref;

	//printf("%d, %d\n", lista->n_elementos, lista->capacity);

	for (int i = 0; i < lista->n_elementos; i++){
		aluno_delete(&(lista->alunos[i]));
		//aluno_print(lista->alunos[i]);
	}

	// for (int i = lista->n_elementos; i < lista->capacity; i++){
	// 	free(lista->alunos[i]);
	// }
	
	lista->n_elementos = 0;
	free(lista->alunos);

	lista->capacity = 0;
	free(lista);
	*lista_ref = NULL;
}

// static void set_leaves(Aluno **tree, Lista *lista){
// 	int k = lista->tam;
// 	Aluno *aluno_invalido_p = aluno_create_invalid();

// 	for (int i = k; i < 2*k; i++){
// 		tree[i] = lista->alunos[i-k];
// 		tree[i-k] = aluno_invalido_p;
// 	}
// }

/*
Percorre no máximo a altura da árvore, log(n).
*/
// static void organize_tree(Aluno **tree, int i){ 
// 	int pai = (int) i/2;
// 	int l_child = 2*pai;
// 	int r_child = 2*pai+1;
// 	int ganhador_p;

// 	if (pai < 1) return;

// 	if (ganhador(tree[l_child], tree[r_child]) == tree[l_child]){
// 		ganhador_p = l_child;
// 	} else {
// 		ganhador_p = r_child;
// 	}

// 	tree[pai] = tree[ganhador_p];
	
// 	organize_tree(tree, pai);
// }

// static void build_tree(Aluno **tree, int last_element){ //Complexidade O(n)
// 	for (int i = last_element; i > 0; i --){
// 		organize_tree(tree, i);
// 	}
// }

// Lista *torneioGeralSort(Lista *lista){
// 	int k = lista->tam;
	
// 	int tree_tam = 2*k;
// 	Aluno **tree = (Aluno**) calloc(tree_tam, sizeof(Aluno*));

// 	int tam_lista_ord = 0;
// 	int raiz = 1;

// 	set_leaves(tree, lista);
// 	build_tree(tree, tree_tam-1);

// 	lista->alunos[tam_lista_ord] = tree[raiz];
// 	tam_lista_ord++;

// 	while(tam_lista_ord < k){
// 		int first_leaf = k;
// 		int i = 1;

// 		while(i < first_leaf){
// 			if (tree[i] == tree[2*i]){
// 				i = 2*i;
// 			} else {
// 				i = 2*i+1;
// 			}
// 		}

// 		tree[i] = tree[0]; //Aponta para o elemento inválido

// 		organize_tree(tree, i);

// 		lista->alunos[tam_lista_ord] = tree[raiz];
// 		tam_lista_ord++;
// 	}

// 	aluno_delete(&tree[0]);
// 	free(tree);

// 	lista_print_resultado_torneio(lista);
// 	return lista;
// }