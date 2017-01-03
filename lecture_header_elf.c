#include <stdio.h>
#include <stdin.h>
#include <elf.h>
#include "lecture_header_elf.h"

int main(int argc, char const *argv[]) {
  Elf32_Ehdr elfHeader;

  return 0;
}

/********************************************************
* Fonction qui permet de lire l'header d'un fichier ELF.
* Paramètre : ...
* Retourne : ...
*********************************************************/
int lecture_header(Elf32_Ehdr *elfHeader){

  /**************************************************************
  * On vérifie que le fichier est bien au format ELF, sinon retourne
  * une erreur (ici -1).
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
}
