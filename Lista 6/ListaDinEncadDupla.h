//Arquivo ListaDinEncadDupla.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct elemento* Lista;

typedef struct fila {
    int info;
    struct fila *prox;
    struct fila *ant;
} Fila;

typedef struct nodesc {
    Fila *ini;
    Fila *fim;
} noDesc;




Lista* cria_lista();
void libera_lista(Lista* li);
int consulta_lista_pos(Lista* li, int pos, struct aluno *al);
int consulta_lista_mat(Lista* li, int mat, struct aluno *al);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
void imprime_lista(Lista* li);

int remover_mat(Lista* li, int n);
/*A função faz a verificação se a lista é nula ou vazia, declara um nó, nó caminha até achar a matricula ou ser nulo, verifica se a matricula encontrada
é a primeira da lista, se for faz o processo para arrumar os ponteiros, verifica se é o ultimo e faz o processo para ajustar os ponteiros, e caso seja 
no meio ele faz os ajustes do ponteiros*/

int insere_lista_ordenada(Lista* li, struct aluno al);
/*Verifica se a lista é vazia, declara um nó, se a lista estiver vazia, faz os processos para colocar o no como primeiro elemento, caso não seja ele entra 
num while para percorrer a lista até a matricula ser maior que a matricula do nó, verifica se é o ultimo da lista, faz os ajustes dos ponteiros, e caso seja
no meio da lista também é feito os ajustes de ponteiros.*/

int conta_lista_nota(Lista* li, float n1);
/*Faz as verificações de segurança, cria um contador iniciado em 0, cria um while para percorrer todo o li, caso o li.mat == n1, ele incrementa o contador
verifica se o li.prox == NULL para que quando for nulo ele nao chegue realmente nulo, e anda o li para o proximo, entra num while para percorrer até o li.ant
ser igual a nulo, que é o primeiro elemento, a 'cabeça' da lista */


int insere_lista_circ(Lista* li, struct aluno al);
/*Verifica se a lista é nula, aloca um novo nó e preenche com os dados do aluno. 
Se a lista estiver vazia, faz o nó apontar para ele mesmo nos campos prox e ant, tornando-o o único elemento circular.
Se a lista não estiver vazia, ajusta os ponteiros do novo nó, do primeiro e do último elemento para manter a circularidade,
inserindo o novo nó sempre no início da lista.*/

int remove_lista_circ(Lista* li);
/*Verifica se a lista é nula ou vazia. Se houver apenas um elemento, libera o nó e faz a lista apontar para NULL.
Se houver mais de um elemento, ajusta os ponteiros do anterior e do próximo ao nó removido para manter a circularidade,
remove o primeiro elemento e atualiza o ponteiro da lista para o novo início.*/

void imprime_lista_circ(Lista* li);
/*Verifica se a lista é nula ou vazia. Se não for, percorre a lista circular a partir do início,
imprimindo os dados de cada nó até retornar ao ponto de partida, garantindo que todos os elementos sejam exibidos uma única vez.*/

int inicializa_noDesc(noDesc **no);
/*Verifica se o ponteiro do nó descritor é nulo, aloca memória para o nó descritor e inicializa os ponteiros ini e fim como NULL,
indicando que a fila está vazia. Retorna 1 em caso de sucesso e 0 em caso de falha na alocação.*/

int enfileirar(noDesc *n, int elem);
/*Verifica se o nó descritor é nulo, aloca um novo nó para o elemento, preenche o campo info e ajusta os ponteiros prox e ant.
Se a fila estiver vazia, faz o novo nó ser o início e o fim. Caso contrário, insere o novo nó no final da fila e atualiza o ponteiro fim do nó descritor.*/

int desenfileirar(noDesc *n, int *elem);
/*Verifica se o nó descritor é nulo ou se a fila está vazia. Se não estiver, remove o nó do início da fila, armazena o valor removido em elem,
ajusta o ponteiro ini do nó descritor para o próximo elemento e libera o nó removido. Se a fila ficar vazia após a remoção, ajusta também o ponteiro fim para NULL.*/

void imprimirFila(noDesc *n);
/*Verifica se o nó descritor é nulo ou se a fila está vazia. Se não estiver, percorre a fila a partir do início, imprimindo o campo info de cada nó até o final da fila.*/