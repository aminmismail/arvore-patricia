#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

int main() {

    int opcao;
    char text[50];

    while(1){
        imprime_menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 0:
                printf("Fim do Programa\n");
                return 0;
            case 1:
                //Carregar arquivo de texto
                carregaArquivo(0);
                break;
            case 2:
                //Consultar palavra
                printf("Entre com a palavra prefixo: ");
                scanf("%*c%s%*c", text);
                //consultaPalavra(text);
                break;
            case 3:
                //Imprimir dicionario
                //imprimeDicionario();
                break;
            case 4:
                //Carregar arquivo de stopwords
                //carregaArquivo(1);
                break;
            case 5:
                //Imprimir subarvore por niveis
                //imprimeNivel();
                break;
            default:
                printf("Entrada invalida\n");
                break;
        }
        system("pause");
    }
}
