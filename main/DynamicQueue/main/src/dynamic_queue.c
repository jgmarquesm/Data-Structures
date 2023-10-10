#include <stdlib.h>
#include <stdio.h>
#include "../include/doubly_linked_list.h"
//#--ADD_TO_INCLUDE
#include "../include/dynamic_queue.h"

typedef struct _dynamic_queue {
    DoublyLinkedList *data;
} DynamicQueue;

const size_t size_of_dynamic_queue_type = sizeof(DynamicQueue);

DynamicQueue *DynamicQueue_create() {
    DynamicQueue *S = (DynamicQueue *) calloc(1, size_of_dynamic_queue_type);
    S->data = DoublyLinkedList_create();
    return S;
}

bool DynamicQueue_clean(DynamicQueue *queue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicQueue_clean", "DynamicQueue", (void *) queue, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    DoublyLinkedList_clean(queue->data);
    return __NOT_DEFAULT_BOOL__;
}

bool DynamicQueue_destroy(DynamicQueue **queue_ref) {
    DynamicQueue *queue = *queue_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicQueue_destroy", "DynamicQueue", (void *) queue, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    DoublyLinkedList_destroy(&(queue->data));
    free(queue);
    *queue_ref = __DEFAULT_PTR__;
    return __NOT_DEFAULT_BOOL__;
}

bool DynamicQueue_is_empty(void *queue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicQueue_is_empty", "DynamicQueue", (void *) queue, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __NOT_DEFAULT_BOOL__;
    return DoublyLinkedList_is_empty(((DynamicQueue *) queue)->data);
}

bool DynamicQueue_enqueue(DynamicQueue *queue, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicQueue_enqueue", "DynamicQueue", (void *) queue, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DynamicQueue_enqueue", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    DoublyLinkedList_add_last(queue->data, data);
    return __NOT_DEFAULT_BOOL__;
}

void *DynamicQueue_peek(const DynamicQueue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicQueue_peek", "DynamicQueue", (void *) queue, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DynamicQueue_peek", "DynamicQueue", (void *) queue, DynamicQueue_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return DoublyLinkedList_get(queue->data, 0);
}

void *DynamicQueue_dequeue(DynamicQueue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicQueue_dequeue", "DynamicQueue", (void *) queue, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DynamicQueue_dequeue", "DynamicQueue", (void *) queue, DynamicQueue_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return DoublyLinkedList_remove_first(queue->data);
}

void DynamicQueue_print(const DynamicQueue *queue, __TYPE_PRINT_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicQueue_print", "DynamicQueue", (void *) queue, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DynamicQueue_print", "DynamicQueue", (void *) queue, DynamicQueue_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return;
    printf("--(");
    size_t size = DoublyLinkedList_size(queue->data);
    for(size_t i = 0; i < size - 1; i++) {
        __TYPE_PRINT_FUNCTION_NAME__(DoublyLinkedList_get(queue->data, i));
        printf(" -> ");
    }
    __TYPE_PRINT_FUNCTION_NAME__(DoublyLinkedList_get(queue->data, DoublyLinkedList_size(queue->data) - 1));
    puts(")--");
}

size_t DynamicQueue_size(const DynamicQueue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicQueue_size", "DynamicQueue", (void *) queue, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DynamicQueue_size", "DynamicQueue", (void *) queue, DynamicQueue_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_SIZE_T__;
    return DoublyLinkedList_size(queue->data);
}