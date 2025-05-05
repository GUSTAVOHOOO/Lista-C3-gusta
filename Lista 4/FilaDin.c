#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h" //inclui os Prot�tipos

Fila* cria_Fila(){
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if(fi != NULL){
        fi->final = NULL;
        fi->inicio = NULL;
        fi->qtd = 0;
    }
    return fi;
}

void libera_Fila(Fila* fi){
    if(fi != NULL){
        Elem* no;
        while(fi->inicio != NULL){
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

int consulta_Fila(Fila* fi, int n){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)//fila vazia
        return 0;
    n = fi->inicio->n;
    return 1;
}

int insere_Fila(Fila* fi, int n){
    if(fi == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->n = n;
    no->prox = NULL;
    if(fi->final == NULL)//fila vazia
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}

int remove_Fila(Fila* fi){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)//fila vazia
        return 0;
    Elem *no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL)//fila ficou vazia
        fi->final = NULL;
    free(no);
    fi->qtd--;
    return 1;
}

int tamanho_Fila(Fila* fi){
    if(fi == NULL)
        return 0;
    return fi->qtd;
}

int Fila_vazia(Fila* fi){
    if(fi == NULL)
        return 1;
    if(fi->inicio == NULL)
        return 1;
    return 0;
}

int Fila_cheia(Fila* fi){
    return 0;
}

void imprime_Fila(Fila* fi){
    if(fi == NULL)
        return;
    Elem* no = fi->inicio;
    while(no != NULL){
        printf("Numero: %d\n",no->n);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

int separa(Fila *f1, Fila *f2, int n){
    if(f1 == NULL) return 0;
   
    Elem *no = f1->inicio;
    
    while(no != NULL){
        if(no->n == n){
            f2->inicio = no->prox;
            f2->final = f1->final;
            no->prox = NULL;
            f1->final = no;
            return 1;
        }
        no = no->prox;
    }

    return 0;
    
}

Pilha* cria_Pilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi != NULL)
        *pi = NULL;
    return pi;
}

FilaPI* cria_FilaPI(){
    FilaPI* fi = (FilaPI*) malloc(sizeof(FilaPI));
    if(fi != NULL){
        fi->final = NULL;
        fi->inicio = NULL;
        fi->qtd = 0;
    }
    return fi;
}

int insere_Pilha(Pilha* pi, int n){
    if(pi == NULL)
        return 0;
    ElemPI* no;
    no = (ElemPI*) malloc(sizeof(ElemPI));
    if(no == NULL)
        return 0;
    no->n = n;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

void imprime_Pilha(Pilha* pi){
    if(pi == NULL)
        return;
    ElemPI* no = *pi;
    while(no != NULL){
        printf("Numero: %d\n",no->n);
        printf("-------------------------------\n");
        no = no->prox;
    }
}


void libera_Pilha(Pilha* pi){
    if(pi != NULL){
        ElemPI* no;
        while((*pi) != NULL){
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }
        free(pi);
    }
}

int insere_FilaPI(FilaPI* fi, Pilha* pi){
    if(fi == NULL)
        return 0;
    ElemFila *no = (ElemFila*) malloc(sizeof(ElemFila));
    if(no == NULL)
        return 0;
    no->pilha = pi;
    no->prox = NULL;
    if(fi->final == NULL)
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}

void imprime_FilaPI(FilaPI* fi){
    if(fi == NULL)
        return;
    ElemFila* no = fi->inicio;
    while(no != NULL){
        imprime_Pilha(no->pilha);
        no = no->prox;
    }
}

void libera_FilaPI(FilaPI* fi){
    if(fi != NULL){
        ElemFila* no;
        while(fi->inicio != NULL){
            libera_Pilha(fi->inicio->pilha);
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }

        free(fi);
    }
}

FilaFI* cria_FilaFI(){
    FilaFI* fi = (FilaFI*) malloc(sizeof(FilaFI));
    if(fi != NULL){
        fi->final = NULL;
        fi->inicio = NULL;
        fi->qtd = 0;
    }
    return fi;
}

int insereFilaFI(FilaFI* fi, Fila* n){
    if(fi == NULL)
        return 0;
    ElemFilaFI *no = (ElemFilaFI*) malloc(sizeof(ElemFilaFI));
    if(no == NULL)
        return 0;
    no->fi = n;
    no->prox = NULL;
    if(fi->final == NULL)
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}

void imprime_FilaFI(FilaFI* fi){
    if(fi == NULL)
        return;
    ElemFilaFI* no = fi->inicio;
    while(no != NULL){
        imprime_Fila(no->fi);
        no = no->prox;
    }
}

void libera_FilaFI(FilaFI* fi){
    if(fi != NULL){
        ElemFilaFI* no;
        while(fi->inicio != NULL){
            libera_Fila(fi->inicio->fi);
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }

        free(fi);
    }
}

PilhaFI* cria_PilhaFI(){
    PilhaFI* pi = (PilhaFI*) malloc(sizeof(PilhaFI));
    if(pi != NULL)
        *pi = NULL;
    return pi;
}

int insere_PilhaFI(PilhaFI* pi, Fila* fi){
    if(pi == NULL)
        return 0;
    ElemPIFI* no;
    no = (ElemPIFI*) malloc(sizeof(ElemPIFI));
    if(no == NULL)
        return 0;
    no->fi = fi;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

void imprime_PilhaFI(PilhaFI* pi){
    if(pi == NULL)
        return;
    ElemPIFI* no = *pi;
    while(no != NULL){
        imprime_Fila(no->fi);
        no = no->prox;
    }
}


void libera_PilhaFI(PilhaFI* pi){
    if(pi != NULL){
        ElemPIFI* no;
        while((*pi) != NULL){
            libera_Fila((*pi)->fi);
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }
        free(pi);
    }
}

int remove_Pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    ElemPI *no = *pi;
    *pi = no->prox;
    free(no);
    return 1;
}

Fila* ex3(Fila* fi){
    Pilha* pi = cria_Pilha();
    int n;

    
    while(fi->inicio != NULL){
        n = fi->inicio->n;
        remove_Fila(fi);
        insere_Pilha(pi,n);
    } 


    while (*pi != NULL) {
        n = (*pi)->n; 
        insere_Fila(fi, n); 
        remove_Pilha(pi);
    }
    
    free(pi); 
    return fi;

}

FilaAE* cria_FilaAE(){
    FilaAE* fi = (FilaAE*) malloc(sizeof(FilaAE));
    if(fi != NULL){
        fi->final = NULL;
        fi->inicio = NULL;
        fi->qtd = 0;
    }
    return fi;
}

int insere_FilaAE(FilaAE* fi, Aviao a){
    if(fi == NULL)
        return 0;
    ElemAero* no = (ElemAero*) malloc(sizeof(ElemAero));
    if(no == NULL)
        return 0;
    no->a = a;
    no->prox = NULL;
    if(fi->final == NULL)//fila vazia
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}

int remove_FilaAE(FilaAE* fi){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)//fila vazia
        return 0;
    ElemAero *no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL)//fila ficou vazia
        fi->final = NULL;
    free(no);
    fi->qtd--;
    return 1;
}

