#include <stdlib.h>
#include <stdio.h>
#include "../include/vertex.h"
//#--ADD_TO_INCLUDE
#include "../include/undirected_weighted_graph.h"

typedef struct _undirected_weighted_graph {
    long capacity;
    long size;
    Vertex* *vertices;
    int **adjacency_matrix;
    float **weight_matrix;
} UndirectedWeightedGraph, UWG;

long _vertex_index(UWG *uwg, void *data) {
    for (long i = 0; i < uwg->size; i++) {
        if (Vertex_get_data(uwg->vertices[i]) == data) {
            return i;
        }
    }
    return -1;
}

Vertex *_vertex_get_at(UWG *uwg, long index) {
    return uwg->vertices[index];
}

Vertex *_vertex_find(UWG *uwg, void *data) {
    long index = _vertex_index(uwg, data);
    if (index != -1) {
        return _vertex_get_at(uwg, index);
    }
    return NULL;
}

int **_initial_adjacency_matrix(long max_of_vertices) {
    int **adjacency_matrix = (int **) calloc(max_of_vertices, sizeof(int *));
    for (long i = 0; i < max_of_vertices; i++) {
        adjacency_matrix[i] = (int *) calloc(max_of_vertices, sizeof(int));
        for (long j = 0; j < max_of_vertices; j++) {
            adjacency_matrix[i][j] = DEFAULT_NULL_EDGE_VALUE;
        }
    }
    return adjacency_matrix;
}

float **_initial_weight_matrix(long max_of_vertices) {
    float **weight_matrix = (float **) calloc(max_of_vertices, sizeof(float *));
    for (long i = 0; i < max_of_vertices; i++) {
        weight_matrix[i] = (float *) calloc(max_of_vertices, sizeof(float));
        for (long j = 0; j < max_of_vertices; j++) {
            weight_matrix[i][j] = DEFAULT_INITIAL_WEIGHT;
        }
    }
    return weight_matrix;
}

void _print_adjacency_matrix(UWG *uwg) {
    puts("Adjacency Matrix:");
    puts("[");
    for (long i = 0; i < uwg->size; i++) {
        printf("[");
        for(long j = 0; j < uwg->size-1; j++) {
            printf("%d", uwg->adjacency_matrix[i][j]);
            printf(", ");
        }
        printf("%d", uwg->adjacency_matrix[i][uwg->size-1]);
        puts("],");
    }
    puts("]");
}

void _print_weight_matrix(UWG *uwg) {
    puts("Weight Matrix:");
    puts("[");
    for (long i = 0; i < uwg->size; i++) {
        printf("[");
        for(long j = 0; j < uwg->size-1; j++) {
            printf("%.2f", uwg->weight_matrix[i][j]);
            printf(", ");
        }
        printf("%.2f", uwg->weight_matrix[i][uwg->size-1]);
        puts("],");
    }
    puts("]");
}

void _print_vertices(UWG *uwg, void (*type_print_function)(void *data)) {
    printf("Vertices:\n[");
    if (UWG_is_empty(uwg)) {
        puts("]");
    } else {
        for(long i = 0; i < uwg->size-1; i++) {
            type_print_function(Vertex_get_data(uwg->vertices[i]));
            printf(", ");
        }
        type_print_function(Vertex_get_data(uwg->vertices[uwg->size-1]));
        puts("]");
    }
}

bool _already_has_an_edge(UWG *uwg, long exit_index, long entry_index) {
   return uwg->adjacency_matrix[exit_index][entry_index] != DEFAULT_NULL_EDGE_VALUE;
}

void _set_value_to_matrices(UWG *uwg, long exit_index, long entry_index, float weight, int edge_value) {
    if (exit_index == entry_index) {
        uwg->weight_matrix[entry_index][exit_index] = weight;
        uwg->adjacency_matrix[exit_index][entry_index] = 2 * edge_value;
    } else {
        uwg->weight_matrix[exit_index][entry_index] = weight;
        uwg->weight_matrix[entry_index][exit_index] = weight;
        uwg->adjacency_matrix[exit_index][entry_index] = edge_value;
        uwg->adjacency_matrix[entry_index][exit_index] = edge_value;
    }
}

