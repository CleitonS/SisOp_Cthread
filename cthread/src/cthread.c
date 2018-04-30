//
//  cthread.c
//
//
//

#include "../src/contextCthread.c"
#include "../src/kernelCthread.c"
#include "../src/interruptCthread.c"



FILA2 aptos;
FILA2 bloqueados;
FILA2 aptos_sus;
FILA2 bloqueados_sus;
TCB_t *execute;
/*csem_t semafaro; */
TCB_t threadMain;

int init = 0;


/*Função que testa se a Main está criada. Se não estiver, cria e inicializa ela.
Retorna zero se tudo estiver certo, e negativo caso contrário.*/

int checkMainThread(){

	if(init != 0){
		//Já inicializamos com a init
		return 0;
	}else{
		if(!initLib()){
			printf("Thread Main nao estava iniciada e foi criada junto com as filas.\n");
			init = 1;
			return 0;
		}else{
			printf("Erro na execucao de initLib.\n");
			return -1;
		}
	}

}




int cidentify (char *name, int size){


  	checkMainThread();

	name = "Bernardo Neuhaus Lignati - 230159 \nCleiton Souza Lima - 262511\nLucas Augusto - 265038 \n";
	if (sizeof(name) > size)
		return -1;
	else
		return 0;
}
