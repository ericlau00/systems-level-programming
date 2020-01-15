#include "networking.h"
#include "game.h"

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    // int i;
    struct response * s;
    char message[10];
    read(server_socket, &message, 10 * sizeof(char));
    // read(server_socket, &i, sizeof(i));
    // printf("received: [%d]\n", i);
    // read(server_socket, &s, sizeof(s));
    // read(server_socket, buffer, sizeof(buffer));
    // read(server_socket, &s, sizeof(s));
    // printf("received: [%d]\n", s->user);
    // printf("received: [%d]\n", s->type);
    // printf("received: [%s]\n", s->content);
    // printf("received: [%d]\n", i);
    printf("receive %d\n", s->type);

    // printf("received: [%s]\n", buffer);
  }
}
