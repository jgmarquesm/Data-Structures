#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

/**
 * As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
 * 1 - Type printing function: To print data correctly.\n
 * 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
 * 3 - Type comparison function: To compare correctly data.
 */
typedef struct _linked_list DoublyLinkedList, LinkedList;
/**
 *
 * @return a new LinkedList (empty)
 */
LinkedList *LinkedList_create();
/**
 * This function is responsible for clearing all data from a LinkedList. After calling this function, all data era
 * erased and the the LinkedList is empty.
 * @param LL -> The (Doubly))LinkedList to clean up
 */
void LinkedList_clean(LinkedList *LL);
/**
 * When calling this function it will clean up and free all nodes and free the DoublyLinkedList.
 * @param LL_ref -> The DoublyLinkedList reference
 */
void LinkedList_destroy(LinkedList **LL_ref);
/**
 *
 * @param LL -> The LinkedList to verify if is empty
 * @return true if the LinkedList is empty and false otherwise
 */
bool LinkedList_is_empty(const LinkedList *LL);
/**
 *
 * @param LL -> The LinkedLIst to verify if is sorted
 * @return true if the LinkedList is sorted and false otherwise.
 */
bool LinkedList_is_sorted(const LinkedList *LL);
/**
 *
 * @param LL -> The LinkedLIst to verify sort order
 * @return -1 if descending sort;\n 0 if unsorted;\n 1 if ascending sort.
 */
int LinkedList_sort_order(const LinkedList *LL);
/**
 *
 * @param LL -> DoublyLinkedList to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void LinkedList_print(const LinkedList *LL, void (*type_print_function)(void *data));
/**
 * When calling this functions it will add data to the first LinkedList node.
 * @param LL -> LinkedList to add data
 * @param data -> data to be added.
 */
void LinkedList_add_first(LinkedList *LL, void *data);
/**
 * When calling this functions it will add data to the last LinkedList node.
 * @param LL -> LinkedList to add data
 * @param data -> data to be added.
 */
void LinkedList_add_last(LinkedList *LL, void *data);
/**
 * When calling this function it will remove first node of LinkedList.
 * @param LL -> LinkedList to remove data
 * @return The data of the removed node in the LinkedList.
 */
void *LinkedList_remove_first(LinkedList *LL);
/**
 * When calling this function it will remove last node of LinkedList.
 * @param LL -> LinkedList to remove data
 * @return The data of the removed node in the LinkedList.
 */
void *LinkedList_remove_last(LinkedList *LL);
/**
 * When calling this function it will remove index-th node of LinkedList.
 * @param LL -> LinkedList to remove data
 * @param index -> Index to remove data at
 * @return The data of the removed node in the LinkedList.
 */
void *LinkedList_remove_at(LinkedList *LL, const size_t index);
/**
 * When calling this function it will remove first occurrence of data in the LinkedList.
 * @param LL -> LinkedList to remove data
 * @param data -> data to be removed
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
void LinkedList_remove(LinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will remove all occurrences of data in the LinkedList.
 * @param LL -> LinkedList to remove data
 * @param data -> data to be removed
  * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
void LinkedList_remove_all(LinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param LL -> LinkedList to check its size
 * @return Number of elements in the LinkedList
 */
size_t LinkedList_size(const LinkedList *LL);
/**
 *
 * @param LL -> LinkedList to get first element
 * @return The data (void *) of first LinkedList node
 */
void *LinkedList_first_element(const LinkedList *LL);
/**
 *
 * @param LL -> LinkedList to get last element
 * @return The data (void *) of last LinkedList node
 */
void *LinkedList_last_element(const LinkedList *LL);
/**
 *
 * @param LL -> LinkedList to get data from (index)th LinkedList node
 * @param index -> index of data to be got
 * @return The data (void *) of (index)th LinkedList node
 */
void *LinkedList_get(const LinkedList *LL, const size_t index);
/**
 *
 * @param LL -> LinkedList to count number os occurrences os data
 * @param data -> Data that the number of occurrences will be returned
 * @return The number of occurrences of data in the LinkedList
 */
int LinkedList_count(const LinkedList *LL, void *data);
/**
 *
 * @param LL -> LinkedList to check if data is contained
 * @param data -> Data that will be checked if it is contained in LinkedList
 * @return true if LinkedList contains the data, false otherwise
 */
bool LinkedList_contains(const LinkedList *LL, void *data);

/**
 * When calling this function it will insert data into (index)th LinkedList node
 * @param LL -> LinkedList add data
 * @param data -> Data to be added
 * @param index -> Index to add data at
 */
void LinkedList_insert_at(LinkedList *LL, void *data, const size_t index);
/**
 *
 * @param LL -> LinkedList to be cloned
 * @return A clone of LinkedList
 */
LinkedList *LinkedList_clone(const LinkedList *LL);
/**
 *
 * @param LL1 -> First LinkedList to be concatenated
 * @param LL2 -> Second LinkedList to be concatenated
 * @return A new LinkedList with LL1 on begin and then the LL2
 */
LinkedList *LinkedList_concat(LinkedList *LL1, LinkedList *LL2);
/**
 *
 * @param LL -> LinkedList to be reversed
 * @return A new LinkedList with opposite order os original LinkedList
 */
LinkedList *LinkedList_reverse(LinkedList *LL);
/**
 *
 * @param LL1 -> First LinkedList to check equality
 * @param LL2 -> Second LinkedList to check equality
 * @return true if LL1 === LL2;\n false if LL1 !== LL2
 */
bool LinkedList_is_equals_strict(const LinkedList *LL1, const LinkedList *LL2);
/**
 *
 * @param LL1 -> First LinkedList to check equality
 * @param LL2 -> Second LinkedList to check equality
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return rue if LL1 == LL2;\n false if LL1 != LL2
 */
bool LinkedList_is_equals(const LinkedList *LL1, const LinkedList *LL2, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will sort the LinkedList in ascending order
 * @param LL -> LinkedList to sort in ascending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
void LinkedList_sort_asc(LinkedList *LL, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will sort the LinkedList in descending order
 * @param LL -> LinkedList to sort in descending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
void LinkedList_sort_desc(LinkedList *LL, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will add data to LinkedList following the order sort
 * @param LL -> LinkedList to add data
 * @param data -> Data to be added
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
void LinkedList_sorted_insert(LinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param LL -> LinkedList to get the smaller data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The smaller data in LinkedList
 */
void *LinkedList_min(const LinkedList *LL, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param LL -> LinkedList to get the bigger data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The bigger data in LinkedList
 */
void *LinkedList_max(const LinkedList *LL, int (*type_compare_function)(void *data1, void *data2));

#endif