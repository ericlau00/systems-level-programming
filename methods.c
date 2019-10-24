#include <stdlib.h>
#include <stdio.h>
#include "headers.h"

void print_list(struct node * node) {
    printf("[ ");
    for(; node != NULL; node = node->next) {
        printf("%d ", node->i);
    }
    printf("]\n");
}

struct node * insert_front(struct node * node, int value) {
    struct node * front = malloc(sizeof(struct node));
    front->i = value;
    front->next = node;
    return front;
}

struct node * free_list(struct node * node) {
    for(; node != NULL; node = node->next) {
        printf("freeing node: %d\n", node->i);
        struct node * current = node;
        free(current);
        current = NULL;
    }
    return node;
}

struct node * remove(struct node * front, int data) {
    for(; front != NULL; front )
}