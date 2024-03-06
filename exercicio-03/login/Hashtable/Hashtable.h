#ifndef HASHTABLE_H 
#define HASHTABLE_H

#include "../Student/Student.h"
#include "../Util/Util.h"

typedef struct item_st Item;
typedef struct hashtable_st Hashtable;

Hashtable *ht_create(int size_ht);

boolean ht_insert_item(Hashtable *hashtable, Student *student);
Student *ht_search_item(Hashtable *hashtable, char *nusp);

void ht_print(Hashtable *hashtable);

void ht_delete_table(Hashtable **ht_ref);

#endif