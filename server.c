#include "networking.h"

void process(char *s);
void subserver(int from_client);
int numplayers;

int main() {

  int listen_socket;
  int f;
  listen_socket = server_setup();
  char ** randomcharacters = get_random();

  while (1) {
    if (numplayers == 0) {
        printf("0 players connected. 2 players must connect to play.\n");
    }
    else if (numplayers == 1) {
        printf("1 player connected. 1 more player must connect to play.\n");
    }
    else if (numplayers == 2) {
        printf("Playing.\n");
        // setup game
        // get array of 16 characters
    }
    int client_socket = server_connect(listen_socket);
    f = fork();
    numplayers++;
    if (f == 0) {
      subserver(client_socket);
    }
    else
      close(client_socket);
    }
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];
  // create board for user
  // setup struct with previous variable for array of 16 characters
  while (read(client_socket, buffer, sizeof(buffer))) {
    int pid = getpid();
    printf("[subserver %d] received: [%s]\n", pid, buffer);
    process(buffer);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
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
