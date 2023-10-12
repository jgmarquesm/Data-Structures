#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H
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

#define SIZE_OF_CIRCULAR_DOUBLY_LINKED_LIST_TYPE size_of_circular_doubly_linked_list_type

extern const size_t size_of_circular_doubly_linked_list_type;

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
typedef struct _circular_doubly_linked_list CircularDoublyLinkedList;
/**
 *
 * @return a new CircularDoublyLinkedList (empty)
 */
CircularDoublyLinkedList *CircularDoublyLinkedList_create();
/**
 * This function is responsible for clearing all data from a CircularDoublyLinkedList. After calling this function, all data era
 * erased and the the CircularDoublyLinkedList is empty.
 * @param CDLL -> The CircularDoublyLinkedList to clean up
 * @return true if: Circular Doubly Linked List was successfully cleaned;\n false if (Circular Doubly Linked List == NULL).
 */
bool CircularDoublyLinkedList_clean(CircularDoublyLinkedList *CDLL);
/**
 * When calling this function it will clean up and free all nodes and free the (Doubly)CircularDoublyLinkedList.
 * @param CDLL_ref -> The CircularDoublyLinkedList reference
 * @return true if: Circular Doubly Linked List was successfully destroyed;\n false if (Circular Doubly Linked List == NULL).
 */
bool CircularDoublyLinkedList_destroy(CircularDoublyLinkedList **CDLL_ref);
/**
 *
 * @param CDLL -> The CircularDoublyLinkedList to verify if is empty
 * @return true if: CDLL is empty (size == 0) or CDLL == NULL;\n false if: CDLL not empty (size > 0).
 */
bool CircularDoublyLinkedList_is_empty(void *CDLL);
/**
 *
 * @param CDLL -> The CircularDoublyLinkedList to verify if is sorted
 * @return true if: sort_order == +-1;\n false if sort_order == 0 or CDLL == NULL.
 */
bool CircularDoublyLinkedList_is_sorted(void *CDLL);
/**
 *
 * @param CDLL -> The CircularDoublyLinkedList to verify sort order
 * @return -1 if: descending order;\n 0 if: not sorted or CDLL == NULL;\n 1 if: ascending order.
 */
int CircularDoublyLinkedList_sort_order(const CircularDoublyLinkedList *CDLL);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void CircularDoublyLinkedList_print(const CircularDoublyLinkedList *CDLL, __TYPE_PRINT_FUNCTION_SIGNATURE__);
/**
 * When calling this functions it will add data to the first CircularDoublyLinkedList node.
 * @param CDLL -> CircularDoublyLinkedList to add data
 * @param data -> data to be added.
 * @return true if: Data was successfully added;\n false if (CDLL == NULL || Data == NULL).
 */
bool CircularDoublyLinkedList_add_first(CircularDoublyLinkedList *CDLL, void *data);
/**
 * When calling this functions it will add data to the last CircularDoublyLinkedList node.
 * @param CDLL -> CircularDoublyLinkedList to add data
 * @param data -> data to be added.
 * @return true if: Data was successfully added;\n false if (CDLL == NULL || Data == NULL).
 */
bool CircularDoublyLinkedList_add_last(CircularDoublyLinkedList *CDLL, void *data);
/**
 * When calling this function it will remove first node of CircularDoublyLinkedList.
 * @param CDLL -> CircularDoublyLinkedList to remove data
 * @return The data of the removed node in the CircularDoublyLinkedList.
 * @return true if: Data was successfully removed;\n false if (CDLL == NULL || CDLL is empty).
 */
void *CircularDoublyLinkedList_remove_first(CircularDoublyLinkedList *CDLL);
/**
 * When calling this function it will remove last node of CircularDoublyLinkedList.
 * @param CDLL -> CircularDoublyLinkedList to remove data
 * @return The data of the removed node in the CircularDoublyLinkedList.
 * @return true if: Data was successfully removed;\n false if (CDLL == NULL || CDLL is empty).
 */
void *CircularDoublyLinkedList_remove_last(CircularDoublyLinkedList *CDLL);
/**
 * When calling this function it will remove index-th node of CircularDoublyLinkedList.
 * @param CDLL -> CircularDoublyLinkedList to remove data
 * @param index -> index of data to be removed
 * @return The data of the removed node in the CircularDoublyLinkedList.
 * @return true if: Data was successfully removed;\n false if (CDLL == NULL || CDLL is empty || index is out of bounds).
 */
void *CircularDoublyLinkedList_remove_at(CircularDoublyLinkedList *CDLL, const size_t index);
/**
 * When calling this function it will remove first occurrence of data in the CircularDoublyLinkedList.
 * @param CDLL -> CircularDoublyLinkedList to remove data
 * @param data -> data to be removed
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully removed;\n false if (CDLL == NULL || CDLL is empty || Data == NULL).
 */
