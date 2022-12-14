/*∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */
/* Aluno : 		 Victor de Oliveira Bezerra | Victor Manuel Castro Silva | Victor Mendes de Souza */
/* Matricula :       20221045050567 			|		    20221045050419 	     |	   20221045050583     */
/* Avaliacao 04: Trabalho Final                                                                 */
/* 04.505.23 − 2022.2 − Prof. Daniel Ferreira                                                   */
/* Compilador : GCC (tdm64-1) 10.3.0                                                            */
/*∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */

#include <stdio.h>
#include <stdlib.h>

struct pgm{																											//declara a estrutura pgm
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};

//funcoes de pgm.c
void readPGMImage(struct pgm *, char *filename);								

//funcoes de operations.c
int mapElements(int valor, int vf1, int vf2);
int *gerarSCM(struct pgm *pio, struct pgm *pioF, int quant);