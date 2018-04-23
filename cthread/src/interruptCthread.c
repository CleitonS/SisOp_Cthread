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



extern FILA2 aptos;
extern FILA2 bloqueados;
extern FILA2 aptos_sus;
extern FILA2 bloqueados_sus;
extern TCB_t *execute;
extern csem_t semafaro; /*Obs: Na especificacao, o nome da variavel esta descrita com acento: "semáfaro". */




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
    if(execute->tid == tid) return -1;

    if(findInFila(tid,&bloqueados) == 0){
        moveToBloqueadosSusFromBloqueados(tid);
        return 0;
    }
    else
        if (findInFila(tid,&aptos) == 0){
            moveToAptosSusFromAptos(tid);
            return 0;
        }
        else return -2;



}

/******************************************************************************
 Par‚metros:
	tid:	identificador da thread que ter· sua execuÁ„o retomada.
 Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
Erro -2 => Nao achou a Thread a ser liberada
 ******************************************************************************/
int cresume(int tid){

    if(findInFila(tid,&bloqueados_sus) == 0){
        moveToBloqueadosFromBloqueadoSus(tid);
        return 0;
    }
    else
        if (findInFila(tid,&aptos_sus) == 0){
            moveToAptosFromAptosSus(tid);
            return 0;
        }
        else return -2;




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
    if(sem->count <= 0){
    
        movoToFilaSemafora(sem);//adiciona a fila interna do semaforo e bloqueia o processo em execucao escalonador
        return -1;
    }
    else{
        sem->count --;
        return 0;
    }

}
 /******************************************************************************
 Par‚metros:
	sem:	ponteiro para uma vari·vel do tipo sem·foro.
 Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
 ******************************************************************************/
/*Liberação de recurso: a chamada csignal serve para indicar que a thread está liberando o recurso. Para cada chamada da primitiva csignal, a variável count deverá ser incrementada de uma unidade. Se houver mais de uma thread bloqueada a espera desse recurso a primeira delas, segundo uma política de FIFO, deverá passar para o estado apto e as demais devem continuar no estado bloqueado.*/
int csignal(csem_t *sem){
    sem -> count ++;
    if(isNotEmpty(sem -> fila)){
        removeFromSemFila(sem);//remove da fila do semafaro e passa para estado de apto
        
    }
    //escalonador(?)


}

int moveToBloqueadosFromBloqueadoSus(int tid){

}

int moveToBloqueadosSusFromBloqueados(int tid){

}

int moveToAptosSusFromAptos(int tid){

}

int moveToAptosFromAptosSus(int tid){

}


int moveToFilaSemaforo(csem_t *sem){
    moveToBloqueadosFromExecutando();

}
int moveToBloqueadosFromExecutando(){
}
int removeFromSemFila(sem){
}
