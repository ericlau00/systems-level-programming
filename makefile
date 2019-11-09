ifeq ($(DEBUG), true)
	CC = gcc -g
else 
	CC = gcc
endif 

all: main.c
	$(CC) -o program main.c

val:
	valgrind --leak-check=yes --track-origins=yes ./program

run: 
	./program

clean:
	rm program