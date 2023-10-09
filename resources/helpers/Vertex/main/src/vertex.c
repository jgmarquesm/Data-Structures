#include <stdlib.h>
#include <stdbool.h>
//#--ADD_TO_INCLUDE
#include "../include/vertex.h"

typedef struct _vertex {
    void *data;
    long valency;
} Vertex;

const size_t size_of_vertex_type = sizeof(Vertex);

Vertex *Vertex_create(void *data) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_create", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Vertex *vertex = (Vertex *) calloc(1, size_of_vertex_type);
    vertex->data = data;
    vertex->valency = 0;
    return vertex;
}

bool Vertex_destroy(Vertex **vertex_ref) {
    Vertex *vertex = *vertex_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_destroy", "vertex", vertex, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    free(vertex);
    *vertex_ref = NULL;
    return __NOT_DEFAULT_BOOL__;
}

void *Vertex_get_data(Vertex *vertex) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_get_data", "Vertex", vertex, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_get_data", "Vertex::Data", vertex->data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;

    return vertex->data;
}

bool Vertex_set_data(Vertex *vertex, void *new_data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_set_data", "Vertex", vertex, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Vertex_set_data", "New Data", new_data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    vertex->data = new_data;
    return __NOT_DEFAULT_BOOL__;
}

long Vertex_get_valency(Vertex *vertex) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_get_valency", "Vertex", vertex, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_non_positive("Vertex_get_valency", "Vertex::Valency", vertex->valency, true, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;
    return vertex->valency;
}

long Vertex_set_valency(Vertex *vertex, long new_valency) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_set_valency", "Vertex", vertex, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Vertex_set_valency", "New Valency", new_valency, true, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;
    vertex->valency = new_valency;
    return new_valency;
}

bool Vertex_valency_up(Vertex *vertex) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_valency_up", "Vertex", vertex, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    vertex->valency++;
    return __NOT_DEFAULT_BOOL__;
}

bool Vertex_valency_down(Vertex *vertex) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_valency_down", "Vertex", vertex, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_non_positive("Vertex_valency_down", "Vertex::Valency", vertex->valency, false, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    vertex->valency--;
    return __NOT_DEFAULT_BOOL__;
}
