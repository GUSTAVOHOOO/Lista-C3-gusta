#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h" //inclui os Prot�tipos
#include <float.h>

#define INFINITY FLT_MAX

//Defini��o do tipo Grafo
struct grafo{
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
};

/*
Exercicio 3:
    A função cria grafo recebe 3 parametos, o numero de vertices, o numero de grau máximo, e se é ou não ponderado (se as vertices tem peso).
    Declara o grafo e aloca dinamicamente, passa as variaveis para dentro da estrutura do grafo, e aloca um vetor para os graus na quantidade de numero de vertices,
    aloca dinamicamente a quantidade de arestas de acordo com o numero de vertices, entra no for e aloca mais uma vez só que agora de acordo com o numero máximo de 
    grau. Se o grafo por ponderado ele cria uma outra alocação igual a de cima para armazenar os valores dos pesos de cada vertice.
*/
Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = (eh_ponderado != 0)?1:0;
        gr->grau = (int*) calloc(nro_vertices,sizeof(int));

        gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));
        for(i=0; i<nro_vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));

        if(gr->eh_ponderado){
            gr->pesos = (float**) malloc(nro_vertices * sizeof(float*));
            for(i=0; i<nro_vertices; i++)
                gr->pesos[i] = (float*) malloc(grau_max * sizeof(float));
        }

    }
    return gr;
}

