#ifndef __LECTURE_HEADER_ELF_H__ 
#define __LECTURE_HEADER_ELF_H__

int check_header(Elf32_Ehdr *elfHeader);

// fonction de renomage des elements de la structure elfheader

char* typeClasse(unsigned char ei_class);
char* typeDonnee(unsigned char ei_data);
char* typeType(unsigned char type);
char* typeVersion(unsigned char version);
char* typeMachine(unsigned char machine);

/**********************************************************************
* Affichage des informations relative au header sur la sortie standard
* Paramètre : ...
**********************************************************************/

void read_elf_header(Elf32_Ehdr *elfHeader);

#endif

