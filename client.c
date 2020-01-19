#include "game.h"

int main(int argc, char **argv) {

    if (argc == 2) {

        int listen_socket;
        listen_socket = client_listen();

        printf("Waiting for player...\n");

        int client_1 = client_accept(listen_socket);

        printf("Player connected!\n");

        char characters[6][20] = {"x","y","z","a","b","c"};
        char chosen[20];
        strcpy(chosen, characters[2]);
        write(client_1, &characters, sizeof(characters));
        printf("Your character is: %s\n", chosen);

        printf("Ask a question: ");
        struct response res;
        res.type = 0;
        fgets(res.content, sizeof(res.content), stdin);
        *strchr(res.content, '\n') = 0;
        write(client_1, &res, sizeof(res));

        while(1) {
            logic(client_1, res, chosen);
        }
    }
    else {
        int client_0 = client_connect( TEST_IP );

        printf("You have successfuly connected!\n");

        char characters[6][20];
        read(client_0, &characters, sizeof(characters));
        char chosen[20];
        strcpy(chosen, characters[3]);
        printf("Your character is: %s\n", chosen);

        struct response res;

        while(1) {
            logic(client_0, res, chosen);
        }
    }
}
