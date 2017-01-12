#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "info.h"

// fonctions de renomage des elements de la structure elfheader

char* typeClasse(unsigned char ei_class)
{
	switch(ei_class)
	{
		case ELFCLASSNONE:
			return "Invalid Class";
		case ELFCLASS32:
			return "32-bit objects";
		case ELFCLASS64:
			return "64-bit objects";
		default:
			return "Unknow";
	}
}

char* typeDonnee(unsigned char ei_data)
{
	switch(ei_data)
	{
		case ELFDATANONE:
			return "Invalid data encoding";
		case ELFDATA2LSB:
			return "Little Endian";
		case ELFDATA2MSB:
			return "Big Endian";
		default:
			return "Unknow";
	}
}

char* typeType(unsigned char type)
{
	switch(type)
	{
		case ET_NONE:
			return "No file type";
		case ET_REL:
			return "Relocatable file";
		case ET_EXEC:
			return "Executable file";
		case ET_DYN:
			return "Shared object file";
		case ET_CORE:
			return "Core file";
		default:
			return "Unknow";
	}
}

char* typeVersion(unsigned char version)
{
	switch(version)
	{
		case EV_NONE:
			return "0 (INVALID)";
		case EV_CURRENT:
			return "1 (CURRENT)";
		default:
			return "Unknow";
	}
}

char* typeMachine(unsigned char machine)
{
	switch(machine)
	{
		case EM_NONE:
			return "No machine";
		case EM_M32:
			return "AT&T WE 32100";
		case EM_SPARC:
			return "SPARC";
		case EM_386:
			return "Intel 80386";
		case EM_68K:
			return "Motorola 68000";
		case EM_88K:
			return "Motorola 88000";
		case EM_860:
			return "Intel 80860";
		case EM_MIPS:
			return "MIPS I Architecture";
		case EM_S370:
			return "IBM System/370 Processor";
		case EM_MIPS_RS3_LE:
			return "MIPS RS3000 Little-endian";
		case EM_PARISC:
			return "Hewlett-Packard PA-RISC";
		case EM_VPP500:
			return "Fujitsu VPP500";
		case EM_SPARC32PLUS:
			return "Enhanced instruction set SPARC";
		case EM_960:
			return "Intel 80960";
		case EM_PPC:
			return "PowerPC";
		case EM_PPC64:
			return "64-bit PowerPC";
		case EM_S390:
			return "IBM System/390 Processor";
		case EM_V800:
			return "NEC V800";
		case EM_FR20:
			return "Fujitsu FR20";
		case EM_RH32:
			return "TRW RH-32";
		case EM_RCE:
			return "Motorola RCE";
		case EM_ARM:
			return "ARM 32-bit architecture (AARCH32)";
		case EM_SH:
			return "Hitachi SH";
		case EM_SPARCV9:
			return "SPARC Version 9";
		case EM_TRICORE:
			return "Siemens TriCore embedded processor";
		case EM_ARC:
			return "Argonaut RISC Core, Argonaut Technologies Inc.";
		case EM_H8_300:
			return "Hitachi H8/300";
		case EM_H8_300H:
			return "Hitachi H8/300H";
		case EM_H8S:
			return "Hitachi H8S";
		case EM_H8_500:
			return "Hitachi H8/500";
		case EM_IA_64:
			return "Intel IA-64 processor architecture";
		default:
			return "Unknow";
	}
}

/* Sémantique du nom en fonction de la valeur du type de section */
char* section_type_name(Elf32_Word type_number) {

	switch (type_number)
	{
		case 0:
			return "NULL";
		case 1:
			return "PROGBITS";
		case 2:
			return "SYMTAB";
		case 3:
			return "STRTAB";
		case 4:
			return "RELA";
		case 5:
			return "HASH";
		case 6:
			return "DYNAMIC";
		case 7:
			return "NOTE";
		case 8:
			return "NOBITS";
		case 9:
			return "REL";
		case 10:
			return "SHLIB";
		case 11:
			return "DYNSYM";
		case 0x70000000:
			return "LOPROC";
		case 0x7fffffff:
			return "HIPROC";
		case 0x80000000:
			return "LOUSER";
		case 0xffffffff:
			return "HIUSER";
		default :
			return "???";
	}
}

/* Construction de la sémantique du FLAG en fonction des entier lus bit à bit */
char* flags_name(int f) {

	char* r = malloc(sizeof(char)*4);

		if (f & 0x1)
			r = strcat(r,"W");
		if (f & 0x2)
			r = strcat(r,"A");
		if (f & 0x4)
			r = strcat(r,"X");
		if (f & 0x10)
			r = strcat(r,"M");
		if (f & 0x20)
			r = strcat(r,"S");
		if (f & 0x40)
			r = strcat(r,"I");
		if (f & 0x80)
			r = strcat(r,"O");
		if (f & 0x100)
			r = strcat(r,"N");
		if (f & 0x200)
			r = strcat(r,"G");
		if (f & 0x400)
			r = strcat(r,"T");
		if (f & 0x0ff00000)
			r = strcat(r,"o");
		if (f & 0xf0000000)
			r = strcat(r,"P");

	return r;

}

