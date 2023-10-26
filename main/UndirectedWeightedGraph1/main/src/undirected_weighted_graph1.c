#include <stdlib.h>
#include <stdio.h>
#include "../include/vertex.h"
#include "../include/matrix.h"
#include "../include/array.h"
//#--ADD_TO_INCLUDE
#include "../include/undirected_weighted_graph1.h"

void _print_adjacency(void *value) {
    printf("%.2f", *((float *) value));
}

typedef struct _undirected_weighted_graph1 {
    long capacity;
    long size;
    Array *vertices;
    Matrix *adjacency_matrix;
} UndirectedWeightedGraph1;

const size_t size_of_undirected_weighted_graph1_type = sizeof(UndirectedWeightedGraph1);

long _vertex_index(UndirectedWeightedGraph1 *uwg, void *data) {
    for (long i = 0; i < uwg->size; i++) {
        if (Vertex_get_data((Vertex *) Array_get_at(uwg->vertices, i)) == data) {
            return i;
        }
    }
    return __DEFAULT_LONG__;
}

Vertex *_vertex_get_at(UndirectedWeightedGraph1 *uwg, long index) {
    return (Vertex *) Array_get_at(uwg->vertices, index);
}

Vertex *_vertex_find(UndirectedWeightedGraph1 *uwg, void *data) {
    long index = _vertex_index(uwg, data);
    if (index != -1) {
        return _vertex_get_at(uwg, index);
    }
    return NULL;
}

Matrix *_initial_adjacency_matrix(long max_of_vertices) {
    float default_initial_weight = __DEFAULT_INITIAL_WEIGHT__;
    Matrix *adjacency_matrix = Matrix_create(max_of_vertices, max_of_vertices, sizeof(int), &default_initial_weight);
    return adjacency_matrix;
}

void _print_adjacency_matrix(UndirectedWeightedGraph1 *uwg) {
    puts("Adjacency Matrix:");
    Matrix_print(uwg->adjacency_matrix, _print_adjacency);
}

