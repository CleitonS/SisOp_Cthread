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
extern csem_t semafaro; 
extern TCB_t threadMain;





/*Parametros para a ccreate: start é o ponteiro para função que a thread executará
			     arg é um ponteiro que pode ser passado para sua thread na execução
			     prio sempre zero.
*/


int ccreate (void *(*start)(void *), void *arg, int prio){


	/*Assumindo que o Cechin poderia chamar prio com um valor difernente de zero*/
	if(prio == 0){
	
	/*---------------------------------Inicialização da TCB---------------------------------*/
	TCB_t *newThread;

	newThread->tid = 
	newThread->prio = prio;
	newThread->state = /*TODO: COLOCAR ESTADO APTO*/ ;



	/*TODO: utilizar getContext*/
	newThread->ucontext_t->context = 
	

	/*---------------------------------Fim inicialização da TCB---------------------------------*/


	/*---------------------------------Inserção na fila de Aptos---------------------------------*/

	/*---------------------------------Fim inserção na fila de Aptos---------------------------------*/
	} else{
		/*Valor negativo caso der errado.*/
		return -1;
	}





}
