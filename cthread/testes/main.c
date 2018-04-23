/*Teste da função cidentify*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/cthread.c"

int main(){	

TCB_t NewNode1;
TCB_t NewNode2;
TCB_t NewNode3;
FILA2 teste;

TCB_t *NodeCurrent;


printf("criou fila %d\n", CreateFila2(&teste));

NewNode1.state = 1;
NewNode2.state = 2;
NewNode3.state = 3;

insertInFila(&teste, &NewNode1); 
insertInFila(&teste, &NewNode2);
insertInFila(&teste, &NewNode3);

FirstFila2(&teste);
NodeCurrent = (TCB_t *) GetAtIteratorFila2(&teste);
printf("Primeiro nodo: %d\n", NodeCurrent->state);
NextFila2(&teste);
NodeCurrent = (TCB_t *) GetAtIteratorFila2(&teste);
printf("Segundo nodo: %d\n", NodeCurrent->state);
NextFila2(&teste);
NodeCurrent = (TCB_t *) GetAtIteratorFila2(&teste);
printf("Terceiro e Ultimo nodo: %d\n", NodeCurrent->state);



printf("Excluindo primeiro nodo...\n");
FirstFila2(&teste);
if (DeleteAtIteratorFila2(&teste) == 0)
	printf("Exclui nodo \n");
else
	printf("ERRO - Exclui nodo \n");




LastFila2(&teste);

NodeCurrent = (TCB_t *) GetAtIteratorFila2(&teste);
printf("Último nodo: %d\n", NodeCurrent->state);


FirstFila2(&teste);
NodeCurrent = (TCB_t *) GetAtIteratorFila2(&teste);
printf("Primeiro nodo: %d\n", NodeCurrent->state);



}