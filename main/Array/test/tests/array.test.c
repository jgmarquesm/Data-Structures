#include "../../main/include/unity.h"
#include "../../main/include/array.h"

void setUp(){}

void tearDown(){}

int _convert_to_int(void *data) {
    return *((int *) data);
}

void _print_int(void *data) {
    printf("%d", _convert_to_int(data));
}

int _compare_int(void *data1, void *data2) {
    int d1 = _convert_to_int(data1), d2 = _convert_to_int(data2);
    return d2 - d1;
}

// Array_create(capacity, size_of_type)
void test_1() {
    TEST_MESSAGE("Test: Array_create(capacity, size_of_type): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    bool is_empty = Array_is_empty(array);
    TEST_ASSERT_EQUAL(1, is_empty);
    TEST_ASSERT_EQUAL(0, Array_size(array));
    TEST_ASSERT_EQUAL(0, Array_is_sorted(array));
    TEST_ASSERT_EQUAL(0, Array_sort_order(array));
}

// Array_clean(array)
void test_2() {
    TEST_MESSAGE("Test: Array_clean(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_first(array, &data1);
    Array_add_first(array, &data2);
    Array_add_last(array, &data2);
    Array_add_last(array, &data2);
    Array_add_last(array, &data2);

    Array_clean(array);
    TEST_ASSERT_EQUAL(1, Array_is_empty(array));
    TEST_ASSERT_EQUAL(0, Array_size(array));
}

// Array_delete(&array)
void test_3() {
    TEST_MESSAGE("Test: Array_delete(&array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_first(array, &data1);
    Array_add_first(array, &data2);
    Array_add_last(array, &data2);
    Array_add_last(array, &data2);
    Array_add_last(array, &data2);

    Array_delete(&array);
    TEST_ASSERT_EQUAL(NULL, array);
}

// Array_capacity(array)
void test_4() {
    TEST_MESSAGE("Test: Array_capacity(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    TEST_ASSERT_EQUAL(capacity, Array_capacity(array));
}

// Array_size(array)
void test_5() {
    TEST_MESSAGE("Test: Array_size(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42;
    int data2 = 99;
    Array_add_first(array, &data1);
    Array_add_last(array, &data2);
    TEST_ASSERT_EQUAL(2, Array_size(array));
}

// Array_sort_order(array)
void test_6() {
    TEST_MESSAGE("Test: Array_sort_order(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);
    Array_add_last(array, &data4);
    TEST_ASSERT_EQUAL(0, Array_sort_order(array));
    Array_sort_asc(array, _compare_int);
    TEST_ASSERT_EQUAL(1, Array_sort_order(array));
    Array_sort_desc(array, _compare_int);
    TEST_ASSERT_EQUAL(-1, Array_sort_order(array));
    Array_add_first(array, &data3);
    TEST_ASSERT_EQUAL(0, Array_sort_order(array));
}

// Array_is_empty(array)
void test_7() {
    TEST_MESSAGE("Test: Array_is_empty(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, Array_is_empty(array));
    TEST_ASSERT_EQUAL(0, Array_size(array));
    Array_add_first(array, &data1);
    Array_add_first(array, &data2);
    TEST_ASSERT_EQUAL(0, Array_is_empty(array));
    TEST_ASSERT_EQUAL(2, Array_size(array));
}

// Array_is_full(array)
void test_8() {
    TEST_MESSAGE("Test: Array_is_full(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_first(array, &data1);
    Array_add_first(array, &data2);
    TEST_ASSERT_EQUAL(0, Array_is_full(array));
    TEST_ASSERT_EQUAL(1, Array_capacity(array) != Array_size(array));
    Array_add_first(array, &data1);
    Array_add_first(array, &data2);
    Array_add_first(array, &data2);
    TEST_ASSERT_EQUAL(1, Array_is_full(array));
    TEST_ASSERT_EQUAL(Array_capacity(array), Array_size(array));
}

// Array_is_sorted(array)
void test_9() {
    TEST_MESSAGE("Test: Array_is_sorted(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);
    Array_add_last(array, &data4);
    TEST_ASSERT_EQUAL(0, Array_is_sorted(array));
    Array_sort_asc(array, _compare_int);
    TEST_ASSERT_EQUAL(1, Array_is_sorted(array));
    Array_sort_desc(array, _compare_int);
    TEST_ASSERT_EQUAL(1, Array_is_sorted(array));
    Array_add_first(array, &data3);
    TEST_ASSERT_EQUAL(0, Array_is_sorted(array));
    Array_sort_desc(array, _compare_int);
    TEST_ASSERT_EQUAL(1, Array_is_sorted(array));
}

// Array_add_first(array)
void test_10() {
    TEST_MESSAGE("Test: Array_add_first(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_first(array, &data1);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_first_element(array)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_last_element(array)));
    Array_add_first(array, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_first_element(array)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_last_element(array)));
    TEST_ASSERT_EQUAL(0,  Array_sort_order(array));
}

// Array_add_last(array)
void test_11() {
    TEST_MESSAGE("Test: Array_add_last(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_last(array, &data1);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_first_element(array)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_last_element(array)));
    Array_add_last(array, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_first_element(array)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_last_element(array)));
    TEST_ASSERT_EQUAL(0,  Array_sort_order(array));
}

// Array_first_element(array)
void test_12() {
    TEST_MESSAGE("Test: Array_first_element(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_first(array, &data1);
    Array_add_first(array, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_first_element(array)));
}

// Array_last_element(array)
void test_13() {
    TEST_MESSAGE("Test: Array_last_element(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_last_element(array)));
}

// Array_remove_first(array)
void test_14() {
    TEST_MESSAGE("Test: Array_remove_first(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data0 = 42, data1 = 99, data2 = 55;
    Array_add_last(array, &data0);
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);

    size_t size_before = Array_size(array);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Array_get_at(array, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_get_at(array, 1)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_get_at(array, 2)));

    Array_remove_first(array);
    size_t size_after = Array_size(array);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, Array_contains(array, &data0, _compare_int));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_get_at(array, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_get_at(array, 1)));
}

// Array_remove_last(array)
void test_15() {
    TEST_MESSAGE("Test: Array_remove_last(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data0 = 42, data1 = 99, data2 = 55;
    Array_add_last(array, &data0);
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);

    size_t size_before = Array_size(array);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Array_get_at(array, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_get_at(array, 1)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_get_at(array, 2)));

    Array_remove_last(array);
    size_t size_after = Array_size(array);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, Array_contains(array, &data2, _compare_int));
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Array_get_at(array, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_get_at(array, 1)));
}

// Array_remove_at(array, index)
void test_16() {
    TEST_MESSAGE("Test: Array_remove_at(array, index): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data0 = 42, data1 = 99, data2 = 55;
    Array_add_last(array, &data0);
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);

    size_t size_before = Array_size(array);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Array_get_at(array, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_get_at(array, 1)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_get_at(array, 2)));

    Array_remove_at(array, 1);
    size_t size_after = Array_size(array);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, Array_contains(array, &data1, _compare_int));
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Array_get_at(array, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_get_at(array, 1)));
}

// Array_remove(array, data, type_compare_func)
void test_17() {
    TEST_MESSAGE("Test: Array_remove(array, data, type_compare_func): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_first(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data2);
    Array_add_first(array, &data2);
    Array_add_last(array, &data2);

    TEST_ASSERT_EQUAL(5, Array_size(array));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_get_at(array, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_get_at(array, 1)));

    Array_remove(array, &data1, _compare_int);
    TEST_ASSERT_EQUAL(4, Array_size(array));
    TEST_ASSERT_EQUAL(0, Array_contains(array, &data1, _compare_int));
}

// Array_remove_all(array, data, type_compare_func)
void test_18() {
    TEST_MESSAGE("Test: Array_remove_all(array, data, type_compare_func): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = 99, data4 = 55;
    Array_add_first(array, &data1);
    Array_add_first(array, &data4);
    Array_add_last(array, &data2);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);

    Array_remove_all(array, &data2, _compare_int);
    TEST_ASSERT_EQUAL(1, Array_contains(array, &data1, _compare_int));
    TEST_ASSERT_EQUAL(0, Array_contains(array, &data2, _compare_int));
    TEST_ASSERT_EQUAL(0, Array_contains(array, &data3, _compare_int));
    TEST_ASSERT_EQUAL(1, Array_contains(array, &data4, _compare_int));
    TEST_ASSERT_EQUAL(2, Array_size(array));
}

// Array_insert_at(array, data, index)
void test_19() {
    TEST_MESSAGE("Test: Array_insert_at(array, data, index): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data0 = 357, data3 = -761, data6 = 4242;
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);

    Array_insert_at(array, &data0, 0);
    TEST_ASSERT_EQUAL(3, Array_size(array));
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Array_get_at(array, 0)));

    Array_insert_at(array, &data3, 3);
    TEST_ASSERT_EQUAL(4, Array_size(array));
    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Array_get_at(array, 3)));

    Array_insert_at(array, &data6, 4);
    TEST_ASSERT_EQUAL(5, Array_size(array));
    TEST_ASSERT_EQUAL(_convert_to_int(&data6), _convert_to_int(Array_get_at(array, 4)));

    TEST_ASSERT_EQUAL(0, Array_is_sorted(array));
}

