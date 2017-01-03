#include <stdio.h>
#include <stdin.h>
#include <elf.h>
#include "lecture_header_elf.h"

int main(int argc, char const *argv[]) {
  Elf32_Ehdr elfHeader;

  return 0;
}

/********************************************************
* Valide le header d'un fichier ELF.
* Paramètre : ...
* Retourne : -1 si le header n'est pas au format ELF
*             0 si le header est au format ELF
*********************************************************/
int check_header(Elf32_Ehdr *elfHeader){

  /**************************************************************
  * Les 4 premiers octets doivent correspondre au nombre magique
  * qui sert d'identification des fichiers ELF :
  *   ELFMAG0 == e_ident[EI_MAG0] "0x7f"
  *   ELFMAG1 == e_ident[EI_MAG1] "E"
  *   ELFMAG2 == e_ident[EI_MAG2] "L"
  *   ELFMAG3 == e_ident[EI_MAG3] "F"
  **************************************************************/
  if (elfHeader->e_ident[EI_MAG0] != EIMAG0 ||
      elfHeader->e_ident[EI_MAG1] != EIMAG1 ||
      elfHeader->e_ident[EI_MAG2] != EIMAG2 ||
      elfHeader->e_ident[EI_MAG3] != EIMAG3) {
    return -1;
  }

	else {
		return 0;
	}
}

/**********************************************************************
* Affichage des informations relative au header sur la sortie standard
* Paramètre : ...
**********************************************************************/
void read_elf_header(Elf32_Ehdr *elfHeader){
  printf("* Plateforme cible :\n");
  printf("*   Architecture                                     :\n", elfHeader->e_machine);
  printf("*   Encodage des données                             :\n", elfHeader->e_ident[EI_DATA]);
  printf("*\n");
  printf("* Taille des mots                                    :\n", elfHeader->e_ident[EI_CLASS]);
  printf("* Type de fichier ELF                                :\n", elfHeader->e_type);
  printf("* Specification de la table des sections :\n", );
  printf("*   Position dans le fichier (offset)                :\n", elfHeader->e_shnum);
  printf("*   Taille globale                                   :\n", elfHeader->e_shentsize);
  printf("*   Nombre d'entree                                  :\n", );
  printf("* Entree de la table des chaines de noms de sections :\n", elfHeader->e_shstrndx);
  printf("* Taille de l'en-tete                                :\n", elfHeader->e_ehsize);
}
