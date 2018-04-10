#include "../include/cdata.h"
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cthreadaux.h"




FILA2 aptos;
FILA2 bloqueados;
TCB_t *execute;




int cidentify (char *name, int size){
	name = "Bernardo Neuhaus Lignati - 230159 \nCleiton Souza Lima - 262511\nLucas Augusto - xxxx \n";
	/*Falta a parte do tamanho...*/
	return 0;
}


/******************************************************************************
Parâmetros:
	tid:	identificador da thread cujo término está sendo aguardado.
Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
******************************************************************************/
int cjoin(int tid){

    if (findInApto(tid) !=0 && findInBloqueados(tid) != 0){
        /*Posso terminar o processo, pois o tid que ele esta esperando não esta nem na fila de aptos
        nem na fila de bloqueados.*/
        /*completar com a função de termino...*/
        return 0;
    }
    else{
        if (findOtherJoinAptos(tid) != 0 && findOtherJoinBloqueados(tid) != 0 )
            return -1; /*existem outro processo que esta aguardando esse mesmo tid*/
        else{
            execute->waintingJoin = tid;
            /*funcao de: 'bloqueia processo'*/
            return 0;
        }
    }

}

/*-------------------------------------------------------------------
Função:	Retorna 0 se o tid passado se encontra na fila de aptos e
        !0 se não se encontra.
-------------------------------------------------------------------*/
int findInApto(int tid){
    TCB_t *thread = NULL;
	if (FirstFila2(&aptos) != 0)
        return -1;
    else{
        while (GetAtIteratorFila2(&aptos) != NULL){
            thread = GetAtIteratorFila2(&aptos);
            if (thread -> tid == tid)
                return 0;
            else
                if (NextFila2(&aptos) != 0)
                    return -1;
        }
        return -1;
    }
}


/*-------------------------------------------------------------------
Função:	Retorna 0 se o tid passado se encontra na fila de bloqueados
        e !0 se não se encontra.
-------------------------------------------------------------------*/
int findInBloqueados(int tid){
    TCB_t *thread = NULL;
	if (FirstFila2(&bloqueados) != 0)
        return -1;
    else{
        while (GetAtIteratorFila2(&bloqueados) != NULL){
            thread = GetAtIteratorFila2(&bloqueados);
            if (thread -> tid == tid)
                return 0;
            else
                if (NextFila2(&bloqueados) != 0)
                    return -1;
        }
        return -1;
    }
}



/*-------------------------------------------------------------------
Função:	Retorna !0 se o tid passado já esta sendo esperado por outra
		thread da lista de aptos. Do contrário, retorna 0.
-------------------------------------------------------------------*/
int findOtherJoinAptos(int tid){

    TCB_t *thread = NULL;
	if (FirstFila2(&aptos) != 0)
        return 0;
    else{
        while (GetAtIteratorFila2(&aptos) != NULL){
            thread = GetAtIteratorFila2(&aptos);
            if (thread -> waintingJoin == tid)
                return -1;
            else
                if (NextFila2(&aptos) != 0)
                    return 0;
        }
    }
    return 0;
}



/*-------------------------------------------------------------------
Função:	Retorna !0 se o tid passado já esta sendo esperado por outra
		thread da lista de bloqueados. Do contrário, retorna 0.
-------------------------------------------------------------------*/
int findOtherJoinBloqueados(int tid){

    TCB_t *thread = NULL;
	if (FirstFila2(&bloqueados) != 0)
        return 0;
    else{
        while (GetAtIteratorFila2(&bloqueados) != NULL){
            thread = GetAtIteratorFila2(&bloqueados);
            if (thread -> waintingJoin == tid)
                return -1;
            else
                if (NextFila2(&bloqueados) != 0)
                    return 0;
        }
    }
    return 0;
}













