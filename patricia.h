#ifndef PATRICIATESTE_PATRICIA_H
#define PATRICIATESTE_PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct no{
    char* texto;
    struct no* filhos[1000];
    int numFilhos;
    int isFinal;
    int isPalavra;
}No;

int findFirstDif(const char *str1, const char *str2);

int isPrefixo(const char* str1, const char* str2);

No* criaNoFinal(char *text);

No* criaNoRaiz();

//No* criaNoInterno(No* no, int ind);

void consultaPalavraAux(No* no, char *word, char* prefix, int* count);

void consultaPalavra(No* raiz, char* prefix);

void imprimeDicionarioAux(No* no, char* word);

void imprimeDicionario(No* raiz);

void inserePalavra(char *str, No* no);

No *buscaPos(No* no, char text[], int *pos);

//No* getPos(No* raiz, int *pos);

#endif //PATRICIATESTE_PATRICIA_H
