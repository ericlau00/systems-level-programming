#include "networking.h"
#include "random.h"

int main(int argc, char **argv) {

    int client_0;
    char buffer[BUFFER_SIZE];

    if (argc == 2) {
        char ** random_characters = malloc(sizeof(char *) * 16);
        get_random(random_characters);

        int i = 0;
        for(; i < 16; i++) {
            printf("%s\n", random_characters[i]);
        }
        int listen_socket;
        listen_socket = client_listen();

        // char message[16][256] =
        while (1) {
            int client_1 = client_accept(listen_socket);
            write(client_1, &random_characters, sizeof(random_characters));
            while (read(client_1, buffer, sizeof(buffer))) {
                printf("[other %d] received: [%s]\n", client_1, buffer);
                write(client_1, buffer, sizeof(buffer));
            }
        }
    }
    else {
        client_0 = client_connect( TEST_IP );

        char message[16][256];
        read(client_0, &message, sizeof(message));

        int i = 0;
        for(; i < 16; i++) {
            printf("%s\n", message[i]);
        }

        while( 1 ) {
            printf("enter data: ");
            fgets(buffer, sizeof(buffer), stdin);
            *strchr(buffer, '\n') = 0;
            write(client_0, buffer, sizeof(buffer));
            read(client_0, buffer, sizeof(buffer));
            printf("received: [%s]\n", buffer);
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
