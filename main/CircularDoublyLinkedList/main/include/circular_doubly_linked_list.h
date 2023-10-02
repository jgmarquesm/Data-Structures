#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#ifdef SUPPRESS_PRINT_ERROR
    #undef SUPPRESS_PRINT_ERROR
#endif
#define SUPPRESS_PRINT_ERROR false
#define SIZE_OF_CIRCULAR_DOUBLY_LINKED_LIST_TYPE size_of_circular_doubly_linked_list_type

extern const size_t size_of_circular_doubly_linked_list_type;

/**
 * As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
 * 1 - Type printing function: To print data correctly.\n
 * 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
 * 3 - Type comparison function: To compare correctly data.
 */
typedef struct _circular_doubly_linked_list CircularDoublyLinkedList;
/**
 *
 * @return a new CircularDoublyLinkedList (empty)
 */
CircularDoublyLinkedList *CircularDoublyLinkedList_create();
/**
 * This function is responsible for clearing all data from a CircularDoublyLinkedList. After calling this function, all data era
 * erased and the the CircularDoublyLinkedList is empty.
 * @param CDLL -> The (Doubly)CircularDoublyLinkedList to clean up
 */
bool CircularDoublyLinkedList_clean(CircularDoublyLinkedList *CDLL);
/**
 * When calling this function it will clean up and free all nodes and free the (Doubly)CircularDoublyLinkedList.
 * @param CDLL_ref -> The (Doubly)CircularDoublyLinkedList reference
 */
bool CircularDoublyLinkedList_destroy(CircularDoublyLinkedList **CDLL_ref);
/**
 *
 * @param CDLL -> The CircularDoublyLinkedList to verify if is empty
 * @return true if the CircularDoublyLinkedList is empty and false otherwise
 */
bool CircularDoublyLinkedList_is_empty(void *CDLL);
/**
 *
 * @param CDLL -> The LinkedLIst to verify if is sorted
 * @return true if the CircularDoublyLinkedList is sorted and false otherwise.
 */
bool CircularDoublyLinkedList_is_sorted(void *CDLL);
/**
 *
 * @param CDLL -> The LinkedLIst to verify sort order
 * @return -1 if descending sort;\n 0 if unsorted;\n 1 if ascending sort.
 */
int CircularDoublyLinkedList_sort_order(const CircularDoublyLinkedList *CDLL);
/**
 *
 * @param CDLL -> (Doubly)CircularDoublyLinkedList to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void CircularDoublyLinkedList_print(const CircularDoublyLinkedList *CDLL, void (*type_print_function)(void *data));
/**
 * When calling this functions it will add data to the first CircularDoublyLinkedList node.
 * @param CDLL -> CircularDoublyLinkedList to add data
 * @param data -> data to be added.
 */
bool CircularDoublyLinkedList_add_first(CircularDoublyLinkedList *CDLL, void *data);
/**
 * When calling this functions it will add data to the last CircularDoublyLinkedList node.
 * @param CDLL -> CircularDoublyLinkedList to add data
 * @param data -> data to be added.
 */
bool CircularDoublyLinkedList_add_last(CircularDoublyLinkedList *CDLL, void *data);
/**
 * When calling this function it will remove first node of CircularDoublyLinkedList.
 * @param CDLL -> CircularDoublyLinkedList to remove data
 * @return The data of the removed node in the CircularDoublyLinkedList.
 */
void *CircularDoublyLinkedList_remove_first(CircularDoublyLinkedList *CDLL);
/**
 * When calling this function it will remove last node of CircularDoublyLinkedList.
 * @param CDLL -> CircularDoublyLinkedList to remove data
 * @return The data of the removed node in the CircularDoublyLinkedList.
 */
void *CircularDoublyLinkedList_remove_last(CircularDoublyLinkedList *CDLL);
/**
 * When calling this function it will remove index-th node of CircularDoublyLinkedList.
 * @param CDLL -> CircularDoublyLinkedList to remove data
 * @param index -> index of data to be removed
 * @return The data of the removed node in the CircularDoublyLinkedList.
 */
void *CircularDoublyLinkedList_remove_at(CircularDoublyLinkedList *CDLL, const size_t index);
/**
 * When calling this function it will remove first occurrence of data in the CircularDoublyLinkedList.
 * @param CDLL -> CircularDoublyLinkedList to remove data
 * @param data -> data to be removed
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool CircularDoublyLinkedList_remove(CircularDoublyLinkedList *CDLL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will remove all occurrences of data in the CircularDoublyLinkedList.
 * @param CDLL -> CircularDoublyLinkedList to remove data
 * @param data -> data to be removed
  * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
size_t CircularDoublyLinkedList_remove_all(CircularDoublyLinkedList *CDLL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to check its size
 * @return Number of elements in the CircularDoublyLinkedList
 */
