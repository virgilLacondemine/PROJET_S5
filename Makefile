main: main.c lecture_header_elf.o 
	gcc -o main main.c lecture_header_elf.o


lecture_header_elf.o: lecture_header_elf.c lecture_header_elf.h
	gcc -c lecture_header_elf.c

clean:
	rm *.o
