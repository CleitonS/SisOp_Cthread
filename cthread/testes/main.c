/*Teste da função ccreate*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/contextCthread.c"


void* first(){
  printf("Thread first.\n");
}
void* second(){
  printf("Thread second.\n");
}
void* third(){
  printf("Thread third.\n");
}


int main(){

  int firstID, secondID, thirdID;

  firstID = ccreate(first,(void *) NULL,0);
  printf("first TID: %d\n", firstID);




}
