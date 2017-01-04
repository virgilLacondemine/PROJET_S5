#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "lecture_header_elf.h"

/********************************************************
* Valide le header d'un fichier ELF.
* Paramètre : ...
* Retourne : 0 si le header n'est pas au format ELF
*            1 si le header est au format ELF
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
  
	int EIMAG0=127;
	char EIMAG1='E';
	char EIMAG2='L';
	char EIMAG3='F';
  
  if (elfHeader->e_ident[EI_MAG0] != EIMAG0 ||
     elfHeader->e_ident[EI_MAG1] != EIMAG1 ||
      elfHeader->e_ident[EI_MAG2] != EIMAG2 ||
      elfHeader->e_ident[EI_MAG3] != EIMAG3) {
    return 0;
  }
	else {
		return 1;
	}
}

// fonction de renomage des elements de la structure elfheader

char* typeClasse(unsigned char ei_class){
	switch(ei_class){
		case ELFCLASSNONE: return "Invalid Class";
		case ELFCLASS32: return "32-bit objects";
		case ELFCLASS64: return "64-bit objects";
		default: return "Unknow";
	}
}

char* typeDonnee(unsigned char ei_data){
	switch(ei_data){
		case ELFDATANONE: return "Invalid data encoding";
		case ELFDATA2LSB: return "Little Endian";
		case ELFDATA2MSB: return "Big Endian";
		default: return "Unknow";
	}
}

char* typeType(unsigned char type){
	switch(type){
		case ET_NONE: return "No file type";
		case ET_REL: return "Relocatable file"; 
		case ET_EXEC: return "Executable file";
		case ET_DYN: return "Shared object file";
		case ET_CORE: return "Core file";
		default: return "Unknow";
	}
}

char* typeVersion(unsigned char version){
	switch(version){
		case EV_NONE: return "0 (INVALID)";
		case EV_CURRENT: return "1 (CURRENT)"; 
		default: return "Unknow";
	}
}

char* typeMachine(unsigned char machine){
	switch(machine){
		case EM_NONE: return "No machine";
		case EM_M32: return "AT&T WE 32100";
		case EM_SPARC: return "SPARC";
		case EM_386: return "Intel 80386";
		case EM_68K: return "Motorola 68000";
		case EM_88K: return "Motorola 88000";
		case EM_860: return "Intel 80860";
		case EM_MIPS: return "MIPS I Architecture";
		case EM_S370: return "IBM System/370 Processor";
		case EM_MIPS_RS3_LE: return "MIPS RS3000 Little-endian";
		case EM_PARISC: return "Hewlett-Packard PA-RISC";
		case EM_VPP500: return "Fujitsu VPP500";
		case EM_SPARC32PLUS: return "Enhanced instruction set SPARC";
		case EM_960: return "Intel 80960";
		case EM_PPC: return "PowerPC";
		case EM_PPC64: return "64-bit PowerPC";
		case EM_S390: return "IBM System/390 Processor";
		case EM_V800: return "NEC V800";
		case EM_FR20: return "Fujitsu FR20";
		case EM_RH32: return "TRW RH-32";
		case EM_RCE: return "Motorola RCE";
		case EM_ARM: return "ARM 32-bit architecture (AARCH32)";
		case EM_SH: return "Hitachi SH";
		case EM_SPARCV9: return "SPARC Version 9";
		case EM_TRICORE: return "Siemens TriCore embedded processor";
		case EM_ARC: return "Argonaut RISC Core, Argonaut Technologies Inc.";
		case EM_H8_300: return "Hitachi H8/300";
		case EM_H8_300H: return "Hitachi H8/300H";
		case EM_H8S: return "Hitachi H8S";
		case EM_H8_500: return "Hitachi H8/500";
		case EM_IA_64: return "Intel IA-64 processor architecture";
		default: return "Unknow";
	}
}
/**********************************************************************
* Affichage des informations relative au header sur la sortie standard
* Paramètre : ...
**********************************************************************/

void read_elf_header(Elf32_Ehdr *elfHeader){
  printf("* Plateforme cible :\n");
  printf("* Magique                                            :%x %x %x %x\n", elfHeader->e_ident[EI_MAG0],elfHeader->e_ident[EI_MAG1],elfHeader->e_ident[EI_MAG2],elfHeader->e_ident[EI_MAG3]);
	printf("* Classe du fichier                                  :%s\n", typeClasse(elfHeader->e_ident[EI_CLASS]));
  printf("* Encodage des données                               :%s\n", typeDonnee(elfHeader->e_ident[EI_DATA]));
	printf("* Type                                               :%s\n", typeType(elfHeader->e_type));
  printf("* Machine                                            :%s\n", typeMachine(elfHeader->e_machine));
  printf("* Version                                            :0x%s\n", typeVersion(elfHeader->e_version));
  printf("* Point d'entrée                                     :0x%x\n", elfHeader->e_entry);
  printf("* Adresse de la table des segments                   :%d\n", elfHeader->e_phoff);
  printf("* Adresse de la table de section                     :%d\n", elfHeader->e_shoff);
  printf("* Flags                                              :0x%x\n", elfHeader->e_flags);
  printf("* Taille de l'en-tete                                :%d\n", elfHeader->e_ehsize);
  printf("* Taille de la table du programme                    :%d\n", elfHeader->e_phentsize);
  printf("* Nombre d'element dans la table des segments        :%d\n", elfHeader->e_phnum);
  printf("* Taille de la table des sections                    :%d\n", elfHeader->e_shentsize);
  printf("* Nombre d'elements dans la table des sections       :%d\n", elfHeader->e_shnum);
  printf("* Table d'indexe                                     :%d\n", elfHeader->e_shstrndx);  
}


