#include "game.h"

int board_setup(struct gameboard * board) {
    get_random(board->characters);
    int i = 0;
    for(i = 0; i < 16; i++) {
        board->index[i] = 0;
    }
    return 0;
}

int chosen_setup(int * chosen) {
    *chosen = random_int(16);
}

int print_board(struct gameboard * board, int chosen) {
    int i;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    for(i = 0; i < 16; i++) {
        // printf("%d. %s  %2d\n", i, board->characters[i], board->index[i]);
        if (i <= 9) {
            printf("%d.  %s", i, board->characters[i]);
        }
        else {
            printf("%d. %s", i, board->characters[i]);
        }

        int size = name_size(board->characters[i]);
        // printf("size: %d\n", size);
        int j;
        for (j=0; j<(24-size); j++) {
            printf(" ");
        }

        if (board->index[i]) {
            printf("[X]\n");
        }
        else {
            printf("[ ]\n");
        }
    }
    printf("\n");
    printf("\tYour character is: %s\n\n\n", board->characters[chosen]);
}

int name_size(char *name) {
    int i=0;
    while(name[i] != '\0') {
        i++;
    }
    return i;
}

int game_logic(int client, struct response res, int chosen, struct gameboard * board) {

    print_board(board, chosen);
    read(client, &res, sizeof(res));

    if (res.type == QUESTION) {
        answer_question(&res);
    }
    else if (res.type == GUESS) {
        check_guess(&res, chosen, client, board);
        if(res.type == GAMEOVER) {
            write(client, &res, sizeof(struct response));
            exit(0);
        }
        else {
            ask_or_guess(&res);
        }
    }
    else if (res.type == ANSWER) {
        flip_characters(&res, board);
    }
    else if (res.type == DONE) {
        ask_or_guess(&res);
    }
    else if (res.type == GAMEOVER) {
        printf("YOU WON!\n");
        exit(0);
    }
    write(client, &res, sizeof(res));

    return 0;
}

int ask_initial_question(int client, struct response res) {
    res.type = QUESTION;
    fgets(res.content, sizeof(res.content), stdin);
    *strchr(res.content, '\n') = 0;
    write(client, &res, sizeof(res));

    return 0;
}

int answer_question(struct response * res) {
    printf("You were asked: %s\n", res->content);
    printf("Your answer: ");
    res->type = ANSWER;
    fgets(res->content, sizeof(res->content), stdin);
    *strchr(res->content, '\n') = 0;

    return 0;
}

int check_guess(struct response * res, int chosen, int client, struct gameboard * board) {
    int guess;
    sscanf(res->content, "%d", &guess);
    printf("Your opponent guessed: %s\n", board->characters[guess]);
    if (guess == chosen) {
        printf("YOU LOST!\n");
        res->type = GAMEOVER;
        strcpy(res->content, "Game Over");
    }
    else {
        printf("The guess was incorrect\n");
    }
    return 0;
}

int flip_characters(struct response * res, struct gameboard * board) {
    printf("Your opponent answered: %s\n", res->content);
    printf("Enter characters ID to flip or type done when finished: ");
    char input[20];
    fgets(input, sizeof(input), stdin);
    *strchr(input, '\n') = 0;
    while (strcmp(input, "done") != 0) {
        int currflip;
        sscanf(input, "%d", &currflip);
        if (currflip < 0 || currflip > 15) {
            printf("Invalid character ID\n");
            printf("Enter a valid character ID or type done when finished: ");
            fgets(input, sizeof(input), stdin);
            *strchr(input, '\n') = 0;
        }
        else {
            board->index[currflip] = 1;
            printf("You flipped: %s\n", board->characters[currflip]);
            printf("Enter another characters ID to flip or type done when finished: ");
            fgets(input, sizeof(input), stdin);
            *strchr(input, '\n') = 0;
        }
    }
    res->type = DONE;
    strcpy(res->content, "flipping done");
    return 0;
}

int ask_or_guess(struct response * res) {
    printf("Ask a question or type g to guess: ");
    char input[256];
    fgets(input, sizeof(input), stdin);
    *strchr(input, '\n') = 0;
    if (strcmp(input, "g") == 0) {
        printf("Make a guess by entering the character's ID: ");
        res->type = GUESS;
        fgets(res->content, sizeof(res->content), stdin);
        *strchr(res->content, '\n') = 0;
    }
    else {
        res->type = QUESTION;
        strcpy(res->content, input);
    }
}