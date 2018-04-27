/*Teste da função Cjoin*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/cthread.c"

int main(){	

TCB_t NewNode1;
TCB_t NewNode2;
TCB_t NewNode3;
TCB_t NewNode4;


NewNode1.tid = 1;
NewNode2.tid = 2;
NewNode3.tid = 3;
NewNode4.tid = 4;

printf("Inicialização das estruturas - Erros: %d\n\n", initLib() );

printf("Inserindo nodos nas filas...\n");
if (insertInFila(&aptos, &NewNode1) != 0)
	printf("ERRO\n");
printf("Inserindo nodos nas filas...\n");
if (insertInFila(&aptos, &NewNode2) != 0)
	printf("ERRO\n");
printf("Inserindo nodos nas filas...\n");
if (insertInFila(&aptos, &NewNode3) != 0)
	printf("ERRO\n");
printf("Inserindo nodos nas filas...\n");
if (insertInFila(&aptos, &NewNode4) != 0)
	printf("ERRO\n");

printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);


printf("Exec -> Bloc; nextApto\n");
if (shiftNextApto(&bloqueados) != 0)
	printf("ERRO\n");
printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);

printf("Cjoin : A thread que esta executando (t1) está esperando o término da t4... Erros: %d\n", cjoin(4));
printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);

printf("Exec -> apt; nextApto\n");
if (shiftNextApto(&aptos) != 0)
	printf("ERRO\n");
printf("Exec -> apt; nextApto\n");
if (shiftNextApto(&aptos) != 0)
	printf("ERRO\n");
printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);

findInFila(1, &bloqueados);
TCB_t * nodeTeste = GetAtIteratorFila2(&bloqueados);
printf("OBS: Thread 1 esperando por : waiting = %d\n", nodeTeste->waintingJoin);
printf("Finish thread em exec.(t4) ERRO: %d\n", finishThread());

printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);

}

