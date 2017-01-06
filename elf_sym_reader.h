
char* sym_type_name(Elf32_Word  type_number);
char* sym_bind_name(Elf32_Word  type_number);
char* sym_vis_name(Elf32_Word  type_number);
char* sym_ndx_name(Elf32_Word  type_number);
void read_sym_table(const char* file);

