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
extern TCB_t *execute;
/*extern csem_t semafaro; */
extern TCB_t threadMain;
extern ucontext_t finalThreadAddress, dispatchAddress;

/*#define RESOURCE 1 */


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
  -3 -> Erro pois não conseguiu chamar o dispatcher

-------------------------------------------------------------------*/
int shiftNextApto(FILA2 *fila){

    if (insertInFila(fila, execute) != 0 )
      return -1;
    else {
      if (nextApto() != 0)
        return -2;
      else
        return -3; //VER AQUI onde tinha o dispatch
    }


}



/******************************************************************************
Inicializa Thread Main na primeira execução.
Parâmetros:
Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
******************************************************************************/
int createThreadMain(){
	threadMain.tid = 0;
	threadMain.state = PROCST_EXEC;
	threadMain.prio = 0;

	if (getcontext(&(threadMain.context)) != 0)
		return -1;
	threadMain.waintingJoin = -1;
  threadMain.context.uc_link = 0;

  printf("LINK DA MAIN=%d",(int)  threadMain.context.uc_link);

	execute = (TCB_t *) malloc(sizeof(TCB_t));
	execute = (TCB_t *) &threadMain;
	return 0;


}




/******************************************************************************
Parâmetros:
	tid:	identificador da thread cujo término está sendo aguardado.
Retorno:
	Se correto => 0 (zero)
	Se erro	   => Valor negativo.
		-1 --> Outro processo esta aguardando essa thread
		-2 --> Thread que estou esperando terminar não foi encontrada
		-3 --> Erro ao bloquear processo ou executar próximo da fila de aptos.

******************************************************************************/
int cjoin(int tid){


		checkMainThread();

    printf("passoucheckmain");
    if (findInFila(tid, &aptos) !=0  && findInFila(tid, &bloqueados)     != 0 &&
		findInFila(tid, &aptos_sus) != 0 && findInFila(tid, &bloqueados_sus) != 0){
		/*Thread não encontrada: Não foi criada ou já terminou...*/
        printf("passou");
        return -2;
    }
    else{
        if (findOtherJoin(tid, &aptos)     != 0 && findOtherJoin(tid, &bloqueados)     != 0  &&
			findOtherJoin(tid, &aptos_sus) != 0 && findOtherJoin(tid, &bloqueados_sus) != 0 )
            return -1; /*existem outro processo que esta aguardando esse mesmo tid*/
        else{
            execute->waintingJoin = tid;
			swapcontext(&execute->context, &dispatch_ctx);
            if (shiftNextApto(&bloqueados) != 0)
				return -3;
			else{
				
				return 0;
			}
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

	checkMainThread();

	FILA2 thrBlocSem;
	if(CreateFila2(&thrBlocSem) != 0)
		return -1;
	sem -> count = count;
	sem -> fila = &thrBlocSem;
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

	if (CreateFila2(&aptos) != 0){
		printf("ERROR - Inicializacao da fila de aptos \n");
		error++;
	}
	if (CreateFila2(&bloqueados)!= 0){
		printf("ERROR - Inicializacao da fila de bloqueados \n");
		error++;
	}
	if (CreateFila2(&aptos_sus)!= 0){
		printf("ERROR - Inicializacao da fila de aptos-suspensos \n");
		error++;
	}
	if (CreateFila2(&bloqueados_sus)!= 0){
		printf("ERROR - Inicializacao da fila de bloqueados-suspensos \n");
		error++;
	}
	
	
	if (initDispatch()!= 0){
		printf("ERROR - Inicializacao Dispacther\n");
		error++;
	}

	if (createThreadMain()!= 0){
		printf("ERROR - Inicializacao thread main\n");
		error++;
	}

  if(instantiateFinalThread()!=0){
    printf("ERROR - Inicializacao da Thread final\n");
    error++;
  }

	return error;
}
