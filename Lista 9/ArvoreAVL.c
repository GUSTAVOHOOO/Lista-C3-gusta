#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h" //inclui os Prot�tipos

struct NO{
    int info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
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

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        //printf("%d\n",(*raiz)->info);
        //printf("No %d: %d\n",(*raiz)->info,fatorBalanceamento_NO(*raiz));
        printf("No %d: %d\n",(*raiz)->info,altura_NO(*raiz));
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->info);
        printf("No %d: H(%d) fb(%d)\n",(*raiz)->info,altura_NO(*raiz),fatorBalanceamento_NO(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvAVL(&((*raiz)->esq));
        posOrdem_ArvAVL(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}

int consulta_ArvAVL(ArvAVL *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

//=================================
void RotacaoLL(ArvAVL *raiz){//LL
    printf("RotacaoLL\n");
    struct NO *B;
    B = (*raiz)->esq;
    (*raiz)->esq = B->dir;
    B->dir = *raiz;
    (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*raiz)->altura) + 1;
    *raiz = B;
}

void RotacaoLR(ArvAVL *raiz){//LR
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(raiz);
}

void RotacaoRL(ArvAVL *raiz){//RL
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(raiz);
}

int insere_ArvAVL(ArvAVL *raiz, int valor){
    int res;
    if(*raiz == NULL){//�rvore vazia ou n� folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(valor < atual->info){
        if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(valor < (*raiz)->esq->info ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(valor > atual->info){
            if((res = insere_ArvAVL(&(atual->dir), valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info < valor){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

struct NO* procuraMenor(struct NO* atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){// valor n�o existe
	    printf("valor n�o existe!!\n");
	    return 0;
	}

    int res;
	if(valor < (*raiz)->info){
	    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->info < valor){
	    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info == valor){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// n� tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // n� tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}

/*-------------------------------------------------------------------------------------------------------------------------------*/
/*Exercicio 1:
    A primeira arvore apresentada não é AVL pois o primeiro no a esquerda da arvore não esta corretamente balanceado, já
    que se tem uma altura total de 2 para sua esquerda e para sua direita não tem nenhum nó, logo -1 (2 - (-1) = 3, fb = 3), 
    o que ja justifica não ser uma árvore AVL.

    A segunda arvore também não é AVL pelo mesmo motivo o no da esquerda da raiz não está balanceado corretamente pois a altura da sua
    subarvore a esquerda é 2 e a da direita é -1, mesmo caso da primeira arvore.

    A terceira árvore é um árvore AVL pelo fato dela ser apenas um nó o que significa que está totalmente balanceada já que só
    tem ele.

    A quarta arvore não está balanceada da forma correta pois o primeiro no a direita está desbalanceado pois tem 2 de altura na sua 
    subarvore a direita e -1 de altura na sua subarvore a esquerda. Também não é AVL. 
*/


/*
Exercicio 2:

     Os desenhos das arvores ficaram em uma pasta "Exercicio 2 - Desenho".

     Ordem 1 = {50, 30, 20, 70, 40, 35, 37, 38, 10, 32, 45, 42, 25, 47, 36}.
     Primeiro é inserido o 50 como raiz, após o 30 fica como filho a esquerda dele e o 20 fica a esquerda do 30, causando um desbalanceamento tendo que ser feita a rotação
     esquerda simples, trazendo o 30 como raiz, o 70 entra como filho a direita do 50, e o 40 como filho a esquerda do 50, o 35 entra como filho a esquerda do 40 causando um desbalanceamento, 
     o que eu fiz foi uma rotação a esquerda simples para deixar o 40 como pai do 50 e do 35 e apos isso uma rotação a esquerda dupla para deixar o 35 como raiz. Como o 35 como raiz o seu lado
     direito ficou desbalanceado, fiz uma rotação a direita simples para deixar o 50 como pai novamente do 40 e do 70. É adicionado o 37 que entra como filho a esquerda do 40 e o 38 que fica como filho
     a direita do 37 causando um desbalanceamento no nó 40. É resolvido com uma rotação dupla a direita deixando o 38 como pai do 37 e do 40. O 10 é adicionado e deixa desbalanceado, uso uma LL para deixar
     o 20 como pai do 30 e do 10. O 32 entra como filho a direita do 30 e o 45 como filho a direita do 40. É feita uma LR para corrigir o 45 como pai do 38 e do 50. O resto dos numeros são adicionados de uma
     forma que não causa desbalanceamento.

    Ordem 2 = {100, 80, 60, 40, 20, 70, 30, 50, 35, 45, 55, 75, 65, 73, 77}.
    O 100 entra primeiro como raiz, o 80 como filho dele a esquerda e o 60 como filho do 80, tendo que fazer uma LL para equilibrar deixando o 80 como pai de ambos, o 40 entra como filho do 60, e o 20 como 
    filho do 40, tendo que fazer uma LL para equilibrar. O 70 entra como filho a esquerda do 60, tendo q fazer uma RR e uma LR para deixar ele como a raiz de tudo. O 30 entra como filho a direita do 20 e o 50 
    como filho a esquerda do 60, o 35 entra como filho a direita do 30 e é necessario fazer um RR para ajustar. O 45 entra como filho a esquerda do 50, fazendo um LL é resolvido e é adicionado o 55, o que é necessário
    fazer um RL e depois um LR para deixar o 60 como raiz de todos. Depois um RR para ajeitar o lado direito da raiz. É adicionado o 75 como filho do 70 a direita e o 65 como filho do 70 a esquerda. O 73 entra como 
    filho a esquerda do 75 e é necessario fazer um RL para corrigir deixando o 75 como pai do 80 e do 70. O 77 já vai diretamente para um lugar balanceado.  

    Ordem 3 = {41,38, 31, 12, 19, 8, 27, 49}.
    Primeiro a raiz é 41, logo depois o 38 é colocado como seu filho a esquerda e o 31 como filho do 38, causando um desbalanceamento ajustado com a rotação direita
    simples, deixando o 38 como raiz pai do 31 e do 41, o 12 entra como filho do 31, e o 19 como filho a direita do 12, deixando desbanlaceada, para arrumar é so fazer
    uma rotação direita simples denovo deixando o 19 como pai do 12 e do 31, o 8 entra como filho do 12, ficando desbalanceada de novo. Para arrumar é necessario uma 
    rotação dupla a direita, deixando o 31 como raiz da arvore, porém após essa rotação o filho a esquerda da raiz (19) fica desbalanceado, ajustando com uma direita simples
    o 27 entra como filho do 19, ainda balanceada. O 49 entra como filho a direita do 41, e é ajustado com a rotação esquerda simples

    Ordem 4 = {10, 21, 15, 17, 16, 19, 20}.
    Primeiro é inserido o 10, seu filho a direita é o 21 e o filho a esquerda do 21 é o 15, já está desbalanceado, é preciso fazer uma rotação dupla a esquerda,
    deixando o 15 como raiz e seu filho a esquerda o 10 e 21 a direita. O 17 entra como filho a esquerda do 21, e o 16 como filho a esquerda, o que desbalancea 
    tendo que fazer uma rotação direita simples transformando o 17 como pai do 21 e 16. Próximo numero a ser adicionado é o 19, fica como filho a esquerda do 21
    o que desbalanceia a raiz e é necessário fazer uma rotação dupla a esquerda, o que transformaria a raiz de toda a arvore em 16, porém o 17 ficaria desbalanceado 
    e tendo que aplicar uma rotação dupla a esquerda também. Essa é a ultima rotação e é so inserir o 20 como filho a esquerda do 21 e fica perfeitamente equilibrado.
*/

/*
Exercicio 3:
    Um contra argumento valido seria os elementos {1,2,3,4}, se inseridos nessa forma a arvore construida seria  2 
                                                                                                              /      \
                                                                                                             1        3
                                                                                                                        \
                                                                                                                         4
    Já se fosse {4,3,2,1} seria:                                                                                 3 
                                                                                                              /      \
                                                                                                             2        4
                                                                                                            /   
                                                                                                           1
    Logo sim a ordem em que os conjuntos forem inseridos é importante na construção da árvore
*/



/*
Exercicio 4:
    A construção dessa função se baseia de acordo com a função já criada a rotação LL, apenas alterando os ponteiros onde era direita para a esquerda 
    e onde era esquerda para direita. Mas o passo a passo é declarar um no, B ser igual ao filho a direita da arvore, o filho a direita ser o filho do B a esquerda
    e o filho a esquerda de B ser a raiz. Aqui já foi feito todo o processo de rotação, ai é ajustada a altura da raiz e a do B e declara o novo ponteiro de raiz para B
    Foi feita a troca e ajustes de alturas para o balanceamento correto
*/
void RotacaoRR(ArvAVL *raiz){//RR
    printf("RotacaoRR\n");
    struct NO *B;
    B = (*raiz)->dir;
    (*raiz)->dir = B->esq;
    B->esq = *raiz;
    (*raiz)->altura = maior(altura_NO((*raiz)->dir),altura_NO((*raiz)->esq)) + 1;
    B->altura = maior(altura_NO(B->dir),(*raiz)->altura) + 1;
    *raiz = B;
}

/*
Exercicio 5: 
    Primeiramente a função recebe uma arvore raiz e um valor a ser inserido, a função cria um int auxiliar, faz a verificação se a arvore está vazia, se estiver
    ele ja aloca e insere o valor e passa o ponteiro da raiz para ele. Se nao for vazia ele cria um nó que aponta para a raiz e entra num if para ver o valor é menor
    que o valor do nó atual, se for ele chama recursivamente a função para a esquerda, aplica o mesmo para caso não for menor. Se não for nenhum dos casos ele é igual e 
    é retornado 0. Ele percorre a árvore inteira até achar o lugar correto onde a arvore for nula e insere o valor no lugar correto. E vai voltando recursivamente aonde 
    foi parado. É nesse momento quando se entra no if de fator de balanceamento for maior ou igual a 2, se for ele faz a rotação necessária para ajustar e tornar o balanceamento
    correto, e vai voltando as chamadas recurisvas e arrumando as posições para a arvore ficar corretamente balanceada e no final ele sai do if else e é ajustado a altura do atual.

    As funções auxiliares dentro dessa de inserir foram: Fator Balancemaento, Rotação LL/LR, Rotação RR/RL, maior e AlturaNo, vou explicar cada uma delas:
    Fator Balanceamento: apenas retorna o calculo de (altura subarvore esquerda - altura subarvore direita). 
    Rotações: As funções de rotações são utilizadas para fazer os ajustes necessários dentro da inserção e não deixar de ser uma arvore AVL.
    Maior: Ele apenas retorna qual é o maior int dentro de 2 passados.
    AlturaNo: Apenas retorna a altura da arvore passada.

*/

/*
Exercicio 6: 
    Essa função de remoção tem a mesma base recursiva da de inserir mudando poucas coisas, é passado uma raiz e um valor a ser removido, é verificado se a raiz é nula ou não, se for
    já retorna 0. É declarado um int auxiliar, ai é o mesmo processo que nem da função de inserir, é o caminhamento dentro da arvore para achar o no correto, verificar se o valor é maior 
    ou menor que o no e é chamado uma função recursiva para algum dos lados. As chamadas recursivas param a partir do momento que o valor do no for igual ao valor passado, ai é entrado em outro
    if e else, para verificar quantos filhos esse no a ser removido tem, é feito as adaptações para cada caso se tiver 1 filho se tiver os dois ou se for folha. É liberado o nó e ajustado a sua altura, 
    após isso as chamadas recursivas vão voltando e é feito todo o processo de ajustes para a arvore ficar balanceada.

    As funções auxiliares dentro dessa função de de remover foram: FatorBalanceamento, AlturaNo, Rotações e maior, que já foram todas explicadas no exercicio acima.
    Apenas o procuraMenor uma função que é passada uma raiz e ele percorre totalmente a esquerda e retorna o no de menor valor encontrado.

*/

/*
Exercicio 7:
    Essa função retorna 1 se a raiz passada for uma arvore AVL e retorna 0 caso contrario, de uma forma recursiva simples ela verifica se a arvore é vazia ou nula o caso base onde a recursão para
    se for algum dos dois a arvore é AVL, se nao for o caso ele declara um int pegando o fator Balanceamento do no atual e verifica se ele é maior que 1 ou menor que -1, se for ele ja retorna 0, e 
    o passo recursivo por ultimo que é retornar a propria função passado os nos da esquerda e da direita. Após todo o processo de busca acabar ele diz se é ou não AVL.
*/
int verificaArvoreAVL(ArvAVL *raiz){
    if(raiz == NULL || *raiz == NULL)
        return 1; 
    
    int fb = fatorBalanceamento_NO(*raiz);
    if(fb >= 2) return 0; 
    
    return verificaArvoreAVL(&((*raiz)->esq)) && verificaArvoreAVL(&((*raiz)->dir));
}
/*
Exercicio 8:
    Essa função recebe uma arvore binaria como parametro e retorna essa mesma arvore balanceada, ela utiliza 2 funções auxiliares, uma para contar os nos da arvore
    passada como parametro e outra para preencher um array do tamanho da arvore passada. 
    Primeiramente a função principal verifica se a arvore existe ou se ela é vazia ou se ela já é uma arvore AVL, se for retorna ela mesma. É declarado um inteiro 
    com o tamanho de nos dentro da arvore e é alocado um vetor de inteiros com a quantidade de nós, esse vetor recebe todos os os valores da arvore de forma ordenada
    com a função auxiliar, depois é criada uma arvore AVL e um for para ir preenchendo a arvore com a função de inserir na arvore avl, depois é liberada a arvore passada
    como parametro e retornada a arvore AVL criada.
*/

int conta_nos(struct NO* no) {
    if(no == NULL)
        return 0;
    return 1 + conta_nos(no->esq) + conta_nos(no->dir);
}

void preenche_array(struct NO* no, int *elementos, int *indice) {
    if(no == NULL)
        return;
    preenche_array(no->esq, elementos, indice);
    elementos[(*indice)++] = no->info;
    preenche_array(no->dir, elementos, indice);
}
    

ArvAVL *transformaArvore(ArvAVL* raiz){
    if(raiz == NULL || *raiz == NULL || verificaArvoreAVL(raiz))
        return raiz; 

    int quantidade = conta_nos(*raiz);

    int *elementos = (int*)malloc(quantidade * sizeof(int));
    if(elementos == NULL)
        return raiz;

    int indice = 0;
    preenche_array(*raiz, elementos, &indice);

    ArvAVL* nova_arvore = cria_ArvAVL();
    if(nova_arvore == NULL) {
        free(elementos);
        return raiz; 
    }
    
    for(int i = 0; i < quantidade; i++) {
        insere_ArvAVL(nova_arvore, elementos[i]);
    }
    
    
    free(elementos);
    libera_ArvAVL(raiz);
    
    return nova_arvore;
}
