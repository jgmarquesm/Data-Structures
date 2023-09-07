#include "undirected_weighted_graph.h"
#include <stdlib.h>
#include <stdio.h>
//#--ADD_TO_INCLUDE

void _negative_number_checker(char *function, char *field, long value, bool includesZero) {
    if (includesZero) {
        if (value >= 0) return;
        fprintf(stderr, "\nERROR: on function '%s'.\n", function);
        fprintf(stderr, "ERROR MESSAGE: %s must be greater or equals to 0, but was %ld.\n", field, value);
    } else {
        if (value > 0) return;
        fprintf(stderr, "\nERROR: on function '%s'.\n", function);
        fprintf(stderr, "ERROR MESSAGE: %s must be greater than 0, but was %ld.\n", field, value);
    }
    exit(EXIT_FAILURE);
}

void _nullish_checker(char *function, void *ADT_value, char *ADT_name) {
    if (ADT_value != NULL) {
        return;
    }
    fprintf(stderr, "\nERROR: on function '%s'.\n", function);
    fprintf(stderr, "ERROR MESSAGE: %s is NULL.\n", ADT_name);
    exit(EXIT_FAILURE);
}

void _emptiness_checker(char *function, void *ADT_value, bool (*is_empty_function)(void *data), char *ADT_name) {
    if (!is_empty_function(ADT_value)) return;
    fprintf(stderr, "\nERROR: on function '%s'.\n", function);
    fprintf(stderr, "ERROR MESSAGE: %s is empty.\n", ADT_name);
    exit(EXIT_FAILURE);
}

void _fullness_checker(char *function, void *ADT_value, bool (*is_full_function)(void *data), char *ADT_name) {
    if (!is_full_function(ADT_value)) return;
    fprintf(stderr, "\nERROR: on function '%s'.\n", function);
    fprintf(stderr, "ERROR MESSAGE: %s is full.\n", ADT_name);
    exit(EXIT_FAILURE);
}

typedef struct _vertex {
    void *data;
    long valency;
} Vertex;

typedef struct _undirected_weighted_graph {
    long capacity;
    long size;
    Vertex* *vertices;
    int **adjacency_matrix;
    float **weight_matrix;
} UndirectedWeightedGraph, UWG;

Vertex *_vertex_create(void *data) {
    Vertex *vertex = (Vertex *) calloc(1, sizeof(Vertex));
    vertex->data = data;
    vertex->valency = 0;
    return vertex;
}

