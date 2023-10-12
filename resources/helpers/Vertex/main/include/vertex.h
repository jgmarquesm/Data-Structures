#ifndef VERTEX_H
#define VERTEX_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stddef.h>
#include <stdbool.h>

#ifdef __DEFAULT_LONG__
    #undef __DEFAULT_LONG__
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

#define __DEFAULT_LONG__ -1
#define __DEFAULT_BOOL__ false
#define __NOT_DEFAULT_BOOL__ true
#define __DEFAULT_PTR__ NULL

#define SIZE_OF_VERTEX_TYPE size_of_vertex_type

extern const size_t size_of_vertex_type;

typedef struct _vertex Vertex;
/**
 *
 * @param data -> Data to create a Vertex with;
 * @return If Data != NULL, a new Vertex with data.\n NULL: Otherwise.
 */
Vertex *Vertex_create(void *data);
/**
 *
 * @param vertex_ref -> The pointer of the Vertex to be destroyed;
 * @return true if: Vertex was successfully destroyed;\n false if (Vertex == NULL).
 */
bool Vertex_destroy(Vertex **vertex_ref);
/**
 *
 * @param vertex -> Vertex to get Data.
 * @return Data (void *) of Vertex;\n NULL if (Vertex == NULL || Data == NULL).
 */
void *Vertex_get_data(Vertex *vertex);
/**
 *
 * @param vertex -> Vertex to set Data.
 * @param data -> Data to be set.
 * @return true if Data was successfully set;\n false if (Vertex == NULL || Data == NULL).
 */
bool Vertex_set_data(Vertex *vertex, void *data);
/**
 *
 * @param vertex -> Vertex to get Valency.
 * @return Valency of Vertex;\n -1 if (Vertex == NULL).
 */
long Vertex_get_valency(Vertex *vertex);
/**
 *
 * @param vertex -> Vertex to get Valency.
 * @param new_valency -> New Valency to set.
 * @return New Valency if Valency was successfully set;\n -1 if (Vertex == NULL || New Valency \< 0).
 */
long Vertex_set_valency(Vertex *vertex, long new_valency);
/**
 *
 * @param vertex -> Vertex to Valency UP.
 * @return true if Valency upped;\n false if Vertex == NULL.
 */
bool Vertex_valency_up(Vertex *vertex);
/**
 *
 * @param vertex -> Vertex to Valency DOWN.
 * @return true if Valency downed;\n false if Vertex == NULL.
 */
bool Vertex_valency_down(Vertex *vertex);

#endif
