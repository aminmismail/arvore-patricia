#ifndef PATRICIATESTE_PATRICIA_H
#define PATRICIATESTE_PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numFilhosNo 50

typedef struct no{
    char texto[200];
    struct no* filhos[numFilhosNo];
    int numFilhos;
    int isPalavra;
}No;

typedef struct no_fila{
    No *no;
    struct no_fila* prox;
}NO_FILA;

typedef struct fila{
    NO_FILA* inicio;
    NO_FILA* fim;
}FILA;

// Verifica se str1 é um prefixo de str2
// Pré-condição: nenhuma
// Pós-condição: retorna 1 se str1 é um prefixo de str2, 0 caso contrário
int isPrefixo(const char* str1, const char* str2);

// Converte a palavra word para letras minúsculas
// Pré-condição: nenhuma
// Pós-condição: a palavra word é convertida para letras minúsculas
void lowerWord(char word[]);

// Cria um nó raiz da árvore Patricia
// Pré-condição: nenhuma
// Pós-condição: retorna um ponteiro para o nó raiz criado
No* criaNoRaiz();

// Consulta as palavras que começam com o prefixo prefix
// Pré-condição: no aponta para um nó válido da árvore, word é uma palavra auxiliar, count é um contador, vet é um vetor de palavras, op é um valor auxiliar
// Pós-condição: preenche o vetor vet com as palavras que começam com o prefixo prefix e atualiza o valor de count
void consultaPalavrasAux(No* no, char *word, char* prefix, int* count, char vet[][50], int op);

// Consulta as palavras que começam com o prefixo prefix na árvore com raiz raiz
// Pré-condição: raiz aponta para um nó válido da árvore, prefix é um prefixo, op é um valor auxiliar
// Pós-condição: imprime as palavras que começam com o prefixo prefix na árvore com raiz raiz
void consultaPalavras(No* raiz, char* prefix, int op);

// Imprime o vetor passado como parametro
// Pré-condição: vetor valido e numero de palavras
// Pós-condição: vetor impresso na tela do usuario
void printVet(char vet[][50], int n);

// Cria um novo nó com o texto especificado
// Pré-condição: texto é uma string válida
// Pós-condição: retorna um ponteiro para o novo nó criado
No* criaNo(char* texto);

// Remove o no de posicao i de um no pai
// Pré-condição: no é valido nao nulo e i é a posicao do no a ser removido
// Pós-condição: no removido no outro no (pai)
void removeNo(No* no, int i);

// Move os nos de um no para a direita
// Pré-condição: no é valido nao nulo e i é a posicao inicial dos nos a serem movidos
// Pós-condição: nos movidos para a direita
void moveDireita(No* no, int pos);

// Move os filhos de um no para o outro
// Pré-condição: nos validos nao nulos
// Pós-condição: move o filho de no para a posição dos filhos do pai
void copiaFilhos(No* pai, No* filho);

// Remove a palavra especificada da árvore
// Pré-condição: no aponta para um nó válido, palavra é a palavra a ser removida
// Pós-condição: remove a palavra da árvore com raiz no
void remover(No* no, char* palavra);

// Divide o nó atual em dois nós diferentes
// Pré-condição: noAtual é um nó válido, i é a posição onde a divisão deve ocorrer, restoNovo é a parte restante a ser inserida no novo nó, prefixo é o prefixo compartilhado pelos dois nós, novoFilho é o texto do novo filho
// Pós-condição: divide o nó atual em dois nós diferentes
void split(No* noAtual, int i, char restoNovo[], char prefixo[], char novoFilho[]);

// Insere uma chave na árvore
// Pré-condição: raiz é um nó válido, chave é a chave a ser inserida
// Pós-condição: insere a chave na árvore com raiz raiz
void inserir(No* raiz, char* chave);

// Imprime os nós da árvore por níveis
// Pré-condição: raiz é um nó válido, str é uma string auxiliar
// Pós-condição: imprime os nós da árvore com raiz raiz por níveis
void imprime_por_niveis(No *raiz, int c);

// Busca um prefixo na árvore
// Pré-condição: no aponta para um nó válido, str é o prefixo a ser buscado
// Pós-condição: retorna um ponteiro para o nó que representa o prefixo buscado, ou NULL caso não seja encontrado
No* buscaPrefixo(No* no, char* str, int* nivel);

// cria uma fila
// Pré-condição: nenhuma
// Pós-condição: fila criada
FILA* cria_fila();

//pré-requisitos: Recebe um ponteiro não nulo para fila
//pós-requisitos: Retorna 1 se a fila for vazio e 0 se não
int fila_vazia(FILA *f);

// enfileira uma chave na fila
// Pré-condição: fila existente e chave a ser inserida
// Pós-condição: fila atualizada com chave
void enqueue(FILA *f, No* no);

// desenfileira uma chave na fila
// Pré-condição: fila existente e chave a ser removida
// Pós-condição: fila atualizada sem a chave
No* dequeue(FILA* f);

#endif //PATRICIATESTE_PATRICIA_H
