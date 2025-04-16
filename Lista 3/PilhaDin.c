#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PilhaDin.h" 


struct elemento{
    int n;
    struct elemento *prox;
};
typedef struct elemento Elem;


Pilha* cria_Pilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi != NULL)
        *pi = NULL;
    return pi;
}

void libera_Pilha(Pilha* pi){
    if(pi != NULL){
        Elem* no;
        while((*pi) != NULL){
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }
        free(pi);
    }
}


int consulta_topo_Pilha(Pilha* pi, int n){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    n = (*pi)->n;
    return 1;
}

int insere_Pilha(Pilha* pi, int n){
    if(pi == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->n = n;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int remove_Pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    Elem *no = *pi;
    *pi = no->prox;
    free(no);
    return 1;
}

int tamanho_Pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    int cont = 0;
    Elem* no = *pi;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int Pilha_cheia(Pilha* pi){
    return 0;
}

int Pilha_vazia(Pilha* pi){
    if(pi == NULL)
        return 1;
    if(*pi == NULL)
        return 1;
    return 0;
}

void imprime_Pilha(Pilha* pi){
    if(pi == NULL)
        return;
    Elem* no = *pi;
    while(no != NULL){
        printf("Numero: %d\n",no->n);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

/*Ex1*/
int pop2(Pilha *pi){
    if(pi == NULL)
    return 0;
    if((*pi) == NULL)
        return 0;
    if(tamanho_Pilha(pi) < 2)
        return 0;
    for(int i = 0; i < 2; i++){
    Elem *no = *pi;
    *pi = no->prox;
    free(no);
    }
    return 1;
}
/*Aqui eu apenas fiz as verificações da pilha ser nula, e se ela era menor que 2 elementos que iam ser desempilhados, depois disso apenas abri um for de 0 a 2, dentro do for
eu passo o no apontando para a pilha, faço a pilha apontar para o elemento de baixo, e libero o nó, o loop volta e repete o processo mais uma vez, assim desempilhando dois
elementos*/

int push2(Pilha *pi, int n, int x){
    if(pi == NULL){
        return 0;
    }
    Elem *no, *no2;
    no = (Elem*) malloc(sizeof(Elem));
    no2 = (Elem*) malloc(sizeof(Elem));
    if(no == NULL || no2 == NULL){
        return 0;
    }
    no->n = n;
    no->prox = (*pi);
    *pi = no;
    no2->n = x;
    no2->prox = (*pi);
    *pi = no2;
    return 1;
} 
/*Aqui eu fiz a verificação da pilha, criei 2 nós e aloquei ambos dinamicamente, fiz a verificação caso a alocação desse errado, o primeiro passo é o procedimento padrão do
empilhamento, o N dentro de no recebe o n passado pela função, o ponteiro prox aponta para a pilha, e o ponteiro da pilha recebe o no, o segundo passo só repete o que ja foi explicado. */

int ex2(Pilha *pi, int n){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    
    for(int i = 0; i < n; i++){
        Elem *no = *pi;
        *pi = no->prox;
        free(no);
    }
    return 1;
}
/*Aqui contem a mesma logica para o de desempilhar 2 elementos porem com um numero N*/

Pilha *copia(Pilha *pi){
    if(pi == NULL || (*pi) == NULL){
        return NULL;
    }

    int tamanho = tamanho_Pilha(pi);
    int vet[tamanho], i = 0;
    Pilha *pa = cria_Pilha();
    Elem *no = *pi;
   
    while(no != NULL){
        vet[i++]= no->n ;
        no = no->prox;
    }

    for(i = tamanho-1; i>=0; i--){
        insere_Pilha(pa, vet[i]);
    }


    return pa;
}
/*Aqui faço primeiramente a verificação de caso a pilha for nula, ai ja crio todas as variaveis necessarias, tamanho recebe o tamanho da pilha passada como parametro, crio um vetor
com com o tamanho recebido, e passo i = 0, crio uma segunda pilha, e crio um no para passar por cada elemento da pilha, abro um while para inserir cada elemento da pilha no vetor
até ele ficar nulo, e faço um for que vai de (tamanho - 1) até 0 inserindo os elementos do vetor na segunda pilha. */


int ex4(Pilha *pi, int *media, int *maior, int *menor) {
    if (pi == NULL || *pi == NULL) {
        return 0; 
    }

    Elem *no = *pi;
    int soma = 0, cont = 0;

    *maior = no->n;
    *menor = no->n;

    while (no != NULL) {
        soma += no->n;
        if (no->n < *maior) 
            *maior = no->n;
        if (no->n > *menor) 
            *menor = no->n;
        cont++;
        no = no->prox;
    }

    *media = soma / cont;

    return 1; // Sucesso
}
/*Nessa função é feita a verificação da pilha caso ela seja nula, é criado o no e inicializa a soma e o contador como 0, menor e maior recebem ambos N, e dentro do while a lógica
é enquanto o no for diferente de nulo, a soma recebe N, se n for maior que o maior, maior recebe N, se N for menor que o menor, menor recebe N, o contador é incrementado, e passa
para o elemento de baixo, a media é calculada com a soma/cont.*/


int ex5(Pilha *pi, Pilha *pa){
    if(pi == NULL || pa == NULL){
        return 0;
    }
    
    Elem *no1 = *pi;
    Elem *no2 = *pa;

    if(tamanho_Pilha(pi) != tamanho_Pilha(pa)){
        return 0;
    }

    while(no2 != NULL || no1 != NULL){
        if(no2->n != no1->n){
            return 0;
        }
        no2 = no2->prox;
        no1 = no1->prox;
    }
    return 1;
}
/*Primeiras linhas são apenas para verificação de caso as pilhas sejam nulas, crio um no para cada pilha, verifico se as duas tem o mesmo tamanho, dentro do while ele fica
até que uma das pilhas se tornem nulas e caso qualquer elemento dentro não seja igual, a função ja retorna 0, se todos forem iguais ela sai do while e retorna 1*/


PilhaC* cria_PilhaCHAR(){
    PilhaC* pi = (PilhaC*) malloc(sizeof(PilhaC));
    if(pi != NULL)
        *pi = NULL;
    return pi;
}
/*Função que cria uma pilha de CHAR, a função é a mesma que foi passada, apenas que o nome da Pilha muda, tive que criar para resolver o ex6*/


int tamanho_PilhaCHAR(PilhaC* pi){
    if(pi == NULL)
        return 0;
    int cont = 0;
    ElemC* no = *pi;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}
/*Mesmo caso, a função faz a mesma coisa da função de tamanho passada, porém como o nome da pilha não é o mesmo tive que criar outra função.*/

int insere_PilhaCHAR(PilhaC* pi, char c){
    if(pi == NULL)
        return 0;
    ElemC* no;
    no = (ElemC*) malloc(sizeof(ElemC));
    if(no == NULL)
        return 0;
    no->c = c;
    no->prox = (*pi);
    *pi = no;
    return 1;
}
/*Outra função porém essa ainda foi mudada um pouco, o nome da pilha, o parametro recebido, e também dentro do nó, mas faz basicamente o que a função passada para nos
faz*/

char* strInvertida(PilhaC* pi){
    if(pi == NULL) return NULL;
    ElemC* no = *pi;
    int tamanho = tamanho_PilhaCHAR(pi);
    char *str = malloc((tamanho + 1) * sizeof(char));
    
    for(int i = 0; i < tamanho; i++){
        str[i] = no->c;
        no = no->prox;
    }
    str[tamanho] = '\0';
    return str;
}
/*Aqui eu precisava pegar a string ao contrario, percebi que a função de imprimir já fazia isso e a modifiquei, inves de printar passa ela para uma string e retorna, cria um no
que recebe a pilha, recebe o tamanho da pilha, e aloca uma string dinamicamente para tamanho + 1, abri o for de 0 até tamanho e recebi todos os caracteres dentro da string
no final da string coloquei um '\0' e retornei ela*/


void libera_PilhaCHAR(PilhaC* pi){
    if(pi != NULL){
        ElemC* no;
        while((*pi) != NULL){
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }
        free(pi);
    }
}
/*Mesma função apenas trocada para funcionar para a pilha de char criada.*/

void ex6(){
    
    PilhaC *pi = cria_PilhaCHAR();
    char c;

    printf("Digite um caracter desejado, e digite 0 quando quiser parar: ");
    scanf(" %c", &c);

    while(c != '0'){
        insere_PilhaCHAR(pi, c);
        scanf(" %c", &c);
    }

    int tamanho = tamanho_PilhaCHAR(pi);
    char str[tamanho + 1];
    ElemC *no = *pi;

    while(no != NULL){
        str[--tamanho] = no->c; 
        no = no->prox;
    }
    str[tamanho_PilhaCHAR(pi)] = '\0';

    char* resultado = strInvertida(pi);
    
    if(strcmp(resultado, str) == 0){
        printf("Palavras palindromas! \n");
    }else{    
        printf("Palavras nao palindromas! \n");
    }

    printf("%s \n", resultado);
    
    printf("%s \n", str);

    free(resultado);
    libera_PilhaCHAR(pi);
}
/*Aqui ele cria uma pilha, e um char, pede para escrever um caracter e enquanto for diferente de 0 ele nao para de receber caracter e inserir na pilha, recebe o tamanho da pilha 
criada, cria uma string de tamanho + 1, e cria um nó que recebe a pilha, dentro do while ele vai recebendo os caracteres da pilha ao contrario, até que a pilha seja nula, 
coloca um '\0' no final da string, chama a função para receber a string invertida, faz a comparação de ambas, se elas foram iguais elas sao palindromas se não não, printa as duas
lado a lado e libera a pilha*/


int ex7(Pilha *pi, int *n){
    if(pi == NULL || *pi == NULL){
        return 0;
    }

    Elem *no = *pi;
    int par = 0, cont = 0;

    while (no != NULL){
        if(no->n % 2 == 0)
            par++;
        cont++;
        no = no->prox;
    }
    *n = cont - par;
    return par;
}
/*Verificação do caso da pilha ser nula, criado um nó que recebe a pilha, inicializa par e contador com 0, dentro do while ele verifica se n é par, se nao for apenas continua o 
codigo e incrementa o contador, e o no recebe o proximo, fora do while n = cont - par, essa conta é para saber quantos impares tem, o total de numeros menos os pares, e a 
função retorna os pares*/


void menu(){
    int escolha = 0;
    Pilha *pilha = NULL;
    int n = 0;

    while (escolha != 8) {
        printf("\nMenu\n");
        printf("1 - Inicializa pilha.\n");
        printf("2 - Verifica se a pilha e vazia.\n");
        printf("3 - Verifica se a pilha e cheia.\n");
        printf("4 - Empilha o elemento na pilha.\n");
        printf("5 - Desempilha elemento da pilha.\n");
        printf("6 - Le topo de uma pilha.\n");
        printf("7 - Converte um número decimal em binario.\n");
        printf("8 - Sair.\n");

        printf("Digite a sua escolha: ");
        scanf(" %d", &escolha);

        switch (escolha) {
            case 1:
                pilha = cria_Pilha();
                if (pilha != NULL) {
                    printf("Pilha criada com sucesso.\n");
                } else {
                    printf("Erro ao criar a pilha.\n");
                }
                break;

            case 2:
                if (Pilha_vazia(pilha)) {
                    printf("A pilha esta vazia.\n");
                } else {
                    printf("A pilha nao esta vazia.\n");
                }
                break;

            case 3:
                if (Pilha_cheia(pilha)) {
                    printf("A pilha esta cheia.\n");
                } else {
                    printf("A pilha nao este cheia.\n");
                }
                break;

            case 4:
                printf("Qual numero deseja empilhar? ");
                scanf("%d", &n);
                if (insere_Pilha(pilha, n)) {
                    printf("Numero %d empilhado com sucesso.\n", n);
                } else {
                    printf("Nao foi possível empilhar o número.\n");
                }
                break;

            case 5:
                if (remove_Pilha(pilha)) {
                    printf("Elemento desempilhado com sucesso.\n");
                } else {
                    printf("Erro ao desempilhar elemento.\n");
                }
                break;

            case 6:
                if (consulta_topo_Pilha(pilha, n)) {
                    printf("O elemento no topo da pilha e: %d\n", n);
                } else {
                    printf("Erro ao consultar o topo da pilha.\n");
                }
                break;

            case 7:
                printf("Digite um numero decimal: ");
                scanf("%d", &n);
                printf("A conversao para binario ainda nao foi implementada.\n");
                break;

            case 8:
                printf("Saindo...\n");
                break;

            default:
                printf("Opçao invalida. Tente novamente.\n");
                break;
        }
    }

    libera_Pilha(pilha);
}

