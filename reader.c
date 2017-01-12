#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "reader.h"

/****************************************************
* Récupère et retourne le header d'un fichier elf.
* Paramètre : un fichier elf
*****************************************************/
Elf32_Ehdr *getHeader(FILE * f)
{
    Elf32_Ehdr *header;
    header = malloc(sizeof(Elf32_Ehdr));
    fseek(f, 0, SEEK_SET);
    fread(header, sizeof(Elf32_Ehdr), 1, f);
    return header;
}

unsigned char *getSection(FILE * f, Elf32_Shdr *sectionHeader)
{
    unsigned char *section;
    section = malloc(sectionHeader->sh_size);
    fseek(f, sectionHeader->sh_offset, SEEK_SET);
    fread(section, 1, sectionHeader->sh_size, f);
    return section;
}

/********************************************************************
* Récupère et retourne une section header table d'un fichier elf.
* Paramètre : un fichier elf, un header d'elf, l'indexe de la section
*********************************************************************/
Elf32_Shdr *getSectionHeader(FILE * f, Elf32_Ehdr *header, int i)
{
    Elf32_Shdr *sectionHeader;
    sectionHeader = malloc(sizeof(Elf32_Shdr));
    fseek(f, header->e_shoff + i*sizeof(Elf32_Shdr), SEEK_SET);
    fread(sectionHeader, 1, sizeof(Elf32_Shdr), f);
    return sectionHeader;
}

/********************************************************************************
* Récupère et retourne une symbol table d'un fichier elf.
* Paramètre : un fichier elf, une section header table elf, l'indexe du symbole
*********************************************************************************/
Elf32_Sym *getSymbolTable(FILE * f, Elf32_Shdr *sectionHeader, int i)
{
    Elf32_Sym *symbolTable;
    symbolTable = malloc(sizeof(Elf32_Sym));
    fseek(f, sectionHeader->sh_addr + sectionHeader->sh_offset + i * sizeof(Elf32_Sym), SEEK_SET);
    fread(symbolTable, 1, sizeof(Elf32_Sym), f);
    return symbolTable;
}

/************************************************************************************
* Récupère et retourne une relocation table d'un fichier elf.
* Paramètre : un fichier elf, une section header table elf, l'indexe de la relocation
*************************************************************************************/
Elf32_Rel *getRelocationTable(FILE * f, Elf32_Shdr *sectionHeader, int i)
{
    Elf32_Rel *relocationTable;
    relocationTable = malloc(sizeof(Elf32_Rel));
    fseek(f, sectionHeader->sh_addr + sectionHeader->sh_offset + i * sizeof(Elf32_Rel), SEEK_SET);
    fread(relocationTable, 1, sizeof(Elf32_Rel), f);
    return relocationTable;
}

/**********************************************************************
* Récupère et retourne la string table d'un fichier elf.
* Paramètre : un fichier elf, une section header table elf
***********************************************************************/
char* getStringTable(FILE * f, Elf32_Ehdr *header)
{
    Elf32_Shdr *stringTableHeader;
    char* stringTable;
    stringTableHeader = malloc(sizeof(Elf32_Shdr));
    stringTableHeader = getSectionHeader(f, header, header->e_shstrndx);
    stringTable = malloc(stringTableHeader->sh_size);
    fseek(f, stringTableHeader->sh_offset, SEEK_SET);
    fread(stringTable, 1, stringTableHeader->sh_size, f);
    free(stringTableHeader);
    return stringTable;
}
