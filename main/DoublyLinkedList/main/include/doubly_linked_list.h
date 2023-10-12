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
typedef struct _doubly_linked_list DoublyLinkedList;
/**
 *
 * @return a new DoublyLinkedList (empty)
 */
DoublyLinkedList *DoublyLinkedList_create();
/**
 * This function is responsible for clearing all data from a DoublyLinkedList. After calling this function, all data era
 * erased and the the DoublyLinkedList is empty.
 * @param DLL -> The DoublyLinkedList to clean up
 * @return true if: Doubly Linked List was successfully cleaned;\n false if (Doubly Linked List == NULL).
 */
bool DoublyLinkedList_clean(DoublyLinkedList *DLL);
/**
 * When calling this function it will clean up and free all nodes and free the (Doubly)DoublyLinkedList.
 * @param DLL_ref -> The DoublyLinkedList reference
 * @return true if: Doubly Linked List was successfully destroyed;\n false if (Doubly Linked List == NULL).
 */
bool DoublyLinkedList_destroy(DoublyLinkedList **DLL_ref);
/**
 *
 * @param DLL -> The DoublyLinkedList to verify if is empty
 * @return true if: DLL is empty (size == 0) or DLL == NULL;\n false if: DLL not empty (size > 0).
 */
bool DoublyLinkedList_is_empty(void *DLL);
/**
 *
 * @param DLL -> The DoublyLinkedList to verify if is sorted
 * @return true if: sort_order == +-1;\n false if sort_order == 0 or DLL == NULL.
 */
bool DoublyLinkedList_is_sorted(void *DLL);
/**
 *
 * @param DLL -> The DoublyLinkedList to verify sort order
 * @return -1 if: descending order;\n 0 if: not sorted or DLL == NULL;\n 1 if: ascending order.
 */
int DoublyLinkedList_sort_order(const DoublyLinkedList *DLL);
/**
 *
 * @param DLL -> DoublyLinkedList to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void DoublyLinkedList_print(const DoublyLinkedList *DLL, __TYPE_PRINT_FUNCTION_SIGNATURE__);
/**
 * When calling this functions it will add data to the first DoublyLinkedList node.
 * @param DLL -> DoublyLinkedList to add data
 * @param data -> data to be added.
 * @return true if: Data was successfully added;\n false if (DLL == NULL || Data == NULL).
 */
bool DoublyLinkedList_add_first(DoublyLinkedList *DLL, void *data);
/**
 * When calling this functions it will add data to the last DoublyLinkedList node.
 * @param DLL -> DoublyLinkedList to add data
 * @param data -> data to be added.
 * @return true if: Data was successfully added;\n false if (DLL == NULL || Data == NULL).
 */
bool DoublyLinkedList_add_last(DoublyLinkedList *DLL, void *data);
/**
 * When calling this function it will remove first node of DoublyLinkedList.
 * @param DLL -> DoublyLinkedList to remove data
 * @return The data of the removed node in the DoublyLinkedList.
 * @return true if: Data was successfully removed;\n false if (DLL == NULL || DLL is empty).
 */
void *DoublyLinkedList_remove_first(DoublyLinkedList *DLL);
/**
 * When calling this function it will remove last node of DoublyLinkedList.
 * @param DLL -> DoublyLinkedList to remove data
 * @return The data of the removed node in the DoublyLinkedList.
 * @return true if: Data was successfully removed;\n false if (DLL == NULL || DLL is empty).
 */
void *DoublyLinkedList_remove_last(DoublyLinkedList *DLL);
/**
 * When calling this function it will remove index-th node of DoublyLinkedList.
 * @param DLL -> DoublyLinkedList to remove data
 * @param index -> index of data to be removed
 * @return The data of the removed node in the DoublyLinkedList.
 * @return true if: Data was successfully removed;\n false if (DLL == NULL || DLL is empty || index is out of bounds).
 */
void *DoublyLinkedList_remove_at(DoublyLinkedList *DLL, const size_t index);
/**
 * When calling this function it will remove first occurrence of data in the DoublyLinkedList.
 * @param DLL -> DoublyLinkedList to remove data
 * @param data -> data to be removed
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully removed;\n false if (DLL == NULL || DLL is empty || Data == NULL).
 */
