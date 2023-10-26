#include "../include/vertex.h"
#include "../include/edge.h"
//#--ADD_TO_INCLUDE
#include "../include/full_vertex.h"

typedef struct _full_vertex {
    Vertex *vertex;
    Edge *edges;
    struct _full_vertex *next;
    struct _full_vertex *prev;
} FullVertex;

const size_t size_of_full_vertex_type = sizeof(FullVertex);

FullVertex *to_FullVertex(void *full_vertex_address) {
    return (FullVertex *) full_vertex_address;
}

bool FullVertex_is_equals(FullVertex *full_vertex1, FullVertex *full_vertex2) {
    return full_vertex1 == full_vertex2;
}
