#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "elf_header.h"
#include "Affichage.h"
#include "elf_reader.h"

/**********************************************************************
* Affichage des informations relative au header sur la sortie standard
* Paramètre : ...
**********************************************************************/
void print_elf_header(const char* file)
{

	FILE* f;
	f = fopen(file, "r");

	Elf32_Ehdr *elfHeader;
	elfHeader = getHeader(f);

	printf("* Plateforme cible :\n");
	printf("* Magique                                            :%x %x %x %x\n", elfHeader->e_ident[EI_MAG0],elfHeader->e_ident[EI_MAG1],elfHeader->e_ident[EI_MAG2],elfHeader->e_ident[EI_MAG3]);
	printf("* Classe du fichier                                  :%s\n", typeClasse(elfHeader->e_ident[EI_CLASS]));
	printf("* Encodage des données                               :%s\n", typeDonnee(elfHeader->e_ident[EI_DATA]));
	printf("* Type                                               :%s\n", typeType(elfHeader->e_type));
	printf("* Machine                                            :%s\n", typeMachine(elfHeader->e_machine));
	printf("* Version                                            :0x%s\n", typeVersion(elfHeader->e_version));
	printf("* Point d'entrée                                     :0x%x\n", elfHeader->e_entry);
	printf("* Adresse de la table des segments                   :%d\n", elfHeader->e_phoff);
	printf("* Adresse de la table de section                     :%d\n", elfHeader->e_shoff);
	printf("* Flags                                              :0x%x\n", elfHeader->e_flags);
	printf("* Taille de l'en-tete                                :%d\n", elfHeader->e_ehsize);
	printf("* Taille de la table du programme                    :%d\n", elfHeader->e_phentsize);
	printf("* Nombre d'element dans la table des segments        :%d\n", elfHeader->e_phnum);
	printf("* Taille de la table des sections                    :%d\n", elfHeader->e_shentsize);
	printf("* Nombre d'elements dans la table des sections       :%d\n", elfHeader->e_shnum);
	printf("* Table d'indexe                                     :%d\n", elfHeader->e_shstrndx);

	// c'est pour le malloc du getHeader de elf_reader.c
	free(elfHeader);
	fclose(f);
}

