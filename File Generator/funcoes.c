#define MAXNOME 100

/*****************************************************BIBLIOTECAS******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcoes.h"

/*********************************************************FILA*********************************************************/

//Inicializa a fila.
//Parâmetros:
//NENHUM
void inicializar_fila(void) {
    raiz = NULL;
}


//Coloca a estrutura "equipa" na fila.
//Parâmetros:
//1. Equipa que vai ser colocada na fila.
int colocar(struct equipa equipa) {
    struct elem_fila * aux;

    aux = (struct elem_fila *) malloc(sizeof(struct elem_fila));
    if (aux == NULL) return 1;

    aux->equipa = equipa;
    aux->equipa_seguinte = raiz;
    raiz = aux;

    return 0;
}


//Retira a ultima estrutura da fila.
//Parâmetros:
//1. Inteiro que vai ter o valor 1 ou 0 dependendo do estado da fila.
void retirar(int *pvazio) {
    struct elem_fila *prox, *anterior;

    if (raiz == NULL) {
        *pvazio = 1;
        return;
    }

    *pvazio = 0;

    anterior = NULL;
    for (prox = raiz; prox->equipa_seguinte != NULL; prox = prox->equipa_seguinte) anterior = prox;

    if (anterior == NULL) {
        free(raiz);
        raiz = NULL;
    }
    else {
        anterior->equipa_seguinte = NULL;
        free(prox);
    }
}

/*******************************************************FUNCOES********************************************************/

//Atoi que não produz avisos.
//Parâmetros:
//1. String que vai ser transformada em inteiro.
int my_atoi(char string[]) {
    int i, inteiro = 0;

    for (i = 0; i < (int)strlen(string); i++){
        inteiro += (string[i] - '0') * (int)pow(10, strlen(string) - 1 - i);
    }

    return inteiro;
}


//Coloca todas as equipas na fila e atribui o valor 0 à sua pontuação.
//Parâmetros:
//1. Nome do ficheiro que contém as equipas.
void guardar_equipas(char equipas[]) {
    char c, palavra[MAXNOME];
    int count = 0;
    struct elem_fila *prox;

    FILE *f = fopen(equipas, "r");

    while (((c = (char)fgetc(f)) != '#') && (c != '\n')) palavra[count++] = c;
    palavra[count] = '\0';
    count = 0;

    struct equipa equipa;
    equipa.nome[0] = '\0';
    equipa.pontuacao = 0;
    strcpy(equipa.nome, palavra);
    colocar(equipa);

    while (!feof(f)){
        while (((c = (char)fgetc(f)) != '#') && (c != '\n') && (c != EOF)) palavra[count++] = c;
        palavra[count] = '\0';
        count = 0;
        equipa.pontuacao = 0;
        strcpy(equipa.nome, palavra);

        for (prox = raiz; prox->equipa_seguinte != NULL; prox = prox->equipa_seguinte) if (!strcmp(prox->equipa.nome, palavra)) break;

        if ((strcmp(prox->equipa.nome, palavra)) != 0){
            strcpy(equipa.nome, palavra);
            colocar(equipa);
        }
    }

    fclose(f);
}


//Adiciona o número "pontos" à pontuação da equipa "equipa".
//Parâmetros:
//1. Nome da equipa à qual vão ser adiconados os pontos.
//2. Número de pontos a adicionar.
void adicionar_pontos(char equipa[], int pontos) {
    struct elem_fila *prox;

    for (prox = raiz; prox->equipa_seguinte != NULL; prox = prox->equipa_seguinte){
        if (!strcmp(prox->equipa.nome,equipa)){
            prox->equipa.pontuacao += pontos;
            break;
        }
    }
}


