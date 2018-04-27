//
//  cthread.c
//
//
//


#include "../src/kernelCthread.c"
/*#include "../src/interruptCthread.c"*/


FILA2 aptos;
FILA2 bloqueados;
FILA2 aptos_sus;
FILA2 bloqueados_sus;
TCB_t *execute;
csem_t semafaro; /*Obs: Na especificacao, o nome da variavel esta descrita com acento: "sem�faro". */
TCB_t threadMain;

int cidentify (char *name, int size){
	name = "Bernardo Neuhaus Lignati - 230159 \nCleiton Souza Lima - 262511\nLucas Augusto - 265038 \n";
	if (sizeof(name) > size) 
		return -1;
	else 
		return 0;
}
