/*-------------------------------------------------------------------
Função:	Retorna 0 se o tid passado se encontra na fila de aptos e
        !0 se não se encontra.
-------------------------------------------------------------------*/
int findInApto(int tid);


/*-------------------------------------------------------------------
Função:	Retorna 0 se o tid passado se encontra na fila de bloqueados
        e !0 se não se encontra.
-------------------------------------------------------------------*/
int findInBloqueados(int tid);


/*-------------------------------------------------------------------
Função:	Retorna !0 se o tid passado já esta sendo esperado por outra
		thread da lista de aptos. Do contrário, retorna 0.
-------------------------------------------------------------------*/
int findOtherJoinAptos(int tid);


/*-------------------------------------------------------------------
Função:	Retorna !0 se o tid passado já esta sendo esperado por outra
		thread da lista de bloqueados. Do contrário, retorna 0.
-------------------------------------------------------------------*/
int findOtherJoinBloqueados(int tid);