//
//  KernelCthread.c
//  
//
//  Created by Lucas on 25/04/18.
//
//

#include "../include/cdata.h"
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cthreadaux.h"

extern FILA2 aptos;
extern FILA2 bloqueados;
extern FILA2 aptos_sus;
extern FILA2 bloqueados_sus;
extern TCB_t *execute;
/*extern csem_t semafaro; */
extern TCB_t threadMain;

int idCounter = 0;




/******************************************************************************
Parâmetros:
	start:	ponteiro para a função que a thread executará.
	arg:	um parâmetro que pode ser passado para a thread na sua criação.
	prio:	NÃO utilizado neste semestre, deve ser sempre zero.
Retorno:
	Se correto => Valor positivo, que representa o identificador da thread criada
	Se erro	   => Valor negativo.	
******************************************************************************/
int ccreate (void *(*start)(void *), void *arg, int prio){

	
	

	/*Assumindo que o Cechin poderia chamar prio com um valor difernente de zero*/
	if(prio == 0){
	
	/*---------------------------------Inicialização da TCB---------------------------------*/
	TCB_t *newThread;

        idCounter++;

	newThread = malloc(sizeof(TCB_t));
	newThread->tid = idCounter;
	newThread->prio = prio; //(ou sempre zero?)
	newThread->state = PROCST_APTO;
        newThread->waintingJoin= -1;


        getcontext(newThread->context);

        newThread->
	

	/*---------------------------------Fim inicialização da TCB---------------------------------*/


	/*---------------------------------Inserção na fila de Aptos---------------------------------*/


	//InsertInFIla r'etorna 0 caso for inicializado com sucesso.
	if(!insertInFila(FILA2,newThread)){
		printf("Thread inserida na fila! Yey (isso me lembrou o johann)");
	} else{
		printf("Erro na inserção da thread na fila");
		return -2;
	}



	/*---------------------------------Fim inserção na fila de Aptos---------------------------------*/
	} else{
		/*Valor negativo caso der errado.*/
		return -1;
	}





}
