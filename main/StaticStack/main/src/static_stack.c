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
    StaticStack *staticStack = (StaticStack *) calloc(1, sizeof(StaticStack));
    staticStack->data = Array_create(capacity, size_of_type);
    return staticStack;
}

void StaticStack_clean(StaticStack *staticStack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_clean", "Static Stack", (void *) staticStack, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    Array_clean(staticStack->data);
}

void StaticStack_destroy(StaticStack **staticStack_ref) {
    StaticStack *staticStack = *staticStack_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_destroy", "Static Stack", (void *) staticStack, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    Array_delete(&(staticStack->data));
    free(staticStack);
    *staticStack_ref = NULL;
}

bool StaticStack_is_empty(void *staticStack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_is_empty", "Static Stack", (void *) staticStack, SUPPRESS_PRINT_ERROR)
        )
    ) return true;
    return Array_is_empty(((StaticStack *) staticStack)->data);
}

bool StaticStack_is_full(void *staticStack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticStack_is_full", "Static Stack", (void *) staticStack, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    return Array_is_full(((StaticStack *) staticStack)->data);
}

void StaticStack_push(StaticStack *staticStack, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_push", "Static Stack", (void *) staticStack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("StaticStack_push", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    Array_add_last(staticStack->data, data);
}

void *StaticStack_peek(const StaticStack *staticStack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_peek", "Static Stack", (void *) staticStack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("StaticStack_peek", "Data", (void *) staticStack, StaticStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    long top = Array_size(staticStack->data) - 1;
    return Array_get_at(staticStack->data, top);
}

void StaticStack_pop(StaticStack *staticStack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_pop", "Static Stack", (void *) staticStack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("StaticStack_pop", "Data", (void *) staticStack, StaticStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    Array_remove_last(staticStack->data);
}

void StaticStack_print(const StaticStack *staticStack, void (*type_print_function)(void * data)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_print", "Static Stack", (void *) staticStack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("StaticStack_print", "Data", (void *) staticStack, StaticStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    printf("\nCapacity: %ld. Top: %ld.\n", Array_capacity(staticStack->data), Array_size(staticStack->data) - 1);
    printf("-:[");
    long size = Array_size(staticStack->data);
    for(long i = 0; i < size - 1; i++) {
        type_print_function(Array_get_at(staticStack->data, i));
        printf(", ");
    }
    type_print_function(Array_get_at(staticStack->data, Array_size(staticStack->data) - 1));
    puts("]:-");
}

long StaticStack_size(const StaticStack *staticStack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticStack_size", "Static Stack", (void *) staticStack, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("StaticStack_size", "Data", (void *) staticStack, StaticStack_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    return Array_size(staticStack->data);
}