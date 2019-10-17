#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "headers.h"

int main() {
    srand( time(NULL) );
    struct wallet wallet0 = createWallet();
    printWallet(&wallet0);
    struct wallet wallet1 = createWallet();
    printWallet(&wallet1);
    struct wallet wallet2 = createWallet();
    printWallet(&wallet2);
    return 0;
}