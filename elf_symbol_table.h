#ifndef __ELF_SYMBOL_TABLE_H__ 
#define __ELF_SYMBOL_TABLE_H__

char* sym_type_name(Elf32_Word  type_number);
char* sym_bind_name(Elf32_Word  type_number);
char* sym_vis_name(Elf32_Word  type_number);
char* sym_ndx_name(Elf32_Word  type_number);
void print_elf_symbol_table(const char* file);

#endif

