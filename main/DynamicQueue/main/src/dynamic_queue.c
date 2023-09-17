#include "../include/dynamic_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/doubly_linked_list.h"
//#--ADD_TO_INCLUDE

typedef struct _dynamic_queue {
    LinkedList *data;
} Queue;

Queue *Queue_create() {
    Queue *S = (Queue *) calloc(1, sizeof(Queue));
    S->data = LinkedList_create();
    return S;
}

void Queue_clean(Queue *queue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Queue_clean", "Queue", (void *) queue)
        )
    ) return;
    LinkedList_clean(queue->data);
}

void Queue_destroy(Queue **queue_ref) {
    Queue *queue = *queue_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Queue_destroy", "Queue", (void *) queue)
        )
    ) return;
    LinkedList_destroy(&(queue->data));
    free(queue);
    *queue_ref = NULL;
}

bool Queue_is_empty(void *queue) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Queue_is_empty", "Queue", (void *) queue)
        )
    ) return true;
    return LinkedList_is_empty(((Queue *) queue)->data);
}

void Queue_enqueue(Queue *queue, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Queue_enqueue", "Queue", (void *) queue),
            ExceptionHandler_is_null("Queue_enqueue", "Data", data)
        )
    ) return;
    LinkedList_add_last(queue->data, data);
}

void *Queue_peek(const Queue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Queue_peek", "Queue", (void *) queue),
            ExceptionHandler_is_empty("Queue_peek", "Queue", (void *) queue, Queue_is_empty)
        )
    ) return NULL;
    return LinkedList_get(queue->data, 0);
}

void Queue_dequeue(Queue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Queue_dequeue", "Queue", (void *) queue),
            ExceptionHandler_is_empty("Queue_dequeue", "Queue", (void *) queue, Queue_is_empty)
        )
    ) return;
    LinkedList_remove_first(queue->data);
}

void Queue_print(const Queue *queue, void (*type_print_function)(void * data)) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Queue_print", "Queue", (void *) queue),
            ExceptionHandler_is_empty("Queue_print", "Queue", (void *) queue, Queue_is_empty)
        )
    ) return;
    printf("--(");
    size_t size = LinkedList_size(queue->data);
    for(size_t i = 0; i < size - 1; i++) {
        type_print_function(LinkedList_get(queue->data, i));
        printf(" -> ");
    }
    type_print_function(LinkedList_get(queue->data, LinkedList_size(queue->data) - 1));
    puts(")--");
}

size_t Queue_size(const Queue *queue) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Queue_size", "Queue", (void *) queue),
            ExceptionHandler_is_empty("Queue_size", "Queue", (void *) queue, Queue_is_empty)
        )
    ) return 0;
    return LinkedList_size(queue->data);
}