#ifndef UNDIRECTED_WEIGHTED_GRAPH2_H
#define UNDIRECTED_WEIGHTED_GRAPH2_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#ifdef __DEFAULT_FLOAT__
    #undef __DEFAULT_FLOAT__
#endif
#ifdef __DEFAULT_SIZE_T__
    #undef __DEFAULT_SIZE_T__
#endif
#ifdef __DEFAULT_BOOL__
    #undef __DEFAULT_BOOL__
#endif
#ifdef __NOT_DEFAULT_BOOL__
    #undef __NOT_DEFAULT_BOOL__
#endif
#ifdef __DEFAULT_PTR__
    #undef __DEFAULT_PTR__
#endif
#ifdef __TYPE_COMPARE_FUNCTION_NAME__
    #undef __TYPE_COMPARE_FUNCTION_NAME__
#endif
#ifdef __TYPE_COMPARE_FUNCTION_SIGNATURE__
    #undef __TYPE_COMPARE_FUNCTION_SIGNATURE__
#endif
#ifdef __TYPE_PRINT_FUNCTION_NAME__
    #undef __TYPE_PRINT_FUNCTION_NAME__
#endif
#ifdef __TYPE_PRINT_FUNCTION_SIGNATURE__
    #undef __TYPE_PRINT_FUNCTION_SIGNATURE__
#endif

#define __DEFAULT_FLOAT__ 0.0
#define __DEFAULT_SIZE_T__ 0
#define __DEFAULT_BOOL__ false
#define __NOT_DEFAULT_BOOL__ true
#define __DEFAULT_PTR__ NULL
#define __TYPE_COMPARE_FUNCTION_NAME__ type_compare_func
#define __TYPE_COMPARE_FUNCTION_SIGNATURE__ int (*__TYPE_COMPARE_FUNCTION_NAME__)(void *data1, void *data2)
#define __TYPE_PRINT_FUNCTION_NAME__ type_print_func
#define __TYPE_PRINT_FUNCTION_SIGNATURE__ void (*__TYPE_PRINT_FUNCTION_NAME__)(void *data)

#define SIZE_OF_UNDIRECTED_WEIGHTED_GRAPH2_TYPE size_of_undirected_weighted_graph2_type

extern const size_t size_of_undirected_weighted_graph2_type;

typedef struct _undirected_weighted_graph2 UndirectedWeightedGraph2;

UndirectedWeightedGraph2 *UndirectedWeightedGraph2_create();

bool UndirectedWeightedGraph2_insert_Vertex(UndirectedWeightedGraph2 *uwg, void *data);

bool UndirectedWeightedGraph2_add_Edge(UndirectedWeightedGraph2 *uwg, size_t source_vertex_index, size_t destination_vertex_index, float weight);

float UndirectedWeightedGraph2_get_weight(UndirectedWeightedGraph2 *uwg, size_t source_vertex_index, size_t destination_vertex_index);

bool UndirectedWeightedGraph2_set_weight(UndirectedWeightedGraph2 *uwg, size_t source_vertex_index, size_t destination_vertex_index, float new_weight);

bool UndirectedWeightedGraph2_is_empty(void *uwg);

bool UndirectedWeightedGraph2_remove_Vertex(UndirectedWeightedGraph2 *uwg, size_t vertex_index);

bool UndirectedWeightedGraph2_remove_Edge(UndirectedWeightedGraph2 *uwg, size_t source_vertex_index, size_t destination_vertex_index);

#endif
