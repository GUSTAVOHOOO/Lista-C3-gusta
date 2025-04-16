//Arquivo PilhaDin.h

//Criação da pilha de CHAR
struct elementoChar{ 
    char c;
    struct elementoChar *prox;
};
typedef struct elementoChar ElemC; 
typedef struct elementoChar* PilhaC;

typedef struct elemento* Pilha;

//Funções passadas para ajudar a resolver os exercicios
Pilha* cria_Pilha();
void libera_Pilha(Pilha* pi);
int consulta_topo_Pilha(Pilha* pi, int n);
int insere_Pilha(Pilha* pi, int n);
int remove_Pilha(Pilha* pi);
int tamanho_Pilha(Pilha* pi);
int Pilha_vazia(Pilha* pi);
int Pilha_cheia(Pilha* pi);
void imprime_Pilha(Pilha* pi);

//Funções criadas para resolver o exercicio 1
int pop2(Pilha* pi);
int push2(Pilha* pi, int n, int x);

//Função criada para o exercicio 2
int ex2(Pilha *pi, int n);

//Função criada para o exercicio 3
Pilha *copia(Pilha *pi);

//Função do exercicio 4
int ex4(Pilha *pi, int *media, int *maior, int *menor);

//Função do exercicio 5
int ex5(Pilha *pi, Pilha *pa);

//Todas as funções criadas para o exercicio 6 funcionar
PilhaC* cria_PilhaCHAR();
int tamanho_PilhaCHAR(PilhaC* pi);
char* strInvertida(PilhaC* pi);
int insere_PilhaCHAR(PilhaC* pi, char c);
void ex6();
void libera_PilhaCHAR(PilhaC* pi);

//Função do exercicio 7
int ex7(Pilha *pi, int *n);


void menu();
