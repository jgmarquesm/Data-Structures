#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#--ADD_TO_INCLUDE
#include "../include/array.h"

#define UNSORTED 0
#define ASC 1
#define DESC -1

typedef struct _array{
    char *data;
    long capacity;
    long size;
    int sort_order;
    int size_of_type;
} Array;

void *_get(const Array *array, const long index) {
    return array->data + (index * array->size_of_type);
}

void _array_sorted_merge(Array *array, long first_index, long mid_index, long last_index, int (*type_compare_function)(void *data1, void *data2), int sort_order) {
    long left_capacity = mid_index - first_index + 1;
    long right_capacity = last_index - mid_index;

    Array *left = Array_create(left_capacity, array->size_of_type);
    Array *right = Array_create(right_capacity, array->size_of_type);

    for (long i = 0; i < left_capacity; i++) {
        void *dest = _get(left, i);
        void *src = _get(array, first_index + i);
        memcpy(dest, src, array->size_of_type);
    }
    for (long j = 0; j < right_capacity; j++) {
        void *dest = _get(right, j);
        void *src = _get(array, mid_index + j + 1);
        memcpy(dest, src, array->size_of_type);
    }

    long i = 0, j = 0, k = first_index;
    void *array_index = NULL;

    while (i < left_capacity && j < right_capacity) {
        void *left_data = _get(left, i);
        void *right_data = _get(right, j);
        array_index = Array_get_at(array, k);
        if (sort_order == ASC) {
            if (type_compare_function(left_data, right_data) >= 0) {
                memcpy(array_index, left_data, array->size_of_type);
                i++;
            } else {
                memcpy(array_index, right_data, array->size_of_type);
                j++;
            }
        } else if (sort_order == DESC) {
            if (type_compare_function(left_data, right_data) <= 0) {
                memcpy(array_index, left_data, array->size_of_type);
                i++;
            } else {
                memcpy(array_index, right_data, array->size_of_type);
                j++;
            }
        }
        k++;
    }

    while (i < left_capacity) {
        array_index = _get(array, k);
        void *left_index = _get(left, i);
        memcpy(array_index, left_index, array->size_of_type);
        i++, k++;
    }
    while (j < right_capacity) {
        array_index = _get(array, k);
        void *right_index = _get(right, j);
        memcpy(array_index, right_index, array->size_of_type);
        j++, k++;
    }
}

void _array_merge_sort(Array *array, long first_index, long last_index, int (*type_compare_function)(void *data1, void *data2), int sort_order) {
    if (first_index < last_index) {
        long mid_index = first_index + (last_index - first_index) / 2;
        _array_merge_sort(array, first_index, mid_index, type_compare_function, sort_order);
        _array_merge_sort(array, mid_index + 1, last_index, type_compare_function, sort_order);
        _array_sorted_merge(array, first_index, mid_index, last_index, type_compare_function, sort_order);
    }
}

Array *Array_create(long capacity, unsigned int size_of_type) {
    if (anyThrows(
            1,
            ExceptionHandler_is_non_positive("Array_create", "Capacity", capacity, false, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Array *array = (Array *) calloc(1, sizeof(Array));
    char *data = (char *) calloc(capacity, size_of_type);
    array->data = data;
    array->capacity = capacity;
    array->size = 0;
    array->sort_order = UNSORTED;
    array->size_of_type = size_of_type;
    return array;
}

bool Array_clean(Array *array) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Array_clean", "Array", (void *) array, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->sort_order = UNSORTED;
    array->size_of_type = 0;
    return true;
}

bool Array_delete(Array **array_ref) {
    Array *array = *array_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Array_delete", "Array", (void *) array, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Array_clean(array);
    free(array);
    *array_ref= NULL;
    return true;
}

long Array_capacity(const Array *array) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Array_capacity", "Array", (void *) array, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    return array->capacity;
}

long Array_size(const Array *array) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Array_size", "Array", (void *) array, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    return array->size;
}

