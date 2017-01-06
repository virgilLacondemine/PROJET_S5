main: main.c lecture_header_elf.o elf_section_reader.o lecture_section.o
	gcc -o main main.c lecture_header_elf.o elf_section_reader.o lecture_section.o


lecture_header_elf.o: lecture_header_elf.c lecture_header_elf.h
	gcc -c lecture_header_elf.c

elf_section_header.o:  elf_section_header.c  elf_section_header.h
	gcc -c elf_section_header.c

lecture_section.o: lecture_section.c lecture_section.h
	gcc -fstack-protector -c lecture_section.c

clean:
	rm *.o main
