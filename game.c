#include "game.h"

int game_logic(int client, struct response res, char * chosen) {
    read(client, &res, sizeof(res));

    if (res.type == QUESTION) {
        answer_question(&res);
    }
    else if (res.type == GUESS) {
        check_guess(&res, chosen, client);
        ask_or_guess(&res);
    }
    else if (res.type == ANSWER) {
        printf("Your opponent answered: %s\n", res.content);
        printf("Enter characters name to flip or type done when finished: ");
        char currflip[20];
        fgets(currflip, sizeof(currflip), stdin);
        *strchr(currflip, '\n') = 0;
        while (strcmp(currflip, "done") != 0) {
            //modify board
            printf("You flipped: %s\n", currflip);
            printf("Enter another characters name to flip or type done when finished: ");
            fgets(currflip, sizeof(currflip), stdin);
            *strchr(currflip, '\n') = 0;
        }
        res.type = 3;
        strcpy(res.content, "flipping done");
    }
    else if (res.type == DONE) {
        ask_or_guess(&res);
    }
    else if (res.type == GAMEOVER) {
        printf("Congratulations u are slightly less trash than other guy\n");
        exit(0);
    }
    write(client, &res, sizeof(res));

    return 0;
}

int ask_initial_question(int client, struct response res) {
    res.type = 0;
    fgets(res.content, sizeof(res.content), stdin);
    *strchr(res.content, '\n') = 0;
    write(client, &res, sizeof(res));

    return 0;
}

int answer_question(struct response * res) {
    printf("You were asked: %s\n", res->content);
    printf("Your answer: ");
    res->type = 2;
    fgets(res->content, sizeof(res->content), stdin);
    *strchr(res->content, '\n') = 0;

    return 0;
}

int check_guess(struct response * res, char * chosen, int client) {
    printf("Your opponent guessed: %s\n", res->content);
    if (strcmp(res->content, chosen) == 0) {
        printf("HAHAHAHAH U TRASH U LOST\n");
        res->type = 4;
        strcpy(res->content, "Game Over");
        write(client, &res, sizeof(struct response));
        exit(0);
    }
    else {
        printf("The guess was incorrect\n");
    }
}

int ask_or_guess(struct response * res) {
    printf("Ask a question or type g to guess: ");
    char input[256];
    fgets(input, sizeof(input), stdin);
    *strchr(input, '\n') = 0;
    if (strcmp(input, "g") == 0) {
        printf("Make a guess: ");
        res->type = 1;
        fgets(res->content, sizeof(res->content), stdin);
        *strchr(res->content, '\n') = 0;
    }
    else {
        res->type = 0;
        strcpy(res->content, input);
    }

    return 0;
}