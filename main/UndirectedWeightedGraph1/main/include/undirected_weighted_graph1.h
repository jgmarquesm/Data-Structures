#ifndef UNDIRECTED_WEIGHTED_GRAPH_1_H
#define UNDIRECTED_WEIGHTED_GRAPH_1_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#ifdef __DEFAULT_INITIAL_WEIGHT__
    #undef __DEFAULT_INITIAL_WEIGHT__
#endif
#ifdef __DEFAULT_NULL_EDGE_VALUE__
    #undef __DEFAULT_NULL_EDGE_VALUE__
#endif
#ifdef __DEFAULT_EDGE_VALUE__
    #undef __DEFAULT_EDGE_VALUE__
#endif
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
#ifdef __TYPE_PRINT_FUNCTION_NAME__
    #undef __TYPE_PRINT_FUNCTION_NAME__
#endif
#ifdef __TYPE_PRINT_FUNCTION_SIGNATURE__
    #undef __TYPE_PRINT_FUNCTION_SIGNATURE__
#endif


#define __DEFAULT_INITIAL_WEIGHT__ 0.0
#define __DEFAULT_LONG__ -1
#define __DEFAULT_BOOL__ false
#define __NOT_DEFAULT_BOOL__ true
#define __DEFAULT_PTR__ NULL
#define __TYPE_PRINT_FUNCTION_NAME__ type_print_func
#define __TYPE_PRINT_FUNCTION_SIGNATURE__ void (*__TYPE_PRINT_FUNCTION_NAME__)(void *data)
#define SIZE_OF_UNDIRECTED_WEIGHTED_GRAPH1_TYPE size_of_undirected_weighted_graph1_type

extern const size_t size_of_undirected_weighted_graph1_type;

/**
 * @remark
 * As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
 *
 * 1 - Type printing function: To print data correctly.\n
 * @example void (*type_print_function)(void *data)
 *
 * 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type.\n
 * @example type (*type_convert_function)(void * data)
 *
 * 3 - Type comparison function: To compare data correctly.\n
 * @example int (*type_compare_function)(void *data1, void *data2)
 */
typedef struct _undirected_weighted_graph1 UndirectedWeightedGraph1;

/**
 *
 * @param max_of_vertices -> Max number of vertices that could be stored in the Graph.
 * @return A new Undirected Weighted Graph with capacity to store max_of_vertices vertices;\n NULL if max_of_vertices \<= 0
 */
UndirectedWeightedGraph1 *UndirectedWeightedGraph1_create(const long max_of_vertices);
/**
 * When calling this function, it will clean all data from the Undirected Weighted Graph and restore it to the same state it was created in.
 * It's like a shortcut to: destroy and create a new Undirected Weighted Graph with same capacity of vertices.
 * @param uwg -> Undirected Weighted Graph to be cleaned.
 * @return true if: Undirected Weighted Graph was successfully cleaned;\n false if (Undirected Weighted Graph == NULL).
 */
bool UndirectedWeightedGraph1_clean(UndirectedWeightedGraph1 *uwg);
/**
 * When calling this function, it will free all data that was allocated to store the Undirected Weighted Graph.
 * @param uwg_ref  -> Undirected Weighted Graph reference to be destroyed.
 * @return true if: Undirected Weighted Graph was successfully destroyed;\n false if (Undirected Weighted Graph == NULL).
 */
bool UndirectedWeightedGraph1_destroy(UndirectedWeightedGraph1 **uwg_ref);
/**
 *
 * @param uwg -> Undirected Weighted Graph to get index of Data passed in.
 * @param data -> Data to get index of.
 * @return First index of Data in Undirected Weighted Graph;\n -1 if (UWG does not contain the Data || UWG == NULL || UWG is empty || Data == NULL).
 */
long UndirectedWeightedGraph1_index_of(UndirectedWeightedGraph1 *uwg, void *data);
/**
 *
 * @param uwg -> Undirected Weighted Graph to check emptiness.
 * @return true if: UWG is empty (size == 0) or UWG == NULL;\n false if: UWG not empty (size > 0).
 */
bool UndirectedWeightedGraph1_is_empty(void *uwg);
/**
 *
 * @param uwg -> Undirected Weighted Graph to check fullness.
 * @return true if: UWG is full (size == max_of_vertices);\n false if: UWG is not full (size \<= max_of_vertices) or UWG == NULL.
 */
bool UndirectedWeightedGraph1_is_full(void *uwg);
/**
 * When calling this function it will add a new vertex with the passed data (only if there isn't already a vertex with the same data reference)
 * @param uwg -> Undirected Weighted Graph to add data.
 * @param data -> Data to be added in the Undirected Weighted Graph.
 * @return true if: Vertex was successfully inserted;\n false if (UWG == NULL || UWG is full || Data == NULL).
 */
bool UndirectedWeightedGraph1_insert_vertex(UndirectedWeightedGraph1 *uwg, void *data);
/**
 * When calling this function it will add a edge between two vertices with the passed weight.
 * If there is already a edge between the two vertices, it do nothing just return.
 * Like this is a Undirected Weighted Graph, there is no preference to entry an exit vertices.
 * @param uwg -> Undirected Weighted Graph to edge to vertices.
 * @param exit_data
 * @param entry_data
 * @param weight -> Weight of edge.
 * @return true if: Edge was successfully inserted;\n false if (UWG == NULL || UWG is empty || Exit Vertex == NULL || Entry Vertex == NULL || Exit Vertex not in UWG || Exit Vertex not in UWG).
 */
