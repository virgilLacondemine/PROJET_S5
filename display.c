#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>

#include "display.h"
#include "info.h"
#include "reader.h"



/**********************************************************************
* Affichage des informations relatives au header sur la sortie standard
* Paramètre : fichier
**********************************************************************/
void display_header(const char* file)
{
	FILE* f;
	f = fopen(file, "r");

	Elf32_Ehdr *header;
	header = getHeader(f);

	printf("* Plateforme cible :\n");
	printf("* Magique                                            :%x %x %x %x\n", header->e_ident[EI_MAG0],header->e_ident[EI_MAG1],header->e_ident[EI_MAG2],header->e_ident[EI_MAG3]);
	printf("* Classe du fichier                                  :%s\n", typeClasse(header->e_ident[EI_CLASS]));
	printf("* Encodage des données                               :%s\n", typeDonnee(header->e_ident[EI_DATA]));
	printf("* Type                                               :%s\n", typeType(header->e_type));
	printf("* Machine                                            :%s\n", typeMachine(header->e_machine));
	printf("* Version                                            :0x%s\n", typeVersion(header->e_version));
	printf("* Point d'entrée                                     :0x%x\n", header->e_entry);
	printf("* Adresse de la table des segments                   :%d\n", header->e_phoff);
	printf("* Adresse de la table de section                     :%d\n", header->e_shoff);
	printf("* Flags                                              :0x%x\n", header->e_flags);
	printf("* Taille de l'en-tete                                :%d\n", header->e_ehsize);
	printf("* Taille de la table du programme                    :%d\n", header->e_phentsize);
	printf("* Nombre d'element dans la table des segments        :%d\n", header->e_phnum);
	printf("* Taille de la table des sections                    :%d\n", header->e_shentsize);
	printf("* Nombre d'elements dans la table des sections       :%d\n", header->e_shnum);
	printf("* Table d'indexe                                     :%d\n", header->e_shstrndx);

	// c'est pour le malloc du getHeader de elf_reader.c
	free(header);
	fclose(f);
}



/* Lecture et affichage de la table des sections */
void display_section_header_table(const char* file)
{
	/* Déclaration de variables */
	Elf32_Shdr *sectionHeader;
	Elf32_Ehdr *header;

	int i;
	char* name;
	char* stringTable;

	FILE* f = fopen(file, "r");

	header = getHeader(f);
	stringTable = getStringTable(f, header);

	printf("\nIl y a %i en-têtes de section, débutant à l'adresse de décalage 0x%x:\n",header->e_shnum,header->e_shoff);
	printf("  [%2s] %-20s", "Nr", "Nom");
	printf("%-15s ", "Type");
	printf("%-8s ", "Addr");
	printf("%-6s ", "Décala.");
	printf("%-6s ", "Taille");
	printf("%-2s ", "ES");
	printf("%-8s ", "Fan");
	printf("%-8s ", "LN");
	printf("%-8s ", "Inf");
	printf("%-8s\n", "Al");

	for (i = 0; i < header->e_shnum; i++)
	{
		sectionHeader = getSectionHeader(f, header, i);
		name = stringTable + sectionHeader->sh_name;

		printf("  [%2u] %-20s", i, name);
		printf("%-15s ", section_type_name(sectionHeader->sh_type));

		if (sectionHeader->sh_addr != 0)
			printf("%-8i ", sectionHeader->sh_addr);
		else
			printf("%-.8d ", 0);

		printf("%-.6x ", sectionHeader->sh_offset);
		printf("%-.6x ", sectionHeader->sh_size);
		printf("%-.2d ", sectionHeader->sh_entsize);
		printf("%-8s ", flags_name(sectionHeader->sh_flags));
		printf("%-8d ", sectionHeader->sh_link);
		printf("%-8d ", sectionHeader->sh_info);
		printf("%-8d\n", sectionHeader->sh_addralign);

		free(sectionHeader);
	}

	printf("Clé des fanions:\n");
	printf(" W (écriture), A (allocation), X (exécution), M (fusion), S (chaînes)\n");
	printf(" I (info), L (ordre des liens), G (groupe), T (TLS), E (exclu), x (inconnu)\n");
	printf(" O (traiterment additionnel requis pour l'OS) o (spécifique à l'OS), p (spécifique au processeur)\n");

	free(header);
	free(stringTable);
	fclose(f);
}



/********************************************************
* Affiche la section de numéro s a partir du fichier file
*********************************************************/

