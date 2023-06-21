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


No* criaNoRaiz(){
    int i;
    No* aux = (No*) malloc(sizeof(No));
    for(i=0; i < numFilhosNo; i++) aux->filhos[i] = NULL;
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


/*No *buscaPos(No* no, char* text, int *pos) {
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
    }//

    else{
        text += findFirstDif(text, no->filhos[i]->texto);
        return buscaPos(no->filhos[i], text, pos);
    }

}*/

// Realiza busca na arvore de uma palavra
int buscar(No* no, char* str) {
    No* noAtual = no;
    int len = strlen(str), i;

    // Find the appropriate child node
    for (i = 0; i < noAtual->numFilhos; i++) {
        if (str[0] == noAtual->filhos[i]->texto[0]) {
            int k = 0;
            while (str[k] != '\0' && noAtual->filhos[i]->texto[k] != '\0' && str[k] == noAtual->filhos[i]->texto[k]) {
                k++;
            }

            if (str[k] == '\0' && noAtual->filhos[i]->texto[k] == '\0') {
                return noAtual->filhos[i]->isPalavra;
            }

            if (str[k] == '\0' && noAtual->filhos[i]->texto[k] != '\0') {
                return buscar(noAtual->filhos[i], str + k);
            }

            break;
        }
    }

    return 0;
}

void lowerWord(char word[]){
    int i, len = strlen(word);
    for(i=0; i < len; i++) word[i] = tolower(word[i]);
}


void printVet(char vet[][50], int n){
    int i = 0;
    for(; i < n; i++){
        printf("%s", vet[i]);
        if(i < n-1) printf(", ");
    }
    printf("\n");
}

void consultaPalavraAux(No* no, char *word, char* prefix, int* count, char vet[][50]){
    int i;
    if (no == NULL || *count >= 10){
        return;
    }
    if (strcmp(no->texto, "") == 0 && no->numFilhos == 0) {
        printf("Nenhuma palavra na arvore!\n");
        return;
    }

    int len = strlen(word);
    strcat(word, no->texto);

    if (no->isPalavra) {
        word[len + strlen(no->texto)] = '\0';
        if(isPrefixo(prefix,word)){
            strcpy(vet[*count], word);
            (*count)++;
        }
    }

    for (i = 0; i < no->numFilhos; i++) {
        consultaPalavraAux(no->filhos[i], word, prefix, count, vet);
    }

    word[len] = '\0';
}


void consultaPalavra(No* raiz, char* prefix){
    char word[100] = {}, vet[10][50] = {};
    lowerWord(prefix);
    int count = 0;
    consultaPalavraAux(raiz, word, prefix, &count, vet);
    printVet(vet, count);
}

void imprimeDicionarioAux(No* no, char *word) {
    int i;
    if (no == NULL) return;
    if (strcmp(no->texto, "") == 0 && no->numFilhos == 0) {
        printf("Nenhuma palavra na arvore!\n");
        return;
    }

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

}

//Move os filhos de um nó para a direita a partir de uma pos
void moveDireita(No* no, int pos){
    int i = no->numFilhos;
    //printf("i: %d\n", i);
    for(; i >= pos; i--) no->filhos[i+1] = no->filhos[i];
}

No* criaNo(char* texto) {
    No* no = (No*)malloc(sizeof(No));
    strcpy(no->texto, texto);
    no->numFilhos = 0;
    no->isPalavra = 0;
    for (int i = 0; i < numFilhosNo; i++) {
        no->filhos[i] = NULL;
    }
    return no;
}

void split(No* noAtual, int i, char restoNovo[], char prefixo[], char novoFilho[]){
    //atualiza texto do no filho com texto novoFilho
    strcpy(noAtual->filhos[i]->texto, novoFilho);
    No* novoPrefixo = criaNo(prefixo);
    No* restNovo = criaNo(restoNovo);
    restNovo->isPalavra = 1;
    noAtual->filhos[i]->isPalavra = 1;

    //Verifica qual dos filhos é maior
    if(novoFilho[0] < restoNovo[0]){
        novoPrefixo->filhos[0] = noAtual->filhos[i];
        novoPrefixo->filhos[1] = restNovo;
    }
    else{
        novoPrefixo->filhos[0] = restNovo;
        novoPrefixo->filhos[1] = noAtual->filhos[i];
    }

    //Atualiza o filho do no atual pro prefixo
    noAtual->filhos[i] = novoPrefixo;
    novoPrefixo->numFilhos = 2;
}


// Insere uma palavra na arvore
void inserir(No* no, char* str) {
    No* noAtual = no;
    int len = strlen(str), i;
    //Percorre os filhos do nó atual
    for (i = 0; i < noAtual->numFilhos ; i++) {
        if (str[0] < noAtual->filhos[i]->texto[0]) {
            moveDireita(noAtual, i);
            noAtual->filhos[i] = criaNo(str);
            noAtual->filhos[i]->isPalavra = 1;
            noAtual->numFilhos++;
            return;
        }
        else {
            if (str[0] == noAtual->filhos[i]->texto[0]) {
                int k = 0;
                //Percorre o texto do nó filho
                while (str[k] != '\0' && noAtual->filhos[i]->texto[k] != '\0' &&
                       str[k] == noAtual->filhos[i]->texto[k]) {
                    k++;
                }
                //Se o texto do nó e do filho terminaram
                if (str[k] == '\0' && noAtual->filhos[i]->texto[k] == '\0') {
                    noAtual->filhos[i]->isPalavra = 1;
                    return;
                }
                //Se o texto do no terminou mas o novo ainda nao
                if (str[k] != '\0' && noAtual->filhos[i]->texto[k] == '\0') {
                    inserir(noAtual->filhos[i], str + k);
                    return;
                }
                //Se o texto do no e do filho ainda nao terminaram (split)
                if (str[k] != '\0' && noAtual->filhos[i]->texto[k] != '\0') {
                    //cria palavra com resto da palavra a ser inserida
                    char restoNovo[50] = {0};
                    strncpy(restoNovo, str + k, len - k); restoNovo[len - k] = '\0';
                    //cria palavra apenas com o prefixo comum
                    char prefixo[50] = {0};
                    strncpy(prefixo, noAtual->filhos[i]->texto, k); prefixo[k + 1] = '\0';
                    //cria palavra do filho menos o prefixo
                    char novoFilho[50] = {0};
                    strncpy(novoFilho, noAtual->filhos[i]->texto + k, strlen(noAtual->filhos[i]->texto) - k);
                    novoFilho[strlen(noAtual->filhos[i]->texto) - k] = '\0';
                    split(noAtual, i, restoNovo, prefixo, novoFilho);
                    return;
                }
            }
        }
    }

    moveDireita(noAtual, i);
    noAtual->filhos[i] = criaNo(str);
    noAtual->filhos[i]->isPalavra = 1;
    noAtual->numFilhos++;
}