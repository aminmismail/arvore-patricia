#include "arquivo.h"
#include "patricia.h"

// Realiza a impressão do menu na tela
// Pré-condição: nenhuma
// Pós-condição: menu impresso na tela
void imprime_menu(){
    printf("\n\tMenu de Opcoes:\n\n");
    printf("1.  Carregar arquivo de texto\n");
    printf("2.  Consultar palavra\n");
    printf("3.  Imprimir dicionario\n");
    printf("4.  Carregar arquivo de stopwords\n");
    printf("5.  Imprimir subarvore por niveis\n");
    printf("6.  Imprimir arvore completa por niveis\n");
    printf("7.  Inserir palavra manualmente\n");
    printf("8.  Remover palavra manualmente\n");
    printf("0.  Sair\n\n");

    printf("Digite a opcao desejada: ");
}

FILE* loadPath(){
    FILE *fr;
    char path[50];
    do{
        printf("Nome do arquivo:");
        scanf("%s%*c", path);
        fr = fopen(path, "r");
    }
    while(fr == NULL);
    return fr;
}

int validateText(char *text){
    char *aux;
    for(aux = text; *aux != '\0'; aux++){
        if(isalpha(*aux)){
            *aux = tolower(*aux);
        }
        else return 0;
    }
    return 1;
}

//Le o caminho do arquivo passado por input
//Pre-condicao: Um caminho para um arquivo existente
//Pos-condicao: Registro dos itens nos arquivos binarios
void carregaArquivo (int op, No* raiz){
    FILE *fr = loadPath();
    char text[100];
    int total = 0;
    while (fscanf(fr, "%[^\n]%*c", text) != EOF) {
        if (validateText(text)) {
            if (op == 0){
                printf("Inserindo palavra: %s\n", text);
                //inserePalavra(text, raiz);
                inserir(raiz, text);
            }
            else {
                printf("Removendo palavra: %s\n", text);
                remover(raiz, text);
                //remove a palavra
            }
        }
        else printf("Palavra ignorada: %s\n",text);
    }
}