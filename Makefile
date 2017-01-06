main: main.c lecture_header_elf.o elf_section_reader.o lecture_section.o elf_relocation_reader.o elf_sym_reader.o
	gcc -o main main.c lecture_header_elf.o elf_section_reader.o lecture_section.o elf_relocation_reader.o elf_sym_reader.o

lecture_header_elf.o: lecture_header_elf.c lecture_header_elf.h
	gcc -c lecture_header_elf.c

elf_section_header.o:  elf_section_header.c  elf_section_header.h
	gcc -c elf_section_header.c

lecture_section.o: lecture_section.c lecture_section.h
	gcc -fstack-protector -c lecture_section.c
	
elf_sym_reader.o:  elf_sym_reader.c  elf_sym_reader.h
	gcc -c elf_sym_reader.c
	
elf_relocation_reader.o:  elf_relocation_reader.c  elf_relocation_reader.h
	gcc -c elf_relocation_reader.c

clean:
	rm *.o main
