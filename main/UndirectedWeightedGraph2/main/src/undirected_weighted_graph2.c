#include "../include/circular_doubly_linked_list.h"
#include "../include/edge.h"
//#--ADD_TO_INCLUDE
#include "../include/undirected_weighted_graph2.h"

typedef struct _undirected_weighted_graph2 {
    CircularDoublyLinkedList *vertices;
    Edge *edges;
} UndirectedWeightedGraph2;

const size_t size_of_undirected_weighted_graph2_type = sizeof(UndirectedWeightedGraph2);

void _set_indexes_correctly(size_t *src_index, size_t source_vertex_index, size_t *dest_index, size_t destination_vertex_index) {
    if (source_vertex_index < destination_vertex_index) {
        *src_index = source_vertex_index;
        *dest_index = destination_vertex_index;
        return;
    }
    *src_index = destination_vertex_index;
    *dest_index = source_vertex_index;
}

ExceptionResponse *UndirectedWeightedGraph2_already_has_edge(char *function, bool already_added, bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (already_added) {
        throws = true;
        error_message = ExceptionHandler_build_error_message(function, "Edge", " already added.\n");
    }
    return ExceptionHandler_create(throws, error_message, suppress);
}

UndirectedWeightedGraph2 *UndirectedWeightedGraph2_create() {
    UndirectedWeightedGraph2 *uwg = (UndirectedWeightedGraph2 *) calloc(1, size_of_undirected_weighted_graph2_type);
    uwg->vertices = CircularDoublyLinkedList_create();
    uwg->edges = __DEFAULT_PTR__;
    return uwg;
}

bool UndirectedWeightedGraph2_insert_Vertex(UndirectedWeightedGraph2 *uwg, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("UndirectedWeightedGraph2_add_Vertex", "Undirected Weighted Graph", uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph2_add_Vertex", "Data", data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph2_add_Vertex", "Undirected Weighted Graph::Vertices", uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    CircularDoublyLinkedList *vertex = CircularDoublyLinkedList_create();
    CircularDoublyLinkedList_add_first(vertex, data);
    return CircularDoublyLinkedList_add_first(uwg->vertices, vertex);
}

bool UndirectedWeightedGraph2_add_Edge(UndirectedWeightedGraph2 *uwg, size_t source_vertex_index, size_t destination_vertex_index, float weight) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph2_add_Edge", "Undirected Weighted Graph", uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    size_t max_index = CircularDoublyLinkedList_size(uwg->vertices) - 1;
    if (anyThrows(
            2,
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_add_Edge", "Source Vertex", source_vertex_index, max_index, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_add_Edge", "Destination Vertex", destination_vertex_index, max_index, __SUPPRESS_PRINT_ERROR__)
        ) || source_vertex_index == destination_vertex_index
    ) return __DEFAULT_BOOL__;
    size_t src_index, dest_index;
    _set_indexes_correctly(&src_index, source_vertex_index, &dest_index, destination_vertex_index);
    bool already_added = Edge_exists(uwg->edges, src_index, dest_index);
    if (anyThrows(
            1,
            UndirectedWeightedGraph2_already_has_edge("UndirectedWeightedGraph2_add_Edge", already_added, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    if (uwg->edges == __DEFAULT_PTR__) {
        uwg->edges = Edge_create(src_index, dest_index, weight);
        return __NOT_DEFAULT_BOOL__;
    } else return Edge_add(uwg->edges, src_index, dest_index, weight);
}

float UndirectedWeightedGraph2_get_weight(UndirectedWeightedGraph2 *uwg, size_t source_vertex_index, size_t destination_vertex_index) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph2_get_weight", "Undirected Weighted Graph", uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_FLOAT__;
    size_t max_index = CircularDoublyLinkedList_size(uwg->vertices) - 1;
    if (anyThrows(
            2,
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_get_weight", "Source Vertex", source_vertex_index, max_index, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_get_weight", "Destination Vertex", destination_vertex_index, max_index, __SUPPRESS_PRINT_ERROR__)
        ) || source_vertex_index == destination_vertex_index
    ) return __DEFAULT_FLOAT__;
    size_t src_index, dest_index;
    _set_indexes_correctly(&src_index, source_vertex_index, &dest_index, destination_vertex_index);
    Edge *edge = Edge_get_at(uwg->edges, src_index, dest_index);
    return Edge_get_weight(edge);
}

bool UndirectedWeightedGraph2_set_weight(UndirectedWeightedGraph2 *uwg, size_t source_vertex_index, size_t destination_vertex_index, float new_weight) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph2_set_weight", "Undirected Weighted Graph", uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    size_t max_index = CircularDoublyLinkedList_size(uwg->vertices) - 1;
    if (anyThrows(
            2,
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_set_weight", "Source Vertex", source_vertex_index, max_index, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_set_weight", "Destination Vertex", destination_vertex_index, max_index, __SUPPRESS_PRINT_ERROR__)
        ) || source_vertex_index == destination_vertex_index
    ) return __DEFAULT_BOOL__;
    size_t src_index, dest_index;
    _set_indexes_correctly(&src_index, source_vertex_index, &dest_index, destination_vertex_index);
    Edge *edge = Edge_get_at(uwg->edges, src_index, dest_index);
    return Edge_set_weight(edge, new_weight);
}

bool UndirectedWeightedGraph2_is_empty(void *uwg) {
    return CircularDoublyLinkedList_is_empty(((UndirectedWeightedGraph2 *) uwg)->vertices);
}

bool UndirectedWeightedGraph2_remove_Vertex(UndirectedWeightedGraph2 *uwg, size_t vertex_index) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph2_remove_Vertex", "Undirected Weighted Graph", uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    size_t max_index = CircularDoublyLinkedList_size(uwg->vertices) - 1;
    if (anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_remove_Vertex", "Vertex index", vertex_index, max_index, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    if (Edge_remove_edges_with_index(uwg->edges, vertex_index)) return CircularDoublyLinkedList_remove_at(uwg->vertices, vertex_index);
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph2_remove_Edge(UndirectedWeightedGraph2 *uwg, size_t source_vertex_index, size_t destination_vertex_index) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph2_remove_Edge", "Undirected Weighted Graph", uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    size_t max_index = CircularDoublyLinkedList_size(uwg->vertices) - 1;
    if (anyThrows(
            2,
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_remove_Edge", "Source Vertex", source_vertex_index, max_index, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_remove_Edge", "Destination Vertex", destination_vertex_index, max_index, __SUPPRESS_PRINT_ERROR__)
        ) || source_vertex_index == destination_vertex_index
    ) return __DEFAULT_BOOL__;
    size_t src_index, dest_index;
    _set_indexes_correctly(&src_index, source_vertex_index, &dest_index, destination_vertex_index);
    return Edge_remove_at(uwg->edges, src_index, dest_index);
}
