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
/*A lógica desse exercicio, é que ele percorre a primeira fila, e quando o N for igual ao N passado, é nesse ponto aonde
a 2 fila começa passa o final da segunda fila como o final da primeira, e passa o final da primeira fila como o no que está
sendo visto */

//Dessa função até a liberaFILAPI são todas para construir uma fila de pilhas.
Pilha* cria_Pilha();
int insere_Pilha(Pilha* pi, int n);
int remove_Pilha(Pilha* pi);
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
/*Todas essas funções são basicamente as ja passadas nos exercicios apenas com os diferencias das filas,
filas de filas, filas de pilha, pilha de filas.*/


//Resolução exercicio 3
Fila* ex3(Fila* fi);
/*Esse exercicio foi feito basicamente é instaciada a pilha, e enquanto a fila nao for nula é feito a remoção de elemento
e sendo empilhados, e depois é feito o processo inverso, enquanto a pilha nao for nula é feito o desempilhamento e passando
os elementos para dentro da fila*/

int Furafila(Fila* fi, int n);
int insere_Fila_Circ(Fila* fi, int n);
int remove_Fila_circ(Fila* fi);
void imprime_Fila_circ(Fila* fi);
/* A fila circular difernetemente da fila tradicional não possui um "fim" por isso usamos a função furar fila 
para adicionar mai uma estrutura no "meio" da fila circular, pois diferente da fila tradicional não há 
ponteiros apontando para null , no cado o final aponta para prox que paonta para inicio fazendo a circularidade
da fila */

//Criação das funções necessárias para a fila no aeroporto
FilaAE* cria_FilaAE();
int insere_FilaAE(FilaAE* fi, Aviao a);
int remove_FilaAE(FilaAE* fi);
int tamanhoFilaAE(FilaAE* fi);
void listaAero(FilaAE* fi);
void primeiroAviao(FilaAE* fi);
void liberaFilaAE(FilaAE* fi);
/*Todos essas funções são porque tinha que criar novas para funcionar com o struct de aviao, a lógica é simples, ele mostra
o primeiro avião e suas caracteristicas, decola um aviao, coloca mais um na fila e lista todos eles.*/

void ex7(Fila* fi);
/*Aqui é a mesma lógica do exercicio 3 porém sem a pilha auxiliar, no lugar coloquei um vetor, ele desempilha e povoa o vetor
e quando a fila fica nula ele começa um for de trás pra frente no vetor até o vetor ficar zerado.*/

void mesclarFilas(Fila *F1, Fila *F2, Fila *F3);
/* Basicamente usamos as funçoes previamentes disponibilizadas para fazer consultas nas filas que criamos para
preencher a terceira fila que será criada a partir das anteriores , apos isso usamos um auxiliar para para
restaura as filas que tiveram suas entidades que foram removidas para criar a terceira fila*/

