all: main.o methods.o
	gcc -o program main.o methods.o

main.o: main.c headers.h
	gcc -c -g main.c

methods.o: methods.c headers.h
	gcc -c -g methods.c 

run: 
	./program

clean:
	rm *.o
	rm program

val:
	valgrind --leak-check=yes --track-origins=yes ./program