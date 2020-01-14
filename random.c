#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> //open
#include <unistd.h> //read, write, close
#include <errno.h> //errno
#include <sys/stat.h> //umask, stat
#include <time.h> //ctime
#include <dirent.h>
#include <sys/types.h>

void get_characters(char ** characters) {
    FILE * charfile;
    charfile = fopen("characters", "r");
    char temp[255];
    int i;
    for (i = 0; i < 133; i++) {
        fgets(temp, 255, charfile);
        char *pos;
        if ((pos=strchr(temp, '\n')) != NULL)
            *pos = '\0';
        char * str = malloc(strlen(temp)+1);
        strcpy(str, temp);
        characters[i] = str;
    }
    fclose(charfile);
}

int _random() {
    int random;
    int fd = open("/dev/random", O_RDONLY);
    if (fd < 0) {
        printf("errno %d error: %s\n", errno, strerror(errno));
        return 1;
    }
    if (read(fd, &random, sizeof(int)) < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    }
    close(fd);
    return abs(random) % 133;
}

int get_random() {
    char ** characters = malloc(sizeof(char *) * 133);
    get_characters(characters);
    int random_ints[16];
    char ** random_characters = malloc(sizeof(char *) * 16);
    int i, j, x;
    for( i = 0; i < 16; i++ ) {
        x = _random();
        for( j = 0; j < i; j++) {
            while(x == random_ints[j]) {
                x = _random();
            }
        }
        random_ints[i] = x;
        random_characters[i] = characters[random_ints[i]];
    }
    for(i = 0; i < 16; i++) {
        printf("%s\n", random_characters[i]);
    }
    // for(i = 0; i < 133; i++) {
    //     free(characters[i]);
    // }
    // free(characters);
    // free(random_characters);
    return random_characters;
}