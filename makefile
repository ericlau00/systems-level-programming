all: server client

server: server.o networking.o random.o
	gcc -o server server.o networking.o random.o

client: client.o networking.o
	gcc -o client client.o networking.o

random.o: random.c random.h
	gcc -c random.c

server.o: server.c networking.h random.h game.h
	gcc -c server.c

client.o: client.c networking.h
	gcc -c client.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm server
	rm client
	rm *.o
	rm *~
