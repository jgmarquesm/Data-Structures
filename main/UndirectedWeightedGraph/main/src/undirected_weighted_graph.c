#include <stdlib.h>
#include <stdio.h>
#include "../include/vertex.h"
#include "../include/matrix.h"
#include "../include/array.h"
//#--ADD_TO_INCLUDE
#include "../include/undirected_weighted_graph.h"

void _print_adjacency(void *value) {
    printf("%d", *((int *) value));
}

void _print_weight(void *value) {
    printf("%.2f", *((float *) value));
}

typedef struct _undirected_weighted_graph {
    long capacity;
    long size;
    Array *vertices;
    Matrix *adjacency_matrix;
    Matrix *weight_matrix;
} UndirectedWeightedGraph;

const size_t size_of_undirected_weighted_graph_type = sizeof(UndirectedWeightedGraph);

long _vertex_index(UndirectedWeightedGraph *uwg, void *data) {
    for (long i = 0; i < uwg->size; i++) {
        if (Vertex_get_data((Vertex *) Array_get_at(uwg->vertices, i)) == data) {
            return i;
        }
    }
    return __DEFAULT_LONG__;
}

Vertex *_vertex_get_at(UndirectedWeightedGraph *uwg, long index) {
    return (Vertex *) Array_get_at(uwg->vertices, index);
}

Vertex *_vertex_find(UndirectedWeightedGraph *uwg, void *data) {
    long index = _vertex_index(uwg, data);
    if (index != -1) {
        return _vertex_get_at(uwg, index);
    }
    return NULL;
}

Matrix *_initial_adjacency_matrix(long max_of_vertices) {
    int default_null_edge = __DEFAULT_NULL_EDGE_VALUE__;
    Matrix *adjacency_matrix = Matrix_create(max_of_vertices, max_of_vertices, sizeof(int), &default_null_edge);
    return adjacency_matrix;
}

Matrix *_initial_weight_matrix(long max_of_vertices) {
    float default_initial_weight = __DEFAULT_INITIAL_WEIGHT__;
    Matrix *weight_matrix = Matrix_create(max_of_vertices, max_of_vertices, sizeof(int), &default_initial_weight);
    return weight_matrix;
}

void _print_adjacency_matrix(UndirectedWeightedGraph *uwg) {
    puts("Adjacency Matrix:");
    Matrix_print(uwg->adjacency_matrix, _print_adjacency);
}

void _print_weight_matrix(UndirectedWeightedGraph *uwg) {
    puts("Weight Matrix:");
    Matrix_print(uwg->weight_matrix, _print_weight);
}

void _print_vertices(UndirectedWeightedGraph *uwg, __TYPE_PRINT_FUNCTION_SIGNATURE__) {
    printf("Vertices:\n[");
    if (UndirectedWeightedGraph_is_empty(uwg)) {
        puts("]");
    } else {
        for(long i = 0; i < uwg->size-1; i++) {
            __TYPE_PRINT_FUNCTION_NAME__(Vertex_get_data((Vertex *) Array_get_at(uwg->vertices, i)));
            printf(", ");
        }
        __TYPE_PRINT_FUNCTION_NAME__(Vertex_get_data((Vertex *) Array_get_at(uwg->vertices, uwg->size-1)));
        puts("]");
    }
}

bool _already_has_an_edge(UndirectedWeightedGraph *uwg, long exit_index, long entry_index) {
   return *((int *) Matrix_get_at(uwg->adjacency_matrix, exit_index, entry_index)) != __DEFAULT_NULL_EDGE_VALUE__;
}

