/*
Criado por Andressa Colaço (Nº USP: 12610389)
para a disciplina Introdução à Ciência de Computação II [2022/2].
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h"
#include "catalogo.h"

void read_and_catalog(FILE *file, Catalogo *catalogo); 
int get_property_id_by_string(char *property_name);

int main(){
	FILE *file;
	char filename[50];
	scanf("%s", filename);

	file = fopen(filename, "r");
	if (file == NULL){
		perror("fopen failed");
		exit(1);
	}

	Catalogo *catalogo = create_catalogo(500); // Tamanho inicial = 500 itens, porém está implementado o redimensionamento 
	read_and_catalog(file, catalogo);

	int qtd_buscas;
	scanf("%d", &qtd_buscas);

	for (int i = 0; i < qtd_buscas; i++){
		char property_string[50];
		double prop_value;

		scanf("%s %lf", property_string, &prop_value);
		int property = get_property_id_by_string(property_string);
		search_by_property(catalogo, property, prop_value);
	}

	fclose(file);
	delete_catalogo(&catalogo); // Desaloca espaços de memória criados para armazenar os dados
	return 0;
}

//Recebe o arquivo e lê os dados, armazenando-os no catálogo
void read_and_catalog(FILE *file, Catalogo *catalogo){
	char linha[100], *token;
	int i = 0;
	int id;
	double citric_acid, res_sugar, density, ph, alcohol;

	fgets(linha, 100, file); // Recebe o cabeçalho do arquivo, que não entra no loop de armazenamento

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

		register_item(catalogo, id, citric_acid, res_sugar, density, ph, alcohol);
		i++;
	}
	resize_catalogo(catalogo, get_size(catalogo)); //Já que o catalogo não será mais modificado, espaços
												   //não utilizados são desalocados.
}

//As propriedades recebem um id próprio que será usado 
//em outras funções
int get_property_id_by_string(char *property_name){
	if (strcmp(property_name, "citric_acid") == 0) return 1; 
	if (strcmp(property_name, "residual_sugar") == 0) return 2;
	if (strcmp(property_name, "density") == 0) return 3;
	if (strcmp(property_name, "pH") == 0) return 4;
	if (strcmp(property_name, "alcohol") == 0) return 5;
	return -1;
}
