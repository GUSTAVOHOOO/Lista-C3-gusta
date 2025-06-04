
typedef struct NO* ArvBin;

extern int chamadas_recursivas;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
void preOrdem_ArvBin(ArvBin *raiz);

/*Funções feitas para o exercicio 2*/
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

/*Funções para o exercicio 3*/
int totalNO_ArvBin(ArvBin *raiz);

/*Função apra o exercicio 4*/
int cons_Arvore(ArvBin *raiz, int valor);

/*Função do exercicio 5 (Já estava feita com o código, só comentei)*/
struct NO* remove_atual(struct NO* atual);