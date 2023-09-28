#include <stdlib.h>
#include <stdio.h>
#include "../include/doubly_linked_list.h"
//#--ADD_TO_INCLUDE
#include "../include/dynamic_stack.h"

typedef struct _dynamic_stack {
    DoublyLinkedList *data;
} DynamicStack;

const size_t size_of_dynamic_stack_type = sizeof(DynamicStack);

DynamicStack *DynamicStack_create() {
    DynamicStack *stack = (DynamicStack *) calloc(1, sizeof(DynamicStack));
    stack->data = DoublyLinkedList_create();
    return stack;
}

void DynamicStack_clean(DynamicStack *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicStack_clean", "DynamicStack", (void *) stack, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    DoublyLinkedList_clean(stack->data);
}

void DynamicStack_destroy(DynamicStack **stack_ref) {
    DynamicStack *stack = *stack_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicStack_destroy", "DynamicStack", (void *) stack, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    DoublyLinkedList_destroy(&(stack->data));
    free(stack);
    *stack_ref = NULL;
}

bool DynamicStack_is_empty(void *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicStack_empty", "DynamicStack", (void *) stack, SUPPRESS_PRINT_ERROR)
        )
    ) return true;
    return DoublyLinkedList_is_empty(((DynamicStack *) stack)->data);
}

void DynamicStack_push(DynamicStack *stack, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicStack_push", "DynamicStack", (void *) stack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DynamicStack_push", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    DoublyLinkedList_add_last(stack->data, data);
}

void *DynamicStack_peek(const DynamicStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicStack_peek", "DynamicStack", (void *) stack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DynamicStack_peek", "DynamicStack", (void *) stack, DynamicStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    long top = DoublyLinkedList_size(stack->data) - 1;
    return DoublyLinkedList_get(stack->data, top);
}

void DynamicStack_pop(DynamicStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicStack_pop", "DynamicStack", (void *) stack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DynamicStack_pop", "DynamicStack", (void *) stack, DynamicStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    DoublyLinkedList_remove_last(stack->data);
}

void DynamicStack_print(const DynamicStack *stack, void (*type_print_function)(void * data)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicStack_print", "DynamicStack", (void *) stack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DynamicStack_print", "DynamicStack", (void *) stack, DynamicStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    printf("-:[");
    size_t size = DoublyLinkedList_size(stack->data);
    for(size_t i = 0; i < size - 1; i++) {
        type_print_function(DoublyLinkedList_get(stack->data, i));
        printf(" -> ");
    }
    type_print_function(DoublyLinkedList_get(stack->data, DoublyLinkedList_size(stack->data) - 1));
    puts("]:-");
}

size_t DynamicStack_size(const DynamicStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicStack_size", "DynamicStack", (void *) stack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DynamicStack_size", "DynamicStack", (void *) stack, DynamicStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    return DoublyLinkedList_size(stack->data);
}