#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include "Fus_renumsec.h"

int main(int argc, char const *argv[]) {
	FILE * f1,* f2,* f3;

/*******************************************	
	f1 : fichier 1 de la fusion
	f2 : fichier 2 de la fusion
	f3 : fichier resultat de la fusion
*******************************************/
	
	f1 = fopen(argv[1], "rw");
	f2 = fopen(argv[2], "rw");	
	f3 = fopen(argv[3], "rw");
		
	fusion(f1, f2, f3);
	
	fclose(f1);
	fclose(f2);
	fclose(f3);
	
	return 0;
}
