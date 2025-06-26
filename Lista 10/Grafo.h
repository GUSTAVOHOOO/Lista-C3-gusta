//Arquivo Grafo.h

typedef struct grafo Grafo;

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);
void imprime_Grafo(Grafo *gr);

//Funções para o exercicio 1
void grafoSimplesDirecionado(); 
void grafoSimplesNaoDirecionado();
void grafoSimplesConexo();
void grafoSimplesConexo2();

//Exercicio 4
Grafo2* cria_Grafo(int n, int direcionado, int ponderado);
int insere_Aresta(Grafo2* gr, int origem, int destino, float peso);
int remove_Aresta(Grafo2* gr, int origem, int destino);
void libera_Grafo(Grafo2* gr);

//Exercicio 5
int* prim(Grafo* gr, int inicio);
void imprime_MST(Grafo* gr, int* pai);

// Exercício 6
int encontrar_no(Grafo* gr, int no);
float encontrar_aresta_menor_peso(Grafo* gr, int* origem, int* destino);