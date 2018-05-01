
/*
 *	Programa de exemplo de uso da biblioteca cthread
 *
 *	Vers�o 1.0 - 14/04/2016
 *
 *	Sistemas Operacionais I - www.inf.ufrgs.br
 *
 */

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

void* func0(void *arg) {
	printf("Eu sou a thread ID0 imprimindo %d\n", *((int *)arg));
	return;
}

void* func1(void *arg) {
	printf("Eu sou a thread ID1 imprimindo %d\n", *((int *)arg));
	printf("leiteeee");
}


void* func3(void *arg) {
	printf("Eu sou a thread ID3 imprimindo %d\n", *((int *)arg));
}


int main(int argc, char *argv[]) {

	int	id0, id1, id3;
	int i;

	id0 = ccreate(func0, (void *)&i, 0);
	id1 = ccreate(func1, (void *)&i, 0);
	id3 = ccreate(func3, (void *)&i, 0);

	printf("Eu sou a main ap�s a cria��o de ID0 e ID1\n");

	cjoin(id0);
 	cjoin(id1);
  //cjoin(id3);

	printf("Eu sou a main voltando para terminar o programa\n");
}
