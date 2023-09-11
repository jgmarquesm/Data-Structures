#include "../include/static_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/array.h"
#include "../include/exception_handler.h"
//#--ADD_TO_INCLUDE

typedef struct _static_queue {
    Array *data;
} StaticQueue;

StaticQueue *StaticQueue_create(const long capacity, unsigned int size_of_type) {
    StaticQueue *SQ = (StaticQueue *) calloc(1, sizeof(StaticQueue));
    SQ->data = Array_create(capacity, size_of_type);
    return SQ;
}

void StaticQueue_clean(StaticQueue *SQ) {
    Array_clean(SQ->data);
}

void StaticQueue_destroy(StaticQueue **SQ_ref) {
    StaticQueue *SQ = *SQ_ref;
    Array_delete(&(SQ->data));
    free(SQ);
    *SQ_ref = NULL;
}

bool StaticQueue_is_empty(const StaticQueue *SQ) {
    return Array_is_empty(SQ->data);
}

bool StaticQueue_is_full(const StaticQueue *SQ) {
    return Array_is_full(SQ->data);
}

void StaticQueue_enqueue(StaticQueue *SQ, void *data) {
    if (StaticQueue_is_full(SQ)) {
        fprintf(stderr, "\nERROR: on function 'StaticQueue_push'.\n");
        fprintf(stderr, "ERROR: Static Queue is full.\n");
        exit(EXIT_FAILURE);
    }

    Array_add_last(SQ->data, data);
}

void *StaticQueue_peek(const StaticQueue *SQ) {
    if (StaticQueue_is_empty(SQ)) {
        fprintf(stderr, "\nERROR: on function 'StaticQueue_peek'.\n");
        fprintf(stderr, "ERROR: Static Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    return Array_get_at(SQ->data, 0);
}

void StaticQueue_dequeue(StaticQueue *SQ) {
    if (StaticQueue_is_empty(SQ)) {
        fprintf(stderr, "\nERROR: on function 'StaticQueue_pop'.\n");
        fprintf(stderr, "ERROR: Static Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    Array_remove_first(SQ->data);
}

void StaticQueue_print(const StaticQueue *SQ, void (*type_print_function)(void * data)) {
    if (StaticQueue_is_empty(SQ)){
        fprintf(stderr, "\nERROR: on function 'StaticQueue_print'.\n");
        fprintf(stderr, "ERROR: Static Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    printf("\nCapacity: %ld. Top: %ld.\n", Array_capacity(SQ->data), Array_size(SQ->data) - 1);
    printf("--(");
    long size = Array_size(SQ->data);
    for(long i = 0; i < size - 1; i++) {
        type_print_function(Array_get_at(SQ->data, i));
        printf(", ");
    }
    type_print_function(Array_get_at(SQ->data, Array_size(SQ->data) - 1));
    puts(")--");
}

long StaticQueue_size(const StaticQueue *SQ) {
    return Array_size(SQ->data);
}