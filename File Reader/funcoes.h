#define MAXNOME 100
/******************************************************ESTRUTURAS******************************************************/

//Estrutura usada para ler do ficheiro binário.
struct equipa {
    char nome[MAXNOME];
    int pontuacao;
};

/********************************************************STATIC********************************************************/

//Nomes dos ficheiros gerados pelo programa principal para os ficheiros com as classificacoes finais e com o campeao, os promovidos e despromovidos, respetivamente.
static char n_classificacoes[MAXNOME], n_campeao[MAXNOME];

/********************************************************FUNCOES*******************************************************/

void criar_ficheiro_classificacoes(char n[]);

void criar_ficheiro_campeao(char n[]);

/**************************************************PROGRAMAÇÃO*ROBUSTA*************************************************/

int verificar_extensao(char n[], const char extensao[]);

void input_check_classificacoes(char n[]);

void input_check_campeao(char n[]);

/**********************************************************************************************************************/