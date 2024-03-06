#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aluno.h"

static void update_average(Aluno *aluno);
static void aluno_register_grades(Aluno *aluno, int *grades, int n_avaliacoes);

struct aluno_st {
	char name[50];

	int n_avaliacoes;
	int *grades;
	float av_grade;

	int desempate;
};

/*
A função aluno_create() retorna um aluno válido com valor inválido de
desempate, que pode ser atualizado caso o aluno empate em média com
outro aluno.
*/
Aluno *aluno_create(char *name, int *grades, int n_avaliacoes){
	Aluno *new_aluno = (Aluno*) calloc(1, sizeof(Aluno));
	strcpy(new_aluno->name, name);

	new_aluno->n_avaliacoes = n_avaliacoes;
	aluno_register_grades(new_aluno, grades, n_avaliacoes);

	new_aluno->desempate = -1;
	return new_aluno;
}

/*
A função aluno_create_invalid() automatiza o processo de criar um elemento 
inválido para a árvore do torneio. Como comparamos médias, pode-se utilizar apenas
uma nota inválida (-1), menor que todas as notas válidas, ou seja, perderá
todos os torneios contra um aluno válido.
*/
Aluno *aluno_create_invalid(){
	int *filler_grade = (int*) calloc(1, sizeof(int));
	filler_grade[0] = -1;

	Aluno *invalid_aluno = aluno_create("NULL", filler_grade, 1);

	free(filler_grade);
	return invalid_aluno;
}

/*
As funções update_average() e aluno_register_grades() são auxiliares da
aluno_create(), com o objetivo de deixá-la mais organizada.
*/
static void update_average(Aluno *aluno){
	float sum = 0;

	for (int i = 0; i < aluno->n_avaliacoes; i++){
		sum = sum + aluno->grades[i];
	}

	aluno->av_grade = sum/aluno->n_avaliacoes;
}

static void aluno_register_grades(Aluno *aluno, int *grades, int n_avaliacoes){
	aluno->grades = (int*) calloc(n_avaliacoes, sizeof(int));

	for (int i = 0; i < n_avaliacoes; i++){
		aluno->grades[i] = grades[i];
	}
	
	update_average(aluno);
}

/*
A função ganhador() atua como uma função que encontra o maior de dois valores,
mas adaptada para os critérios da tarefa. Se uma média é maior que a outra, a função
retorna o ponteiro para o aluno com a maior média. Caso contrário, encontra-se
a primeira nota diferente e retorna-se o aluno que a tirou. Em caso de todas as notas 
serem iguais, optou-se por apenas retornar o primeiro aluno. A nota de desempate é 
salva na struct do aluno que perdeu o torneio. Isso ocorre para que, em casos com múltiplos
alunos com notas iguais, possamos recuperar os desempates em sequẽncia de saída do aluno. 
*/
Aluno *ganhador(Aluno *aluno1, Aluno *aluno2){ 

	if(aluno_av(aluno1)>aluno_av(aluno2)) return aluno1;
	if(aluno_av(aluno1)<aluno_av(aluno2)) return aluno2;

	int i = 0;
	while(aluno1->grades[i] == aluno2->grades[i] && i < aluno1->n_avaliacoes-1){
		i++;
	}

	if (aluno1->grades[i] < aluno2->grades[i]){
		aluno1->desempate = i+1;
		return aluno2;
	} 
	
	aluno2->desempate = i+1;
	return aluno1;
}

float aluno_av(Aluno *aluno){
	return aluno->av_grade;
}

char *aluno_name(Aluno *aluno){
	return aluno->name;
}

int aluno_desempate(Aluno *aluno){
	return aluno->desempate;
}

/*
A função aluno_print() não é utilizada no código principal, mas foi 
implementada para auxiliar na escrita do código e visualização das
estruturas criadas.
*/
void aluno_print(Aluno *aluno){ 
	printf("--------------\n");
	printf("Aluno: %s \n", aluno->name);

	printf("Notas: ");
	for (int i=0; i<aluno->n_avaliacoes;i++){
		printf("%d ", aluno->grades[i]);
	}
	printf("\b\n");

	printf("Média: %.3f\n", aluno->av_grade);

	if (aluno->desempate > 0){
		printf("Desempate: %d\n", aluno->desempate);
	}
}

void aluno_delete(Aluno **aluno_ref){
	Aluno *aluno = *aluno_ref;

	free(aluno->grades);
	free(aluno);
	*aluno_ref = NULL;
}