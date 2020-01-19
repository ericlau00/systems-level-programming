#include "networking.h"
#include "random.h"

struct response {
    int type; // 0 is question, 1 is guess, 2 is answer, 3 is done, 4 is gameover
    char content[256];
};

int game_logic(int client, struct response res, char * chosen);

int ask_initial_question(int client, struct response res);