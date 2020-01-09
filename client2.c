#include "networking.h"

void process(char *s);
void subserver(int from_client);

int main(int argc, char **argv) {

  
  int server_socket;
  char buffer[BUFFER_SIZE];
  server_socket = client_setup(argv[1]);
  printf("enter data: ");
  fgets(buffer, sizeof(buffer), stdin);
  *strchr(buffer, '\n') = 0;
  write(server_socket, buffer, sizeof(buffer));
  read(server_socket, buffer, sizeof(buffer));
  printf("received: [%s]\n", buffer);
    
  int listen_socket;
  int f;
  listen_socket = server_setup();
    
  while (1) {
      
    int state_iteration = 0;

    if (state_iteration == 1) {
      printf("enter data: ");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(server_socket, buffer, sizeof(buffer));
      read(server_socket, buffer, sizeof(buffer));
      printf("received: [%s]\n", buffer);
      state_iteration = 0;
    }

    if (state_iteration == 0) {
      int client_socket = server_connect(listen_socket);
      char buffer[BUFFER_SIZE];
      read(client_socket, buffer, sizeof(buffer));
      process(buffer);
      write(client_socket, buffer, sizeof(buffer));
      close(client_socket);
      state_iteration = 1;
    }

  }

}

void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
