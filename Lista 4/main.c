#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h"

void menu() {
    printf("1 - Inicializa fila.\n");
    printf("2 - Verifica se a fila é vazia.\n");
    printf("3 - Verifica se a fila é cheia.\n");
    printf("4 - Enfileira o elemento na fila.\n");
    printf("5 - Desenfileira elemento da fila.\n");
    printf("6 - Lê o número no início da fila.\n");
    printf("7 - Testar qual fila possui mais elementos.\n");
    printf("8 - Furar a fila.\n");
    printf("9 - Sair.\n");
}

int main() {
    Fila* fila1 = NULL;
    Fila* fila2 = NULL;
    int opcao, valor, resultado;

    do {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Inicializa fila
                if (fila1 == NULL) fila1 = cria_Fila();
                if (fila2 == NULL) fila2 = cria_Fila();
                printf("Filas inicializadas.\n");
                break;

            case 2: // Verifica se a fila é vazia
                if (Fila_vazia(fila1))
                    printf("Fila 1 está vazia.\n");
                else
                    printf("Fila 1 não está vazia.\n");
                break;

            case 3: // Verifica se a fila é cheia
                if (Fila_cheia(fila1))
                    printf("Fila 1 está cheia.\n");
                else
                    printf("Fila 1 não está cheia.\n");
                break;

            case 4: // Enfileira o elemento na fila
                printf("Digite o valor a ser enfileirado: ");
                scanf("%d", &valor);
                if (insere_Fila(fila1, valor))
                    printf("Valor %d enfileirado com sucesso.\n", valor);
                else
                    printf("Erro ao enfileirar o valor.\n");
                break;

            case 5: // Desenfileira elemento da fila
                if (remove_Fila(fila1))
                    printf("Elemento desenfileirado com sucesso.\n");
                else
                    printf("Erro ao desenfileirar. Fila pode estar vazia.\n");
                break;

            case 6: // Lê o número no início da fila
                if (consulta_Fila(fila1, &valor))
                    printf("Número no início da fila: %d\n", valor);
                else
                    printf("Erro ao consultar. Fila pode estar vazia.\n");
                break;

            case 7: // Testar qual fila possui mais elementos
                if (tamanho_Fila(fila1) > tamanho_Fila(fila2))
                    printf("Fila 1 possui mais elementos.\n");
                else if (tamanho_Fila(fila1) < tamanho_Fila(fila2))
                    printf("Fila 2 possui mais elementos.\n");
                else
                    printf("As filas possuem a mesma quantidade de elementos.\n");
                break;

            case 8: // Furar a fila
                printf("Digite o valor a ser inserido no início da fila: ");
                scanf("%d", &valor);
                if (Furafila(fila1, valor))
                    printf("Valor %d inserido no início da fila com sucesso.\n", valor);
                else
                    printf("Erro ao furar a fila.\n");
                break;

            case 9: // Sair
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 9);

    // Libera as filas antes de sair
    libera_Fila(fila1);
    libera_Fila(fila2);

    return 0;
}


