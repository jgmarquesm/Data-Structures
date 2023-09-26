#include "../../main/include/unity.h"
#include "../../main/include/array.h"

#define CAPACITY 5
#define SIZE 3
#define TYPE int

void setUp(){}

void tearDown(){}

TYPE _convert_to_TYPE(void *data) {
    return *((TYPE *) data);
}

TYPE _compare_TYPE(void *data1, void *data2) {
    TYPE d1 = _convert_to_TYPE(data1), d2 = _convert_to_TYPE(data2);
    return d2 - d1;
}

void test_Array_create_1() {
    TEST_MESSAGE("Case 1 --> Positive Capacity:");
    Array *array = NULL;
    TEST_ASSERT_EQUAL(NULL, array);

    array = Array_create(CAPACITY, sizeof(TYPE));
    TEST_ASSERT_NOT_EQUAL(NULL, array);

    long capacity = Array_capacity(array);
    TEST_ASSERT_EQUAL(CAPACITY, capacity);

    long size = Array_size(array);
    TEST_ASSERT_EQUAL(0, size);
}

void test_Array_create_2() {
    TEST_MESSAGE("Case 2 --> Negative Capacity:");
    Array *array = NULL;
    TEST_ASSERT_EQUAL(NULL, array);

    array = Array_create(-CAPACITY, sizeof(TYPE));
    TEST_ASSERT_EQUAL(NULL, array);
}

void test_Array_create_3() {
    TEST_MESSAGE("Case 3 --> Capacity equals to 0:");
    Array *array = NULL;
    TEST_ASSERT_EQUAL(NULL, array);

    array = Array_create(0, sizeof(TYPE));
    TEST_ASSERT_EQUAL(NULL, array);
}

void test_Array_clean_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool cleaned = Array_clean(array);
    TEST_ASSERT_EQUAL(true, cleaned);
}

void test_Array_clean_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    bool cleaned = Array_clean(array);
    TEST_ASSERT_EQUAL(false, cleaned);
}

void test_Array_delete_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool deleted = Array_delete(&array);
    TEST_ASSERT_EQUAL(true, deleted);
    TEST_ASSERT_EQUAL(NULL, array);
}

void test_Array_delete_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    bool deleted = Array_delete(&array);
    TEST_ASSERT_EQUAL(false, deleted);
}

void test_Array_capacity_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    long capacity = Array_capacity(array);
    TEST_ASSERT_EQUAL(CAPACITY, capacity);
}

void test_Array_capacity_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    long capacity = Array_capacity(array);
    TEST_ASSERT_EQUAL(-1, capacity);
}

void test_Array_size_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < SIZE; i++) {
        Array_add_first(array, &i);
    }

    long size = Array_size(array);
    TEST_ASSERT_EQUAL(SIZE, size);
}

void test_Array_size_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    long size = Array_size(array);
    TEST_ASSERT_EQUAL(-1, size);
}

void test_Array_sort_order_1() {
    TEST_MESSAGE("Case 1 --> Non Null Unsorted Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    int sort_order = Array_sort_order(array);
    TEST_ASSERT_EQUAL(0, sort_order);
}

void test_Array_sort_order_2() {
    TEST_MESSAGE("Case 2 --> Non Null ASC Sorted Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < SIZE; i++) {
        Array_add_first(array, &i);
    }
    Array_sort_asc(array, _compare_TYPE);

    int sort_order = Array_sort_order(array);
    TEST_ASSERT_EQUAL(1, sort_order);
}

void test_Array_sort_order_3() {
    TEST_MESSAGE("Case 3 --> Non Null DESC Sorted Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < SIZE; i++) {
        Array_add_first(array, &i);
    }
    Array_sort_desc(array, _compare_TYPE);


    int sort_order = Array_sort_order(array);
    TEST_ASSERT_EQUAL(-1, sort_order);
}

void test_Array_sort_order_4() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    int sort_order = Array_sort_order(array);
    TEST_ASSERT_EQUAL(0, sort_order);
}

