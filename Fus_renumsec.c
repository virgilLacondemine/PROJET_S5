#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "Fus_renumsec.h"
#include "elf_reader.h"

void fusion(FILE * f1, FILE * f2, FILE * f3){

	int i, j, k;
	
	Elf32_Ehdr *header1, *header2, *header3;
	Elf32_Shdr *sectionHeader1, *sectionHeader2, *sectionHeader3;
	char* stringTable1;
	char* stringTable2;
	char* stringTable3;
	char* name1="";
	char* name2="";
	char* name3="";
	
	stringTable3[0] = '\0';
	
	header1 = getHeader(f1);
	header2 = getHeader(f2);
	
	header3 = header1;
	
	fwrite(header3, 1, sizeof(header3), f3);
	
	for(i = 0; i<header1->e_shnum; i++){
		sectionHeader1 = getSectionHeader(f1, header1, i);
		stringTable1 = getStringTable(f1, header1);
		name1 = stringTable1 +  sectionHeader1->sh_name ;
		
		for(j = 0; j<header2->e_shnum || ( !strcmp(name1, name2) && sectionHeader1->sh_type==1 && sectionHeader2->sh_type==1 ); j++){
			sectionHeader2 = getSectionHeader(f2, header2, j);
			stringTable2 = getStringTable(f2, header2);
			name2 = stringTable2 +  sectionHeader2->sh_name ;			
		}
		
		if(!strcmp(name1, name2)){
			sectionHeader3 = getSectionHeader(f1, header1, i);
			name3 = name1;
			
			unsigned char *section = malloc(sectionHeader1->sh_size + sectionHeader2->sh_size);
			unsigned char *section1 = malloc(sectionHeader1->sh_size);
			unsigned char *section2 = malloc(sectionHeader2->sh_size);

			fseek(f1,sectionHeader1->sh_offset, SEEK_SET);
			fread(section1, 1, sectionHeader1->sh_size, f1);
			
			fseek(f2,sectionHeader2->sh_offset, SEEK_SET);
			fread(section2, 1, sectionHeader2->sh_size, f2);
			
			for(k = 0; k<sectionHeader1->sh_size;k++)
			{
				section[k] = section1[k];
			}
			for(k = sectionHeader1->sh_size; k<sectionHeader1->sh_size + sectionHeader2->sh_size;k++)
			{
				section[k] = section2[k - sectionHeader1->sh_size];
			}
			
			fwrite(section, 1, sizeof(section), f3);
			
			free(section);
			free(section1);
			free(section2);
		}
		
	}
	
}
