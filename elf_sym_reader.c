#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <elf.h>
#include <string.h>

/* 32-bit ELF base types. */
typedef unsigned int Elf32_Addr;
typedef unsigned short Elf32_Half;
typedef unsigned int Elf32_Off;
typedef signed int Elf32_Sword;
typedef unsigned int Elf32_Word;

char* sym_type_name(Elf32_Word  type_number) {

	switch (type_number)
	{
		case 0:
			return "NOTYPE";
		case 1:
			return "OBJECT";
		case 2:
			return "FUNC";
		case 3:
			return "SECTION";
		case 4:
			return "FILE";
		case 13:
			return "LOPROC";
		case 15:
			return "HIPROC";
		default :
			return "NOTYPE";
	}
}

char* sym_bind_name(Elf32_Word  type_number) {

	switch (type_number)
	{
		case 0:
			return "LOCAL";
		case 1:
			return "GLOBAL";
		case 2:
			return "WEAK";
		case 13:
			return "LOPROC";
		case 15:
			return "HIPROC";
		default :
			return "LOCAL";
	}
}

char* sym_vis_name(Elf32_Word  type_number) {

	switch (type_number)
	{
		case 0:
			return "DEFAULT";
		case 1:
			return "INTERNAL";
		case 2:
			return "HIDDEN";
		case 3:
			return "PROTECTED";
		default :
			return "DEFAULT";
	}
}


char* sym_ndx_name(Elf32_Word  type_number) {

	char* buf = malloc(sizeof(char) * 16);

	switch ((int)type_number)
	{
		case 0:
			return "UND";
		case (65521):
			return "ABS";
		default :
			
			sprintf(buf,"%d",type_number);
			return buf;
	}
}

void read_sym_table(const char* file) {
	int idx;
	Elf32_Shdr data;
	Elf32_Shdr data2;
	Elf32_Ehdr hdr;


	Elf32_Sym sym_tab;
	
	char* name;
	char* name2;

	char* SectNames = "";

	FILE* fd = fopen(file, "r");
	
  	fread(&hdr, 1, sizeof(Elf32_Ehdr), fd);

	fseek(fd, hdr.e_shoff + hdr.e_shstrndx * sizeof(Elf32_Shdr), SEEK_SET);
  	fread(&data, 1, sizeof(data), fd);

	SectNames = malloc(data.sh_size);

	fseek(fd, data.sh_offset, SEEK_SET);
  	fread(SectNames, 1, data.sh_size, fd);

	for (idx = 0; idx < hdr.e_shnum; idx++)
	{
		fseek(fd, hdr.e_shoff + idx * sizeof(data), SEEK_SET);
		fread(&data, 1, sizeof(data), fd);

		name = SectNames + data.sh_name;

		if (strcmp(name,".symtab")==0) {
			name2 = name;
			data2 = data;
		}
		
	}

	
	printf("Table de symboles ' %s ' contient %i entrées:\n", name2, data2.sh_size / data2.sh_entsize);


	free(SectNames);


	fseek(fd, hdr.e_shoff + hdr.e_shstrndx * sizeof(Elf32_Shdr) + data2.sh_offset * sizeof(Elf32_Shdr), SEEK_SET);
  	fread(&sym_tab, 1, sizeof(Elf32_Sym), fd);



	SectNames = malloc(data.sh_size);

	fseek(fd, data.sh_offset, SEEK_SET);
  	fread(SectNames, 1, data.sh_size, fd);



	printf(" %6s", "Num:");
	printf("%9s", "Valeur");
	printf(" %4s", "Tail");
	printf(" %-8s", "Type");
	printf(" %-6s", "Lien");
	printf(" %-8s", "Vis");
	printf(" %5s", "Ndx");
	printf(" %-8s\n", "Nom:");


	for (idx = 0; idx < data2.sh_size / data2.sh_entsize; idx++)
	{
		fseek(fd, data2.sh_addr + data2.sh_offset + idx * sizeof(Elf32_Sym), SEEK_SET);
		fread(&sym_tab, 1, sizeof(Elf32_Sym), fd);


		printf("%6i: ",idx);
		printf("%-.8x",sym_tab.st_value);
		printf(" %4i",sym_tab.st_size);
		printf(" %-8s",sym_type_name(ELF32_ST_TYPE(sym_tab.st_info)));
		printf(" %-6s",sym_bind_name(ELF32_ST_BIND(sym_tab.st_info)));
		printf(" %-8s",sym_vis_name(sym_tab.st_other));
		printf(" %5s",sym_ndx_name(sym_tab.st_shndx));

		name = SectNames + sym_tab.st_name;
		
		printf(" %-8s\n",name);

	}

	free(SectNames);
	
}

