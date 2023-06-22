#include "patricia.h"
#include "arquivo.h"

// Verifica se str1 é um prefixo de str2
// Pré-condição: nenhuma
// Pós-condição: retorna 1 se str1 é um prefixo de str2, 0 caso contrário
int isPrefixo(const char* str1, const char* str2) {
    return (strncmp(str1, str2, strlen(str1)) == 0);
}

// Cria um nó raiz da árvore Patricia
// Pré-condição: nenhuma
// Pós-condição: retorna um ponteiro para o nó raiz criado
No* criaNoRaiz(){
    int i;
    No* aux = (No*) malloc(sizeof(No));
    for(i=0; i < numFilhosNo; i++) aux->filhos[i] = NULL;
    aux->isPalavra = 0;
    aux->numFilhos = 0;
    strcpy(aux->texto, "");
    return aux;
}

// Converte a palavra word para letras minúsculas
// Pré-condição: nenhuma
// Pós-condição: a palavra word é convertida para letras minúsculas
void lowerWord(char word[]){
    int i, len = strlen(word);
    for(i=0; i < len; i++) word[i] = tolower(word[i]);
}


void printVet(char vet[][50], int n){
    int i = 0;
    printf("Total: %d\n",n);
    for(; i < n; i++){
        printf("%s", vet[i]);
        if(i < n-1) printf(", ");
    }
    printf("\n");
}


void consultaPalavrasAux(No* no, char *word, char* prefix, int* count, char vet[][50], int op){
    int i;
    if (no == NULL || (op == 1 && *count >= 10)){
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
        if((op == 1 && isPrefixo(prefix,word)) || op == 0){
            strcpy(vet[*count], word);
            (*count)++;
        }
    }

    for (i = 0; i < no->numFilhos; i++) {
        consultaPalavrasAux(no->filhos[i], word, prefix, count, vet, op);
    }

    word[len] = '\0';
}


void consultaPalavras(No* raiz, char* prefix, int op){
    char word[100] = {}, vet[10000][50] = {};
    lowerWord(prefix);
    int count = 0;
    consultaPalavrasAux(raiz, word, prefix, &count, vet, op);
    printVet(vet, count);
}


//Move os filhos de um nó para a direita a partir de uma pos
void moveDireita(No* no, int pos){
    int i = no->numFilhos;
    for(; i >= pos; i--) no->filhos[i+1] = no->filhos[i];
}

