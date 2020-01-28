#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  


char ** parse_args(char * line ) { 
    char * buff = line;
    char ** args = malloc(sizeof(char) * 6);
    int arg = 0;
    while(buff != NULL) { 
        args[arg++] = strsep(&buff, " ");
    }
    args[arg] = NULL;
    return args; 
}

int main() {
    char line[9] = "ls -a -l";
    char ** args = parse_args(line);
    execvp(args[0], args);
    return 0;
}
