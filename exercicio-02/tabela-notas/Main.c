/*
Criado por Andressa Colaço (Nº USP: 12610389)
para a disciplina Introdução à Ciência de Computação II [2022/2].
*/ 

#include <stdio.h>
#include <stdlib.h>

#include "Aluno/Aluno.h"
#include "Lista/Lista.h"
#include "Arvore/Arvore.h"

int main(){
	int n_alunos, n_avaliacoes;
	char aluno_name[50];

	scanf("%d %d", &n_alunos, &n_avaliacoes);

	Aluno *aluno_p;
	int *aluno_grades = (int*) calloc(n_avaliacoes, sizeof(int));
	Lista *lista_p = lista_create(n_alunos);

	for (int i = 0; i < n_alunos; i++){
		scanf("%s", aluno_name);

		for(int j = 0;j < n_avaliacoes; j++){
			scanf("%d", &aluno_grades[j]);
		} 

		aluno_p = aluno_create(aluno_name, aluno_grades, n_avaliacoes);
		lista_register_element(lista_p, aluno_p);
	}

	torneioGeralSort(lista_p);    

	free(aluno_grades);
	lista_delete(&lista_p);
	return 0;
}