void _set_value_to_matrices(UndirectedWeightedGraph *uwg, long exit_index, long entry_index, float weight, int edge_value) {
    if (exit_index == entry_index) {
        int edge = 2 * edge_value;
        Matrix_set_at(uwg->weight_matrix, entry_index, exit_index, &weight);
        Matrix_set_at(uwg->adjacency_matrix, exit_index, entry_index, &edge);
    } else {
        Matrix_set_at(uwg->weight_matrix, exit_index, entry_index, &weight);
        Matrix_set_at(uwg->weight_matrix, entry_index, exit_index, &weight);
        Matrix_set_at(uwg->adjacency_matrix, exit_index, entry_index, &edge_value);
        Matrix_set_at(uwg->adjacency_matrix, entry_index, exit_index, &edge_value);
    }
}

UndirectedWeightedGraph *UndirectedWeightedGraph_create(const long max_of_vertices) {
    if (anyThrows(
            1,
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph_create", "Max of vertices", max_of_vertices, false, __SUPPRESS_PRINT_ERROR__)
        )
    ) return NULL;

    UndirectedWeightedGraph *uwg = (UndirectedWeightedGraph *) calloc(1, size_of_undirected_weighted_graph_type);
    uwg->capacity = max_of_vertices;
    uwg->size = 0;

    Array *vertices = Array_create(max_of_vertices, SIZE_OF_VERTEX_TYPE);
    uwg->vertices = vertices;

    Matrix *adjacency_matrix = _initial_adjacency_matrix(max_of_vertices);
    uwg->adjacency_matrix = adjacency_matrix;

    Matrix *weight_matrix = _initial_weight_matrix(max_of_vertices);
    uwg->weight_matrix = weight_matrix;

    return uwg;
}

bool UndirectedWeightedGraph_clean(UndirectedWeightedGraph *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_clean", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Array_clean(uwg->vertices);
    Matrix_clean(uwg->adjacency_matrix);
    Matrix_clean(uwg->weight_matrix);
    uwg->size = 0;
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph_destroy(UndirectedWeightedGraph **uwg_ref) {
    UndirectedWeightedGraph *uwg = *uwg_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_clean", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Array_delete(&(uwg->vertices));
    Matrix_delete(&(uwg->adjacency_matrix));
    Matrix_delete(&(uwg->weight_matrix));
    free(uwg);
    *uwg_ref = NULL;
    return __NOT_DEFAULT_BOOL__;
}

long UndirectedWeightedGraph_index_of(UndirectedWeightedGraph *uwg, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("UndirectedWeightedGraph_index_of", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph_index_of", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_index_of", "Data", data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_index_of", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;
    return _vertex_index(uwg, data);
}

bool UndirectedWeightedGraph_is_empty(void *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_is_empty", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __NOT_DEFAULT_BOOL__;
    return ((UndirectedWeightedGraph *) uwg)->size == 0;
}

bool UndirectedWeightedGraph_is_full(void *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_is_full", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    return ((UndirectedWeightedGraph *) uwg)->size == ((UndirectedWeightedGraph *) uwg)->capacity;
}

bool UndirectedWeightedGraph_insert_vertex(UndirectedWeightedGraph *uwg, void *data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph_insert_vertex", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_insert_vertex", "Data", data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_full("UndirectedWeightedGraph_insert_vertex", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph_is_full, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_insert_vertex", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    if (_vertex_find(uwg, data)) return __DEFAULT_BOOL__;
    Array_insert_at(uwg->vertices, Vertex_create(data), uwg->size);
    uwg->size++;
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph_insert_edge(UndirectedWeightedGraph *uwg, void *exit_data, void *entry_data, float weight) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph_insert_edge", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph_insert_edge", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_insert_edge", "Exit Data", exit_data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_insert_edge", "Entry Data", entry_data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_insert_edge", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    long exit_index = UndirectedWeightedGraph_index_of(uwg, exit_data);
    long entry_index = UndirectedWeightedGraph_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph_insert_edge", "Exit index", exit_index, true, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph_insert_edge", "Entry index", entry_index, true, __SUPPRESS_PRINT_ERROR__)
        ) || _already_has_an_edge(uwg, exit_index, entry_index)
    ) return __DEFAULT_BOOL__;

    _set_value_to_matrices(uwg, exit_index, entry_index, weight, __DEFAULT_EDGE_VALUE__);
    Vertex_valency_up((Vertex *) Array_get_at(uwg->vertices, exit_index));
    Vertex_valency_up((Vertex *) Array_get_at(uwg->vertices, entry_index));
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph_change_weight(UndirectedWeightedGraph *uwg, void *exit_data, void *entry_data, float new_weight) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph_change_weight", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph_change_weight", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_change_weight", "Exit Data", exit_data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_change_weight", "Entry Data", entry_data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_change_weight", "Undirected Weighted Graph::Weight Matrix", (void *) uwg->weight_matrix, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    long exit_index = UndirectedWeightedGraph_index_of(uwg, exit_data);
    long entry_index = UndirectedWeightedGraph_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph_change_weight", "Exit index", exit_index, true, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph_change_weight", "Entry index", entry_index, true, __SUPPRESS_PRINT_ERROR__)
        ) || UndirectedWeightedGraph_get_weight(uwg, exit_data, entry_data) == __DEFAULT_INITIAL_WEIGHT__
    ) return __DEFAULT_BOOL__;

    Matrix_set_at(uwg->weight_matrix, exit_index, entry_index, &new_weight);
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph_change_data(UndirectedWeightedGraph *uwg, void *old_data, void *new_data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph_change_data", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph_change_data", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_change_data", "Exit Data", old_data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_change_data", "Entry Data", new_data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_change_data", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    Vertex *vertex = _vertex_find(uwg, old_data);
    if (!vertex) return __DEFAULT_BOOL__;
    Vertex_set_data(vertex, new_data);
    return __NOT_DEFAULT_BOOL__;
}

