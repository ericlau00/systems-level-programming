#include <stdio.h>
#include <stdlib.h>

int sum_squares(int limit) {
    int i;
    int sum = 0;
    for(i = 1; i < limit + 1; i++) {
        sum += i * i;
    }
    return sum;
}

int square_sum(int limit) {
    int i;
    int sum = 0;
    for(i = 1; i < limit + 1; i++) {
        sum += i;
    }
    return sum * sum;
}

int difference(int limit) {
    return square_sum(limit) - sum_squares(limit);
}

int main() {
    printf("%d\n", difference(100));
    return 0;
}