//Percorre os dois ficheiros recebidos pelo utilizador, atribuindo os respetivos pontos às equipas vencedoras e perdedoras.
//Parâmetros:
//1. Nome do ficheiro que contém as equipas.
//2. Nome do ficheiro que contém os resultados.
void atribuir_pontos(char equipas[], char resultados[]) {
    char c, equipa1[100], equipa2[100], string_temporaria[100];
    int count = 0, resultado1, resultado2;

    FILE *f_equipas = fopen(equipas, "r");
    FILE *f_resultados = fopen(resultados, "r");

    while (!feof(f_equipas)){
        while (((c = (char)fgetc(f_equipas)) != '#') && (c != '\n') && (c != EOF)) equipa1[count++] = c;
        equipa1[count] = '\0';
        count = 0;

        while (((c = (char)fgetc(f_equipas)) != '#') && (c != '\n') && (c != EOF)) equipa2[count++] = c;
        equipa2[count] = '\0';
        count = 0;

        while (((c = (char)fgetc(f_resultados)) != '#') && (c != '\n') && (c != EOF)) string_temporaria[count++] = c;
        string_temporaria[count] = '\0';
        count = 0;
        resultado1 = my_atoi(string_temporaria);

        while (((c = (char)fgetc(f_resultados)) != '#') && (c != '\n') && (c != EOF)) string_temporaria[count++] = c;
        string_temporaria[count] = '\0';
        count = 0;
        resultado2 = my_atoi(string_temporaria);

        if (resultado1 > resultado2){
            adicionar_pontos(equipa1, 2);
            adicionar_pontos(equipa2, 1);
        }
        else{
            adicionar_pontos(equipa2, 2);
            adicionar_pontos(equipa1, 1);
        }
    }
}


//Escreve os ficheiros binários que serão usados no programa autónomo.
//Parâmetros:
//1. Nome do ficheiro no qual vão ser guardados os resultados finais.
//2. Nome do ficheiro no qual vão ser apresentadas as equipas promovidas e despromovidas.
void devolver_equipas(char output_1[], char output_2[]) {
    struct elem_fila *prox;
    struct equipa maior;
    int check1 = 0, check2 = 1;

    FILE *output1 = fopen(output_1, "wb");
    FILE *output2 = fopen(output_2, "wb");

    while (check1 != check2){
        check1 = 0;
        check2 = 1;

        maior = raiz->equipa;
        for (prox = raiz; prox->equipa_seguinte != NULL; prox = prox->equipa_seguinte){
            check1++;
            if (prox->equipa.pontuacao > maior.pontuacao) maior = prox->equipa;
            if (prox->equipa.pontuacao == -2) check2++;
        }

        fwrite(&maior, sizeof(struct equipa), 1, output1);
        if (check2 == 1) fwrite(&maior, sizeof(struct equipa), 1, output2);
        if (check2 == 2) fwrite(&maior, sizeof(struct equipa), 1, output2);
        if (check1 - check2 == 1) fwrite(&maior, sizeof(struct equipa), 1, output2);
        if (check1 - check2 == 0) fwrite(&maior, sizeof(struct equipa), 1, output2);

        for (prox = raiz; prox->equipa_seguinte != NULL; prox = prox->equipa_seguinte){
            if (!strcmp(prox->equipa.nome,maior.nome)){
                prox->equipa.pontuacao = -2;
                break;
            }
        }
    }

    fclose(output1);
    fclose(output2);
}


//Limpa a fila.
//Parâmetros:
//NENHUM
void limpar_fila(void) {
    int vazio = 0;

    while(!vazio){
        retirar(&vazio);
    }
}

/*************************************************PROGRAMACAO*ROBUSTA**************************************************/

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