int Array_sort_order(const Array *array) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Array_sort_order", "Array", (void *) array, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    return array->sort_order;
}

bool Array_is_empty(void *array) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Array_is_empty", "Array", array, SUPPRESS_PRINT_ERROR)
        )
    ) return true;
    return ((Array *) array)->size == 0;
}

bool Array_is_full(void *array) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Array_is_full", "Array", array, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    return ((Array *) array)->size == ((Array *) array)->capacity;
}

bool Array_is_sorted(void *array) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Array_is_sorted", "Array", (void *) array, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    return ((Array *) array)->sort_order == ASC || ((Array *) array)->sort_order == DESC;
}

bool Array_add_first(Array *array, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Array_add_first", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_full("Array_add_first", "Array", (void *) array, Array_is_full, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_add_first", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    for (int i = array->size; i >= 0; i--) {
        void *index_dest_ptr = array->data + ((i + 1) * array->size_of_type);
        void *index_src_ptr = array->data + (i * array->size_of_type);
        memcpy(index_dest_ptr, index_src_ptr, sizeof(array->size_of_type));
    }
    void *index_ptr = _get(array, 0);
    memcpy(index_ptr, data, sizeof(array->size_of_type));
    array->sort_order = UNSORTED;
    array->size++;
    return true;
}

bool Array_add_last(Array *array, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Array_add_last", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_full("Array_add_last", "Array", (void *) array, Array_is_full, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_add_last", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    void *index_ptr = _get(array, array->size);
    memcpy(index_ptr, data, sizeof(array->size_of_type));
    array->sort_order = UNSORTED;
    array->size++;
    return true;
}

void *Array_first_element(Array *array) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_first_element", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_first_element", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return Array_get_at(array, 0);
}

void *Array_last_element(Array *array) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_last_element", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_last_element", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return Array_get_at(array, array->size - 1);
}

bool Array_remove_first(Array *array) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_remove_first", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_remove_first", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    for (int i = 1; i <= array->size; i++) {
        void *index_dest_ptr = _get(array, i - 1);
        void *index_src_ptr = _get(array, i);
        memcpy(index_dest_ptr, index_src_ptr, sizeof(array->size_of_type));
    }
    array->size--;
    return true;
}

bool Array_remove_last(Array *array) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_remove_last", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_remove_last", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    array->size--;
    return true;
}

bool Array_remove_at(Array *array, const long index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_remove_at", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_remove_at", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        ) || anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("Array_remove_at", "Index", index, array->size-1, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    long range = array->size;
    for (int i = index; i <= range; i++) {
        void *index_dest_ptr = _get(array, i);
        void *index_src_ptr = _get(array, i + 1);
        memcpy(index_dest_ptr, index_src_ptr, sizeof(array->size_of_type));
    }
    array->size--;
    return true;
}

bool Array_remove(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Array_remove", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_remove", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_remove", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    long range = array->size;
    for (int i = 0; i <= range; i++) {
        void *ith_data = _get(array, i);
        if (type_compare_function(data, ith_data) == 0) {
            Array_remove_at(array, i);
            return true;
        }
    }
    return false;
}

bool Array_remove_all(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Array_remove_all", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_remove_all", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_remove_all", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    long range = array->size;
    int count = 0;
    for (int i = 0; i <= range; i++) {
        void *ith_data = _get(array, i);
        if (type_compare_function(data, ith_data) == 0) {
            array->size = range;
            Array_remove_at(array, i);
            count++;
        }
    }
    array->size -= count;
    return count > 0;
}

void Array_print(Array *array, void (*type_print_function)(void * data)) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Array_print", "Array", (void *) array, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    printf("[");
    for(long i = 0; i < array->size-1; i++) {
        void *data = Array_get_at(array, i);
        type_print_function(data);
        printf(", ");
    }
    type_print_function(Array_get_at(array, array->size-1));
    puts("]");
}

