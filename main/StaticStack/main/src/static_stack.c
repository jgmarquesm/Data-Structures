#include "../include/static_stack.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/array.h"
//#--ADD_TO_INCLUDE

typedef struct _static_stack {
    Array *data;
} StaticStack;

StaticStack *StaticStack_create(const long capacity, unsigned int size_of_type) {
    StaticStack *SS = (StaticStack *) calloc(1, sizeof(StaticStack));
    SS->data = Array_create(capacity, size_of_type);
    return SS;
}

void StaticStack_clean(StaticStack *SS) {
    Array_clean(SS->data);
}

void StaticStack_destroy(StaticStack **SS_ref) {
    StaticStack *SS = *SS_ref;
    Array_delete(&(SS->data));
    free(SS);
    *SS_ref = NULL;
}

bool StaticStack_is_empty(const StaticStack *SS) {
    return Array_is_empty(SS->data);
}

bool StaticStack_is_full(const StaticStack *SS) {
    return Array_is_full(SS->data);
}

void StaticStack_push(StaticStack *SS, void *data) {
    if (StaticStack_is_full(SS)) {
        fprintf(stderr, "\nERROR: on function 'StaticStack_push'.\n");
        fprintf(stderr, "ERROR: StaticStack is full.\n");
        exit(EXIT_FAILURE);
    }

    Array_add_last(SS->data, data);
}

void *StaticStack_peek(const StaticStack *SS) {
    if (StaticStack_is_empty(SS)) {
        fprintf(stderr, "\nERROR: on function 'StaticStack_peek'.\n");
        fprintf(stderr, "ERROR: StaticStack is empty.\n");
        exit(EXIT_FAILURE);
    }
    long top = Array_size(SS->data) - 1;
    return Array_get_at(SS->data, top);
}

void StaticStack_pop(StaticStack *SS) {
    if (StaticStack_is_empty(SS)) {
        fprintf(stderr, "\nERROR: on function 'StaticStack_pop'.\n");
        fprintf(stderr, "ERROR: StaticStack is empty.\n");
        exit(EXIT_FAILURE);
    }
    Array_remove_last(SS->data);
}

void StaticStack_print(const StaticStack *SS, void (*type_print_function)(void * data)) {
    if (StaticStack_is_empty(SS)){
        fprintf(stderr, "\nERROR: on function 'StaticStack_print'.\n");
        fprintf(stderr, "ERROR: StaticStack is empty.\n");
        exit(EXIT_FAILURE);
    }
    printf("\nCapacity: %ld. Top: %ld.\n", Array_capacity(SS->data), Array_size(SS->data) - 1);
    printf("-:[");
    long size = Array_size(SS->data);
    for(long i = 0; i < size - 1; i++) {
        type_print_function(Array_get_at(SS->data, i));
        printf(", ");
    }
    type_print_function(Array_get_at(SS->data, Array_size(SS->data) - 1));
    puts("]:-");
}

long StaticStack_size(const StaticStack *SS) {
    return Array_size(SS->data);
}