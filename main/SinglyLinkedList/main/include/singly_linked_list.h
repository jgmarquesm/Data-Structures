#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#define SIZE_OF_SINGLY_LINKED_LIST_TYPE size_of_singly_linked_list_type

extern const size_t size_of_singly_linked_list_type;

/**
 * As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
 * 1 - Type printing function: To print data correctly.\n
 * 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
 * 3 - Type comparison function: To compare correctly data.
 */
typedef struct _singly_linked_list SinglyLinkedList;
/**
 *
 * @return a new SinglyLinkedList (empty)
 */
SinglyLinkedList *SinglyLinkedList_create();
/**
 * This function is responsible for clearing all data from a SinglyLinkedList. After calling this function, all data era
 * erased and the the SinglyLinkedList is empty.
 * @param SLL -> The SinglyLinkedLIst to clean up
 */
bool SinglyLinkedList_clean(SinglyLinkedList *SLL);
/**
 * When calling this function it will clean up and free all nodes and free the SinglyLinkedList.
 * @param SLL_ref -> The SinglyLinkedList reference
 */
bool SinglyLinkedList_destroy(SinglyLinkedList **SLL_ref);
/**
 *
 * @param SLL -> The SinglyLinkedList to verify if is empty
 * @return true if the SinglyLinkedList is empty and false otherwise
 */
bool SinglyLinkedList_is_empty(void *SLL);
/**
 *
 * @param SLL -> The SinglyLinkedLIst to verify if is sorted
 * @return true if the SinglyLinkedList is sorted and false otherwise.
 */
bool SinglyLinkedList_is_sorted(void *SLL);
/**
 *
 * @param SLL -> The SinglyLinkedLIst to verify sort order
 * @return -1 if descending sort;\n 0 if unsorted;\n 1 if ascending sort.
 */
int SinglyLinkedList_sort_order(const SinglyLinkedList *SLL);
/**
 *
 * @param SLL -> SinglyLinkedList to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void SinglyLinkedList_print(const SinglyLinkedList *SLL, void (*type_print_function)(void *data));
/**
 * When calling this functions it will add data to the first SinglyLinkedList node.
 * @param SLL -> SinglyLinkedList to add data
 * @param data -> data to be added.
 */
bool SinglyLinkedList_add_first(SinglyLinkedList *SLL, void *data);
/**
 * When calling this functions it will add data to the last SinglyLinkedList node.
 * @param SLL -> SinglyLinkedList to add data
 * @param data -> data to be added.
 */
bool SinglyLinkedList_add_last(SinglyLinkedList *SLL, void *data);
/**
 * When calling this function it will remove first node of SinglyLinkedList.
 * @param SLL -> SinglyLinkedList to remove data
 * @return The data of the removed node
 */
void *SinglyLinkedList_remove_first(SinglyLinkedList *SLL);
/**
 * When calling this function it will remove last node of SinglyLinkedList.
 * @param SLL -> SinglyLinkedList to remove data
 * @return The data of the removed node
 */
void *SinglyLinkedList_remove_last(SinglyLinkedList *SLL);
/**
 * When calling this function it will remove index-th node of SinglyLinkedList.
 * @param SLL -> SinglyLinkedList to remove data
 * @param index -> index of node to be removed
 * @return The data of the removed node
 */
void *SinglyLinkedList_remove_at(SinglyLinkedList *SLL, const size_t index);
/**
 * When calling this function it will remove first occurrence of data in the SinglyLinkedList.
 * @param SLL -> SinglyLinkedList to remove data
 * @param data -> data to be removed
 */
