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
    DynamicStack *stack = (DynamicStack *) calloc(1, size_of_dynamic_stack_type);
    stack->data = DoublyLinkedList_create();
    return stack;
}

bool DynamicStack_clean(DynamicStack *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicStack_clean", "DynamicStack", (void *) stack, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    DoublyLinkedList_clean(stack->data);
    return __NOT_DEFAULT_BOOL__;
}

bool DynamicStack_destroy(DynamicStack **stack_ref) {
    DynamicStack *stack = *stack_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicStack_destroy", "DynamicStack", (void *) stack, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    DoublyLinkedList_destroy(&(stack->data));
    free(stack);
    *stack_ref = __DEFAULT_PTR__;
    return __NOT_DEFAULT_BOOL__;
}

bool DynamicStack_is_empty(void *stack) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicStack_empty", "DynamicStack", (void *) stack, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __NOT_DEFAULT_BOOL__;
    return DoublyLinkedList_is_empty(((DynamicStack *) stack)->data);
}

bool DynamicStack_push(DynamicStack *stack, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicStack_push", "DynamicStack", (void *) stack, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DynamicStack_push", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    DoublyLinkedList_add_last(stack->data, data);
    return __NOT_DEFAULT_BOOL__;
}

void *DynamicStack_peek(const DynamicStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicStack_peek", "DynamicStack", (void *) stack, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DynamicStack_peek", "DynamicStack", (void *) stack, DynamicStack_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    long top = DoublyLinkedList_size(stack->data) - 1;
    return DoublyLinkedList_get(stack->data, top);
}

void *DynamicStack_pop(DynamicStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicStack_pop", "DynamicStack", (void *) stack, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DynamicStack_pop", "DynamicStack", (void *) stack, DynamicStack_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return DoublyLinkedList_remove_last(stack->data);
}

void DynamicStack_print(const DynamicStack *stack, __TYPE_PRINT_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicStack_print", "DynamicStack", (void *) stack, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DynamicStack_print", "DynamicStack", (void *) stack, DynamicStack_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return;
    printf("-:[");
    size_t size = DoublyLinkedList_size(stack->data);
    for(size_t i = 0; i < size - 1; i++) {
        __TYPE_PRINT_FUNCTION_NAME__(DoublyLinkedList_get(stack->data, i));
        printf(" -> ");
    }
    __TYPE_PRINT_FUNCTION_NAME__(DoublyLinkedList_get(stack->data, DoublyLinkedList_size(stack->data) - 1));
    puts("]:-");
}

size_t DynamicStack_size(const DynamicStack *stack) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicStack_size", "DynamicStack", (void *) stack, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DynamicStack_size", "DynamicStack", (void *) stack, DynamicStack_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_SIZE_T__;
    return DoublyLinkedList_size(stack->data);
}