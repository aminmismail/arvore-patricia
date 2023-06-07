#ifndef PATRICIATESTE_PATRICIA_H
#define PATRICIATESTE_PATRICIA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    char* texto;
    struct no* filhos[1000];
    int numFilhos;
}No;

#endif //PATRICIATESTE_PATRICIA_H
