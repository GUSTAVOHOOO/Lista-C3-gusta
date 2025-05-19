#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncad.h"
int main(){
    struct aluno a[4] = {{1,"Andre",9.5,7.8,8.5},
                         {2,"Ricardo",7.5,8.7,6.8},
                         {2,"Bianca",9.7,6.7,8.4},
                         {4,"Ana",5.7,6.1,7.4}};
    Lista* li = cria_lista();
   
    for(int i=0; i < 4; i++)
        insere_lista_final(li,a[i]);


    remover_repetidos(li);
    imprime_lista(li);



    return 0;
}

