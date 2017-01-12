#ifndef __DISPLAY_H__
#define __DISPLAY_H__

void display_header(const char* file);

void display_section_header_table(const char* file);

void display_section_num(const char* file, int s);
int display_section_nom(const char* file, const char *s);

void display_symbol_table(const char* file);

void display_relocation_table(const char* file);

#endif