void test_Array_is_empty_1() {
    TEST_MESSAGE("Case 1 --> Non Null Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool empty = Array_is_empty(array);
    TEST_ASSERT_EQUAL(true, empty);
}

void test_Array_is_empty_2() {
    TEST_MESSAGE("Case 2 --> Non Null Not Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < SIZE; i++) {
        Array_add_first(array, &i);
    }

    bool empty = Array_is_empty(array);
    TEST_ASSERT_EQUAL(false, empty);
}

void test_Array_is_empty_3() {
    TEST_MESSAGE("Case 3 --> Null Array:");
    Array *array = NULL;

    bool empty = Array_is_empty(array);
    TEST_ASSERT_EQUAL(true, empty);
}

void test_Array_is_full_1() {
    TEST_MESSAGE("Case 1 --> Non Null Full Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < CAPACITY; i++) {
        Array_add_first(array, &i);
    }

    bool full = Array_is_full(array);
    TEST_ASSERT_EQUAL(true, full);
}

void test_Array_is_full_2() {
    TEST_MESSAGE("Case 2 --> Non Null Not Full Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool full = Array_is_full(array);
    TEST_ASSERT_EQUAL(false, full);
}

void test_Array_is_full_3() {
    TEST_MESSAGE("Case 3 --> Null Array:");
    Array *array = NULL;

    bool full = Array_is_full(array);
    TEST_ASSERT_EQUAL(false, full);
}

void test_Array_is_sorted_1() {
    TEST_MESSAGE("Case 1 --> Non Null Unsorted Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    int is_sorted = Array_is_sorted(array);
    TEST_ASSERT_EQUAL(false, is_sorted);
}

void test_Array_is_sorted_2() {
    TEST_MESSAGE("Case 2 --> Non Null ASC Sorted Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < SIZE; i++) {
        Array_add_first(array, &i);
    }
    Array_sort_asc(array, _compare_TYPE);

    int is_sorted = Array_is_sorted(array);
    TEST_ASSERT_EQUAL(true, is_sorted);
}

void test_Array_is_sorted_3() {
    TEST_MESSAGE("Case 3 --> Non Null DESC Sorted Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < SIZE; i++) {
        Array_add_first(array, &i);
    }
    Array_sort_desc(array, _compare_TYPE);


    int is_sorted = Array_is_sorted(array);
    TEST_ASSERT_EQUAL(true, is_sorted);
}

void test_Array_is_sorted_4() {
    TEST_MESSAGE("Case 4 --> Null Array:");
    Array *array = NULL;

    int is_sorted = Array_is_sorted(array);
    TEST_ASSERT_EQUAL(false, is_sorted);
}

void test_Array_add_first_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    TYPE d1 = 1, d2 = 2;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool added_first = Array_add_first(array, &d1);
    TYPE *first_element = (TYPE *) Array_first_element(array);
    TEST_ASSERT_EQUAL(true, added_first);
    TEST_ASSERT_EQUAL(d1, *first_element);

    Array_add_first(array, &d2);
    TYPE *new_first_element = (TYPE *) Array_first_element(array);
    TEST_ASSERT_EQUAL(d2, *new_first_element);
}

void test_Array_add_first_2() {
    TEST_MESSAGE("Case 2 --> Non Null but Full Array:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < CAPACITY; i++) {
        Array_add_first(array, &i);
    }

    bool added_first = Array_add_first(array, &d1);
    TEST_ASSERT_EQUAL(false, added_first);
}

void test_Array_add_first_3() {
    TEST_MESSAGE("Case 3 --> Non Null Array, but Null data:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool added_first = Array_add_first(array, NULL);
    TEST_ASSERT_EQUAL(false, added_first);
}

void test_Array_add_first_4() {
    TEST_MESSAGE("Case 4 --> Null Array:");
    TYPE d1;
    Array *array = NULL;

    bool added_first = Array_add_first(array, &d1);
    TEST_ASSERT_EQUAL(false, added_first);
}

void test_Array_add_last_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    TYPE d1 = 1, d2 = 2;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool added_last = Array_add_last(array, &d1);
    TYPE *last_element = (TYPE *) Array_last_element(array);
    TEST_ASSERT_EQUAL(true, added_last);
    TEST_ASSERT_EQUAL(d1, *last_element);

    Array_add_last(array, &d2);
    TYPE *new_last_element = (TYPE *) Array_last_element(array);
    TEST_ASSERT_EQUAL(d2, *new_last_element);
}

void test_Array_add_last_2() {
    TEST_MESSAGE("Case 2 --> Non Null but Full Array:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < CAPACITY; i++) {
        Array_add_last(array, &i);
    }

    bool added_last = Array_add_last(array, &d1);
    TEST_ASSERT_EQUAL(false, added_last);
}

void test_Array_add_last_3() {
    TEST_MESSAGE("Case 3 --> Non Null Array, but Null data:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool added_last = Array_add_last(array, NULL);
    TEST_ASSERT_EQUAL(false, added_last);
}

void test_Array_add_last_4() {
    TEST_MESSAGE("Case 4 --> Null Array:");
    TYPE d1;
    Array *array = NULL;

    bool added_last = Array_add_last(array, &d1);
    TEST_ASSERT_EQUAL(false, added_last);
}

void test_Array_first_element_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1 = 1, d2 = 2;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_first(array, &d1);
    Array_add_first(array, &d2);

    void *first = Array_first_element(array);
    TEST_ASSERT_EQUAL(d2, _convert_to_TYPE(first));
}

void test_Array_first_element_2() {
    TEST_MESSAGE("Case 2 --> Non Null Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    void *first = Array_first_element(array);
    TEST_ASSERT_EQUAL(NULL, first);
}

void test_Array_first_element_3() {
    TEST_MESSAGE("Case 3 --> Null Array:");
    Array *array = NULL;

    void *first = Array_first_element(array);
    TEST_ASSERT_EQUAL(NULL, first);
}

void test_Array_last_element_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1 = 1, d2 = 2;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);

    void *last = Array_last_element(array);
    TEST_ASSERT_EQUAL(d2, _convert_to_TYPE(last));
}

void test_Array_last_element_2() {
    TEST_MESSAGE("Case 2 --> Non Null Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    void *last = Array_last_element(array);
    TEST_ASSERT_EQUAL(NULL, last);
}

void test_Array_last_element_3() {
    TEST_MESSAGE("Case 3 --> Null Array:");
    Array *array = NULL;

    void *last = Array_last_element(array);
    TEST_ASSERT_EQUAL(NULL, last);
}

void test_Array_remove_first_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1 = 1, d2 = 2;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_first(array, &d1);
    Array_add_first(array, &d2);

    void *first = Array_first_element(array);
    TEST_ASSERT_EQUAL(d2, _convert_to_TYPE(first));

    bool removed_first = Array_remove_first(array);
    TEST_ASSERT_EQUAL(true, removed_first);

    void *new_first = Array_first_element(array);
    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(new_first));
}

void test_Array_remove_first_2() {
    TEST_MESSAGE("Case 2 --> Non Null Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool removed_first = Array_remove_first(array);
    TEST_ASSERT_EQUAL(false, removed_first);
}

void test_Array_remove_first_3() {
    TEST_MESSAGE("Case 3 --> Null Array:");
    Array *array = NULL;

    bool removed_first = Array_remove_first(array);
    TEST_ASSERT_EQUAL(false, removed_first);
}

void test_Array_remove_last_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1, d2;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);

    void *last = Array_last_element(array);
    TEST_ASSERT_EQUAL(d2, _convert_to_TYPE(last));

    bool removed_last = Array_remove_last(array);
    TEST_ASSERT_EQUAL(true, removed_last);

    void *new_last = Array_last_element(array);
    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(new_last));
}

void test_Array_remove_last_2() {
    TEST_MESSAGE("Case 2 --> Non Null Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool removed_last = Array_remove_last(array);
    TEST_ASSERT_EQUAL(false, removed_last);
}

void test_Array_remove_last_3() {
    TEST_MESSAGE("Case 3 --> Null Array:");
    Array *array = NULL;

    bool removed_last = Array_remove_last(array);
    TEST_ASSERT_EQUAL(false, removed_last);
}

void test_Array_remove_at_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d3);

    bool removed = Array_remove_at(array, 0);
    TEST_ASSERT_EQUAL(true, removed);
    TEST_ASSERT_EQUAL(d2, _convert_to_TYPE(Array_first_element(array)));
}

void test_Array_remove_at_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    bool removed = Array_remove_at(array, 1);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_Array_remove_at_3() {
    TEST_MESSAGE("Case 3 --> Non Null but Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool removed = Array_remove_at(array, 1);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_Array_remove_at_4() {
    TEST_MESSAGE("Case 4 --> Non Null Array and negative index:");
    TYPE d1, d2, d3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d3);

    bool removed = Array_remove_at(array, -1);
    TEST_ASSERT_EQUAL(false, removed);
    TEST_ASSERT_EQUAL(3, Array_size(array));
}

