//
//  cthread.c
//
//
//


#include "../src/kernelCthread.c"
#include "../src/interruptCthread.c"


FILA2 aptos;
FILA2 bloqueados;
FILA2 aptos_sus;
FILA2 bloqueados_sus;
TCB_t *execute;
csem_t semafaro; /*Obs: Na especificacao, o nome da variavel esta descrita com acento: "sem�faro". */

int cidentify (char *name, int size){
	/*N�o esta funcionando!!! */
	name = "Bernardo Neuhaus Lignati - 230159 \nCleiton Souza Lima - 262511\nLucas Augusto - 265038 \n";
	/*Falta a parte do tamanho...*/
	return 0;
}
