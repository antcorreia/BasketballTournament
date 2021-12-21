#define MAXNOME 100

/********************************************************STATIC********************************************************/

//Variáveis que representam os nomes dos ficheiros com as equipas, resultados, e dos outputs, respetivamente.
static char n_equipas[MAXNOME], n_resultados[MAXNOME], n_output1[MAXNOME], n_output2[MAXNOME];

//Raiz da fila.
static struct elem_fila *raiz;

/******************************************************ESTRUTURAS******************************************************/

//Estrutura com o nome e a pontuacao da equipa.
struct equipa {
    char nome[MAXNOME];
    int pontuacao;
};

//Estrutura usada para guardar os elementos da fila.
struct elem_fila {
    struct equipa equipa;
    struct elem_fila *equipa_seguinte;
};

/*********************************************************FILA*********************************************************/

void inicializar_fila();

int colocar(struct equipa equipa);

void retirar(int *pvazio);

/*******************************************************FUNCOES********************************************************/

int my_atoi(char string[]);

void guardar_equipas(char equipas[]);

void adicionar_pontos(char equipa[], int pontos);

void atribuir_pontos(char equipas[], char resultados[]);

void devolver_equipas(char output_1[], char output_2[]);

void limpar_fila();

/*************************************************PROGRAMACAO*ROBUSTA**************************************************/

int verificar_extensao(char n[], const char extensao[]);

void input_check_equipas(char n[]);

void input_check_resultados(char n[]);

void output_check_classificacoes(char n[]);

void output_check_campeao(char n[]);

void verificar_equipas(char n[]);

void verificar_resultados(char n[]);

void verificar_linhas(char n1[], char n2[]);

/**********************************************************************************************************************/