bool CircularDoublyLinkedList_remove(CircularDoublyLinkedList *CDLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will remove all occurrences of data in the CircularDoublyLinkedList.
 * @param CDLL -> CircularDoublyLinkedList to remove data
 * @param data -> data to be removed
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully removed;\n false if (CDLL == NULL || CDLL is empty || Data == NULL).
 */
size_t CircularDoublyLinkedList_remove_all(CircularDoublyLinkedList *CDLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to check its size
 * @return Number of elements in the CDLL;\n 0 if (CDLL == NULL or CDLL is empty).
 */
size_t CircularDoublyLinkedList_size(const CircularDoublyLinkedList *CDLL);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to get first element
 * @return The data (void *) of first CircularDoublyLinkedList node;\n NULL if (CDLL == NULL || CDLL is empty).
 */
void *CircularDoublyLinkedList_first_element(const CircularDoublyLinkedList *CDLL);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to get last element
 * @return The data (void *) of last CircularDoublyLinkedList node;\n NULL if (CDLL == NULL || CDLL is empty).
 */
void *CircularDoublyLinkedList_last_element(const CircularDoublyLinkedList *CDLL);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to get data from (index)th CircularDoublyLinkedList node
 * @param index -> index of data to be got
 * @return The data (void *) of (index)th CircularDoublyLinkedList node;\n NULL if (CDLL == NULL || CDLL is empty || index is out of bounds).
 */
void *CircularDoublyLinkedList_get(const CircularDoublyLinkedList *CDLL, const size_t index);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to count number os occurrences os data
 * @param data -> Data that the number of occurrences will be returned
 * @return The number of occurrences of data in the CDLL;\n 0 if (CDLL does not contain the Data || CDLL == NULL || CDLL is empty || Data == NULL).
 */
size_t CircularDoublyLinkedList_count(const CircularDoublyLinkedList *CDLL, void *data);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to check if data is contained
 * @param data -> Data that will be checked if it is contained in CircularDoublyLinkedList
 * @return true if CircularDoublyLinkedList contains the data;\n false if (CDLL does not contain the Data || CDLL == NULL || CDLL is empty || Data == NULL).
 */
bool CircularDoublyLinkedList_contains(const CircularDoublyLinkedList *CDLL, void *data);
/**
 * When calling this function it will insert data into (index)th CircularDoublyLinkedList node
 * @param CDLL -> CircularDoublyLinkedList add data
 * @param data -> Data to be added
 * @param index -> Index to add data at
 * @return true if: Data was successfully added;\n false if (CDLL == NULL || CDLL is empty || Data == NULL || index is out of bounds).

 */
bool CircularDoublyLinkedList_insert_at(CircularDoublyLinkedList *CDLL, void *data, const size_t index);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to be cloned
 * @return A clone of CDLL;\n NULL if (CDLL == NULL || CDLL is empty).
 */
CircularDoublyLinkedList *CircularDoublyLinkedList_clone(const CircularDoublyLinkedList *CDLL);
/**
 *
 * @param CDLL1 -> First CircularDoublyLinkedList to be concatenated
 * @param CDLL2 -> Second CircularDoublyLinkedList to be concatenated
 * @return A new CircularDoublyLinkedList with CDLL1 on begin and then the CDLL2;\n NULL if (CDLL1 == NULL || CDLL1 is empty || CDLL2 == NULL || CDLL2 is empty).
 */
CircularDoublyLinkedList *CircularDoublyLinkedList_concat(CircularDoublyLinkedList *CDLL1, CircularDoublyLinkedList *CDLL2);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to be reversed
 * @return A new CircularDoublyLinkedList with opposite order os original CDLL;\n NULL if (CDLL == NULL || CDLL is empty).
 */
bool CircularDoublyLinkedList_reverse(CircularDoublyLinkedList **CDLL_ref);
/**
 *
 * @param CDLL1 -> First CircularDoublyLinkedList to check equality
 * @param CDLL2 -> Second CircularDoublyLinkedList to check equality
 * @return true if CDLL1 === CDLL2;\n false if (CDLL1 !== CDLL2 || CDLL1 == NULL || CDLL1 is empty || CDLL2 == NULL || CDLL2 is empty).
 */
bool CircularDoublyLinkedList_is_equals_strict(const CircularDoublyLinkedList *CDLL1, const CircularDoublyLinkedList *CDLL2);
/**
 *
 * @param CDLL1 -> First CircularDoublyLinkedList to check equality
 * @param CDLL2 -> Second CircularDoublyLinkedList to check equality
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return rue if CDLL1 == CDLL2;\n false if (CDLL1 != CDLL2 || CDLL1 == NULL || CDLL1 is empty || CDLL2 == NULL || CDLL2 is empty).
 */
bool CircularDoublyLinkedList_is_equals(const CircularDoublyLinkedList *CDLL1, const CircularDoublyLinkedList *CDLL2, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will sort the CircularDoublyLinkedList in ascending order
 * @param CDLL_ref -> CircularDoublyLinkedList reference to sort in ascending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully sorted;\n false if (CDLL == NULL || CDLL is empty || Data == NULL).
 */
bool CircularDoublyLinkedList_sort_asc(CircularDoublyLinkedList **CDLL_ref, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will sort the CircularDoublyLinkedList in descending order
 * @param CDLL_ref -> CircularDoublyLinkedList reference to sort in descending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully sorted;\n false if (CDLL == NULL || CDLL is empty || Data == NULL).
 */
bool CircularDoublyLinkedList_sort_desc(CircularDoublyLinkedList **CDLL_ref, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will add data to CircularDoublyLinkedList following the order sort
 * @param CDLL -> CircularDoublyLinkedList to add data
 * @param data -> Data to be added
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully inserted;\n false if (CDLL == NULL || Data == NULL || CDLL is not sorted).
 */
bool CircularDoublyLinkedList_sorted_insert(CircularDoublyLinkedList *CDLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to get the smaller data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The smaller data in CDLL;\n NULL if (CDLL == NULL || CDLL is empty).
 */
void *CircularDoublyLinkedList_min(const CircularDoublyLinkedList *CDLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param CDLL -> CircularDoublyLinkedList to get the bigger data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The bigger data in CDLL;\n NULL if (CDLL == NULL || CDLL is empty).
 */
void *CircularDoublyLinkedList_max(const CircularDoublyLinkedList *CDLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__);

#endif