/* Sémantique du nom en fonction de la valeur du type du symbole */
char* sym_type_name(Elf32_Word  type_number) {

	switch (type_number)
	{
		case 0:
			return "NOTYPE";
		case 1:
			return "OBJECT";
		case 2:
			return "FUNC";
		case 3:
			return "SECTION";
		case 4:
			return "FILE";
		case 13:
			return "LOPROC";
		case 15:
			return "HIPROC";
		default :
			return "NOTYPE";
	}
}

/* Sémantique du nom en fonction de la valeur du type du lien */
char* sym_bind_name(Elf32_Word  type_number) {

	switch (type_number)
	{
		case 0:
			return "LOCAL";
		case 1:
			return "GLOBAL";
		case 2:
			return "WEAK";
		case 13:
			return "LOPROC";
		case 15:
			return "HIPROC";
		default :
			return "LOCAL";
	}
}

/* Sémantique du nom en fonction de la valeur du type de la visibilité */
char* sym_vis_name(Elf32_Word  type_number) {

	switch (type_number)
	{
		case 0:
			return "DEFAULT";
		case 1:
			return "INTERNAL";
		case 2:
			return "HIDDEN";
		case 3:
			return "PROTECTED";
		default :
			return "DEFAULT";
	}
}

/* Sémantique du nom en fonction de la valeur du type du ndx */
char* sym_ndx_name(Elf32_Word  type_number) {

	char* buf = malloc(sizeof(char) * 16);

	switch ((int)type_number)
	{
		case 0:
			return "UND";
		case (65521):
			return "ABS";
		default :

			sprintf(buf,"%d",type_number);
			return buf;
	}
}

