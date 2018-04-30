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




	/*Assumindo que o Cechin poderia chamar prio com um valor difernente de zero*/
	if(prio == 0){

	/*---------------------------------Inicialização da TCB---------------------------------*/
	TCB_t *newThread;

  idCounter++;

	newThread = (TCB_t*) malloc(sizeof(TCB_t));
	newThread->tid = idCounter;
	newThread->prio = prio; //(ou sempre zero?)
	newThread->state = PROCST_APTO;
	newThread->waintingJoin= -1;


  getcontext(&(newThread->context));

	//Aqui receberemos o endereço da thread final
	newThread->context.uc_link = &finalThreadAddress;
	newThread->context.uc_stack.ss_sp = stackMem;
	newThread->context.uc_stack.ss_size = sizeof stackMem;
	

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
	printf("Nova thread criada com sucesso. tid=%d\n",newThread->tid);
	return (newThread->tid);

}

/*Função que faz o despacho da fila de apto para executando
retorna 0 caso dê tudo certo, c.c valor negativo*/
int dispatch(){

	TCB_t *nextThreadToCPU = NULL;

	/*verificar se a fila de aptos contém algo. Por default, se
	retornar zero, tem algo!*/
	if(FirstFila2(&aptos) == 0){
		/*Pegar o que está executando, e trocar pelo primeiro da fila*/
		/*Pegar o conteúdo do primeiro cara a ser executado!*/
		if(GetAtIteratorFila2(&aptos)!= NULL){
			nextThreadToCPU = (TCB_t*) GetAtIteratorFila2(&aptos);
			/*Nova execução recebe o primeiro da fila de aptos*/
			execute = nextThreadToCPU;

			/*Remover ponteiro do primeiro da fila de aptos, pois foi para CPU*/
			if(FirstFila2(&aptos)==0){
				if(DeleteAtIteratorFila2(&aptos) == 0){
					setcontext(&execute->context);
					return 0;
				}
			}
		}

	}else{
		printf("Não há mais threads a serem executadas!\n");
	}

	//Retorno de erro -3 caso não der para executar o dispatch.
	return -3;

}
