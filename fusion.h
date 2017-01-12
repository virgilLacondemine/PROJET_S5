#ifndef __FUSION_H__
#define __FUSION_H__

Elf32_Shdr write_elf_PROGBIT(FILE* f1, FILE* f2, Elf32_Shdr data1, Elf32_Shdr data2, char* name);
void fusion(const char* file1, const char* file2,const char* file3);

#endif
