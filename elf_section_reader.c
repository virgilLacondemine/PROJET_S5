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


/* Sémantique du nom en fonction de la valeur du type de section */
char* section_type_name(Elf32_Word  type_number) {

	switch (type_number)
	{
		case 0:
			return "NULL";
		case 1:
			return "PROGBITS";
		case 2:
			return "SYMTAB";
		case 3:
			return "STRTAB";
		case 4:
			return "RELA";
		case 5:
			return "HASH";
		case 6:
			return "DYNAMIC";
		case 7:
			return "NOTE";
		case 8:
			return "NOBITS";
		case 9:
			return "REL";
		case 10:
			return "SHLIB";
		case 11:
			return "DYNSYM";
		case 0x70000000:
			return "LOPROC";
		case 0x7fffffff:
			return "HIPROC";
		case 0x80000000:
			return "LOUSER";
		case 0xffffffff:
			return "HIUSER";
		default :
			return "???";
	}
}


/* Construction de la sémantique du FLAG en fonction des entier lus bit à bit */
char* flags_name(int f) {

	char* r = malloc(sizeof(char)*4);

		if (f & 0x1)
			r = strcat(r,"W");
		if (f & 0x2)
			r = strcat(r,"A");
		if (f & 0x4)
			r = strcat(r,"X");
		if (f & 0x10)
			r = strcat(r,"M");
		if (f & 0x20)
			r = strcat(r,"S");
		if (f & 0x40)
			r = strcat(r,"I");
		if (f & 0x80)
			r = strcat(r,"O");
		if (f & 0x100)
			r = strcat(r,"N");
		if (f & 0x200)
			r = strcat(r,"G");
		if (f & 0x400)
			r = strcat(r,"T");
		if (f & 0x0ff00000)
			r = strcat(r,"o");
		if (f & 0xf0000000)
			r = strcat(r,"P");

	return r;

}



void elf_print_section(const char* file) {


	/* Déclaration d'attributs */
	int idx;
	Elf32_Shdr data;
	Elf32_Ehdr hdr;
	char*  name;
	char* SectNames = "";

	FILE* fd = fopen(file, "r");
	
  	fread(&hdr, 1, sizeof(Elf32_Ehdr), fd);

	fseek(fd, hdr.e_shoff + hdr.e_shstrndx * sizeof(Elf32_Shdr), SEEK_SET);
  	fread(&data, 1, sizeof(data), fd);

	SectNames = malloc(data.sh_size);

	fseek(fd, data.sh_offset, SEEK_SET);
  	fread(SectNames, 1, data.sh_size, fd);

	printf("Il y a %i en-têtes de section, débutant à l'adresse de décalage 0x%x:\n",hdr.e_shnum,hdr.e_shoff);

	printf("  [%2s] %-20s", "Nr", "Nom");
	printf("%-15s ", "Type");
	printf("%-8s ", "Addr");
	printf("%-6s ", "Décala.");
	printf("%-6s ", "Taille");
	printf("%-2s ", "ES");
	printf("%-8s ", "Fan");
	printf("%-8s ", "LN");
	printf("%-8s ", "Inf");
	printf("%-8s\n", "Al");


	for (idx = 0; idx < hdr.e_shnum; idx++)
	{


		fseek(fd, hdr.e_shoff + idx * sizeof(Elf32_Shdr), SEEK_SET);
		fread(&data, 1, sizeof(Elf32_Shdr), fd);

		name = SectNames + data.sh_name;
				
		printf("  [%2u] %-20s", idx,name);	

		printf("%-15s ", section_type_name(data.sh_type));

		if (data.sh_addr != 0)
			printf("%-8i ", data.sh_addr);
		else
			printf("%-.8d ", 0);

		printf("%-.6x ", data.sh_offset);
		printf("%-.6x ", data.sh_size);
		printf("%-.2d ", data.sh_entsize);
		printf("%-8s ", flags_name(data.sh_flags));
		printf("%-8d ", data.sh_link);
		printf("%-8d ", data.sh_info);
		printf("%-8d\n", data.sh_addralign);
	}
	printf("Clé des fanions:\n W (écriture), A (allocation), X (exécution), M (fusion), S (chaînes)\n I (info), L (ordre des liens), G (groupe), T (TLS), E (exclu), x (inconnu)\n O (traiterment additionnel requis pour l'OS) o (spécifique à l'OS), p (spécifique au processeur)\n");

}
