#ifndef ARRAY_H
#define ARRAY_H
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
#define __DEFAULT_LONG__ -1
#define __DEFAULT_BOOL__ false
#define __NOT_DEFAULT_BOOL__ true
#define __DEFAULT_PTR__ NULL
#define __TYPE_COMPARE_FUNCTION_NAME__ type_compare_func
#define __TYPE_COMPARE_FUNCTION_SIGNATURE__ int (*__TYPE_COMPARE_FUNCTION_NAME__)(void *data1, void *data2)
#define __TYPE_PRINT_FUNCTION_NAME__ type_print_func
#define __TYPE_PRINT_FUNCTION_SIGNATURE__ void (*__TYPE_PRINT_FUNCTION_NAME__)(void *data)

#define SIZE_OF_ARRAY_TYPE size_of_array_type

extern const size_t size_of_array_type;

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
typedef struct _array Array;
/**
 *
 * @param capacity -> max number of elements to be allocated
 * @param size_of_type -> size of data type to be allocated
 * @return If capacity > 0, a new Array of type and max number of elements equals to capacity.\n NULL: Otherwise.
 */
Array *Array_create(long capacity, unsigned int size_of_type);
/**
 * When calling this function it will clean all data from Array;
 * @param array -> The array to be clean;
 * @return true if: Array was successfully cleaned;\n false if (Array == NULL).
 */
bool Array_clean(Array *array);
/**
 * When calling this function, it will clean all data from Array and it will be deallocated;
 * @param array_ref -> The pointer of the Array to be deleted;
 * @return true if: Array was successfully deleted;\n false if (Array == NULL).
 */
bool Array_delete(Array **array_ref);
/**
 *
 * @param array -> Array to get the capacity;
 * @return The max number of elements of the Array;\n -1 if Array == NULL.
 */
long Array_capacity(const Array *array);
/**
 *
 * @param array -> Array to check size;
 * @return Number of elements that are allocated in the Array;\n -1 if Array == NULL.
 */
long Array_size(const Array *array);
/**
 *
 * @param array -> Array to check the sorting order;
 * @return -1 if: descending order;\n 0 if: not sorted or Array == NULL;\n 1 if: ascending order.
 */
int Array_sort_order(const Array *array);
/**
 *
 * @param array -> Array to check emptiness;
 * @return true if: Array is empty (size == 0) or Array == NULL;\n false if: Array not empty (size > 0).
 */
bool Array_is_empty(void *array);
/**
 *
 * @param array -> Array to check the fullness;
 * @return true if: Array is full (size == capacity);\n false if: Array is not full (size \<= capacity) or Array == NULL.
 */
bool Array_is_full(void *array);
/**
 *
 * @param array -> Array to check ordering;
 * @return true if: sort_order == +-1;\n false if sort_order == 0 or Array == NULL.
 */
bool Array_is_sorted(void *array);
/**
 * When calling this function it will add the data in first position;
 * @param array -> Array to add data;
 * @param data -> Data to be add in Array;
 * @return true if: Data was successfully added;\n false if (Array == NULL || Array is full || Data == NULL).
 */
bool Array_add_first(Array *array, void *data);
/**
 * When calling this function it will add the data in last position;
 * @param array -> Array to add data;
 * @param data -> Data to be add in Array;
 * @return true if: Data was successfully added;\n false if (Array == NULL || Array is full || Data == NULL).
 */
bool Array_add_last(Array *array, void *data);
/**
 *
 * @param array -> Array to get first element;
 * @return The first element of Array;\n NULL if Array == NULL or Array is empty.
 */
void *Array_first_element(Array *array);
/**
 *
 * @param array -> Array to get last element;
 * @return The last element of Array;\n NULL if Array == NULL or Array is empty.
 */
void *Array_last_element(Array *array);
/**
 * When calling this function it will remove the first element of Array;
 * @param array -> Array to remove first element;
 * @return true if: Data was successfully removed;\n false if (Array == NULL || Array is empty).
 */
bool Array_remove_first(Array *array);
/**
 * When calling this function it will remove the last element of Array;
 * @param array -> Array to remove last element;
 * @return true if: Data was successfully removed;\n false if (Array == NULL || Array is empty).
 */
bool Array_remove_last(Array *array);
/**
 * When calling this function it will remove the index-th element of Array;
 * @param array -> Array to remove index-th element;
 * @param index -> Index to remove data at
 * @return true if: Data was successfully removed;\n false if (Array == NULL || Array is empty || index is out of bounds).
 */
bool Array_remove_at(Array *array, const long index);
/**
 * When calling this function it will remove the element in the Array
 * @param array -> Array to remove the element
 * @param data -> Element to be removed
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully removed;\n false if (Array == NULL || Array is empty || Data == NULL).
 */
