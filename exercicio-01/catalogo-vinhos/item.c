#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

struct _item{
	int id;
	double citric_acid;
	double res_sugar;
	double density;
	double ph;
	double alcohol;
};

Item *create_item(int id, double citric_acid, double res_sugar, double density, double ph, double alcohol){
	Item *item = (Item*) calloc(1, sizeof(Item));
	item->id = id;
	item->citric_acid = citric_acid;
	item->res_sugar = res_sugar;
	item->density = density;
	item->ph = ph;
	item->alcohol = alcohol;
	return item;
}

void print_item(Item *item){
	printf("ID: %d, Citric Acid: %.5f, Residual Sugar %.5f, Density %.5f, pH %.5f, Alcohol %.5f\n",
			   item->id, 
			   item->citric_acid, 
			   item->res_sugar, 
			   item->density, 
			   item->ph, 
			   item-> alcohol);
}

int get_item_id(Item *item){
	return item->id;
}

double get_property_value(Item *item, int pos){
	if (pos == 1) return item->citric_acid;
	if (pos == 2) return item->res_sugar;
	if (pos == 3) return item->density;
	if (pos == 4) return item->ph;
	if (pos == 5) return item->alcohol;
	return -1;
}

void delete_item(Item **item_ref){
	Item *item = *item_ref;
	free(item);
	*item_ref = NULL;
}