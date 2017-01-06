#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <elf.h>
#include <string.h>
#include "elf_relocation_reader.h"

/* 32-bit ELF Types de base */
typedef unsigned int Elf32_Addr;
typedef unsigned short Elf32_Half;
typedef unsigned int Elf32_Off;
typedef signed int Elf32_Sword;
typedef unsigned int Elf32_Word;

/* Sémantique du nom en fonction de la valeur du type de relocation */
char* rel_type_name(Elf32_Word  type_number) {

	switch (type_number)
	{
		 case 0:
			 return "R_ARM_NONE";
		 case 1:		 	 return "R_ARM_PC24";
		 case 2:		 	 return "R_ARM_ABS32";
		 case 3:		 	 return "R_ARM_REL32";
		 case 4:		 	 return "R_ARM_PC13";
		 case 5:		 	 return "R_ARM_ABS16";
		 case 6:		 	 return "R_ARM_ABS12";
		 case 7:		 	 return "R_ARM_THM_ABS5";
		 case 8:		 	 return "R_ARM_ABS8";
		 case 9:		 	 return "R_ARM_SBREL32";
		 case 10:		 	 return "R_ARM_THM_PC22";
		 case 11:		 	 return "R_ARM_THM_PC8";
		 case 12:		 	 return "R_ARM_AMP_VCALL9";
		 case 13:		 	 return "R_ARM_TLS_DESC";
		 case 14:		 	 return "R_ARM_THM_SWI8";
		 case 15:		 	 return "R_ARM_XPC25";
		 case 16:		 	 return "R_ARM_THM_XPC22";
		 case 17:		 	 return "R_ARM_TLS_DTPMOD32";
		 case 18:		 	 return "R_ARM_TLS_DTPOFF32";
		 case 19:		 	 return "R_ARM_TLS_TPOFF32";
		 case 20:		 	 return "R_ARM_COPY";
		 case 21:		 	 return "R_ARM_GLOB_DAT";
		 case 22:		 	 return "R_ARM_JUMP_SLOT";
		 case 23:		 	 return "R_ARM_RELATIVE";
		 case 24:		 	 return "R_ARM_GOTOFF";
		 case 25:		 	 return "R_ARM_GOTPC";
		 case 26:		 	 return "R_ARM_GOT32";
		 case 27:		 	 return "R_ARM_PLT32";
		 case 28:		 	 return "R_ARM_CALL";
		 case 29:		 	 return "R_ARM_JUMP24";
		 case 30:		 	 return "R_ARM_THM_JUMP24";
		 case 31:		 	 return "R_ARM_BASE_ABS";
		 case 32:		 	 return "R_ARM_ALU_PCREL_7_0";
		 case 33:		 	 return "R_ARM_ALU_PCREL_15_8";
		 case 34:		 	 return "R_ARM_ALU_PCREL_23_15";
		 case 35:		 	 return "R_SBREL_11_0";	
		 case 36:		 	 return "R_ARM_ALU_SBREL_19_12";	
		 case 37:		 	 return "R_ARM_ALU_SBREL_27_20";	
		 case 38:		 	 return "R_ARM_TARGET1";
		 case 39:		 	 return "R_ARM_SBREL31";
		 case 40:		 	 return "R_ARM_V4BX";
		 case 41:		 	 return "R_ARM_TARGET2";
		 case 42:		 	 return "R_ARM_PREL31";
		 case 43:		 	 return "R_ARM_MOVW_ABS_NC";	
		 case 44:		 	 return "R_ARM_MOVT_ABS";	
		 case 45:		 	 return "R_ARM_MOVW_PREL_NC";
		 case 46:		 	 return "R_ARM_MOVT_PREL";
		 case 47:		 	 return "R_ARM_THM_MOVW_ABS_NC";	
		 case 48:		 	 return "R_ARM_THM_MOVT_ABS";					
		 case 49:		 	 return "R_ARM_THM_MOVW_PREL_NC";
		 case 50:		 	 return "R_ARM_THM_MOVT_PREL";
		 case 51:		 	 return "R_ARM_THM_JUMP19";
		 case 52:		 	 return "R_ARM_THM_JUMP6";
		 case 53:		 	 return "R_ARM_THM_ALU_PREL_11_0";
		 case 54:		 	 return "R_ARM_THM_PC12";
		 case 55:		 	 return "R_ARM_ABS32_NOI";
		 case 56:		 	 return "R_ARM_REL32_NOI";
		 case 57:		 	 return "R_ARM_ALU_PC_G0_NC";
		 case 58:		 	 return "R_ARM_ALU_PC_G0";
		 case 59:		 	 return "R_ARM_ALU_PC_G1_NC";
		 case 60:		 	 return "R_ARM_ALU_PC_G1";
		 case 61:		 	 return "R_ARM_ALU_PC_G2";
		 case 62:		 	 return "R_PC_G1";
		 case 63:		 	 return "R_PC_G2";
		 case 64:		 	 return "R_ARM_LDRS_PC_G0";
		 case 65:		 	 return "R_ARM_LDRS_PC_G1";
		 case 66:		 	 return "R_ARM_LDRS_PC_G2";
		 case 67:		 	 return "R_ARM_LDC_PC_G0";
		 case 68:		 	 return "R_ARM_LDC_PC_G1";
		 case 69:		 	 return "R_ARM_LDC_PC_G2";
		 case 70:		 	 return "R_ARM_ALU_SB_G0_NC";
		 case 71:		 	 return "R_ARM_ALU_SB_G0";
		 case 72:		 	 return "R_ARM_ALU_SB_G1_NC";	
		 case 73:		 	 return "R_ARM_ALU_SB_G1";
		 case 74:		 	 return "R_ARM_ALU_SB_G2";
		 case 75:		 	 return "R_SB_G0";
		 case 76:		 	 return "R_SB_G1";
		 case 77:		 	 return "R_SB_G2";
		 case 78:		 	 return "R_ARM_LDRS_SB_G0";
		 case 79:		 	 return "R_ARM_LDRS_SB_G1";
		 case 80:		 	 return "R_ARM_LDRS_SB_G2";
		 case 81:		 	 return "R_ARM_LDC_SB_G0";
		 case 82:		 	 return "R_ARM_LDC_SB_G1";
		 case 83:		 	 return "R_ARM_LDC_SB_G2";
		 case 84:		 	 return "R_ARM_MOVW_BREL_NC";
		 case 85:		 	 return "R_ARM_MOVT_BREL";
		 case 86:		 	 return "R_ARM_MOVW_BREL";
		 case 104:		 	 return "R_ARM_TLS_GD32";
		 case 105:		 	 return "R_ARM_TLS_LDM32";
		 case 106:		 	 return "R_ARM_TLS_LDO32";
		 case 107:		 	 return "R_ARM_TLS_IE32";
		 case 108:		 	 return "R_ARM_TLS_LE32";
		 case 109:		 	 return "R_ARM_TLS_LDO12";
		 case 110:		 	 return "R_ARM_TLS_LE12";
		 case 111:		 	 return "R_ARM_TLS_IE12GP";
		 case 128:		 	 return "R_ARM_ME_TOO";
		 case 129:		 	 return "R_ARM_THM_TLS_DESCSEQ";
		 case 130:		 	 return "R_ARM_THM_TLS_DESCSEQ32";
		 case 131:		 	 return "R_ARM_THM_GOT_BREL12";
		 case 160:		 	 return "R_ARM_IRELATIVE";
		 case 249:		 	 return "R_ARM_RXPC25";
		 case 250:		 	 return "R_ARM_RSBREL32";
		 case 251:		 	 return "R_ARM_THM_RPC22";
		 case 252:		 	 return "R_ARM_RREL32";
		 case 253:		 	 return "R_ARM_RABS22";
		 case 254:		 	 return "R_ARM_RPC24";
		 case 255:		 	 return "R_ARM_RBASE";
		 case 256:		 	 return "R_ARM_NUM";	 	 		 	 			
		 default :
			 return "???";			
	}
}

