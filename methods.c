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
    for(; node != NULL;) {
        printf("freeing node: %d\n", node->i);
        struct node * current = node;
        node = node -> next;
        free(current);
        current = NULL;
    }
    return node;
}

struct node * remove_node(struct node * front, int data) {
    struct node * current = front; 
    if (front == NULL ) return front;
    else {
        if(front->i == data) {
            front = front -> next;
            free(current);
            current = NULL;
            return front;
        }
        else {
            while(current->next != NULL) {
                if(current->next->i == data) {
                    struct node * nix = current;
                    current = current ->next -> next; 
                    free(nix);
                    nix = NULL;
                    return front;
                }
                current = current -> next;
            }
        }
    }
    return 0;
}