//Move os filhos de um nó para a esquerda a partir de uma pos
void moveEsquerda(No* no, int pos){
    int i = pos;
    for(; i > no->numFilhos; i++) no->filhos[i] = no->filhos[i+1];
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


void removeNo(No* no, int i){
    no->numFilhos--;
    for(; i < no->numFilhos; i++) no->filhos[i] = no->filhos[i+1];
    no->filhos[i] = NULL;
    free(no->filhos[i]);
}


// Remove uma palavra da arvore
void remover(No* no, char* palavra) {
    int i;
    for (i = 0; i < no->numFilhos; i++) {
        if (palavra[0] == no->filhos[i]->texto[0]) {
            if (strcmp(palavra, no->filhos[i]->texto) == 0) {
                if (no->filhos[i]->numFilhos != 0){
                    no->filhos[i]->isPalavra = 0;
                }
                else if (no->filhos[i]->isPalavra){
                    removeNo(no, i);
                    return;
                }
            }
            else {
                int k;
                for(k=0; palavra[k] == no->filhos[i]->texto[k]; k++);
                remover(no->filhos[i], palavra + k);
                if (no->filhos[i]->numFilhos == 0 && no->filhos[i]->isPalavra == 0) {
                    removeNo(no, i);
                    return;
                }
            }
        }
    }
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

// Busca um prefixo na árvore
// Pré-condição: no aponta para um nó válido, str é o prefixo a ser buscado
// Pós-condição: retorna um ponteiro para o nó que representa o prefixo buscado, ou NULL caso não seja encontrado
No* buscaPrefixo(No* no, char* str, int* nivel){
    No* noAtual = no;
    int i;
    if(noAtual->numFilhos == 0) return NULL;
    if(strcmp(no->texto, "") == 0){
        printf("Nivel 0: (-:%d)\n", no->numFilhos);
        *nivel += 1;
    }
    //Percorre os filhos do nó atual
    for (i = 0; i < noAtual->numFilhos ; i++) {
        if (str[0] == noAtual->filhos[i]->texto[0]){
            int k = 0;
            //Percorre o texto do nó filho
            while (str[k] != '\0' && noAtual->filhos[i]->texto[k] != '\0' && str[k] == noAtual->filhos[i]->texto[k]) {
                k++;
            }
            //Se o texto do nó e do filho terminaram
            if (str[k] == '\0'){
                return noAtual->filhos[i];
            }
            //Se o texto do no terminou mas o novo ainda nao
            if (str[k] != '\0' && noAtual->filhos[i]->texto[k] == '\0'){
                printf("Nivel %d: ", *nivel);
                printf("(%s:%d)\n", no->filhos[i]->texto, no->numFilhos);
                *nivel += 1;
                return buscaPrefixo(noAtual->filhos[i], str + k, nivel);
            }
            //Se o texto do no e do filho ainda nao terminaram
            if (str[k] != '\0' && noAtual->filhos[i]->texto[k] != '\0'){
                return NULL;
            }
        }
    }
    return NULL;
}


// Imprime a árvore por níveis
// Pré-condição: Arquivo de índices aberto e contendo pelo menos o cabeçalho gravado
// Pós-condição: Impressão da árvore por níveis
void imprime_por_niveis(No* raiz, char* str, int c){
    if(raiz == NULL){
        printf("Arvore vazia\n");
        return;
    }
    int nivel = c;
    FILA* fila = cria_fila();

    enqueue(fila, raiz);
    enqueue(fila, NULL);
    printf("Nivel %d: ", nivel);
    while (!fila_vazia(fila)) {
        No* no = dequeue(fila);

        if (no == NULL){
            printf("\n");
            if (!fila_vazia(fila)) {
                ++nivel;
                printf("Nivel %d: ", nivel);
                enqueue(fila, NULL);
            }
            continue;
        }
        int len = strlen(str);
        /*if(no == raiz && (strcmp(str + (len - strlen(no->texto)), no->texto) == 0)){
            printf("(-:%d)", no->numFilhos);
        }*/
        printf("(%s:%d) ", no->texto, no->numFilhos);
        if (no->numFilhos != 0) {
            int n = no->numFilhos;
            for (int i = 0; i < n; i++) {
                enqueue(fila, no->filhos[i]);
            }
        }
    }
    free(fila);
}

// cria uma fila
// Pré-condição: nenhuma
// Pós-condição: fila criada
FILA* cria_fila(){
    FILA *f = (FILA*)malloc(sizeof(FILA));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

//pré-requisitos: Recebe um ponteiro não nulo para fila
//pós-requisitos: Retorna 1 se a fila for vazio e 0 se não
int fila_vazia(FILA *f){
    return f->inicio == NULL;
}

// enfileira uma chave na fila
// Pré-condição: fila existente e chave a ser inserida
// Pós-condição: fila atualizada com chave
void enqueue(FILA *f, No* no){
    NO_FILA* aux = (NO_FILA*)malloc(sizeof(NO_FILA));
    aux->no = no;
    aux->prox = NULL;
    if(fila_vazia(f)){
        f->inicio = aux;
    }else{
        f->fim->prox = aux;
    }
    f->fim = aux;
}

// desenfileira uma chave na fila
// Pré-condição: fila existente e chave a ser removida
// Pós-condição: fila atualizada sem a chave
No* dequeue(FILA* f){
    NO_FILA* aux = f->inicio;
    No* no = f->inicio->no;
    if(f->inicio == f->fim){
        f->fim = NULL;
    }
    f->inicio = f->inicio->prox;
    free(aux);
    return no;
}
