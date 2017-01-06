#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include "lecture_header_elf.h"
#include "elf_section_reader.h"
#include "lecture_section.h"
#include "elf_relocation_reader.h"
#include "elf_sym_reader.h"

int main(int argc, char const *argv[]) {

	// incrementeur
	int i;
	// On ouvre le premier fichier
	FILE* f1;
	if ( argc == 3 )
	{
		f1 = fopen(argv[2], "r");
	}
	else if ( argc == 4 )
	{
		f1 = fopen(argv[3], "r");
	}
	else
	{
		printf("Nombre d'arguments incorrecte\n");
		return -1;
	}

	// On definie et alloue la memoire pour
	// chaque partie du fichier ELF
	Elf32_Ehdr *elfHeader;
	elfHeader = malloc(sizeof * elfHeader);
	fseek(f1, 0, SEEK_SET);
	fread(elfHeader, sizeof(Elf32_Ehdr), 1, f1);


//	Elf32_Shdr *elfSectionHeader;
//	elfSectionHeader = malloc(sizeof * elfSectionHeader);
//	fseek(f1, elfHeader->e_shoff, SEEK_SET);
//	fread(elfSectionHeader, sizeof(Elf32_Shdr), 1, f1);

	// Si le fichier n'est pas au format ELF, il y a une erreur
	if ( !check_header(elfHeader) )
	{
		return -1;
	}

	// Affichage de l'en-tête si option "-h"
	if ( !strcmp(argv[1], "-h") && argc == 3)
	{
		read_elf_header(elfHeader);
	}

	// Affichage de la table des sections si option "-S"
	else if ( !strcmp(argv[1], "-S") && argc == 3 )
	{
		elf_print_section(argv[2]);
	}

	// Affichage de'une section x si option "-x" et que n°x
	else if ( !strcmp(argv[1], "-x") && argc == 4)
	{
		if( (argv[2][0]>47) && (argv[2][0]<58) )
		{
			
			if ( (argv[2]>=0) && (atoi(argv[2])<elfHeader->e_shnum) )
			{
				read_elf_section_num(argv[3], atoi(argv[2]));
			}
			else
			{
				printf("Numéro de section invalide");
				return -1;
			}
		}
		else if(argv[2][0]==46) // Si le nom de fichier est potentiellement valide on gere le fait qu'un nom n'existe pas dans Lecture_section.c
		{
			read_elf_section_nom(argv[3], argv[2]);
		}
		else
		{
			printf("L'argument concernant la section est invalide\n");
			return -1;
		}
	}
	
	// Affichage de la table des symboles si option "-s"
	else if ( !strcmp(argv[1], "-s") && argc == 3 )
	{
		read_sym_table(argv[2]);
	}
	
	// Affichage de la table de relocation si option "-r"
	else if ( !strcmp(argv[1], "-r") && argc == 3 )
	{
		read_rel_table(argv[2]);
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

