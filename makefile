all: client1 client2

client2: client2.o networking.o
	gcc -o client2 client2.o networking.o

client1: client1.o networking.o
	gcc -o client1 client1.o networking.o

client2.o: client2.c networking.h
	gcc -c client2.c

client1.o: client1.c networking.h
	gcc -c client1.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm client1
	rm client2
	rm *.o
	rm *~
