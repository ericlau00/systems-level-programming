#include <stdio.h>
#include <stdlib.h>
#include "methods.h"

int main()
{
    int ARRAY_SIZE = 3;
    int one[ARRAY_SIZE];
    one[0] = 1;
    one[1] = 10;
    one[2] = 24;
    printf("one: ");
    print_array(one, ARRAY_SIZE);

    printf("one average: %lf\n", average_array(one, ARRAY_SIZE));

    int two[ARRAY_SIZE];
    two[0] = 2;
    two[1] = 13;
    two[2] = 6;
    printf("two: ");
    print_array(two, ARRAY_SIZE);

    copy_array(one, two, ARRAY_SIZE);

    printf("two as copy of one: ");
    print_array(two, ARRAY_SIZE);

    char three[] = "three";
    printf("length of three: %d\n", length_array(three));

    char hellomynameisericlau[] = "hellomynameisericlau";
    printf("length of hellomynameisericlau: %d\n", length_array(hellomynameisericlau));
    return 0;
}