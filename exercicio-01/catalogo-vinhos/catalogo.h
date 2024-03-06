#ifndef CATALOGO_H
#define CATALOGO_H
#include "item.h"

typedef struct _catalogo Catalogo;

Catalogo *create_catalogo(int initial_capacity);
Catalogo *resize_catalogo(Catalogo *catalogo, int new_capacity);

int get_size(Catalogo *catalogo);

void register_item(Catalogo *catalogo, int id, double citric_acid, double res_sugar, double density, double ph, double alcohol);

Item *get_item(Catalogo *catalogo, int pos);

Catalogo *catalogo_sort(Catalogo *catalogo, int size, int property);
void search_by_property(Catalogo *catalogo, int property, double key);

void delete_catalogo(Catalogo **catalogo_ref);

#endif //CATALOGO_H