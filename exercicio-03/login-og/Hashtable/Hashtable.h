#ifndef HASHTABLE_H 
#define HASHTABLE_H

#include "../Student/Student.h"
#include "../Util/Util.h"

typedef struct item_st Item;
typedef struct hashtable_st Hashtable;

Hashtable *ht_create(int size_ht);

unsigned int hash_function(char *nusp);

boolean ht_insert_item(Hashtable *hashtable, char *nusp, char *senha,
	double *notas);
Student *ht_access_item(Hashtable *hashtable, char *nusp, char *senha);

void ht_print(Hashtable *hashtable);

void ht_delete_item(Item **item_ref);
void ht_delete_table(Hashtable **ht_ref);

#endif