// Array_set(array, data, index)
void test_20() {
    TEST_MESSAGE("Test: Array_set(array, data, index): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data0 = 357, data3 = -761, data6 = 4242;
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);
    Array_add_last(array, &data6);

    TEST_ASSERT_EQUAL(4, Array_size(array));
    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Array_get_at(array, 2)));

    Array_set(array, &data0, 2);
    TEST_ASSERT_EQUAL(4, Array_size(array));
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Array_get_at(array, 2)));

    TEST_ASSERT_EQUAL(0, Array_is_sorted(array));
}

// Array_get_at(array, index)
void test_21() {
    TEST_MESSAGE("Test: Array_get_at(array, index): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_first(array, &data1);
    Array_add_first(array, &data2);
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    size_t index = Array_size(array) - 1;
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_get_at(array, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_get_at(array, index)));
}

// Consistence between Array_first_element(array) && Array_get_at(array, 0)
void test_22() {
    TEST_MESSAGE("Test: Consistence between Array_first_element(array) && Array_get_at(array, 0): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_first(array, &data1);
    Array_add_first(array, &data2);
    TEST_ASSERT_EQUAL(Array_get_at(array, 0), Array_first_element(array));
}

// Consistence between Array_last_element(array) && Array_get_at(array, size-1)
void test_23() {
    TEST_MESSAGE("Test: Consistence between Array_last_element(array) && Array_get_at(array, size-1): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    size_t index = Array_size(array) - 1;
    TEST_ASSERT_EQUAL(Array_get_at(array, index), Array_last_element(array));
}

// Array_clone(array)
void test_24() {
    TEST_MESSAGE("Test: Array_clone(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);
    Array_add_last(array, &data4);

    Array *clone = Array_clone(array);

    TEST_ASSERT_EQUAL(Array_size(clone), Array_size(array));
    TEST_ASSERT_EQUAL(Array_is_sorted(clone), Array_is_sorted(array));
    TEST_ASSERT_EQUAL(Array_sort_order(clone), Array_sort_order(array));
    TEST_ASSERT_EQUAL(_convert_to_int(Array_first_element(clone)), _convert_to_int(Array_first_element(array)));
    TEST_ASSERT_EQUAL(_convert_to_int(Array_get_at(clone, 2)), _convert_to_int(Array_get_at(array, 2)));
    TEST_ASSERT_EQUAL(_convert_to_int(Array_last_element(clone)), _convert_to_int(Array_last_element(array)));
}

// Array_concat(array1, array2)
void test_25() {
    TEST_MESSAGE("Test: Array_concat(array1, array2): ");
    long capacity1 = 5;
    long capacity2 = 3;
    int size_of_type = sizeof(int);
    Array *array1 = Array_create(capacity1, size_of_type);
    Array *array2 = Array_create(capacity2, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    Array_add_last(array1, &data1);
    Array_add_last(array1, &data2);
    Array_add_last(array2, &data3);
    Array_add_last(array2, &data4);

    Array *array_new = Array_concat(array1, array2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Array_first_element(array_new)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data4), _convert_to_int(Array_last_element(array_new)));
    TEST_ASSERT_EQUAL(capacity1 + capacity2, Array_capacity(array_new));

    Array *array_new2 = Array_concat(array2, array1);
    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Array_first_element(array_new2)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_last_element(array_new2)));
    TEST_ASSERT_EQUAL(capacity2 + capacity1, Array_capacity(array_new2));
}

// Array_sub(array, initial_index, final_index)
void test_26() {
    TEST_MESSAGE("Test: Array_sub(array, initial_index, final_index): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    long initial_index = 1;
    long final_index = 4;
    long sub_capacity = final_index - initial_index;
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data1);
    Array_add_last(array, &data4);
    Array_add_last(array, &data3);

    Array *sub_array = Array_sub(array, initial_index, final_index);
    TEST_ASSERT_EQUAL(_convert_to_int(Array_get_at(array, initial_index)), _convert_to_int(Array_get_at(sub_array, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(Array_get_at(array, final_index-1)), _convert_to_int(Array_get_at(sub_array, Array_size(sub_array) - 1)));
    TEST_ASSERT_EQUAL(sub_capacity, Array_capacity(sub_array));
    TEST_ASSERT_EQUAL(Array_size(sub_array), Array_capacity(sub_array));
}

// Array_reverse(array)
void test_27() {
    TEST_MESSAGE("Test: Array_reverse(array): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);
    Array_add_last(array, &data4);

    Array *array_reverse = Array_reverse(array);
    TEST_ASSERT_EQUAL(_convert_to_int(Array_first_element(array)), _convert_to_int(Array_last_element(array_reverse)));
    TEST_ASSERT_EQUAL(_convert_to_int(Array_last_element(array)), _convert_to_int(Array_first_element(array_reverse)));
    TEST_ASSERT_EQUAL(Array_sort_order(array), (-1)*Array_sort_order(array_reverse));
}

// Array_contains(array, data, _compare_int)
void test_28() {
    TEST_MESSAGE("Test: Array_contains(array, data, _compare_int): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = 55;
    Array_add_first(array, &data1);
    Array_add_first(array, &data2);
    TEST_ASSERT_EQUAL(1, Array_contains(array, &data2, _compare_int));
    TEST_ASSERT_EQUAL(0, Array_contains(array, &data3, _compare_int));
}

// Array_count(array, data, _compare_int)
void test_29() {
    TEST_MESSAGE("Test: Array_count(array, data, _compare_int): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99;
    Array_add_first(array, &data1);
    Array_add_first(array, &data2);
    Array_add_last(array, &data2);
    Array_add_last(array, &data2);
    Array_add_first(array, &data2);
    int count = Array_count(array, &data2, _compare_int);
    TEST_ASSERT_EQUAL(4, count);
}

// Array_is_equals(array1, array2, _compare_func)
void test_30() {
    TEST_MESSAGE("Test: Array_is_equals(array1, array2, _compare_func): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array1 = Array_create(capacity, size_of_type);
    Array *array2 = Array_create(capacity, size_of_type);
    Array *array3 = Array_create(capacity, size_of_type);
    Array *array4 = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    int data5 = 42, data6 = 99, data7 = -1, data8 = 10;

    Array_add_last(array1, &data1);
    Array_add_last(array1, &data2);
    Array_add_last(array1, &data3);
    Array_add_last(array1, &data4);

    Array_add_last(array2, &data1);
    Array_add_last(array2, &data2);
    Array_add_last(array2, &data3);
    Array_add_last(array2, &data4);

    Array_add_last(array3, &data2);
    Array_add_last(array3, &data3);
    Array_add_last(array3, &data4);

    Array_add_last(array4, &data5);
    Array_add_last(array4, &data6);
    Array_add_last(array4, &data7);
    Array_add_last(array4, &data8);

    TEST_ASSERT_EQUAL(1, Array_is_equals(array1, array2, _compare_int));
    TEST_ASSERT_EQUAL(0, Array_is_equals(array1, array3, _compare_int));
    TEST_ASSERT_EQUAL(1, Array_is_equals(array1, array4, _compare_int));
    TEST_ASSERT_EQUAL(0, Array_is_equals(array2, array3, _compare_int));
    TEST_ASSERT_EQUAL(1, Array_is_equals(array3, array3, _compare_int));
}

// Array_index_of(array, data, _compare_func)
void test_31() {
    TEST_MESSAGE("Test: Array_index_of(array, data, _compare_func): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10, data5 = 1000;

    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);
    Array_add_last(array, &data4);

    TEST_ASSERT_EQUAL(-1, Array_index_of(array, &data5, _compare_int));
    TEST_ASSERT_EQUAL(0, Array_index_of(array, &data1, _compare_int));
    TEST_ASSERT_EQUAL(1, Array_index_of(array, &data2, _compare_int));
    TEST_ASSERT_EQUAL(2, Array_index_of(array, &data3, _compare_int));
    TEST_ASSERT_EQUAL(3, Array_index_of(array, &data4, _compare_int));
}

// Array_last_index_of(array, data, _compare_func)
void test_32() {
    TEST_MESSAGE("Test: Array_last_index_of(array, data, _compare_func): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1;

    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data1);
    Array_add_last(array, &data2);

    TEST_ASSERT_EQUAL(-1, Array_last_index_of(array, &data3, _compare_int));
    TEST_ASSERT_EQUAL(2, Array_last_index_of(array, &data1, _compare_int));
    TEST_ASSERT_EQUAL(3, Array_last_index_of(array, &data2, _compare_int));
}

// Array_sort_asc(array, _compare_func)
void test_33() {
    TEST_MESSAGE("Test: Array_sort_asc(array, _compare_func): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);
    Array_add_last(array, &data4);

    TEST_ASSERT_EQUAL(0, Array_is_sorted(array));
    TEST_ASSERT_EQUAL(0, Array_sort_order(array));

    Array_sort_asc(array, _compare_int);
    TEST_ASSERT_EQUAL(1, Array_is_sorted(array));
    TEST_ASSERT_EQUAL(1, Array_sort_order(array));
    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Array_first_element(array)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_last_element(array)));
}

// Array_sort_desc(array, _compare_func)
void test_34() {
    TEST_MESSAGE("Test: Array_sort_desc(array, _compare_func): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);
    Array_add_last(array, &data4);

    TEST_ASSERT_EQUAL(0, Array_is_sorted(array));
    TEST_ASSERT_EQUAL(0, Array_sort_order(array));

    Array_sort_desc(array, _compare_int);
    TEST_ASSERT_EQUAL(1, Array_is_sorted(array));
    TEST_ASSERT_EQUAL(-1, Array_sort_order(array));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_first_element(array)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Array_last_element(array)));
}

// Array_sorted_insert(array, _compare_func, data)
void test_35() {
    TEST_MESSAGE("Test: Array_sorted_insert(array, _compare_func, data): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data0 = -35, data3 = 29, data6 = 888;

    Array_add_last(array, &data1);
    Array_add_last(array, &data2);

    Array_sort_asc(array, _compare_int);

    Array_sorted_insert(array, &data0, _compare_int);
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Array_get_at(array, 0)));
    Array_sorted_insert(array, &data3, _compare_int);
    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Array_get_at(array, 1)));
    Array_sorted_insert(array, &data6, _compare_int);
    TEST_ASSERT_EQUAL(_convert_to_int(&data6), _convert_to_int(Array_get_at(array, 4)));
}

// Array_min(array, _compare_func)
void test_36() {
    TEST_MESSAGE("Test: Array_min(array, _compare_func): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);
    Array_add_last(array, &data4);

    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Array_min(array, _compare_int)));
    Array_sort_desc(array, _compare_int);
    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Array_min(array, _compare_int)));
    Array_sort_asc(array, _compare_int);
    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Array_min(array, _compare_int)));
}