void test_Array_remove_at_5() {
    TEST_MESSAGE("Case 5 --> Non Null Array and index greater than size:");
    TYPE d1, d2, d3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d3);

    bool removed = Array_remove_at(array, 4);
    TEST_ASSERT_EQUAL(false, removed);
    TEST_ASSERT_EQUAL(3, Array_size(array));
}

void test_Array_remove_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d3);
    long size_before = Array_size(array);

    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_first_element(array)));
    bool removed = Array_remove(array, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(true, removed);
    TEST_ASSERT_EQUAL(size_before-1, Array_size(array));
    TEST_ASSERT_NOT_EQUAL(d1, _convert_to_TYPE(Array_first_element(array)));
}

void test_Array_remove_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    TYPE d1;
    Array *array = NULL;

    bool removed = Array_remove(array, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_Array_remove_3() {
    TEST_MESSAGE("Case 3 --> Non Null Array but Null data:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);

    bool removed = Array_remove(array, NULL, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_Array_remove_4() {
    TEST_MESSAGE("Case 4 --> Non Null Empty Array:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool removed = Array_remove(array, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_Array_remove_all_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1 = 1, d2 = 2;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    long size_before = Array_size(array);

    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_first_element(array)));
    bool removed = Array_remove(array, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(true, removed);
    TEST_ASSERT_EQUAL(size_before-1, Array_size(array));
    TEST_ASSERT_NOT_EQUAL(d2, _convert_to_TYPE(Array_first_element(array)));
}

void test_Array_remove_all_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    TYPE d1;
    Array *array = NULL;

    bool removed = Array_remove(array, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_Array_remove_all_3() {
    TEST_MESSAGE("Case 3 --> Non Null Array but Null data:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);

    bool removed = Array_remove(array, NULL, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_Array_remove_all_4() {
    TEST_MESSAGE("Case 4 --> Non Null Empty Array:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool removed = Array_remove(array, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_Array_insert_at_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d2);
    Array_add_last(array, &d1);
    long size_before = Array_size(array);

    bool inserted = Array_insert_at(array, &d1, 0);
    TEST_ASSERT_EQUAL(true, inserted);
    TEST_ASSERT_EQUAL(size_before+1, Array_size(array));
    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_first_element(array)));

    bool inserted2 = Array_insert_at(array, &d3, 3);
    TEST_ASSERT_EQUAL(true, inserted2);
    TEST_ASSERT_EQUAL(size_before+2, Array_size(array));
    TEST_ASSERT_EQUAL(d3, _convert_to_TYPE(Array_last_element(array)));
}

void test_Array_insert_at_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    TYPE d1;
    Array *array = NULL;

    bool inserted = Array_insert_at(array, &d1, 0);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_Array_insert_at_3() {
    TEST_MESSAGE("Case 3 --> Non Null Array, but Null data:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool inserted = Array_insert_at(array, NULL, 0);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_Array_insert_at_4() {
    TEST_MESSAGE("Case 4 --> Full Array:");
    TYPE d1, d2, d3, d4, d5, d6;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d3);
    Array_add_last(array, &d4);
    Array_add_last(array, &d5);

    bool inserted = Array_insert_at(array, &d6, 0);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_Array_insert_at_5() {
    TEST_MESSAGE("Case 5 --> Non Null Array, negative index:");
    TYPE d1, d2, d3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);

    bool inserted = Array_insert_at(array, &d3, -1);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_Array_insert_at_6() {
    TEST_MESSAGE("Case 6 --> Non Null Array and index greater than size:");
    TYPE d1, d2, d3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);

    bool inserted = Array_insert_at(array, &d3, 3);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_Array_set_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d2);
    Array_add_last(array, &d1);
    long size_before = Array_size(array);

    bool set = Array_set(array, &d1, 0);
    TEST_ASSERT_EQUAL(true, set);
    TEST_ASSERT_EQUAL(size_before, Array_size(array));
    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_first_element(array)));

    bool set2 = Array_set(array, &d3, 1);
    TEST_ASSERT_EQUAL(true, set2);
    TEST_ASSERT_EQUAL(size_before, Array_size(array));
    TEST_ASSERT_EQUAL(d3, _convert_to_TYPE(Array_last_element(array)));
}

void test_Array_set_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    TYPE d1;
    Array *array = NULL;

    bool set = Array_set(array, &d1, 0);
    TEST_ASSERT_EQUAL(false, set);
}

void test_Array_set_3() {
    TEST_MESSAGE("Case 3 --> Non Null Array, but Null data:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool set = Array_set(array, NULL, 0);
    TEST_ASSERT_EQUAL(false, set);
}

void test_Array_set_4() {
    TEST_MESSAGE("Case 4 --> Non Null Array, negative index:");
    TYPE d1, d2, d3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);

    bool set = Array_set(array, &d3, -1);
    TEST_ASSERT_EQUAL(false, set);
}

void test_Array_set_5() {
    TEST_MESSAGE("Case 5 --> Non Null Array and index greater than size:");
    TYPE d1, d2, d3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);

    bool inserted = Array_set(array, &d3, 3);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_Array_get_at_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_first(array, &d1);
    Array_add_first(array, &d2);
    Array_add_last(array, &d3);

    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_get_at(array, 1)));
    TEST_ASSERT_EQUAL(d2, _convert_to_TYPE(Array_get_at(array, 0)));
    TEST_ASSERT_EQUAL(d3, _convert_to_TYPE(Array_get_at(array, 2)));
}

void test_Array_get_at_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;
    TEST_ASSERT_EQUAL(NULL, Array_get_at(array, 0));
}