void _print_vertices(UndirectedWeightedGraph1 *uwg, __TYPE_PRINT_FUNCTION_SIGNATURE__) {
    printf("Vertices:\n[");
    if (UndirectedWeightedGraph1_is_empty(uwg)) {
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

bool _already_has_an_edge(UndirectedWeightedGraph1 *uwg, long exit_index, long entry_index) {
   return *((int *) Matrix_get_at(uwg->adjacency_matrix, exit_index, entry_index)) != __DEFAULT_INITIAL_WEIGHT__;
}

void _set_value_to_matrices(UndirectedWeightedGraph1 *uwg, long exit_index, long entry_index, float weight) {
    if (exit_index == entry_index) {
        float weight_value = 2 * weight;
        Matrix_set_at(uwg->adjacency_matrix, entry_index, exit_index, &weight_value);
    } else {
        Matrix_set_at(uwg->adjacency_matrix, exit_index, entry_index, &weight);
        Matrix_set_at(uwg->adjacency_matrix, entry_index, exit_index, &weight);
    }
}

UndirectedWeightedGraph1 *UndirectedWeightedGraph1_create(const long max_of_vertices) {
    if (anyThrows(
            1,
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph1_create", "Max of vertices", max_of_vertices, false, __SUPPRESS_PRINT_ERROR__)
        )
    ) return NULL;

    UndirectedWeightedGraph1 *uwg = (UndirectedWeightedGraph1 *) calloc(1, size_of_undirected_weighted_graph1_type);
    uwg->capacity = max_of_vertices;
    uwg->size = 0;

    Array *vertices = Array_create(max_of_vertices, SIZE_OF_VERTEX_TYPE);
    uwg->vertices = vertices;

    Matrix *adjacency_matrix = _initial_adjacency_matrix(max_of_vertices);
    uwg->adjacency_matrix = adjacency_matrix;

    return uwg;
}

bool UndirectedWeightedGraph1_clean(UndirectedWeightedGraph1 *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_clean", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Array_clean(uwg->vertices);
    Matrix_clean(uwg->adjacency_matrix);
    uwg->size = 0;
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph1_destroy(UndirectedWeightedGraph1 **uwg_ref) {
    UndirectedWeightedGraph1 *uwg = *uwg_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_clean", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Array_delete(&(uwg->vertices));
    Matrix_delete(&(uwg->adjacency_matrix));
    free(uwg);
    *uwg_ref = NULL;
    return __NOT_DEFAULT_BOOL__;
}

long UndirectedWeightedGraph1_index_of(UndirectedWeightedGraph1 *uwg, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_index_of", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph1_index_of", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph1_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_index_of", "Data", data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_index_of", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;
    return _vertex_index(uwg, data);
}

bool UndirectedWeightedGraph1_is_empty(void *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_is_empty", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __NOT_DEFAULT_BOOL__;
    return ((UndirectedWeightedGraph1 *) uwg)->size == 0;
}

bool UndirectedWeightedGraph1_is_full(void *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_is_full", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    return ((UndirectedWeightedGraph1 *) uwg)->size == ((UndirectedWeightedGraph1 *) uwg)->capacity;
}

bool UndirectedWeightedGraph1_insert_vertex(UndirectedWeightedGraph1 *uwg, void *data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_insert_vertex", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_insert_vertex", "Data", data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_full("UndirectedWeightedGraph1_insert_vertex", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph1_is_full, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_insert_vertex", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    if (_vertex_find(uwg, data)) return __DEFAULT_BOOL__;
    Array_insert_at(uwg->vertices, Vertex_create(data), uwg->size);
    uwg->size++;
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph1_insert_edge(UndirectedWeightedGraph1 *uwg, void *exit_data, void *entry_data, float weight) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_insert_edge", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph1_insert_edge", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph1_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_insert_edge", "Exit Data", exit_data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_insert_edge", "Entry Data", entry_data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_insert_edge", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    long exit_index = UndirectedWeightedGraph1_index_of(uwg, exit_data);
    long entry_index = UndirectedWeightedGraph1_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph1_insert_edge", "Exit index", exit_index, true, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph1_insert_edge", "Entry index", entry_index, true, __SUPPRESS_PRINT_ERROR__)
        ) || _already_has_an_edge(uwg, exit_index, entry_index)
    ) return __DEFAULT_BOOL__;

    _set_value_to_matrices(uwg, exit_index, entry_index, weight);
    Vertex_valency_up((Vertex *) Array_get_at(uwg->vertices, exit_index));
    Vertex_valency_up((Vertex *) Array_get_at(uwg->vertices, entry_index));
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph1_change_weight(UndirectedWeightedGraph1 *uwg, void *exit_data, void *entry_data, float new_weight) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_change_weight", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph1_change_weight", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph1_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_change_weight", "Exit Data", exit_data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_change_weight", "Entry Data", entry_data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_change_weight", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    long exit_index = UndirectedWeightedGraph1_index_of(uwg, exit_data);
    long entry_index = UndirectedWeightedGraph1_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph1_change_weight", "Exit index", exit_index, true, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph1_change_weight", "Entry index", entry_index, true, __SUPPRESS_PRINT_ERROR__)
        ) || UndirectedWeightedGraph1_get_weight(uwg, exit_data, entry_data) == __DEFAULT_INITIAL_WEIGHT__
    ) return __DEFAULT_BOOL__;

    Matrix_set_at(uwg->adjacency_matrix, exit_index, entry_index, &new_weight);
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph1_change_data(UndirectedWeightedGraph1 *uwg, void *old_data, void *new_data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_change_data", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph1_change_data", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph1_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_change_data", "Exit Data", old_data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_change_data", "Entry Data", new_data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_change_data", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    Vertex *vertex = _vertex_find(uwg, old_data);
    if (!vertex) return __DEFAULT_BOOL__;
    Vertex_set_data(vertex, new_data);
    return __NOT_DEFAULT_BOOL__;
}

long UndirectedWeightedGraph1_get_capacity(UndirectedWeightedGraph1 *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_capacity", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;
    return uwg->capacity;
}

long UndirectedWeightedGraph1_get_size(UndirectedWeightedGraph1 *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_size", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;
    return uwg->size;
}

float UndirectedWeightedGraph1_get_weight(UndirectedWeightedGraph1 *uwg, void *exit_data, void *entry_data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_weight", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph1_get_weight", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph1_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_weight", "Exit Data", exit_data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_weight", "Entry Data", entry_data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_weight", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, __SUPPRESS_PRINT_ERROR__)
        )
    ) return (float) __DEFAULT_INITIAL_WEIGHT__;

    long exit_index = UndirectedWeightedGraph1_index_of(uwg, exit_data);
    long entry_index = UndirectedWeightedGraph1_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph1_get_weight", "Exit index", exit_index, true, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph1_get_weight", "Entry index", entry_index, true, __SUPPRESS_PRINT_ERROR__)
        )
    ) return (float) __DEFAULT_INITIAL_WEIGHT__;

    return *((float *) Matrix_get_at(uwg->adjacency_matrix, exit_index, entry_index));
}