bool SinglyLinkedList_remove(SinglyLinkedList *SLL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will remove all occurrences of data in the SinglyLinkedList.
 * @param SLL -> SinglyLinkedList to remove data
 * @param data -> data to be removed
 */
size_t SinglyLinkedList_remove_all(SinglyLinkedList *SLL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param SLL -> SinglyLinkedList to check its size
 * @return Number of elements in the SinglyLinkedList
 */
size_t SinglyLinkedList_size(const SinglyLinkedList *SLL);
/**
 *
 * @param SLL -> SinglyLinkedList to get first element
 * @return The data (void *) of first SinglyLinkedList node
 */
void *SinglyLinkedList_first_element(const SinglyLinkedList *SLL);
/**
 *
 * @param SLL -> SinglyLinkedList to get last element
 * @return The data (void *) of last SinglyLinkedList node
 */
void *SinglyLinkedList_last_element(const SinglyLinkedList *SLL);
/**
 *
 * @param SLL -> SinglyLinkedList to get data from (index)th SinglyLinkedList node
 * @param index -> index of data to be got
 * @return The data (void *) of (index)th SinglyLinkedList node
 */
void *SinglyLinkedList_get(const SinglyLinkedList *SLL, const size_t index);
/**
 *
 * @param SLL -> SinglyLinkedList to count number os occurrences os data
 * @param data -> Data that the number of occurrences will be returned
 * @return The number of occurrences of data in the SinglyLinkedList
 */
size_t SinglyLinkedList_count(const SinglyLinkedList *SLL, void *data);
/**
 *
 * @param SLL -> SinglyLinkedList to check if data is contained
 * @param data -> Data that will be checked if it is contained in SinglyLinkedList
 * @return true if SinglyLinkedList contains the data, false otherwise
 */
bool SinglyLinkedList_contains(const SinglyLinkedList *SLL, void *data);
/**
 * When calling this function it will insert data into (index)th SinglyLinkedList node
 * @param SLL -> SinglyLinkedList add data
 * @param data -> Data to be added
 * @param index -> Index to add data at
 */
bool SinglyLinkedList_insert_at(SinglyLinkedList *SLL, void *data, const size_t index);
/**
 *
 * @param SLL -> SinglyLinkedList to be cloned
 * @return A clone of SinglyLinkedList
 */
SinglyLinkedList *SinglyLinkedList_clone(const SinglyLinkedList *SLL);
/**
 *
 * @param SLL1 -> First SinglyLinkedList to be concatenated
 * @param SLL2 -> Second SinglyLinkedList to be concatenated
 * @return A new SinglyLinkedList with SLL1 on begin and then the SLL2
 */
SinglyLinkedList *SinglyLinkedList_concat(SinglyLinkedList *SLL1, SinglyLinkedList *SLL2);
/**
 *
 * @param SLL -> SinglyLinkedList to be reversed
 * @return A new SinglyLinkedList with opposite order os original SinglyLinkedList
 */
SinglyLinkedList *SinglyLinkedList_reverse(SinglyLinkedList *SLL);
/**
 *
 * @param SLL1 -> First SinglyLinkedList to check equality
 * @param SLL2 -> Second SinglyLinkedList to check equality
 * @return true if SLL1 === SLL2;\n false if SLL1 !== SLL2
 */
bool SinglyLinkedList_is_equals_strict(const SinglyLinkedList *SLL1, const SinglyLinkedList *SLL2);
/**
 *
 * @param SLL1 -> First SinglyLinkedList to check equality
 * @param SLL2 -> Second SinglyLinkedList to check equality
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if SLL1 == SLL2;\n false if SLL1 != SLL2
 */
bool SinglyLinkedList_is_equals(const SinglyLinkedList *SLL1, const SinglyLinkedList *SLL2, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will sort the SinglyLinkedList in ascending order
 * @param SLL -> SinglyLinkedList to sort in ascending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool SinglyLinkedList_sort_asc(SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will sort the SinglyLinkedList in descending order
 * @param SLL -> SinglyLinkedList to sort in descending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool SinglyLinkedList_sort_desc(SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will add data to SinglyLinkedList following the order sort
 * @param SLL -> SinglyLinkedList to add data
 * @param data -> Data to be added
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool SinglyLinkedList_sorted_insert(SinglyLinkedList *SLL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param SLL -> SinglyLinkedList to get the smaller data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The smaller data in SinglyLinkedList
 */
void *SinglyLinkedList_min(const SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param SLL -> SinglyLinkedList to get the bigger data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The bigger data in SinglyLinkedList
 */
void *SinglyLinkedList_max(const SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2));

#endif
