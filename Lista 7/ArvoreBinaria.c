#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" //inclui os Prot�tipos

int chamadas_recursivas = 0;

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
/*Essa função para inserir faz os seguintes passos, verifica se a raiz existe, declara um novo no, aloca esse no, passa
o int valor como info dele e coloca os ponteiros de direita e esquerda como nulo, verifica se a raiz é vazia se for passa 
o ponteiro de raiz para o no criado, se não for declara dois nos, um atual que aponta para a raiz, e um ant que é nulo
faz um while até o atual ficar nulo, igual anterior ao atual, se valor for igual a um dado ele já libera e retorna, ai o
caminhamento do no depende se o valor dele é maior que o atual se for ele anda para direita se for menos ele anda para esquerda
e faz isso até atual ficar nulo ou encontrar um valor igual. Após sair do while ele vai verificar se o valor é maior que 
o anterior, mesmo passo de dentro do while, mas esse é para colocar o nó no lugar certo. Fazendo assim uma ordenação.*/


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
/*A função verifica se a arvore existe, declara dois nos, um anterior e um atual que é igual a raiz, faz um while que 
para quando o atual for nulo, se o valor passado for igual ao valor do atual ele entra no if, que verifica se o atual é 
a própria raiz, se for chama a função para remover, caso não for verifica se é o do da direita ou da esquerda, depois disso
retorna 1. Caso não tenha entrado no primeiro if, iguala ant com atual e verifica se o valor é maior que o no atual, se for anda 
para direita, se não for anda para esquerda. Se sair do while é porque não existe.*/


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
/*Se o nó não possui filho à esquerda, simplesmente retorna o filho à direita, liberando o nó atual.
Se possui filho à esquerda, procura o maior nó da subárvore esquerda (mais à direita), 
ajusta os ponteiros do pai desse nó e do próprio nó removido para manter a estrutura da árvore,
e então libera o nó atual, retornando o novo nó que ocupará sua posição.
*/



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

void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n",(*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}
/*Essa função realiza o percurso em ordem (emOrdem) na árvore binária.
Primeiro visita recursivamente a subárvore esquerda, depois imprime o valor da raiz,
e em seguida visita recursivamente a subárvore direita. 
Em uma árvore binária de busca, esse percurso imprime os valores em ordem crescente.*/


void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));        
        printf("%d\n",(*raiz)->info);
    }
}
/*Essa função realiza o percurso pós-ordem (posOrdem) na árvore binária.
Primeiro visita recursivamente a subárvore esquerda, depois a subárvore direita,
e só então imprime o valor da raiz. Esse percurso é útil, por exemplo, para liberar
todos os nós da árvore, pois garante que os filhos sejam processados antes do pai.*/


int totalNO_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz != NULL){
        chamadas_recursivas++;
        totalNO_ArvBin(&((*raiz)->esq));
        totalNO_ArvBin(&((*raiz)->dir));
    }
    return chamadas_recursivas;
}
/*Funciona de uma forma parecida com as funções de ordem, ela usa uma variavel global que soma para cada nó que ela anda
e no final retorna a quantidade de chamadas recursivas que é a mesma quantidade de nós*/


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
/*Faz a verificação se a raiz é nula ou vazia, declara um atual que é 
igual a raiz, faz um while com a condição de atual diferente de nulo, se o valor
de atual for o mesmo que o do valor passado como parametro ele retorna 1 que encontrou
caso não ele entra num if para ver se o valor é maior que o atual, se for ele vai para a direita
se não for ele vai para esquerda, e é assim até atual ficar nulo, se não encontrar retorna 0*/
