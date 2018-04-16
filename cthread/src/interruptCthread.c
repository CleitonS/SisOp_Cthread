//
//  interruptCthread.c
//  
//
//  Created by Bernardo Lignati on 15/04/18.
//
//
#include "../include/cdata.h"
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cthreadaux.h"

/******************************************************************************
 Par‚metros:
	tid:	identificador da thread a ser suspensa.
 Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
    Erro -1 => TID igual a Thread em execucao
    Erro -2 => Nao achou a Thread a ser bloqueada
 ******************************************************************************/

int csuspend(int tid){
    s_TCB* toSuspendThread;
    if(execute->tid == tid) return -1;
        
    if(findInFila(tid,bloqueados)){
        moveToBloqueadosSus(tid);
        return 0;
    }
    else
        if (findInFila(tid,aptos)){
            moveToAptosSus(tid);
            return 0;
        }
        else return -2
    
    

}

/******************************************************************************
 Par‚metros:
	tid:	identificador da thread que ter· sua execuÁ„o retomada.
 Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
 ******************************************************************************/
int cresume(int tid){



}
/******************************************************************************
 Par‚metros:
	sem:	ponteiro para uma vari·vel do tipo csem_t. Aponta para uma estrutura de dados que representa a vari·vel sem·foro.
	count: valor a ser usado na inicializaÁ„o do sem·foro. Representa a quantidade de recursos controlados pelo sem·foro.
 Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
 */
int cwait(csem_t *sem){




}
 /******************************************************************************
 Par‚metros:
	sem:	ponteiro para uma vari·vel do tipo sem·foro.
 Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
 ******************************************************************************/
int csignal(csem_t *sem){




}
moveToBloqueadosSus(int tid){

}
moveToAptosSus(int tid){

}


