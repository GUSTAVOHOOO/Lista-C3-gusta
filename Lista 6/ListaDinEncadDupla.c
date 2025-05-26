#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h" //inclui os Prot�tipos

//Defini��o do tipo lista
struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->ant = NULL;
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if(*li != NULL)//lista n�o vazia: apontar para o anterior!
        (*li)->ant = no;
    *li = no;
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    while(no->prox != NULL)
        no = no->prox;

    if(no->ant == NULL)//remover o primeiro e �nico
        *li = no->prox;
    else
        no->ant->prox = NULL;

    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
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
    Elem* no = *li;
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

int remover_mat(Lista* li, int n){
    if(li == NULL || *(li) ==  NULL) return 0; //Segurança
    
    Elem* no = *li;   
    
    while(no != NULL && no->dados.matricula != n){  
        no = no->prox;
    }

    //Caso não esteja dentro da lista
    if(no == NULL){
        printf("Matricula não encontrada");
        return 0;
    }
    //Caso seja o primeiro
    if(no == *li){
        *(li) = no->prox;
        free(no);
        (*li)->ant = NULL;
        return 1;
    } 
    
    //Caso seja o ultimo
    if(no->prox == NULL){
        no->ant->prox = NULL;
        free(no);
        return 1;
    }

    //Caso for no meio
    no->prox->ant = no->ant;
    no->ant->prox = no->prox;
    free(no);
    
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL) return 0;

    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;

    no->dados = al;

    if((*li) == NULL){ 
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    } else {
        Elem *atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            atual = atual->prox;
        }
        if(atual == *li){ //Caso início
            no->prox = *li;
            no->ant = NULL;
            (*li)->ant = no;
            *li = no;
        } else if(atual == NULL){ //Caso seja no final
            Elem *ultimo = *li;
            while(ultimo->prox != NULL)
                ultimo = ultimo->prox;
            ultimo->prox = no;
            no->ant = ultimo;
            no->prox = NULL;
        } else { //Caso seja no meio
            no->prox = atual;
            no->ant = atual->ant;
            atual->ant->prox = no;
            atual->ant = no;
        }
        return 1;
    }
}

int conta_lista_nota(Lista* li, float n1) {
    if (li == NULL || *li == NULL) return 0;

    int contador = 0;

    while (*li != NULL) {
        if ((*li)->dados.n1 == n1) {
            contador++;
        }
        if ((*li)->prox == NULL) break; //Para conseguir ter acesso até a ultima célula sem virar NULL
        *li = (*li)->prox;
    }

    
    while (*li != NULL && (*li)->ant != NULL) {
        *li = (*li)->ant;
    }

    return contador;
}



int insere_lista_circ(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;

    no->dados = al;

    if(*li == NULL){ // Lista vazia
        no->prox = no;
        no->ant = no;
        *li = no;
    } else {
        Elem* ultimo = (*li)->ant;
        no->prox = *li;
        no->ant = ultimo;
        ultimo->prox = no;
        (*li)->ant = no;
        *li = no; // Se quiser inserir sempre no início
    }
    return 1;
}

int remove_lista_circ(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return 1;
}