UWG *UWG_create(const long max_of_vertices) {
    if (anyThrows(
            1,
            ExceptionHandler_is_non_positive("UWG_create", "Max of vertices", max_of_vertices, false, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;

    UWG *uwg = (UWG *) calloc(1, sizeof(UWG));
    uwg->capacity = max_of_vertices;
    uwg->size = 0;

    Vertex **vertices = (Vertex **) calloc(max_of_vertices, sizeof(Vertex*));
    uwg->vertices = vertices;

    int **adjacency_matrix = _initial_adjacency_matrix(max_of_vertices);
    uwg->adjacency_matrix = adjacency_matrix;

    float **weight_matrix = _initial_weight_matrix(max_of_vertices);
    uwg->weight_matrix = weight_matrix;

    return uwg;
}

bool UWG_clean(UWG *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UWG_clean", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    for (long i = 0; i < uwg->capacity; i++) {
        free(uwg->vertices[i]);
        free(uwg->adjacency_matrix[i]);
        free(uwg->weight_matrix[i]);
    }
    free(uwg->adjacency_matrix);
    free(uwg->weight_matrix);

    uwg->size = 0;
    uwg->adjacency_matrix = _initial_adjacency_matrix(uwg->capacity);
    uwg->weight_matrix = _initial_weight_matrix(uwg->capacity);
    return true;
}

bool UWG_destroy(UWG **uwg_ref) {
    UWG *uwg = *uwg_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UWG_clean", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    for (long i = 0; i < uwg->capacity; i++) {
        free(uwg->adjacency_matrix[i]);
        free(uwg->weight_matrix[i]);
    }
    free(uwg->vertices);
    uwg->vertices = NULL;
    free(uwg->adjacency_matrix);
    uwg->adjacency_matrix = NULL;
    free(uwg->weight_matrix);
    uwg->weight_matrix = NULL;
    free(uwg);
    *uwg_ref = NULL;
    return true;
}

long UWG_index_of(UWG *uwg, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("UWG_index_of", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("UWG_index_of", "Undirected Weighted Graph", (void *) uwg, UWG_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_index_of", "Data", data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UWG_index_of", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    return _vertex_index(uwg, data);
}

bool UWG_is_empty(void *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UWG_is_empty", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR)
        )
    ) return true;
    return ((UWG *) uwg)->size == 0;
}

bool UWG_is_full(void *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UWG_is_full", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    return ((UWG *) uwg)->size == ((UWG *) uwg)->capacity;
}

bool UWG_insert_vertex(UWG *uwg, void *data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UWG_insert_vertex", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_insert_vertex", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_full("UWG_insert_vertex", "Undirected Weighted Graph", (void *) uwg, UWG_is_full, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UWG_insert_vertex", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    if (_vertex_find(uwg, data)) return false;
    uwg->vertices[uwg->size] = Vertex_create(data);
    uwg->size++;
    return true;
}

bool UWG_insert_edge(UWG *uwg, void *exit_data, void *entry_data, float weight) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UWG_insert_edge", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("UWG_insert_edge", "Undirected Weighted Graph", (void *) uwg, UWG_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_insert_edge", "Exit Data", exit_data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_insert_edge", "Entry Data", entry_data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UWG_insert_edge", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    long exit_index = UWG_index_of(uwg, exit_data);
    long entry_index = UWG_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UWG_insert_edge", "Exit index", exit_index, true, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_non_positive("UWG_insert_edge", "Entry index", entry_index, true, SUPPRESS_PRINT_ERROR)
        ) || _already_has_an_edge(uwg, exit_index, entry_index)
    ) return false;

    _set_value_to_matrices(uwg, exit_index, entry_index, weight, DEFAULT_EDGE_VALUE);
    Vertex_valency_up(uwg->vertices[exit_index]);
    Vertex_valency_up(uwg->vertices[entry_index]);
    return true;
}

bool UWG_change_weight(UWG *uwg, void *exit_data, void *entry_data, float new_weight) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UWG_change_weight", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("UWG_change_weight", "Undirected Weighted Graph", (void *) uwg, UWG_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_change_weight", "Exit Data", exit_data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_change_weight", "Entry Data", entry_data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UWG_change_weight", "Undirected Weighted Graph::Weight Matrix", (void *) uwg->weight_matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    long exit_index = UWG_index_of(uwg, exit_data);
    long entry_index = UWG_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UWG_change_weight", "Exit index", exit_index, true, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_non_positive("UWG_change_weight", "Entry index", entry_index, true, SUPPRESS_PRINT_ERROR)
        ) || UWG_get_weight(uwg, exit_data, entry_data) == DEFAULT_INITIAL_WEIGHT
    ) return false;

    uwg->weight_matrix[exit_index][entry_index] = new_weight;
    return true;
}

bool UWG_change_data(UWG *uwg, void *old_data, void *new_data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UWG_change_data", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("UWG_change_data", "Undirected Weighted Graph", (void *) uwg, UWG_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_change_data", "Exit Data", old_data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_change_data", "Entry Data", new_data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UWG_change_data", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    Vertex *vertex = _vertex_find(uwg, old_data);
    if (!vertex) return false;
    Vertex_set_data(vertex, new_data);
    return true;
}

long UWG_get_capacity(UWG *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UWG_get_capacity", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    return uwg->capacity;
}

long UWG_get_size(UWG *uwg) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("UWG_get_size", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    return uwg->size;
}

float UWG_get_weight(UWG *uwg, void *exit_data, void *entry_data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UWG_get_weight", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("UWG_get_weight", "Undirected Weighted Graph", (void *) uwg, UWG_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_get_weight", "Exit Data", exit_data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_get_weight", "Entry Data", entry_data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UWG_get_weight", "Undirected Weighted Graph::Weight Matrix", (void *) uwg->weight_matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;

    long exit_index = UWG_index_of(uwg, exit_data);
    long entry_index = UWG_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UWG_get_weight", "Exit index", exit_index, true, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_non_positive("UWG_get_weight", "Entry index", entry_index, true, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;

    return uwg->weight_matrix[exit_index][entry_index];
}

