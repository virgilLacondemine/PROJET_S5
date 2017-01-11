#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <elf.h>
#include <string.h>
#include "elf_relocation_table.h"
#include "Affichage.h"
#include "elf_reader.h"

/* Lecture et affichage de la table de relocation */
void print_relocation_table(const char* file)
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

}
