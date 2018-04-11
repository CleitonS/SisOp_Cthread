#include "../include/cdata.h"
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cthreadaux.h"




#define RESOURCE 1  /* representa a quantidade existente do recurso controlado pelo sem�foro */

FILA2 aptos;
FILA2 bloqueados;
FILA2 aptos_sus;
FILA2 bloqueados_sus;
TCB_t *execute;

csem_t semafaro; /*Obs: Na especificacao, o nome da variavel esta fixa com acento: "sem�faro". */


int cidentify (char *name, int size){
	/*N�o esta funcionando!!! */
	name = "Bernardo Neuhaus Lignati - 230159 \nCleiton Souza Lima - 262511\nLucas Augusto - xxxx \n";
	/*Falta a parte do tamanho...*/
	return 0;
}


/******************************************************************************
Par�metros:
	tid:	identificador da thread cujo t�rmino est� sendo aguardado.
Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
******************************************************************************/
int cjoin(int tid){

    if (findInFila(tid, &aptos)     !=0  && findInFila(tid, &bloqueados)     != 0 &&
		findInFila(tid, &aptos_sus) != 0 && findInFila(tid, &bloqueados_sus) != 0){
        /*Posso terminar o processo, pois o tid que ele esta esperando n�o esta em nenhuma das filas, 
		logo, ou ele nunca existiu ou existiu e j� foi terminado*/
		
        /* --> completar com a fun��o de termino... <-- */
        return 0;
    }
    else{
        if (findOtherJoin(tid, &aptos)     != 0 && findOtherJoin(tid, &bloqueados)     != 0  &&
			findOtherJoin(tid, &aptos_sus) != 0 && findOtherJoin(tid, &bloqueados_sus) != 0 )
            return -1; /*existem outro processo que esta aguardando esse mesmo tid*/
        else{
            execute->waintingJoin = tid;
            /*funcao de: 'bloqueia processo'*/
            return 0;
        }
    }

}

/*-------------------------------------------------------------------
Fun��o:	Retorna 0 se o tid passado se encontra na fila passado como 
		par�metro e !0 se n�o se encontra.
-------------------------------------------------------------------*/
int findInFila(int tid, FILA2 *fila){
    TCB_t *thread = NULL;
	if (FirstFila2(fila) != 0)
        return -1;
    else{
        while (GetAtIteratorFila2(fila) != NULL){
            thread = GetAtIteratorFila2(fila);
            if (thread -> tid == tid)
                return 0;
            else
                if (NextFila2(fila) != 0)
                    return -1;
        }
        return -1;
    }
}



/*-------------------------------------------------------------------
Fun��o:	Retorna !0 se o tid passado j� esta sendo esperado por outra
		thread da fila passada. Do contr�rio, retorna 0.
-------------------------------------------------------------------*/
int findOtherJoin(int tid, FILA2 *fila){

    TCB_t *thread = NULL;
	if (FirstFila2(fila) != 0)
        return 0;
    else{
        while (GetAtIteratorFila2(fila) != NULL){
            thread = GetAtIteratorFila2(fila);
            if (thread -> waintingJoin == tid)
                return -1;
            else
                if (NextFila2(fila) != 0)
                    return 0;
        }
    }
    return 0;
}




/*-------------------------------------------------------------------
Fun��o:	Inicializa todas as estruturas da biblioteca.
		Deve ser chamada na primeira vez em que a biblioteca for usada.
		Caso n�o ocorra nenhum erro, retorna o valor zero.
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
	
	return error;		
}

int csem_init (csem_t *sem, int count){
	FILA2 thrBlocSem;
	if(!CreateFila2(&thrBlocSem))
		return -1;
	semafaro.count = RESOURCE;
	semafaro.fila = &thrBlocSem;	
	return 0;
}
















