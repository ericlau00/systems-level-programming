#include <stdlib.h>
#include <stdio.h>
#include "headers.h"

int main() {
    struct node * list = NULL;

    printf("Printing empty list:\n");
    print_list(list);

    printf("\n");

    printf("Adding #s 0-9 to list.\n");
    int value;
    for( value = 0; value < 10; value++) {
        list = insert_front(list, value);
    }

    printf("Printing list:\n");
    print_list(list);

    printf("\n");

    printf("Removing 9:\n");
    list = remove_node(list, 9);
    print_list(list);

    printf("\n");

    // printf("Removing 8:\n");
    // list = remove_node(list, 8);
    // print_list(list);

    // printf("\n");

    // printf("Removing 0:\n");
    // list = remove_node(list, 0);
    // print_list(list);

    // printf("\n");

    // printf("Removing 1:\n");
    // list = remove_node(list, 1);
    // print_list(list);

    // printf("\n");

    // printf("Removing 5:\n");
    // list = remove_node(list, 5);
    // print_list(list);

    // printf("\n");

    printf("Freeing list.\n");
    list = free_list(list);

    printf("Printing list:\n");
    print_list(list);

}