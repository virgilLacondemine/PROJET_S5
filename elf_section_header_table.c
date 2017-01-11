#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <elf.h>
#include <string.h>
#include "elf_section_header_table.h"
#include "Affichage.h"
#include "elf_reader.h"


/* Lecture et affichage de la table des sections */
void print_elf_section_header_table(const char* file) {

	/* Déclaration de variables */
	Elf32_Shdr *sectionHeader;
	Elf32_Ehdr *header;
	Elf32_Shdr *stringTableHeader;
	
	int idx;
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

	for (idx = 0; idx < header->e_shnum; idx++)
	{
		sectionHeader = getSectionHeader(f, header, idx);
		name = stringTable + sectionHeader->sh_name;

		printf("  [%2u] %-20s", idx,name);
		printf("%-15s ", section_type_name(sectionHeader->sh_type));

		if (sectionHeader->sh_addr != 0)
			printf("%-8i ", sectionHeader->sh_addr);
		else
			printf("%-.8d ", 0);

		printf("%-.6x ", sectionHeader->sh_offset);
		printf("%-.6x ", sectionHeader->sh_size);
		printf("%-.2x ", sectionHeader->sh_entsize);
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



