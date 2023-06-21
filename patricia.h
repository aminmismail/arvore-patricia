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

int findFirstDif(const char *str1, const char *str2);

int isPrefixo(const char* str1, const char* str2);

void lowerWord(char word[]);

No* criaNoRaiz();

void consultaPalavrasAux(No* no, char *word, char* prefix, int* count, char vet[][50], int op);

void consultaPalavras(No* raiz, char* prefix, int op);

No* criaNo(char* texto);

int buscar(No* no, char* str);

void split(No* noAtual, int i, char restoNovo[], char prefixo[], char novoFilho[]);

void inserir(No* raiz, char* chave);

void imprime_por_niveis(No* raiz);

No* buscaNo(No* no, char* str);

// cria uma fila
// Pré-condição: nenhuma
// Pós-condição: fila criada
FILA* cria_fila();

//pré-requisitos: Recebe um ponteiro não nulo para fila
//pós-requisitos: Retorna 1 se a fila for vazio e 0 se não
int fila_vazia(FILA *f);

//pré-requisitos: Um ponteiro não nulo para fila
//pós-requisitos: a quantidade de elementos na fila é retornado
int fila_tam(FILA *f);

// enfileira uma chave na fila
// Pré-condição: fila existente e chave a ser inserida
// Pós-condição: fila atualizada com chave
void enqueue(FILA *f, No* no);

// desenfileira uma chave na fila
// Pré-condição: fila existente e chave a ser removida
// Pós-condição: fila atualizada sem a chave
No* dequeue(FILA* f);

#endif //PATRICIATESTE_PATRICIA_H
