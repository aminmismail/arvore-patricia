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
    for(i=0; i < numFilhosNo; i++) aux->filhos[i] = NULL;
    aux->isFinal = 1;
    aux->isPalavra = 1;
    aux->numFilhos = 0;
    strcpy(aux->texto, text);
    return aux;
}


No* criaNoRaiz(){
    int i;
    No* aux = (No*) malloc(sizeof(No));
    for(i=0; i < numFilhosNo; i++) aux->filhos[i] = NULL;
    aux->isFinal = 0;
    aux->isPalavra = 0;
    aux->numFilhos = 0;
    strcpy(aux->texto, "");
    return aux;
}


/*No* criaNoInterno(No* no, int ind){
    No* aux1 = (No*) malloc(sizeof(No));
    No* aux2 = (No*) malloc(sizeof(No));


    return no;
}*/


No *buscaPos(No* no, char* text, int *pos) {
    if (no == NULL) return NULL;
    int i;
    for (i = 0; i < no->numFilhos && text[0] > no->filhos[i]->texto[0]; i++);
    if ((i + 1) > no->numFilhos || findFirstDif(text, no->filhos[i]->texto) == 0) {
        *pos = i;
        return no;
    }

    /*else if (isPrefixo(no->filhos[i]->texto, text)){
        text += strlen(no->filhos[i]->texto);
        return buscaPos(no->filhos[i], text, pos);
    }*/

    else{
        text += findFirstDif(text, no->filhos[i]->texto);
        return buscaPos(no->filhos[i], text, pos);
    }

}


void consultaPalavraAux(No* no, char *word, char* prefix, int* count) {
    int i;
    if (no == NULL || *count >= 10){

        return;
    }

    int len = strlen(word);
    strcat(word, no->texto);

    if (no->isPalavra) {
        word[len + strlen(no->texto)] = '\0';
        if(isPrefixo(prefix,word)){
            printf("%s, ", word);
            (*count)++;
        }
    }

    for (i = 0; i < no->numFilhos; i++) {
        consultaPalavraAux(no->filhos[i], word, prefix, count);
    }

    word[len] = '\0';
}


void consultaPalavra(No* raiz, char* prefix){
    char word[100] = {};
    int count = 0;
    consultaPalavraAux(raiz, word, prefix, &count);
}


void imprimeDicionarioAux(No* no, char *word) {
    int i;
    if (no == NULL) return;
    if (strcmp(no->texto, "") == 0 && no->numFilhos == 0) printf("Nenhuma palavra na arvore!\n");

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
    char word[100] = {}, vet[1000][100] = {};
    imprimeDicionarioAux(raiz, word);
    //imprimeVetDic()
}


//Move os filhos de um nó para a direita a partir de uma pos
void moveDireita(No* no, int pos){
    int i = no->numFilhos;
    for(; i >= pos; i--) no->filhos[i+1] = no->filhos[i];
    //no->numFilhos++;
}


//
void desceFilhos(No* noAtual, int pos, char* insertWord){
    int i=0, index = -1;
    char *prefixo = NULL;
    index = findFirstDif(noAtual, insertWord);
    insertWord += index;
    strncpy(prefixo,noAtual->texto,index);
    No* novoNo = criaNoFinal(prefixo);
    strcpy(noAtual->texto, &noAtual->texto[index]);
    //noAtual->texto += index;
    //buscar pai
}


/* No* getPos(No* raiz, int *pos){
    //if(raiz == NULL);
}*/


void inserePalavra(char *str, No* raiz){
    /*int i = 0;
    if(raiz == NULL) raiz = criaNoRaiz();

    if(raiz->numFilhos == 0){
        No* aux = criaNoFinal(str);
        raiz->numFilhos++;
        raiz->filhos[0] = aux;
    }

    else{
        for(i=0; i < raiz->numFilhos && str[0] < raiz->filhos[i]->texto[0]; i++);
        if(findFirstDif(raiz->texto, str) == 0){
            if(){
                No* aux = criaNoFinal(str);
                raiz->numFilhos++;
                raiz->filhos[raiz->numFilhos]
            }
        }


    }*/
}

No* createNode(char* texto) {
    No* node = (No*)malloc(sizeof(No));
    strcpy(node->texto, texto);
    node->numFilhos = 0;
    node->isFinal = 0;
    node->isPalavra = 0;
    for (int i = 0; i < numFilhosNo; i++) {
        node->filhos[i] = NULL;
    }
    return node;
}


// Insert a key into the Radix Tree
void inserir(No* no, char* str) {
    No* noAtual = no;
    int len = strlen(str), i;

    for (i = 0; i < noAtual->numFilhos && str[0] >= noAtual->filhos[i]->texto[0]; i++) {
        if (str[0] == noAtual->filhos[i]->texto[0]) {
            int k = 0;
            while (str[k] != '\0' && noAtual->filhos[i]->texto[k] != '\0' && str[k] == noAtual->filhos[i]->texto[k]) {
                k++;
            }

            if (str[k] == '\0' && noAtual->filhos[i]->texto[k] == '\0') {
                noAtual->filhos[i]->isPalavra = 1;
                return;
            }

            if (str[k] == '\0' && noAtual->filhos[i]->texto[k] != '\0') {
                inserir(noAtual->filhos[i], str + k);
                return;
            }

            if (str[k] != '\0' && noAtual->filhos[i]->texto[k] == '\0') {
                char* restante = (char*) malloc((len - k + 1));
                strncpy(restante, str + k, len - k);
                restante[len - k] = '\0';

                char* restanteFilho = (char*) malloc((strlen(noAtual->filhos[i]->texto) - k + 1));
                strncpy(restanteFilho, noAtual->filhos[i]->texto + k, strlen(noAtual->filhos[i]->texto) - k);
                restanteFilho[strlen(noAtual->filhos[i]->texto) - k] = '\0';

                strcpy(noAtual->filhos[i]->texto, restanteFilho);

                No* novoNo = createNode(restante);
                novoNo->isPalavra = 1;
                novoNo->filhos[0] = noAtual->filhos[i];
                noAtual->filhos[i] = novoNo;
                noAtual->numFilhos++;

                return;
            }
        }
    }

    moveDireita(noAtual, i);
    noAtual->filhos[i] = createNode(str);
    noAtual->filhos[i]->isPalavra = 1;
    noAtual->numFilhos++;
}