long UndirectedWeightedGraph_get_capacity(UndirectedWeightedGraph *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_capacity", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;
    return uwg->capacity;
}

long UndirectedWeightedGraph_get_size(UndirectedWeightedGraph *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_size", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;
    return uwg->size;
}

float UndirectedWeightedGraph_get_weight(UndirectedWeightedGraph *uwg, void *exit_data, void *entry_data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_weight", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph_get_weight", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_weight", "Exit Data", exit_data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_weight", "Entry Data", entry_data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_weight", "Undirected Weighted Graph::Weight Matrix", (void *) uwg->weight_matrix, __SUPPRESS_PRINT_ERROR__)
        )
    ) return 0;

    long exit_index = UndirectedWeightedGraph_index_of(uwg, exit_data);
    long entry_index = UndirectedWeightedGraph_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph_get_weight", "Exit index", exit_index, true, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph_get_weight", "Entry index", entry_index, true, __SUPPRESS_PRINT_ERROR__)
        )
    ) return 0;

    return *((float *) Matrix_get_at(uwg->weight_matrix, exit_index, entry_index));
}

void *UndirectedWeightedGraph_get_data(UndirectedWeightedGraph *uwg, long index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_data", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph_get_data", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph_is_empty, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            2,
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_data", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph_get_data", "Undirected Weighted Graph", index, uwg->size, __SUPPRESS_PRINT_ERROR__)
        )
    ) return NULL;
    return Vertex_get_data((Vertex *) Array_get_at(uwg->vertices, index));
}

long UndirectedWeightedGraph_get_valency(UndirectedWeightedGraph *uwg, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_valency", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph_get_valency", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_valency", "Data", data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_get_valency", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;

    Vertex *vertex = _vertex_find(uwg, data);
    if (!vertex) return __DEFAULT_LONG__;
    return Vertex_get_valency(vertex);
}

