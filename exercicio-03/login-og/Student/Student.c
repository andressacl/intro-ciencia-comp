#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Student.h"

struct student_st {
	char nusp[20];
	char password[30];
	double *notas;
}; 

Student *student_create(char *nusp, char *senha, double *notas){
	Student *new_student = (Student*) calloc(1, sizeof(Student));


	strcpy(new_student->nusp, nusp);
	strcpy(new_student->password, senha);
	new_student->notas = (double*) calloc(4, sizeof(double));
	
	for (int i = 0; i < 4; i++){
		new_student->notas[i] = notas[i];
	}

	return new_student;
}

void student_print(Student *student){
	// printf("Número USP: %s ", student->nusp);
	// printf("Senha: %s ", student->password);
	printf("Notas: P1=%.1lf, P2=%.1lf, T1= %.1lf, T2=%.1lf \n", 
		   student->notas[0], student->notas[1],
		   student->notas[2], student->notas[3]);
}

boolean student_validate_password(Student *student, char *password){
	if (strcmp(password, student->password) == 0) return TRUE;
	return FALSE;
}

char *get_nusp(Student *student){
	return student->nusp;
}

void student_delete(Student **student_ref){
	Student *student = *student_ref;

	free(student->notas);
	free(student);
	*student_ref = NULL;
}