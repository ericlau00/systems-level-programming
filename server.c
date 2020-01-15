#include "networking.h"
#include "random.h"
#include "game.h"

void process(char *s);
void subserver(int from_client);
int numplayers;
char ** random_characters;

// struct board {
//   int type;

// };

int main() {
  random_characters = malloc(sizeof(char *) * 16);
  get_random(random_characters);

  int listen_socket;
  int f;
  listen_socket = server_setup();

  while (1) {
    if (numplayers == 0) {
        printf("0 players connected. 2 players must connect to play.\n");
    }
    else if (numplayers == 1) {
        printf("1 player connected. 1 more player must connect to play.\n");
    }
    else if (numplayers == 2) {
        printf("2 players connected. Playing.\n");
        // setup game
        // get array of 16 characters
    }
    printf("numplayers %d\n", numplayers);
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
    // int i = 5;

    // char * tell = "h";

    // struct response * s;
    // s->user = 0;
    // s->type = 1;
    // s->content = tell;

    // write(client_socket, &i, sizeof(i));
    // char * test = "test";
    // int h = 1;

    // struct response * s;
    // s->user = 0;
    // s->type = 1;
    // s->content = "hello";

    char message[10]= "hello";

    write(client_socket, &message, 10 * sizeof(char));
    // write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

// void process(char * s) {
//   while (*s) {
//     if (*s >= 'a' && *s <= 'z')
//       *s = ((*s - 'a') + 13) % 26 + 'a';
//     else  if (*s >= 'A' && *s <= 'Z')
//       *s = ((*s - 'a') + 13) % 26 + 'a';
//     s++;
//   }
// }
