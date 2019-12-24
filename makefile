ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

control: control.c
	$(CC) -o control control.c

write: write.c
	$(CC) -o write write.c

valcontrol:
	valgrind --leak-check=yes --track-origins=yes ./control

valwrite:
	valgrind --leak-check=yes --track-origins=yes ./write

clean:
	rm program