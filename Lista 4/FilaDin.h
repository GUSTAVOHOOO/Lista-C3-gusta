struct elemento{
    int n;
    struct elemento *prox;
}; typedef struct elemento Elem;

struct fila{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
}; typedef struct fila Fila;

//Definição de fila de pilhas
typedef struct elemPI {
    int n; 
    struct elemPI* prox; 
} ElemPI;

typedef ElemPI* Pilha; 

typedef struct elemFila {
    Pilha* pilha;
    struct elemFila* prox;
} ElemFila;

typedef struct filaPI {
    ElemFila* inicio;
    ElemFila* final;
    int qtd;
} FilaPI;

//Definição para criar fila de filas
typedef struct elemFilaFI {
    Fila* fi;
    struct elemFilaFI* prox;
} ElemFilaFI;

typedef struct filaFI {
    ElemFilaFI* inicio;
    ElemFilaFI* final;
    int qtd;
} FilaFI;

//Criacao da pilha de fila
typedef struct elemPIFI {
    Fila* fi; // Ponteiro para uma fila
    struct elemPIFI* prox; // Ponteiro para o próximo elemento da pilha
} ElemPIFI;

typedef ElemPIFI* PilhaFI;

//construção Fila de aviões
typedef struct aviao {
    int capacidade;
    char modelo[50];
    char destino[50];
} Aviao;

typedef struct elemAero {
    Aviao a;
    struct elemAero* prox;
} ElemAero;

struct filaAeroporto{
    struct elemAero *inicio;
    struct elemAero *final;
    int qtd;
};
typedef struct filaAeroporto FilaAE; 


Fila* cria_Fila();
void libera_Fila(Fila* fi);
int consulta_Fila(Fila* fi, int n);
int insere_Fila(Fila* fi, int n);
int remove_Fila(Fila* fi);
int tamanho_Fila(Fila* fi);
int Fila_vazia(Fila* fi);
int Fila_cheia(Fila* fi);
void imprime_Fila(Fila* fi);

int separa(Fila *f1, Fila *f2, int n); //Exercicio 1

//Dessa função até a liberaFILAPI são todas para construir uma fila de pilhas.
Pilha* cria_Pilha();
int insere_Pilha(Pilha* pi, int n);
void imprime_Pilha(Pilha* pi);
void libera_Pilha(Pilha* pi);
int insere_FilaPI(FilaPI* fi, Pilha *pi);
FilaPI* cria_FilaPI();
void imprime_FilaPI(FilaPI* fi);
void libera_FilaPI(FilaPI* fi);

//Dessa função até a imprime fila é feita para criar fila de filas.
FilaFI* cria_FilaFI();
int insereFilaFI(FilaFI* fi, Fila* n);
void imprime_FilaFI(FilaFI* fi);

//Dessa função até liberaPilhaFI são para criar uma pilha de fila
PilhaFI* cria_PilhaFI();
int insere_PilhaFI(PilhaFI* pi, Fila* fi);
void imprime_PilhaFI(PilhaFI* pi);
void libera_PilhaFI(PilhaFI* pi);

//Resolução exercicio 3
Fila* ex3(Fila* fi);
int remove_Pilha(Pilha* pi);

//Criação das funções necessárias para a fila no aeroporto
FilaAE* cria_FilaAE();
int insere_FilaAE(FilaAE* fi, Aviao a);
int remove_FilaAE(FilaAE* fi);
int tamanhoFilaAE(FilaAE* fi);
void listaAero(FilaAE* fi);
void primeiroAviao(FilaAE* fi);
void liberaFilaAE(FilaAE* fi);

void ex7(Fila* fi);

void ex8(Fila* fi, Fila* f2, Fila* f3);