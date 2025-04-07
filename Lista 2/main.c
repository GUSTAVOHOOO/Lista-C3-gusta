#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*  Exercicio 1 - Sendo p um ponteiro, qual a diferença entre:
        • p++; Aponta para o próximo slot na memória.
        • (*p)++; Incrementa o valor do que o ponteiro está apontando.
        • *(p++); Aponta para o próximo slot na memória.
        • O que quer dizer *(p+10); Caminha 10 espaços na memória.
*/

/*  Exercicio 2 -    
        int y, *p, x; Declaração das variáveis.
        y = 0; Atribuição de valor para o int.
        p = &y; Ponteiro aponta para o endereço de y.
        x = *p; X recebe o valor de y.
        x = 4; X recebe o valor 4.
        (*p)++; Incrementa o valor de onde p aponta.
        x--; Decrementa x.
        (*p) += x; Valor de que P está apontando += o valor de x.
        printf ("y = %d\n", y); Printa o valor de y,
        return(0);
*/

/*  Exercicio 3 - Corrigir o código para que ele exiba 10.
        int x, *p;
        int **q;
        p = &x;
        q = &p;
        x = 10;
        printf("\n %d\n", **q); Unica alteração feita foi que para imprimir a variável tem que ser '**'
*/

void ex4();
int ex5(int *v1, int *v2, int n);
void ex6();
struct produtos* cadastroProdutos(int n);
void printarProdutos(struct produtos *produtos, int n);
void consultarPreco(struct produtos *produtos, int n);
void ex7();
void ex8();
void ex9();


int main(){

    printf("\nExercicio 4 - Criar e alocar dinamicamente um vetor de inteiros.\n");
    ex4();
    printf("\n");
    
    /*-----------------------------------------------------------------------------------------------------------------*/

    printf("\nExercicio 5 - Inverter um vetor e passar o maior numero dele.\n");
    int v1[10] = {1,2,3,4,5,6,7,8,9,10}, v2[10];
    int resultado = ex5(v1, v2, 10);
    printf("Vetor invertido: \n");
    for(int i = 0; i < 10; i++){
        printf("%d ", v2[i]);
    }
    printf("\n");
    printf("Maior numero presente no vetor: %d ", resultado);
    printf("\n");

    /*-----------------------------------------------------------------------------------------------------------------*/

    printf("\nExercicio 6 - Inverter um vetor de char.\n");
    ex6();
    printf("\n");

    /*-----------------------------------------------------------------------------------------------------------------*/

    printf("\nExercicio 7 - Criar e cadastrar produtos dentro de um struct, imprimir e consultar produtos pelo codigo.\n");
    ex7();
    printf("\n");

    /*-----------------------------------------------------------------------------------------------------------------*/

    printf("\nExercicio 8 - Alocar dinamicamente um vetor, preencher, imprimir e liberar a memoria.\n");
    ex8();
    printf("\n");

    /*-----------------------------------------------------------------------------------------------------------------*/

    printf("\nExercicio 9 - Alocar dinamicamente uma matriz, preencher, e liberar a memoria.\n");
    ex9();
    printf("\n");
    return(0);
}


void ex4(){
    printf("Qual o tamanho desejado? ");
    int n;
    scanf(" %d", &n);
    int *vetor = malloc(n * sizeof(int));
    if(vetor == NULL){
        printf("Erro");
    }
    
    free(vetor);
}
/*Aqui ele recebe um numero n, aloca dinamicamente o vetor, faz a verificacao se foi possivel alocar e após isso logo libera pois o exercicio so pede isso.*/


int ex5(int *v1, int *v2, int n){
    int maior = v1[0];
    for(int i = 0; i< n; i++){
        v2[i] = v1[n - i - 1]; 
        if(v1[i] > maior)
            maior = v1[i];
    }
    return maior;
}
/*Aqui ele recebe 3 parametros, os dois vetores, um preenchido e outro vazio, e o ultimo que é o tamanho dos dois vetores, considera que o primeiro valor do vetor é o maior, 
abre um for percorrendo de 0 até o tamanho do vetor, faz a inversão dos vetores, caso o valor que está sendo trocado seja maior que a variavel maior ele vira o maior, e apos 
isso a função retorna o maior numero presente no vetor.*/

void ex6() {
    char s[10] = "abcde"; 
    char *ptr;

    ptr = s + strlen(s) - 1;

    while (ptr >= s) {
        printf("%c", *ptr);
        ptr--;
    }
}
/*Aqui é passado a string e o ponteiro de char, faz o ponteiro apontar para a ultima posição da string, entra dentro do while e enquanto o ponteiro nao for maior ou igual a S
ele vai printando e o ponteiro sendo decrementado*/

