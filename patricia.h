#ifndef PATRICIATESTE_PATRICIA_H
#define PATRICIATESTE_PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct no{
    char texto[100];
    struct no* filhos[1000];
    int numFilhos;
    int isFinal;
    int isPalavra;
}No;

int findFirstDif(const char *str1, const char *str2);

int isPrefixo(const char* str1, const char* str2);

No* criaNoFinal(char *text);

No* criaNoRaiz();

No* criaNoInterno(No* no, int ind);

void imprimeDicionarioAux(No* no, char* word);

void imprimeDicionario(No* raiz);

void inserePalavra(char *str, No* no);

#endif //PATRICIATESTE_PATRICIA_H
