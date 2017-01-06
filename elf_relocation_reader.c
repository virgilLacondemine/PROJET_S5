#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <elf.h>
#include <string.h>
#include "elf_relocation_reader.h"

/* 32-bit ELF base types. */
typedef unsigned int Elf32_Addr;
typedef unsigned short Elf32_Half;
typedef unsigned int Elf32_Off;
typedef signed int Elf32_Sword;
typedef unsigned int Elf32_Word;


void read_rel_table(const char* file) {
	int idx;
	Elf32_Shdr data;
	Elf32_Shdr data2;
	Elf32_Ehdr hdr;


	Elf32_Rel rel_tab;
	
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

		if (strcmp(name,".rel.text")==0) {
			name2 = name;
			data2 = data;
		}
		
	}


	free(SectNames);

	fseek(fd, hdr.e_shoff + hdr.e_shstrndx * sizeof(Elf32_Shdr) + data2.sh_offset * sizeof(Elf32_Shdr), SEEK_SET);
  	fread(&rel_tab, 1, sizeof(Elf32_Rel), fd);


	printf("\nSection de relocalisation '%s' à l'adresse de décalage 0x%x contient %i entrées:\n",name2, data2.sh_offset,data2.sh_size / data2.sh_entsize);


	printf("%8s ", " Décalage");
	printf("%6s ", "Info");
	printf("%-8s\n", "Type");

	
	for (idx = 0; idx < data2.sh_size / data2.sh_entsize; idx++)
	{
		fseek(fd, data2.sh_addr + data2.sh_offset + idx * sizeof(Elf32_Rel), SEEK_SET);
		fread(&rel_tab, 1, sizeof(Elf32_Rel), fd);


		printf("%-.8x ",rel_tab.r_offset);
		printf("%-.8x ",rel_tab.r_info);
		printf("%-8i",ELF32_R_TYPE(rel_tab.r_info));

		printf("\n");

	}

}
