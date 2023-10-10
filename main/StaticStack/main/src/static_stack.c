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
            ExceptionHandler_is_non_positive("StaticStack_create", "Capacity", capacity, true, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    StaticStack *stack = (StaticStack *) calloc(1, size_of_static_stack_type);
    stack->data = Array_create(capacity, size_of_type);
    return stack;
}

bool StaticStack_clean(StaticStack *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_clean", "Static Stack", (void *) stack, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Array_clean(stack->data);
    return __NOT_DEFAULT_BOOL__;
}

bool StaticStack_destroy(StaticStack **stack_ref) {
    StaticStack *stack = *stack_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_destroy", "Static Stack", (void *) stack, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Array_delete(&(stack->data));
    free(stack);
    *stack_ref = __DEFAULT_PTR__;
    return __NOT_DEFAULT_BOOL__;
}

bool StaticStack_is_empty(void *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_is_empty", "Static Stack", (void *) stack, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __NOT_DEFAULT_BOOL__;
    return Array_is_empty(((StaticStack *) stack)->data);
}

bool StaticStack_is_full(void *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_is_full", "Static Stack", (void *) stack, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    return Array_is_full(((StaticStack *) stack)->data);
}

bool StaticStack_push(StaticStack *stack, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_push", "Static Stack", (void *) stack, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("StaticStack_push", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Array_add_last(stack->data, data);
    return __NOT_DEFAULT_BOOL__;
}

void *StaticStack_peek(const StaticStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_peek", "Static Stack", (void *) stack, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("StaticStack_peek", "Data", (void *) stack, StaticStack_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return Array_last_element(stack->data);
}

void *StaticStack_pop(StaticStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_pop", "Static Stack", (void *) stack, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("StaticStack_pop", "Data", (void *) stack, StaticStack_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    void *popped = Array_last_element(stack->data);
    Array_remove_last(stack->data);
    return popped;
}

void StaticStack_print(const StaticStack *stack, __TYPE_PRINT_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_print", "Static Stack", (void *) stack, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("StaticStack_print", "Data", (void *) stack, StaticStack_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return;
    printf("\nCapacity: %ld. Top: %ld.\n", Array_capacity(stack->data), Array_size(stack->data) - 1);
    printf("-:[");
    long size = Array_size(stack->data);
    for(long i = 0; i < size - 1; i++) {
        __TYPE_PRINT_FUNCTION_NAME__(Array_get_at(stack->data, i));
        printf(", ");
    }
    __TYPE_PRINT_FUNCTION_NAME__(Array_get_at(stack->data, Array_size(stack->data) - 1));
    puts("]:-");
}

long StaticStack_size(const StaticStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_size", "Static Stack", (void *) stack, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("StaticStack_size", "Data", (void *) stack, StaticStack_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;
    return Array_size(stack->data);
}