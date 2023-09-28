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
typedef struct _circular_linked_list CircularLinkedList;
/**
 *
 * @return a new CircularLinkedList (empty)
 */
CircularLinkedList *CircularLinkedList_create();
/**
 * This function is responsible for clearing all data from a CircularLinkedList. After calling this function, all data era
 * erased and the the CircularLinkedList is empty.
 * @param CLL -> The (Doubly)CircularLinkedList to clean up
 */
void CircularLinkedList_clean(CircularLinkedList *CLL);
/**
 * When calling this function it will clean up and free all nodes and free the (Doubly)CircularLinkedList.
 * @param CLL_ref -> The (Doubly)CircularLinkedList reference
 */
void CircularLinkedList_destroy(CircularLinkedList **CLL_ref);
/**
 *
 * @param CLL -> The CircularLinkedList to verify if is empty
 * @return true if the CircularLinkedList is empty and false otherwise
 */
bool CircularLinkedList_is_empty(void *CLL);
/**
 *
 * @param CLL -> The LinkedLIst to verify if is sorted
 * @return true if the CircularLinkedList is sorted and false otherwise.
 */
bool CircularLinkedList_is_sorted(void *CLL);
/**
 *
 * @param CLL -> The LinkedLIst to verify sort order
 * @return -1 if descending sort;\n 0 if unsorted;\n 1 if ascending sort.
 */
int CircularLinkedList_sort_order(const CircularLinkedList *CLL);
/**
 *
 * @param CLL -> (Doubly)CircularLinkedList to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void CircularLinkedList_print(const CircularLinkedList *CLL, void (*type_print_function)(void *data));
/**
 * When calling this functions it will add data to the first CircularLinkedList node.
 * @param CLL -> CircularLinkedList to add data
 * @param data -> data to be added.
 */
void CircularLinkedList_add_first(CircularLinkedList *CLL, void *data);
/**
 * When calling this functions it will add data to the last CircularLinkedList node.
 * @param CLL -> CircularLinkedList to add data
 * @param data -> data to be added.
 */
void CircularLinkedList_add_last(CircularLinkedList *CLL, void *data);
/**
 * When calling this function it will remove first node of CircularLinkedList.
 * @param CLL -> CircularLinkedList to remove data
 * @return The data of the removed node in the CircularLinkedList.
 */
void *CircularLinkedList_remove_first(CircularLinkedList *CLL);
/**
 * When calling this function it will remove last node of CircularLinkedList.
 * @param CLL -> CircularLinkedList to remove data
 * @return The data of the removed node in the CircularLinkedList.
 */
void *CircularLinkedList_remove_last(CircularLinkedList *CLL);
/**
 * When calling this function it will remove index-th node of CircularLinkedList.
 * @param CLL -> CircularLinkedList to remove data
 * @param index -> index of data to be removed
 * @return The data of the removed node in the CircularLinkedList.
 */
void *CircularLinkedList_remove_at(CircularLinkedList *CLL, const size_t index);
/**
 * When calling this function it will remove first occurrence of data in the CircularLinkedList.
 * @param CLL -> CircularLinkedList to remove data
 * @param data -> data to be removed
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
void CircularLinkedList_remove(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will remove all occurrences of data in the CircularLinkedList.
 * @param CLL -> CircularLinkedList to remove data
 * @param data -> data to be removed
  * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
void CircularLinkedList_remove_all(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param CLL -> CircularLinkedList to check its size
 * @return Number of elements in the CircularLinkedList
 */
size_t CircularLinkedList_size(const CircularLinkedList *CLL);
/**
 *
 * @param CLL -> CircularLinkedList to get first element
 * @return The data (void *) of first CircularLinkedList node
 */
void *CircularLinkedList_first_element(const CircularLinkedList *CLL);
/**
 *
 * @param CLL -> CircularLinkedList to get last element
 * @return The data (void *) of last CircularLinkedList node
 */
void *CircularLinkedList_last_element(const CircularLinkedList *CLL);
/**
 *
 * @param CLL -> CircularLinkedList to get data from (index)th CircularLinkedList node
 * @param index -> index of data to be got
 * @return The data (void *) of (index)th CircularLinkedList node
 */
void *CircularLinkedList_get(const CircularLinkedList *CLL, const size_t index);
/**
 *
 * @param CLL -> CircularLinkedList to count number os occurrences os data
 * @param data -> Data that the number of occurrences will be returned
 * @return The number of occurrences of data in the CircularLinkedList
 */
int CircularLinkedList_count(const CircularLinkedList *CLL, void *data);
/**
 *
 * @param CLL -> CircularLinkedList to check if data is contained
 * @param data -> Data that will be checked if it is contained in CircularLinkedList
 * @return true if CircularLinkedList contains the data, false otherwise
 */
bool CircularLinkedList_contains(const CircularLinkedList *CLL, void *data);
/**
 * When calling this function it will insert data into (index)th CircularLinkedList node
 * @param CLL -> CircularLinkedList add data
 * @param data -> Data to be added
 * @param index -> Index to add data at
 */
void CircularLinkedList_insert_at(CircularLinkedList *CLL, void *data, const size_t index);
/**
 *
 * @param CLL -> CircularLinkedList to be cloned
 * @return A clone of CircularLinkedList
 */
CircularLinkedList *CircularLinkedList_clone(const CircularLinkedList *CLL);
/**
 *
 * @param CLL1 -> First CircularLinkedList to be concatenated
 * @param CLL2 -> Second CircularLinkedList to be concatenated
 * @return A new CircularLinkedList with CLL1 on begin and then the CLL2
 */
CircularLinkedList *CircularLinkedList_concat(CircularLinkedList *CLL1, CircularLinkedList *CLL2);
/**
 *
 * @param CLL -> CircularLinkedList to be reversed
 * @return A new CircularLinkedList with opposite order os original CircularLinkedList
 */
CircularLinkedList *CircularLinkedList_reverse(CircularLinkedList *CLL);
/**
 *
 * @param CLL1 -> First CircularLinkedList to check equality
 * @param CLL2 -> Second CircularLinkedList to check equality
 * @return true if CLL1 === CLL2;\n false if CLL1 !== CLL2
 */
bool CircularLinkedList_is_equals_strict(const CircularLinkedList *CLL1, const CircularLinkedList *CLL2);
/**
 *
 * @param CLL1 -> First CircularLinkedList to check equality
 * @param CLL2 -> Second CircularLinkedList to check equality
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return rue if CLL1 == CLL2;\n false if CLL1 != CLL2
 */
bool CircularLinkedList_is_equals(const CircularLinkedList *CLL1, const CircularLinkedList *CLL2, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will sort the CircularLinkedList in ascending order
 * @param CLL_ref -> CircularLinkedList reference to sort in ascending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
void CircularLinkedList_sort_asc(CircularLinkedList **CLL_ref, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will sort the CircularLinkedList in descending order
 * @param CLL_ref -> CircularLinkedList reference to sort in descending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
void CircularLinkedList_sort_desc(CircularLinkedList **CLL_ref, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will add data to CircularLinkedList following the order sort
 * @param CLL -> CircularLinkedList to add data
 * @param data -> Data to be added
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
void CircularLinkedList_sorted_insert(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param CLL -> CircularLinkedList to get the smaller data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The smaller data in CircularLinkedList
 */
void *CircularLinkedList_min(const CircularLinkedList *CLL, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param CLL -> CircularLinkedList to get the bigger data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The bigger data in CircularLinkedList
 */
void *CircularLinkedList_max(const CircularLinkedList *CLL, int (*type_compare_function)(void *data1, void *data2));

#endif