#include "networking.h"
#include "random.h"

#define QUESTION 0
#define GUESS 1
#define ANSWER 2
#define DONE 3
#define GAMEOVER 4

struct response {
    int type; // 0 is question, 1 is guess, 2 is answer, 3 is done, 4 is gameover
    char content[256];
};

int game_logic(int client, struct response res, char * chosen);

int ask_initial_question(int client, struct response res);

int answer_question(struct response * res);

int check_guess(struct response * res, char * chosen, int client);

int flip_characters(struct response * res);

int ask_or_guess(struct response * res);