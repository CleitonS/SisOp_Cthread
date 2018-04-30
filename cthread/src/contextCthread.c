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

extern int init;
extern int checkMainThread();
extern FILA2 aptos;
extern FILA2 bloqueados;
extern FILA2 aptos_sus;
extern FILA2 bloqueados_sus;
extern TCB_t *execute;
/*extern csem_t semafaro; */
extern TCB_t threadMain;

//#define stackMem 64000;
char stackMem[64000];


ucontext_t finalThreadAddress;


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
	TCB_t *newThread;


	checkMainThread();


	/*Assumindo que o Cechin poderia chamar prio com um valor difernente de zero*/
	if(prio == 0){

	/*---------------------------------Inicialização da TCB---------------------------------*/


  idCounter++;

	newThread = (TCB_t*) malloc(sizeof(TCB_t));
	newThread->tid = idCounter;
	newThread->prio = prio; //(ou sempre zero?)
	newThread->state = PROCST_APTO;
	newThread->waintingJoin= -1;


  getcontext(&(newThread->context));

	//Aqui receberemos o endereço da thread final
	newThread->context.uc_link = execute->context.uc_link;
	newThread->context.uc_stack.ss_sp = stackMem;
	newThread->context.uc_stack.ss_size = sizeof stackMem;


	printf("LINK DA NOVA FUNCAO CRIADA=%d\n",(int)newThread->context.uc_link);

	//Referencia para as atribuições acima se alguém quiser ver.
  //http://nitish712.blogspot.com.br/2012/10/thread-library-using-context-switching.html


	//Arg passado como parametro da função ccreate.
	makecontext(&(newThread->context),(void(*)(void))start,1,arg);


	/*---------------------------------Fim inicialização da TCB---------------------------------*/


	/*---------------------------------Inserção na fila de Aptos---------------------------------*/


	//InsertInFIla r'etorna 0 caso for inicializado com sucesso.
	if(!insertInFila(&aptos,newThread)){
		printf("Thread inserida na fila! Yey (isso me lembrou o johann)");
	} else{
		printf("Erro na inserção da thread na fila");
		return -2;
	}

	/*---------------------------------Fim inserção na fila de Aptos---------------------------------*/
	} else{
		/*Valor negativo caso prio != 0  e der errado.*/
		return -1;
	}

	//Retorno do tId da thread criada.
	printf("Nova thread criada com sucesso. tid=%d\n", newThread->tid);
	return (newThread->tid);

}


int dispatch(TCB_t* oldNode, TCB_t *newNode){
	printf("dispatcher entrou\n");

	getcontext(&(newNode->context));
	printf("dispatcher getcontext\n");


	setcontext(&(oldNode->context));
	printf("dispatcher set\n");
	return 0;



}
