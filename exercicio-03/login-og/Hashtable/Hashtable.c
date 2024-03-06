#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Hashtable.h"


struct item_st {
	unsigned int key;
	Student *student;
	Item *next;
};

struct hashtable_st {
	Item **table;
	int size;
	int capacity;
};

Item *item_create(unsigned int key, char *nusp, char *senha, double *notas){
	Item *new_item = (Item*) calloc(1, sizeof(Item));

	new_item->key = key;
	new_item->student = student_create(nusp, senha, notas);
	new_item->next = NULL;

	return new_item;
}

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

boolean ht_insert_item(Hashtable *hashtable, char *nusp, char *senha,
	double *notas){

	int m = hashtable->capacity;

	unsigned int key = hash_function(nusp);
	int index = key % m;
	// printf("index: %d", index);

	Item *item = item_create(key, nusp, senha, notas);

	if (hashtable->table[index] == NULL){
		hashtable->table[index] = item;
	} else {
		Item *p = hashtable->table[index];
		Item *q = p->next;

		while(q != NULL){
			// printf("p key: %d; item key: %d\n", p->key, item->key);
			if (strcmp(nusp, get_nusp(p->student)) == 0){
			 	ht_delete_item(&item);
			 	return FALSE;
			}
			p = q;
			q = p->next;
		}

		if (strcmp(nusp, get_nusp(p->student)) == 0){
			 	ht_delete_item(&item);
			 	return FALSE;
		}
		p->next = item;
		// printf("olha a colisão\n");
	}

	hashtable->size++;
	return TRUE;
}

unsigned int hash_function(char *nusp){
	unsigned int low = 0;
	unsigned int high = 1;
	int tam = strlen(nusp);

	for(int i = 0; i < tam; i++){
		low = (low+nusp[i]) % 65521;
		high = (low+high) % 65521;
	}

	return ((high << 16) | low);
}

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

Student *ht_access_item(Hashtable *hashtable, char *nusp, char *senha){
	unsigned int key = hash_function(nusp);
	int index = key % hashtable->capacity;

	Item *p = hashtable->table[index];
	while(p != NULL){
		if (key == p->key){
			return p->student;
		}
		p = p->next;
	}

	return NULL;
}

void ht_delete_item(Item **item_ref){
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