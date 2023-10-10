#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#ifdef __UNSORTED__
    #undef __UNSORTED__
#endif
#ifdef __ASC__
    #undef __ASC__
#endif
#ifdef __DESC__
    #undef __DESC__
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

#define __UNSORTED__ 0
#define __ASC__ 1
#define __DESC__ -1
#define __DEFAULT_SIZE_T__ 0
#define __DEFAULT_BOOL__ false
#define __NOT_DEFAULT_BOOL__ true
#define __DEFAULT_PTR__ NULL
#define __TYPE_COMPARE_FUNCTION_NAME__ type_compare_func
#define __TYPE_COMPARE_FUNCTION_SIGNATURE__ int (*__TYPE_COMPARE_FUNCTION_NAME__)(void *data1, void *data2)
#define __TYPE_PRINT_FUNCTION_NAME__ type_print_func
#define __TYPE_PRINT_FUNCTION_SIGNATURE__ void (*__TYPE_PRINT_FUNCTION_NAME__)(void *data)

#define SIZE_OF_DOUBLY_LINKED_LIST_TYPE size_of_doubly_linked_list_type

extern const size_t size_of_doubly_linked_list_type;

/**
 * As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
 * 1 - Type printing function: To print data correctly.\n
 * 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
 * 3 - Type comparison function: To compare correctly data.
 */
typedef struct _doubly_linked_list DoublyLinkedList;
/**
 *
 * @return a new DoublyLinkedList (empty)
 */
DoublyLinkedList *DoublyLinkedList_create();
/**
 * This function is responsible for clearing all data from a DoublyLinkedList. After calling this function, all data era
 * erased and the the DoublyLinkedList is empty.
 * @param LL -> The (Doubly))DoublyLinkedList to clean up
 */
bool DoublyLinkedList_clean(DoublyLinkedList *LL);
/**
 * When calling this function it will clean up and free all nodes and free the DoublyLinkedList.
 * @param LL_ref -> The DoublyLinkedList reference
 */
bool DoublyLinkedList_destroy(DoublyLinkedList **LL_ref);
/**
 *
 * @param LL -> The DoublyLinkedList to verify if is empty
 * @return true if the DoublyLinkedList is empty and false otherwise
 */
bool DoublyLinkedList_is_empty(void *LL);
/**
 *
 * @param LL -> The LinkedLIst to verify if is sorted
 * @return true if the DoublyLinkedList is sorted and false otherwise.
 */
bool DoublyLinkedList_is_sorted(void *LL);
/**
 *
 * @param LL -> The LinkedLIst to verify sort order
 * @return -1 if descending sort;\n 0 if unsorted;\n 1 if ascending sort.
 */
int DoublyLinkedList_sort_order(const DoublyLinkedList *LL);
/**
 *
 * @param LL -> DoublyLinkedList to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void DoublyLinkedList_print(const DoublyLinkedList *LL, __TYPE_PRINT_FUNCTION_SIGNATURE__);
/**
 * When calling this functions it will add data to the first DoublyLinkedList node.
 * @param LL -> DoublyLinkedList to add data
 * @param data -> data to be added.
 */
bool DoublyLinkedList_add_first(DoublyLinkedList *LL, void *data);
/**
 * When calling this functions it will add data to the last DoublyLinkedList node.
 * @param LL -> DoublyLinkedList to add data
 * @param data -> data to be added.
 */
bool DoublyLinkedList_add_last(DoublyLinkedList *LL, void *data);
/**
 * When calling this function it will remove first node of DoublyLinkedList.
 * @param LL -> DoublyLinkedList to remove data
 * @return The data of the removed node in the DoublyLinkedList.
 */
void *DoublyLinkedList_remove_first(DoublyLinkedList *LL);
/**
 * When calling this function it will remove last node of DoublyLinkedList.
 * @param LL -> DoublyLinkedList to remove data
 * @return The data of the removed node in the DoublyLinkedList.
 */
void *DoublyLinkedList_remove_last(DoublyLinkedList *LL);
/**
 * When calling this function it will remove index-th node of DoublyLinkedList.
 * @param LL -> DoublyLinkedList to remove data
 * @param index -> Index to remove data at
 * @return The data of the removed node in the DoublyLinkedList.
 */
void *DoublyLinkedList_remove_at(DoublyLinkedList *LL, const size_t index);
/**
 * When calling this function it will remove first occurrence of data in the DoublyLinkedList.
 * @param LL -> DoublyLinkedList to remove data
 * @param data -> data to be removed
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool DoublyLinkedList_remove(DoublyLinkedList *LL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will remove all occurrences of data in the DoublyLinkedList.
 * @param LL -> DoublyLinkedList to remove data
 * @param data -> data to be removed
  * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
size_t DoublyLinkedList_remove_all(DoublyLinkedList *LL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param LL -> DoublyLinkedList to check its size
 * @return Number of elements in the DoublyLinkedList
 */
