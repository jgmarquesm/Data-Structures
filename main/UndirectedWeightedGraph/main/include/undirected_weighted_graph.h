#ifndef UNDIRECTED_WEIGHTED_GRAPH_H
#define UNDIRECTED_WEIGHTED_GRAPH_H

#include <stdbool.h>

#define DEFAULT_INITIAL_WEIGHT 0.0
#define DEFAULT_NULL_EDGE_VALUE 0
#define DEFAULT_EDGE_VALUE 1

typedef struct _undirected_weighted_graph UndirectedWeightedGraph, UWG;

/**
 *
 * @param max_of_vertices -> Max number of vertices that could be stored in the Graph.
 * @return A new Undirected Weighted Graph with capacity to store max_of_vertices vertices.
 */
UWG *UWG_create(const long max_of_vertices);
/**
 * When calling this function, it will clean all data from the Undirected Weighted Graph and restore it to the same state it was created in.
 * It's like a shortcut to: destroy and create a new Undirected Weighted Graph with same capacity of vertices.
 * @param uwg -> Undirected Weighted Graph to be cleaned.
 */
void UWG_clean(UWG *uwg);
/**
 * When calling this function, it will free all data that was allocated to store the Undirected Weighted Graph.
 * @param uwg_ref  -> Undirected Weighted Graph reference to be destroyed.
 */
void UWG_destroy(UWG **uwg_ref);
/**
 *
 * @param uwg -> Undirected Weighted Graph to get index of Data passed in.
 * @param data -> Data to get index of.
 * @return Index of the Data if Data is present in Undirected Weighted Graph, otherwise -1;
 */
long UWG_index_of(UWG *uwg, void *data);
/**
 *
 * @param uwg -> Undirected Weighted Graph to check emptiness.
 * @return true if Undirected Weighted Graph is empty, false otherwise.
 */
bool UWG_is_empty(void *uwg);
/**
 *
 * @param uwg -> Undirected Weighted Graph to check fullness.
 * @return true if Undirected Weighted Graph is full, false otherwise.
 */
bool UWG_is_full(void *uwg);
/**
 * When calling this function it will add a new vertex with the passed data (only if there isn't already a vertex with the same data reference)
 * @param uwg -> Undirected Weighted Graph to add data.
 * @param data -> Data to be added in the Undirected Weighted Graph.
 */
void UWG_insert_vertex(UWG *uwg, void *data);
/**
 * When calling this function it will add a edge between two vertices with the passed weight.
 * If there is already a edge between the two vertices, it do nothing just return.
 * Like this is a Undirected Weighted Graph, there is no preference to entry an exit vertices.
 * @param uwg -> Undirected Weighted Graph to edge to vertices.
 * @param exit_data
 * @param entry_data
 * @param weight -> Weight of edge.
 */
void UWG_insert_edge(UWG *uwg, void *exit_data, void *entry_data, float weight);
/**
 * When calling this function it will change teh weight of the edge between two vertices.
 * Like this is a Undirected Weighted Graph, there is no preference to entry an exit vertices.
 * @param uwg -> Undirected Weighted Graph to change weight of edge.
 * @param exit_data
 * @param entry_data
 * @param new_weight -> New Weight of edge.
 */
void UWG_change_weight(UWG *uwg, void *exit_data, void *entry_data, float new_weight);
/**
 * When calling this function, it will change the data of a vertex in the Undirected Weighted Graph.
 * @param uwg -> Undirected Weighted Graph to change the data of a vertex.
 * @param old_data -> Old vertex data.
 * @param new_data -> New data of the vertex.
 */
void UWG_change_data(UWG *uwg, void *old_data, void *new_data);
/**
 *
 * @param uwg -> Undirected Weighted Graph to get capacity.
 * @return Max number of vertices that Undirected Weighted Graph supports.
 */
long UWG_get_capacity(UWG *uwg);
/**
 *
 * @param uwg -> Undirected Weighted Graph to get size.
 * @return Actual size of Undirected Weighted Graph.
 */
long UWG_get_size(UWG *uwg);
/**
 *
 * Like this is a Undirected Weighted Graph, there is no preference to entry an exit vertices.
 * @param uwg -> Undirected Weighted Graph to get weight between two vertices.
 * @param exit_data
 * @param entry_data
 * @return -> The Weight of the Edge between the vertices passed.
 */
float UWG_get_weight(UWG *uwg, void *exit_data, void *entry_data);
/**
 *
 * @param uwg -> Undirected Weighted Graph to get valency of the vertex.
 * @param data -> Vertex to get the valency.
 * @return Valency (Degree) of the vertex.
 */
long UWG_get_valency(UWG *uwg, void *data);
/**
 * When calling this function, it will remove the edge between the two vertices passed.
 * Like this is a Undirected Weighted Graph, there is no preference to entry an exit vertices.
 * @param uwg
 * @param exit_data
 * @param entry_data
 */
void UWG_remove_edge(UWG *uwg, void *exit_data, void *entry_data);
/**
 * When calling this function, it will remove the vertex of Undirected Weighted Graph.
 * @param uwg -> Undirected Weighted Graph to remove the vertex.
 * @param data -> Vertex to be removed.
 */
void UWG_remove_vertex(UWG *uwg, void *data);
/**
 * When calling this function, it will print Adjacency Matrix, Weight Matrix and Vertex Array of Undirected Weighted Graph.
 * @param uwg -> Undirected Weighted Graph to be printed.
 * @param type_print_function -> like: void (*type_print_function)(void *data).
 */
void UWG_print_full_graph(UWG *uwg, void (*type_print_function)(void *data));

#endif
