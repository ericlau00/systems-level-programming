#include <stdio.h>
#include <stdlib.h>

double average_array(int *array, int size)
{
    double sum = 0;
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
    for(; array[i] != '\0'; i++) { }
    return i;
}