// Array_max(array, _compare_func)
void test_37() {
    TEST_MESSAGE("Test: Array_max(array, _compare_func): ");
    long capacity = 5;
    int size_of_type = sizeof(int);
    Array *array = Array_create(capacity, size_of_type);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    Array_add_last(array, &data1);
    Array_add_last(array, &data2);
    Array_add_last(array, &data3);
    Array_add_last(array, &data4);

    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_max(array, _compare_int)));
    Array_sort_desc(array, _compare_int);
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_max(array, _compare_int)));
    Array_sort_asc(array, _compare_int);
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Array_max(array, _compare_int)));
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);
    RUN_TEST(test_4);
    RUN_TEST(test_5);
    RUN_TEST(test_6);
    RUN_TEST(test_7);
    RUN_TEST(test_8);
    RUN_TEST(test_9);
    RUN_TEST(test_10);
    RUN_TEST(test_11);
    RUN_TEST(test_12);
    RUN_TEST(test_13);
    RUN_TEST(test_14);
    RUN_TEST(test_15);
    RUN_TEST(test_16);
    RUN_TEST(test_17);
    RUN_TEST(test_18);
    RUN_TEST(test_19);
    RUN_TEST(test_20);
    RUN_TEST(test_21);
    RUN_TEST(test_22);
    RUN_TEST(test_23);
    RUN_TEST(test_24);
    RUN_TEST(test_25);
    RUN_TEST(test_26);
    RUN_TEST(test_27);
    RUN_TEST(test_28);
    RUN_TEST(test_29);
    RUN_TEST(test_30);
    RUN_TEST(test_31);
    RUN_TEST(test_32);
    RUN_TEST(test_33);
    RUN_TEST(test_34);
    RUN_TEST(test_35);
    RUN_TEST(test_36);
    RUN_TEST(test_37);
    return UNITY_END();
}
