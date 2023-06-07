#ifndef PATRICIATESTE_ARQUIVO_H
#define PATRICIATESTE_ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "patricia.h"

void imprime_menu();

int validateText(char *text);

FILE* loadPath();

void carregaArquivo(int op, No* raiz);

#endif //PATRICIATESTE_ARQUIVO_H
