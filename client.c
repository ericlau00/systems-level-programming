#include "networking.h"
#include "random.h"

int main(int argc, char **argv) {

    int client_0;
    char buffer[BUFFER_SIZE];

    struct response {
        int client_turn;
        int prev_turn;
        char content[256];
    };

    int prev_turn = 0;
    int client_turn = 0;

    if (argc == 2) {
        // char ** random_characters = malloc(sizeof(char *) * 16);
        // get_random(random_characters);

        char random_characters[16][256] = {"hh", "hh", "hh", "hh", "hh", "hh", "hh", "hh", "hh", "hh", "hh", "hh", "hh", "hh", "hh", "hh" };
        char buffer[BUFFER_SIZE];
        int i = 0;
        for(; i < 16; i++) {
            printf("%s\n", random_characters[i]);
        }
        int listen_socket;
        listen_socket = client_listen();

        while (1) {
            //write all the characters
            int client_1 = client_accept(listen_socket);
            write(client_1, &random_characters, sizeof(random_characters));

            if (client_turn == 0 && prev_turn == 0) {
                struct response res;
                printf("ask a question, or guess: ");
                fgets(res.content, sizeof(res.content), stdin);
                *strchr(res.content, '\n') = 0;

                res.client_turn = 0;
                res.prev_turn= 0;
                write(client_1, &res, sizeof(res));
            }

            while (read(client_1, buffer, sizeof(buffer))) {
                printf("[other %d] received: [%s]\n", client_1, buffer);
                write(client_1, buffer, sizeof(buffer));
            }
        }
    }
    else {
        client_0 = client_connect( TEST_IP );

        // read all the characters
        char random_characters[16][256];
        read(client_0, &random_characters, sizeof(random_characters));

        int i = 0;
        for(; i < 16; i++) {
            printf("%s\n", random_characters[i]);
        }

        struct response res;
        read(client_0, &res, sizeof(res));
        // printf("%d\n", res.client_turn);
        // printf("%d\n", res.prev_turn);
        printf("%s\n", res.content);


        while( 1 ) {
            printf("enter data: ");
            fgets(buffer, sizeof(buffer), stdin);
            *strchr(buffer, '\n') = 0;
            write(client_0, buffer, sizeof(buffer));
            // printf("received: [%s]\n", message);
        }
    }


    // int other_client_socket;
    // char buffer[BUFFER_SIZE];

    // if (argc == 2)
    //     other_client_socket = client_connect( argv[1]);
    // else
    //     other_client_socket = client_connect( TEST_IP );

    // while (1) {
    //     printf("enter data: ");
    //     fgets(buffer, sizeof(buffer), stdin);
    //     *strchr(buffer, '\n') = 0;
    //     write(other_client_socket, buffer, sizeof(buffer));
    //     read(other_client_socket, buffer, sizeof(buffer));
    //     printf("received: [%s]\n", buffer);
    // }
}