struct produtos{
    char nome[50];
    int codigo;
    float preco;
};
/*Declaracao do struct com 3 variaveis, nome, codigo e preço*/

struct produtos* cadastroProdutos(int n){
    struct produtos *produtos = malloc(n * sizeof(struct produtos));
    if (produtos == NULL) {
        return NULL;
    }

    for(int i = 0; i < n; i++){
        printf("Produto numero: %d\n", i + 1);
        printf("Codigo do produto: ");
        scanf("%d", &produtos[i].codigo);
        getchar(); 
        
        printf("Nome do produto: ");
        fgets(produtos[i].nome, 50, stdin);
        produtos[i].nome[strcspn(produtos[i].nome, "\n")] = '\0';
        
        printf("Preco do produto: ");
        scanf("%f", &produtos[i].preco);
    }

    return produtos;
}
/*Aqui a função aloca dinamicamente um vetor do struct, e preenche ele utilizando um for*/


void printarProdutos(struct produtos *produtos, int n){
    for(int i = 0; i < n; i++){
        printf("Produto %d \n", i + 1);
        printf("Codigo do produto: %d \n", produtos[i].codigo);
        printf("Nome do produto: %s \n", produtos[i].nome);
    }
}
/*Aqui ele printa o codigo e o nome de todos os produtos presente no vetor*/

void consultarPreco(struct produtos *produtos, int n){
    int x, codigo;
    do{
    printf("Qual codigo deseja consultar o preco?\n");
    scanf("%d", &codigo);

    int encontrado = 0;
    for(int i = 0; i < n; i++){
        if(codigo == produtos[i].codigo){
            printf("%.2f \n", produtos[i].preco);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado){
        printf("Nao tem produto com esse codigo\n");
    }
    printf("Digite 0 se quiser parar, 1 se quiser verificar outro produto: ");
    scanf("%d", &x);
    }while(x != 0);
}
/*Aqui ele recebe um codigo e procura se tem algum produto com esse codigo, se tem ele printa o preço do produto, se nao tiver ele printa que não tem
e após isso o programa pergunta se quer procurar mais produtos ou não utilizando o while*/

void ex7(){
    int n;
    printf("Quantos elementos deseja cadastrar? ");
    scanf("%d", &n);

    struct produtos *produtos = cadastroProdutos(n);
    if(produtos != NULL){
        printarProdutos(produtos, n);
        consultarPreco(produtos, n);
        free(produtos);
    }
}
/*Aqui a função recebe quantos elementos dentro do vetor o usuario quer, recebe a função de cadastro passando o struct, apos o cadastro é feito a verificao se a alocação deu certo
se deu, ele printa e consulta e apos isso libera, uma junção das 3 funções acima para nao poluir o main*/

void ex8(){
    int n, *vetor, i;
    printf("Qual o tamanho do vetor: ");
    scanf("%d", &n);

    vetor = malloc(n * sizeof(int));
    if(vetor == NULL){
        printf("Erro na alocacao\n");
    }

    for(i = 0; i < n; i++){
        printf("Posição %d do vetor: \n", i);
        scanf("%d", &vetor[i]);
    }

    for(i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
   
    free(vetor);

}
/*Recebe o tamanho do vetor, aloca dinamicamente de acordo com o tamanho, le e recebe para todas as posições do vetor, imprime na tela o vetor inteiro e apos isso libera 
a alocacao dinamica*/


void ex9(){
    int m, n, **matriz;
    printf("Quantas linhas vai ter a sua matriz? \n");
    scanf("%d", &m);

    printf("Quantas colunas vai ter a sua matriz? \n");
    scanf("%d", &n);

    matriz =  malloc(m * sizeof(int *));
    if(matriz == NULL){
        printf("Erro na alocacao\n");
    }
    
    for(int i = 0; i < m; i++){
        matriz[i] = malloc(n * sizeof(int));
        if(matriz[i] == NULL){
            printf("Erro na alocacao\n");
        }      
    }

    for(int i = 0; i<m; i++){
        for(int j = 0; j < n; j++){
            printf("Posicao [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    for (int i = 0; i < m; i++) {
        free(matriz[i]); 
    }
    free(matriz); 
}
/*Recebe a quantidade de linhas e colunas para a matriz, aloca as linhas, e depois vai alocando coluna por coluna, e le posição por posição da matriz
e depois disso libera a matriz toda. */