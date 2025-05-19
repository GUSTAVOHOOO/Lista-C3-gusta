//Arquivo ListaDinEncad.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista(Lista* li, int mat);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
int lista_cheia(Lista* li);
void imprime_lista(Lista* li);

//Funções para o exercicio 1
int consulta_matricula(Lista* li, int num);
int consulta_posicao(Lista* li, int num);
/*As duas funções são bem parecidas, fazem a verificação se são nulas ou não, declaram um nó para percorrer
a lista, percorrem a lista até acaharem a matricula e a posição desejada, se o no for nulo é porque não foi
encontrado dentro da lista, se nao for eles printam o resultado encontrado.*/

//Funcoes para o exercicio 2
int remove_rec(Lista* li, int n);
int listas_iguais(Lista* li, Lista* l2);
/*A primeira função recebe uma lista e um numero de matricula, dentro da função faz a verificação se a lista é nula, 
um if para verificar se a matricula do elemento é a mesma matricula passada e remove se for, e faz o passo recursivo 
retornando o endereço da lista.prox.

Já a segunda função verifica se as listas acabam junto para poder dizer que são iguais, faz a verificação se uma terminou,
antes da outra, e faz a verificação de cada dado dentro do strut aluno, e retorna a lista dos proximo elementos dentro 
de cada lista.
*/

//Função para o exercicio 3
int insere_posicao(Lista* li, int num, struct aluno al);
/*Aqui é passado uma lista um numero e um aluno, faz a verificação da lista ser vazia ou se o num menor que 0
faz a alocação de um novo nó, e passa o aluno como os dados, se a posição desejada for 1 ele adiciona como primeiro
e vira a cabeça da lista, após é feito um wihle para podermos chegar até a posição necessária, se o ptr for null é 
porque é a posição da lista, e é preciso fazer o no.prox apontar para null, caso contrario é so fazer os ajustes de 
ptrAnt para no e no.prox para ptr, para poder inserir no meio.*/

//Funcao para o exercicio 4
Lista* cria_lista_ordem(struct aluno* al, int n);
/*A função cria uma lista e faz um for para poder inserir a quantidade necessária de alunos presentes dentro
do vetor, e após retorna a lista*/

//Funcao para o exercicio 5
int remove_n(Lista* li, int n);
/*Recebe uma lista e um inteiro, verifica se a lista ta vazia, pega o tamanho da lista, faz um for de 0 até
tamanho e remove todos os n presentes da lista*/

//Funcoes para o exercicio 6
int concatenar_listas(Lista* l1, Lista* l2);
/*Verifica se algumas das listas é vazia, declara no como a primeira lista, percorre o no até no.prox ser nulo
e coloca no.prox para apontar a lista 2*/

//Funcao para o exercicio 7
int remover_repetidos(Lista* li);
/*Verifica se é vazia ou não existe, declara um comp como li, faz um while para rodar até comp ser nulo
declara um anterior e um no, e corre todo o no verificando se o no da matricula é igual ao do comp, se for
o prox de anterior aponta para no.prox, libera o no e faz no ser anterior.prox, se nao for atualiza anterior
e o no, repete todo esses passos para verificar um por um por um dentro da lista*/

//Função para o exercicio 8
void junta_e_ordena(Lista *l1, Lista *l2);
/*o codigo implementa a junção de duas listas encadeasdas em uma unica lista  oredenada , sem criar novos nós como foi pedido 
no exercico . Ele compara os elementos da duas listas , nó a nó e reorganiza os ponteiros para formar uma 
nova sequencia crescente de acordo com as matriculas dos alunos
a função percorre ambas as listas simultanemaente sempre adicionando o menor valor no finalda lista.
Quando uma das listas termina, orestante da outra é anexada diretamente, O resultado final substitui a lista original l1 e a esvazia a lista
l2, esse codigo simula um  Merge Sort.*/


//Função para o exercicio 9
int Troca(Lista* li, Elemento* p );
/*Faz a verificação se a lista é vazia ou nula, se o p é nulo ou se o proximo dele é nulo
abre um if para caso p seja o primeiro elemento, é feito o tratamento necessário, caso contrario 
percorre toda a lista até o elemento anterior de p e é feito a troca necessária.*/


