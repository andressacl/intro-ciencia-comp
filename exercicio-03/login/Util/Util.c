#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

/*
    TAD padrão para a adição de funções de uso comum entre os
    outros TADS. 
*/

void boolean_print(boolean bool)
{
    if(bool == TRUE)
    {
        printf("True\n");
    }
    else if(bool == FALSE)
    {
        printf("False\n");
    }
    else
    {
        printf("ERRO\n");
    }
}