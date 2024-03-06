#ifndef ITEM_H
#define ITEM_H

typedef struct _item Item;

Item *create_item(int id, double citric_acid, double res_sugar, double density, double ph, double alcohol);

void print_item(Item *item);

double get_property_value(Item *item, int pos);
int get_item_id(Item *item);

void delete_item(Item **item_ref);

#endif //ITEM_H

