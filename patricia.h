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

#endif //PATRICIATESTE_PATRICIA_H
