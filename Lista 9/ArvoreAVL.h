
typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_NO(struct NO* no);
void libera_ArvAVL(ArvAVL *raiz);
int altura_NO(struct NO* no);
int fatorBalanceamento_NO(struct NO* no);
int maior(int x, int y);
int estaVazia_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
void preOrdem_ArvAVL(ArvAVL *raiz);
void emOrdem_ArvAVL(ArvAVL *raiz);
void posOrdem_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, int valor);
void RotacaoLL(ArvAVL *raiz);
void RotacaoLR(ArvAVL *raiz);
void RotacaoRL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int data);
struct NO* procuraMenor(struct NO* atual);
int remove_ArvAVL(ArvAVL *raiz, int valor);


void RotacaoRR(ArvAVL *raiz); // Exercicio 4
int verificaArvoreAVL(ArvAVL *raiz); //Exercicio 7

int conta_nos(struct NO* no); //Função aux para o ex 8
void preenche_array(struct NO* no, int *elementos, int *indice); //Função aux para o ex 8
ArvAVL* transformaArvore(ArvAVL* raiz); //Exercicio 8