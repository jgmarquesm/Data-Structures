#include <stdlib.h>
#include <stdio.h>
//#--ADD_TO_INCLUDE
#include "../include/edge.h"

typedef struct _edge {
    size_t source_index;
    size_t destination_index;
    float weight;
    struct _edge *next;
    struct _edge *prev;
} Edge;

const size_t size_of_edge_type = sizeof(Edge);

Edge *Edge_create(size_t src_index, size_t dest_index, float weight) {
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("Edge_create", "Source Index", src_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_create", "Destination Index", dest_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Edge *edge = (Edge *) calloc(1, size_of_edge_type);
    edge->source_index = src_index;
    edge->destination_index = dest_index;
    edge->weight = weight;
    edge->next = __DEFAULT_PTR__;
    edge->prev = __DEFAULT_PTR__;
    return edge;
}

bool Edge_add(Edge *edge, size_t src_index, size_t dest_index, float weight) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Edge_add", "Edge", edge, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_add", "Source Index", src_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_add", "Destination Index", dest_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Edge *next = Edge_create(src_index, dest_index, weight);
    next->prev = edge;
    Edge *temp_edge = edge;
    while (temp_edge->next != __DEFAULT_PTR__) {
        temp_edge = temp_edge->next;
    }
    temp_edge->next = next;
    return __NOT_DEFAULT_BOOL__;
}

Edge *Edge_get_at(Edge *edge, size_t src_index, size_t dest_index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Edge_get_at", "Edge", edge, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_get_at", "Source Index", src_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_get_at", "Destination Index", dest_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Edge *temp_edge = edge;
    while (temp_edge != __DEFAULT_PTR__) {
        if (temp_edge->source_index == src_index && temp_edge->destination_index == dest_index) {
            return temp_edge;
        }
        temp_edge = temp_edge->next;
    }
    return __DEFAULT_PTR__;
}

float Edge_get_weight(Edge *edge) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Edge_get_weight", "Edge", edge, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_FLOAT__;
    return edge->weight;
}

bool Edge_set_weight(Edge *edge, float new_weight) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Edge_set_weight", "Edge", edge, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    edge->weight = new_weight;
    return edge->weight == new_weight;
}

bool Edge_exists(Edge *edge, size_t src_index, size_t dest_index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Edge_exists", "Edge", edge, __NOT_DEFAULT_BOOL__),
            ExceptionHandler_is_non_positive("Edge_exists", "Source Index", src_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_exists", "Destination Index", dest_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Edge *temp_edge = edge;
    while (temp_edge != __DEFAULT_PTR__) {
        if (temp_edge->source_index == src_index && temp_edge->destination_index == dest_index) {
            return __NOT_DEFAULT_BOOL__;
        }
        temp_edge = temp_edge->next;
    }
    return __DEFAULT_BOOL__;
}

bool Edge_remove(Edge *edge) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Edge_remove", "Edge", edge, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    if (edge->prev != __DEFAULT_PTR__) edge->prev->next = edge->next;
    if (edge->next != __DEFAULT_PTR__) edge->next->prev = edge->prev;
    free(edge);
    return __NOT_DEFAULT_BOOL__;
}

bool Edge_remove_at(Edge *edge, size_t src_index, size_t dest_index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Edge_remove_at", "Edge", edge, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_remove_at", "Source Index", src_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_remove_at", "Destination Index", dest_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Edge *edge_to_remove = Edge_get_at(edge, src_index, dest_index);
    return Edge_remove(edge_to_remove);
}

bool Edge_remove_edges_with_index(Edge *edge, size_t vertex_index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Edge_remove_edges_with_index", "Edge", edge, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_remove_edges_with_index", "Vertex index", vertex_index, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Edge *temp_edge = edge;
    while (temp_edge != __DEFAULT_BOOL__) {
        if (temp_edge->source_index == vertex_index || temp_edge->destination_index == vertex_index) {
            if (!Edge_remove(temp_edge)) return __DEFAULT_BOOL__;
        }
        temp_edge = temp_edge->next;
    }
    return __NOT_DEFAULT_BOOL__;
}
