#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>

void write_elf_PROGBIT(FILE* f1, FILE* f2, Elf32_Shdr data1, Elf32_Shdr data2)
{

	unsigned char Section1[data1.sh_size+data2.sh_size]; // Pour le stockage du contenu de la section
	unsigned char Section2[data2.sh_size];	
	
	fseek(f2, data2.sh_offset, SEEK_SET);
	fread(Section2, 1, data2.sh_size, f2);
	
	fseek(f1, data1.sh_offset, SEEK_SET);
	fread(Section1, 1, data1.sh_size, f1);
	
	for(int i=0; i<data2.sh_size; i++)
	{	
		Section1[data1.sh_size + i]=Section2[i];		
	}
	
	printf("-------YOLO--------\n");	
	printf("Section finale : \n");
	
	for(int i=0; i<data1.sh_size + data2.sh_size; i++)
	{
		printf("%x",Section1[i]);
	}
	
	printf("\n");	
	printf("Section 1 : \n");
	
	for(int i=0; i<data1.sh_size; i++)
	{
		printf("%x",Section1[i]);
	}
	
	printf("\n");
	printf("Section 2 : \n");
	
	for(int i=0; i<data2.sh_size; i++)
	{
		printf("%x",Section2[i]);
	}
	
	printf("\n");
	printf("--------PUIS--------\n");
	printf("Section lue : \n");

	fwrite(&Section1,sizeof(Section1),1,f1);
	fseek(f1, data1.sh_offset, SEEK_SET);
	fread(Section1, 1, data1.sh_size + data2.sh_size, f1);
	
	for(int i=0; i<data1.sh_size + data2.sh_size; i++)
	{
		printf("%x",Section1[i]);
	}
	
	printf("\n");
	printf("--------------------\n");
	
	
	//4b02de50b08de2cd04de2030a0e3830be5000000000000a43120
	//4b02de50b08de2cd04de2030a0e3830be530a0e10d04be24b09de41eff2fe1

	data1.sh_size = data1.sh_size + data2.sh_size;
	data1.sh_entsize = data1.sh_entsize + data2.sh_entsize;
	
	fseek(f1, data1.sh_offset, SEEK_SET);
	fwrite(&data1,sizeof(Elf32_Shdr),1,f1);	
	
	
}

void fusion(FILE * f1, FILE * f2, FILE * f3)
{

	Elf32_Shdr data1, data2;
	Elf32_Ehdr hdr1, hdr2;
	char* sectNames1, * sectNames2;
	char* name1, * name2;
	
	// fichier 1
	fread(&hdr1, 1, sizeof(Elf32_Ehdr), f1);

	fseek(f1, hdr1.e_shoff + hdr1.e_shstrndx * sizeof(Elf32_Shdr), SEEK_SET);
	fread(&data1, 1, sizeof(Elf32_Shdr), f1);

	sectNames1 = malloc(data1.sh_size);

	fseek(f1, data1.sh_offset, SEEK_SET);
	fread(sectNames1, 1, data1.sh_size, f1);
 
	// fichier 2
	fread(&hdr2, 1, sizeof(Elf32_Ehdr), f2);

	fseek(f2, hdr2.e_shoff + hdr2.e_shstrndx * sizeof(Elf32_Shdr), SEEK_SET);
	fread(&data2, 1, sizeof(Elf32_Shdr), f2);

	sectNames2 = malloc(data2.sh_size);

	fseek(f2, data2.sh_offset, SEEK_SET);
	fread(sectNames2, 1, data2.sh_size, f2);
  
	// Parcour des types de data1 / Pour le PROGBITS
	for (int idx = 0; idx < hdr1.e_shnum; idx++)
	{
		fseek(f1, hdr1.e_shoff + idx * sizeof(Elf32_Shdr), SEEK_SET);
		fread(&data1, 1, sizeof(Elf32_Shdr), f1);		
		
		if(data1.sh_type == 1) // Si le data1.sh_type est un PROGBITS
		{
			// Parcour des types de data2
			for (int idy = 0; idy < hdr2.e_shnum; idy++)
			{
				fseek(f2, hdr2.e_shoff + idy * sizeof(Elf32_Shdr), SEEK_SET);
				fread(&data2, 1, sizeof(Elf32_Shdr), f2);
				
				if(data2.sh_type == 1)
				{
					name2 = sectNames2 + data2.sh_name;
					name1 = sectNames1 + data1.sh_name;
					
					if(!strcmp(name1, name2))
					{
						write_elf_PROGBIT(f1,f2,data1,data2);
					}
				}
			}
		}

	}
}
