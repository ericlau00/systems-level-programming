all: client

client: client.o networking.o random.o game.o
	gcc -o client client.o networking.o random.o game.o

client.o: client.c game.h
	gcc -c client.c

networking.o: networking.c networking.h
	gcc -c networking.c

random.o: random.c random.h
	gcc -c random.c

game.o: game.c game.h networking.h random.h
	gcc -c game.c

clean:
	rm client
	rm *.o
	rm *~
