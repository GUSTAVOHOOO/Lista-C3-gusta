#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
int main(){
   
    Grafo* gr = cria_Grafo(6, 6, 1); // Grafo ponderado com 6 vértices
    
    // Adicionando arestas com pesos
    insereAresta(gr, 0, 1, 0, 6.0);
    insereAresta(gr, 0, 2, 0, 1.0);
    insereAresta(gr, 1, 2, 0, 5.0);
    insereAresta(gr, 1, 3, 0, 3.0);
    insereAresta(gr, 2, 3, 0, 8.0);
    insereAresta(gr, 2, 4, 0, 2.0);
    insereAresta(gr, 3, 4, 0, 7.0);
    insereAresta(gr, 3, 5, 0, 9.0);
    insereAresta(gr, 4, 5, 0, 4.0);
    
    printf("\n=== Exemplo de MST com Algoritmo de Prim ===\n");
    printf("Grafo original:\n");
    imprime_Grafo(gr);
    
    int* pai = prim(gr, 0);
    imprime_MST(gr, pai);


    grafoSimplesConexo();
    grafoSimplesConexo2();
    grafoSimplesDirecionado();
    grafoSimplesNaoDirecionado();


    
    free(pai);
    libera_Grafo(gr);

    
    return 0;
}
