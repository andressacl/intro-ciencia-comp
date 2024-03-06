#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno_st Aluno;

Aluno *aluno_create(char* name, int *grades, int n_avaliacoes);
Aluno *aluno_create_invalid();

Aluno *ganhador(Aluno *aluno1, Aluno *aluno2);

char *aluno_name(Aluno *aluno);
float aluno_av(Aluno *aluno);
int aluno_desempate(Aluno *aluno);

void aluno_print(Aluno *aluno);

void aluno_delete(Aluno **aluno_ref);

#endif //ALUNO_H