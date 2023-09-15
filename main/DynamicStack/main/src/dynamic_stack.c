#include "../include/dynamic_stack.h"
#include "../include/doubly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/doubly_linked_list.h"
#include "../include/node.h"
#include "../include/exception_handler.h"
//#--ADD_TO_INCLUDE

typedef struct _dynamic_stack {
    LinkedList *data;
} Stack;

Stack *Stack_create() {
    Stack *stack = (Stack *) calloc(1, sizeof(Stack));
    stack->data = LinkedList_create();
    return stack;
}

void Stack_clean(Stack *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Stack_clean", "Stack", (void *) stack)
        )
    ) return;
    LinkedList_clean(stack->data);
}

void Stack_destroy(Stack **stack_ref) {
    Stack *stack = *stack_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Stack_destroy", "Stack", (void *) stack)
        )
    ) return;
    LinkedList_destroy(&(stack->data));
    free(stack);
    *stack_ref = NULL;
}

bool Stack_is_empty(void *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Stack_empty", "Stack", (void *) stack)
        )
    ) return true;
    return LinkedList_is_empty(((Stack *) stack)->data);
}

void Stack_push(Stack *stack, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Stack_push", "Stack", (void *) stack),
            ExceptionHandler_is_null("Stack_push", "Data", data)
        )
    ) return;
    LinkedList_add_last(stack->data, data);
}

void *Stack_peek(const Stack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Stack_peek", "Stack", (void *) stack),
            ExceptionHandler_is_empty("Stack_peek", "Stack", (void *) stack, Stack_is_empty)
        )
    ) return NULL;
    long top = LinkedList_size(stack->data) - 1;
    return LinkedList_get(stack->data, top);
}

void Stack_pop(Stack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Stack_pop", "Stack", (void *) stack),
            ExceptionHandler_is_empty("Stack_pop", "Stack", (void *) stack, Stack_is_empty)
        )
    ) return;
    LinkedList_remove_last(stack->data);
}

void Stack_print(const Stack *stack, void (*type_print_function)(void * data)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Stack_print", "Stack", (void *) stack),
            ExceptionHandler_is_empty("Stack_print", "Stack", (void *) stack, Stack_is_empty)
        )
    ) return;
    printf("-:[");
    size_t size = LinkedList_size(stack->data);
    for(size_t i = 0; i < size - 1; i++) {
        type_print_function(LinkedList_get(stack->data, i));
        printf(" -> ");
    }
    type_print_function(LinkedList_get(stack->data, LinkedList_size(stack->data) - 1));
    puts("]:-");
}

size_t Stack_size(const Stack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Stack_size", "Stack", (void *) stack),
            ExceptionHandler_is_empty("Stack_size", "Stack", (void *) stack, Stack_is_empty)
        )
    ) return 0;
    return LinkedList_size(stack->data);
}