void *UndirectedWeightedGraph1_get_data(UndirectedWeightedGraph1 *uwg, long index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_data", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph1_get_data", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph1_is_empty, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            2,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_data", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_out_of_bounds("UndirectedWeightedGraph1_get_data", "Undirected Weighted Graph", index, uwg->size, __SUPPRESS_PRINT_ERROR__)
        )
    ) return NULL;
    return Vertex_get_data((Vertex *) Array_get_at(uwg->vertices, index));
}

long UndirectedWeightedGraph1_get_valency(UndirectedWeightedGraph1 *uwg, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_valency", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph1_get_valency", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph1_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_valency", "Data", data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_get_valency", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_LONG__;

    Vertex *vertex = _vertex_find(uwg, data);
    if (!vertex) return __DEFAULT_LONG__;
    return Vertex_get_valency(vertex);
}

bool UndirectedWeightedGraph1_remove_edge(UndirectedWeightedGraph1 *uwg, void *exit_data, void *entry_data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_edge", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph1_remove_edge", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph1_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_edge", "Exit Data", exit_data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_edge", "Entry Data", entry_data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            2,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_edge", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_edge", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    long exit_index = UndirectedWeightedGraph1_index_of(uwg, exit_data);
    long entry_index = UndirectedWeightedGraph1_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph1_remove_edge", "Exit index", exit_index, true, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_non_positive("UndirectedWeightedGraph1_remove_edge", "Entry index", entry_index, true, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    _set_value_to_matrices(uwg, exit_index, entry_index, __DEFAULT_INITIAL_WEIGHT__);

    Vertex_valency_down((Vertex *) Array_get_at(uwg->vertices, exit_index));
    Vertex_valency_down((Vertex *) Array_get_at(uwg->vertices, entry_index));
    return __NOT_DEFAULT_BOOL__;
}

bool UndirectedWeightedGraph1_remove_vertex(UndirectedWeightedGraph1 *uwg, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_vertex", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("UndirectedWeightedGraph1_remove_vertex", "Undirected Weighted Graph", (void *) uwg, UndirectedWeightedGraph1_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_vertex", "Data", data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            2,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_vertex", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_vertex", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    long index = _vertex_index(uwg, data);
    if (index < 0) return __DEFAULT_BOOL__;
    float default_initial_weight = __DEFAULT_INITIAL_WEIGHT__;

    long size = uwg->size;
    if (index != size-1) {
        for (long i = 0; i < size; i++) {
            if (*((int *) Matrix_get_at(uwg->adjacency_matrix, index, i)) != __DEFAULT_INITIAL_WEIGHT__) {
                Matrix_set_at(uwg->adjacency_matrix, index, i, &default_initial_weight);
                Matrix_set_at(uwg->adjacency_matrix, i, index, &default_initial_weight);
                Vertex_valency_down((Vertex *) Array_get_at(uwg->vertices, i));
            }
            Matrix_set_at(uwg->adjacency_matrix, size-1, i, &default_initial_weight);
            Matrix_set_at(uwg->adjacency_matrix, i, size-1, &default_initial_weight);
        }
        for (long i = index; i < size-1; i++) {
            Array_set(uwg->vertices, (Vertex *) Array_get_at(uwg->vertices, i + 1), i);
            for (long j = index; j < size-1; j++) {
                Matrix_set_at(uwg->adjacency_matrix, i, j, Matrix_get_at(uwg->adjacency_matrix, i + 1, j + 1));
            }
        }
    } else {
        for (long i = 0; i < size; i++) {
            if (*((int *) Matrix_get_at(uwg->adjacency_matrix, index, i)) != __DEFAULT_INITIAL_WEIGHT__) {
                Vertex_valency_down((Vertex *) Array_get_at(uwg->vertices, i));
            }
        }
        Matrix_set_at(uwg->adjacency_matrix, index, index, &default_initial_weight);
    }
    uwg->size--;
    return __NOT_DEFAULT_BOOL__;
}

void UndirectedWeightedGraph1_print_full_graph(UndirectedWeightedGraph1 *uwg, __TYPE_PRINT_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_vertex", "Undirected Weighted Graph", (void *) uwg, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            2,
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_vertex", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("UndirectedWeightedGraph1_remove_vertex", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, __SUPPRESS_PRINT_ERROR__)
        )
    ) return;
    _print_adjacency_matrix(uwg);
    _print_vertices(uwg, __TYPE_PRINT_FUNCTION_NAME__);
}
