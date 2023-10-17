//#--ADD_TO_INCLUDE
#include "../include/edge.h"

typedef struct _edge {
    size_t source_index;
    size_t destination_index;
    float weight;
    struct _edge *next;
} Edge;

const size_t size_of_edge_type = sizeof(Edge);

Edge *Edge_create(size_t src_vertex, size_t dest_vertex, float weight) {
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("Edge_create", "Source Index", src_vertex, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_create", "Destination Index", dest_vertex, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Edge *edge = (Edge *) calloc(1, size_of_edge_type);
    edge->source_index = src_vertex;
    edge->destination_index = dest_vertex;
    edge->weight = weight;
    edge->next = __DEFAULT_PTR__;
    return edge;
}

bool Edge_add(Edge *edge, size_t src_vertex, size_t dest_vertex, float weight) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Edge_add", "Edge", edge, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_add", "Source Index", src_vertex, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("Edge_add", "Destination Index", dest_vertex, __NOT_DEFAULT_BOOL__, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Edge *next = Edge_create(src_vertex, dest_vertex, weight);
    edge->next = next;
    return true;
}