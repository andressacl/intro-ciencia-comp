#ifndef STUDENT_H
#define STUDENT_H

#include "../Util/Util.h"

typedef struct student_st Student;

Student *student_create(char *nusp, char *password, double *notas);

unsigned int hash_function(char *str);

void student_print(Student *student);

char *get_nusp(Student *student);
boolean student_validate_password(Student *student, char *password);
boolean student_compare_nusp(Student *student1, Student *student2);

void student_delete(Student **student_ref);

#endif //STUDENT_H