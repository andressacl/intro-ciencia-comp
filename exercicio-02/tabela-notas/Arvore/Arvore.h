#ifndef ARVORE_H
#define ARVORE_H

#include "../Aluno/Aluno.h"

typedef struct arvore_st Arvore;

Arvore *arvore_create(Aluno **alunos, int tam);

void arvore_print(Arvore *arvore);

Aluno *raiz(Arvore *arvore);

void arvore_point_null(Arvore *arvore, int indice);
Aluno *arvore_get_element(Arvore *arvore, int element);
void build_arvore(Arvore *arvore);
void organize_arvore(Arvore *arvore, int i);

void arvore_delete(Arvore **arvore_ref);

#endif //ARVORE_H