/*∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */
/* Aluno : 		 Victor de Oliveira Bezerra | Victor Manuel Castro Silva | Victor Mendes de Souza */
/* Matricula :       20221045050567 			|		    20221045050419 	     |	   20221045050583     */
/* Avaliacao 04: Trabalho Final                                                                 */
/* 04.505.23 − 2022.2 − Prof. Daniel Ferreira                                                   */
/* Compilador : GCC (tdm64-1) 10.3.0                                                            */
/*∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */

#include "pgm.h"

int mapElements(int valor, int vf1, int vf2)
{
  int y;                                                        //Declarando variavel y.
  y = (vf2 * valor) / vf1;                                      //Calculo para mapear o valor de y (Famosa regra de 3).
  return y;
}

int *gerarSCM(struct pgm *pio, struct pgm *pioF, int quant)     //Funcao para gerar o vetor da matriz SCM. Recebendo 2 struct pgm,
{                                                               //uma para a imagem normal e a outra para filtrada, e o nivel de quantizacao.

  int matrizSCM[quant + 1][quant + 1];                          //Declaracao da matriz SCM.

  int *vetorSCM;                                                //Declaracao do vetor SCM.
  vetorSCM = malloc(quant * quant * sizeof(int));

  for (int i = 0; i < quant; i++)                               //Percorrer a matriz SCM, preenchendo tudo com 0.
  {
    for (int j = 0; j < quant; j++)
    {
      matrizSCM[i][j] = 0;
    }
  }

  int u = 0, l = 0;                                             //Declaracao de 2 variaveis auxiliares para iteracao
  for (int i = 0; i < pio->r; i++)                              //Percorrer o tamanho da imagem PGM
  {
    for (int j = 0; j < pio->c; j++)
    {
      matrizSCM[mapElements(*(pioF->pData + u), pio->mv, quant)][mapElements(*(pio->pData + u), pio->mv, quant)]++;
          //Acrescenta 1 de valor da matriz SCM, na posicao calculada pela funcao mapElements, com os parametros
          //*(pioF->pData + u), que equivale ao valor na faixa do pio->mv da imagem;
          //pio->mv, que é o maior valor que o pixel da imagem pode ter;
          //quant, que é o nivel de quantizacao passado pelo usuario;
          //para as linhas, já para as colunas troca *(pioF->pData + u) por *(pio->pData + u), para ser usado a imagem Filtrada.
      u++;
    }
  }

  for (int i = 0; i < quant; i++)                               //Percorre a matriz SCM.
  {
    for (int j = 0; j < quant; j++)
    {
      vetorSCM[l] = matrizSCM[i][j];                            //Vetor SCM recebe o valor correspondente a posicao da matriz.
      l++;
    }
  }

  return vetorSCM;
}