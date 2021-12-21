//  Este programa recebe dois ficheiros, já criados por outro programa e devolve as informações desses mesmos ficheiros
//na coinsola, o que torna possível a sua leitura.
//  Como reforço do meu programa, para evitar possiveis erros, ao pedir os ficheiros ao utilizador, verifico se a extenção
//do mesmo é a pretendida e se o ficheiro existe.
//  Para efeitos de teste usei os ficheiros "classificacoes.bin"*, "campeao.bin"**, os quais estão incluídos no projeto.
//
//   * Ficheiro que contém as classificacoes finais.
//  ** Ficheiro que contém o campeao, os promovidos e despromovidos.

#include "funcoes.h"

int main() {
    input_check_classificacoes(n_classificacoes);
    input_check_campeao(n_campeao);

    criar_ficheiro_classificacoes(n_classificacoes);
    criar_ficheiro_campeao(n_campeao);
}
