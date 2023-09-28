#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#ifdef SUPPRESS_PRINT_ERROR
    #undef SUPPRESS_PRINT_ERROR
#endif
#define SUPPRESS_PRINT_ERROR false
#define SIZE_OF_ARRAY_TYPE size_of_array_type

extern const size_t size_of_array_type;

/**
 * As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
 * 1 - Type printing function: To print data correctly.\n
 * 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
 * 3 - Type comparison function: To compare correctly data.
 */
typedef struct _array Array;
/**
 *
 * @param capacity -> max number of elements to be allocated
 * @param size_of_type -> size of data type to be allocated
 * @return A new Array of type and max number of elements equals to capacity
 */
Array *Array_create(long capacity, unsigned int size_of_type);
/**
 * When calling this function it will clean all data from Array;
 * @param array -> The array to be clean;
 */
bool Array_clean(Array *array);
/**
 * When calling this function, it will clean all data from Array and it will be deallocated;
 * @param array_ref -> The pointer of the Array to be deleted;
 */
bool Array_delete(Array **array_ref);
/**
 *
 * @param array -> Array to get the capacity;
 * @return The max number of elements of the Array.
 */
long Array_capacity(const Array *array);
/**
 *
 * @param array -> Array to check size;
 * @return Number of elements that are allocated in the Array.
 */
long Array_size(const Array *array);
/**
 *
 * @param array -> Array to check the sorting order;
 * @return -1 if: descending order;\n 0 if: not sorted;\n 1 if: ascending order.
 */
int Array_sort_order(const Array *array);
/**
 *
 * @param array -> Array to check emptiness;
 * @return true if: Array is empty (size == 0);\n false if: Array not empty (size > 0).
 */
bool Array_is_empty(void *array);
/**
 *
 * @param array -> Array to check the fullness;
 * @return true if: Array is full (size == capacity);\n false if: Array is not full (size <= capacity).
 */
bool Array_is_full(void *array);
/**
 *
 * @param array -> Array to check ordering;
 * @return true if: sort_order == +-1;\n false if sort_order == 0.
 */
bool Array_is_sorted(void *array);
/**
 * When calling this function it will add the data in first position;
 * @param array -> Array to add data;
 * @param data -> Data to be add in Array;
 */
bool Array_add_first(Array *array, void *data);
/**
 * When calling this function it will add the data in last position;
 * @param array -> Array to add data;
 * @param data -> Data to be add in Array;
 */
bool Array_add_last(Array *array, void *data);
/**
 *
 * @param array -> Array to get first element;
 * @return The first element of Array.
 */
void *Array_first_element(Array *array);
/**
 *
 * @param array -> Array to get last element;
 * @return The last element of Array.
 */
void *Array_last_element(Array *array);
/**
 * When calling this function it will remove the first element of Array;
 * @param array -> Array to remove first element;
 */
bool Array_remove_first(Array *array);
/**
 * When calling this function it will remove the last element of Array;
 * @param array -> Array to remove last element;
 */
bool Array_remove_last(Array *array);
/**
 * When calling this function it will remove the index-th element of Array;
 * @param array -> Array to remove index-th element;
 * @param index -> Index to remove data at
 */
bool Array_remove_at(Array *array, const long index);
/**
 * When calling this function it will remove the element in the Array
 * @param array -> Array to remove the element
 * @param data -> Element to be removed
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool Array_remove(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will remove all occurs of the element in the Array;
 * @param array -> Array to remove the element;
 * @param data -> Element to be removed;
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool Array_remove_all(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param array -> Array to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void Array_print(Array *array, void (*type_print_function)(void * data));
/**
 * When calling this function it will insert data into index-th Array index
 * @param array -> Array add data
 * @param data -> Data to be added
 * @param index -> Index to add data at
 */
bool Array_insert_at(Array *array, void *data, const long index);
/**
 * When calling this function it will update the data of index-th Array index
 * @param array -> Array update data
 * @param data -> Data to be set
 * @param index -> Index to update data at
 */
bool Array_set(Array *array, void *data, const long index);
/**
 *
 * @param array -> Array to get data from index-th Array index
 * @param index -> index of data to be got
 * @return The data (void *) of index-th Array index
 */
void *Array_get_at(Array *array, const long index);
/**
 *
 * @param array -> Array to be cloned
 * @return A clone of Array
 */
Array *Array_clone(Array *array);
/**
 *
 * @param array1 -> First Array to be concatenated
 * @param array2 -> Second Array to be concatenated
 * @return A new Array with array1 on begin and then the array2
 */
Array *Array_concat(Array *array1, Array *array2);
/**
 * @param array -> Array to be taken a sub-Array
 * @param first_index -> index tha will be the first index of the new array.
 * @param last_index -> index tha will be the last index of the new array.
 * @return A sub-Array of Array
 */
Array *Array_sub(Array *array, const long first_index, const long last_index);
/**
 *
 * @param array -> Array to be reversed
 * @return A new Array with opposite order of original Array
 */
Array *Array_reverse(Array *array);
/**
 *
 * @param array -> Array to check if data is contained
 * @param data -> Data that will be checked if it is contained in Array
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if Array contains the data, false otherwise
 */
bool Array_contains(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param array -> Array to count number os occurrences of data
 * @param data -> Data that the number of occurrences will be returned
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The number of occurrences of data in the Array
 */
long Array_count(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param array1 -> First Array to check equality
 * @param array2 -> Second Array to check equality
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if array1 == array2;\n false if array1 != array2
 */
bool Array_is_equals(Array *array1, Array *array2, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param array -> Array to find index of data
 * @param data -> Data to find the first index
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return First index of Data in Array, if does not exist it will return -1
 */
long Array_index_of(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param array -> Array to find index of data
 * @param data -> Data to find the last index
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return Last index of Data in Array, if does not exist it will return -1
 */
long Array_last_index_of(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will sort the Array in ascending order
 * @param array -> Array to sort in ascending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool Array_sort_asc(Array *array, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will sort the Array in descending order
 * @param array -> Array to sort in descending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool Array_sort_desc(Array *array, int (*type_compare_function)(void *data1, void *data2));
/**
 * When calling this function it will add data to Array following the order sort
 * @param array -> Array to add data
 * @param data -> Data to be added
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 */
bool Array_sorted_insert(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param array -> Array to get the smaller data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The smaller data in Array
 */
void *Array_min(Array *array, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param array -> Array to get the bigger data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The bigger data in Array
 */
void *Array_max(Array *array, int (*type_compare_function)(void *data1, void *data2));

#endif