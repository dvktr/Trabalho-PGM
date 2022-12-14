/*∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */
/* Aluno : 		 Victor de Oliveira Bezerra | Victor Manuel Castro Silva | Victor Mendes de Souza */
/* Matricula :       20221045050567 			|		    20221045050419 	     |	   20221045050583     */
/* Avaliacao 04: Trabalho Final                                                                 */
/* 04.505.23 − 2022.2 − Prof. Daniel Ferreira                                                   */
/* Compilador : GCC (tdm64-1) 10.3.0                                                            */
/*∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */

#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

void readPGMImage(struct pgm *pio, char *filename)										//Funcao para ler uma imagem em pgm.
{

	FILE *fp;																														//Declaracao
	char ch;																														//de variaveis.

	if (!(fp = fopen(filename, "r")))																		//Verifica se consegue ler o arquivo.
	{
		perror("Erro.");																									//Apresenta erro se houver.
		exit(1);
	}

	if ((ch = getc(fp)) != 'P')																					//Verifica se esta no formato certo.
	{
		puts("A imagem fornecida não está no formato pgm");
		exit(2);
	}

	pio->tipo = getc(fp) - 48;																					//pio->tipo recebe o valor ASCII depois do "P" e subtrai de 48.

	fseek(fp, 1, SEEK_CUR);																							//avanca 1 byte depois de ler o tipo, pulando o \n.

	while ((ch = getc(fp)) == '#')																			//pula todos os #(comentarios) e depois o \n.
	{
		while ((ch = getc(fp)) != '\n')
			;
	}

	fseek(fp, -1, SEEK_CUR);																						//apos verificacao da "#", volta 1 casa para nao pular nenhum dado.

	fscanf(fp, "%d %d", &pio->r, &pio->c);															//pega os valores do tamanho da matriz(linha x coluna).

	if (ferror(fp))																											//verifica se tem erro no arquivo.
	{
		perror(NULL);
		exit(3);
	}
	fscanf(fp, "%d", &pio->mv);																					//pega o valor do mv da imagem
	fseek(fp, 0, SEEK_CUR);

	pio->pData = (unsigned char *)malloc(pio->r * pio->c * sizeof(unsigned char) * sizeof(unsigned char)); //aloca memoria para o pData

	switch (pio->tipo)
	{
	case 2:
		puts("Lendo imagem PGM (dados em texto)");												//verifica se é em texto
		for (int k = 0; k < (pio->r * pio->c); k++)
		{
			fscanf(fp, "%hhu", pio->pData + k);
		}
		break;
	case 5:
		puts("Lendo imagem PGM (dados em binário)");											//verifica se é em binario
		fread(pio->pData, sizeof(unsigned char), pio->r * pio->c, fp);
		break;
	default:
		puts("Não está implementado");
	}

	fclose(fp);
}

