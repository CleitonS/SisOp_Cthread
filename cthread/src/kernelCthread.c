//
//  KernelCthread.c
//  
//
//  Created by Cleiton on 10/04/18.
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
extern TCB_t execute;
extern csem_t semafaro; /*Obs: Na especificacao, o nome da variavel esta descrita com acento: "semáfaro". */



#define RESOURCE 1  /* representa a quantidade existente do recurso controlado pelo semáforo */




int callScheduler(){
	
}



/******************************************************************************
Parâmetros:
	tid:	identificador da thread cujo término está sendo aguardado.
Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
******************************************************************************/
int cjoin(int tid){

    if (findInFila(tid, &aptos)     !=0  && findInFila(tid, &bloqueados)     != 0 &&
		findInFila(tid, &aptos_sus) != 0 && findInFila(tid, &bloqueados_sus) != 0){
        /*Posso terminar o processo, pois o tid que ele esta esperando não esta em nenhuma das filas, 
		logo, ou ele nunca existiu ou existiu e já foi terminado*/
		
        /* --> completar com a função de termino... <-- */
        return 0;
    }
    else{
        if (findOtherJoin(tid, &aptos)     != 0 && findOtherJoin(tid, &bloqueados)     != 0  &&
			findOtherJoin(tid, &aptos_sus) != 0 && findOtherJoin(tid, &bloqueados_sus) != 0 )
            return -1; /*existem outro processo que esta aguardando esse mesmo tid*/
        else{
            execute.waintingJoin = tid;
            /*funcao de: 'bloqueia processo'*/
            return 0;
        }
    }

}



/******************************************************************************
Inicializador do semáfaro
Parâmetros: Ponteiro para a variável global "Semafaro". 
			Número de dispositivos que o semáfaro controla na sessão crítica
	
Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
******************************************************************************/
int csem_init (csem_t *sem, int count){
	
	FILA2 thrBlocSem;
	if(!CreateFila2(&thrBlocSem))
		return -1;
	semafaro.count = RESOURCE;
	semafaro.fila = &thrBlocSem;	
	return 0;
}


/*-------------------------------------------------------------------
Função:	Inicializa todas as estruturas da biblioteca.
		Deve ser chamada na primeira vez em que a biblioteca for usada.
		Caso não ocorra nenhum erro, retorna o valor zero.
		Se ocorrer erro, retornar a quantidade de erros que aconteceram.
-------------------------------------------------------------------*/
int initLib(){
	int error = 0;
	
	if (!CreateFila2(&aptos)){
		printf("ERROR - Inicializacao da fila de aptos \n");
		error++;		
	}
	if (!CreateFila2(&bloqueados)){
		printf("ERROR - Inicializacao da fila de bloqueados \n");
		error++;		
	}	
	if (!CreateFila2(&aptos_sus)){
		printf("ERROR - Inicializacao da fila de aptos-suspensos \n");
		error++;		
	}
	if (!CreateFila2(&bloqueados_sus)){
		printf("ERROR - Inicializacao da fila de bloqueados-suspensos \n");
		error++;		
	}		
	
	if (!csem_init(&semafaro, RESOURCE)){
		printf("ERROR - Inicializacao do semafaro \n");
		error++;
	}	
	
	if (!createThreadMain()){
		printf("ERROR - Inicializacao thread main\n");
		error++;
	}
	
	return error;		
}




/******************************************************************************
Inicializa Thread Main na primeira execução.
Parâmetros:
Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
******************************************************************************/
int createThreadMain(){
	TCB_t threadMain;
	threadMain.tid = 0;
	threadMain.state = PROCST_EXEC;
	threadMain.prio = 0;
	if (!getcontext(&(threadMain.context)))
		return -1;
	threadMain.waintingJoin = -1;
	
	execute = threadMain;	
	return 0;
	
	
}









