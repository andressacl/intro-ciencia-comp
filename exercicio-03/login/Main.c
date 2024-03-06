/*
Criado por Andressa Colaço (Nº USP: 12610389)
para a disciplina Introdução à Ciência de Computação II [2022/2].
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Student/Student.h"
#include "Util/Util.h"
#include "Hashtable/Hashtable.h"

/*Foi definido um tamanho a ser utilizado em todos os casos
  previamente, escolhendo-se um número primo para minimizar
  o número de possíveis colisões na tabela.*/
#define TABLE_SIZE 67
 
int main(){

	int n_alunos;
	scanf("%d\n", &n_alunos);

	char *nusp = (char*) calloc(20, sizeof(char));
	char *senha = (char*) calloc(30, sizeof(char));
	double *notas = (double*) calloc(4, sizeof(double));

	Hashtable *alunos_ht = ht_create(TABLE_SIZE);
	Student *student;

	for (int i = 0; i < n_alunos; i++){

		scanf("%s %s %lf %lf %lf %lf", nusp, senha,
			&notas[0], &notas[1], &notas[2], &notas[3]);

		student = student_create(nusp, senha, notas);

		if (student != NULL) {

			/* A função ht_insert_item retorna um boolean. Em
		  	   caso de inserção não realizada, imprimimos uma 
		   	   mensagem de erro na tela.*/
			if (ht_insert_item(alunos_ht, student)){
				printf("Cadastro efetuado com sucesso\n");
			} else {
				printf("NUSP ja cadastrado\n");
			}
			student = NULL;  
		}
	}
	
	int n_op;
	scanf("%d", &n_op);

	for (int i = 0; i < n_op; i++){
		scanf("%s %s", nusp, senha);

		Student *student_p = ht_search_item(alunos_ht, nusp);

		/* A função ht_search_item retorna um ponteiro para um estudante.
		   Caso ele não seja encontrado, é impressa uma mensagem de erro.
		   Em caso de sucesso, usamos uma função de validação que indica
		   se a senha passada é correta.*/
		if (student_p == NULL){

			printf("NUSP invalido\n");

		} else {

			if (student_validate_password(student_p, senha)){
				student_print(student_p);
			} else {
				printf("Senha incorreta para o NUSP digitado\n");
			}

		}
	}

	free(nusp);
	free(senha);
	free(notas);

	ht_delete_table(&alunos_ht);

	return 0;
}