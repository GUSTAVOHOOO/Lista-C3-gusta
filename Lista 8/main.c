#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"
int main(){
    int N = 8, dados[8] = {50,100,30,20,40,45,35,37};

    ArvBin* raiz = cria_ArvBin();

    int i;
    for(i=0; i < 8; i++)
        insere_ArvBin(raiz,dados[i]);

    int dados2[8] = {50,120,30,15,40,45,35,37};

    ArvBin* raiz2 = cria_ArvBin();

    
    for(i=0; i < 8; i++)
        insere_ArvBin(raiz2,dados2[i]);
    
    printf("%d",arvoresSimilares(raiz, raiz2));

    
    




    
    
    return 0;
}
