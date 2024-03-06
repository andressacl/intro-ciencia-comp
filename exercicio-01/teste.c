#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _item{
	int id;
	double citric_acid;
	double res_sugar;
	double density;
	double ph;
	double alcohol;
} Item;

Item *criar_item(int id, double citric_acid, double res_sugar, double density, double ph, double alcohol){
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
	printf("ID: %i\n", item->id);
	printf("Citric acid: %f\n", item->citric_acid);
	printf("Residual sugar: %f\n", item->res_sugar);
	printf("Density: %f\n", item->density);
	printf("pH: %f\n", item->ph);
	printf("Alcohol: %f\n", item->alcohol);
}

typedef struct _catalogo{
	Item **data;
	int size;
} Catalogo;

Catalogo *create_catalogo(int capacity){
	Catalogo *catalogo = (Catalogo*) calloc(1, sizeof(Catalogo));

	catalogo->data = (Item**) calloc(capacity, sizeof(Item*));
	catalogo->size = 0;

	return catalogo;
};



int main(){
	FILE *file;
	char filename[50], linha[100], *token;
	scanf("%s", filename);

	file = fopen(filename, "r");
	if (file == NULL){
		perror("fopen failed");
		exit(1);
	}

	Catalogo *catalogo = create_catalogo(3);
	int i = 0;
	int id;
	double citric_acid, res_sugar, density, ph, alcohol;

	fgets(linha, 100, file); // Recebe o cabeçalho do arquivo, mas não entra no loop de armazenamento

	while (feof(file) != true){
		fgets(linha, 100, file);

		token = strtok(linha, ",");
		id = atoi(token);

		token = strtok(NULL, ",");
		citric_acid = atof(token);

		token = strtok(NULL, ",");
		res_sugar = atof(token);

		token = strtok(NULL, ",");
		density = atof(token);

		token = strtok(NULL, ",");
		ph = atof(token);

		token = strtok(NULL, ",");
		alcohol = atof(token);

		catalogo->data[i] = criar_item(id, citric_acid, res_sugar, density, ph, alcohol);
		catalogo->size++;
		print_item(catalogo->data[i]);
		i++;
	}

	fclose(file);
	return 0;
}