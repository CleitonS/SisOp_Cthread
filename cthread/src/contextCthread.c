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
extern int finishThread();
extern FILA2 aptos;
extern FILA2 bloqueados;
extern FILA2 aptos_sus;
extern FILA2 bloqueados_sus;
extern TCB_t *execute;
/*extern csem_t semafaro; */
extern TCB_t threadMain;

//#define stackMem 64000;
char stackMem[64000];


extern ucontext_t finalThreadAddress, dispatchAddress;


int idCounter = 0;




/*Função que inicia a thread finalizadora, para que todos as outras
threads possam apontar para ela. Essa thread recebe uma função
endJob, que finaliza a thread.
Retorna 0 se ocorrer tudo certo.*/

int instantiateFinalThread(){

	getcontext(&finalThreadAddress);

	finalThreadAddress.uc_link = 0;
	finalThreadAddress.uc_stack.ss_sp = stackMem;
	finalThreadAddress.uc_stack.ss_size = sizeof stackMem;

	//Aqui, colocamos a função endJob para a thread final!
	makecontext(&finalThreadAddress,(void(*)(void))finishThread, 0);

	return 0;

}




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
	newThread->prio = 0; //(ou sempre zero?)
	newThread->state = PROCST_APTO;
	newThread->waintingJoin= -1;


  getcontext(&(newThread->context));

	//Aqui receberemos o endereço da thread final
	newThread->context.uc_link = &finalThreadAddress;

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
		printf("Thread inserida na fila!\n");
	} else{
		printf("Erro na inserção da thread na fila\n");
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


void dispatch(TCB_t * oldDispatch){
	printf("\n dispatcher entrou\n");

	if (FirstFila2(&aptos) == 0) {
		TCB_t* novaThreadExecutar = NULL;
		if(GetAtIteratorFila2(&aptos) != NULL){
<<<<<<< Updated upstream
			printf("atribuindo nova thread com o que tem em apto\n");
			novaThreadExecutar = (TCB_t*) GetAtIteratorFila2(&aptos);
			execute = novaThreadExecutar;
=======
			novaThreadExecutar = (TCB_t*) GetAtIteratorFila2(&aptos);//pedaco do escalonador na dispactch
>>>>>>> Stashed changes
			if(execute == NULL){
				execute = novaThreadExecutar;
				DeleteAtIteratorFila2(&aptos);
			}
		}
	}
	printFila(&aptos);
	printf("<-fila \n  thread a ser escalonada=%d\n",execute->tid);
		printf("1");
	if(oldDispatch != NULL)
		swapcontext(&(oldDispatch->context),&(execute->context));
	else
		setcontext(&(execute->context));

}
