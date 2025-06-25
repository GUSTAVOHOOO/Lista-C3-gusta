#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h" //inclui os Prot�tipos
#include <float.h>

#define INFINITY FLT_MAX

//Defini��o do tipo Grafo
struct grafo{
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
};


/*
Exercicio 3:
    A função cria grafo recebe 3 parametos, o numero de vertices, o numero de grau máximo, e se é ou não ponderado (se as vertices tem peso).
    Declara o grafo e aloca dinamicamente, passa as variaveis para dentro da estrutura do grafo, e aloca um vetor para os graus na quantidade de numero de vertices,
    aloca dinamicamente a quantidade de arestas de acordo com o numero de vertices, entra no for e aloca mais uma vez só que agora de acordo com o numero máximo de 
    grau. Se o grafo por ponderado ele cria uma outra alocação igual a de cima para armazenar os valores dos pesos de cada vertice.
*/
Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = (eh_ponderado != 0)?1:0;
        gr->grau = (int*) calloc(nro_vertices,sizeof(int));

        gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));
        for(i=0; i<nro_vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));

        if(gr->eh_ponderado){
            gr->pesos = (float**) malloc(nro_vertices * sizeof(float*));
            for(i=0; i<nro_vertices; i++)
                gr->pesos[i] = (float*) malloc(grau_max * sizeof(float));
        }

    }
    return gr;
}

