#include "networking.h"
#include "random.h"

int main(int argc, char **argv) {

    int client_0;
    char buffer[BUFFER_SIZE];

    struct response {
        int from_client;
        int type; // 0 is question, 1 is guess, 2 is answer, 3 is done,
        int client_turn;
        int prev_turn;
        char content[256];
    };

    int prev_turn = 0;
    int client_turn = 0;

    if (argc == 2) {

        char buffer[BUFFER_SIZE];

        int listen_socket;
        listen_socket = client_listen();

        while (1) {
            //write all the characters
            int client_1 = client_accept(listen_socket);
            // write(client_1, &random_characters, sizeof(random_characters));

            // if (client_turn == 0 && prev_turn == 0) {
                struct response res;

                char temp[3];
                printf("[Q to ask question // G to guess]: ");

                fgets(temp, sizeof(temp), stdin);
                *strchr(temp, '\n') = 0;

                if(strcmp(temp, "Q") == 0) {
                    res.type = 0;
                    printf("[Ask your question]: ");
                }

                else if(strcmp(temp, "G") == 0) {
                    res.type = 1;
                    printf("[Guess]: ");
                }

                fgets(res.content, sizeof(res.content), stdin);
                *strchr(res.content, '\n') = '\0';
                write(client_1, &res, sizeof(res));

                if(strcmp(temp, "Q") == 0) {
                    read(client_1, &res, sizeof(res));
                    printf("Client 1 answered: %s\n", res.content);
                    printf("Eliminate a name // G to guess // D to finish: ");
                    fgets(temp, sizeof(temp), stdin);
                    *strchr(temp, '\n') = 0;
                    if(strcmp(temp, "G") == 0) {
                        res.type = 1;
                        printf("[Guess]: ");
                        fgets(res.content, sizeof(res.content), stdin);
                        *strchr(res.content, '\n') = '\0';
                        write(client_1, &res, sizeof(res));
                    }
                    if(strcmp(temp, "D") == 0) {
                        res.type = 3;
                        write(client_1, &res, sizeof(res));
                    }
                }
        }
    }
    else {
        client_0 = client_connect( TEST_IP );

        while( 1 ) {
            struct response res;
            read(client_0, &res, sizeof(res));
            if(res.type == 0) {
                printf("Client 0 asked: %s\n[Answer]: ", res.content);
                fgets(res.content, sizeof(res.content), stdin);
                *strchr(res.content, '\n') = '\0';
                res.type = 2;
                res.from_client = 1;
                res.client_turn = 1;
                res.prev_turn= 0;
                write(client_0, &res, sizeof(res));
            }

            if(res.type == 1) {
                // handles guesses
            }

            if(res.type == 3) {
                char temp[3];
                printf("[Q to ask question // G to guess]: ");

                fgets(temp, sizeof(temp), stdin);
                *strchr(temp, '\n') = 0;

                if(strcmp(temp, "Q") == 0) {
                    res.type = 0;
                    printf("[Ask your question]: ");
                }

                else if(strcmp(temp, "G") == 0) {
                    res.type = 1;
                    printf("[Guess]: ");
                }

                fgets(res.content, sizeof(res.content), stdin);
                *strchr(res.content, '\n') = '\0';
                res.from_client = 0;
                res.client_turn = 0;
                res.prev_turn= 1;
                write(client_0, &res, sizeof(res));

                if(strcmp(temp, "Q") == 0) {
                    read(client_0, &res, sizeof(res));
                    printf("Client 0 answered: %s\n", res.content);
                    printf("Eliminate a name // G to guess // D to finish: ");
                    fgets(temp, sizeof(temp), stdin);
                    *strchr(temp, '\n') = 0;
                    if(strcmp(temp, "G") == 0) {
                        res.type = 1;
                        printf("[Guess]: ");
                        fgets(res.content, sizeof(res.content), stdin);
                        *strchr(res.content, '\n') = '\0';
                        write(client_0, &res, sizeof(res));
                    }
                    if(strcmp(temp, "D") == 0) {
                        res.type = 3;
                        write(client_0, &res, sizeof(res));
                    }
                }
            }
        }
    }
}
