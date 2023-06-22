#include "arquivo.h"
#include "patricia.h"

int main() {

    int opcao;
    char text[50];
    No* raiz = NULL;
    raiz = criaNoRaiz();

    while(1){
        imprime_menu();
        scanf("%d%*c", &opcao);
        switch (opcao) {
            case 0:
                printf("Fim do Programa\n");
                return 0;
            case 1:
                //Carregar arquivo de texto
                carregaArquivo(0, raiz);
                break;
            case 2:
                //Consultar palavra
                printf("Entre com a palavra prefixo: ");
                scanf("%s%*c", text);
                consultaPalavras(raiz, text, 1);
                break;
            case 3:
                //Imprimir dicionario
                consultaPalavras(raiz, "", 0);
                break;
            case 4:
                //Carregar arquivo de stopwords
                carregaArquivo(1, raiz);
                break;
            case 5:
                //Imprimir subarvore por niveis
                printf("Entre com a palavra: ");
                scanf("%s%*c", text);
                No* no = buscaPrefixo(raiz, text);
                if(no == NULL) printf("Prefixo nao encontrado!\n");
                else imprime_por_niveis(no, text);
                break;
            case 6:
                //Verifica se uma palavra existe
                imprime_por_niveis(raiz, "");
                break;
            default:
                printf("Entrada invalida\n");
                break;
        }
        system("pause");
    }
}
