#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "elf_reader.h"

/****************************************************
* Récupère et retourne le header d'un fichier elf.
* Paramètre : un fichier elf
*****************************************************/
Elf32_Ehdr *getHeader(FILE * elfFile){
  Elf32_Ehdr *elfHeader;
	elfHeader = malloc(sizeof(Elf32_Ehdr));
	fseek(elfFile, 0, SEEK_SET);
	fread(elfHeader, sizeof(Elf32_Ehdr), 1, elfFile);
  return elfHeader;
}

/*****************************************************************
* Récupère et retourne la section header table d'un fichier elf.
* Paramètre : un fichier elf, un header d'elf.
******************************************************************/
Elf32_Shdr *getSectionHeader(FILE * elfFile, Elf32_Ehdr *elfHeader, int i){
  Elf32_Shdr *elfSectionHeader;
  elfSectionHeader = malloc(sizeof(Elf32_Shdr));
  fseek(elfFile, elfHeader->e_shoff + i*sizeof(Elf32_Shdr), SEEK_SET);
  fread(elfSectionHeader, 1, sizeof(Elf32_Shdr), elfFile);
  return elfSectionHeader;
}

/*************************************************************************
* Récupère et retourne la symbol table d'un fichier elf.
* Paramètre : un fichier elf, une section header table elf
**************************************************************************/

Elf32_Sym *getSymbolTable(FILE * elfFile, Elf32_Shdr *elfSectionHeader, int i){
  Elf32_Sym *elfSymbolTable;
  elfSymbolTable = malloc(sizeof(Elf32_Sym));
	fseek(elfFile, elfSectionHeader->sh_addr + elfSectionHeader->sh_offset + i * sizeof(Elf32_Sym), SEEK_SET);
	fread(elfSymbolTable, 1, sizeof(Elf32_Sym), elfFile);
  return elfSymbolTable;
}

/*************************************************************************
* Récupère et retourne la relocation table d'un fichier elf.
* Paramètre : ...
**************************************************************************/

Elf32_Rel *getRelocationTable(FILE * elfFile, Elf32_Shdr *elfSectionHeader, int i){
  Elf32_Rel *elfRelocationTable;
  elfRelocationTable = malloc(sizeof(Elf32_Rel));
	fseek(elfFile, elfSectionHeader->sh_addr + elfSectionHeader->sh_offset + i * sizeof(Elf32_Rel), SEEK_SET);
	fread(elfRelocationTable, 1, sizeof(Elf32_Rel), elfFile);
  return elfRelocationTable;
}

/**********************************************************************
* Récupère et retourne la string table d'un fichier elf.
* Paramètre : un fichier elf, une section header table elf
***********************************************************************/
char* getStringTable(FILE * elfFile, Elf32_Ehdr *elfHeader){
  Elf32_Shdr *stringTableHeader;
  char* stringTable;
  stringTableHeader = malloc(sizeof(Elf32_Shdr));
  stringTableHeader = getSectionHeader(elfFile, elfHeader, elfHeader->e_shstrndx);
  stringTable = malloc(stringTableHeader->sh_size);
  fseek(elfFile, stringTableHeader->sh_offset, SEEK_SET);
  fread(stringTable, 1, stringTableHeader->sh_size, elfFile);
  free(stringTableHeader);
  return stringTable;
}