bool UndirectedWeightedGraph_remove_edge(UndirectedWeightedGraph *uwg, void *exit_data, void *entry_data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_edge", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph_remove_edge", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_edge", "Exit Data", exit_data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_edge", "Entry Data", entry_data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            3,
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_edge", "Undirected Weighted Graph::Weight Matrix", (void *) uwg->weight_matrix, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_edge", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_edge", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    long exit_index = UndirectedWeightedGraph_index_of(uwg, exit_data);
    long entry_index = UndirectedWeightedGraph_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph_remove_edge", "Exit index", exit_index, true, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph_remove_edge", "Entry index", entry_index, true, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    _set_value_to_matrices(uwg, exit_index, entry_index, __DEFAULT_INITIAL_WEIGHT__, __DEFAULT_NULL_EDGE_VALUE__);

    Vertex_valency_down((Vertex *) Array_get_at(uwg->vertices, exit_index));
    Vertex_valency_down((Vertex *) Array_get_at(uwg->vertices, entry_index));
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph_remove_vertex(UndirectedWeightedGraph *uwg, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_vertex", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph_remove_vertex", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_vertex", "Data", data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            3,
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_vertex", "Undirected Weighted Graph::Weight Matrix", (void *) uwg->weight_matrix, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_vertex", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_vertex", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    long index = _vertex_index(uwg, data);
    if (index < 0) return __DEFAULT_BOOL__;
    int default_null_edge_value = __DEFAULT_NULL_EDGE_VALUE__;
    float default_initial_weight = __DEFAULT_INITIAL_WEIGHT__;

    long size = uwg->size;
    if (index != size-1) {
        for (long i = 0; i < size; i++) {
            if (*((int *) Matrix_get_at(uwg->adjacency_matrix, index, i)) != default_null_edge_value) {
                Matrix_set_at(uwg->adjacency_matrix, index, i, &default_null_edge_value);
                Matrix_set_at(uwg->adjacency_matrix, i, index,  &default_null_edge_value);
                Matrix_set_at(uwg->weight_matrix, index, i, &default_initial_weight);
                Matrix_set_at(uwg->weight_matrix, i, index, &default_initial_weight);
                Vertex_valency_down((Vertex *) Array_get_at(uwg->vertices, i));
            }
            Matrix_set_at(uwg->adjacency_matrix, size-1, i, &default_null_edge_value);
            Matrix_set_at(uwg->adjacency_matrix, i, size-1,  &default_null_edge_value);
            Matrix_set_at(uwg->weight_matrix, size-1, i, &default_initial_weight);
            Matrix_set_at(uwg->weight_matrix, i, size-1, &default_initial_weight);
        }
        for (long i = index; i < size-1; i++) {
            Array_set(uwg->vertices, (Vertex *) Array_get_at(uwg->vertices, i + 1), i);
            for (long j = index; j < size-1; j++) {
                Matrix_set_at(uwg->adjacency_matrix, i, j, Matrix_get_at(uwg->adjacency_matrix, i + 1, j + 1));
                Matrix_set_at(uwg->weight_matrix, i, j, Matrix_get_at(uwg->weight_matrix, i + 1, j + 1));
            }
        }
    } else {
        for (long i = 0; i < size; i++) {
            if (*((int *) Matrix_get_at(uwg->adjacency_matrix, index, i)) != default_null_edge_value) {
                Vertex_valency_down((Vertex *) Array_get_at(uwg->vertices, i));
            }
        }
        Matrix_set_at(uwg->adjacency_matrix, index, index, &default_null_edge_value);
        Matrix_set_at(uwg->weight_matrix, index, index, &default_initial_weight);
    }
    uwg->size--;
    return __NOT_DEFAULT_BOOL__;
}

void UndirectedWeightedGraph_print_full_graph(UndirectedWeightedGraph *uwg, __TYPE_PRINT_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_vertex", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            3,
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_vertex", "Undirected Weighted Graph::Weight Matrix", (void *) uwg->weight_matrix, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_vertex", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph_remove_vertex", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return;
    _print_adjacency_matrix(uwg);
    _print_weight_matrix(uwg);
    _print_vertices(uwg, __TYPE_PRINT_FUNCTION_NAME__);
}
