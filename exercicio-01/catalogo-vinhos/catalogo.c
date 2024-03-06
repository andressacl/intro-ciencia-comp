#include <stdio.h>
#include <stdlib.h>
#include "catalogo.h"

struct _catalogo{
	Item **data;
	int size;
	int capacity;
};

Catalogo *create_catalogo(int initial_capacity){
	Catalogo *catalogo = (Catalogo*) calloc(1, sizeof(Catalogo));

	catalogo->data = (Item**) calloc(initial_capacity, sizeof(Item*));
	catalogo->size = 0;
	catalogo->capacity = initial_capacity;

	return catalogo;
};

Catalogo *resize_catalogo(Catalogo *catalogo, int new_capacity){
	catalogo->data = (Item**) realloc(catalogo->data, sizeof(Item*)*new_capacity);
	catalogo->capacity = new_capacity;
	return catalogo;
};

int get_size(Catalogo *catalogo){
	return catalogo->size;
}

void register_item(Catalogo *catalogo, int id, double citric_acid, double res_sugar, double density, double ph, double alcohol){
	int size = catalogo->size;
	if (catalogo->capacity == catalogo->size){
		catalogo = resize_catalogo(catalogo, size+100); //Foi escolhido o tamanho incremental do tamanho do catálogo como 100 para reduzir o número de reallocs 
														// mas não alocar muitos espaços desnecessariamente 
	}
	catalogo->data[size] = create_item(id, citric_acid, res_sugar, density, ph, alcohol);
	catalogo->size++;
}

Item *get_item(Catalogo *catalogo, int pos){
	return catalogo->data[pos];
}

Catalogo *catalogo_sort(Catalogo *catalogo, int size, int property){
	if (size == 1) return catalogo;

	int last_indice = size-1;
	int maior_indice = 0;
	int maior_id = get_item_id(catalogo->data[maior_indice]);
	double maior_prop = get_property_value(catalogo->data[maior_indice], property);

	for (int i = 0; i < size; i++){
		double prop = get_property_value(catalogo->data[i], property);
		int id = get_item_id(catalogo->data[i]);
		if (prop > maior_prop || (prop == maior_prop &&  id > maior_id)){ 
			maior_prop = prop;
			maior_indice = i;
			maior_id = id;
		} 
	}
	
	Item *aux = catalogo->data[maior_indice]; 
	catalogo->data[maior_indice] = catalogo->data[last_indice];
	catalogo->data[last_indice] = aux;

	return catalogo_sort(catalogo, size-1, property);
}

/*search_items: função auxiliar que implementa a busca binária para a função de busca
principal, separadas por conta das ordenações dependentes da propriedade requerida*/
static int search_items(Catalogo *catalogo, int posInicial, int posFinal, int property, double key){
	int centro = (int)(posFinal+posInicial)/2;
	double prop_centro = get_property_value(catalogo->data[centro], property);

	if (posFinal < posInicial) return -1;
	if (prop_centro == key) return centro;
	if (key < prop_centro) return search_items(catalogo, posInicial, centro-1, property, key);
	return search_items(catalogo, centro+1, posFinal, property, key);
}

void search_by_property(Catalogo *catalogo, int property, double key){
	int size = catalogo->size;
	catalogo = catalogo_sort(catalogo, size, property);

	int position = search_items(catalogo, 0, size-1, property, key);
	
	if (position < 0){
		printf("Nenhum vinho encontrado\n");
		return;
	}

	int count = position-1;
	double prop_pos = get_property_value(catalogo->data[position], property);

	while (count >= 0){
		double prop_cmp = get_property_value(catalogo->data[count], property);
		if (prop_pos != prop_cmp){
			break;
		}
		position = count;
		count--;
	}

	print_item(catalogo->data[position]);

	count = position;
	int count_vinhos = 0;

	while(count < size){
		double prop_cmp = get_property_value(catalogo->data[count], property);
		if (prop_pos != prop_cmp){
			break;
		}
		count_vinhos++;
		count++;
	}

	printf("Total de vinhos encontrados: %d\n", count_vinhos);
	return;
}


void delete_catalogo(Catalogo **catalogo_ref){
	Catalogo *catalogo = *catalogo_ref;
	for (int i = 0; i < catalogo->size; i++){
		delete_item(&(catalogo->data[i]));
	}

	for (int i = catalogo->size; i < catalogo->capacity; i++){
		free(catalogo->data[i]);
	}
	
	catalogo->size = 0;
	free(catalogo->data);
	catalogo->capacity =0;
	free(catalogo);
	*catalogo_ref = NULL;
}
