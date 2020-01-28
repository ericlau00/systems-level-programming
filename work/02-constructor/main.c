#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "headers.h"

int main() {
    srand( time(NULL) );

    struct wallet wallet0 = createWallet();
    printWallet(&wallet0);
    printf("spend 10 dollars\n");
    spendMoney(&wallet0, 10);
    printWallet(&wallet0);
    printf("\n");

    struct wallet wallet1 = createWallet();
    printWallet(&wallet1);
    printf("gain 1000 dollars\n");
    gainMoney(&wallet1, 1000);
    printWallet(&wallet1);
    printf("\n");

    struct wallet wallet2 = createWallet();
    printWallet(&wallet2);
    printf("change owner to Eric Lau\n");
    changeOwner(&wallet2, "Eric", "Lau");
    printWallet(&wallet2);
    printf("\n");

    return 0;
}