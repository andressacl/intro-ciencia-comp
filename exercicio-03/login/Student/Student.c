#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Student.h"

struct student_st {
	char *nusp;
	unsigned int password;
	double *grades;
}; 

/*
	A função hash_function retorna um valor unsigned int que é utilizado
	para posicionar um elemento na tabela ou para encriptar a senha
	ao ser cadastrada, de forma com a qual esta não esteja disponível no
	banco de dados, apenas seu valor hash.
*/
unsigned int hash_function(char *str){
	unsigned int low = 0;
	unsigned int high = 1;
	int tam = strlen(str);

	for(int i = 0; i < tam; i++){
		low = (low+str[i]) % 65521;
		high = (low+high) % 65521;
	}

	return ((high << 16) | low);
}

/*
	A função student_create retorna um aluno, dadas suas informações.
	O número usp é guardado como string para servir como chave de busca
	na tabela, enquanto a senha é armazenada encriptada.
*/
Student *student_create(char *nusp, char *password, double *grades){
	Student *new_student = (Student*) calloc(1, sizeof(Student));

	new_student->nusp = (char*) calloc(strlen(nusp)+1, sizeof(char));
	strcpy(new_student->nusp, nusp);

	new_student->password = hash_function(password);

	new_student->grades = (double*) calloc(4, sizeof(double));
	
	for (int i = 0; i < 4; i++){
		new_student->grades[i] = grades[i];
	}

	return new_student;
}

char *get_nusp(Student *student){
	return student->nusp;
}

void student_print(Student *student){
	printf("Notas: P1=%.1lf, P2=%.1lf, T1=%.1lf, T2=%.1lf \n", 
		   student->grades[0], student->grades[1],
		   student->grades[2], student->grades[3]);
}

boolean student_compare_nusp(Student *student1, Student *student2){
	if (strcmp(student1->nusp, student2->nusp) == 0) return TRUE;
	return FALSE;
}

/*
	A função student_validate_password é utilizada para verificar se,
	dada uma senha pelo usuário, esta corresponde ou não com a senha 
	armazenada em um determinado item da tabela de forma a não ser
	possível acessar a senha fora da struct.
*/
boolean student_validate_password(Student *student, char *password){
	unsigned int entry_password = hash_function(password);
	return (entry_password == student->password);
}

void student_delete(Student **student_ref){
	Student *student = *student_ref;

	free(student->nusp);
	free(student->grades);
	free(student);
	*student_ref = NULL;
}