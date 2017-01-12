#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "fusion.h"

Elf32_Shdr write_elf_PROGBIT(FILE* f1, FILE* f2, Elf32_Shdr data1, Elf32_Shdr data2, char* name)
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

	printf("-------%s--------\n",name);
	printf("\n");
	printf("Section 1 : \n\n");

	for(int i=0; i<data1.sh_size; i++)
	{
		printf("%x",Section1[i]);
	}

	printf("\n");
	printf("\n");
	printf("Section 2 : \n\n");

	for(int i=0; i<data2.sh_size; i++)
	{
		printf("%x",Section2[i]);
	}

	printf("\n");
	printf("\n");
	printf("Section finale : \n\n");

	for(int i=0; i<data1.sh_size + data2.sh_size; i++)
	{
		printf("%x",Section1[i]);
	}

	printf("\n");
	printf("\n");
	printf("\n");

	data1.sh_size = data1.sh_size + data2.sh_size;

	return data1;

}

void fusion(const char* file1, const char* file2,const char* file3)
{
	FILE* f1;
	FILE* f2;
	FILE* f3;

	f1 = fopen(file1, "r");
	f2 = fopen(file2, "r");
	f3 = fopen(file3, "w");

	Elf32_Shdr data1, data2;
	Elf32_Ehdr hdr1, hdr2;
	char* sectNames1, * sectNames2;
	char* name1, * name2, * name;
	int u_should_not_pass[50];
	int i1=0, i2=1, j=0;


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

		// Parcour des types de data2
		for (int idy = 0; idy < hdr2.e_shnum; idy++)
		{
			fseek(f2, hdr2.e_shoff + idy * sizeof(Elf32_Shdr), SEEK_SET);
			fread(&data2, 1, sizeof(Elf32_Shdr), f2);

			if(u_should_not_pass[idy] != idy)
			{
				if(data1.sh_type == 1) // Si le data1.sh_type est un PROGBITS
				{

					if(data2.sh_type == 1)
					{
						name2 = sectNames2 + data2.sh_name;
						name1 = sectNames1 + data1.sh_name;

						if(!strcmp(name1, name2))
						{
							u_should_not_pass[idy]=idy;
							j++;
						}
					}
				}
			}
		}

	}

	Elf32_Shdr data[sizeof(Elf32_Shdr)* (hdr1.e_shnum + hdr2.e_shnum - j)];


	// Parcour des types de data1 / Pour le PROGBITS
	for (int idx = 0; idx < hdr1.e_shnum; idx++)
	{
		fseek(f1, hdr1.e_shoff + idx * sizeof(Elf32_Shdr), SEEK_SET);
		fread(&data1, 1, sizeof(Elf32_Shdr), f1);

		// Parcour des types de data2
		for (int idy = 0; idy < hdr2.e_shnum; idy++)
		{
			fseek(f2, hdr2.e_shoff + idy * sizeof(Elf32_Shdr), SEEK_SET);
			fread(&data2, 1, sizeof(Elf32_Shdr), f2);

			if(u_should_not_pass[idy] != idy)
			{
				data[i1] = data1;
				data[hdr1.e_shnum + i2] = data2;
				i2++;
			}
			else
			{
				if(data1.sh_type == 1) // Si le data1.sh_type est un PROGBITS
				{
					if(data2.sh_type == 1)
					{
						name2 = sectNames2 + data2.sh_name;
						name1 = sectNames1 + data1.sh_name;

						if(!strcmp(name1, name2))
						{
							data1 = write_elf_PROGBIT(f1,f2,data1,data2,name1);
							data[i1] = data1;
							u_should_not_pass[idy]=idy;
						}
					}
				}
			}
		}

		i1++;


	}

	printf("\nIl y a %i en-têtes de section, débutant à l'adresse de décalage 0x%x:\n", hdr1.e_shnum + hdr2.e_shnum - j, hdr1.e_shoff);

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

	for (int idx = 0; idx < hdr1.e_shnum + hdr2.e_shnum - j ; idx++)
	{
		/* L'adresse contenu dans name devient celle du début de la String Table auquel on rajoute l'offset correspondant au nom section */

		if(idx < hdr1.e_shnum)
			name = sectNames1 + data[idx].sh_name;
		else
			name = sectNames2 + data[idx].sh_name;

		printf("  [%2u] %-20s", idx,name);

		printf("%-15d ", data[idx].sh_type);

		if (data1.sh_addr != 0)
			printf("%-8i ", data[idx].sh_addr);
		else
			printf("%-.8d ", 0);

		printf("%-.6x ", data[idx].sh_offset);
		printf("%-.6x ", data[idx].sh_size);
		printf("%-.2x ", data[idx].sh_entsize);
		printf("%-8d ", data[idx].sh_flags);
		printf("%-8d ", data[idx].sh_link);
		printf("%-8d ", data[idx].sh_info);
		printf("%-8d\n", data[idx].sh_addralign);
	}

	printf("Clé des fanions:\n");
	printf(" W (écriture), A (allocation), X (exécution), M (fusion), S (chaînes)\n");
	printf(" I (info), L (ordre des liens), G (groupe), T (TLS), E (exclu), x (inconnu)\n");
	printf(" O (traiterment additionnel requis pour l'OS) o (spécifique à l'OS), p (spécifique au processeur)\n");


	// fichier 3
	hdr1.e_shnum = hdr1.e_shnum + hdr2.e_shnum - j;
	fwrite(&hdr1,sizeof(Elf32_Ehdr),1,f3);
	fwrite(&sectNames1,sizeof(Elf32_Ehdr),1,f3);
	fread(&hdr1, 1, sizeof(Elf32_Ehdr), f3);
	fseek(f3, hdr1.e_shoff + hdr1.e_shstrndx * sizeof(Elf32_Shdr), SEEK_SET);
	fwrite(data,sizeof(Elf32_Shdr),1,f3);

	fclose(f1);
	fclose(f2);
	fclose(f3);
}