void *UWG_get_data(UWG *uwg, long index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("UWG_get_data", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("UWG_get_data", "Undirected Weighted Graph", (void *) uwg, UWG_is_empty, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            2,
            ExceptionHandler_is_null("UWG_get_data", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("UWG_get_data", "Undirected Weighted Graph", index, uwg->size, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return Vertex_get_data(uwg->vertices[index]);
}

long UWG_get_valency(UWG *uwg, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("UWG_get_valency", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("UWG_get_valency", "Undirected Weighted Graph", (void *) uwg, UWG_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_get_valency", "Data", data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("UWG_get_valency", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;

    Vertex *vertex = _vertex_find(uwg, data);
    if (!vertex) return -1;
    return Vertex_get_valency(vertex);
}

bool UWG_remove_edge(UWG *uwg, void *exit_data, void *entry_data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UWG_remove_edge", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("UWG_remove_edge", "Undirected Weighted Graph", (void *) uwg, UWG_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_remove_edge", "Exit Data", exit_data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_remove_edge", "Entry Data", entry_data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            3,
            ExceptionHandler_is_null("UWG_remove_edge", "Undirected Weighted Graph::Weight Matrix", (void *) uwg->weight_matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_remove_edge", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_remove_edge", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    long exit_index = UWG_index_of(uwg, exit_data);
    long entry_index = UWG_index_of(uwg, entry_data);
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("UWG_remove_edge", "Exit index", exit_index, true, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_non_positive("UWG_remove_edge", "Entry index", entry_index, true, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    _set_value_to_matrices(uwg, exit_index, entry_index, DEFAULT_INITIAL_WEIGHT, DEFAULT_NULL_EDGE_VALUE);

    Vertex_valency_down(uwg->vertices[exit_index]);
    Vertex_valency_down(uwg->vertices[entry_index]);
    return true;
}

bool UWG_remove_vertex(UWG *uwg, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("UWG_remove_vertex", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("UWG_remove_vertex", "Undirected Weighted Graph", (void *) uwg, UWG_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_remove_vertex", "Data", data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            3,
            ExceptionHandler_is_null("UWG_remove_vertex", "Undirected Weighted Graph::Weight Matrix", (void *) uwg->weight_matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_remove_vertex", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_remove_vertex", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    long index = _vertex_index(uwg, data);
    if (index < 0) return false;

    long size = uwg->size;
    if (index != size-1) {
        for (long i = 0; i < size; i++) {
            if (uwg->adjacency_matrix[index][i] != DEFAULT_NULL_EDGE_VALUE) {
                uwg->adjacency_matrix[index][i] = DEFAULT_NULL_EDGE_VALUE;
                uwg->adjacency_matrix[i][index] = DEFAULT_NULL_EDGE_VALUE;
                uwg->weight_matrix[index][i] = DEFAULT_INITIAL_WEIGHT;
                uwg->weight_matrix[i][index] = DEFAULT_INITIAL_WEIGHT;
                Vertex_valency_down(uwg->vertices[i]);
            }
            uwg->adjacency_matrix[i][size-1] = DEFAULT_NULL_EDGE_VALUE;
            uwg->adjacency_matrix[size-1][i] = DEFAULT_NULL_EDGE_VALUE;
            uwg->weight_matrix[i][size-1] = DEFAULT_INITIAL_WEIGHT;
            uwg->weight_matrix[size-1][i] = DEFAULT_INITIAL_WEIGHT;
        }
        for (long i = index; i < size-1; i++) {
            uwg->vertices[i] = uwg->vertices[i + 1];
            for (long j = index; j < size-1; j++) {
                uwg->adjacency_matrix[i][j] = uwg->adjacency_matrix[i + 1][j + 1];
                uwg->weight_matrix[i][j] = uwg->weight_matrix[i + 1][j + 1];
            }
        }
    } else {
        for (long i = 0; i < size; i++) {
            if (uwg->adjacency_matrix[index][i] != DEFAULT_NULL_EDGE_VALUE) {
                Vertex_valency_down(uwg->vertices[i]);
            }
        }
        uwg->adjacency_matrix[index][index] = DEFAULT_NULL_EDGE_VALUE;
        uwg->weight_matrix[index][index] = DEFAULT_INITIAL_WEIGHT;
    }
    uwg->size--;
    return true;
}

void UWG_print_full_graph(UWG *uwg, void (*type_print_function)(void *data)) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("UWG_remove_vertex", "Undirected Weighted Graph", (void *) uwg, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_remove_vertex", "Undirected Weighted Graph::Weight Matrix", (void *) uwg->weight_matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_remove_vertex", "Undirected Weighted Graph::Adjacency Matrix", (void *) uwg->adjacency_matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("UWG_remove_vertex", "Undirected Weighted Graph::Vertices", (void *) uwg->vertices, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    _print_adjacency_matrix(uwg);
    _print_weight_matrix(uwg);
    _print_vertices(uwg, type_print_function);
}
