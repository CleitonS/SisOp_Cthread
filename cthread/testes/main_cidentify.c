/*Teste da função cidentify*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/cthread.c"

int main(){	
	int size = 1000;
	char *name = malloc(size * sizeof(char));
	cidentify(name, size);
	printf("Nomes: %s\n", name);	
	return 0;
}
