#include <stdio.h>
#include <stdlib.h>

int solve(int limit) {
    int i;
    int sum = 0;
    for(i = 1; i < limit; i++) {
        if(i % 3 == 0 || i % 5 == 0) 
            sum += i;
    }
    return sum;
}

int main() {
    printf("%d\n", solve(1000));
    return 0;
}