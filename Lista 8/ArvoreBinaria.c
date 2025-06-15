#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" //inclui os Prot�tipos

int nos_folha = 0;


struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}

int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0;//elemento j� existe
            }

            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

// http://www.ime.usp.br/~pf/algoritmos/aulas/binst.html
int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    // no2 � o n� anterior a r na ordem e-r-d
    // no1 � o pai de no2
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}


int nos_folhaArv(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz != NULL){
        if((*raiz)->esq == NULL && (*raiz)->dir == NULL) 
            nos_folha ++;
        nos_folhaArv(&((*raiz)->esq));
        nos_folhaArv(&((*raiz)->dir));
    }
    return nos_folha;
}
/*
Exercicio 1: 
Essa função retorna de forma recursiva a quantidade de nós folhas, nós que não tem nenhum filho, ela usa uma variável global para que a cada no sem filho
seja somado, e retorna de forma recursiva, a base é a mesma das pré_ordem porém com a alteração da soma da variavel.
*/

int cons_Arvore(ArvBin *raiz, int valor){
    if(raiz == NULL || *raiz == NULL) return 0;

    struct NO* atual = *raiz;
    
    while(atual != NULL){
        if(atual->info == valor) return 1;
        
        if(valor > atual->info){
            atual = atual->dir;
        }else{
            atual = atual->esq;
        }
    }

    return 0;
}

/*
Exercicio 2:
A função recebe a árvore e um inteiro que indica o nível do nó na hierarquia. Primeiro verifica se a árvore existe 
e não está vazia. Em seguida, imprime espaços de acordo com o nível para criar a indentação visual. Depois, 
analisa se o nó é uma folha (sem filhos) ou um pai (com pelo menos um filho) e imprime o valor do nó com essa informação.
Para cada filho existente (esquerdo ou direito), chama recursivamente a função aumentando o nível de indentação
e indicando a direção do filho (E para esquerda, D para direita), criando assim uma representação visual
da estrutura hierárquica da árvore.
*/

void imprime_arvore(ArvBin *raiz, int nivel) {
    if(raiz == NULL || *raiz == NULL)
        return;
    
    int i;
    for(i = 0; i < nivel; i++)
        printf("   ");
    
    // Verifica se é folha (sem filhos)
    if((*raiz)->esq == NULL && (*raiz)->dir == NULL)
        printf("%d [FOLHA]\n", (*raiz)->info);
    else
        printf("%d [PAI]\n", (*raiz)->info);
    
    // Se tiver filho à esquerda
    if((*raiz)->esq != NULL) {
        for(i = 0; i < nivel+1; i++)
            printf("   ");
        printf("E: ");
        imprime_arvore(&((*raiz)->esq), nivel+1);
    }
    
    // Se tiver filho à direita
    if((*raiz)->dir != NULL) {
        for(i = 0; i < nivel+1; i++)
            printf("   ");
        printf("D: ");
        imprime_arvore(&((*raiz)->dir), nivel+1);
    }
}


/*
Exercicio 3:
Como a árvore binária que estamos trabalhando não tem como inserir mais de um valor igual, essa função verifica se um valor passado como parametro existe dentro 
da árvore existe. Primeiro faz a verificação se a árvore existe e se ela está vazia, declara um no que é igual a raiz, e enquanto o no for diferente de nulo ele 
vai caminhando, se o valor for achado retorna 1, se não for ele vai verificando se é maior ou menor para ir para direita e esquerda. Se sair do while significa que não
está presente dentro da árvore
*/

void folhas_decrescente(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return;
    folhas_decrescente(&((*raiz)->dir));
    if((*raiz)->esq == NULL && (*raiz)->dir == NULL)
        printf("%d\n", (*raiz)->info);
    folhas_decrescente(&((*raiz)->esq));
}
/*
Exercicio 4:
Essa função imprime de forma decrescente os nós folha, ela segue a mesma base das funções para printar de forma recursiva porém com uma mudança,
ela sempre vai para o mais a direita possível e ai printa apenas os nos onde os ponteiros da esquerda e da direita forem nulos, os nos folhas. 
*/


int arvoresIguais(ArvBin *raiz, ArvBin *raiz2){    
    if((raiz == NULL || raiz2 == NULL) || (*raiz == NULL || *raiz2 == NULL)) return 0; 

    if(altura_ArvBin(raiz) != altura_ArvBin(raiz2)) return 0;

    if((*raiz)->info != (*raiz2)->info) return 0;

    if((raiz == NULL && raiz2 == NULL) || (*raiz == NULL && *raiz2 == NULL)) return 1; 

    arvoresIguais(&((*raiz)->esq), &((*raiz2)->esq)) && arvoresIguais(&((*raiz)->dir), &((*raiz2)->dir));
}
/*
Exercicio 5:
Essa função retorna 0 se a as duas arvores passadas forem diferentes, e retorna 1 se as duas são iguais. Começa comparando caso não seja igual, 
que é para ver se apenas uma das raizes existem ou se apenas umas delas são vazias, se for algum desses casos elas não são iguais. Compara se a 
altura das arvores são as mesmas, se for retorna 0, compara se os inteiros dentro dos nos são diferentes, se forem retorna 0 também. Só retorna 1 se as
duas arvores forem vazias juntas ou não existirem juntas. O passo recursivo retorna andando com as duas arvores para direita e para esquerda. 
*/

void remove_pares(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL) return;

    remove_pares(&((*raiz)->dir));
    remove_pares(&((*raiz)->esq));

    if((*raiz) != NULL && (*raiz)->info % 2 == 0){
        remove_ArvBin(raiz, (*raiz)->info);
    }
}
/*
Exercicio 6:
Nessa função com o objetivo de reitrar os pares da arvore é feita a verificação de segurança caso a arvore não exista ou seja vazia, após isso ele caminha pelos 
nós, fazendo com que só remova após chegar nos filhos dos nós a serem removidos, para ser feita a remoção correta, ai depois de caminhar ele verifica se a raiz 
é diferente de nula e se o numero é divisivel por 2 com resto 0, se for ele remove.
*/

int arvoresSimilares(ArvBin *raiz, ArvBin *raiz2){
    if((raiz == NULL && raiz2 == NULL) || (*raiz == NULL && *raiz2 == NULL)) return 1; 

    if((raiz == NULL || raiz2 == NULL) || (*raiz == NULL || *raiz2 == NULL)) return 0; 

    return arvoresSimilares(&((*raiz)->esq), &((*raiz2)->esq)) && arvoresSimilares(&((*raiz)->dir), &((*raiz2)->dir));
}
/*
Exercicio 7:
Nessa função eu utilizei da lógica das função das arvores iguais porque é praticamente o mesmo problema, apenas não preciso saber do valor dos nós
então a função percorre as duas raizes de forma recursiva e tem a verificação dos if's um para ver se todos os ponteiros são nulos e um para ver se apenas
um deles é nulo. Assim é possível descobrir se as arvores são similares e possuem o mesmo formato.
*/