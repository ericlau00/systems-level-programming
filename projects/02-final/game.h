#include "networking.h"
#include "random.h"

#define HEADER " ______________________\n|                      |\n|   Guess Whom'st've   |\n|______________________|\n"
#define QUESTION 0
#define GUESS 1
#define ANSWER 2
#define DONE 3
#define GAMEOVER 4

struct response {
    int type;
    char content[256];
};

struct gameboard {
    int index[16];
    char characters[16][20];
};

int board_setup(struct gameboard * board);

int chosen_setup(int * chosen);

int print_board(struct gameboard * board, int chosen);

int name_size(char *name);

int game_logic(int client, struct response res, int chosen, struct gameboard * board);

int ask_initial_question(int client, struct response res);

int answer_question(struct response * res);

int check_guess(struct response * res, int chosen, int client, struct gameboard * board);

int flip_characters(struct response * res, struct gameboard * board);

int ask_or_guess(struct response * res);