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
            if (thread->tid == tid)
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
int insertInFila(FILA2 *fila, TCB_t *newThread){
	
	if (AppendFila2(fila, (void *) newThread) != 0)
		return -1;
	else 
		return 0;
	/*
	if (LastFila2(fila) != 0 && FirstFila2(fila) != 0){
		AppendFila2(fila, (void *) newThread);
		return 0;
	}
	else {
		if (LastFila2(fila) != 0)
			return -1;
		if (InsertAfterIteratorFila2(fila, newThread) != 0)
			return -1;
		else 
			return 0;	
		*/

}




/*-------------------------------------------------------------------
Função:	Realiza a troca da thread que esta executando.
		Pega o primeiro elemento da fila de aptos e coloca na 
		variável execute.	
Retorna 0 se a operação acorreu sem problemas.
Retona !0 se ocorreu se erro.
		
		IMPORTANTE: Caso ocorra qualquer erro no processo, a thread 
		que estava executando, continua executando...

Erros:
	-1 -> Falha ao posicionar o primeiro elemento da fila de aptos.
	-2 -> Falha ao obter o nodo da fila.
	-3 -> Falha ao excluir elemento da fila.
-------------------------------------------------------------------*/
int nextApto(){
	TCB_t *OldNode;	

	if (FirstFila2(&aptos) != 0)
		return -1;
	else{
		OldNode = execute;
		execute = GetAtIteratorFila2(&aptos); /*Testar...*/
		if (execute == NULL){
			execute = OldNode;
			return -2;
		}
		else{
			if (DeleteAtIteratorFila2(&aptos) != 0){
				execute = OldNode;
				return -3;
			}
			else			
				return 0;	
		}
	}
}


/*-------------------------------------------------------------------
Função:	Insere a thread que esta executando na fila passada por 
parametro e coloca o primeiro elemento da fila de aptos para executar.

Retorna 0 se a operação acorreu sem problemas.
Retona !0 se ocorreu se erro.

ERROS:
	-1 -> Erro ao inserir a thread que estava executando na
			fila passada por parâmetro.
	-2 -> Erro ao pegar o primeiro elemento da fila de aptos e 
			colocá-lo a executar.

-------------------------------------------------------------------*/
int shiftNextApto(FILA2 *fila){	
	if (insertInFila(fila, execute) != 0 )
		return -1;
	else {
		if (nextApto() != 0)
			return -2;
		else 
			return 0;
	}
}




/*-------------------------------------------------------------------
Função:	Recebe duas filas (FilaIn e FilaOut) e o identificador da 
		thread tid.
		A operação da função é:
		Procurar a thread correspondente ao tid na filaOut;
		remover o nodo da filaOut;
		Inserir o nodo no final da filaIn.
		

Retorna 0 se a operação acorreu sem problemas.
Retona !0 se ocorreu se erro.

ERROS:
	-1 -> Tid não encontrado			
	-2 -> Erro ao obter o ponteiro para a thread 
	-3 -> Erro ao excluir nodo
	-4 -> Erro ao inserir o nodo na filaIn			
-------------------------------------------------------------------*/
int shiftFilas(FILA2 *filaIn, FILA2 *filaOut, int tidOut){
	TCB_t *nodeOut;
	//TCB_t BackNodeOut;
	
	if (findInFila(tidOut, filaOut) != 0) //posiciona o iterador da fila no elemento
		return -1;
	nodeOut = GetAtIteratorFila2(filaOut);
	if (nodeOut == NULL)
		return -2;
	if(DeleteAtIteratorFila2(filaOut) != 0) 
		return -3;
	if (insertInFila(filaIn, nodeOut) != 0)
		return -4;
	return 0;	
}



void printFila(FILA2 *fila){
    TCB_t *thread = NULL;
	if (FirstFila2(fila) != 0)
        printf("ERRO - fila vazia/n");
    else{
        while (GetAtIteratorFila2(fila) != NULL){
			thread = GetAtIteratorFila2(fila);
			printf("tid: %d, ", thread->tid);
			NextFila2(fila);			
        }
    }	
		
}





#endif
