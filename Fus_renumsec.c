#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

void fusion(FILE * f1, FILE * f2, FILE * f3){

	Elf32_Shdr data1, data2;
	Elf32_Ehdr hdr1, hdr2;
	char* sectNames1, sectNames2;
	char* name1, name2;
	
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
  for (int idx = 0; idx < hdr.e_shnum; idx++)
	{

		fseek(f1, hdr1.e_shoff + idx * sizeof(Elf32_Shdr), SEEK_SET);
		fread(&data1, 1, sizeof(Elf32_Shdr), f1);		
		
		if(data1.sh_type == 1) // Si le data1.sh_type est un PROGBITS
		{
			// Parcour des types de data2
			for (int idy = 0; idy < hdr.e_shnum; idy++)
			{
				fseek(f2, hdr2.e_shoff + idy * sizeof(Elf32_Shdr), SEEK_SET);
				fread(&data2, 1, sizeof(Elf32_Shdr), f2);
				
				if(data2.sh_type == 1)
				{
					name2 = sectNames2 + data2.sh_name;
					name1 = sectNames1 + data1.sh_name;
					
					if(!strcmp(name1, name2))
					{
						
					}
				}
			}
		}
	}
}
