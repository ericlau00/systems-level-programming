#include "game.h"

int ask_initial_question(int client, struct response res) {
    res.type = 0;
    fgets(res.content, sizeof(res.content), stdin);
    *strchr(res.content, '\n') = 0;
    write(client, &res, sizeof(res));

    return 0;
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
}

int game_logic(int client, struct response res, char * chosen) {
    read(client, &res, sizeof(res));

    // checking res type
    // res = question
    if (res.type == 0) {
        printf("You were asked: %s\n", res.content);
        printf("Your answer: ");
        res.type = 2;
        fgets(res.content, sizeof(res.content), stdin);
        *strchr(res.content, '\n') = 0;
    }
    // res = guess
    else if (res.type == 1) {
        printf("Your opponent guessed: %s\n", res.content);
        if (strcmp(res.content, chosen) == 0) {
            printf("HAHAHAHAH U TRASH U LOST\n");
            res.type = 4;
            strcpy(res.content, "Game Over");
            write(client, &res, sizeof(res));
            exit(0);
        }
        else {
            printf("The guess was incorrect\n");
        }
        ask_or_guess(&res);
    }
    // res = answer
    else if (res.type == 2) {
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
    // res = done
    else if (res.type == 3) {
        ask_or_guess(&res);
    }
    // res = gameover
    else if (res.type == 4) {
        printf("Congratulations u are slightly less trash than other guy\n");
        exit(0);
    }
    write(client, &res, sizeof(res));

    return 0;
}