void test_Array_get_at_3() {
    TEST_MESSAGE("Case 3 --> Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    TEST_ASSERT_EQUAL(NULL, Array_get_at(array, 0));
}

void test_Array_get_at_4() {
    TEST_MESSAGE("Case 4 --> Non Null Array, negative index:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_first(array, &d1);

    TEST_ASSERT_EQUAL(NULL, Array_get_at(array, -1));
}

void test_Array_get_at_5() {
    TEST_MESSAGE("Case 5 --> Non Null Array, index greater than size:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_first(array, &d1);

    TEST_ASSERT_EQUAL(NULL, Array_get_at(array, 2));
}

void test_consistence_between_first_element_and_get_at_0() {
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_first(array, &d1);
    Array_add_first(array, &d2);
    Array_add_first(array, &d3);
    TEST_ASSERT_EQUAL(Array_get_at(array, 0), Array_first_element(array));
}

void test_consistence_between_last_element_and_get_at_size_minus_1() {
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_first(array, &d1);
    Array_add_first(array, &d2);
    Array_add_first(array, &d3);
    TEST_ASSERT_EQUAL(Array_get_at(array, 2), Array_last_element(array));
}

void test_Array_clone_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_first(array, &d1);
    Array_add_first(array, &d2);
    Array_add_last(array, &d3);

    Array *clone = Array_clone(array);

    TEST_ASSERT_EQUAL(Array_size(clone), Array_size(array));
    TEST_ASSERT_EQUAL(Array_is_sorted(clone), Array_is_sorted(array));
    TEST_ASSERT_EQUAL(Array_sort_order(clone), Array_sort_order(array));
    TEST_ASSERT_EQUAL(_convert_to_TYPE(Array_first_element(clone)), _convert_to_TYPE(Array_first_element(array)));
    TEST_ASSERT_EQUAL(_convert_to_TYPE(Array_get_at(clone, 1)), _convert_to_TYPE(Array_get_at(array, 1)));
    TEST_ASSERT_EQUAL(_convert_to_TYPE(Array_last_element(clone)), _convert_to_TYPE(Array_last_element(array)));
}

void test_Array_clone_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    Array *clone = Array_clone(array);

    TEST_ASSERT_EQUAL(NULL, clone);
}

void test_Array_clone_3() {
    TEST_MESSAGE("Case 3 --> Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    Array *clone = Array_clone(array);

    TEST_ASSERT_EQUAL(NULL, clone);
}

void test_Array_concat_1() {
    TEST_MESSAGE("Case 1 --> Non Null and Not Empty Array1 and Array2:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array1, &d3);
    Array_add_last(array1, &d2);
    Array_add_last(array1, &d1);

    Array *array2 = Array_create(SIZE, sizeof(TYPE));
    Array_add_last(array2, &d1);
    Array_add_last(array2, &d2);
    Array_add_last(array2, &d3);

    Array *array_new = Array_concat(array1, array2);
    TEST_ASSERT_EQUAL(d3, _convert_to_TYPE(Array_first_element(array_new)));
    TEST_ASSERT_EQUAL(d3, _convert_to_TYPE(Array_last_element(array_new)));
    TEST_ASSERT_EQUAL(CAPACITY + SIZE, Array_capacity(array_new));

    Array *array_new2 = Array_concat(array2, array1);
    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_first_element(array_new2)));
    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_last_element(array_new2)));
    TEST_ASSERT_EQUAL(SIZE + CAPACITY, Array_capacity(array_new2));
}

void test_Array_concat_2() {
    TEST_MESSAGE("Case 2 --> Null Array1 and Not Null Array2:");
    TYPE d1, d2, d3;
    Array *array1 = NULL;

    Array *array2 = Array_create(SIZE, sizeof(TYPE));
    Array_add_last(array2, &d1);
    Array_add_last(array2, &d2);
    Array_add_last(array2, &d3);

    Array *array_new = Array_concat(array1, array2);
    TEST_ASSERT_EQUAL(NULL, array_new);
}

void test_Array_concat_3() {
    TEST_MESSAGE("Case 3 --> Non Null Array1 and Null Array2:");
    TYPE d1, d2, d3;
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array1, &d1);
    Array_add_last(array1, &d2);
    Array_add_last(array1, &d3);

    Array *array2 = NULL;

    Array *array_new = Array_concat(array1, array2);
    TEST_ASSERT_EQUAL(NULL, array_new);
}

void test_Array_concat_4() {
    TEST_MESSAGE("Case 4 --> Null Array1 and Null Array2:");
    Array *array1 = NULL;
    Array *array2 = NULL;

    Array *array_new = Array_concat(array1, array2);
    TEST_ASSERT_EQUAL(NULL, array_new);
}

void test_Array_concat_5() {
    TEST_MESSAGE("Case 5 --> Empty Array1 and Not Empty Array2:");
    TYPE d1, d2, d3;
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));

    Array *array2 = Array_create(SIZE, sizeof(TYPE));
    Array_add_last(array2, &d1);
    Array_add_last(array2, &d2);
    Array_add_last(array2, &d3);

    Array *array_new = Array_concat(array1, array2);
    TEST_ASSERT_EQUAL(NULL, array_new);
}

void test_Array_concat_6() {
    TEST_MESSAGE("Case 6 --> Non Empty Array1 and Empty Array2:");
    TYPE d1, d2, d3;
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array1, &d1);
    Array_add_last(array1, &d2);
    Array_add_last(array1, &d3);

    Array *array2 = NULL;

    Array *array_new = Array_concat(array1, array2);
    TEST_ASSERT_EQUAL(NULL, array_new);
}

void test_Array_concat_7() {
    TEST_MESSAGE("Case 7 --> Empty Array1 and Empty Array2:");
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));
    Array *array2 = Array_create(SIZE, sizeof(TYPE));

    Array *array_new = Array_concat(array1, array2);
    TEST_ASSERT_EQUAL(NULL, array_new);
}

void test_Array_concat_8() {
    TEST_MESSAGE("Case 8 --> Empty Array1 and Null Array2:");
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));
    Array *array2 = NULL;

    Array *array_new = Array_concat(array1, array2);
    TEST_ASSERT_EQUAL(NULL, array_new);
}

void test_Array_concat_9() {
    TEST_MESSAGE("Case 9 --> Null Array1 and Empty Array2:");
    Array *array1 = NULL;
    Array *array2 = Array_create(SIZE, sizeof(TYPE));

    Array *array_new = Array_concat(array1, array2);
    TEST_ASSERT_EQUAL(NULL, array_new);
}

void test_Array_sub_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    long initial_sub = 1, final_sub = 4;
    long capacity_sub = final_sub - initial_sub;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < CAPACITY; i++) {
        Array_add_last(array, &i);
    }

    Array *sub_array = Array_sub(array, initial_sub, final_sub);
    TEST_ASSERT_EQUAL(true, Array_is_full(sub_array));
    TEST_ASSERT_EQUAL(_convert_to_TYPE(Array_get_at(array, initial_sub)), _convert_to_TYPE(Array_get_at(sub_array, 0)));
    TEST_ASSERT_EQUAL(_convert_to_TYPE(Array_get_at(array, final_sub-1)), _convert_to_TYPE(Array_get_at(sub_array, capacity_sub - 1)));
    TEST_ASSERT_EQUAL(capacity_sub, Array_capacity(sub_array));
}

