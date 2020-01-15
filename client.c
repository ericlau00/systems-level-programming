#include "networking.h"
#include "game.h"

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  char message[16][256];
  write(server_socket, buffer, sizeof(buffer));
  read(server_socket, &message, sizeof(message));
  int i = 0;
    for(; i < 16; i++) {
      printf("%s\n", message[i]);
  }

  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    // int i;
    // struct response * s;

    read(server_socket, &message, sizeof(message));
    // read(server_socket, &i, sizeof(i));
    // printf("received: [%d]\n", i);
    // read(server_socket, &s, sizeof(s));
    // read(server_socket, buffer, sizeof(buffer));
    // read(server_socket, &s, sizeof(s));
    // printf("received: [%d]\n", s->user);
    // printf("received: [%d]\n", s->type);
    // printf("received: [%s]\n", s->content);
    // printf("received: [%d]\n", i);
    // printf("receive %s\n", message);

    // printf("received: [%s]\n", buffer);
  }
}
