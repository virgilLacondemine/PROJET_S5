#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include "lecture_header_elf.h"

int main(int argc, char const *argv[]) {

	if ( !strcmp(argv[1], "-h") )
	{
		Elf32_Ehdr *elfHeader;
		FILE* f1;

		elfHeader = malloc(sizeof * elfHeader);
			 	
		f1 = fopen(argv[2], "r");

		fseek(f1, 0, SEEK_SET);

		fread(elfHeader, sizeof(Elf32_Ehdr), 1, f1);

		if ( check_header(elfHeader) )
		{
			read_elf_header(elfHeader);
		}
		free(elfHeader);
		fclose(f1);
	}
	
	else
	{
		printf("	-h : Affichage de l'en-tête\n");
		printf("	-S : Affichage de la table des sections\n");
		printf("	-x : Affichage du contenu d'une section\n");
		printf("	-s : Affichage de la table des symboles\n");
		printf("	-r : Affichage des table de reimplantation\n");
	}

	return 0;
}

