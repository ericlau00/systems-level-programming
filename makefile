ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o methods.o

all: main.o methods.o
	$(CC) -o program main.o methods.o

main.o: main.c headers.h
	$(CC) -c main.c

methods.o: methods.c headers.h
	$(CC) -c methods.c

val:
	valgrind --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./program

run:
	./program

clean:
	rm *.o
	rm program