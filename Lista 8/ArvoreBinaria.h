
extern int nos_folha;

typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_NO(struct NO* no);
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
int estaVazia_ArvBin(ArvBin *raiz);
struct NO* remove_atual(struct NO* atual);
int altura_ArvBin(ArvBin *raiz);
void preOrdem_ArvBin(ArvBin *raiz);


int nos_folhaArv(ArvBin *raiz); // Função para o exercicio 1.

int cons_Arvore(ArvBin *raiz, int valor);//Função para o exercicio 3.

void folhas_decrescente(ArvBin *raiz); //Função para o exercicio 4.

int arvoresIguais(ArvBin *raiz, ArvBin *raiz2); //Função para o exercicio 5.

void remove_pares(ArvBin *raiz); //Função para o exercicio 6.

int arvoresSimilares(ArvBin *raiz, ArvBin *raiz2);