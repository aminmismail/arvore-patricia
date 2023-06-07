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
    No* aux = (No*) malloc(sizeof(No));
    aux->isFinal = 1;
    aux->isPalavra = 1;
    aux->numFilhos = 0;
    strcpy(aux->texto, text);
    return aux;
}

No* criaNoRaiz(){
    No* aux = (No*) malloc(sizeof(No));
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

void imprimeDicionarioAux(No* no, char* word){
    int i;
    if(no == NULL) return;

    for(i = 0; i < no->numFilhos; i++){
        imprimeDicionarioAux(no->filhos[i], word);
    }

    strcat(word, no->texto);
    if(no->isPalavra){
        int final = strlen(word);
        if(no->isFinal){
            word[final] = '\0';
            printf("%s\n", word);
        }
        else{
            char word2[50];
        }
    }

    imprimeDicionarioAux(no->filhos[i], word);

}

void imprimeDicionario(No* raiz){
    char word[100];
    imprimeDicionarioAux(raiz, word);
}

void inserePalavra(char *str, No* raiz){
    int i=0;
    if(raiz == NULL) raiz = criaNoRaiz();

    if(raiz->numFilhos == 0){
        No* aux = criaNoFinal(str);
        raiz->numFilhos++;
        raiz->filhos[0] = aux;
    }
    else{
        for(i=0; )
        if(findFirstDif(raiz->texto, str) == 0){
            if(str[0] > raiz->texto[0]){
                No* aux = criaNoFinal(str);
                raiz->numFilhos++;
                raiz->filhos[raiz->numFilhos]
            }
        }
    }


}