/* Sémantique du nom en fonction de la valeur du type de relocation */
char* rel_type_name(Elf32_Word  type_number) {

	switch (type_number)
	{
		 case 0:
			 return "R_ARM_NONE";
		 case 1:
		 	 return "R_ARM_PC24";
		 case 2:
		 	 return "R_ARM_ABS32";
		 case 3:
		 	 return "R_ARM_REL32";
		 case 4:
		 	 return "R_ARM_PC13";
		 case 5:
		 	 return "R_ARM_ABS16";
		 case 6:
		 	 return "R_ARM_ABS12";
		 case 7:
		 	 return "R_ARM_THM_ABS5";
		 case 8:
		 	 return "R_ARM_ABS8";
		 case 9:
		 	 return "R_ARM_SBREL32";
		 case 10:
		 	 return "R_ARM_THM_PC22";
		 case 11:
		 	 return "R_ARM_THM_PC8";
		 case 12:
		 	 return "R_ARM_AMP_VCALL9";
		 case 13:
		 	 return "R_ARM_TLS_DESC";
		 case 14:
		 	 return "R_ARM_THM_SWI8";
		 case 15:
		 	 return "R_ARM_XPC25";
		 case 16:
		 	 return "R_ARM_THM_XPC22";
		 case 17:
		 	 return "R_ARM_TLS_DTPMOD32";
		 case 18:
		 	 return "R_ARM_TLS_DTPOFF32";
		 case 19:
		 	 return "R_ARM_TLS_TPOFF32";
		 case 20:
		 	 return "R_ARM_COPY";
		 case 21:
		 	 return "R_ARM_GLOB_DAT";
		 case 22:
		 	 return "R_ARM_JUMP_SLOT";
		 case 23:
		 	 return "R_ARM_RELATIVE";
		 case 24:
		 	 return "R_ARM_GOTOFF";
		 case 25:
		 	 return "R_ARM_GOTPC";
		 case 26:
		 	 return "R_ARM_GOT32";
		 case 27:
		 	 return "R_ARM_PLT32";
		 case 28:
		 	 return "R_ARM_CALL";
		 case 29:
		 	 return "R_ARM_JUMP24";
		 case 30:
		 	 return "R_ARM_THM_JUMP24";
		 case 31:
		 	 return "R_ARM_BASE_ABS";
		 case 32:
		 	 return "R_ARM_ALU_PCREL_7_0";
		 case 33:
		 	 return "R_ARM_ALU_PCREL_15_8";
		 case 34:
		 	 return "R_ARM_ALU_PCREL_23_15";
		 case 35:
		 	 return "R_SBREL_11_0";
		 case 36:
		 	 return "R_ARM_ALU_SBREL_19_12";
		 case 37:
		 	 return "R_ARM_ALU_SBREL_27_20";
		 case 38:
		 	 return "R_ARM_TARGET1";
		 case 39:
		 	 return "R_ARM_SBREL31";
		 case 40:
		 	 return "R_ARM_V4BX";
		 case 41:
		 	 return "R_ARM_TARGET2";
		 case 42:
		 	 return "R_ARM_PREL31";
		 case 43:
		 	 return "R_ARM_MOVW_ABS_NC";
		 case 44:
		 	 return "R_ARM_MOVT_ABS";
		 case 45:
		 	 return "R_ARM_MOVW_PREL_NC";
		 case 46:
		 	 return "R_ARM_MOVT_PREL";
		 case 47:
		 	 return "R_ARM_THM_MOVW_ABS_NC";
		 case 48:
		 	 return "R_ARM_THM_MOVT_ABS";
		 case 49:
		 	 return "R_ARM_THM_MOVW_PREL_NC";
		 case 50:
		 	 return "R_ARM_THM_MOVT_PREL";
		 case 51:
		 	 return "R_ARM_THM_JUMP19";
		 case 52:
		 	 return "R_ARM_THM_JUMP6";
		 case 53:
		 	 return "R_ARM_THM_ALU_PREL_11_0";
		 case 54:
		 	 return "R_ARM_THM_PC12";
		 case 55:
		 	 return "R_ARM_ABS32_NOI";
		 case 56:
		 	 return "R_ARM_REL32_NOI";
		 case 57:
		 	 return "R_ARM_ALU_PC_G0_NC";
		 case 58:
		 	 return "R_ARM_ALU_PC_G0";
		 case 59:
		 	 return "R_ARM_ALU_PC_G1_NC";
		 case 60:
		 	 return "R_ARM_ALU_PC_G1";
		 case 61:
		 	 return "R_ARM_ALU_PC_G2";
		 case 62:
		 	 return "R_PC_G1";
		 case 63:
		 	 return "R_PC_G2";
		 case 64:
		 	 return "R_ARM_LDRS_PC_G0";
		 case 65:
		 	 return "R_ARM_LDRS_PC_G1";
		 case 66:
		 	 return "R_ARM_LDRS_PC_G2";
		 case 67:
		 	 return "R_ARM_LDC_PC_G0";
		 case 68:
		 	 return "R_ARM_LDC_PC_G1";
		 case 69:
		 	 return "R_ARM_LDC_PC_G2";
		 case 70:
		 	 return "R_ARM_ALU_SB_G0_NC";
		 case 71:
		 	 return "R_ARM_ALU_SB_G0";
		 case 72:
		 	 return "R_ARM_ALU_SB_G1_NC";
		 case 73:
		 	 return "R_ARM_ALU_SB_G1";
		 case 74:
		 	 return "R_ARM_ALU_SB_G2";
		 case 75:
		 	 return "R_SB_G0";
		 case 76:
		 	 return "R_SB_G1";
		 case 77:
		 	 return "R_SB_G2";
		 case 78:
		 	 return "R_ARM_LDRS_SB_G0";
		 case 79:
		 	 return "R_ARM_LDRS_SB_G1";
		 case 80:
		 	 return "R_ARM_LDRS_SB_G2";
		 case 81:
		 	 return "R_ARM_LDC_SB_G0";
		 case 82:
		 	 return "R_ARM_LDC_SB_G1";
		 case 83:
		 	 return "R_ARM_LDC_SB_G2";
		 case 84:
		 	 return "R_ARM_MOVW_BREL_NC";
		 case 85:
		 	 return "R_ARM_MOVT_BREL";
		 case 86:
		 	 return "R_ARM_MOVW_BREL";
		 case 104:
		 	 return "R_ARM_TLS_GD32";
		 case 105:
		 	 return "R_ARM_TLS_LDM32";
		 case 106:
		 	 return "R_ARM_TLS_LDO32";
		 case 107:
		 	 return "R_ARM_TLS_IE32";
		 case 108:
		 	 return "R_ARM_TLS_LE32";
		 case 109:
		 	 return "R_ARM_TLS_LDO12";
		 case 110:
		 	 return "R_ARM_TLS_LE12";
		 case 111:
		 	 return "R_ARM_TLS_IE12GP";
		 case 128:
		 	 return "R_ARM_ME_TOO";
		 case 129:
		 	 return "R_ARM_THM_TLS_DESCSEQ";
		 case 130:
		 	 return "R_ARM_THM_TLS_DESCSEQ32";
		 case 131:
		 	 return "R_ARM_THM_GOT_BREL12";
		 case 160:
		 	 return "R_ARM_IRELATIVE";
		 case 249:
		 	 return "R_ARM_RXPC25";
		 case 250:
		 	 return "R_ARM_RSBREL32";
		 case 251:
		 	 return "R_ARM_THM_RPC22";
		 case 252:
		 	 return "R_ARM_RREL32";
		 case 253:
		 	 return "R_ARM_RABS22";
		 case 254:
		 	 return "R_ARM_RPC24";
		 case 255:
		 	 return "R_ARM_RBASE";
		 case 256:
		 	 return "R_ARM_NUM";
		 default :
			 return "???";
	}
}
