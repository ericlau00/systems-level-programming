#include <stdio.h>
#include <stdlib.h>

int problem1(int limit);

int problem5(int limit);
int is_divisible(int number, int limit);

int problem6(int limit);
int sum_squares(int limit);
int square_sum(int limit);

int main() {
    printf("%d\n",problem1(1000));
    printf("%d\n",problem5(20));
    printf("%d\n",problem6(100));
}

int problem1(int limit) {
    int i;
    int sum = 0;
    for(i = 1; i < limit; i++) {
        if(i % 3 == 0 || i % 5 == 0) 
            sum += i;
    }
    return sum;
}

int problem5(int limit) {
    int solved = 1;
    int smallest;
    for(smallest = 1; solved == 1; smallest++) {
        solved = is_divisible(smallest, limit);
    }
    return smallest - 1;
}

int is_divisible(int number, int limit) {
    int i;
    for(i = 1; i < limit + 1; i++) {
        if(number % i != 0)
            return 1;
    }
    return 0;
}

int problem6(int limit) {
    return square_sum(limit) - sum_squares(limit);
}

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