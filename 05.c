#include <stdio.h>
#include <stdlib.h>

int divisible(int number, int limit) {
    int i;
    for(i = 1; i < limit + 1; i++) {
        if(number % i != 0) {
            return 1;
        }
    }
    return 0;
}

int solve(int limit) {
    int solved = 1;
    int smallest;
    for(smallest = 1; solved == 1; smallest++) {
        solved = divisible(smallest, limit);
    }
    return smallest - 1;
}

int main() {
    printf("%d\n",solve(20));
    return 0;
}