bool Array_insert_at(Array *array, void *data, const long index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Array_insert_at", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_insert_at", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_full("Array_insert_at", "Array", (void *) array, Array_is_full, SUPPRESS_PRINT_ERROR)
        ) || anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("Array_insert_at", "Index", index, array->size, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    for (int i = array->size; i >= index; i--) {
        void *index_dest_ptr = array->data + ((i + 1) * array->size_of_type);
        void *index_src_ptr = array->data + (i * array->size_of_type);
        memcpy(index_dest_ptr, index_src_ptr, sizeof(array->size_of_type));
    }
    void *ith_data = _get(array, index);
    memcpy(ith_data, data, array->size_of_type);
    array->sort_order = UNSORTED;
    array->size++;
    return true;
}

bool Array_set(Array *array, void *data, const long index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_set", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_set", "Data", data, SUPPRESS_PRINT_ERROR)
        ) || anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("Array_set", "Index", index, array->size-1, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    void *ith_data = _get(array, index);
    memcpy(ith_data, data, array->size_of_type);
    array->sort_order = UNSORTED;
    return true;
}

void *Array_get_at(Array *array, const long index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_get_at", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_get_at", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        ) || anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("Array_get_at", "Index", index, array->size-1, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return _get(array, index);
}

Array *Array_clone(Array *array) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_clone", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_clone", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Array *clone = Array_create(array->capacity, array->size_of_type);
    for (int i = 0; i < array->size; i++) {
        void *data = Array_get_at(array, i);
        Array_add_last(clone, data);
    }
    clone->sort_order = array->sort_order;
    return clone;
}

Array *Array_concat(Array *array1, Array *array2) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("Array_concat", "Array1", (void *) array1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_concat", "Array2", (void *) array2, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_concat", "Array1", (void *) array1, Array_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_concat", "Array2", (void *) array2, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    long capacity = array1->capacity+array2->capacity;
    Array *concat = Array_create(capacity, array1->size_of_type);
    for (int i = 0; i < array1->size; i++) {
        void *data = Array_get_at(array1, i);
        Array_add_last(concat, data);
    }
    for (int j = 0; j < array2->size; j++) {
        void *data = Array_get_at(array2, j);
        Array_add_last(concat, data);
    }
    return concat;
}

Array *Array_sub(Array *array, const long initial_index, const long final_index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_sub", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_sub", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        ) || anyThrows(
            2,
            ExceptionHandler_is_out_of_bounds("Array_sub", "Final index", final_index, array->size-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Array_sub", "Initial index", initial_index, final_index-1, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    long capacity = final_index - initial_index;
    Array *sub = Array_create(capacity, array->size_of_type);
    for (int i = initial_index; i < final_index; i++) {
        void *data = Array_get_at(array, i);
        Array_add_last(sub, data);
    }
    sub->sort_order = array->sort_order;
    return sub;
}

Array *Array_reverse(Array *array) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_reverse", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_reverse", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Array *reverse = Array_create(array->capacity, array->size_of_type);
    for (int i = (array->size - 1); i >= 0; i--) {
        void *data = Array_get_at(array, i);
        Array_add_last(reverse, data);
    }
    reverse->sort_order = (-1)*array->sort_order;
    return reverse;
}

bool Array_contains(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Array_contains", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_contains", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_contains", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    for (int i = 0; i < array->size; i++) {
        void *ith_data = Array_get_at(array, i);
        if (type_compare_function(ith_data, data) == 0) {
            return true;
        }
    }
    return false;
}

long Array_count(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Array_count", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_count", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_count", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    long count = 0;
    for (int i = 0; i < array->size; i++) {
        void *ith_data = Array_get_at(array, i);
        if (type_compare_function(ith_data, data) == 0) {
            count++;
        }
    }
    return count;
}

