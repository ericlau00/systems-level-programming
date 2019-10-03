#include <stdio.h>
#include <stdlib.h>

int main() {
    char x = 'x';
    int integer = 1;
    long longer = 12345678901;
    printf("%p\n", &x);
    printf("%p\n", &integer);
    printf("%p\n", &longer);
    char *cp = &x;
    int *ip = &integer;
    long *lp = &longer;
    printf("%c\n", *cp);
    printf("%d\n", *ip);
    printf("%ld\n", *lp);
    char unknown = *cp - 10;
    int unko = *ip * 4;
    printf("%d\n", unko);
    char *character = &integer;
    *character = 2;
    printf("%d\n", *character);
    printf("%d\n", integer);
}