//Verifica se o ficheiro com o nome indicado com os nomes das equipas existe e se tem a extensao certa.
//Parâmetros:
//1. Nome do ficheiro a ser verificado.
void input_check_equipas(char n[]) {
    int exit_check1 = 0, exit_check2 = 0;
    FILE *f = NULL;

    while (f == NULL) {
        do {
            if ((exit_check2 > 0) && (exit_check2 < 3)) printf("O formato desse ficheiro nao e .txt, tem mais %d tentativas\n", 3 - exit_check2);
            printf("Qual o nome do ficheiro com as equipas?\n");
            scanf("%s", n);

            if (exit_check2++ == 2){
                printf("Numero de tentativas excedido, o programa ira encerrar");
                exit(1);
            }
        }while (!verificar_extensao(n, ".txt"));
        exit_check2 = 5;

        f = fopen(n, "r");
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


//Veririca se o ficheiro com o nome indicado com os resultados dos jogos existe e se tem a extensao certa.
//Parâmetros:
//1. Nome do ficheiro a ser verificado.
void input_check_resultados(char n[]) {
    int exit_check = 0, exit_check2 = 0;
    FILE *f = NULL;

    while (f == NULL) {
        do {
            if ((exit_check2 > 0) && (exit_check2 < 3)) printf("O formato desse ficheiro nao e .txt, tem mais %d tentativas\n", 3 - exit_check2);
            printf("Qual o nome do ficheiro com os resultados?\n");
            scanf("%s", n);

            if (exit_check2++ == 2){
                printf("Numero de tentativas excedido, o programa ira encerrar");
                exit(1);
            }
        }while (!verificar_extensao(n, ".txt"));
        exit_check2 = 5;

        f = fopen(n, "r");
        if (f == NULL) {
            if (exit_check < 2) printf("Esse ficheiro nao existe, tem mais %d tentativas.\n", 2 - exit_check);
            if (exit_check++ == 2) {
                printf("Numero de tentativas excedido, o programa ira encerrar");
                exit(1);
            }
        }
    }

    fclose(f);
}


//Verifica se o ficheiro com o nome indicado para guardar as classificacoes finais existe (caso nao exista pergunta se quer criá-lo).
//Parâmetros:
//1. Nome do ficheiro a ser verificado.
void output_check_classificacoes(char n[]) {
    int exit_check1 = 0, exit_check2 = 0, exit_check3 = 0;
    char confirmacao[MAXNOME];
    FILE *f = NULL;

    while (f == NULL) {
        if (exit_check2 > 0) printf("Tem mais %d tentativas\n", 3 - exit_check2);
        do {
            if ((exit_check3 > 0) && (exit_check3 < 3)) printf("O formato desse ficheiro nao e .txt, tem mais %d tentativas\n", 3 - exit_check3);
            printf("Qual o nome do ficheiro onde quer guardar as classificacoes finais?\n");
            scanf("%s", n);

            if (exit_check3++ == 2){
                printf("Numero de tentativas excedido, o programa ira encerrar");
                exit(1);
            }
        }while (!verificar_extensao(n, ".bin"));
        exit_check3 = 5;

        f = fopen(n, "r");
        if (f == NULL) {
            if (exit_check1 < 2) printf("Esse ficheiro nao existe, pretende criar um com este nome?\n");
            scanf("%s",confirmacao);
            while ((strcmp(confirmacao, "Sim") != 0) && (strcmp(confirmacao,"Nao") != 0)){
                if (exit_check1 < 3) printf("Essa resposta nao e valida, tem mais %d tentativas\n", 2-exit_check1++);
                scanf("%s",confirmacao);
                if (exit_check1 == 3) {
                    printf("Numero de tentativas excedido, o programa ira encerrar");
                    exit(1);
                }
            }

            if (!strcmp(confirmacao, "Sim")){
                f = fopen(n, "w");
                fclose(f);
                return;
            }
            else {
                if (exit_check2++ == 2) {
                    printf("Numero de tentativas excedido, o programa ira encerrar");
                    exit(1);
                }
            }
        }
    }

    fclose(f);
}


//Verifica se o ficheiro com o nome indicado para guardar o nome do campeao, dos promovidos e dos despromovidos existe (caso nao exista pergunta se quer criá-lo).
//Parâmetros:
//1. Nome do ficheiro a ser verificado.
void output_check_campeao(char n[]) {
    int exit_check1 = 0, exit_check2 = 0, exit_check3 = 0;
    char confirmacao[MAXNOME];
    FILE *f = NULL;

    while (f == NULL) {
        if (exit_check2 > 0) printf("Tem mais %d tentativas\n", 3 - exit_check2);
        do {
            if ((exit_check3 > 0) && (exit_check3 < 3)) printf("O formato desse ficheiro nao e .txt, tem mais %d tentativas\n", 3 - exit_check3);
            printf("Qual o nome do ficheiro onde quer guardar o campeao, os promovidos e os despromovidos?\n");
            scanf("%s", n);

            if (exit_check3++ == 2){
                printf("Numero de tentativas excedido, o programa ira encerrar");
                exit(1);
            }
        }while (!verificar_extensao(n, ".bin"));
        exit_check3 = 5;

        f = fopen(n, "r");
        if (f == NULL) {
            if (exit_check1 < 2) printf("Esse ficheiro nao existe, pretende criar um com este nome?\n");
            scanf("%s",confirmacao);
            while ((strcmp(confirmacao, "Sim") != 0) && (strcmp(confirmacao,"Nao") != 0)){
                if (exit_check1 < 3) printf("Essa resposta nao e valida, tem mais %d tentativas\n", 2-exit_check1++);
                scanf("%s",confirmacao);
                if (exit_check1 == 3) {
                    printf("Numero de tentativas excedido, o programa ira encerrar");
                    exit(1);
                }
            }

            if (!strcmp(confirmacao, "Sim")) {
                f = fopen(n, "w");
                fclose(f);
                return;
            }
            else {
                if (exit_check2++ == 2) {
                    printf("Numero de tentativas excedido, o programa ira encerrar");
                    exit(1);
                }
            }
        }
    }

    fclose(f);
}


//Verifica se o ficheiro com o nome indicado com os nomes das equipas está corretamente construido.
//Parâmetros:
//1. Nome do ficheiro a ser verificado.
void verificar_equipas(char n[]) {
    char c;
    int count = 0;

    FILE *f = fopen(n, "r");

    fseek(f, -1, SEEK_END);
    if (fgetc(f) == '\n'){
        printf("O ficheiro indicado contem uma ou mais linhas vazias .\n");
        exit(1);
    }
    rewind(f);

    while ((c = (char)fgetc(f)) != EOF){

        if (c == '#'){
            count++;
            if (count == 2){
                printf("O ficheiro indicado com os nomes das equipas nao esta no formato certo.\nTem de estar no formato EQUIPA1#EQUIPA2.\n");
                exit(1);
            }
        }
        if (c == '\n'){
            if (count == 0) {
                printf("O ficheiro indicado contem uma ou mais linhas vazias.\n");
                exit(1);
            }
            count = 0;
        }
    }

    fclose(f);
}


//Verifica se o ficheiro com o nome  indicado com os resultados dos jogos está corretamente construido.
//Parâmetros:
//1. Nome do ficheiro a ser verificado.
void verificar_resultados(char n[]) {
    char c, string_temporaria[MAXNOME];
    int count = 0, resultado1, resultado2;

    FILE *f = fopen(n, "r");

    fseek(f, -1, SEEK_END);
    if (fgetc(f) == '\n'){
        printf("O ficheiro indicado contem uma ou mais linhas vazias.\n");
        exit(1);
    }
    rewind(f);

    while ((c = (char)fgetc(f)) != EOF){

        if (c == '#'){
            if (++count == 2){
                printf("O ficheiro indicado nao esta no formato certo.\nTem de estar no formato RESULTADO1#RESULTADO2.\n");
                exit(1);
            }
        }
        if (c == '\n'){
            if (count == 0) {
                printf("O ficheiro indicado contem uma ou mais linhas vazias.\n");
                exit(1);
            }
            count = 0;
        }
        if (!isdigit(c) && (c != '#') && (c != '\n')){
            printf("O ficheiro indicado tem valores os quais nao sao numeros.\n");
            exit(1);
        }
    }

    rewind(f);
    count = 0;
    while (!feof(f)){
        while (((c = (char)fgetc(f)) != '#') && (c != '\n') && (c != EOF)) string_temporaria[count++] = c;
        string_temporaria[count] = '\0';
        count = 0;
        resultado1 = my_atoi(string_temporaria);

        while (((c = (char)fgetc(f)) != '#') && (c != '\n') && (c != EOF)) string_temporaria[count++] = c;
        string_temporaria[count] = '\0';
        count = 0;
        resultado2 = my_atoi(string_temporaria);

        if (resultado1 == resultado2){
            printf("O ficheiro que contem os resultados contem empates, o programa ira encerrar");
            exit(1);
        }
    }

    fclose(f);
}


//Verifica se os ficheiros com os nomes indicados têm o mesmo número de linhas e se têm mais do que 4 linhas.
//Parâmetros:
//1. Nome do primeiro ficheiro.
//2. Nome do segundo ficheiro.
void verificar_linhas(char n1[], char n2[]) {
    int count1 = 0, count2 = 0;
    FILE *f1 = fopen(n1, "r");
    FILE *f2 = fopen(n2, "r");

    while (!feof(f1)) if (fgetc(f1) == '\n') count1++;
    while (!feof(f2)) if (fgetc(f2) == '\n') count2++;

    if (count1 != count2){
        printf("Os ficheiros nao tem o mesmo numero de linhas, o programa ira encerrar");
        exit(1);
    }

    if ((count1 <= 4) || (count2 <=4)){
        printf("Os ficheiros tem de ter mais do que 4 equipas.");
        exit(1);
    }
}

/**********************************************************************************************************************/