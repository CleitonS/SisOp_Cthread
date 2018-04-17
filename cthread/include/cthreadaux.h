//
//  CthreadAux.c
//  
//	Funções de suporte à biblioteca cthread
//
//


#ifndef	__cthreadAux__
#define	__cthreadAux__

#include "../include/cdata.h"
#include "../include/support.h"

extern FILA2 aptos;
extern FILA2 bloqueados;
extern FILA2 aptos_sus;
extern FILA2 bloqueados_sus;
extern TCB_t *execute;
extern csem_t semafaro; 


/*-------------------------------------------------------------------
Função:	Retorna 0 se o tid passado se encontra na fila passado como 
		parâmetro e !0 se não se encontra.
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
Função:	Retorna !0 se o tid passado já esta sendo esperado por outra
		thread da fila passada. Do contrário, retorna 0.
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
Função:	Retorna 0 se o elemento foi inserido na fila com sucesso.
		Retona !0 se ocorreu se erro.
		
-------------------------------------------------------------------*/
int insertInFila(FILA2 *fila, TCB *newThread){
	if (LastFila2(fila) != 0)
		return -1;
	else{
		if (InsertAfterIteratorFila2(fila, newThread) != 0)
			return -1
		else 
			return 0;				
	} 	
}


#endif
