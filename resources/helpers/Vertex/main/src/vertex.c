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
    Vertex *vertex = (Vertex *) calloc(1, sizeof(Vertex));
    vertex->data = data;
    vertex->valency = 0;
    return vertex;
}

void Vertex_destroy(Vertex **vertex_ref) {
    Vertex *vertex = *vertex_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_destroy", "vertex", vertex, SUPPRESS_PRINT_ERROR)
        )
    ) return;

    free(vertex);
    *vertex_ref = NULL;
}

void *Vertex_get_data(Vertex *vertex) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_get_data", "vertex", vertex, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Vertex_get_data", "vertex.data", vertex->data, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;

    return vertex->data;
}

void Vertex_set_data(Vertex *vertex, void *new_data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_set_data", "vertex", vertex, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Vertex_set_data", "new_data", new_data, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    vertex->data = new_data;
}

long Vertex_get_valency(Vertex *vertex) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_get_valency", "vertex", vertex, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_non_positive("Vertex_get_valency", "vertex.valency", vertex->valency, true, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    return vertex->valency;
}

void Vertex_set_valency(Vertex *vertex, long new_valency) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_set_valency", "vertex", vertex, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_non_positive("Vertex_set_valency", "new_valency", new_valency, true, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    vertex->valency = new_valency;
}

void Vertex_valency_up(Vertex *vertex) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_valency_up", "vertex", vertex, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    vertex->valency++;
}

void Vertex_valency_down(Vertex *vertex) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_valency_down", "vertex", vertex, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_non_positive("Vertex_valency_down", "vertex.valency", vertex->valency, false, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    vertex->valency--;
}
