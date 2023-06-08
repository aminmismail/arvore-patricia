#include "patricia.h"
#include "arquivo.h"

int findFirstDif(const char *str1, const char *str2){
    int i;
    for(i=0; str1[i] == str2[i]; i++);
    return i;
}

int isPrefixo(const char* str1, const char* str2) {
    return (strncmp(str1, str2, strlen(str1)) == 0);
}

No* criaNoFinal(char *text){
    int i;
    No* aux = (No*) malloc(sizeof(No));
    for(i=0; i < 1000; i++) aux->filhos[i] = NULL;
    aux->isFinal = 1;
    aux->isPalavra = 1;
    aux->numFilhos = 0;
    strcpy(aux->texto, text);
    return aux;
}

No* criaNoRaiz(){
    int i;
    No* aux = (No*) malloc(sizeof(No));
    for(i=0; i < 1000; i++) aux->filhos[i] = NULL;
    aux->isFinal = 0;
    aux->isPalavra = 0;
    aux->numFilhos = 0;
    strcpy(aux->texto, " ");

    return aux;
}

No* criaNoInterno(No* no, int ind){
    No* aux1 = (No*) malloc(sizeof(No));
    No* aux2 = (No*) malloc(sizeof(No));


    return no;
}

No *buscaPos(No* no, char text[], int *pos) {
    if (no == NULL) return NULL;
    int i = 0;
    for(i=0; i < no->numFilhos && text[0] < no->filhos[i]->texto[0]; i++);
    if ()
        return buscaPos(no->filhos[i], text, pos);
    *pos = i;
    return no;
}

void imprimeDicionarioAux(No* no, char *word) { //colocar prefixo ainda
    int i;
    if (no == NULL) return;

    int len = strlen(word);
    strcat(word, no->texto);

    if (no->isPalavra) {
        word[len + strlen(no->texto)] = '\0';
        printf("%s\n", word);
    }

    for (i = 0; i < no->numFilhos; i++) {
        imprimeDicionarioAux(no->filhos[i], word);
    }

    word[len] = '\0';
}


void imprimeDicionario(No* raiz){
    char word[100] = {};
    imprimeDicionarioAux(raiz, word);
}

No* getPos(No* raiz, int *pos){
    //if(raiz == NULL)
}


void inserePalavra(char *str, No* raiz){
    /*int i=0;
    if(raiz == NULL) raiz = criaNoRaiz();

    if(raiz->numFilhos == 0){
        No* aux = criaNoFinal(str);
        raiz->numFilhos++;
        raiz->filhos[0] = aux;
    }
    else{
        for(i=0; i<raiz->numFilhos && str[0] < raiz->filhos[i]->texto[0]; i++);
        if(findFirstDif(raiz->texto, str) == 0){
            if(){
                No* aux = criaNoFinal(str);
                raiz->numFilhos++;
                raiz->filhos[raiz->numFilhos]
            }
        }


    }*/
}