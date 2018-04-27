/*Teste da função cidentify*/
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



/*
teste consiste em:
Colocar t1 em executando
colocar t2 e t3 na fila de aptos
Colocar t4 na fila de bloqueados

Executar funcao para colocar o que esta executando em bloqueado e
pegar o proximo de apto e colocar a executar: funcao "shiftNextApto"

Depois buscar a thread 4 que esta na fila de bloqueado e coloca-la 
no fim da fila de aptos: funcao "shiftFilas"


*/



//execute = &NewNode1;


printf("Inserindo nodos nas filas...\n");
if (insertInFila(&aptos, &NewNode2) != 0)
	printf("ERRO\n");
if (insertInFila(&aptos, &NewNode3) != 0)
	printf("ERRO\n");
if(insertInFila(&bloqueados, &NewNode4) != 0)
	printf("ERRO\n");
if(insertInFila(&bloqueados, &NewNode1) != 0)
	printf("ERRO\n");



printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);

printf("exec -> apto e apto -> exec \n");
shiftNextApto(&aptos);
printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);

printf("exec -> apto e apto -> exec \n");
shiftNextApto(&aptos);
printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);

printf("exec -> apto e apto -> exec \n");
shiftNextApto(&aptos);
printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);

printf("exec -> apto e apto -> exec \n");
shiftNextApto(&aptos);
printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);

printf("fim teste 01");
















printf("exec -> block e apto -> exec \n");
shiftNextApto(&bloqueados);

printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);

printf("Troca a thread 4 de bloc para apto\n");
if (shiftFilas(&aptos, &bloqueados, 4) != 0)
	printf("ERRO\n");

printf("Fila de aptos: ");
printFila(&aptos);
printf("\nFila de block: ");
printFila(&bloqueados);
printf("\n");
printf("Executando: %d\n", execute->tid);


printf("Teste do semáfaro - inserindo t2\n");
if (insertInFila((FILA2 *)(&(semafaro.fila)), &NewNode2) != 0)
	printf("ERRO\n");
printf("\nFila do semáfaro: ");
printFila((FILA2 *)(&(semafaro.fila)));
printf("\n");




}

