//  Este programa recebe dois ficheiros, cada linha desses ficheiros representa um jogo. No primeiro ficheiro cada linha
//contém os nomes das duas equipas que se defrontaram nesse jogo, no segundo cada linha contém o número de golos que
//cada equipa marcou. Após receber estes ficheiros o programa compara percorre o primeiro ficheiro guardando numa fila
//todas as equipas e atribui-lhes pontuação 0. De seguida, analisa os dois ficheiros recebidos linha a linha e atribui
//corretamente os pontos ganhos por cada vitória ou derrota. Por fim, o ficheiro percorre a fila guardando num terceiro
//ficheiro pedido ao utilizador, por ordem de pontos, as equipas guardadas na fila. Ao mesmo tempo guarda num quarto e
//último ficheiro, também pedido ao utilizador, as duas equipas com mais e menos pontos.
//  Como reforço do meu programa, para evitar possiveis erros, ao pedir os ficheiros ao utilizador, verifico se a extenção
//do mesmo é a pretendida, se o ficheiro existe e, no caso dos ficheiros que vão ser devolvidos, se não existirem os
//indicados pelo utilizador, pergunto se quer que seja criado um com esse nome. Ao receber os ficheiros, verifico ainda
//se ambos estão corretamente estruturados (EQUIPA1#EQUIPA2), se têm o mesmo número de linhas, se existem linhas vazias
//nos mesmos e, no caso do ficheiro com os resultados, se contém apenas números e se não há empastes.
//  Para efeitos de teste usei os ficheiros "equipas.txt"*, "resultados.txt"**, "classificacoes.bin"*** e "campeao.bin"****, os
//quais estão incluídos no projeto.
//
//   * Ficheiro que contém os nomes das equipas que se defrontaram.
//  ** Ficheiro que contém os resultados dos jogos.
// *** Ficheiro no qual vão ser escritas as classificações finais.
//**** Ficheiro no qual vai ser escrito o campeão, assim como as equipas que subiram e desceram de divisão.

#include "funcoes.h"

int main(void) {
    inicializar_fila();

    input_check_equipas(n_equipas);
    verificar_equipas(n_equipas);

    input_check_resultados(n_resultados);
    verificar_resultados(n_resultados);

    verificar_linhas(n_equipas, n_resultados);

    output_check_classificacoes(n_output1);
    output_check_campeao(n_output2);

    guardar_equipas(n_equipas);
    atribuir_pontos(n_equipas, n_resultados);
    devolver_equipas(n_output1, n_output2);
    limpar_fila();
}
