#ifndef __AFFICHAGE__
#define __AFFICHAGE__

// Fonction de renomage des elements de la structure elfheader
char* typeClasse(unsigned char ei_class);
char* typeDonnee(unsigned char ei_data);
char* typeType(unsigned char type);
char* typeVersion(unsigned char version);
char* typeMachine(unsigned char machine);

// Renomage des elements du section header table
char* section_type_name(Elf32_Word  type_number);
char* flags_name(int f);

// Renomage des elements de la table des symboles
char* sym_type_name(Elf32_Word  type_number);
char* sym_bind_name(Elf32_Word  type_number);
char* sym_vis_name(Elf32_Word  type_number);
char* sym_ndx_name(Elf32_Word  type_number);

// Renomage en fonction du type de realocation
char* rel_type_name(Elf32_Word  type_number);

#endif
