#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h"

int main() {
    // Criando uma fila
    Fila* fi = cria_Fila();

    // Inserindo elementos na fila
    insere_Fila(fi, 10);
    insere_Fila(fi, 20);
    insere_Fila(fi, 30);
    insere_Fila(fi, 40);

    // Chamando a função ex7
    ex7(fi);

    // Exibindo o resultado
    imprime_Fila(fi);

    // Liberando a memória da fila
    libera_Fila(fi);

    return 0;
}


