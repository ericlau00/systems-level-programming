all: client

client: client.o game.o networking.o random.o
	gcc -o client client.o game.o networking.o random.o

game.o: game.c game.h networking.h random.h
	gcc -c game.c

client.o: client.c game.h networking.h random.h
	gcc -c client.c

networking.o: networking.c networking.h
	gcc -c networking.c

random.o: random.c random.h
	gcc -c random.c

clean:
	rm client
	rm *.o
	rm *~