size_t DoublyLinkedList_size(const DoublyLinkedList *LL);
/**
 *
 * @param LL -> DoublyLinkedList to get first element
 * @return The data (void *) of first DoublyLinkedList node
 */
void *DoublyLinkedList_first_element(const DoublyLinkedList *LL);
/**
 *
 * @param LL -> DoublyLinkedList to get last element
 * @return The data (void *) of last DoublyLinkedList node
 */
void *DoublyLinkedList_last_element(const DoublyLinkedList *LL);
/**
 *
 * @param LL -> DoublyLinkedList to get data from (index)th DoublyLinkedList node
 * @param index -> index of data to be got
 * @return The data (void *) of (index)th DoublyLinkedList node
 */
void *DoublyLinkedList_get(const DoublyLinkedList *LL, const size_t index);
/**
 *
 * @param LL -> DoublyLinkedList to count number os occurrences os data
 * @param data -> Data that the number of occurrences will be returned
 * @return The number of occurrences of data in the DoublyLinkedList
 */
size_t DoublyLinkedList_count(const DoublyLinkedList *LL, void *data);
/**
 *
 * @param LL -> DoublyLinkedList to check if data is contained
 * @param data -> Data that will be checked if it is contained in DoublyLinkedList
 * @return true if DoublyLinkedList contains the data, false otherwise
 */
bool DoublyLinkedList_contains(const DoublyLinkedList *LL, void *data);

/**
 * When calling this function it will insert data into (index)th DoublyLinkedList node
 * @param LL -> DoublyLinkedList add data
 * @param data -> Data to be added
 * @param index -> Index to add data at
 */
bool DoublyLinkedList_insert_at(DoublyLinkedList *LL, void *data, const size_t index);
/**
 *
 * @param LL -> DoublyLinkedList to be cloned
 * @return A clone of DoublyLinkedList
 */
DoublyLinkedList *DoublyLinkedList_clone(const DoublyLinkedList *LL);
/**
 *
 * @param LL1 -> First DoublyLinkedList to be concatenated
 * @param LL2 -> Second DoublyLinkedList to be concatenated
 * @return A new DoublyLinkedList with LL1 on begin and then the LL2
 */
DoublyLinkedList *DoublyLinkedList_concat(DoublyLinkedList *LL1, DoublyLinkedList *LL2);
/**
 *
 * @param LL -> DoublyLinkedList to be reversed
 * @return A new DoublyLinkedList with opposite order os original DoublyLinkedList
 */
DoublyLinkedList *DoublyLinkedList_reverse(DoublyLinkedList *LL);
/**
 *
 * @param LL1 -> First DoublyLinkedList to check equality
 * @param LL2 -> Second DoublyLinkedList to check equality
 * @return true if LL1 === LL2;\n false if LL1 !== LL2
 */
bool DoublyLinkedList_is_equals_strict(const DoublyLinkedList *LL1, const DoublyLinkedList *LL2);
/**
 *
 * @param LL1 -> First DoublyLinkedList to check equality
 * @param LL2 -> Second DoublyLinkedList to check equality
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return rue if LL1 == LL2;\n false if LL1 != LL2
 */
bool DoublyLinkedList_is_equals(const DoublyLinkedList *LL1, const DoublyLinkedList *LL2, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will sort the DoublyLinkedList in ascending order
 * @param LL -> DoublyLinkedList to sort in ascending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool DoublyLinkedList_sort_asc(DoublyLinkedList *LL, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will sort the DoublyLinkedList in descending order
 * @param LL -> DoublyLinkedList to sort in descending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool DoublyLinkedList_sort_desc(DoublyLinkedList *LL, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will add data to DoublyLinkedList following the order sort
 * @param LL -> DoublyLinkedList to add data
 * @param data -> Data to be added
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool DoublyLinkedList_sorted_insert(DoublyLinkedList *LL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param LL -> DoublyLinkedList to get the smaller data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The smaller data in DoublyLinkedList
 */
void *DoublyLinkedList_min(const DoublyLinkedList *LL, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param LL -> DoublyLinkedList to get the bigger data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The bigger data in DoublyLinkedList
 */
void *DoublyLinkedList_max(const DoublyLinkedList *LL, __TYPE_COMPARE_FUNCTION_SIGNATURE__);

#endif