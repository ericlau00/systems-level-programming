#include <stdio.h>
#include <stdlib.h>

int average_array(int array[], int size);
void copy_array(int *one, int *two, int size);
void print_array(int array[], int size);
int length_array(char *array);

int main()
{
    int ARRAY_SIZE = 3;
    int one[ARRAY_SIZE];
    one[0] = 1;
    one[1] = 11;
    one[2] = 24;
    printf("one: ");
    print_array(one, ARRAY_SIZE);

    printf("one average: %d\n", average_array(one, ARRAY_SIZE));

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

int average_array(int array[], int size)
{
    int sum = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        sum += array[i];
    }
    return sum / size;
}

void copy_array(int *x, int *y, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        y[i] = x[i];
    }
}

void print_array(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("\n");
}

int length_array(char *array)
{
    int i = 0;
    for(; array[i] != '\0'; i++) {
        printf("%c\n", array[i]);
    }
    return i;
}