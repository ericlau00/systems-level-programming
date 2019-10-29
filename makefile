all: main.o methods.o
	gcc -g -o program main.o methods.o

main.o: main.c headers.h
	gcc -g -c main.c

methods.o: methods.c headers.h
	gcc -g -c methods.c 

run: 
	./program

clean:
	rm *.o
	rm program

val:
	valgrind --leak-check=yes --track-origins=yes ./program