#ifndef EDGE_H
#define EDGE_H
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

#define SIZE_OF_EDGE_TYPE size_of_edge_type

extern const size_t size_of_edge_type;

typedef struct _edge Edge;

Edge *Edge_create(void *src_full_vertex_ref, void *dest_full_vertex_ref, float weight);

bool Edge_add(Edge *edge, void *src_full_vertex_ref, void *dest_full_vertex_ref, float weight);

Edge *Edge_get(Edge *edge, void *src_full_vertex_ref, void *dest_full_vertex_ref);

float Edge_get_weight(Edge *edge);

bool Edge_set_weight(Edge *edge, float new_weight);

bool Edge_exists(Edge *edge, void *src_full_vertex_ref, void *dest_full_vertex_ref);

bool Edge_remove(Edge *edge);

bool Edge_remove_between(Edge *edge, void *src_full_vertex_ref, void *dest_full_vertex_ref);

bool Edge_remove_edges_from_vertex(Edge *edge, void *full_vertex_ref);

#endif