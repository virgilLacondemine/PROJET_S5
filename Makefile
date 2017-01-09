my_readelf: my_readelf.c elf_header.o elf_section_header_table.o elf_section.o elf_symbol_table.o elf_relocation_table.o
	gcc -o my_readelf my_readelf.c elf_header.o elf_section_header_table.o elf_section.o elf_symbol_table.o elf_relocation_table.o

fusion_elf: main_fus.c Fus_renumsec.o
	gcc -o fusion_elf main_fus.c Fus_renumsec.o

Fus_renumsec.o: Fus_renumsec.c Fus_renumsec.h
	gcc -c Fus_renumsec.c
	
elf_header.o: elf_header.c elf_header.h
	gcc -c elf_header.c

elf_section_header_table.o: elf_section_header_table.c elf_section_header_table.h
	gcc -c elf_section_header_table.c

elf_section.o: elf_section.c elf_section.h
	gcc -fstack-protector -c elf_section.c

elf_symbol_table.o: elf_symbol_table.c elf_symbol_table.h
	gcc -c elf_symbol_table.c

elf_relocation_table.o: elf_relocation_table.c elf_relocation_table.h
	gcc -c elf_relocation_table.c

clean:
	rm *.o my_readelf
	rm *.o fusion_elf
