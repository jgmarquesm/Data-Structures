#include <stdlib.h>
#include <stdio.h>
#include "../include/array.h"
//#--ADD_TO_INCLUDE
#include "../include/static_stack.h"

typedef struct _static_stack {
    Array *data;
} StaticStack;

const size_t size_of_static_stack_type = sizeof(StaticStack);

StaticStack *StaticStack_create(const long capacity, unsigned int size_of_type) {
    if (anyThrows(
            1,
            ExceptionHandler_is_non_positive("StaticStack_create", "Capacity", capacity, true, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    StaticStack *stack = (StaticStack *) calloc(1, sizeof(StaticStack));
    stack->data = Array_create(capacity, size_of_type);
    return stack;
}

bool StaticStack_clean(StaticStack *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_clean", "Static Stack", (void *) stack, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Array_clean(stack->data);
    return true;
}

bool StaticStack_destroy(StaticStack **stack_ref) {
    StaticStack *stack = *stack_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_destroy", "Static Stack", (void *) stack, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Array_delete(&(stack->data));
    free(stack);
    *stack_ref = NULL;
    return true;
}

bool StaticStack_is_empty(void *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_is_empty", "Static Stack", (void *) stack, SUPPRESS_PRINT_ERROR)
        )
    ) return true;
    return Array_is_empty(((StaticStack *) stack)->data);
}

bool StaticStack_is_full(void *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_is_full", "Static Stack", (void *) stack, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    return Array_is_full(((StaticStack *) stack)->data);
}

bool StaticStack_push(StaticStack *stack, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_push", "Static Stack", (void *) stack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("StaticStack_push", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Array_add_last(stack->data, data);
    return true;
}

void *StaticStack_peek(const StaticStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_peek", "Static Stack", (void *) stack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("StaticStack_peek", "Data", (void *) stack, StaticStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return Array_last_element(stack->data);
}

void *StaticStack_pop(StaticStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_pop", "Static Stack", (void *) stack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("StaticStack_pop", "Data", (void *) stack, StaticStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    void *popped = Array_last_element(stack->data);
    Array_remove_last(stack->data);
    return popped;
}

void StaticStack_print(const StaticStack *stack, void (*type_print_function)(void * data)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_print", "Static Stack", (void *) stack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("StaticStack_print", "Data", (void *) stack, StaticStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    printf("\nCapacity: %ld. Top: %ld.\n", Array_capacity(stack->data), Array_size(stack->data) - 1);
    printf("-:[");
    long size = Array_size(stack->data);
    for(long i = 0; i < size - 1; i++) {
        type_print_function(Array_get_at(stack->data, i));
        printf(", ");
    }
    type_print_function(Array_get_at(stack->data, Array_size(stack->data) - 1));
    puts("]:-");
}

long StaticStack_size(const StaticStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_size", "Static Stack", (void *) stack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("StaticStack_size", "Data", (void *) stack, StaticStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    return Array_size(stack->data);
}