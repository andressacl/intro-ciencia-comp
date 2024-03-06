#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Student/Student.h"
#include "Util/Util.h"
#include "Hashtable/Hashtable.h"

int define_table_size(int v);
int next_pr(int num);
int is_prime(int num);
 
int main(){

	int n_alunos;
	scanf("%d\n", &n_alunos);

	char nusp[20], senha[30];
	double *notas = (double*) calloc(4, sizeof(double));

	// int table_size = (int) n_alunos*1.5;
	int table_size = define_table_size(n_alunos);
	Hashtable *alunos_ht = ht_create(table_size);

	for (int i = 0; i < n_alunos; i++){
		scanf("%s %s %lf %lf %lf %lf", nusp, senha,
			&notas[0], &notas[1], &notas[2], &notas[3]);

		boolean ctrl = ht_insert_item(alunos_ht, nusp, senha, notas);

		if (ctrl == TRUE){
			printf("Cadastro efetuado com sucesso\n");
		} else {
			printf("NUSP ja cadastrado\n");
		}

	}
	
	// ht_print(alunos_ht);
	// printf("--------------------------------\n");

	free(notas);
	
	int n_op;
	scanf("%d", &n_op);

	for (int i = 0; i < n_op; i++){
		scanf("%s %s", nusp, senha);

		Student *student_p = ht_access_item(alunos_ht, nusp, senha);

		if (student_p == NULL){
			printf("NUSP inválido\n");
		} else {
			if (student_validate_password(student_p, senha) == TRUE){
				student_print(student_p);
			} else {
				printf("Senha incorreta para o NUSP digitado\n");
			}
		}
	}

	ht_delete_table(&alunos_ht);
	return 0;
}

int define_table_size(int v){
	v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    // printf("%d\n", next_pr(v));
    return next_pr(v);
}

int next_pr(int num){
    int c;
    if(num < 2)
        c = 2;
    else if (num == 2)
        c = 3;
    else if(num & 1){
        num += 2;
        c = is_prime(num) ? num : next_pr(num);
    } else
        c = next_pr(num-1);

    return c;
}

int is_prime(int num){
    if((num & 1)==0)
        return num == 2;
    else {
        int i, limit = sqrt(num);
        for (i = 3; i <= limit; i+=2){
            if (num % i == 0)
                return 0;
        }
    }
    return 1;
}