void test_Array_sub_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    long initial_sub = 1, final_sub = 4;
    Array *array = NULL;

    Array *sub_array = Array_sub(array, initial_sub, final_sub);
    TEST_ASSERT_EQUAL(NULL, sub_array);
}

void test_Array_sub_3() {
    TEST_MESSAGE("Case 3 --> Empty Array:");
    long initial_sub = 1, final_sub = 4;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    Array *sub_array = Array_sub(array, initial_sub, final_sub);
    TEST_ASSERT_EQUAL(NULL, sub_array);
}

void test_Array_sub_4() {
    TEST_MESSAGE("Case 4 --> Negative final Index:");
    long initial_sub = 1, final_sub = -1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < CAPACITY; i++) {
        Array_add_last(array, &i);
    }

    Array *sub_array = Array_sub(array, initial_sub, final_sub);
    TEST_ASSERT_EQUAL(NULL, sub_array);
}

void test_Array_sub_5() {
    TEST_MESSAGE("Case 5 --> Final index greater than size:");
    long initial_sub = 1, final_sub = 6;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < CAPACITY; i++) {
        Array_add_last(array, &i);
    }

    Array *sub_array = Array_sub(array, initial_sub, final_sub);
    TEST_ASSERT_EQUAL(NULL, sub_array);
}

void test_Array_sub_6() {
    TEST_MESSAGE("Case 6 --> Negative initial Index:");
    long initial_sub = -11, final_sub = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < CAPACITY; i++) {
        Array_add_last(array, &i);
    }

    Array *sub_array = Array_sub(array, initial_sub, final_sub);
    TEST_ASSERT_EQUAL(NULL, sub_array);
}

void test_Array_sub_7() {
    TEST_MESSAGE("Case 7 --> Initial index greater than final index:");
    long initial_sub = 1, final_sub = 6;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < CAPACITY; i++) {
        Array_add_last(array, &i);
    }

    Array *sub_array = Array_sub(array, initial_sub, final_sub);
    TEST_ASSERT_EQUAL(NULL, sub_array);
}

void test_Array_sub_8() {
    TEST_MESSAGE("Case 8 --> Initial index equals to final index:");
    long initial_sub = 3, final_sub = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < CAPACITY; i++) {
        Array_add_last(array, &i);
    }

    Array *sub_array = Array_sub(array, initial_sub, final_sub);
    TEST_ASSERT_EQUAL(NULL, sub_array);
}

void test_Array_reverse_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    for (int i = 0; i < CAPACITY; i++) {
        Array_add_last(array, &i);
    }

    Array *array_reverse = Array_reverse(array);
    TEST_ASSERT_EQUAL(_convert_to_TYPE(Array_first_element(array)), _convert_to_TYPE(Array_last_element(array_reverse)));
    TEST_ASSERT_EQUAL(_convert_to_TYPE(Array_last_element(array)), _convert_to_TYPE(Array_first_element(array_reverse)));
    TEST_ASSERT_EQUAL(Array_sort_order(array), (-1)*Array_sort_order(array_reverse));
}

void test_Array_reverse_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    Array *array_reverse = Array_reverse(array);
    TEST_ASSERT_EQUAL(NULL, array_reverse);
}

void test_Array_reverse_3() {
    TEST_MESSAGE("Case 3 --> Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    Array *array_reverse = Array_reverse(array);
    TEST_ASSERT_EQUAL(NULL, array_reverse);
}

void test_Array_contains_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);

    TEST_ASSERT_EQUAL(true, Array_contains(array, &d1, _compare_TYPE));
    TEST_ASSERT_EQUAL(true, Array_contains(array, &d2, _compare_TYPE));
    TEST_ASSERT_EQUAL(false, Array_contains(array, &d3, _compare_TYPE));
}

void test_Array_contains_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    TYPE d1;
    Array *array = NULL;

    TEST_ASSERT_EQUAL(false, Array_contains(array, &d1, _compare_TYPE));
}

void test_Array_contains_3() {
    TEST_MESSAGE("Case 3 --> Null Data:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);

    TEST_ASSERT_EQUAL(false, Array_contains(array, NULL, _compare_TYPE));
}

void test_Array_contains_4() {
    TEST_MESSAGE("Case 4 --> Empty Array:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    TEST_ASSERT_EQUAL(false, Array_contains(array, &d1, _compare_TYPE));
}

void test_Array_count_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d2);
    Array_add_last(array, &d2);
    Array_add_last(array, &d3);
    int count_d2 = Array_count(array, &d2, _compare_TYPE);
    TEST_ASSERT_EQUAL(3, count_d2);
}

void test_Array_count_2() {
    TEST_MESSAGE("Case 2 --> Data not in the Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    int count_d3 = Array_count(array, &d3, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, count_d3);
}

void test_Array_count_3() {
    TEST_MESSAGE("Case 3 --> Null Array:");
    TYPE d1;
    Array *array = NULL;
    int count_d1 = Array_count(array, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(-1, count_d1);
}

void test_Array_count_4() {
    TEST_MESSAGE("Case 4 --> Null Data:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    int count_null = Array_count(array, NULL, _compare_TYPE);
    TEST_ASSERT_EQUAL(-1, count_null);
}

void test_Array_count_5() {
    TEST_MESSAGE("Case 5 --> Empty Array:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    int count_null = Array_count(array, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(-1, count_null);
}

void test_Array_is_equals_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));
    Array *array2 = Array_create(CAPACITY, sizeof(TYPE));
    Array *array3 = Array_create(CAPACITY, sizeof(TYPE));
    Array *array4 = Array_create(CAPACITY, sizeof(TYPE));
    int d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    int d5 = 1, d6 = 2, d7 = 3, d8 = 4;

    Array_add_last(array1, &d1);
    Array_add_last(array1, &d2);
    Array_add_last(array1, &d3);
    Array_add_last(array1, &d4);

    Array_add_last(array2, &d1);
    Array_add_last(array2, &d2);
    Array_add_last(array2, &d3);
    Array_add_last(array2, &d4);

    Array_add_last(array3, &d2);
    Array_add_last(array3, &d3);
    Array_add_last(array3, &d4);

    Array_add_last(array4, &d5);
    Array_add_last(array4, &d6);
    Array_add_last(array4, &d7);
    Array_add_last(array4, &d8);

    TEST_ASSERT_EQUAL(true, Array_is_equals(array1, array2, _compare_TYPE));
    TEST_ASSERT_EQUAL(false, Array_is_equals(array1, array3, _compare_TYPE));
    TEST_ASSERT_EQUAL(true, Array_is_equals(array1, array4, _compare_TYPE));
    TEST_ASSERT_EQUAL(false, Array_is_equals(array2, array3, _compare_TYPE));
    TEST_ASSERT_EQUAL(true, Array_is_equals(array3, array3, _compare_TYPE));
}

void test_Array_is_equals_2() {
    TEST_MESSAGE("Case 2 --> Null Array1 and Not Null Array2:");
    TYPE d1, d2, d3;
    Array *array1 = NULL;

    Array *array2 = Array_create(SIZE, sizeof(TYPE));
    Array_add_last(array2, &d1);
    Array_add_last(array2, &d2);
    Array_add_last(array2, &d3);

    bool equals = Array_is_equals(array1, array2, _compare_TYPE);
    TEST_ASSERT_EQUAL(NULL, equals);
}

void test_Array_is_equals_3() {
    TEST_MESSAGE("Case 3 --> Non Null Array1 and Null Array2:");
    TYPE d1, d2, d3;
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array1, &d1);
    Array_add_last(array1, &d2);
    Array_add_last(array1, &d3);

    Array *array2 = NULL;

    bool equals = Array_is_equals(array1, array2, _compare_TYPE);
    TEST_ASSERT_EQUAL(NULL, equals);
}