bool Array_remove(Array *array, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will remove all occurs of the element in the Array;
 * @param array -> Array to remove the element;
 * @param data -> Element to be removed;
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully removed;\n false if (Array == NULL || Array is empty || Data == NULL).
 */
bool Array_remove_all(Array *array, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param array -> Array to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void Array_print(Array *array, __TYPE_PRINT_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will insert data into index-th Array index
 * @param array -> Array add data
 * @param data -> Data to be added
 * @param index -> Index to add data at
 * @return true if: Data was successfully added;\n false if (Array == NULL || Array is empty || Data == NULL || index is out of bounds || Array is full).
 */
bool Array_insert_at(Array *array, void *data, const long index);
/**
 * When calling this function it will update the data of index-th Array index
 * @param array -> Array update data
 * @param data -> Data to be set
 * @param index -> Index to update data at
 * @return true if: Data was successfully set;\n false if (Array == NULL || Array is empty || Data == NULL || index is out of bounds).
 */
bool Array_set(Array *array, void *data, const long index);
/**
 *
 * @param array -> Array to get data from index-th Array index
 * @param index -> index of data to be got
 * @return The data (void *) of index-th Array index;\n NULL if (Array == NULL || Array is empty || index is out of bounds).
 */
void *Array_get_at(Array *array, const long index);
/**
 *
 * @param array -> Array to be cloned
 * @return A clone of Array;\n NULL if (Array == NULL || Array is empty).
 */
Array *Array_clone(Array *array);
/**
 *
 * @param array1 -> First Array to be concatenated
 * @param array2 -> Second Array to be concatenated
 * @return A new Array with array1 on begin and then the array2;\n NULL if (array1 == NULL || array1 is empty || array2 == NULL || array2 is empty).
 */
Array *Array_concat(Array *array1, Array *array2);
/**
 * @param array -> Array to be taken a sub-Array
 * @param first_index -> index tha will be the first index of the new array.
 * @param last_index -> index tha will be the last index of the new array.
 * @return A sub-Array of Array;\n NULL if (Array == NULL || Array is empty || first index is out of bounds || last index is out of bounds).
 */
Array *Array_sub(Array *array, const long first_index, const long last_index);
/**
 *
 * @param array -> Array to be reversed
 * @return A new Array with opposite order of original Array;\n NULL if (Array == NULL || Array is empty).
 */
Array *Array_reverse(Array *array);
/**
 *
 * @param array -> Array to check if data is contained
 * @param data -> Data that will be checked if it is contained in Array
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if Array contains the data;\n false if (Array does not contain the Data || Array == NULL || Array is empty || Data == NULL).
 */
bool Array_contains(Array *array, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param array -> Array to count number os occurrences of data
 * @param data -> Data that the number of occurrences will be returned
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The number of occurrences of data in the Array;\n -1 if (Array does not contain the Data || Array == NULL || Array is empty || Data == NULL).
 */
long Array_count(Array *array, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param array1 -> First Array to check equality
 * @param array2 -> Second Array to check equality
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if array1 == array2;\n false if (array1 == NULL || array1 is empty || array2 == NULL || array2 is empty).
 */
bool Array_is_equals(Array *array1, Array *array2, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param array -> Array to find index of data
 * @param data -> Data to find the first index
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return First index of Data in Array;\n -1 if (Array does not contain the Data || Array == NULL || Array is empty || Data == NULL).
 */
long Array_index_of(Array *array, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param array -> Array to find index of data
 * @param data -> Data to find the last index
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return Last index of Data in Array;\n -1 if (Array does not contain the Data || Array == NULL || Array is empty || Data == NULL).
 */
long Array_last_index_of(Array *array, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will sort the Array in ascending order
 * @param array -> Array to sort in ascending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully sorted;\n false if (Array == NULL || Array is empty || Data == NULL).
 */
bool Array_sort_asc(Array *array, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will sort the Array in descending order
 * @param array -> Array to sort in descending order
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully sorted;\n false if (Array == NULL || Array is empty || Data == NULL).
 */
bool Array_sort_desc(Array *array, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 * When calling this function it will add data to Array following the order sort
 * @param array -> Array to add data
 * @param data -> Data to be added
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if: Data was successfully inserted;\n false if (Array == NULL || Array is full || Data == NULL || Array is not sorted).
 */
bool Array_sorted_insert(Array *array, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param array -> Array to get the smaller data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The smaller data in Array;\n NULL if (Array == NULL || Array is empty).
 */
void *Array_min(Array *array, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param array -> Array to get the bigger data
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The bigger data in Array;\n NULL if (Array == NULL || Array is empty).
 */
void *Array_max(Array *array, __TYPE_COMPARE_FUNCTION_SIGNATURE__);

#endif