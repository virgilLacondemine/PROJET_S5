#ifndef __ELF_SECTION_HEADER_TABLE_H__ 
#define __ELF_SECTION_HEADER_TABLE_H__

char* section_type_name(Elf32_Word  type_number);
char* flags_name(int f);

void print_elf_section_header_table(const char* file);

#endif
