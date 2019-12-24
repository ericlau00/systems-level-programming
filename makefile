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

control: control.c
	$(CC) -o control control.c

write: write.c
	$(CC) -o write write.c

valcontrol:
	valgrind --leak-check=yes --track-origins=yes ./control $(ARGUMENT)

valwrite:
	valgrind --leak-check=yes --track-origins=yes ./write

clean:
	rm control
	rm file
	rm write
