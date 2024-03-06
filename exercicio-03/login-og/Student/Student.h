#ifndef STUDENT_H
#define STUDENT_H

#include "../Util/Util.h"

typedef struct student_st Student;

Student *student_create(char *nusp, char *senha, double *notas);

boolean student_validate_password(Student *student, char *password);

void student_print(Student *student);
void student_delete(Student **student);
char *get_nusp(Student *student);

void student_delete(Student **student_ref);

#endif //STUDENT_H