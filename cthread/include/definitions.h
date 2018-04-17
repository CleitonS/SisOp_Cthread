

#ifndef __definitions__
#define __definitions__

#include "../include/cdata.h"
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cthreadaux.h"



FILA2 aptos;
FILA2 bloqueados;
FILA2 aptos_sus;
FILA2 bloqueados_sus;
TCB_t *execute;

csem_t semafaro; /*Obs: Na especificacao, o nome da variavel esta descrita com acento: "semáfaro". */


#endif