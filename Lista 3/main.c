#include <stdio.h>
#include <stdlib.h>
#include "PilhaDin.h"

int main() {
    
    menu();
    
    Pilha *pilha = cria_Pilha();
    Pilha *pilha2 = cria_Pilha();
    PilhaC *pilhaChar = NULL;
    int n = 0, x = 0, media, maior, menor, impares, pares;

    insere_Pilha(pilha, 10);
    insere_Pilha(pilha, 20);
    insere_Pilha(pilha, 30);
    insere_Pilha(pilha, 40);
    insere_Pilha(pilha, 50);
    
    printf("Digite dois numeros para empilhar: ");
    scanf("%d %d", &n, &x);
    if (push2(pilha, n, x)) {
        printf("Elementos %d e %d empilhados com sucesso.\n", n, x);
        imprime_Pilha(pilha);
    } else {
        printf("Erro ao empilhar os elementos.\n");
    }

    printf("\n-------------------------------------------------------------------------------\n");

    if (pop2(pilha)) {
        printf("Dois elementos desempilhados com sucesso.\n");
        imprime_Pilha(pilha);
    } else {
        printf("Erro ao desempilhar dois elementos.\n");
    }

    printf("\n-------------------------------------------------------------------------------\n");

    printf("Digite o numero de elementos a desempilhar: ");
    scanf("%d", &n);
    if (ex2(pilha, n)) {
        printf("%d elementos desempilhados com sucesso.\n", n);
        imprime_Pilha(pilha);
    } else {
        printf("Erro ao desempilhar os elementos.\n");
    }

    printf("\n-------------------------------------------------------------------------------\n");

    pilha2 = copia(pilha);
    if (pilha2 != NULL) {
        printf("Pilha copiada com sucesso.\n");
        printf("Pilha original:\n");
        imprime_Pilha(pilha);
        printf("Pilha copiada:\n");
        imprime_Pilha(pilha2);
    } else {
        printf("Erro ao copiar a pilha.\n");
    }

    printf("\n-------------------------------------------------------------------------------\n");

    if (ex4(pilha, &media, &maior, &menor)) {
        printf("Media: %d, Maior: %d, Menor: %d\n", media, maior, menor);
    } else {
        printf("Erro ao calcular maior, menor e media.\n");
    }

    // Comparar pilhas
    if (ex5(pilha, pilha2)) {
        printf("As pilhas sao iguais.\n");
    } else {
        printf("As pilhas nao sao iguais.\n");
    }

    printf("\n-------------------------------------------------------------------------------\n");

    ex6();

    printf("\n-------------------------------------------------------------------------------\n");

    pares = ex7(pilha, &impares);
    printf("Pares: %d, Impares: %d\n", pares, impares);

    
    libera_Pilha(pilha);
    libera_Pilha(pilha2);

    return 0;
}

