#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Hashtable.h"

static Item *item_create(Student *student);
static void ht_delete_item(Item **item_ref);

struct item_st {
	Student *student;
	Item *next;
};

struct hashtable_st {
	Item **table;
	int size;
	int capacity;
};

/*
	As funções relacionadas à struct item são auxiliares para a 
	manipulação da tabela, definida como um vetor de itens.
*/
static Item *item_create(Student *student){
	Item *new_item = (Item*) calloc(1, sizeof(Item));

	new_item->student = student;
	new_item->next = NULL;

	return new_item;
}

/*
	A função ht_create cria uma tabela baseada em um tamanho inicial
	fornecido.
*/
Hashtable *ht_create(int size_ht){
	Hashtable *new_hashtable = (Hashtable*) calloc(1, sizeof(Hashtable));
	new_hashtable->table = (Item**) calloc(size_ht, sizeof(Item*));

	for (int i = 0; i < size_ht; i++){
		new_hashtable->table[i] = NULL;
	}

	new_hashtable->capacity = size_ht;
	new_hashtable->size = 0;

	return new_hashtable;
}

/*
	A função ht_insert_item recebe as informações para o cadastro de um
	aluno na tabela. Optou

*/
boolean ht_insert_item(Hashtable *hashtable, Student *student){

	int m = hashtable->capacity;

	unsigned int key = hash_function(get_nusp(student));
	int index = key % m;

	Item *item = item_create(student);

	if (hashtable->table[index] == NULL){

		hashtable->table[index] = item;

	} else {

		Item *p = hashtable->table[index];
		Item *q = p->next;

		while(q != NULL){
			if (student_compare_nusp(student, p->student)){
		 		ht_delete_item(&item);
		 		return FALSE;
		 	}
			
			p = q;
			q = p->next;
		}

		if (student_compare_nusp(student, p->student)){
			ht_delete_item(&item);
			return FALSE;
		}

		p->next = item;
	}

	hashtable->size++;
	return TRUE;
}

/*
	Função auxiliar utilizada para verificar a correta inserção
	dos dados durante a criação do projeto.
*/
void ht_print(Hashtable *hashtable){
	Item *p;
	for (int i = 0; i < hashtable->capacity; i++){
		p = hashtable->table[i];

		if (p != NULL){
			while(p->next != NULL){
				student_print(p->student);
				p = p->next;
			}
			student_print(p->student);
		}
	}
}

/*
	A função de busca utiliza a função hash para inferir
	a posição do item na tabela. Caso não seja o primeiro,
	procura até o fim da lista ligada pelo elemento através do
	número usp.
*/
Student *ht_search_item(Hashtable *hashtable, char *nusp){
	unsigned int key = hash_function(nusp);
	int index = key % hashtable->capacity;

	Item *p = hashtable->table[index];
	while(p != NULL){
		if (strcmp(nusp, get_nusp(p->student)) == 0) return p->student;
		p = p->next;
	}

	return NULL;
}

static void ht_delete_item(Item **item_ref){
	Item *item = *item_ref;

	student_delete(&item->student);
	item->next = NULL;
	free(item);
	*item_ref = NULL;
}

void ht_delete_table(Hashtable **ht_ref){
	Hashtable *ht = *ht_ref;

	for (int i = 0; i < ht->capacity; i++){
		if (ht->table[i] != NULL){
			Item *p = ht->table[i];
			Item *q = p->next;

			while(q != NULL){
				ht_delete_item(&p);
				p = q;
				q = q->next;
			}

			ht_delete_item(&p);
		}
	}

	ht->capacity = 0;
	ht->size = 0;
	free(ht->table);
	free(ht);
	*ht_ref = NULL;
}