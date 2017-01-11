#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include "elf_section.h"
#include "elf_reader.h"

/********************************************************
* Affiche la section de numéro s a partir du fichier file
*********************************************************/

void print_elf_section_num(const char* file, int s)
{
	FILE* f = fopen(file, "r");
	Elf32_Ehdr *header;
	Elf32_Shdr *sectionHeader;
	int i;
	char *name;
	char *stringTable;

	header = getHeader(f);
	stringTable = getStringTable(f, header);

	sectionHeader = getSectionHeader(f, header, s);
	unsigned char Section[sectionHeader->sh_size];

	name = stringTable + sectionHeader->sh_name;

	printf("Vidange hexadécimale de la section %s\n", name);

	fseek(f,sectionHeader->sh_offset, SEEK_SET);
	fread(Section, 1, sectionHeader->sh_size, f); // Remplissage de Section[]

	// Affichage complet du contenu de la section a l'aide du tableau de Section[] (utilise le fread)
	
	for(i=0; i<(sectionHeader->sh_size); i++)
	{
		printf("%02x ", Section[i]);
	}
	printf("\n");

	fclose(f);
	free(header);
	free(sectionHeader);
	free(stringTable);
}

/********************************************************
* Affiche la section de nom s a partir du fichier file
*********************************************************/

int print_elf_section_nom(const char* file, const char *s)
{
	FILE* f = fopen(file, "r");
	Elf32_Ehdr *header;
	Elf32_Shdr *sectionHeader;
	char *name;
	char *stringTable;
	int i = 0;

	header = getHeader(f);
	stringTable = getStringTable(f, header);

	//On cherche le nom dans notre table des sections
	do
	{
		sectionHeader = getSectionHeader(f, header, i);
		name = stringTable + sectionHeader->sh_name;
		i++;
	}while(strcmp(name, s) && i<header->e_shnum);

	if(!strcmp(name, s))
	{
		unsigned char section[sectionHeader->sh_size];
		printf("Vidange hexadécimale de la section %s\n", name);

		fseek(f, sectionHeader->sh_offset, SEEK_SET);
		fread(section, 1, sectionHeader->sh_size, f); // Remplissage de Section[]

		// Affichage complet du contenu de la section a l'aide du tableau de Section[] (utilise le fread)	
		for(i = 0; i<sectionHeader->sh_size; i++)
		{
			printf("%02x ", section[i]);
		}
		printf("\n");

	}
	else // Si le nom de section n'existe pas
	{
		printf("Le nom de section donnée n'existe pas\n");
	}

	fclose(f);
	free(stringTable);
	free(sectionHeader);
	free(header);
}

