/******************************************************BIBLIOTECAS*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/********************************************************FUNCOES*******************************************************/

//Lê do ficheiro binário e cria o ficheiro final com as classificações finais do campeonato.
//Parâmetros:
//1. Nome do ficheiro com as classificacoes finais.
void criar_ficheiro_classificacoes(char n[]) {
    struct equipa equipa1;
    FILE *input = fopen(n, "rb");

    printf("CLASSIFICACOES FINAIS:\n");
    while (fread(&equipa1, sizeof(struct equipa), 1, input)) printf("%s - %d\n", equipa1.nome, equipa1.pontuacao);

    printf("\n");

    fclose(input);
}

//Lê do ficheiro binário e cria o ficheiro final com o campeao, os promovidos e os despromovidos.
//Parâmetros:
//1. Nome do ficheiro com o campeao, os promovidos e os depromovidos.
void criar_ficheiro_campeao(char n[]) {
    struct equipa equipa1;
    FILE *input = fopen(n, "rb");

    fread(&equipa1, sizeof(struct equipa), 1, input);
    printf("CAMPEAO:\n%s\n\nPROMOVIDOS:\n%s\n", equipa1.nome, equipa1.nome);
    fread(&equipa1, sizeof(struct equipa), 1, input);
    printf("%s\n\nDESPROMOVIDOS:\n", equipa1.nome);
    fread(&equipa1, sizeof(struct equipa), 1, input);
    printf("%s\n", equipa1.nome);
    fread(&equipa1, sizeof(struct equipa), 1, input);
    printf("%s\n", equipa1.nome);

    fclose(input);
}

/**************************************************PROGRAMAÇÃO*ROBUSTA*************************************************/

//Verifica se a string "n" termina com a extensao "extensao", devolvendo 1 ou 0 caso isto se verifique ou não, respetivamente.
//Parâmetros:
//1. String que vai ter a sua extensão verificada.
//2. Extensao que a string deve ter.
int verificar_extensao(char n[], const char extensao[]) {
    if ((n[strlen(n) - 4]) != extensao[0]) return 0;
    if ((n[strlen(n) - 3]) != extensao[1]) return 0;
    if ((n[strlen(n) - 2]) != extensao[2]) return 0;
    if ((n[strlen(n) - 1]) != extensao[3]) return 0;

    return 1;
}

//Recebe o ficheiro binário com as classificacoes finais, verifica se existe e verifica se tem a extensao certa.
//Parâmetros:
//1. Nome do ficheiro que vai ser analisado.
void input_check_classificacoes(char n[]) {
    int exit_check1 = 0, exit_check2 = 0;
    FILE *f = NULL;

    while (f == NULL) {
        do {
            if ((exit_check2 > 0) && (exit_check2 < 3)) printf("O formato desse ficheiro nao e .bin, tem mais %d tentativas\n", 3 - exit_check2);
            printf("Qual o nome do ficheiro que contem as classificacoes?\n");
            scanf("%s", n);

            if (exit_check2++ == 2){
                printf("Numero de tentativas excedido, o programa ira encerrar");
                exit(1);
            }
        }while (!verificar_extensao(n, ".bin"));
        exit_check2 = 5;

        f = fopen(n, "rb");
        if (f == NULL) {
            if (exit_check1 < 2) printf("Esse ficheiro nao existe, tem mais %d tentativas.\n", 2 - exit_check1);
            if (exit_check1++ == 2) {
                printf("Numero de tentativas excedido, o programa ira encerrar");
                exit(1);
            }
        }
    }

    fclose(f);
}

//Recebe o ficheiro binário com o campeao, os promovidos e os despromovidos, verifica se existe e verifica se tem a extensao certa.
//Parâmetros:
//1. Nome do ficheiro que vai ser analisado.
void input_check_campeao(char n[]) {
    int exit_check1 = 0, exit_check2 = 0;
    FILE *f = NULL;

    while (f == NULL) {
        do {
            if ((exit_check2 > 0) && (exit_check2 < 3)) printf("O formato desse ficheiro nao e .bin, tem mais %d tentativas\n", 3 - exit_check2);
            printf("Qual o nome do ficheiro que contem o campeao, os promovidos e os despromovidos?\n");
            scanf("%s", n);

            if (exit_check2++ == 2){
                printf("Numero de tentativas excedido, o programa ira encerrar");
                exit(1);
            }
        }while (!verificar_extensao(n, ".bin"));
        exit_check2 = 5;

        f = fopen(n, "rb");
        if (f == NULL) {
            if (exit_check1 < 2) printf("Esse ficheiro nao existe, tem mais %d tentativas.\n", 2 - exit_check1);
            if (exit_check1++ == 2) {
                printf("Numero de tentativas excedido, o programa ira encerrar");
                exit(1);
            }
        }
    }

    fclose(f);
}

/**********************************************************************************************************************/