void test_Array_is_equals_4() {
    TEST_MESSAGE("Case 4 --> Null Array1 and Null Array2:");
    Array *array1 = NULL;
    Array *array2 = NULL;

    bool equals = Array_is_equals(array1, array2, _compare_TYPE);
    TEST_ASSERT_EQUAL(NULL, equals);
}

void test_Array_is_equals_5() {
    TEST_MESSAGE("Case 5 --> Empty Array1 and Not Empty Array2:");
    TYPE d1, d2, d3;
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));

    Array *array2 = Array_create(SIZE, sizeof(TYPE));
    Array_add_last(array2, &d1);
    Array_add_last(array2, &d2);
    Array_add_last(array2, &d3);

    bool equals = Array_is_equals(array1, array2, _compare_TYPE);
    TEST_ASSERT_EQUAL(NULL, equals);
}

void test_Array_is_equals_6() {
    TEST_MESSAGE("Case 6 --> Non Empty Array1 and Empty Array2:");
    TYPE d1, d2, d3;
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array1, &d1);
    Array_add_last(array1, &d2);
    Array_add_last(array1, &d3);

    Array *array2 = NULL;

    bool equals = Array_is_equals(array1, array2, _compare_TYPE);
    TEST_ASSERT_EQUAL(NULL, equals);
}

void test_Array_is_equals_7() {
    TEST_MESSAGE("Case 7 --> Empty Array1 and Empty Array2:");
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));
    Array *array2 = Array_create(SIZE, sizeof(TYPE));

    bool equals = Array_is_equals(array1, array2, _compare_TYPE);
    TEST_ASSERT_EQUAL(NULL, equals);
}

void test_Array_is_equals_8() {
    TEST_MESSAGE("Case 8 --> Empty Array1 and Null Array2:");
    Array *array1 = Array_create(CAPACITY, sizeof(TYPE));
    Array *array2 = NULL;

    bool equals = Array_is_equals(array1, array2, _compare_TYPE);
    TEST_ASSERT_EQUAL(NULL, equals);
}

void test_Array_is_equals_9() {
    TEST_MESSAGE("Case 9 --> Null Array1 and Empty Array2:");
    Array *array1 = NULL;
    Array *array2 = Array_create(SIZE, sizeof(TYPE));

    bool equals = Array_is_equals(array1, array2, _compare_TYPE);
    TEST_ASSERT_EQUAL(NULL, equals);
}

void test_Array_index_of_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d3);
    Array_add_last(array, &d4);

    TEST_ASSERT_EQUAL(-1, Array_index_of(array, &d5, _compare_TYPE));
    TEST_ASSERT_EQUAL(0, Array_index_of(array, &d1, _compare_TYPE));
    TEST_ASSERT_EQUAL(1, Array_index_of(array, &d2, _compare_TYPE));
    TEST_ASSERT_EQUAL(2, Array_index_of(array, &d3, _compare_TYPE));
    TEST_ASSERT_EQUAL(3, Array_index_of(array, &d4, _compare_TYPE));
}

void test_Array_index_of_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    TYPE d1;
    Array *array = NULL;

    TEST_ASSERT_EQUAL(-1, Array_index_of(array, &d1, _compare_TYPE));
}

void test_Array_index_of_3() {
    TEST_MESSAGE("Case 3 --> Null Data:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);

    TEST_ASSERT_EQUAL(-1, Array_index_of(array, NULL, _compare_TYPE));
}

void test_Array_index_of_4() {
    TEST_MESSAGE("Case 4 --> Empty Array:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    TEST_ASSERT_EQUAL(-1, Array_index_of(array, &d1, _compare_TYPE));
}

void test_Array_last_index_of_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);

    TEST_ASSERT_EQUAL(-1, Array_last_index_of(array, &d3, _compare_TYPE));
    TEST_ASSERT_EQUAL(2, Array_last_index_of(array, &d1, _compare_TYPE));
    TEST_ASSERT_EQUAL(3, Array_last_index_of(array, &d2, _compare_TYPE));
}

void test_Array_last_index_of_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    TYPE d1;
    Array *array = NULL;

    TEST_ASSERT_EQUAL(-1, Array_last_index_of(array, &d1, _compare_TYPE));
}

void test_Array_last_index_of_3() {
    TEST_MESSAGE("Case 3 --> Null Data:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);

    TEST_ASSERT_EQUAL(-1, Array_last_index_of(array, NULL, _compare_TYPE));
}

void test_Array_last_index_of_4() {
    TEST_MESSAGE("Case 4 --> Empty Array:");
    TYPE d1;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    TEST_ASSERT_EQUAL(-1, Array_last_index_of(array, &d1, _compare_TYPE));
}

void test_Array_sort_asc_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    Array_add_last(array, &d4);
    Array_add_last(array, &d3);
    Array_add_last(array, &d2);
    Array_add_last(array, &d1);

    TEST_ASSERT_EQUAL(0, Array_is_sorted(array));
    TEST_ASSERT_EQUAL(0, Array_sort_order(array));

    bool sorted = Array_sort_asc(array, _compare_TYPE);
    TEST_ASSERT_EQUAL(true, sorted);
    TEST_ASSERT_EQUAL(true, Array_is_sorted(array));
    TEST_ASSERT_EQUAL(1, Array_sort_order(array));
    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_first_element(array)));
    TEST_ASSERT_EQUAL(d4, _convert_to_TYPE(Array_last_element(array)));
}