long _vertex_index(UWG *uwg, void *data) {
    for (long i = 0; i < uwg->size; i++) {
        if (uwg->vertices[i]->data == data) {
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
            type_print_function(uwg->vertices[i]->data);
            printf(", ");
        }
        type_print_function(uwg->vertices[uwg->size-1]->data);
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
    _negative_number_checker("UWG_create", "max_of_vertices", max_of_vertices, false);

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

void UWG_clean(UWG *uwg) {
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
}

void UWG_destroy(UWG **uwg_ref) {
    UWG *uwg = *uwg_ref;
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
}

long UWG_index_of(UWG *uwg, void *data) {
    _nullish_checker("UWG_index_of", uwg, "UWG");
    _nullish_checker("UWG_index_of", uwg->vertices, "UWG.vertices");
    return _vertex_index(uwg, data);
}

bool UWG_is_empty(void *uwg) {
    _nullish_checker("UWG_is_empty", uwg, "UWG");
    return ((UWG *) uwg)->size == 0;
}

bool UWG_is_full(void *uwg) {
    _nullish_checker("UWG_is_full", uwg, "UWG");
    return ((UWG *) uwg)->size == ((UWG *) uwg)->capacity;
}

void UWG_insert_vertex(UWG *uwg, void *data) {
    _nullish_checker("UWG_insert_vertex", uwg, "UWG");
    _nullish_checker("UWG_insert_vertex", uwg->vertices, "UWG.vertices");
    _fullness_checker("UWG_insert_vertex", uwg, UWG_is_full, "UWG");
    if (_vertex_find(uwg, data)) {
        return;
    }
    uwg->vertices[uwg->size] = _vertex_create(data);
    uwg->size++;
}

void UWG_insert_edge(UWG *uwg, void *exit_data, void *entry_data, float weight) {
    _nullish_checker("UWG_insert_edge", uwg, "UWG");

    long exit_index = UWG_index_of(uwg, exit_data);
    _negative_number_checker("UWG_insert_edge", "exit_index", exit_index, true);

    long entry_index = UWG_index_of(uwg, entry_data);
    _negative_number_checker("UWG_insert_edge", "entry_index", entry_index, true);

    if (_already_has_an_edge(uwg, exit_index, entry_index)) {
        return;
    }

    _set_value_to_matrices(uwg, exit_index, entry_index, weight, DEFAULT_EDGE_VALUE);

    uwg->vertices[exit_index]->valency++;
    uwg->vertices[entry_index]->valency++;
}

void UWG_change_weight(UWG *uwg, void *exit_data, void *entry_data, float new_weight) {
    _nullish_checker("UWG_change_weight", uwg, "UWG");
    _nullish_checker("UWG_change_weight", uwg->weight_matrix, "UWG.weight_matrix");
    _emptiness_checker("UWG_change_weight", uwg, UWG_is_empty, "UWG");

    long exit_index = UWG_index_of(uwg, exit_data);
    _negative_number_checker("UWG_change_weight", "exit_index", exit_index, true);

    long entry_index = UWG_index_of(uwg, entry_data);
    _negative_number_checker("UWG_change_weight", "entry_index", entry_index, true);

    uwg->weight_matrix[exit_index][entry_index] = new_weight;
}

void UWG_change_data(UWG *uwg, void *old_data, void *new_data) {
    _nullish_checker("UWG_insert_vertex", uwg, "UWG");
    _nullish_checker("UWG_insert_vertex", uwg->vertices, "UWG.vertices");

    Vertex *vertex = _vertex_find(uwg, old_data);
    if (!vertex) {
        return;
    }
    vertex->data = new_data;
}

long UWG_get_capacity(UWG *uwg) {
    return uwg->capacity;
}

long UWG_get_size(UWG *uwg) {
    return uwg->size;
}

float UWG_get_weight(UWG *uwg, void *exit_data, void *entry_data) {
    _nullish_checker("UWG_get_weight", uwg, "UWG");
    _nullish_checker("UWG_get_weight", uwg->weight_matrix, "UWG.weight_matrix");
    _emptiness_checker("UWG_get_weight", uwg, UWG_is_empty, "UWG");

    long exit_index = UWG_index_of(uwg, exit_data);
    _negative_number_checker("UWG_get_weight", "exit_index", exit_index, true);

    long entry_index = UWG_index_of(uwg, entry_data);
    _negative_number_checker("UWG_get_weight", "entry_index", entry_index, true);

    return uwg->weight_matrix[exit_index][entry_index];
}

long UWG_get_valency(UWG *uwg, void *data) {
    _nullish_checker("UWG_get_valency", uwg, "UWG");
    _nullish_checker("UWG_get_valency", uwg->vertices, "UWG.vertices");
    _emptiness_checker("UWG_get_valency", uwg, UWG_is_empty, "UWG");

    Vertex *vertex = _vertex_find(uwg, data);
    if (!vertex) {
        return -1;
    }
    return vertex->valency;
}

void UWG_remove_edge(UWG *uwg, void *exit_data, void *entry_data) {
    _nullish_checker("UWG_remove_edge", uwg, "UWG");
    _emptiness_checker("UWG_remove_edge", uwg, UWG_is_empty, "UWG");
    _nullish_checker("UWG_remove_edge", uwg->vertices, "UWG.vertices");
    _nullish_checker("UWG_remove_edge", uwg->adjacency_matrix, "UWG.adjacency_matrix");
    _nullish_checker("UWG_remove_edge", uwg->weight_matrix, "UWG.weight_matrix");

    long exit_index = UWG_index_of(uwg, exit_data);
    _negative_number_checker("UWG_remove_edge", "exit_index", exit_index, true);

    long entry_index = UWG_index_of(uwg, entry_data);
    _negative_number_checker("UWG_remove_edge", "entry_index", entry_index, true);

    _set_value_to_matrices(uwg, exit_index, entry_index, DEFAULT_INITIAL_WEIGHT, DEFAULT_NULL_EDGE_VALUE);

    uwg->vertices[exit_index]->valency--;
    uwg->vertices[entry_index]->valency--;
}

void UWG_remove_vertex(UWG *uwg, void *data) {
    _nullish_checker("UWG_remove_vertex", uwg, "UWG");
    _emptiness_checker("UWG_remove_vertex", uwg, UWG_is_empty, "UWG");
    _nullish_checker("UWG_remove_vertex", uwg->vertices, "UWG.vertices");
    _nullish_checker("UWG_remove_vertex", uwg->adjacency_matrix, "UWG.adjacency_matrix");
    _nullish_checker("UWG_remove_vertex", uwg->weight_matrix, "UWG.weight_matrix");

    long index = _vertex_index(uwg, data);
    if (index < 0) return;

    if (index != uwg->size-1) {
        for (long i = 0; i < uwg->size; i++) {
            if (uwg->adjacency_matrix[index][i] != DEFAULT_NULL_EDGE_VALUE) {
                uwg->adjacency_matrix[index][i] = DEFAULT_NULL_EDGE_VALUE;
                uwg->adjacency_matrix[i][index] = DEFAULT_NULL_EDGE_VALUE;
                uwg->weight_matrix[index][i] = DEFAULT_INITIAL_WEIGHT;
                uwg->weight_matrix[i][index] = DEFAULT_INITIAL_WEIGHT;
                uwg->vertices[i]->valency--;
            }
        }
        for (long i = index; i < uwg->size + 1; i++) {
            uwg->vertices[i] = uwg->vertices[i + 1];
            for (long j = index; j < uwg->size + 1; j++) {
                uwg->adjacency_matrix[i][j] = uwg->adjacency_matrix[i + 1][j + 1];
                uwg->weight_matrix[i][j] = uwg->weight_matrix[i + 1][j + 1];
            }
        }
    } else {
        for (long i = 0; i < uwg->size; i++) {
            if (uwg->adjacency_matrix[index][i] != DEFAULT_NULL_EDGE_VALUE) {
                uwg->vertices[i]->valency--;
            }
        }
        uwg->adjacency_matrix[index][index] = DEFAULT_NULL_EDGE_VALUE;
        uwg->weight_matrix[index][index] = DEFAULT_INITIAL_WEIGHT;
    }
    uwg->size--;
}

void UWG_print_full_graph(UWG *uwg, void (*type_print_function)(void *data)) {
    _nullish_checker("UWG_print_full_graph", uwg->vertices, "UWG.vertices");
    _nullish_checker("UWG_print_full_graph", uwg, "UWG");
    _nullish_checker("UWG_print_full_graph", uwg->adjacency_matrix, "UWG.adjacency_matrix");
    _nullish_checker("UWG_print_full_graph", uwg->weight_matrix, "UWG.weight_matrix");
    _print_adjacency_matrix(uwg);
    _print_weight_matrix(uwg);
    _print_vertices(uwg, type_print_function);
}
