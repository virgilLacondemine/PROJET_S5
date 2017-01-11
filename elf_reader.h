#ifndef __ELF_READER_H__
#define __ELF_READER_H__

Elf32_Ehdr *getHeader(FILE * elfFile);
Elf32_Shdr *getSectionHeader(FILE * elfFile, Elf32_Ehdr *elfHeader, int i);
Elf32_Sym *getSymbolTable(FILE * elfFile, Elf32_Shdr *elfSectionHeader, int i);
Elf32_Rel *getRelocationTable(FILE * elfFile, Elf32_Shdr *elfSectionHeader, int i);
char* getStringTable(FILE * elfFile, Elf32_Ehdr *elfHeader);

#endif
