#include <stdlib.h>
#include <stdio.h>
#include "headers.h"

int main() {
    struct node * list;

    printf("Printing empty list:\n");
    print_list(list);

    printf("Adding #s 0-9 to list.\n");
    int value;
    for( value = 0; value < 10; value++) {
        list = insert_front(list, value);
    }

    printf("Printing list:\n");
    print_list(list);

    printf("Freeing list.\n");
    list = free_list(list);

    printf("Printing list:\n");
    print_list(list);

}