size_t CircularDoublyLinkedList_size(const CircularDoublyLinkedList *CDLL);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to get first element
 * @return The data (void *) of first CircularDoublyLinkedList node
 */
void *CircularDoublyLinkedList_first_element(const CircularDoublyLinkedList *CDLL);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to get last element
 * @return The data (void *) of last CircularDoublyLinkedList node
 */
void *CircularDoublyLinkedList_last_element(const CircularDoublyLinkedList *CDLL);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to get data from (index)th CircularDoublyLinkedList node
 * @param index -> index of data to be got
 * @return The data (void *) of (index)th CircularDoublyLinkedList node
 */
void *CircularDoublyLinkedList_get(const CircularDoublyLinkedList *CDLL, const size_t index);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to count number os occurrences os data
 * @param data -> Data that the number of occurrences will be returned
 * @return The number of occurrences of data in the CircularDoublyLinkedList
 */
int CircularDoublyLinkedList_count(const CircularDoublyLinkedList *CDLL, void *data);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to check if data is contained
 * @param data -> Data that will be checked if it is contained in CircularDoublyLinkedList
 * @return true if CircularDoublyLinkedList contains the data, false otherwise
 */
bool CircularDoublyLinkedList_contains(const CircularDoublyLinkedList *CDLL, void *data);
/**
 * When calling this function it will insert data into (index)th CircularDoublyLinkedList node
 * @param CDLL -> CircularDoublyLinkedList add data
 * @param data -> Data to be added
 * @param index -> Index to add data at
 */
bool CircularDoublyLinkedList_insert_at(CircularDoublyLinkedList *CDLL, void *data, const size_t index);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to be cloned
 * @return A clone of CircularDoublyLinkedList
 */
CircularDoublyLinkedList *CircularDoublyLinkedList_clone(const CircularDoublyLinkedList *CDLL);
/**
 *
 * @param CDLL1 -> First CircularDoublyLinkedList to be concatenated
 * @param CDLL2 -> Second CircularDoublyLinkedList to be concatenated
 * @return A new CircularDoublyLinkedList with CDLL1 on begin and then the CDLL2
 */
CircularDoublyLinkedList *CircularDoublyLinkedList_concat(CircularDoublyLinkedList *CDLL1, CircularDoublyLinkedList *CDLL2);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to be reversed
 * @return A new CircularDoublyLinkedList with opposite order os original CircularDoublyLinkedList
 */
bool CircularDoublyLinkedList_reverse(CircularDoublyLinkedList **CDLL_ref);
/**
 *
 * @param CDLL1 -> First CircularDoublyLinkedList to check equality
 * @param CDLL2 -> Second CircularDoublyLinkedList to check equality
 * @return true if CDLL1 === CDLL2;\n false if CDLL1 !== CDLL2
 */
bool CircularDoublyLinkedList_is_equals_strict(const CircularDoublyLinkedList *CDLL1, const CircularDoublyLinkedList *CDLL2);
/**
 *
 * @param CDLL1 -> First CircularDoublyLinkedList to check equality
 * @param CDLL2 -> Second CircularDoublyLinkedList to check equality
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return rue if CDLL1 == CDLL2;\n false if CDLL1 != CDLL2
 */
bool CircularDoublyLinkedList_is_equals(const CircularDoublyLinkedList *CDLL1, const CircularDoublyLinkedList *CDLL2, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will sort the CircularDoublyLinkedList in ascending order
 * @param CDLL_ref -> CircularDoublyLinkedList reference to sort in ascending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool CircularDoublyLinkedList_sort_asc(CircularDoublyLinkedList **CDLL_ref, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will sort the CircularDoublyLinkedList in descending order
 * @param CDLL_ref -> CircularDoublyLinkedList reference to sort in descending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool CircularDoublyLinkedList_sort_desc(CircularDoublyLinkedList **CDLL_ref, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will add data to CircularDoublyLinkedList following the order sort
 * @param CDLL -> CircularDoublyLinkedList to add data
 * @param data -> Data to be added
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool CircularDoublyLinkedList_sorted_insert(CircularDoublyLinkedList *CDLL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to get the smaller data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The smaller data in CircularDoublyLinkedList
 */
void *CircularDoublyLinkedList_min(const CircularDoublyLinkedList *CDLL, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to get the bigger data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The bigger data in CircularDoublyLinkedList
 */
void *CircularDoublyLinkedList_max(const CircularDoublyLinkedList *CDLL, int (*type_compare_function)(void *data1, void *data2));

#endif