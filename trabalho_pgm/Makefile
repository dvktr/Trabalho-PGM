#################################################################################################
# Aluno : 		 Victor de Oliveira Bezerra | Victor Manuel Castro Silva | Victor Mendes de Souza #
# Matricula :       20221045050567 			  |		    20221045050419 	     |	   20221045050583     #
# Avaliacao 04: Trabalho Final ∗/ 																															#
# 04.505.23 − 2022.2 − Prof. Daniel Ferreira ∗/																									#
# Compilador : GCC (tdm64-1) 10.3.0																														  #
#################################################################################################

CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = pgm.o operations.o main.o #objs
TARGET = program #nome do programa
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) arquivo.txt *~

#comandos
#make
# ./program "0_10309_Colon TMA.pgm" "0_10309_Colon TMA_mean.pgm" 31
#make clean