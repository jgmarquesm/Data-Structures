#include <stdlib.h>
#include <stdio.h>
#include "../include/array.h"
//#--ADD_TO_INCLUDE
#include "../include/static_queue.h"

typedef struct _static_queue {
    Array *data;
} StaticQueue;

const size_t size_of_static_queue_type = sizeof(StaticQueue);

StaticQueue *StaticQueue_create(const long capacity, unsigned int size_of_type) {
    if (anyThrows(
            1,
            ExceptionHandler_is_non_positive("StaticQueue_create", "Capacity", capacity, true, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    StaticQueue *queue = (StaticQueue *) calloc(1, size_of_static_queue_type);
    queue->data = Array_create(capacity, size_of_type);
    return queue;
}

bool StaticQueue_clean(StaticQueue *queue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticQueue_clean", "Static Queue", (void *) queue, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Array_clean(queue->data);
    return __NOT_DEFAULT_BOOL__;
}

bool StaticQueue_destroy(StaticQueue **queue_ref) {
    StaticQueue *queue = *queue_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticQueue_destroy", "Static Queue", (void *) queue, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Array_delete(&(queue->data));
    free(queue);
    *queue_ref = __DEFAULT_PTR__;
    return __NOT_DEFAULT_BOOL__;
}

bool StaticQueue_is_empty(void *queue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticQueue_is_empty", "Static Queue", (void *) queue, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __NOT_DEFAULT_BOOL__;
    return Array_is_empty(((StaticQueue *) queue)->data);
}

bool StaticQueue_is_full(void *queue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticQueue_is_full", "Static Queue", (void *) queue, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    return Array_is_full(((StaticQueue *) queue)->data);
}

bool StaticQueue_enqueue(StaticQueue *queue, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticQueue_enqueue", "Static Queue", (void *) queue, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("StaticQueue_enqueue", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Array_add_last(queue->data, data);
    return __NOT_DEFAULT_BOOL__;
}

void *StaticQueue_peek(const StaticQueue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticQueue_peek", "Static Queue", (void *) queue, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("StaticQueue_peek", "Data", (void *) queue, StaticQueue_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return Array_first_element(queue->data);
}

bool StaticQueue_dequeue(StaticQueue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticQueue_dequeue", "Static Queue", (void *) queue, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("StaticQueue_dequeue", "Data", (void *) queue, StaticQueue_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    return Array_remove_first(queue->data);
}

void StaticQueue_print(const StaticQueue *queue, __TYPE_PRINT_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticQueue_print", "Static Queue", (void *) queue, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("StaticQueue_print", "Data", (void *) queue, StaticQueue_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return;
    printf("\nCapacity: %ld. Top: %ld.\n", Array_capacity(queue->data), Array_size(queue->data) - 1);
    printf("--(");
    long size = Array_size(queue->data);
    for(long i = 0; i < size - 1; i++) {
        __TYPE_PRINT_FUNCTION_NAME__(Array_get_at(queue->data, i));
        printf(", ");
    }
    __TYPE_PRINT_FUNCTION_NAME__(Array_get_at(queue->data, Array_size(queue->data) - 1));
    puts(")--");
}

long StaticQueue_size(const StaticQueue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticQueue_size", "Static Queue", (void *) queue, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("StaticQueue_size", "Data", (void *) queue, StaticQueue_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;
    return Array_size(queue->data);
}