void display_section_num(const char* file, int s)
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
	unsigned char *section = malloc(sectionHeader->sh_size);

	name = stringTable + sectionHeader->sh_name;

	printf("Vidange hexadécimale de la section %s\n", name);

	//fseek(f,sectionHeader->sh_offset, SEEK_SET);
	//fread(section, 1, sectionHeader->sh_size, f); // Remplissage de Section[]
	section = getSection(f, sectionHeader);

	// Affichage complet du contenu de la section a l'aide du tableau de Section[]

	for(i=0; i<(sectionHeader->sh_size); i++)
	{
		printf("%02x ", section[i]);
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

int display_section_nom(const char* file, const char *s)
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
		unsigned char *section = malloc(sectionHeader->sh_size);
		printf("Vidange hexadécimale de la section %s\n", name);

//		fseek(f, sectionHeader->sh_offset, SEEK_SET);
//		fread(section, 1, sectionHeader->sh_size, f); // Remplissage de Section[]
		section = getSection(f, sectionHeader);

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



/* Lecture et Affichage de la table des symboles */
void display_symbol_table(const char* file) {

	int i = 0;
	Elf32_Shdr *sectionHeader;
	Elf32_Shdr *symbolTableHeader;
	Elf32_Ehdr *header;
	Elf32_Sym *symbolTable;
	char* name;
	char* stringTable;


	FILE* f = fopen(file, "r");

	header = getHeader(f);
	stringTable = getStringTable(f, header);

	for (i = 0; i < header->e_shnum; i++)
	{
		sectionHeader = getSectionHeader(f, header, i);
		name = stringTable + sectionHeader->sh_name;

		if (strcmp(name,".symtab")==0)
		{
			symbolTableHeader = sectionHeader;
		}
	}


	printf("\nTable de symboles '.symtab' contient %i entrées:\n", symbolTableHeader->sh_size / symbolTableHeader->sh_entsize);

	fseek(f, sectionHeader->sh_offset, SEEK_SET);
 	fread(stringTable, 1, sectionHeader->sh_size, f);

	printf(" %6s", "Num:");
	printf("%9s", "Valeur");
	printf(" %4s", "Tail");
	printf(" %-8s", "Type");
	printf(" %-6s", "Lien");
	printf(" %-8s", "Vis");
	printf(" %5s", "Ndx");
	printf(" %-8s\n", "Nom:");

	for (i = 0; i < symbolTableHeader->sh_size / symbolTableHeader->sh_entsize; i++)
	{
		symbolTable = getSymbolTable(f, symbolTableHeader, i);

		printf("%6i: ",i);
		printf("%-.8x",symbolTable->st_value);
		printf(" %4i",symbolTable->st_size);
		printf(" %-8s",sym_type_name(ELF32_ST_TYPE(symbolTable->st_info)));
		printf(" %-6s",sym_bind_name(ELF32_ST_BIND(symbolTable->st_info)));
		printf(" %-8s",sym_vis_name(symbolTable->st_other));
		printf(" %5s",sym_ndx_name(symbolTable->st_shndx));

		name = stringTable + symbolTable->st_name;

		printf(" %-8s\n",name);
	}

	free(stringTable);
	free(header);
	free(sectionHeader);
	free(symbolTableHeader);
	free(symbolTable);
	fclose(f);

}



/* Lecture et affichage de la table de relocation */
void display_relocation_table(const char* file)
{

	/* Déclaration de variables */
	int i;
	Elf32_Shdr *sectionHeader;
	Elf32_Shdr *relocationTableHeader;
	Elf32_Ehdr *header;
	Elf32_Rel *relocationTable;
	char* name;
	char* stringTable;


	FILE* f = fopen(file, "r");

	header = getHeader(f);
	stringTable = getStringTable(f, header);

	/* Parcours des sections jusqu'à '.rel.text' */
	for (i = 0; i < header->e_shnum; i++)
	{
		sectionHeader = getSectionHeader(f, header, i);
		name = stringTable + sectionHeader->sh_name;

		if (strcmp(name,".rel.text")==0)
		{
			relocationTableHeader = sectionHeader;
		}
	}

	free(stringTable);

	printf("\nSection de relocalisation '.rel.text' à l'adresse de décalage 0x%x contient %i entrées:\n", relocationTableHeader->sh_offset,relocationTableHeader->sh_size / relocationTableHeader->sh_entsize);
	printf("%8s ", " Décalage");
	printf("%6s ", "Info");
	printf("%8s\n", "Type");

	for (i = 0; i < relocationTableHeader->sh_size / relocationTableHeader->sh_entsize; i++)
	{
		relocationTable = getRelocationTable(f, relocationTableHeader, i);

		printf("%-.8x ",relocationTable->r_offset);
		printf("%-.8x ",relocationTable->r_info);
		printf("%-8s",rel_type_name(ELF32_R_TYPE(relocationTable->r_info)));
		printf("\n");
	}

	free(sectionHeader);
	free(relocationTableHeader);
	free(header);
	free(relocationTable);
	fclose(f);
}
