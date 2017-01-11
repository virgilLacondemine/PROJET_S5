#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <elf.h>
#include <string.h>
#include "elf_symbol_table.h"
#include "Affichage.h"
#include "elf_reader.h"

/* Lecture et Affichage de la table des symboles */
void print_elf_symbol_table(const char* file) {

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
	fclose(f);
		
}

