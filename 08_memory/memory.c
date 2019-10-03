#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int q = 2151686160;
    printf("%%d: %d\n", q);
    printf("%%u: %u\n", q);
    printf("%%o: %o\n", q);
    printf("%%x: %x\n", q);
    printf("%%hhx: %hhx\n", q);
    printf("%%hhu: %hhu\n", q);
    return 0;
}