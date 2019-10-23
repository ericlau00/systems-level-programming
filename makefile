all: main.o methods.o
	gcc -o program main.o methods.o

main.o: main.c headers.h
	gcc -c main.c

methods.o: methods.c headers.h
	gcc -c methods.c 

run: 
	./program

clean:
	rm *.o
	rm program