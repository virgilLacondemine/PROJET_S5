#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include "elf_section.h"

/********************************************************
* Affiche la section de numéro s a partir du fichier file
*********************************************************/

void print_elf_section_num(const char* file, int s)
{
	FILE* f = fopen(file, "r");
	Elf32_Ehdr hdr;
	Elf32_Shdr data;
	char *name;
	char *SectNames;
	unsigned char Section[sizeof(data)]; // Pour le stockage du contenu de la section
	
	// Recuperation des données nécessaires
	fseek(f, 0, SEEK_SET);
	fread(&hdr, 1, sizeof(Elf32_Ehdr), f);

	fseek(f, hdr.e_shoff + hdr.e_shstrndx * sizeof(Elf32_Shdr), SEEK_SET);
	fread(&data, 1, sizeof(data), f);

	SectNames = malloc(data.sh_size);

	// Recuperation de la string table			
	fseek(f, data.sh_offset, SEEK_SET);
	fread(SectNames, 1, data.sh_size, f);

	fseek(f, hdr.e_shoff + s * sizeof(data), SEEK_SET);
	fread(&data, 1, sizeof(data), f);
	
	name = SectNames + data.sh_name;

	printf("Vidange hexadécimale de la section %s\n", name);

	fseek(f, data.sh_offset, SEEK_SET);
	fread(Section, 1, data.sh_size, f); // Remplissage de Section[]

	// Affichage complet du contenu de la section a l'aide du tableau de Section[] (utilise le fread)
	
	for(int i=0; i<data.sh_size; i++)
	{
		printf("%02x ", Section[i]);
	}
	printf("\n");

	fclose(f);
	free(SectNames);
}

/********************************************************
* Affiche la section de nom s a partir du fichier file
*********************************************************/

int print_elf_section_nom(const char* file, const char *s)
{
	FILE* f = fopen(file, "r");
	Elf32_Ehdr hdr;
	Elf32_Shdr data;
	char *name;
	char *SectNames;
	int i =0;
	unsigned char Section[sizeof(data)]; // Pour le stockage du contenu de la section

	// Recuperation des données nécessaires
	fseek(f, 0, SEEK_SET);
	fread(&hdr, 1, sizeof(Elf32_Ehdr), f);

	fseek(f, hdr.e_shoff + hdr.e_shstrndx * sizeof(Elf32_Shdr), SEEK_SET);
	fread(&data, 1, sizeof(data), f);

	SectNames = malloc(data.sh_size);

	// Recuperation de la string table
	fseek(f, data.sh_offset, SEEK_SET);
	fread(SectNames, 1, data.sh_size, f);

	//On cherche le nom dans notre table des sections
	do
	{
		fseek(f, hdr.e_shoff + i*sizeof(data), SEEK_SET);
		fread(&data, 1, sizeof(data), f);

		name = SectNames + data.sh_name;
		i++;
	}while(strcmp(name, s) && i<hdr.e_shnum);

	if(!strcmp(name, s))
	{
		printf("Vidange hexadécimale de la section %s\n", name);

		fseek(f, data.sh_offset, SEEK_SET);
		fread(Section, 1, data.sh_size, f); // Remplissage de Section[]

		// Affichage complet du contenu de la section a l'aide du tableau de Section[] (utilise le fread)	
		for(int j = 0; j<data.sh_size; j++)
		{
			printf("%02x ", Section[j]);
		}
		printf("\n");

	}
	else // Si le nom de section n'existe pas
	{
		printf("Le nom de section donnée n'existe pas\n");
	}

	fclose(f);
	free(SectNames);
}

















