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

bool UndirectedWeightedGraph2_add_Edge(UndirectedWeightedGraph2 *uwg, size_t src_vertex, size_t dest_vertex, float weight) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph2_add_Edge", "Undirected Weighted Graph", uwg, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            2,
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_add_Edge", "Source Vertex", src_vertex, uwg->size, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph2_add_Edge", "Destination Vertex", dest_vertex, uwg->size, __SUPPRESS_PRINT_ERROR__)
        ) || src_vertex == dest_vertex
    ) return __DEFAULT_BOOL__;

    if (uwg->edges == __DEFAULT_PTR__) {
        uwg->edges = Edge_create(src_vertex, dest_vertex, weight);
        return __NOT_DEFAULT_BOOL__;
    }
    else return Edge_add(uwg->edges, src_vertex, dest_vertex, weight);
}
