#include <stdlib.h>
#include <stdio.h>
#include "../include/full_vertex.h"
//#--ADD_TO_INCLUDE
#include "../include/edge.h"

typedef struct _edge {
    FullVertex *source_vertex;
    FullVertex *destination_vertex;
    float weight;
    struct _edge *next;
    struct _edge *prev;
} Edge;

const size_t size_of_edge_type = sizeof(Edge);

Edge *Edge_create(void *src_full_vertex_ref, void *dest_full_vertex_ref, float weight) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Edge_create", "Source Index", src_full_vertex_ref, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Edge_create", "Destination Index", dest_full_vertex_ref, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Edge *edge = (Edge *) calloc(1, size_of_edge_type);
    edge->source_vertex = to_FullVertex(src_full_vertex_ref);
    edge->destination_vertex = to_FullVertex(dest_full_vertex_ref);
    edge->weight = weight;
    edge->next = __DEFAULT_PTR__;
    edge->prev = __DEFAULT_PTR__;
    return edge;
}

bool Edge_add(Edge *edge, void *src_full_vertex_ref, void *dest_full_vertex_ref, float weight) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Edge_add", "Edge", edge, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Edge_add", "Source Index", src_full_vertex_ref, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Edge_add", "Destination Index", dest_full_vertex_ref, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Edge *next = Edge_create(src_full_vertex_ref, dest_full_vertex_ref, weight);
    next->prev = edge;
    Edge *temp_edge = edge;
    while (temp_edge->next != __DEFAULT_PTR__) {
        temp_edge = temp_edge->next;
    }
    temp_edge->next = next;
    return __NOT_DEFAULT_BOOL__;
}

Edge *Edge_get(Edge *edge, void *src_full_vertex_ref, void *dest_full_vertex_ref) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Edge_get_at", "Edge", edge, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Edge_get_at", "Source Index", src_full_vertex_ref, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Edge_get_at", "Destination Index", dest_full_vertex_ref, __SUPPRESS_PRINT_ERROR__)
    )
            ) return __DEFAULT_PTR__;
    Edge *temp_edge = edge;
    FullVertex *src_full_vertex = to_FullVertex(src_full_vertex_ref);
    FullVertex *dest_full_vertex = to_FullVertex(dest_full_vertex_ref);
    while (temp_edge != __DEFAULT_PTR__) {
        if (
                FullVertex_is_equals(temp_edge->source_vertex, src_full_vertex)
                && FullVertex_is_equals(temp_edge->destination_vertex, dest_full_vertex)
        ) return temp_edge;
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

bool Edge_exists(Edge *edge, void *src_full_vertex_ref, void *dest_full_vertex_ref) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Edge_exists", "Edge", edge, __NOT_DEFAULT_BOOL__),
            ExceptionHandler_is_null("Edge_exists", "Source Index", src_full_vertex_ref, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Edge_exists", "Destination Index", dest_full_vertex_ref, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Edge *temp_edge = edge;
    FullVertex *src_full_vertex = to_FullVertex(src_full_vertex_ref);
    FullVertex *dest_full_vertex = to_FullVertex(dest_full_vertex_ref);
    while (temp_edge != __DEFAULT_PTR__) {
        if (
                FullVertex_is_equals(temp_edge->source_vertex, src_full_vertex)
                && FullVertex_is_equals(temp_edge->destination_vertex, dest_full_vertex)
        ) return __NOT_DEFAULT_BOOL__;
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

bool Edge_remove_between(Edge *edge, void *src_full_vertex_ref, void *dest_full_vertex_ref) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Edge_remove_between", "Edge", edge, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Edge_remove_between", "Source Index", src_full_vertex_ref, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Edge_remove_between", "Destination Index", dest_full_vertex_ref, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Edge *edge_to_remove = Edge_get(edge, src_full_vertex_ref, dest_full_vertex_ref);
    return Edge_remove(edge_to_remove);
}

bool Edge_remove_edges_from_vertex(Edge *edge, void *full_vertex_ref) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Edge_remove_edges_with_index", "Edge", edge, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Edge_remove_edges_with_index", "Vertex index", full_vertex_ref, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Edge *temp_edge = edge;
    FullVertex *full_vertex = to_FullVertex(full_vertex_ref);
    while (temp_edge != __DEFAULT_BOOL__) {
        if (
                FullVertex_is_equals(temp_edge->source_vertex, full_vertex)
                || FullVertex_is_equals(temp_edge->destination_vertex, full_vertex)
        ) {
            if (!Edge_remove(temp_edge)) return __DEFAULT_BOOL__;
        }
        temp_edge = temp_edge->next;
    }
    return __NOT_DEFAULT_BOOL__;
}