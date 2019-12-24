ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

ifeq ($(ARG), -c)
	ARGUMENT = -c
endif

ifeq ($(ARG), -r)
	ARGUMENT = -r
endif

ifeq ($(ARG), -v)
	ARGUMENT = -v
endif

all: control.o write.o functions.o
	$(CC) -o control control.o functions.o
	$(CC) -o write write.o functions.o

control.o: control.c headers.h functions.o
	$(CC) -c control.c

write.o: write.c headers.h functions.o
	$(CC) -c write.c

functions.o: functions.c headers.h
	$(CC) -c functions.c

valcontrol:
	valgrind --leak-check=yes --track-origins=yes ./control $(ARGUMENT)

valwrite:
	valgrind --leak-check=yes --track-origins=yes ./write

clean:
	rm *.o
	rm control
	rm write
	rm file
