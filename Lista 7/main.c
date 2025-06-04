#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int main(){
    int N = 8, dados[8] = {50,100,30,20,40,45,35,37};

    ArvBin* raiz = cria_ArvBin();

    int i;
    for(i=0; i < N; i++)
        insere_ArvBin(raiz,dados[i]);

    printf("Percurso em ordem:\n");
    emOrdem_ArvBin(raiz);

    printf("\nPercurso pre-ordem:\n");
    preOrdem_ArvBin(raiz);

    printf("\nPercurso pos-ordem:\n");
    posOrdem_ArvBin(raiz);

    printf("\nAltura da arvore: %d\n", altura_ArvBin(raiz));

    int valor = 45;
    printf("\nBusca pelo valor %d: %s\n", valor, cons_Arvore(raiz, valor) ? "Encontrado" : "Nao encontrado");

    totalNO_ArvBin(raiz);
    printf("Chamadas recursivas: %d\n", chamadas_recursivas);

    libera_ArvBin(raiz);
    printf("\nFim!\n");
    return 0;
}
