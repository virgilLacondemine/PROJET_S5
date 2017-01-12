main: main.c display.o info.o reader.o fusion.o
	gcc -o main main.c display.o info.o reader.o fusion.o

display.o: display.c display.h
	gcc -c display.c

reader.o: reader.c reader.h
	gcc -c reader.c

info.o: info.c info.h
	gcc -c info.c

fusion.o: fusion.c fusion.h
	gcc -c fusion.c

clean:
	rm *.o main