void test_Array_sort_asc_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    bool sorted = Array_sort_asc(array, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, sorted);
}

void test_Array_sort_asc_3() {
    TEST_MESSAGE("Case 3 --> Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool sorted = Array_sort_asc(array, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, sorted);
}

void test_Array_sort_desc_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d3);
    Array_add_last(array, &d4);

    TEST_ASSERT_EQUAL(0, Array_is_sorted(array));
    TEST_ASSERT_EQUAL(0, Array_sort_order(array));

    bool sorted = Array_sort_desc(array, _compare_TYPE);
    TEST_ASSERT_EQUAL(true, sorted);
    TEST_ASSERT_EQUAL(true, Array_is_sorted(array));
    TEST_ASSERT_EQUAL(-1, Array_sort_order(array));
    TEST_ASSERT_EQUAL(d4, _convert_to_TYPE(Array_first_element(array)));
    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_last_element(array)));
}

void test_Array_sort_desc_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    bool sorted = Array_sort_desc(array, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, sorted);
}

void test_Array_sort_desc_3() {
    TEST_MESSAGE("Case 3 --> Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    bool sorted = Array_sort_desc(array, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, sorted);
}

void test_Array_sorted_insert_1() {
    TEST_MESSAGE("Case 1 --> Asc Sorted Array:");
    TYPE d0 = 0, d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d3);
    Array_add_last(array, &d1);

    Array_sort_asc(array, _compare_TYPE);

    Array_sorted_insert(array, &d0, _compare_TYPE);
    TEST_ASSERT_EQUAL(d0, _convert_to_TYPE(Array_get_at(array, 0)));
    Array_sorted_insert(array, &d2, _compare_TYPE);
    TEST_ASSERT_EQUAL(d2, _convert_to_TYPE(Array_get_at(array, 2)));
    Array_sorted_insert(array, &d4, _compare_TYPE);
}

void test_Array_sorted_insert_2() {
    TEST_MESSAGE("Case 2 --> Desc Sorted Array:");
    TYPE d0 = 0, d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d1);
    Array_add_last(array, &d3);

    Array_sort_desc(array, _compare_TYPE);

    Array_sorted_insert(array, &d4, _compare_TYPE);
    TEST_ASSERT_EQUAL(d4, _convert_to_TYPE(Array_get_at(array, 0)));
    Array_sorted_insert(array, &d2, _compare_TYPE);
    TEST_ASSERT_EQUAL(d2, _convert_to_TYPE(Array_get_at(array, 2)));
    Array_sorted_insert(array, &d0, _compare_TYPE);
    TEST_ASSERT_EQUAL(d0, _convert_to_TYPE(Array_get_at(array, 4)));
}

void test_Array_sorted_insert_3() {
    TEST_MESSAGE("Case 3 --> Null Array:");
    TYPE d0;
    Array *array = NULL;

    bool inserted = Array_sorted_insert(array, &d0, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_Array_sorted_insert_4() {
    TEST_MESSAGE("Case 4 --> Full Array:");
    TYPE d0 = 0, d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d3);
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d4);
    Array_add_last(array, &d0);

    bool inserted = Array_sorted_insert(array, &d5, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_Array_sorted_insert_5() {
    TEST_MESSAGE("Case 5 --> Not sorted Array:");
    TYPE d0 = 0, d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));
    Array_add_last(array, &d3);
    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d0);

    bool inserted = Array_sorted_insert(array, &d4, _compare_TYPE);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_Array_min_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d3);
    Array_add_last(array, &d4);

    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_min(array, _compare_TYPE)));

    Array_sort_desc(array, _compare_TYPE);
    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_min(array, _compare_TYPE)));

    Array_sort_asc(array, _compare_TYPE);
    TEST_ASSERT_EQUAL(d1, _convert_to_TYPE(Array_min(array, _compare_TYPE)));
}

void test_Array_min_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    TEST_ASSERT_EQUAL(NULL, Array_min(array, _compare_TYPE));
}