bool UndirectedWeightedGraph1_insert_edge(UndirectedWeightedGraph1 *uwg, void *exit_data, void *entry_data, float weight);
/**
 * When calling this function it will change teh weight of the edge between two vertices.
 * Like this is a Undirected Weighted Graph, there is no preference to entry an exit vertices.
 * @param uwg -> Undirected Weighted Graph to change weight of edge.
 * @param exit_data
 * @param entry_data
 * @param new_weight -> New Weight of edge.
 * @return true if: Weight was successfully changed;\n false if (UWG == NULL || UWG is empty || Exit Vertex == NULL || Entry Vertex == NULL || Exit Vertex not in UWG || Exit Vertex not in UWG).
 */
bool UndirectedWeightedGraph1_change_weight(UndirectedWeightedGraph1 *uwg, void *exit_data, void *entry_data, float new_weight);
/**
 * When calling this function, it will change the data of a vertex in the Undirected Weighted Graph.
 * @param uwg -> Undirected Weighted Graph to change the data of a vertex.
 * @param old_data -> Old vertex data.
 * @param new_data -> New data of the vertex.
 * @return true if: Data was successfully changed;\n false if (UWG == NULL || UWG is empty || New Data == NULL || Old Data == NULL || Old Data not in UWG)
 */
bool UndirectedWeightedGraph1_change_data(UndirectedWeightedGraph1 *uwg, void *old_data, void *new_data);
/**
 *
 * @param uwg -> Undirected Weighted Graph to get capacity.
 * @return Max number of vertices that Undirected Weighted Graph supports;\n -1 if UWG == NULL.
 */
long UndirectedWeightedGraph1_get_capacity(UndirectedWeightedGraph1 *uwg);
/**
 *
 * @param uwg -> Undirected Weighted Graph to get size.
 * @return Actual size of Undirected Weighted Graph;\n -1 if UWG == NULL.
 */
long UndirectedWeightedGraph1_get_size(UndirectedWeightedGraph1 *uwg);
/**
 *
 * Like this is a Undirected Weighted Graph, there is no preference to entry an exit vertices.
 * @param uwg -> Undirected Weighted Graph to get weight between two vertices.
 * @param exit_data
 * @param entry_data
 * @return -> The Weight of the Edge between the vertices passed;\n 0 if (UWG == NULL || UWG is empty || Exit Vertex == NULL || Entry Vertex == NULL || Exit Vertex not in UWG || Exit Vertex not in UWG).
 */
float UndirectedWeightedGraph1_get_weight(UndirectedWeightedGraph1 *uwg, void *exit_data, void *entry_data);
/**
 *
 * @param uwg -> Undirected Weighted Graph to get data from vertex on index.
 * @param index -> index to get data from.
 * @return Data from vertex at index;\n NULL if (UWG == NULL || UWG is empty || index is out of bounds).
 */
void *UndirectedWeightedGraph1_get_data(UndirectedWeightedGraph1 *uwg, long index);
/**
 *
 * @param uwg -> Undirected Weighted Graph to get valency of the vertex.
 * @param data -> Vertex to get the valency.
 * @return Valency (Degree) of the vertex;\n -1 if (UWG == NULL || UWG is empty || Data == NULL).
 */
long UndirectedWeightedGraph1_get_valency(UndirectedWeightedGraph1 *uwg, void *data);
/**
 * When calling this function, it will remove the edge between the two vertices passed.
 * Like this is a Undirected Weighted Graph, there is no preference to entry an exit vertices.
 * @param uwg
 * @param exit_data
 * @param entry_data
 * @return true if: Edge was successfully removed;\n false if (UWG == NULL || UWG is empty || Exit Vertex == NULL || Entry Vertex == NULL || Exit Vertex not in UWG || Exit Vertex not in UWG).
 */
bool UndirectedWeightedGraph1_remove_edge(UndirectedWeightedGraph1 *uwg, void *exit_data, void *entry_data);
/**
 * When calling this function, it will remove the vertex of Undirected Weighted Graph.
 * @param uwg -> Undirected Weighted Graph to remove the vertex.
 * @param data -> Vertex to be removed.
 * @return true if: Vertex was successfully removed;\n false if (UWG == NULL || UWG is empty || Data == NULL || Data not in UWG).
 */
bool UndirectedWeightedGraph1_remove_vertex(UndirectedWeightedGraph1 *uwg, void *data);
/**
 * When calling this function, it will print Adjacency Matrix, Weight Matrix and Vertex Array of Undirected Weighted Graph.
 * @param uwg -> Undirected Weighted Graph to be printed.
 * @param type_print_function -> like: void (*type_print_function)(void *data).
 */
void UndirectedWeightedGraph1_print_full_graph(UndirectedWeightedGraph1 *uwg, __TYPE_PRINT_FUNCTION_SIGNATURE__);

#endif
