#include "../include/dynamic_queue.h"
#include "../include/doubly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>
//#--ADD_TO_INCLUDE

typedef struct _dynamic_stack {
    LinkedList *data;
} Stack;

Stack *Stack_create() {
    Stack *S = (Stack *) calloc(1, sizeof(Stack));
    S->data = LinkedList_create();
    return S;
}

void Stack_clean(Stack *S) {
    LinkedList_clean(S->data);
}

void Stack_destroy(Stack **S_ref) {
    Stack *S = *S_ref;
    LinkedList_destroy(&(S->data));
    free(S);
    *S_ref = NULL;
}

bool Stack_is_empty(const Stack *S) {
    return LinkedList_is_empty(S->data);
}

void Stack_enqueue(Stack *S, void *data) {
    LinkedList_add_last(S->data, data);
}

void *Stack_peek(const Stack *S) {
    if (Stack_is_empty(S)) {
        fprintf(stderr, "\nERROR: on function 'Stack_peek'.\n");
        fprintf(stderr, "ERROR: Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    return LinkedList_get(S->data, 0);
}

void Stack_dequeue(Stack *S) {
    if (Stack_is_empty(S)) {
        fprintf(stderr, "\nERROR: on function 'Stack_pop'.\n");
        fprintf(stderr, "ERROR: Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    LinkedList_remove_first(S->data);
}

void Stack_print(const Stack *S, void (*type_print_function)(void * data)) {
    if (Stack_is_empty(S)){
        fprintf(stderr, "\nERROR: on function 'Stack_print'.\n");
        fprintf(stderr, "ERROR: Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    printf("--(");
    size_t size = LinkedList_size(S->data);
    for(size_t i = 0; i < size - 1; i++) {
        type_print_function(LinkedList_get(S->data, i));
        printf(" -> ");
    }
    type_print_function(LinkedList_get(S->data, LinkedList_size(S->data) - 1));
    puts(")--");
}

size_t Stack_size(const Stack *S) {
    return LinkedList_size(S->data);
}