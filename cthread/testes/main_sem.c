/*Teste do semáfaro*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/cthread.c"

int main(){	

TCB_t NewNode1;
TCB_t NewNode2;
TCB_t NewNode3;
TCB_t NewNode4;

csem_t semafaro;
csem_t semafaro2;



NewNode1.tid = 1;
NewNode2.tid = 2;
NewNode3.tid = 3;
NewNode4.tid = 4;

printf("Inicialização das estruturas - Erros: %d\n\n", initLib() );

printf("inicializacao do semáfaro. ERROS: %d\n", csem_init(&semafaro, 1));
printf("inicializacao do semáfaro. ERROS: %d\n", csem_init(&semafaro2, 1));

printf("Inserindo t1 na fila do semáfaro: ERROS: %d\n", insertInFila((FILA2 *)(&(semafaro.fila)), &NewNode1));

printf("Fila do semafaro: ");
printFila((FILA2 *)(&(semafaro.fila)));
printf("\n");

printf("Inserindo t2 na fila do semáfaro: ERROS: %d\n", insertInFila((FILA2 *)(&(semafaro.fila)), &NewNode2));

printf("Fila do semafaro: ");
printFila((FILA2 *)(&(semafaro.fila)));
printf("\n");



printf("\n\n\nTrabalhando com semafaro2\n\n\n");

printf("Inserindo t3 na fila do semáfaro2: ERROS: %d\n", insertInFila((FILA2 *)(&(semafaro2.fila)), &NewNode3));

printf("Fila do semafaro2: ");
printFila((FILA2 *)(&(semafaro2.fila)));
printf("\n");

printf("Inserindo t4 na fila do semáfaro2: ERROS: %d\n", insertInFila((FILA2 *)(&(semafaro2.fila)), &NewNode4));

printf("Fila do semafaro2: ");
printFila((FILA2 *)(&(semafaro2.fila)));
printf("\n");


printf("Fila do semafaro: ");
printFila((FILA2 *)(&(semafaro.fila)));
printf("\n");





}