int tamanhoFilaAE(FilaAE* fi){
    if(fi == NULL) return 0;
    return fi->qtd;
}

void listaAero(FilaAE* fi){
    if(fi == NULL) {
        printf("Lista Vazia");
        return;
    }
    int tamanho = tamanhoFilaAE(fi);
    ElemAero *no = fi->inicio;
    for(int i = 0; i < tamanho; i++){
        printf("\nAviao %d \n", i + 1);
        printf("Modelo: %s \n", no->a.modelo);
        printf("Destino: %s \n", no->a.destino);
        printf("Capacidade: %d \n", no->a.capacidade);
        printf("------------------------------------------------");
        no = no->prox;
    }
}

void primeiroAviao(FilaAE* fi){
    if(fi == NULL){
        printf("Aeroporto vazio");
        return;
    }
    printf("Primeiro aviao da fila tem essas caracteristicas:\n");
    printf("Modelo: %s \n", fi->inicio->a.modelo);
    printf("Destino: %s \n", fi->inicio->a.destino);
    printf("Capacidade: %d \n", fi->inicio->a.capacidade);
}

void liberaFilaAE(FilaAE* fi){
    if(fi != NULL){
        ElemAero* no;
        while(fi->inicio != NULL){
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
         }
    free(fi);       
    }
}

void ex7(Fila *fi){
    if(fi == NULL) return;
    
    int vetor[fi->qtd], i = 0;

    Elem* no = fi->inicio;
    while(no != NULL){
        vetor[i] = no->n;
        no = no->prox;
        remove_Fila(fi);
        i++;        
    }
    for(i = i - 1; i >= 0; i--){
        insere_Fila(fi, vetor[i]);
    }
}

void ex8(Fila* fi, Fila* f2, Fila* f3){
    if(fi == NULL || f2 == NULL)return;

    
}