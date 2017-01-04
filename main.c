#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include "lecture_header_elf.h"

int main(int argc, char const *argv[]) {

	// On ouvre le premier fichier
	FILE* f1;
	f1 = fopen(argv[2], "r");

	// On definie et alloue la memoire pour
	// chaque partie du fichier ELF
	Elf32_Ehdr *elfHeader;
	elfHeader = malloc(sizeof * elfHeader);

	// On stocke chaque partie du fichier ELF
	fseek(f1, 0, SEEK_SET);
	fread(elfHeader, sizeof(Elf32_Ehdr), 1, f1);

	// Si le fichier n'est pas au format ELF, il y a une erreur
	if ( !check_header(elfHeader) )
	{
		return -1;
	}

	// Affichage de l'en-tête si option "-h"
	if ( !strcmp(argv[1], "-h") )
	{
		read_elf_header(elfHeader);
	}

	// si aucune des option valable n'est utilisee en
	// second argument, on affiche l'ensemble des options 
	else
	{
		printf("	-h : Affichage de l'en-tête\n");
		printf("	-S : Affichage de la table des sections\n");
		printf("	-x : Affichage du contenu d'une section\n");
		printf("	-s : Affichage de la table des symboles\n");
		printf("	-r : Affichage des table de reimplantation\n");
	}

	// On libere toutes la memoire allouee precedement
	free(elfHeader);
	fclose(f1);

	return 0;
}

