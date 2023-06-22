#ifndef PATRICIATESTE_ARQUIVO_H
#define PATRICIATESTE_ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "patricia.h"

// Imprime o menu de opções
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprime_menu();

// Valida o texto fornecido
// Pré-condição: text é um ponteiro não nulo para uma string válida
// Pós-condição: retorna 1 se o texto for válido, 0 caso contrário
int validateText(char *text);

// Carrega o caminho do arquivo
// Pré-condição: nenhuma
// Pós-condição: retorna um ponteiro para o arquivo carregado
FILE* loadPath();

// Carrega o arquivo na árvore Patricia
// Pré-condição: op é uma opção válida, raiz é um ponteiro não nulo para a raiz da árvore
// Pós-condição: o arquivo é carregado na árvore Patricia
void carregaArquivo(int op, No* raiz);


#endif //PATRICIATESTE_ARQUIVO_H
