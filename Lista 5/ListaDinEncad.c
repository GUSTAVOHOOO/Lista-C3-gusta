#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncad.h" //inclui os Prot�tipos

//Defini��o do tipo lista
struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elemento;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elemento* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento *no;
    no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere in�cio
        *li = no;
    }else{
        Elemento *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento* no;
    no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento *no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elemento *ant, *atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere in�cio
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elemento *ant, *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//n�o encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elemento *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elemento *ant, *no = *li;
    while(no->prox != NULL){
        ant = no;
        no = no->prox;
    }

    if(no == (*li))//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elemento* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elemento* no = *li;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");

        no = no->prox;
    }
}

int consulta_matricula(Lista* li, int num){
    if(li == NULL) return 0;
    
    Elemento* no = *li;
    
    while(no != NULL && no->dados.matricula != num)
        no = no->prox;

    if(no == NULL){
        printf("Aluno não encontrado\n");
        return 0;
    }else{
        printf("Aluno encontrado: %s \n", no->dados.nome);
        printf("Notas %f, %f, %f\n", no->dados.n1, no->dados.n2, no->dados.n3);
    }

    return 1;
}

int consulta_posicao(Lista* li, int num){
    if(li == NULL) return 0; 

    int posicao = 1;
    Elemento* no = *li;

    while(no != NULL && posicao != num){
        no = no->prox;
        posicao++;
    }

    if(no == NULL){
        printf("Posicao fora dos alcances da lista\n");
        return 0;
    }else{
        printf("Aluno encontrado: %s \n", no->dados.nome);
        printf("Matricula: %d\n", no->dados.matricula);
        printf("Notas %f, %f, %f\n", no->dados.n1, no->dados.n2, no->dados.n3);
        printf("Posicao: %d", posicao);
    }

    return 1;
}

int remove_rec(Lista* li, int n){
    if(li == NULL) return 0;
    
    if((*li)->dados.matricula == n) {
        remove_lista_inicio(li);
        return 1;
    }   

    return remove_rec(&(*li)->prox, n);
}

int listas_iguais(Lista* li, Lista* l2){
    if((li == NULL || *li == NULL) && (l2 == NULL || *l2 == NULL)) return 1;

    if(li == NULL || *li == NULL || l2 == NULL || *l2 == NULL) return 0;
    
    if((*li)->dados.matricula != (*l2)->dados.matricula) return 0;
    if(strcmp((*li)->dados.nome, (*l2)->dados.nome) != 0) return 0;
    if((*li)->dados.n1 != (*l2)->dados.n1 || (*li)->dados.n2 != (*l2)->dados.n2 || (*li)->dados.n3 != (*l2)->dados.n3 ) return 0;

    return listas_iguais(&(*li)->prox, &(*l2)->prox);
}

int insere_posicao(Lista* li, int num, struct aluno al){
    if(li == NULL || num <= 0) return 0;
    
    Elemento* no = (Elemento*) malloc(sizeof(Elemento));
    no->dados = al;

    if(num == 1){ //Caso seja primeiro da lista
        no->prox = *li;
        *li = no;
        return 1;
    }

    int posicao = 1;
    Elemento* ptr = *li;
    Elemento* ptrAnt;

    while(ptr != NULL && num != posicao){
        ptrAnt = ptr;
        ptr = ptr->prox;
        posicao++;
    }

    if(ptr == NULL){  
        ptrAnt->prox = no;
        no->prox = NULL;
        return 1;
    }else{
        ptrAnt->prox = no;
        no->prox = ptr;
    }

    return 1;

}

Lista* cria_lista_ordem(struct aluno *al, int n){
    Lista* li = cria_lista();

    for(int i = 0; i < n; i++){
        insere_lista_final(li, al[i]);
    }
        
    return li;
}


int remove_n(Lista* li, int n){
    if(li == NULL) return 0;

    int tamanho = tamanho_lista(li);
    
    for(int i = 0; i < tamanho; i++)
        remove_lista(li, n);

    return 1;
}


int concatenar_listas(Lista* l1, Lista* l2){
    if(l1 == NULL || l2 == NULL) return 0;

    Elemento* no = *l1;

    while(no->prox != NULL)
        no = no->prox;

    no->prox = (*l2);
    
    return 1;
}

int remover_repetidos(Lista* li){
    if(li == NULL || *li == NULL) return 0;

    Elemento *comp = *li;
    while(comp != NULL){
        Elemento *anterior = comp;
        Elemento *no = comp->prox;
        while(no != NULL){
            if(no->dados.matricula == comp->dados.matricula){
                anterior->prox = no->prox;
                free(no);
                no = anterior->prox;
            } else {
                anterior = no;
                no = no->prox;
            }
        }
        comp = comp->prox;
    }
    return 1;
}

void junta_e_ordena(Lista *l1, Lista *l2) {

    concatenar_listas(l1,l2);
    if (*l1 == NULL) {
        *l1 = *l2;
        *l2 = NULL;
        return;
    }

    Elemento *p1 = *l1;
    Elemento *p2 = *l2;
    Elemento *novo_inicio = NULL;
    Elemento *ultimo = NULL;


    if (p1->dados.matricula < p2->dados.matricula) {
        novo_inicio = p1;
        p1 = p1->prox;
    } else {
        novo_inicio = p2;
        p2 = p2->prox;
    }

    ultimo = novo_inicio;


    while (p1 != NULL && p2 != NULL) {
        if (p1->dados.matricula < p2->dados.matricula) {
            ultimo->prox = p1;
            p1 = p1->prox;
        } else {
            ultimo->prox = p2;
            p2 = p2->prox;
        }
        ultimo = ultimo->prox;
    }


    if (p1 != NULL) {
        ultimo->prox = p1;
    } else {
        ultimo->prox = p2;
    }


    *l1 = novo_inicio;
    *l2 = NULL;

}

int Troca(Lista* li, Elemento* p ){
    if(li == NULL) return 0;
    if(*li == NULL) return 0; 
    
    if(p == NULL) return 0;
    if(p->prox == NULL) return 0;

    if (p == *li) {
        Elemento* y = p->prox;

        p->prox = y->prox;
        y->prox = p;
        *li = y;

    } else {
        Elemento* ant = *li;

        Elemento* x = p;
        Elemento* y = p->prox;
        // percorre a lista até o elemento anterior ao p
        while(ant->prox!=p){
            ant = ant->prox;
        }
        // troca o elemento p com o próximo
        ant->prox = y;
        x->prox = y->prox;
        y->prox =x;

        }
    return 1;
}
