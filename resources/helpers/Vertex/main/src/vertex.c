#include "../include/vertex.h"
#include "../include/exception_handler.h"
#include <stdlib.h>
#include <stdbool.h>
//#--ADD_TO_INCLUDE

typedef struct _vertex {
    void *data;
    long valency;
} Vertex;

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
            ExceptionHandler_is_null("Vertex_destroy", "vertex", vertex)
        )
    ) return;

    free(vertex);
    *vertex_ref = NULL;
}

void *Vertex_get_data(Vertex *vertex) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_get_data", "vertex", vertex),
            ExceptionHandler_is_null("Vertex_get_data", "vertex.data", vertex->data)
        )
    ) return NULL;

    return vertex->data;
}

void Vertex_set_data(Vertex *vertex, void *new_data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_set_data", "vertex", vertex),
            ExceptionHandler_is_null("Vertex_set_data", "new_data", new_data)
        )
    ) return;
    vertex->data = new_data;
}

long Vertex_get_valency(Vertex *vertex) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_get_valency", "vertex", vertex),
            ExceptionHandler_is_non_positive("Vertex_get_valency", "vertex.valency", vertex->valency, true)
        )
    ) return -1;
    return vertex->valency;
}

void Vertex_set_valency(Vertex *vertex, long new_valency) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_set_valency", "vertex", vertex),
            ExceptionHandler_is_non_positive("Vertex_set_valency", "new_valency", new_valency, true)
        )
    ) return;
    vertex->valency = new_valency;
}

void Vertex_valency_up(Vertex *vertex) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Vertex_valency_up", "vertex", vertex)
        )
    ) return;
    vertex->valency++;
}

void Vertex_valency_down(Vertex *vertex) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Vertex_valency_down", "vertex", vertex),
            ExceptionHandler_is_non_positive("Vertex_valency_down", "vertex.valency", vertex->valency, false)
        )
    ) return;
    vertex->valency--;
}
