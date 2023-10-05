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
            ExceptionHandler_is_null("Vertex_create", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Vertex *vertex = (Vertex *) calloc(1, sizeof(Vertex));
    vertex->data = data;
    vertex->valency = 0;
    return vertex;
}

bool Vertex_destroy(Vertex **vertex_ref) {
    Vertex *vertex = *vertex_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_destroy", "vertex", vertex, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    free(vertex);
    *vertex_ref = NULL;
    return true;
}

void *Vertex_get_data(Vertex *vertex) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_get_data", "Vertex", vertex, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_get_data", "Vertex::Data", vertex->data, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;

    return vertex->data;
}

bool Vertex_set_data(Vertex *vertex, void *new_data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_set_data", "Vertex", vertex, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Vertex_set_data", "New Data", new_data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    vertex->data = new_data;
    return true;
}

long Vertex_get_valency(Vertex *vertex) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_get_valency", "Vertex", vertex, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_non_positive("Vertex_get_valency", "Vertex::Valency", vertex->valency, true, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    return vertex->valency;
}

long Vertex_set_valency(Vertex *vertex, long new_valency) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_set_valency", "Vertex", vertex, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_non_positive("Vertex_set_valency", "New Valency", new_valency, true, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    vertex->valency = new_valency;
    return new_valency;
}

bool Vertex_valency_up(Vertex *vertex) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_valency_up", "Vertex", vertex, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    vertex->valency++;
    return true;
}

bool Vertex_valency_down(Vertex *vertex) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_valency_down", "Vertex", vertex, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_non_positive("Vertex_valency_down", "Vertex::Valency", vertex->valency, false, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    vertex->valency--;
    return true;
}