bool DoublyLinkedList_remove(DoublyLinkedList *DLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will remove all occurrences of data in the DoublyLinkedList.
 * @param DLL -> DoublyLinkedList to remove data
 * @param data -> data to be removed
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully removed;\n false if (DLL == NULL || DLL is empty || Data == NULL).
 */
size_t DoublyLinkedList_remove_all(DoublyLinkedList *DLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param DLL -> DoublyLinkedList to check its size
 * @return Number of elements in the DLL;\n 0 if (DLL == NULL or DLL is empty).
 */
size_t DoublyLinkedList_size(const DoublyLinkedList *DLL);
/**
 *
 * @param DLL -> DoublyLinkedList to get first element
 * @return The data (void *) of first DoublyLinkedList node;\n NULL if (DLL == NULL || DLL is empty).
 */
void *DoublyLinkedList_first_element(const DoublyLinkedList *DLL);
/**
 *
 * @param DLL -> DoublyLinkedList to get last element
 * @return The data (void *) of last DoublyLinkedList node;\n NULL if (DLL == NULL || DLL is empty).
 */
void *DoublyLinkedList_last_element(const DoublyLinkedList *DLL);
/**
 *
 * @param DLL -> DoublyLinkedList to get data from (index)th DoublyLinkedList node
 * @param index -> index of data to be got
 * @return The data (void *) of (index)th DoublyLinkedList node;\n NULL if (DLL == NULL || DLL is empty || index is out of bounds).
 */
void *DoublyLinkedList_get(const DoublyLinkedList *DLL, const size_t index);
/**
 *
 * @param DLL -> DoublyLinkedList to count number os occurrences os data
 * @param data -> Data that the number of occurrences will be returned
 * @return The number of occurrences of data in the DLL;\n 0 if (DLL does not contain the Data || DLL == NULL || DLL is empty || Data == NULL).
 */
size_t DoublyLinkedList_count(const DoublyLinkedList *DLL, void *data);
/**
 *
 * @param DLL -> DoublyLinkedList to check if data is contained
 * @param data -> Data that will be checked if it is contained in DoublyLinkedList
 * @return true if DoublyLinkedList contains the data;\n false if (DLL does not contain the Data || DLL == NULL || DLL is empty || Data == NULL).
 */
bool DoublyLinkedList_contains(const DoublyLinkedList *DLL, void *data);
/**
 * When calling this function it will insert data into (index)th DoublyLinkedList node
 * @param DLL -> DoublyLinkedList add data
 * @param data -> Data to be added
 * @param index -> Index to add data at
 * @return true if: Data was successfully added;\n false if (DLL == NULL || DLL is empty || Data == NULL || index is out of bounds).

 */
bool DoublyLinkedList_insert_at(DoublyLinkedList *DLL, void *data, const size_t index);
/**
 *
 * @param DLL -> DoublyLinkedList to be cloned
 * @return A clone of DLL;\n NULL if (DLL == NULL || DLL is empty).
 */
DoublyLinkedList *DoublyLinkedList_clone(const DoublyLinkedList *DLL);
/**
 *
 * @param DLL1 -> First DoublyLinkedList to be concatenated
 * @param DLL2 -> Second DoublyLinkedList to be concatenated
 * @return A new DoublyLinkedList with DLL1 on begin and then the DLL2;\n NULL if (DLL1 == NULL || DLL1 is empty || DLL2 == NULL || DLL2 is empty).
 */
DoublyLinkedList *DoublyLinkedList_concat(DoublyLinkedList *DLL1, DoublyLinkedList *DLL2);
/**
 *
 * @param DLL -> DoublyLinkedList to be reversed
 * @return A new DoublyLinkedList with opposite order os original DLL;\n NULL if (DLL == NULL || DLL is empty).
 */
DoublyLinkedList *DoublyLinkedList_reverse(DoublyLinkedList *DLL);
/**
 *
 * @param DLL1 -> First DoublyLinkedList to check equality
 * @param DLL2 -> Second DoublyLinkedList to check equality
 * @return true if DLL1 === DLL2;\n false if (DLL1 !== DLL2 || DLL1 == NULL || DLL1 is empty || DLL2 == NULL || DLL2 is empty).
 */
bool DoublyLinkedList_is_equals_strict(const DoublyLinkedList *DLL1, const DoublyLinkedList *DLL2);
/**
 *
 * @param DLL1 -> First DoublyLinkedList to check equality
 * @param DLL2 -> Second DoublyLinkedList to check equality
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return rue if DLL1 == DLL2;\n false if (DLL1 != DLL2 || DLL1 == NULL || DLL1 is empty || DLL2 == NULL || DLL2 is empty).
 */
bool DoublyLinkedList_is_equals(const DoublyLinkedList *DLL1, const DoublyLinkedList *DLL2, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will sort the DoublyLinkedList in ascending order
 * @param DLL_ref -> DoublyLinkedList reference to sort in ascending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully sorted;\n false if (DLL == NULL || DLL is empty || Data == NULL).
 */
bool DoublyLinkedList_sort_asc(DoublyLinkedList *DLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will sort the DoublyLinkedList in descending order
 * @param DLL_ref -> DoublyLinkedList reference to sort in descending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully sorted;\n false if (DLL == NULL || DLL is empty || Data == NULL).
 */
bool DoublyLinkedList_sort_desc(DoublyLinkedList *DLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will add data to DoublyLinkedList following the order sort
 * @param DLL -> DoublyLinkedList to add data
 * @param data -> Data to be added
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully inserted;\n false if (DLL == NULL || Data == NULL || DLL is not sorted).
 */
bool DoublyLinkedList_sorted_insert(DoublyLinkedList *DLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param DLL -> DoublyLinkedList to get the smaller data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The smaller data in DLL;\n NULL if (DLL == NULL || DLL is empty).
 */
void *DoublyLinkedList_min(const DoublyLinkedList *DLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param DLL -> DoublyLinkedList to get the bigger data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The bigger data in DLL;\n NULL if (DLL == NULL || DLL is empty).
 */
void *DoublyLinkedList_max(const DoublyLinkedList *DLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__);

#endif