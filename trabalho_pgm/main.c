/*∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗*/
/* Aluno : 		 Victor de Oliveira Bezerra | Victor Manuel Castro Silva | Victor Mendes de Souza */
/* Matricula :       20221045050567 			|		    20221045050419 	     |	   20221045050583     */
/* Avaliacao 04: Trabalho Final                                                                 */
/* 04.505.23 − 2022.2 − Prof. Daniel Ferreira                                                   */
/* Compilador : GCC (tdm64-1) 10.3.0                                                            */
/*∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include "pgm.h"

int main(int argc, char *argv[])
{
	struct pgm img;
	struct pgm imgF;

	clock_t begin, end;
	double time_per_img, time_total = 0;

	int quantizacao = (int)strtol(argv[1], NULL, 10);

	if (argc != 2)		//Verificacao dos args passados
	{
		printf("Formato: \n\n\t %s <nivel_de_quantizacao>\n\t Niveis = (7, 15, 31, 63, 127, 255)\n\n", argv[0]);
		exit(1);
	}

	begin = clock();	//Inicia o clock

	//Abrir a pasta das imagens normais para ler os nomes.
	DIR *d;
	struct dirent *dir;
	d = opendir("../oncotex_pgm");

	//Abrir a pasta das imagens filtradas para ler os nomes.
	DIR *dMean;
	struct dirent *dirMean;
	dMean = opendir("../oncotex_pgm_mean");

	int *vSCM = malloc(quantizacao * quantizacao * sizeof(int *)); //Vetor que vai receber a matriz SCM.

	char arq[1024] = "..\\oncotex_pgm\\";						//Variaveis auxiliares para 
	char arqMean[1024] = "..\\oncotex_pgm_mean\\";  //copiar o path das imagens.
	char tipo[1024] = "as";													//Variavel para receber o tipo da imagem.

	int qt = 0;																			//Variavel para contar a quantidade de arquivos.

	if (d && dMean)																	//Verificação se deu tudo certo para abrir as duas pastas.
	{

		FILE *arquivo;																//Declaracao e abertura do
		arquivo = fopen("arquivo.txt", "w");					//arquivo para escrever o vetor SCM.

		if (arquivo == NULL)													//Verificacao padrao
		{
			fprintf(stderr, "Erro ao tentar abrir arquivo.txt.");
			return 1;
		}

		fprintf(arquivo, "Quantizacao de nivel: %d\n", quantizacao);							//Escrever na primeira linha do arquivo o nivel de quant.

		while ((dir = readdir(d)) != NULL && (dirMean = readdir(dMean)) != NULL)	//Loop para enquanto tiver arquivos restantes nas 2 pastas.
		{
			if (!(dir->d_name[0] == '.'))																						//Verificacao se o nome do arquivo nao comeca com ".".
			{
				strcpy(tipo, dir->d_name);																						//Copia o nome do arquivo para variavel tipo.
				strcat(arq, dir->d_name);																							//Concatena a string do path com o nome do arquivo.(Ex: "..\\oncotex_pgm\\imagem.pgm").
				readPGMImage(&img, arq);																							//Chama a funcao para ler o pgm.
				strcpy(arq, "..\\oncotex_pgm\\");																			//Seta novamente a variavel com a string do path.
				qt++;
			}
			if (!(dirMean->d_name[0] == '.'))
			{
				strcat(arqMean, dirMean->d_name);																			//Concatena a string do path com o nome do arquivo.(Ex: "..\\oncotex_pgm\\imagem.pgm");
				readPGMImage(&imgF, arqMean);																					//Chama a funcao para ler o pgm.
				strcpy(arqMean, "..\\oncotex_pgm_mean\\");														//Seta novamente a variavel com a string do path.
				qt++;
			}


			if (!(dir->d_name[0] == '.') && !(dirMean->d_name[0] == '.'))
			{

				vSCM = gerarSCM(&img, &imgF, quantizacao);														//Vetor recebe o vetorSCM gerado pela funcao gerarSCM.
				
				for (int i = 0; i < quantizacao * quantizacao; i++)										//For para percorrer o tamanho da matriz SCM.
				{

					if (i == (quantizacao * quantizacao) - 1)														//Verifica se e o ultimo elemento da matriz.
					{
						fprintf(arquivo, "%d | %c\n", vSCM[i], tipo[0]);									//Escrever no arquivo
					}
					else
					{
						fprintf(arquivo, "%d, ", vSCM[i]);																//Escrever no arquivo
					}
				}
			}

		}
		fclose(arquivo);																													//Fechando
		closedir(d);																															//os
		closedir(dMean);																													//arquivos

		printf("Quantidade de arquivos: %d\n", qt);																//Printar a quantidade de arquivos lidos
	}

	end = clock();																															//Encerra a contagem do clock
	time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;											//Calcula o tempo por imagem
	time_total += time_per_img;																									//Calcula o tempo total

	printf("\nTempo Total: %lf\n", time_total);
	printf("Tempo Medio: %lf", time_total / qt);

	return 0;																																		//FIM :)
}