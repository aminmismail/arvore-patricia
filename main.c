#include "arquivo.h"
#include "patricia.h"

int main() {

    int opcao;
    char text[50];
    No* raiz = NULL;
    raiz = criaNoRaiz();

    No* f1 = criaNoFinal("bras");
    f1->numFilhos = 2;
    f1->isFinal = 0;
    f1->isPalavra = 0;
    No* f4 = criaNoFinal("falso");
    f4->numFilhos = 2;
    f4->isFinal = 0;
    f4->isPalavra = 1;
    No* f2 = criaNoFinal("il");
    No* f3 = criaNoFinal("ao");
    No* f5 = criaNoFinal("atim");
    No* f6 = criaNoFinal("zetas");
    raiz->numFilhos = 2;
    raiz->filhos[0] = f1;
    raiz->filhos[1] = f4;
    f1->filhos[0] = f3;
    f1->filhos[1] = f2;
    f4->filhos[0] = f5;
    f4->filhos[1] = f6;


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
                //consultaPalavra(text, raiz);
                break;
            case 3:
                //Imprimir dicionario
                imprimeDicionario(raiz);
                break;
            case 4:
                //Carregar arquivo de stopwords
                carregaArquivo(1, raiz);
                break;
            case 5:
                //Imprimir subarvore por niveis
                //imprimeNivel(raiz);
                break;
            default:
                printf("Entrada invalida\n");
                break;
        }
        system("pause");
    }
}
