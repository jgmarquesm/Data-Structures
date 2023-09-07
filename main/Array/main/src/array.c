#include "../include/array.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#--ADD_TO_INCLUDE

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
    if (capacity <= 0) {
        fprintf(stderr, "\nERROR: on function 'Array_create'.\n");
        fprintf(stderr, "ERROR: capacity must be greater then 0. Current value: %ld.\n", capacity);
        exit(EXIT_FAILURE);
    }
    Array *array = (Array *) calloc(1, sizeof(Array));
    char *data = (char *) calloc(capacity, size_of_type);
    array->data = data;
    array->capacity = capacity;
    array->size = 0;
    array->sort_order = UNSORTED;
    array->size_of_type = size_of_type;
    return array;
}

void Array_clean(Array *array) {
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->sort_order = UNSORTED;
    array->size_of_type = 0;
}

void Array_delete(Array **array_ref) {
    Array *array = *array_ref;
    Array_clean(array);
    free(array);
    *array_ref= NULL;
}

long Array_capacity(const Array *array) {
    return array->capacity;
}

long Array_size(const Array *array) {
    return array->size;
}

int Array_sort_order(const Array *array) {
    return array->sort_order;
}

bool Array_is_empty(const Array *array) {
    return array->size == 0;
}

bool Array_is_full(const Array *array) {
    return array->size == array->capacity;
}

bool Array_is_sorted(const Array *array) {
    return array->sort_order == ASC || array->sort_order == DESC;
}

