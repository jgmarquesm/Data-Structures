#include "../include/circular_doubly_linked_list.h"
#include "../include/edge.h"
//#--ADD_TO_INCLUDE
#include "../include/undirected_weighted_graph2.h"

typedef struct _undirected_weighted_graph2 {
    CircularDoublyLinkedList *vertices;
    Edge *edges;
    size_t size;
} UndirectedWeightedGraph2;

const size_t size_of_undirected_weighted_graph2_type = sizeof(UndirectedWeightedGraph2);

void _set_indexes_correctly(size_t *src_index, size_t src_vertex_idx, size_t *dest_index, size_t dest_vertex_idx) {
    if (src_vertex_idx < dest_vertex_idx) {
        *src_index = src_vertex_idx;
        *dest_index = dest_vertex_idx;
        return;
    }
    *src_index = dest_vertex_idx;
    *dest_index = src_vertex_idx;
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
    uwg->size = __DEFAULT_SIZE_T__;
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
    uwg->size++;
    return CircularDoublyLinkedList_add_first(uwg->vertices, vertex);
}

bool UndirectedWeightedGraph2_add_Edge(UndirectedWeightedGraph2 *uwg, size_t src_vertex_idx, size_t dest_vertex_idx, float weight) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph2_add_Edge", "Undirected Weighted Graph", uwg, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            2,
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_add_Edge", "Source Vertex", src_vertex_idx, uwg->size-1, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_add_Edge", "Destination Vertex", dest_vertex_idx, uwg->size-1, __SUPPRESS_PRINT_ERROR__)
        ) || src_vertex_idx == dest_vertex_idx
    ) return __DEFAULT_BOOL__;
    size_t src_index, dest_index;
    _set_indexes_correctly(&src_index, src_vertex_idx, &dest_index, dest_vertex_idx);
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

float UndirectedWeightedGraph2_edge_weight(UndirectedWeightedGraph2 *uwg, size_t src_vertex_idx, size_t dest_vertex_idx) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph2_edge_weight", "Undirected Weighted Graph", uwg, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
                2,
                ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_edge_weight", "Source Vertex", src_vertex_idx, uwg->size-1, __SUPPRESS_PRINT_ERROR__),
                ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_edge_weight", "Destination Vertex", dest_vertex_idx, uwg->size-1, __SUPPRESS_PRINT_ERROR__)
        ) || src_vertex_idx == dest_vertex_idx
    ) return __DEFAULT_FLOAT__;
    size_t src_index, dest_index;
    _set_indexes_correctly(&src_index, src_vertex_idx, &dest_index, dest_vertex_idx);
    Edge *edge = Edge_get_at(uwg->edges, src_index, dest_index);
    return Edge_get_weight(edge);
}