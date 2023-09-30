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
    DynamicQueue *S = (DynamicQueue *) calloc(1, sizeof(DynamicQueue));
    S->data = DoublyLinkedList_create();
    return S;
}

bool DynamicQueue_clean(DynamicQueue *queue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicQueue_clean", "DynamicQueue", (void *) queue, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    DoublyLinkedList_clean(queue->data);
    return true;
}

bool DynamicQueue_destroy(DynamicQueue **queue_ref) {
    DynamicQueue *queue = *queue_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicQueue_destroy", "DynamicQueue", (void *) queue, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    DoublyLinkedList_destroy(&(queue->data));
    free(queue);
    *queue_ref = NULL;
    return true;
}

bool DynamicQueue_is_empty(void *queue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicQueue_is_empty", "DynamicQueue", (void *) queue, SUPPRESS_PRINT_ERROR)
        )
    ) return true;
    return DoublyLinkedList_is_empty(((DynamicQueue *) queue)->data);
}

bool DynamicQueue_enqueue(DynamicQueue *queue, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicQueue_enqueue", "DynamicQueue", (void *) queue, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DynamicQueue_enqueue", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    DoublyLinkedList_add_last(queue->data, data);
    return true;
}

void *DynamicQueue_peek(const DynamicQueue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicQueue_peek", "DynamicQueue", (void *) queue, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DynamicQueue_peek", "DynamicQueue", (void *) queue, DynamicQueue_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return DoublyLinkedList_get(queue->data, 0);
}

void *DynamicQueue_dequeue(DynamicQueue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicQueue_dequeue", "DynamicQueue", (void *) queue, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DynamicQueue_dequeue", "DynamicQueue", (void *) queue, DynamicQueue_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return DoublyLinkedList_remove_first(queue->data);
}

void DynamicQueue_print(const DynamicQueue *queue, void (*type_print_function)(void * data)) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DynamicQueue_print", "DynamicQueue", (void *) queue, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DynamicQueue_print", "DynamicQueue", (void *) queue, DynamicQueue_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    printf("--(");
    size_t size = DoublyLinkedList_size(queue->data);
    for(size_t i = 0; i < size - 1; i++) {
        type_print_function(DoublyLinkedList_get(queue->data, i));
        printf(" -> ");
    }
    type_print_function(DoublyLinkedList_get(queue->data, DoublyLinkedList_size(queue->data) - 1));
    puts(")--");
}

size_t DynamicQueue_size(const DynamicQueue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DynamicQueue_size", "DynamicQueue", (void *) queue, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DynamicQueue_size", "DynamicQueue", (void *) queue, DynamicQueue_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    return DoublyLinkedList_size(queue->data);
}