#include "game.h"

int main(int argc, char **argv) {

    int OTHER_CLIENT;
    struct response res;

    if (argc == 2) {

        int listen_socket = client_listen();

        printf("Waiting for player...\n");

        OTHER_CLIENT = client_accept(listen_socket);

        printf("Player connected!\n");

        char characters[6][20] = {"x","y","z","a","b","c"};
        write(OTHER_CLIENT, &characters, sizeof(characters));

        char chosen[20];
        strcpy(chosen, characters[2]);
        printf("Your character is: %s\n", chosen);

        printf("Ask a question: ");
        ask_initial_question(OTHER_CLIENT, res);

        while(1) {
            game_logic(OTHER_CLIENT, res, chosen);
        }
    }
    else {
        OTHER_CLIENT = client_connect( TEST_IP );

        printf("You have successfuly connected!\n");

        char characters[6][20];
        read(OTHER_CLIENT, &characters, sizeof(characters));

        char chosen[20];
        strcpy(chosen, characters[3]);
        printf("Your character is: %s\n", chosen);

        while(1) {
            game_logic(OTHER_CLIENT, res, chosen);
        }
    }
}