void test_Array_min_3() {
    TEST_MESSAGE("Case 3 --> Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    TEST_ASSERT_EQUAL(NULL, Array_min(array, _compare_TYPE));
}

void test_Array_max_1() {
    TEST_MESSAGE("Case 1 --> Non Null Array:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    Array_add_last(array, &d1);
    Array_add_last(array, &d2);
    Array_add_last(array, &d3);
    Array_add_last(array, &d4);

    TEST_ASSERT_EQUAL(d4, _convert_to_TYPE(Array_max(array, _compare_TYPE)));

    Array_sort_desc(array, _compare_TYPE);
    TEST_ASSERT_EQUAL(d4, _convert_to_TYPE(Array_max(array, _compare_TYPE)));

    Array_sort_asc(array, _compare_TYPE);
    TEST_ASSERT_EQUAL(d4, _convert_to_TYPE(Array_max(array, _compare_TYPE)));
}

void test_Array_max_2() {
    TEST_MESSAGE("Case 2 --> Null Array:");
    Array *array = NULL;

    TEST_ASSERT_EQUAL(NULL, Array_max(array, _compare_TYPE));
}

void test_Array_max_3() {
    TEST_MESSAGE("Case 3 --> Empty Array:");
    Array *array = Array_create(CAPACITY, sizeof(TYPE));

    TEST_ASSERT_EQUAL(NULL, Array_max(array, _compare_TYPE));
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_Array_create_1);
    RUN_TEST(test_Array_create_2);
    RUN_TEST(test_Array_create_3);
    RUN_TEST(test_Array_clean_1);
    RUN_TEST(test_Array_clean_2);
    RUN_TEST(test_Array_delete_1);
    RUN_TEST(test_Array_delete_2);
    RUN_TEST(test_Array_capacity_1);
    RUN_TEST(test_Array_capacity_2);
    RUN_TEST(test_Array_size_1);
    RUN_TEST(test_Array_size_2);
    RUN_TEST(test_Array_sort_order_1);
    RUN_TEST(test_Array_sort_order_2);
    RUN_TEST(test_Array_sort_order_3);
    RUN_TEST(test_Array_sort_order_4);
    RUN_TEST(test_Array_is_empty_1);
    RUN_TEST(test_Array_is_empty_2);
    RUN_TEST(test_Array_is_empty_3);
    RUN_TEST(test_Array_is_full_1);
    RUN_TEST(test_Array_is_full_2);
    RUN_TEST(test_Array_is_full_3);
    RUN_TEST(test_Array_is_sorted_1);
    RUN_TEST(test_Array_is_sorted_2);
    RUN_TEST(test_Array_is_sorted_3);
    RUN_TEST(test_Array_is_sorted_4);
    RUN_TEST(test_Array_add_first_1);
    RUN_TEST(test_Array_add_first_2);
    RUN_TEST(test_Array_add_first_3);
    RUN_TEST(test_Array_add_first_4);
    RUN_TEST(test_Array_add_last_1);
    RUN_TEST(test_Array_add_last_2);
    RUN_TEST(test_Array_add_last_3);
    RUN_TEST(test_Array_add_last_4);
    RUN_TEST(test_Array_first_element_1);
    RUN_TEST(test_Array_first_element_2);
    RUN_TEST(test_Array_first_element_3);
    RUN_TEST(test_Array_last_element_1);
    RUN_TEST(test_Array_last_element_2);
    RUN_TEST(test_Array_last_element_3);
    RUN_TEST(test_Array_remove_first_1);
    RUN_TEST(test_Array_remove_first_2);
    RUN_TEST(test_Array_remove_first_3);
    RUN_TEST(test_Array_remove_last_1);
    RUN_TEST(test_Array_remove_last_2);
    RUN_TEST(test_Array_remove_last_3);
    RUN_TEST(test_Array_remove_at_1);
    RUN_TEST(test_Array_remove_at_2);
    RUN_TEST(test_Array_remove_at_3);
    RUN_TEST(test_Array_remove_at_4);
    RUN_TEST(test_Array_remove_at_5);
    RUN_TEST(test_Array_remove_1);
    RUN_TEST(test_Array_remove_2);
    RUN_TEST(test_Array_remove_3);
    RUN_TEST(test_Array_remove_4);
    RUN_TEST(test_Array_remove_all_1);
    RUN_TEST(test_Array_remove_all_2);
    RUN_TEST(test_Array_remove_all_3);
    RUN_TEST(test_Array_remove_all_4);
    RUN_TEST(test_Array_insert_at_1);
    RUN_TEST(test_Array_insert_at_2);
    RUN_TEST(test_Array_insert_at_3);
    RUN_TEST(test_Array_insert_at_4);
    RUN_TEST(test_Array_insert_at_5);
    RUN_TEST(test_Array_insert_at_6);
    RUN_TEST(test_Array_set_1);
    RUN_TEST(test_Array_set_2);
    RUN_TEST(test_Array_set_3);
    RUN_TEST(test_Array_set_4);
    RUN_TEST(test_Array_set_5);
    RUN_TEST(test_Array_get_at_1);
    RUN_TEST(test_Array_get_at_2);
    RUN_TEST(test_Array_get_at_3);
    RUN_TEST(test_Array_get_at_4);
    RUN_TEST(test_Array_get_at_5);
    RUN_TEST(test_consistence_between_first_element_and_get_at_0);
    RUN_TEST(test_consistence_between_last_element_and_get_at_size_minus_1);
    RUN_TEST(test_Array_clone_1);
    RUN_TEST(test_Array_clone_2);
    RUN_TEST(test_Array_clone_3);
    RUN_TEST(test_Array_concat_1);
    RUN_TEST(test_Array_concat_2);
    RUN_TEST(test_Array_concat_3);
    RUN_TEST(test_Array_concat_4);
    RUN_TEST(test_Array_concat_5);
    RUN_TEST(test_Array_concat_6);
    RUN_TEST(test_Array_concat_7);
    RUN_TEST(test_Array_concat_8);
    RUN_TEST(test_Array_concat_9);
    RUN_TEST(test_Array_sub_1);
    RUN_TEST(test_Array_sub_2);
    RUN_TEST(test_Array_sub_3);
    RUN_TEST(test_Array_sub_4);
    RUN_TEST(test_Array_sub_5);
    RUN_TEST(test_Array_sub_6);
    RUN_TEST(test_Array_sub_7);
    RUN_TEST(test_Array_sub_8);
    RUN_TEST(test_Array_reverse_1);
    RUN_TEST(test_Array_reverse_2);
    RUN_TEST(test_Array_reverse_3);
    RUN_TEST(test_Array_contains_1);
    RUN_TEST(test_Array_contains_2);
    RUN_TEST(test_Array_contains_3);
    RUN_TEST(test_Array_contains_4);
    RUN_TEST(test_Array_count_1);
    RUN_TEST(test_Array_count_2);
    RUN_TEST(test_Array_count_3);
    RUN_TEST(test_Array_count_4);
    RUN_TEST(test_Array_count_5);
    RUN_TEST(test_Array_is_equals_1);
    RUN_TEST(test_Array_is_equals_2);
    RUN_TEST(test_Array_is_equals_3);
    RUN_TEST(test_Array_is_equals_4);
    RUN_TEST(test_Array_is_equals_5);
    RUN_TEST(test_Array_is_equals_6);
    RUN_TEST(test_Array_is_equals_7);
    RUN_TEST(test_Array_is_equals_8);
    RUN_TEST(test_Array_is_equals_9);
    RUN_TEST(test_Array_index_of_1);
    RUN_TEST(test_Array_index_of_2);
    RUN_TEST(test_Array_index_of_3);
    RUN_TEST(test_Array_index_of_4);
    RUN_TEST(test_Array_last_index_of_1);
    RUN_TEST(test_Array_last_index_of_2);
    RUN_TEST(test_Array_last_index_of_3);
    RUN_TEST(test_Array_last_index_of_4);
    RUN_TEST(test_Array_sort_asc_1);
    RUN_TEST(test_Array_sort_asc_2);
    RUN_TEST(test_Array_sort_asc_3);
    RUN_TEST(test_Array_sort_desc_1);
    RUN_TEST(test_Array_sort_desc_2);
    RUN_TEST(test_Array_sort_desc_3);
    RUN_TEST(test_Array_sorted_insert_1);
    RUN_TEST(test_Array_sorted_insert_2);
    RUN_TEST(test_Array_sorted_insert_3);
    RUN_TEST(test_Array_sorted_insert_4);
    RUN_TEST(test_Array_sorted_insert_5);
    RUN_TEST(test_Array_min_1);
    RUN_TEST(test_Array_min_2);
    RUN_TEST(test_Array_min_3);
    RUN_TEST(test_Array_max_1);
    RUN_TEST(test_Array_max_2);
    RUN_TEST(test_Array_max_3);
    return UNITY_END();
}
