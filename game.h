#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

struct board {
    char * characters[16];
    int state[16];
    char * chosen;
};

struct response {
    int user;
    int type;
    char * content;
};