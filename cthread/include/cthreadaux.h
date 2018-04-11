/*-------------------------------------------------------------------
Função:	Retorna 0 se o tid passado se encontra na fila passado como 
		parâmetro e !0 se não se encontra.
-------------------------------------------------------------------*/
int findInFila(int tid, FILA2 *fila);


/*-------------------------------------------------------------------
Função:	Retorna !0 se o tid passado já esta sendo esperado por outra
		thread da fila passada. Do contrário, retorna 0.
-------------------------------------------------------------------*/
int findOtherJoin(int tid, FILA2 *fila);
