ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

DEPENDENCIES = execution.o parse.o

all: main.o $(DEPENDENCIES)
	$(CC) -o program main.o $(DEPENDENCIES)

main.o: main.c execution.h parse.o
	$(CC) -c main.c

execution.o: execution.c execution.h
	$(CC) -c execution.c

parse.o: parse.c parse.h
	$(CC) -c parse.c

val:
	valgrind --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./program

run:
	./program

clean:
	rm *.o
	rm program