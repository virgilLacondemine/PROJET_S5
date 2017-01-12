#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <unistd.h>

#include "display.h"
#include "reader.h"
#include "fusion.h"



int isnumber(const char* s)
{
	char* e = NULL;
	(void) strtol(s, &e, 0);
	return e != NULL && *e ==(char)0;
}



int isELF(const char* file)
{
	/**************************************************************
	* Les 4 premiers octets doivent correspondre au nombre magique
	* qui sert d'identification des fichiers ELF :
	*   ELFMAG0 == e_ident[EI_MAG0] "0x7f"
	*   ELFMAG1 == e_ident[EI_MAG1] "E"
	*   ELFMAG2 == e_ident[EI_MAG2] "L"
	*   ELFMAG3 == e_ident[EI_MAG3] "F"
	**************************************************************/

	FILE* f;
	f = fopen(file,"r");

	// Allocation memoire de l'en-tete du fichier
	Elf32_Ehdr *header;
	header = malloc(sizeof(Elf32_Ehdr));
	fseek(f, 0, SEEK_SET);
	fread(header, sizeof(Elf32_Ehdr), 1, f);

	int EIMAG0=127;
	char EIMAG1='E';
	char EIMAG2='L';
	char EIMAG3='F';

	if (header->e_ident[EI_MAG0] != EIMAG0 ||
		header->e_ident[EI_MAG1] != EIMAG1 ||
		header->e_ident[EI_MAG2] != EIMAG2 ||
		header->e_ident[EI_MAG3] != EIMAG3)
	{
		fclose(f);
		return 0;
	}
	else
	{
		fclose(f);
		return 1;
	}
}