bool Array_is_equals(Array *array1, Array *array2, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("Array_is_equals", "Array1", (void *) array1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_is_equals", "Array2", (void *) array2, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_is_equals", "Array1", (void *) array1, Array_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_is_equals", "Array2", (void *) array2, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    if (array1->size_of_type != array2->size_of_type) {
        return false;
    }
    if (array1->size != array2->size) {
        return false;
    }
    if (array1->sort_order != array2->sort_order) {
        return false;
    }
    for (int i = 0; i < array1->size; i++) {
        void *data1 = Array_get_at(array1, i);
        void *data2 = Array_get_at(array2, i);
        if (type_compare_function(data1 ,data2) != 0) {
            return false;
        }
    }
    return true;
}

long Array_index_of(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Array_index_of", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_index_of", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_index_of", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    for (int i = 0; i < array->size; i++) {
        void *ith_data = Array_get_at(array, i);
        if (type_compare_function(ith_data ,data) == 0) {
            return i;
        }
    }
    return -1;
}

long Array_last_index_of(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_last_index_of", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Array_last_index_of", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_last_index_of", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return -1;
    for (int i = (array->size - 1); i >= 0; i--) {
        void *ith_data = Array_get_at(array, i);
        if (type_compare_function(ith_data ,data) == 0) {
            return i;
        }
    }
    return -1;
}

bool Array_sort_asc(Array *array, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_sort_asc", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_sort_asc", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    if (array->sort_order == DESC) {
        Array *reverse = Array_reverse(array);
        array->data = reverse->data;
        array->sort_order = reverse->sort_order;
        return true;
    }
    _array_merge_sort(array, 0, array->size-1, type_compare_function, 1);
    array->sort_order = ASC;
    return true;
}

bool Array_sort_desc(Array *array, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_sort_desc", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_sort_desc", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    if (array->sort_order == ASC) {
        Array *reverse = Array_reverse(array);
        array->data = reverse->data;
        array->sort_order = DESC;
        return true;
    }
    _array_merge_sort(array, 0, array->size-1, type_compare_function, -1);
    array->sort_order = DESC;
    return true;
}

bool Array_sorted_insert(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Array_sorted_insert", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_full("Array_sorted_insert", "Array", (void *) array, Array_is_full, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_not_sorted("Array_sorted_insert", "Array", (void *) array, Array_is_sorted, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    void *array_data = Array_get_at(array, array->size - 1);
    int sort_order = array->sort_order, compare = type_compare_function(data, array_data);

    if ((sort_order == ASC && compare < 0)) {
        Array_add_last(array, data);
        array->sort_order = ASC;
        return true;
    }
    if ((sort_order == DESC && compare > 0)) {
        Array_add_last(array, data);
        array->sort_order = DESC;
        return true;
    }

    for (long i = 0; i < array->size; i++) {
        array_data = Array_get_at(array, i);
        compare = type_compare_function(data, array_data);

        if (sort_order == ASC) {
            if (compare > 0) {
                Array_insert_at(array, data, i);
                array->sort_order = ASC;
                return true;
            }
        } else {
            if (compare < 0) {
                Array_insert_at(array, data, i);
                array->sort_order = DESC;
                return true;
            }
        }
    }
    return false;
}

void *Array_min(Array *array, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_min", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_min", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;

    if (Array_is_sorted(array)) {
        if (array->sort_order == ASC) {
            return Array_get_at(array, 0);
        } else {
            return Array_get_at(array, array->size - 1);
        }
    }

    Array *clone = Array_clone(array);
    Array_sort_asc(clone, type_compare_function);
    void *data = Array_get_at(clone, 0);
    return data;
}

void *Array_max(Array *array, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Array_max", "Array", (void *) array, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Array_max", "Array", (void *) array, Array_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;

    if (Array_is_sorted(array)) {
        if (array->sort_order == ASC) {
            return Array_get_at(array, array->size - 1);
        } else {
            return Array_get_at(array, 0);
        }
    }

    Array *clone = Array_clone(array);
    Array_sort_asc(clone, type_compare_function);
    void *data = Array_get_at(clone, array->size - 1);
    return data;
}
