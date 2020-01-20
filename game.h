#include "networking.h"
#include "random.h"

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

int game_setup(struct gameboard * board, char * chosen);

int print_board(struct gameboard * board, char * chosen);

int game_logic(int client, struct response res, char * chosen, struct gameboard * board);

int ask_initial_question(int client, struct response res);

int answer_question(struct response * res);

int check_guess(struct response * res, char * chosen, int client);

int flip_characters(struct response * res);

int ask_or_guess(struct response * res);