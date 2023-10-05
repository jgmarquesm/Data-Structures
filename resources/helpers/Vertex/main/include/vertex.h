#ifndef VERTEX_H
#define VERTEX_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#ifdef SUPPRESS_PRINT_ERROR
    #undef SUPPRESS_PRINT_ERROR
#endif
#define SUPPRESS_PRINT_ERROR false
#define SIZE_OF_VERTEX_TYPE size_of_vertex_type

extern const size_t size_of_vertex_type;

typedef struct _vertex Vertex;

Vertex *Vertex_create(void *data);

bool Vertex_destroy(Vertex **vertex_ref);

void *Vertex_get_data(Vertex *vertex);

bool Vertex_set_data(Vertex *vertex, void *data);

long Vertex_get_valency(Vertex *vertex);

long Vertex_set_valency(Vertex *vertex, long new_valency);

bool Vertex_valency_up(Vertex *vertex);

bool Vertex_valency_down(Vertex *vertex);

#endif