/* Lecture et affichage de la table de relocation */
void read_rel_table(const char* file) {
	
	/* Déclaration de variables */
	int idx;
	Elf32_Shdr data;
	Elf32_Shdr data2;
	Elf32_Ehdr hdr;
	Elf32_Rel rel_tab;	
	char* name;
	char* name2;
	char* SectNames = "";
	
	
	FILE* fd = fopen(file, "r");
	
	/* Chargement de l'adresse du ELF header dans hdr */
  	fread(&hdr, 1, sizeof(Elf32_Ehdr), fd);

	/* Chargement de l'adresse de la Section header dans data */
	fseek(fd, hdr.e_shoff + hdr.e_shstrndx * sizeof(Elf32_Shdr), SEEK_SET);
  	fread(&data, 1, sizeof(data), fd);

	SectNames = malloc(data.sh_size);

	/* Chargement de l'adresse de la String table dans SectNames */
	fseek(fd, data.sh_offset, SEEK_SET);
  	fread(SectNames, 1, data.sh_size, fd);


	/* Parcours des sections jusqu'à '.rel.text' */
	for (idx = 0; idx < hdr.e_shnum; idx++)
	{
		/* Chargement de l'adresse de la prochaine section (En commençant par la première) */
		fseek(fd, hdr.e_shoff + idx * sizeof(data), SEEK_SET);
		fread(&data, 1, sizeof(data), fd);

		/* L'adresse contenu dans name devient celle du début de la String Table auquel on rajoute l'offset correspondant au nom section */
		name = SectNames + data.sh_name;

		if (strcmp(name,".rel.text")==0) {
			name2 = name;
			data2 = data;
		}		
	}

	free(SectNames);

	/* Chargement de l'adresse de la Relocation Table dans rel_tab */
	fseek(fd, hdr.e_shoff + hdr.e_shstrndx * sizeof(Elf32_Shdr) + data2.sh_offset * sizeof(Elf32_Shdr), SEEK_SET);
  	fread(&rel_tab, 1, sizeof(Elf32_Rel), fd);


	printf("\nSection de relocalisation '%s' à l'adresse de décalage 0x%x contient %i entrées:\n",name2, data2.sh_offset,data2.sh_size / data2.sh_entsize);
	printf("%8s ", " Décalage");
	printf("%6s ", "Info");
	printf("%8s\n", "Type");
	
	for (idx = 0; idx < data2.sh_size / data2.sh_entsize; idx++)
	{
		/* Chargement de l'adresse de la prochaine relocation */
		fseek(fd, data2.sh_addr + data2.sh_offset + idx * sizeof(Elf32_Rel), SEEK_SET);
		fread(&rel_tab, 1, sizeof(Elf32_Rel), fd);

		printf("%-.8x ",rel_tab.r_offset);
		printf("%-.8x ",rel_tab.r_info);
		printf("%-8s",rel_type_name(ELF32_R_TYPE(rel_tab.r_info)));
		printf("\n");
	}

}
