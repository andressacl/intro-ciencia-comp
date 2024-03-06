#ifndef LISTA_H
#define LISTA_H

#include "../Aluno/Aluno.h"
#include "../Arvore/Arvore.h"

typedef struct lista_st Lista;

Lista *lista_create(int capacity);

int lista_tam(Lista *lista);
Aluno **lista_elements(Lista *lista);

void lista_print(Lista *lista);
void lista_register_element(Lista *lista, Aluno *aluno);

Lista *torneioGeralSort(Lista *lista);

void lista_delete(Lista **lista_ref);

#endif //LISTA_H