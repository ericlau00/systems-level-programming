#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "headers.h"

struct wallet createWallet() {
    char* first[] = {"Kevin", "David", "Stephanie", "Eric", "Matthew", "Kazi", "Raymond", "Michael", "Ivan", "George", "Caleb"};
    char* last[] = {"Wang", "Lin", "Lau", "Chan", "Jamal", "Lee", "Sultan", "Chen", "Robertson", "Manriquez", "Clinton"};

    struct wallet instance; 
    instance.first_name = first[rand() % sizeof(first)/sizeof(char*)];
    instance.last_name = last[rand() % sizeof(last)/sizeof(char*)];
    instance.money = rand();

    return instance;
}

int printWallet(struct wallet* wallet) {
    printf("%s %s has %d dollars\n", wallet->first_name, wallet->last_name, wallet->money);
    return 0;
}

int spendMoney(struct wallet* wallet, int amount) {

}

int getMoney(struct wallet* wallet, int amount) {

}

int changeOwner(struct wallet* wallet, char* first_name, char* last_name) {

}