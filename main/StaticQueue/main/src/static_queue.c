#include "../include/static_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/array.h"
//#--ADD_TO_INCLUDE

typedef struct _static_queue {
    Array *data;
} StaticQueue;

StaticQueue *StaticQueue_create(const long capacity, unsigned int size_of_type) {
    if (anyThrows(
            1,
            ExceptionHandler_is_non_positive("StaticQueue_create", "Capacity", capacity, true)
        )
    ) return NULL;
    StaticQueue *staticQueue = (StaticQueue *) calloc(1, sizeof(StaticQueue));
    staticQueue->data = Array_create(capacity, size_of_type);
    return staticQueue;
}

void StaticQueue_clean(StaticQueue *staticQueue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticQueue_clean", "Static Queue", (void *) staticQueue)
        )
    ) return;
    Array_clean(staticQueue->data);
}

void StaticQueue_destroy(StaticQueue **staticQueue_ref) {
    StaticQueue *staticQueue = *staticQueue_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticQueue_destroy", "Static Queue", (void *) staticQueue)
        )
    ) return;
    Array_delete(&(staticQueue->data));
    free(staticQueue);
    *staticQueue_ref = NULL;
}

bool StaticQueue_is_empty(void *staticQueue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticQueue_is_empty", "Static Queue", (void *) staticQueue)
        )
    ) return true;
    return Array_is_empty(((StaticQueue *) staticQueue)->data);
}

bool StaticQueue_is_full(void *staticQueue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("StaticQueue_is_full", "Static Queue", (void *) staticQueue)
        )
    ) return false;
    return Array_is_full(((StaticQueue *) staticQueue)->data);
}

void StaticQueue_enqueue(StaticQueue *staticQueue, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticQueue_enqueue", "Static Queue", (void *) staticQueue),
            ExceptionHandler_is_null("StaticQueue_enqueue", "Data", data)
        )
    ) return;
    Array_add_last(staticQueue->data, data);
}

void *StaticQueue_peek(const StaticQueue *staticQueue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticQueue_peek", "Static Queue", (void *) staticQueue),
            ExceptionHandler_is_empty("StaticQueue_peek", "Data", (void *) staticQueue, StaticQueue_is_empty)
        )
    ) return NULL;
    return Array_get_at(staticQueue->data, 0);
}

void StaticQueue_dequeue(StaticQueue *staticQueue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticQueue_dequeue", "Static Queue", (void *) staticQueue),
            ExceptionHandler_is_empty("StaticQueue_dequeue", "Data", (void *) staticQueue, StaticQueue_is_empty)
        )
    ) return;
    Array_remove_first(staticQueue->data);
}

void StaticQueue_print(const StaticQueue *staticQueue, void (*type_print_function)(void * data)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticQueue_print", "Static Queue", (void *) staticQueue),
            ExceptionHandler_is_empty("StaticQueue_print", "Data", (void *) staticQueue, StaticQueue_is_empty)
        )
    ) return;
    printf("\nCapacity: %ld. Top: %ld.\n", Array_capacity(staticQueue->data), Array_size(staticQueue->data) - 1);
    printf("--(");
    long size = Array_size(staticQueue->data);
    for(long i = 0; i < size - 1; i++) {
        type_print_function(Array_get_at(staticQueue->data, i));
        printf(", ");
    }
    type_print_function(Array_get_at(staticQueue->data, Array_size(staticQueue->data) - 1));
    puts(")--");
}

long StaticQueue_size(const StaticQueue *staticQueue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("StaticQueue_size", "Static Queue", (void *) staticQueue),
            ExceptionHandler_is_empty("StaticQueue_size", "Data", (void *) staticQueue, StaticQueue_is_empty)
        )
    ) return 0;
    return Array_size(staticQueue->data);
}