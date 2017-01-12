#ifndef __READER_H__
#define __READER_H__

Elf32_Ehdr *getHeader(FILE * f);
unsigned char *getSection(FILE * f, Elf32_Shdr *sectionHeader);
Elf32_Shdr *getSectionHeader(FILE * f, Elf32_Ehdr *header, int i);
Elf32_Sym *getSymbolTable(FILE * f, Elf32_Shdr *sectionHeader, int i);
Elf32_Rel *getRelocationTable(FILE * f, Elf32_Shdr *sectionHeader, int i);
char* getStringTable(FILE * f, Elf32_Ehdr *header);

#endif
