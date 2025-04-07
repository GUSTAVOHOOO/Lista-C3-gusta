#include <stdio.h>
#include <stdlib.h>

int ex1(int x);
int ex2(int *vet, int tamanho);
int ex3(int x);
int ex4(int n, int k);
int *ex5(int *vet, int tamanho, int i);
int ex6(int x, int y);
int ex7(int x, int n);
int ex8(int n, int k);
int ex9(int x, int i);
int ex10(int x);
int ex11(int x);
int ex12(int x);




int main(){
   
    printf("Exercicio 1 - Faca uma funcao recursiva que permita inverter um numero inteiro N.\n");
    
    int x = 543;
    printf("Numero normal: %d\n", x);
    printf("Numero invertido: ");
    ex1(x);
    printf("\n\n");

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 2 - Faca uma funcao recursiva que permita somar os elementos de um vetor de inteiros.\n");
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = 5;
    printf("Soma dos elementos do vetor: %d\n\n", ex2(vetor, tamanho));

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 3 - Crie uma funcao recursiva que receba um numero inteiro positivo N e calcule o somatorio dos numeros de 1 a N.\n");
    x = 5;
    printf("Somatorio de %d ate 1: %d\n\n", x, ex3(x));

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 4 - Calcular potencia (n^k).\n");
    int n = 2, k = 3;
    printf("%d elevado a %d: %d\n\n", n, k, ex4(n, k));

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 5 - Inverter um vetor.\n");
    int vetor2[] = {1, 2, 3, 4, 5};
    tamanho = 5;
    ex5(vetor2, tamanho, 0);
    printf("Vetor invertido: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor2[i]);
    }
    printf("\n\n");

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 6 - Calcular o MDC de dois numeros.\n");
    int a = 56, b = 98;
    printf("MDC de %d e %d: %d\n\n", a, b, ex6(a, b));

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 7 - Contar ocorrencias de um digito em um numero.\n");
    int digito = 3, numero = 123333;
    printf("O digito %d aparece %d vezes no numero %d\n\n", digito, ex7(digito, numero), numero);

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 8 - Multiplicacao usando soma.\n");
    n = 5, k = 3;
    printf("%d vezes %d: %d\n\n", n, k, ex8(n, k));

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 9 - Imprimir numeros pares de 0 ate X.\n");
    x = 24;
    printf("Numeros pares de 0 ate %d: ", x);
    ex9(x, 0);
    printf("\n\n");

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 10 - Contar regressivamente de X ate 0.\n");
    x = 15;
    printf("Contagem regressiva de %d: ", x);
    ex10(x);
    printf("\n\n");

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 11 - Imprimir numeros pares de X ate 0.\n");
    x = 16;
    printf("Numeros pares de %d ate 0: ", x);
    ex11(x);
    printf("\n\n");

    /* ------------------------------------------------------------------------------------------- */

    printf("Exercicio 12 - Calcular fatorial de numeros impares.\n");
    n = 7;
    printf("Fatorial de %d: %d\n\n", n, ex12(n));

    return 0;
}   

int ex1(int x){
    if(x == 0) return 0;
    printf("%d", x % 10);
    return ex1(x / 10);
}
/*caso x for 0 retorna 0, printa o resto da divisão de x por 10, e chama a função de novo com x divido por 10*/

int ex2(int *vet, int tamanho){
    if(tamanho == 0) return 0;
    return vet[tamanho - 1] + ex2(vet, tamanho - 1);
}
/*Eu usei duas variaveis como parametro para poder acessar o vetor e outra para poder ter o tamanho do vetor para poder criar o caso base que seria se o tamanho do
vetor fosse 0, apos isso ele soma o vet[tamanho -  1] que é o ultimo indice e soma a chamada da recursão, onde so vai parar quando o tamanho igualar a 0.*/

int ex3(int x){
    if(x == 1) return 1;
    return x + ex3(x-1);
}
/*Caso x for 1 ele retorna 1 pois isso retorna o somatorio de x até 1, caso contrario ele retorna a soma de X com a chamada da função com x - 1, assim ele vai fazendo a soma
até que X chegue em 1*/


int ex4(int n, int k){
    if(k == 0) return 1;
    return n * ex4(n, k -1);
}
/*Caso base é se k for 0 pois todo numero elevado a 0 é 1, ele retorna n * a chamada da função com alteração de k-1, assim toda vez até k se tornar 0.*/


int *ex5(int *vet, int tamanho, int i) {
    if (i >= tamanho / 2) return vet; 
    int temp = vet[i]; 
    vet[i] = vet[tamanho - 1 - i]; 
    vet[tamanho - 1 - i] = temp; 
    return ex5(vet, tamanho, i + 1); 
}
/*Aqui foram necessárias 3 variaveis, uma para o vetor e outras duas para o tamanho, caso i for maior ou igual que metade do tamanho ele retorna o proprio vetor, salva 
a variavel temp com o vetor no indice 0, salva vet[0] igual (tamanho total - 1 - i), é assim pois o tamanho total tem que ser menos 1 pois os indices sao a partir de 0,
e é diminuido - i para ir fazendo a inversão, após isso o vet[tamanho - 1 - i] salva a temp que tinha salvado o indice 0, ai retorna a chamada da função somando i + 1 até 
que i seja pelo menos metade do tamanho total*/

int ex6(int x, int y){
    if(y == 0) return x;
    return ex6(y, x%y);
}
//Aqui o caso base é caso y == 0 retorna x, caso contrario o MDC é y com o resto da divisao de x por y, sendo que uma hora y vai chegar em 0.



int ex7(int x, int n){
    if (n == 0) return x == 0 ? 1 : 0; 
    return (n % 10 == x) + ex7(x, n / 10); 
}
/*caso n for 0, ele retorna um operador ternário dizendo que se x for 0 também ele retorna 1, caso contrario retorna, é feito a soma de resto de n por 10 iguala a x para saber 
se existe ocorrencia, após isso é chamada a função com n / 10 para ir diminuindo numero por numero, até que n seja 0 e feita a soma de quantas vezes x apareceu em n*/

int ex8(int n, int k){
    if(k == 0) return 0;
    return n + ex8(n, k-1);
}
/*Aqui é uma função para retornar a multiplicação de um numero utilizando a soma, caso base é se k for 0, e o return n + a chamada da função com k - 1, até que k se torne 0*/


int ex9(int x, int i){
    if(x % 2 != 0 || x == 0) return -1;
    if(i > x) return x;
    printf("%d ",i);
    return ex9(x, i + 2);
}
/*caso base ele retorna a verificação se é par ou se o x é 0, caso i for maior que x ele retorna o proprio x, printa o i, e chama a função retornando i + 2, assim
continua indo de 0 até x de dois em dois*/


int ex10(int x){
    if(x < 0) return 0;
    printf("%d ", x);
    return ex10(x - 1);
}
/*se x for 0 ele retorna 0, printa x e vai decremetando x até chegar em 0*/


int ex11(int x){
    if(x < 0 || x % 2 != 0) return 0;
    printf("%d ", x);
    return ex11(x - 2);
}
/*se x for menor que 0 ou nao for par retorna 0, printa o x e decrementa 2*/

int ex12(int n){
    if(n %2 == 0) return - 1;
    if(n == 1) return 1;
    return n * ex12(n-2);
}
/*se n for par ele retorna - 1, se n for 1 ele retorna 1 e faz a multiplicaçãod e n pela chamada da função decrementando de 2 em dois*/