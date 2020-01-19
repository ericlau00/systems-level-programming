#include "networking.h"
#include "random.h"

struct response {
        int type; // 0 is question, 1 is guess, 2 is answer, 3 is done, 4 is gameover
        char content[256];
    };