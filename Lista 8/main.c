#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int main() {
    // Primeira árvore
    int N1 = 14, dados1[] = {13, 6, 19, 4, 10, 16, 21, 1, 5, 8, 17, 20, 23, 11};
    ArvBin* raiz1 = cria_ArvBin();

    // Segunda árvore (igual à primeira)
    ArvBin* raiz2 = cria_ArvBin();

    // Terceira árvore (mesma estrutura, valores diferentes)
    ArvBin* raiz3 = cria_ArvBin();
    int N3 = 14, dados3[] = {50, 25, 75, 12, 30, 60, 90, 5, 15, 27, 65, 80, 95, 35};

    // Preenche as árvores
    printf("Preenchendo as arvores...\n");
    int i;
    for(i = 0; i < N1; i++) {
        insere_ArvBin(raiz1, dados1[i]);
        insere_ArvBin(raiz2, dados1[i]);  // Mesmos dados que raiz1
        insere_ArvBin(raiz3, dados3[i]);  // Dados diferentes
    }

    // Exercício 1: Conta os nós folha
    printf("\n--- Exercicio 1: Contagem de nos folha ---\n");
    nos_folha = 0; // Reinicia a variável global
    printf("Numero de nos folha na arvore 1: %d\n", nos_folhaArv(raiz1));

    // Exercício 2: Imprime a árvore com hierarquia
    printf("\n--- Exercicio 2: Impressao da arvore com hierarquia ---\n");
    printf("Arvore 1:\n");
    imprime_arvore(raiz1, 0);

    // Exercício 3: Consulta valores na árvore
    printf("\n--- Exercicio 3: Consulta de valores ---\n");
    int valorExistente = 10;
    int valorInexistente = 100;
    printf("Valor %d existe na arvore? %s\n", valorExistente, 
           cons_Arvore(raiz1, valorExistente) ? "Sim" : "Nao");
    printf("Valor %d existe na arvore? %s\n", valorInexistente, 
           cons_Arvore(raiz1, valorInexistente) ? "Sim" : "Nao");

    // Exercício 4: Imprime folhas em ordem decrescente
    printf("\n--- Exercicio 4: Folhas em ordem decrescente ---\n");
    printf("Folhas da arvore 1 em ordem decrescente:\n");
    folhas_decrescente(raiz1);

    // Exercício 5: Verifica se duas árvores são iguais
    printf("\n--- Exercicio 5: Arvores iguais ---\n");
    printf("Arvore 1 e Arvore 2 sao iguais? %s\n", 
           arvoresIguais(raiz1, raiz2) ? "Sim" : "Nao");
    printf("Arvore 1 e Arvore 3 sao iguais? %s\n", 
           arvoresIguais(raiz1, raiz3) ? "Sim" : "Nao");

    // Exercício 6: Remove nós pares
    printf("\n--- Exercicio 6: Remocao de nos pares ---\n");
    printf("Arvore 1 antes da remocao de pares:\n");
    imprime_arvore(raiz1, 0);
    
    remove_pares(raiz1);
    
    printf("\nArvore 1 apos remocao de pares:\n");
    imprime_arvore(raiz1, 0);

    // Exercício 7: Verifica se duas árvores são similares
    printf("\n--- Exercicio 7: Arvores similares ---\n");
    printf("Arvore 2 e Arvore 3 sao similares? %s\n", 
           arvoresSimilares(raiz2, raiz3) ? "Sim" : "Nao");

    // Libera memória
    libera_ArvBin(raiz1);
    libera_ArvBin(raiz2);
    libera_ArvBin(raiz3);

    printf("\nPrograma finalizado com sucesso!\n");
    return 0;
}
