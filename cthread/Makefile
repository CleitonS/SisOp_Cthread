#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
LIB_DIR=./lib/
INC_DIR=./include/
BIN_DIR=./bin/
SRC_DIR=./src/
TES_DIR=./testes/

all:
	gcc -c $(SRC_DIR)cthread.c -o $(BIN_DIR)libcthread.o -Wall
	ar crs $(LIB_DIR)libcthread.a $(BIN_DIR)libcthread.o $(BIN_DIR)support.o 
	
clean:
	rm -rf $(TES_DIR)*.o
	rm $(BIN_DIR)libcthread.o
	rm $(LIB_DIR)libcthread.a
