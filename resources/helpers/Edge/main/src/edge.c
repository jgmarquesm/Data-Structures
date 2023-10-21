//#--ADD_TO_INCLUDE
#include "../include/edge.h"

typedef struct _edge {
    size_t source_index;
    size_t destination_index;
    float weight;
    struct _edge *next;
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

bool Edge_exists(Edge *edge, size_t src_index, size_t dest_index) {
    if (edge == NULL
        || anyThrows(
            2,
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

Edge *Edge_get_next(Edge *edge) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Edge_get_next", "Edge", edge, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return edge->next;
}