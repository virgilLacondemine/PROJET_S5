#ifndef __ELF_SECTION_READER_H__ 
#define __ELF_SECTION_READER_H__

char* section_type_name(Elf32_Word  type_number);

char* flags_name(int f);

void elf_print_section(const char* file);

#endif
