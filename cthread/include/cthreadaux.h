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
#include <stdlib.h>
extern void dispatch(TCB_t * oldDispatch);
extern FILA2 aptos;
extern FILA2 bloqueados;
extern FILA2 aptos_sus;
extern FILA2 bloqueados_sus;
extern TCB_t *execute;
/*extern csem_t semafaro;*/
extern TCB_t threadMain;
extern ucontext_t finalThreadAddress, dispatchAddress;
extern ucontext_t* mainContext;

/*-------------------------------------------------------------------
Função:	Retorna 0 se o tid passado se encontra na fila passado como
		parâmetro e !0 se não se encontra.
-------------------------------------------------------------------*/
int findInFila(int tid, FILA2 *fila){
    TCB_t *thread = (TCB_t *) malloc(sizeof(TCB_t));
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

		Caso o retorno passado seja !0, esse número é o tid da
		thread que estava esperando o tid passado por parâmetro.
		Exceto se for a thread main, nesse caso retorna -1.

		Exemplo:
		Quero saber se alguma thead esta esperando o tid = 5.
		Se o retorno for igual a 2, significa que a thread 2
		esta esperando a thread 5 terminar.
		Se o retorno for -1, significa que a theadMain que esta
		esperando a thread 5
-------------------------------------------------------------------*/
int findOtherJoin(int tid, FILA2 *fila){

    TCB_t *thread = (TCB_t *) malloc(sizeof(TCB_t));
	if (FirstFila2(fila) != 0)
        return 0;
    else{
        while (GetAtIteratorFila2(fila) != NULL){
            thread = GetAtIteratorFila2(fila);
            if (thread -> waintingJoin == tid){
				if (thread -> tid == 0)
					return -1;
				else
					return (thread -> tid);
			}
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
	TCB_t *OldNode = (TCB_t *) malloc(sizeof(TCB_t));

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
			else{
				dispatch(OldNode);
				return 0;
      			}
		}
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
	TCB_t *nodeOut = (TCB_t *) malloc(sizeof(TCB_t));
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
    TCB_t *thread = (TCB_t *) malloc(sizeof(TCB_t));
	if (FirstFila2(fila) != 0)
        printf("ERRO - fila vazia\n");
    else{
        while (GetAtIteratorFila2(fila) != NULL){
			thread = GetAtIteratorFila2(fila);
			printf("tid: %d, ", thread->tid);
			NextFila2(fila);
        }
    }
}




/*-------------------------------------------------------------------
Função:	Finaliza a thread que está executando e busca se alguma outra
		estava na fila de bloqueados aguardando seu término(cjoin).
		Além de finalizar a thread, também coloca o próximo elemento
		da fila de aptos para executar e retira de bloqueados a thread
		que estava aguardando e a coloca em aptos.

Retorna 0 se a operação acorreu sem problemas.
Retona !0 se ocorreu se erro.

ERROS:
	-1 -> Não encontrou a thead que a função findOutherJoin acusou
		  estar esperando pelo término.
		  Erro na findOtherJoin ou na findInFila.

	-2 -> TID diferentes, erro no processo.

	-3 -> Erro ao chamar próxima thread a executar.


-------------------------------------------------------------------*/
int finishThread(){
	TCB_t* novaThreadExecutar = (TCB_t *) malloc(sizeof(TCB_t));
	TCB_t *node = (TCB_t *) malloc(sizeof(TCB_t));
	int tidWaiting;
	printf("----------------\nmatando thread\n---------------------\n");
	tidWaiting =  findOtherJoin(execute->tid, &bloqueados);
	printf("sai da find other join");
	if (tidWaiting != 0){
		if (tidWaiting == -1)
			tidWaiting = 0;

		if (findInFila(tidWaiting, &bloqueados) != 0){
			printf("cai do primeiro return");
			return -1;
		}	
		printf("passei do primeiro return");
		node = GetAtIteratorFila2(&bloqueados);
		if (node -> waintingJoin != execute->tid){
			printf("here");
			return -2;
		}
		else{
			node -> waintingJoin = -1;
			printf("\n\naqui\n\n");
			shiftFilas(&aptos, &bloqueados, node->tid);
			printf("\n\naqui\n\n");
		}
	}
	printf("\ncomeca a desalocar execute:%d\n",execute -> tid);
	printFila(&aptos);
	printf("\n");
	
	if (FirstFila2(&aptos) != 0){
			printf("ta vazio");
			setcontext(mainContext);
			return 0;
			
	}
	else{	
	    FirstFila2(&aptos);    
	    novaThreadExecutar = GetAtIteratorFila2(&aptos);
	    free(execute);
	    execute = novaThreadExecutar;
            DeleteAtIteratorFila2(&aptos);
		   
            finalThreadAddress.uc_link = &(execute->context); 
	  
            return 0;
	
 	 }
	printf("fugi de todos os retornos");
	return -40;

}





#endif
