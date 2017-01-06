#ifndef __ELF_HEADER__
#define __ELF_HEADER__


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

void print_elf_header(const char* file);

#endif