/*
Exercicio 3:
    A função recebe um grafo como parametro, verifica se ele é diferente de nulo, é declarado um int, para ir percorrendo de 0 até o numero de vertices, e ir liberando aresta por aresta.
    E novamente se for ponderado ele libera da mesma maneira pois a estrutura é a mesma, e depois libera o vetor do grau e só depois de liberar essas 3 estruturas alocadas na mémoria que ele 
    libera o grafo.
*/
void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        if(gr->eh_ponderado){
            for(i=0; i<gr->nro_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

/*
Exercicio 3:
    A função de inserir aresta recebe 5 parametros, o grafo a ser colocado a aresta, a origem da aresta, o destino dessa aresta, se é digrafo (se apenas vai, não volta), e se 
    tem peso para essa aresta. Primeiro tem as funções de segurança, verifica se o grafo existe, se a origem dele é menor que 0, ou se essa origem é maior ou igual ao numero de vertices
    e o mesmo processo para o destino, isso garante que exista uma vertice para ser feita a conexão e que não estoure o limite máximo de grau. Esse (gr->arestas[orig][gr->grau[orig]] = dest)
    serve para ajustar dentro da lista adjacente que essa vertice de origem tem uma aresta para o destino, se o grafo for ponderado ele faz o mesmo processo e passa o peso para dentro da lista adjacente
    dos pesos. E ajusta dentro do vetor de grau para adicionar mais uma aresta para a vertice de origem. Caso a aresta não seja digrafo, ele chama a função de novo invertendo o destino com a origem e passando 
    1 como digrafo, essa chamada de função serve para que o processo seja feito para que a o destino passado originalmente consiga apontar para a origem.
*/
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    gr->arestas[orig][gr->grau[orig]] = dest;
    if(gr->eh_ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    if(eh_digrafo == 0)
        insereAresta(gr,dest,orig,1,peso);
    return 1;
}

/*
Exercicio 3:
    Nessa função é passado 4 parametros, o grafo a ser retirado a aresta, a origem daonde essa aresta vai ser removida, o destino, e se é digrafo ou não.
    É feita as verificações de segurança, se o grafo existe, se a origem ou o destino estão dentro dos padrões para o grafo, caso contrário já é retornado 0.
    é declarado um int que vai ser utilizado para achar o destino, dentro do while ele percorre até achar o destino ou até ser igual a quantidade de graus da origem
    se for igual a quantidade de graus da origem é porque o destino não foi achado. Se foi achado já é decrementado dentro do vetor de grau, e essa é a linha de código
    que faz com que a remoção seja feita (gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]]) se o grafo for ponderado ele repete o processo para retirar o peso 
    da lista adjacente, e se não for digrafo ele chama a função de novo para fazer a retirada para o destino para a origem, se não for ele só retorna 1.
*/
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    int i = 0;
    while(i<gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if(i == gr->grau[orig])//elemento nao encontrado
        return 0;
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    if(gr->eh_ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
    if(eh_digrafo == 0)
        removeAresta(gr,dest,orig,1);
    return 1;
}

void imprime_Grafo(Grafo *gr){
    if(gr == NULL)
        return;

    int i, j;
    for(i=0; i < gr->nro_vertices; i++){
        printf("%d: ", i);
        for(j=0; j < gr->grau[i]; j++){
            if(gr->eh_ponderado)
                printf("%d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]);
            else
                printf("%d, ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}

void grafoSimplesDirecionado(){
    Grafo* gf = cria_Grafo(4, 4, 0);

    printf("\n");
    insereAresta(gf, 0, 1, 1, 0);
    insereAresta(gf, 1, 2, 1, 0);
    insereAresta(gf, 2, 3, 1, 0);
    
    printf("Grafo simples direcionado: \n");
    imprime_Grafo(gf);
    
    printf("\n");
    libera_Grafo(gf);
}


void grafoSimplesNaoDirecionado(){
    Grafo* gf = cria_Grafo(4, 4, 0);

    printf("\n");
    insereAresta(gf, 0, 1, 0, 0);
    insereAresta(gf, 1, 2, 0, 0);
    insereAresta(gf, 2, 3, 0, 0);

    printf("Grafo simples não direcionado: \n");
    imprime_Grafo(gf);
    
    printf("\n");
    libera_Grafo(gf);
}

void grafoSimplesConexo(){
    Grafo* gf = cria_Grafo(8,6,0);
    
    printf("\n");
    insereAresta(gf, 0, 1, 0, 0);
    insereAresta(gf, 0, 2, 0, 0);
    insereAresta(gf, 0, 3, 0, 0);
    insereAresta(gf, 0, 4, 0, 0);
    insereAresta(gf, 0, 5, 0, 0);
    insereAresta(gf, 0, 6, 0, 0);
    insereAresta(gf, 1, 2, 0, 0);
    insereAresta(gf, 1, 3, 0, 0);
    insereAresta(gf, 1, 4, 0, 0);
    insereAresta(gf, 2, 4, 0, 0);
    insereAresta(gf, 2, 6, 0, 0);
    insereAresta(gf, 3, 7, 0, 0);
    
    imprime_Grafo(gf);

    printf("\n");
    libera_Grafo(gf);
}

void grafoSimplesConexo2(){
    Grafo* gf = cria_Grafo(8,5,0);
    
    printf("\n");
    insereAresta(gf, 0, 1, 0, 0);
    insereAresta(gf, 0, 2, 0, 0);
    insereAresta(gf, 0, 3, 0, 0);
    insereAresta(gf, 0, 4, 0, 0);
    insereAresta(gf, 0, 5, 0, 0);
    insereAresta(gf, 1, 4, 0, 0);
    insereAresta(gf, 1, 5, 0, 0);
    insereAresta(gf, 1, 6, 0, 0);
    insereAresta(gf, 1, 7, 0, 0);
    insereAresta(gf, 2, 4, 0, 0);
    insereAresta(gf, 2, 5, 0, 0);
    insereAresta(gf, 2, 6, 0, 0);
    insereAresta(gf, 2, 7, 0, 0);
    insereAresta(gf, 3, 6, 0, 0);
    insereAresta(gf, 3, 7, 0, 0);
    
    imprime_Grafo(gf);
    
    printf("\n");
    libera_Grafo(gf);
}


/*
Exercicio 2:
    a) O grafo tem 11 arestas.
    b) O grafo tem 7 vértices.
    c) Não é possível.
    d) Passando por 'DFW' pois tem um peso menor que o caminho direto.
    Os exercicios E e F estão dentro da pasta imagens.
*/

/*
Exercicio 4:
    Essa estrutura do novo grafo é mais simplificada e utiliza listas de adjacências. O grafo é representado por um vetor de listas, onde cada lista contém
    os vértices adjacentes a um determinado vértice. A estrutura possui apenas as variáveis essenciais: o vetor de listas, o número de nós,
    se o grafo é direcionado e se é ponderado. Essas duas últimas propriedades são necessárias para determinar o comportamento
    correto nas operações de inserção e remoção de arestas.
*/

typedef struct no {
    int vertice;         
    float peso;          
    struct no* prox;     
} No;


typedef struct {
    No* inicio;          
} Lista;

// Estrutura do grafo
typedef struct { 
    Lista **vet;         
    int nos;             
    int eh_direcionado;  
    int eh_ponderado;    
} Grafo2;


/*
Exercicio 4:
    Essa função cria um novo grafo utilizando a estrutura Grafo2. Primeiro verifica se o número de nós é válido (maior que zero). Em seguida, aloca
    memória para a estrutura do grafo e inicializa seus campos com os valores recebidos como parâmetros. Depois, aloca um vetor de ponteiros para as
    listas de adjacências, com tamanho igual ao número de nós. Se ocorrer falha na alocação, libera a memória já alocada e retorna NULL.
    
    Para cada posição do vetor, aloca uma estrutura Lista e inicializa seu ponteiro 'inicio' como NULL, indicando que a lista está vazia inicialmente.
    Se ocorrer falha na alocação de alguma lista, libera toda a memória já alocada anteriormente e retorna NULL. Esse processo garante que não haja
    vazamento de memória em caso de falha. Ao final, retorna o ponteiro para o grafo criado.
*/

Grafo2* cria_Grafo(int n, int direcionado, int ponderado) {
    if (n <= 0) return NULL;
    
    Grafo2* gr = (Grafo2*) malloc(sizeof(Grafo2));
    if (gr == NULL) return NULL;
    
    gr->nos = n;
    gr->eh_direcionado = direcionado;
    gr->eh_ponderado = ponderado;
    
    // Aloca o vetor de listas de adjacências
    gr->vet = (Lista**) malloc(n * sizeof(Lista*));
    if (gr->vet == NULL) {
        free(gr);
        return NULL;
    }
    
    // Inicializa cada lista
    for (int i = 0; i < n; i++) {
        gr->vet[i] = (Lista*) malloc(sizeof(Lista));
        if (gr->vet[i] == NULL) {
            // Libera memória já alocada em caso de falha
            for (int j = 0; j < i; j++) {
                free(gr->vet[j]);
            }
            free(gr->vet);
            free(gr);
            return NULL;
        }
        gr->vet[i]->inicio = NULL;  // Lista vazia
    }
    
    return gr;
}

/*
Exercicio 4:
    Essa função insere uma aresta no grafo, conectando o vértice de origem ao vértice de destino. Primeiro são feitas verificações de segurança: se o grafo existe
    e se os índices de origem e destino são válidos (dentro do intervalo de 0 até o número de nós menos 1). Em seguida, aloca memória para um novo nó que
    será inserido na lista de adjacências do vértice de origem. Este nó contém o índice do vértice de destino e o peso da aresta.
    
    O peso da aresta é determinado pelo parâmetro 'peso' se o grafo for ponderado, ou é definido como 1.0 se não for. O novo nó é inserido no início da
    lista de adjacências do vértice de origem (operação O(1)). Se o grafo não for direcionado, a função também cria uma aresta no sentido inverso,
    do vértice de destino para o vértice de origem, com o mesmo peso. Isso garante que ambos os vértices tenham conhecimento da conexão entre eles.
*/

int insere_Aresta(Grafo2* gr, int origem, int destino, float peso) {
    if (gr == NULL) return 0;
    if (origem < 0 || origem >= gr->nos || destino < 0 || destino >= gr->nos) 
        return 0;
    
    // Cria um novo nó para a lista de adjacências
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return 0;
    
    novo->vertice = destino;
    novo->peso = gr->eh_ponderado ? peso : 1.0;
    novo->prox = gr->vet[origem]->inicio;
    gr->vet[origem]->inicio = novo;
    
    // Se o grafo não for direcionado, adiciona a aresta no sentido inverso
    if (!gr->eh_direcionado) {
        No* novo_inv = (No*) malloc(sizeof(No));
        if (novo_inv == NULL) return 0;
        
        novo_inv->vertice = origem;
        novo_inv->peso = gr->eh_ponderado ? peso : 1.0;
        novo_inv->prox = gr->vet[destino]->inicio;
        gr->vet[destino]->inicio = novo_inv;
    }
    
    return 1;
}

/*
Exercicio 4:
    Esta função remove uma aresta que conecta o vértice de origem ao vértice de destino. Primeiro verifica se o grafo existe e se os índices de
    origem e destino são válidos. Em seguida, percorre a lista de adjacências do vértice de origem procurando pelo nó que contém o vértice de destino.
    
    A busca é feita utilizando dois ponteiros: 'atual', que aponta para o nó sendo examinado, e 'anterior', que aponta para o nó que precede 'atual'.
    Se o nó com o vértice de destino não for encontrado, a função retorna 0. Caso contrário, o nó é removido da lista ajustando os ponteiros adequadamente:
    se for o primeiro nó da lista (anterior == NULL), atualiza o ponteiro de início da lista; caso contrário, faz o nó anterior apontar para o próximo do atual.
    
    Se o grafo não for direcionado, a função também remove a aresta no sentido inverso, do vértice de destino para o de origem, seguindo o mesmo processo.
    Esta implementação garante que a remoção de uma aresta seja refletida corretamente em ambas as direções em grafos não direcionados.
*/

int remove_Aresta(Grafo2* gr, int origem, int destino) {
    if (gr == NULL) return 0;
    if (origem < 0 || origem >= gr->nos || destino < 0 || destino >= gr->nos) 
        return 0;
    
    No* atual = gr->vet[origem]->inicio;
    No* anterior = NULL;
    
    // Procura a aresta na lista de adjacências
    while (atual != NULL && atual->vertice != destino) {
        anterior = atual;
        atual = atual->prox;
    }
    
    // Se não encontrou
    if (atual == NULL) return 0;
    
    // Remove o nó da lista
    if (anterior == NULL) {
        gr->vet[origem]->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    
    free(atual);
    
    // Se o grafo não for direcionado, remove a aresta no sentido inverso
    if (!gr->eh_direcionado) {
        atual = gr->vet[destino]->inicio;
        anterior = NULL;
        
        while (atual != NULL && atual->vertice != origem) {
            anterior = atual;
            atual = atual->prox;
        }
        
        if (atual != NULL) {
            if (anterior == NULL) {
                gr->vet[destino]->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
        }
    }
    
    return 1;
}

/*
Exercicio 4:
    Esta função libera toda a memória alocada para o grafo. Primeiro verifica se o grafo existe; se for NULL, simplesmente retorna sem fazer nada.
    Caso contrário, para cada vértice do grafo, percorre sua lista de adjacências liberando cada nó individualmente. O processo é feito usando
    dois ponteiros: 'atual', que aponta para o nó sendo liberado, e 'temp', que guarda temporariamente esse ponteiro antes de avançar para o próximo nó.
    
    Depois de liberar todos os nós de uma lista, libera a estrutura da lista em si. Quando todas as listas forem liberadas, libera o vetor de listas
    e finalmente a estrutura do grafo. Esta função é essencial para evitar vazamentos de memória quando o grafo não for mais necessário.
    O processo de liberação é feito de forma cuidadosa, de dentro para fora, garantindo que toda a memória alocada seja propriamente liberada.
*/

void libera_Grafo(Grafo2* gr) {
    if (gr == NULL) return;
    
    for (int i = 0; i < gr->nos; i++) {
        No* atual = gr->vet[i]->inicio;
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
        free(gr->vet[i]);
    }
    
    free(gr->vet);
    free(gr);
}


/*
Exercicio 5:
    A função prim implementa o algoritmo de Prim para encontrar a Árvore Geradora Mínima de um grafo ponderado. Primeiro são feitas
    verificações de segurança: se o grafo existe, se a vertice inicial é valida e se o grafo é ponderado. Em seguida, são alocados três vetores: 'pai' 
    (armazena a estrutura da MST), 'menor' (armazena o menor peso conhecido para cada vértice) e 'visitado' (indica quais vértices já foram incluídos na MST).
    
    No processo de inicialização, todos os vertices começam com peso infinito exceto o vértice inicial que recebe peso 0. O algoritmo principal
    consiste em um loop que executa para cada vértice: seleciona o vértice não visitado com menor peso conhecido, marca-o como visitado e atualiza
    os pesos dos vértices adjacentes se encontrar caminhos mais baratos. A cada iteração, um novo vértice é adicionado à MST.
    
    Ao final, são liberadas as memórias auxiliares e retornado o vetor 'pai', onde pai[i] indica qual vértice conecta i à MST. Se pai[i] == -1,
    significa que i é o vértice inicial ou não está conectado ao componente principal do grafo.
*/
int* prim(Grafo* gr, int inicio) {
    if(gr == NULL) return NULL;
    if(inicio < 0 || inicio >= gr->nro_vertices) return NULL;
    if(!gr->eh_ponderado) return NULL; // Prim só funciona em grafos ponderados
    
    int i, j, dest, atual;
    float menor_peso;
    int* pai = (int*)malloc(gr->nro_vertices * sizeof(int));
    float* menor = (float*)malloc(gr->nro_vertices * sizeof(float));
    int* visitado = (int*)malloc(gr->nro_vertices * sizeof(int));
    
    // Inicialização
    for(i = 0; i < gr->nro_vertices; i++) {
        pai[i] = -1;
        menor[i] = INFINITY;
        visitado[i] = 0;
    }
    menor[inicio] = 0;
    
    // Algoritmo de Prim
    for(i = 0; i < gr->nro_vertices; i++) {
        // Encontra vértice com menor peso não visitado
        atual = -1;
        menor_peso = INFINITY;
        for(j = 0; j < gr->nro_vertices; j++) {
            if(!visitado[j] && menor[j] < menor_peso) {
                atual = j;
                menor_peso = menor[j];
            }
        }
        
        if(atual == -1) break; // Não há mais vértices alcançáveis
        
        visitado[atual] = 1;
        
        // Atualiza os menores pesos dos vértices adjacentes
        for(j = 0; j < gr->grau[atual]; j++) {
            dest = gr->arestas[atual][j];
            if(!visitado[dest] && gr->pesos[atual][j] < menor[dest]) {
                pai[dest] = atual;
                menor[dest] = gr->pesos[atual][j];
            }
        }
    }
    
    free(menor);
    free(visitado);
    
    return pai;
}

/*
Exercicio 5:
    Esta função recebe um grafo e um vetor de pais que representa a Árvore Geradora Mínima obtida pelo algoritmo de Prim,
    e imprime as arestas que compõem esta árvore junto com seus respectivos pesos. Primeiro são feitas verificações de segurança
    para garantir que o grafo e o vetor de pais existem.
    
    Em seguida, a função percorre todos os vértices do grafo. Para cada vertice i que tem um pai válido (pai[i] != -1),
    busca na lista de adjacências do pai o peso da aresta que conecta pai[i] a i. Isso é feito percorrendo todas as arestas do
    vértice pai[i] até encontrar aquela que aponta para i.
    
    Cada aresta é impressa no formato "(origem, destino) Peso: valor", e o peso é acumulado na variável peso_total.
    Ao final, a função imprime o peso total da MST, que representa o custo mínimo para conectar todos os vértices do grafo.
*/
void imprime_MST(Grafo* gr, int* pai) {
    if(gr == NULL || pai == NULL) return;
    
    printf("Árvore Geradora Mínima:\n");
    float peso_total = 0;
    
    for(int i = 0; i < gr->nro_vertices; i++) {
        if(pai[i] != -1) {
            // Encontrar o peso da aresta (pai[i], i)
            float peso = 0;
            for(int j = 0; j < gr->grau[pai[i]]; j++) {
                if(gr->arestas[pai[i]][j] == i) {
                    peso = gr->pesos[pai[i]][j];
                    break;
                }
            }
            
            printf("(%d, %d) Peso: %.2f\n", pai[i], i, peso);
            peso_total += peso;
        }
    }
    
    printf("Peso total da MST: %.2f\n", peso_total);
}

/*
Exercício 6:
    a) Esta função verifica se um nó específico existe no grafo. A função recebe um grafo e o índice do nó a ser verificado.
    Primeiro são feitas as verificações de segurança: se o grafo existe e se o índice do nó está dentro do intervalo válido
    (entre 0 e número de vértices - 1). Se o nó existe (está dentro do intervalo válido), retorna 1; caso contrário, retorna 0.
    Esta função é útil para validar se um determinado vértice existe antes de realizar operações sobre ele.
*/
int encontrar_no(Grafo* gr, int no) {
    if(gr == NULL) return 0;  // Grafo não existe
    if(no < 0 || no >= gr->nro_vertices) return 0;  // Nó fora do intervalo válido
    
    return 1;  // Nó existe
}

/*
Exercício 6:
    b) Esta função encontra a aresta de menor peso em um grafo ponderado. A função percorre todas as arestas do grafo e
    identifica aquela com o menor peso. Primeiro são feitas verificações de segurança: se o grafo existe e se é ponderado.
    
    A função inicializa o menor peso com infinito e percorre todos os vértices do grafo. Para cada vértice, examina todas as suas
    arestas adjacentes comparando os pesos. Quando encontra um peso menor que o atual menor peso, atualiza as variáveis de menor peso,
    origem e destino. Os parâmetros origem e destino são passados por referência para retornar os vértices da aresta de menor peso.
    
    Retorna o menor peso encontrado, ou -1 se não houver arestas no grafo ou se ocorrer algum erro.
*/
float encontrar_aresta_menor_peso(Grafo* gr, int* origem, int* destino) {
    if(gr == NULL) return -1;  // Grafo não existe
    if(!gr->eh_ponderado) return -1;  // Só funciona em grafos ponderados
    if(origem == NULL || destino == NULL) return -1;  // Ponteiros inválidos
    
    float menor_peso = INFINITY;
    int origem_menor = -1, destino_menor = -1;
    int encontrou_aresta = 0;
    
    // Percorre todos os vértices
    for(int i = 0; i < gr->nro_vertices; i++) {
        // Percorre todas as arestas do vértice i
        for(int j = 0; j < gr->grau[i]; j++) {
            float peso_atual = gr->pesos[i][j];
            
            // Se encontrou peso menor, atualiza
            if(peso_atual < menor_peso) {
                menor_peso = peso_atual;
                origem_menor = i;
                destino_menor = gr->arestas[i][j];
                encontrou_aresta = 1;
            }
        }
    }
    
    // Se não encontrou nenhuma aresta
    if(!encontrou_aresta) return -1;
    
    // Retorna os vértices da aresta por referência
    *origem = origem_menor;
    *destino = destino_menor;
    
    return menor_peso;
}