void Array_add_first(Array *array, void *data) {
    if (Array_is_full(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_add_first'.\n");
        fprintf(stderr, "ERROR: Array is full.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = array->size; i >= 0; i--) {
        void *index_dest_ptr = array->data + ((i + 1) * array->size_of_type);
        void *index_src_ptr = array->data + (i * array->size_of_type);
        memcpy(index_dest_ptr, index_src_ptr, sizeof(array->size_of_type));
    }
    void *index_ptr = _get(array, 0);
    memcpy(index_ptr, data, sizeof(array->size_of_type));
    array->sort_order = UNSORTED;
    array->size++;
}

void Array_add_last(Array *array, void *data) {
    if (Array_is_full(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_add_last'.\n");
        fprintf(stderr, "ERROR: Array is full.\n");
        exit(EXIT_FAILURE);
    }
    void *index_ptr = _get(array, array->size);
    memcpy(index_ptr, data, sizeof(array->size_of_type));
    array->sort_order = UNSORTED;
    array->size++;
}

void *Array_first_element(const Array *array) {
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_first_element'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_first_element'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    return Array_get_at(array, 0);
}

void *Array_last_element(const Array *array) {
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_last_element'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_last_element'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    return Array_get_at(array, array->size - 1);
}

void Array_remove_first(Array *array) {
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_remove_first'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_remove_first'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= array->size; i++) {
        void *index_dest_ptr = _get(array, i - 1);
        void *index_src_ptr = _get(array, i);
        memcpy(index_dest_ptr, index_src_ptr, sizeof(array->size_of_type));
    }
    array->size--;
}

void Array_remove_last(Array *array) {
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_remove_last'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_remove_last'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    array->size--;
}

void Array_remove_at(Array *array, const long index) {
    if (index >= array->size || index < 0) {
        fprintf(stderr, "\nERROR: on function 'Array_remove_at'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %ld. Try an index within [0, %ld].\n", index, array->size - 1);
        exit(EXIT_FAILURE);
    }
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_remove_at'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_remove_at'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    long range = array->size;
    for (int i = index; i <= range; i++) {
        void *index_dest_ptr = _get(array, i);
        void *index_src_ptr = _get(array, i + 1);
        memcpy(index_dest_ptr, index_src_ptr, sizeof(array->size_of_type));
    }
    array->size--;
}

void Array_remove(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    long range = array->size;
    for (int i = 0; i <= range; i++) {
        void *ith_data = _get(array, i);
        if (type_compare_function(data, ith_data) == 0) {
            Array_remove_at(array, i);
            return;
        }
    }
}

void Array_remove_all(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
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
}

void Array_print(const Array *array, void (*type_print_function)(void * data)) {
    printf("[");
    for(long i = 0; i < array->size-1; i++) {
        void *data = Array_get_at(array, i);
        type_print_function(data);
        printf(", ");
    }
    type_print_function(Array_get_at(array, array->size-1));
    puts("]");
}

void Array_insert_at(Array *array, void *data, const long index) {
    if (Array_is_full(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_insert_at'.\n");
        fprintf(stderr, "ERROR: Array is full.\n");
        exit(EXIT_FAILURE);
    }
    if (index > array->size || index < 0) {
        fprintf(stderr, "\nERROR: on function 'Array_insert_at'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %ld. Try an index within [0, %ld].\n", index, array->size);
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_insert_at'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = array->size; i >= index; i--) {
        void *index_dest_ptr = array->data + ((i + 1) * array->size_of_type);
        void *index_src_ptr = array->data + (i * array->size_of_type);
        memcpy(index_dest_ptr, index_src_ptr, sizeof(array->size_of_type));
    }
    void *ith_data = _get(array, index);
    memcpy(ith_data, data, array->size_of_type);
    array->sort_order = UNSORTED;
    array->size++;
}

void Array_set(Array *array, void *data, const long index) {
    if (index > array->size || index < 0) {
        fprintf(stderr, "\nERROR: on function 'Array_set'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %ld. Try an index within [0, %ld].\n", index, array->size);
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_set'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    void *ith_data = _get(array, index);
    memcpy(ith_data, data, array->size_of_type);
    array->sort_order = UNSORTED;
}

void *Array_get_at(const Array *array, const long index) {
    if (index >= array->size || index < 0) {
        fprintf(stderr, "\nERROR: on function 'Array_get_at'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %ld. Try an index within [0, %ld].\n", index, array->size - 1);
        exit(EXIT_FAILURE);
    }
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_get_at'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_get_at'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    return _get(array, index);
}

Array *Array_clone(const Array *array) {
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_clone'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_clone'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    Array *clone = Array_create(array->capacity, array->size_of_type);
    for (int i = 0; i < array->size; i++) {
        void *data = Array_get_at(array, i);
        Array_add_last(clone, data);
    }
    clone->sort_order = array->sort_order;
    return clone;
}

Array *Array_concat(const Array *array1, const Array *array2) {
    if (Array_is_empty(array1) && Array_is_empty(array2)) {
        fprintf(stderr, "\nERROR: on function 'Array_concat'.\n");
        fprintf(stderr, "ERROR: Arrays are empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array1 == NULL || array2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_concat'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
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

Array *Array_sub(const Array *array, const long initial_index, const long final_index) {
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_sub'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_sub'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (initial_index >= final_index) {
        fprintf(stderr, "\nERROR: on function 'Array_sub'.\n");
        fprintf(stderr, "ERROR: initial_index_index greater or equal than final_index: %ld >= %ld.\n", initial_index, final_index);
        exit(EXIT_FAILURE);
    }
    if (initial_index < 0) {
        fprintf(stderr, "\nERROR: on function 'Array_sub'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %ld. Try an index within [0, %ld].\n", initial_index, array->size - 2);
        exit(EXIT_FAILURE);
    }
    if (final_index >= array->size) {
        fprintf(stderr, "\nERROR: on function 'Array_sub'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %ld. Try an index within [1, %ld].\n", final_index, array->size - 1);
        exit(EXIT_FAILURE);
    }
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
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_reverse'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_reverse'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    Array *reverse = Array_create(array->capacity, array->size_of_type);
    for (int i = (array->size - 1); i >= 0; i--) {
        void *data = Array_get_at(array, i);
        Array_add_last(reverse, data);
    }
    reverse->sort_order = (-1)*array->sort_order;
    return reverse;
}

bool Array_contains(const Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_contains'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (Array_is_empty(array)) {
        return false;
    }
    for (int i = 0; i < array->size; i++) {
        void *ith_data = Array_get_at(array, i);
        if (type_compare_function(ith_data, data) == 0) {
            return true;
        }
    }
    return false;
}

long Array_count(const Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_count'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (Array_is_empty(array)) {
        return 0;
    }
    long count = 0;
    for (int i = 0; i < array->size; i++) {
        void *ith_data = Array_get_at(array, i);
        if (type_compare_function(ith_data, data) == 0) {
            count++;
        }
    }
    return count;
}

bool Array_is_equals(const Array *array1, Array *array2, int (*type_compare_function)(void *data1, void *data2)) {
    if (array1 == NULL || array2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_equals'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (Array_is_empty(array1) || Array_is_empty(array2)) {
        fprintf(stderr, "\nERROR: on function 'Array_equals'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
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

long Array_index_of(const Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_index_of'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_index_of'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < array->size; i++) {
        void *ith_data = Array_get_at(array, i);
        if (type_compare_function(ith_data ,data) == 0) {
            return i;
        }
    }
    return -1;
}

long Array_last_index_of(const Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_index_of'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_index_of'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = (array->size - 1); i >= 0; i--) {
        void *ith_data = Array_get_at(array, i);
        if (type_compare_function(ith_data ,data) == 0) {
            return i;
        }
    }
    return -1;
}

void Array_sort_asc(Array *array, int (*type_compare_function)(void *data1, void *data2)) {
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_sort_asc'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_sort_asc'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (array->sort_order == DESC) {
        Array *reverse = Array_reverse(array);
        array->data = reverse->data;
        array->sort_order = reverse->sort_order;
        return;
    }
    _array_merge_sort(array, 0, array->size-1, type_compare_function, 1);
    array->sort_order = ASC;
}

void Array_sort_desc(Array *array, int (*type_compare_function)(void *data1, void *data2)) {
    if (Array_is_empty(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_sort_desc'.\n");
        fprintf(stderr, "ERROR: Array is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_sort_desc'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (array->sort_order == ASC) {
        Array *reverse = Array_reverse(array);
        array->data = reverse->data;
        array->sort_order = DESC;
        return;
    }
    _array_merge_sort(array, 0, array->size-1, type_compare_function, -1);
    array->sort_order = DESC;
}

void Array_sorted_insert(Array *array, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (Array_is_full(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_sorted_insert'.\n");
        fprintf(stderr, "ERROR: Array is full.\n");
        exit(EXIT_FAILURE);
    }
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_sorted_insert'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (!Array_is_sorted(array)) {
        fprintf(stderr, "\nERROR: on function 'Array_sorted_insert'.\n");
        fprintf(stderr, "ERROR: Array must be sorted.\n");
        exit(EXIT_FAILURE);
    }

    void *array_data = Array_get_at(array, array->size - 1);
    int sort_order = array->sort_order, compare = type_compare_function(data, array_data);

    if ((sort_order == ASC && compare < 0)) {
        Array_add_last(array, data);
        array->sort_order = ASC;
        return;
    }
    if ((sort_order == DESC && compare > 0)) {
        Array_add_last(array, data);
        array->sort_order = DESC;
        return;
    }

    for (long i = 0; i < array->size; i++) {
        array_data = Array_get_at(array, i);
        compare = type_compare_function(data, array_data);

        if (sort_order == ASC) {
            if (compare > 0) {
                Array_insert_at(array, data, i);
                array->sort_order = ASC;
                return;
            }
        } else {
            if (compare < 0) {
                Array_insert_at(array, data, i);
                array->sort_order = DESC;
                return;
            }
        }
    }
}

void *Array_min(const Array *array, int (*type_compare_function)(void *data1, void *data2)) {
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_min'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }

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

void *Array_max(const Array *array, int (*type_compare_function)(void *data1, void *data2)) {
    if (array == NULL) {
        fprintf(stderr, "\nERROR: on function 'Array_max'.\n");
        fprintf(stderr, "ERROR: Array is NULL.\n");
        exit(EXIT_FAILURE);
    }

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