/*
Exercicio 3:
    A função recebe um grafo como parametro, verifica se ele é diferente de nulo, é declarado um int, para ir percorrendo de 0 até o numero de vertices, e ir liberando aresta por aresta.
    E novamente se for ponderado ele libera da mesma maneira pois a estrutura é a mesma, e depois libera o vetor do grau e só depois de liberar essas 3 estruturas alocadas na mémoria que ele 
    libera o grafo.
*/
void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        if(gr->eh_ponderado){
            for(i=0; i<gr->nro_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

/*
Exercicio 3:
    A função de inserir aresta recebe 5 parametros, o grafo a ser colocado a aresta, a origem da aresta, o destino dessa aresta, se é digrafo (se apenas vai, não volta), e se 
    tem peso para essa aresta. Primeiro tem as funções de segurança, verifica se o grafo existe, se a origem dele é menor que 0, ou se essa origem é maior ou igual ao numero de vertices
    e o mesmo processo para o destino, isso garante que exista uma vertice para ser feita a conexão e que não estoure o limite máximo de grau. Esse (gr->arestas[orig][gr->grau[orig]] = dest)
    serve para ajustar dentro da lista adjacente que essa vertice de origem tem uma aresta para o destino, se o grafo for ponderado ele faz o mesmo processo e passa o peso para dentro da lista adjacente
    dos pesos. E ajusta dentro do vetor de grau para adicionar mais uma aresta para a vertice de origem. Caso a aresta não seja digrafo, ele chama a função de novo invertendo o destino com a origem e passando 
    1 como digrafo, essa chamada de função serve para que o processo seja feito para que a o destino passado originalmente consiga apontar para a origem.
*/
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    gr->arestas[orig][gr->grau[orig]] = dest;
    if(gr->eh_ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    if(eh_digrafo == 0)
        insereAresta(gr,dest,orig,1,peso);
    return 1;
}

/*
Exercicio 3:
    Nessa função é passado 4 parametros, o grafo a ser retirado a aresta, a origem daonde essa aresta vai ser removida, o destino, e se é digrafo ou não.
    É feita as verificações de segurança, se o grafo existe, se a origem ou o destino estão dentro dos padrões para o grafo, caso contrário já é retornado 0.
    é declarado um int que vai ser utilizado para achar o destino, dentro do while ele percorre até achar o destino ou até ser igual a quantidade de graus da origem
    se for igual a quantidade de graus da origem é porque o destino não foi achado. Se foi achado já é decrementado dentro do vetor de grau, e essa é a linha de código
    que faz com que a remoção seja feita (gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]]) se o grafo for ponderado ele repete o processo para retirar o peso 
    da lista adjacente, e se não for digrafo ele chama a função de novo para fazer a retirada para o destino para a origem, se não for ele só retorna 1.
*/
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    int i = 0;
    while(i<gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if(i == gr->grau[orig])//elemento nao encontrado
        return 0;
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    if(gr->eh_ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
    if(eh_digrafo == 0)
        removeAresta(gr,dest,orig,1);
    return 1;
}

void imprime_Grafo(Grafo *gr){
    if(gr == NULL)
        return;

    int i, j;
    for(i=0; i < gr->nro_vertices; i++){
        printf("%d: ", i);
        for(j=0; j < gr->grau[i]; j++){
            if(gr->eh_ponderado)
                printf("%d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]);
            else
                printf("%d, ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}

void grafoSimplesDirecionado(){
    Grafo* gf = cria_Grafo(4, 4, 0);

    printf("\n");
    insereAresta(gf, 0, 1, 1, 0);
    insereAresta(gf, 1, 2, 1, 0);
    insereAresta(gf, 2, 3, 1, 0);
    
    printf("Grafo simples direcionado: \n");
    imprime_Grafo(gf);
    
    printf("\n");
    libera_Grafo(gf);
}


void grafoSimplesNaoDirecionado(){
    Grafo* gf = cria_Grafo(4, 4, 0);

    printf("\n");
    insereAresta(gf, 0, 1, 0, 0);
    insereAresta(gf, 1, 2, 0, 0);
    insereAresta(gf, 2, 3, 0, 0);

    printf("Grafo simples não direcionado: \n");
    imprime_Grafo(gf);
    
    printf("\n");
    libera_Grafo(gf);
}

void grafoSimplesConexo(){
    Grafo* gf = cria_Grafo(8,6,0);
    
    printf("\n");
    insereAresta(gf, 0, 1, 0, 0);
    insereAresta(gf, 0, 2, 0, 0);
    insereAresta(gf, 0, 3, 0, 0);
    insereAresta(gf, 0, 4, 0, 0);
    insereAresta(gf, 0, 5, 0, 0);
    insereAresta(gf, 0, 6, 0, 0);
    insereAresta(gf, 1, 2, 0, 0);
    insereAresta(gf, 1, 3, 0, 0);
    insereAresta(gf, 1, 4, 0, 0);
    insereAresta(gf, 2, 4, 0, 0);
    insereAresta(gf, 2, 6, 0, 0);
    insereAresta(gf, 3, 7, 0, 0);
    
    imprime_Grafo(gf);

    printf("\n");
    libera_Grafo(gf);
}

void grafoSimplesConexo2(){
    Grafo* gf = cria_Grafo(8,5,0);
    
    printf("\n");
    insereAresta(gf, 0, 1, 0, 0);
    insereAresta(gf, 0, 2, 0, 0);
    insereAresta(gf, 0, 3, 0, 0);
    insereAresta(gf, 0, 4, 0, 0);
    insereAresta(gf, 0, 5, 0, 0);
    insereAresta(gf, 1, 4, 0, 0);
    insereAresta(gf, 1, 5, 0, 0);
    insereAresta(gf, 1, 6, 0, 0);
    insereAresta(gf, 1, 7, 0, 0);
    insereAresta(gf, 2, 4, 0, 0);
    insereAresta(gf, 2, 5, 0, 0);
    insereAresta(gf, 2, 6, 0, 0);
    insereAresta(gf, 2, 7, 0, 0);
    insereAresta(gf, 3, 6, 0, 0);
    insereAresta(gf, 3, 7, 0, 0);
    
    imprime_Grafo(gf);
    
    printf("\n");
    libera_Grafo(gf);
}


/*
Exercicio 2:
    a) O grafo tem 11 arestas.
    b) O grafo tem 7 vértices.
    c) Não é possível.
    d) Passando por 'DFW' pois tem um peso menor que o caminho direto.
    Os exercicios E e F estão dentro da pasta imagens.
*/

int* prim(Grafo* gr, int inicio) {
    if(gr == NULL) return NULL;
    if(inicio < 0 || inicio >= gr->nro_vertices) return NULL;
    if(!gr->eh_ponderado) return NULL; // Prim só funciona em grafos ponderados
    
    int i, j, dest, atual;
    float menor_peso;
    int* pai = (int*)malloc(gr->nro_vertices * sizeof(int));
    float* menor = (float*)malloc(gr->nro_vertices * sizeof(float));
    int* visitado = (int*)malloc(gr->nro_vertices * sizeof(int));
    
    // Inicialização
    for(i = 0; i < gr->nro_vertices; i++) {
        pai[i] = -1;
        menor[i] = INFINITY;
        visitado[i] = 0;
    }
    menor[inicio] = 0;
    
    // Algoritmo de Prim
    for(i = 0; i < gr->nro_vertices; i++) {
        // Encontra vértice com menor peso não visitado
        atual = -1;
        menor_peso = INFINITY;
        for(j = 0; j < gr->nro_vertices; j++) {
            if(!visitado[j] && menor[j] < menor_peso) {
                atual = j;
                menor_peso = menor[j];
            }
        }
        
        if(atual == -1) break; // Não há mais vértices alcançáveis
        
        visitado[atual] = 1;
        
        // Atualiza os menores pesos dos vértices adjacentes
        for(j = 0; j < gr->grau[atual]; j++) {
            dest = gr->arestas[atual][j];
            if(!visitado[dest] && gr->pesos[atual][j] < menor[dest]) {
                pai[dest] = atual;
                menor[dest] = gr->pesos[atual][j];
            }
        }
    }
    
    free(menor);
    free(visitado);
    
    return pai;
}

// Função para imprimir a MST encontrada
void imprime_MST(Grafo* gr, int* pai) {
    if(gr == NULL || pai == NULL) return;
    
    printf("Árvore Geradora Mínima:\n");
    float peso_total = 0;
    
    for(int i = 0; i < gr->nro_vertices; i++) {
        if(pai[i] != -1) {
            // Encontrar o peso da aresta (pai[i], i)
            float peso = 0;
            for(int j = 0; j < gr->grau[pai[i]]; j++) {
                if(gr->arestas[pai[i]][j] == i) {
                    peso = gr->pesos[pai[i]][j];
                    break;
                }
            }
            
            printf("(%d, %d) Peso: %.2f\n", pai[i], i, peso);
            peso_total += peso;
        }
    }
    
    printf("Peso total da MST: %.2f\n", peso_total);
}