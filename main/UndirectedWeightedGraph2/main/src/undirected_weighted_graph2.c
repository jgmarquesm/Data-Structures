#include "../include/full_vertex.h"
//#--ADD_TO_INCLUDE
#include "../include/undirected_weighted_graph2.h"

typedef struct _undirected_weighted_graph2 {
    FullVertex *vertices;
} UndirectedWeightedGraph2;

const size_t size_of_undirected_weighted_graph2_type = sizeof(UndirectedWeightedGraph2);
