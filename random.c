#include "random.h"

int num_characters(int * x) {
    char temp[256];
    int i = 0;
    FILE * wc;
    wc = popen("wc characters", "r");
    if (wc != NULL) {
        while (!feof(wc) && (i < 255)) {
            fread(&temp[i++], 1, 1, wc);
        }
        temp[i] = 0;
        pclose(wc);
        char * result;
        strcpy(result, temp);
        int numnewlines, numlines, numchars;
        sscanf(result, "%d %d %d characters\n", &numnewlines, &numlines, &numchars);
        *x = numlines;
        return 0;
    }
    else {
        return -1;
    }
}

void get_characters(char ** characters) {
    int numchars;
    num_characters(&numchars);
    FILE * charfile;
    charfile = fopen("characters", "r");
    char temp[255];
    int i;
    for (i = 0; i < numchars; i++) {
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

int random_int(int div) {
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
    int ans = abs(random) % div;
    return ans;
}

int get_random(char random_characters[16][20]) {
    int numchars;
    num_characters(&numchars);
    char ** characters = malloc(sizeof(char * ) * numchars);
    get_characters(characters);
    int random_ints[16];
    int i, j, x;
    for( i = 0; i < 16; i++ ) {
        x = random_int(numchars);
        for( j = 0; j < i; j++) {
            while(x == random_ints[j]) {
                x = random_int(numchars);
            }
        }
        random_ints[i] = x;
        strcpy(random_characters[i], characters[random_ints[i]]);
    }
    return 0;
}