int main(int argc, char const *argv[])
{

	if (argc == 3)
	{
		if ( !strcmp(argv[1], "-h") )
		{
			if ( !access(argv[2],R_OK)==0 )
			{
				printf("Le fichier en argument n'existe pas\n");
				return -1;
			}
			if ( !isELF(argv[2]) )
			{
				printf("Le fichier en argument n'est pas au format ELF\n");
				return -1;
			}
			display_header(argv[2]);
		}
		else if ( !strcmp(argv[1], "-S") )
		{
			if ( !access(argv[2],R_OK)==0 )
			{
				printf("Le fichier en argument n'existe pas\n");
				return -1;
			}
			if ( !isELF(argv[2]) )
			{
				printf("Le fichier en argument n'est pas au format ELF\n");
				return -1;
			}
			display_section_header_table(argv[2]);
		}
		else if ( !strcmp(argv[1], "-s") )
		{
			if ( !access(argv[2],R_OK)==0 )
			{
				printf("Le fichier en argument n'existe pas\n");
				return -1;
			}
			if ( !isELF(argv[2]) )
			{
				printf("Le fichier en argument n'est pas au format ELF\n");
				return -1;
			}
			display_symbol_table(argv[2]);
		}
		else if ( !strcmp(argv[1], "-r") )
		{
			if ( !access(argv[2],R_OK)==0 )
			{
				printf("Le fichier en argument n'existe pas\n");
				return -1;
			}
			if ( !isELF(argv[2]) )
			{
				printf("Le fichier en argument n'est pas au format ELF\n");
				return -1;
			}
			display_relocation_table(argv[2]);
		}
		else if ( !strcmp(argv[1], "-x") )
		{
			printf("L'argument -x nécessite de spécifier le numéro ou le nom de la section\n");
			return -1;
		}
		else
		{
			printf("L'option indiquée n'existe pas:\n");
			printf("	./main -h [FILE]: Affichage de l'en-tête du fichier elf [FILE]\n");
			printf("	./main -S [FILE]: Affichage de la table des sections du fichier elf [FILE]\n");
			printf("	./main -x [num] [FILE]: Affichage du contenu de la section n°[num] du fichier elf [FILE]\n");
			printf("	./main -x [name] [FILE]: Affichage du contenu de la section de nom [name] fichier elf [FILE]\n");
			printf("	./main -s [FILE]: Affichage de la table des symboles du fichier elf [FILE]\n");
			printf("	./main -r [FILE]: Affichage des table de réimplantation du fichier elf [FILE]\n");
			printf("	./main -f [FILE1] [FILE2] [FILE3]: Fusion des fichiers [FILE1] et [FILE2] dans le [FILE3]\n");
			return -1;
		}
	}
	else if (argc == 4)
	{
		if ( !strcmp(argv[1], "-x") )
		{
			if( isnumber(argv[2]) )
			{
				if ( !access(argv[3],R_OK)==0 )
				{
					printf("Le fichier en argument n'existe pas\n");
					return -1;
				}
				if ( !isELF(argv[3]) )
				{
					printf("Le fichier en argument n'est pas au format ELF\n");
					return -1;
				}

				FILE* f;
				f = fopen(argv[3], "r");

				Elf32_Ehdr *header;
				header = getHeader(f);

				if ( (argv[2]<0) || (atoi(argv[2])>=header->e_shnum) )
				{
					free(header);
					fclose(f);
					printf("Le numéro de section en argument est invalide\n");
					return -1;
				}
				free(header);
				fclose(f);
				display_section_num(argv[3], atoi(argv[2]));
			}
			else if(argv[2][0]==46) // Si le nom de fichier est potentiellement valide (commence par un point), on gere le fait qu'un nom n'existe pas dans Lecture_section.c
			{
				display_section_nom(argv[3], argv[2]);
			}
			else
			{
				printf("La section en argument est invalide\n");
				return -1;
			}
		}

		else
		{
			printf("L'option indiquée n'existe pas:\n");
			printf("	./main -h [FILE]: Affichage de l'en-tête du fichier elf [FILE]\n");
			printf("	./main -S [FILE]: Affichage de la table des sections du fichier elf [FILE]\n");
			printf("	./main -x [num] [FILE]: Affichage du contenu de la section n°[num] du fichier elf [FILE]\n");
			printf("	./main -x [name] [FILE]: Affichage du contenu de la section de nom [name] fichier elf [FILE]\n");
			printf("	./main -s [FILE]: Affichage de la table des symboles du fichier elf [FILE]\n");
			printf("	./main -r [FILE]: Affichage des table de réimplantation du fichier elf [FILE]\n");
			printf("	./main -f [FILE1] [FILE2] [FILE3]: Fusion des fichiers [FILE1] et [FILE2] dans le [FILE3]\n");
			return -1;
		}
	}
	else if (argc == 5)
	{
		if ( !strcmp(argv[1], "-f") )
		{
			if ( !access(argv[2],R_OK)==0 || !access(argv[3],R_OK)==0 )
			{
				printf("Un ou plusieurs fichiers en argument n'existent pas\n");
				return -1;
			}
			if ( !isELF(argv[2]) || !isELF(argv[3]) )
			{
				printf("Un ou plusieurs fichiers en argument ne sont pas au format ELF\n");
				return -1;
			}
			fusion(argv[2], argv[3], argv[4]);
		}
	}
	else
	{
		printf("Nombre d'arguments incorrecte:\n");
		printf("	./main -h [FILE]: Affichage de l'en-tête du fichier elf [FILE]\n");
		printf("	./main -S [FILE]: Affichage de la table des sections du fichier elf [FILE]\n");
		printf("	./main -x [num] [FILE]: Affichage du contenu de la section n°[num] du fichier elf [FILE]\n");
		printf("	./main -x [name] [FILE]: Affichage du contenu de la section de nom [name] fichier elf [FILE]\n");
		printf("	./main -s [FILE]: Affichage de la table des symboles du fichier elf [FILE]\n");
		printf("	./main -r [FILE]: Affichage des table de réimplantation du fichier elf [FILE]\n");
		printf("	./main -f [FILE1] [FILE2] [FILE3]: Fusion des fichiers [FILE1] et [FILE2] dans le [FILE3]\n");
		return -1;
	}

	return 0;

}
