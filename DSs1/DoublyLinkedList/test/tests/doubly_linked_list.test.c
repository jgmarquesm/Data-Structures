#include "../../main/include/unity.h"
#include "../../main/include/doubly_linked_list.h"

void setUp(){}

void tearDown(){}

int _convert_to_int(void *data){
    return *((int *)data);
}

void _print_int(void *data){
    printf("%d", _convert_to_int(data));
}

int _compare_int(void *data1, void *data2){
    int d1 = _convert_to_int(data1), d2 = _convert_to_int(data2);
    return d2 - d1;
}

// LinkedList_create()
void test_1() {
    TEST_MESSAGE("Test: LinkedList_create(): ");
    LinkedList *LL = LinkedList_create();
    bool is_empty = LinkedList_is_empty(LL);
    TEST_ASSERT_EQUAL(1, is_empty);
    TEST_ASSERT_EQUAL(0, LinkedList_size(LL));
    TEST_ASSERT_EQUAL(0, LinkedList_is_sorted(LL));
    TEST_ASSERT_EQUAL(0, LinkedList_sort_order(LL));
}

// LinkedList_clean(LL)
void test_2() {
    TEST_MESSAGE("Test: LinkedList_clean(LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_first(LL, &data1);
    LinkedList_add_first(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);

    LinkedList_clean(LL);
    TEST_ASSERT_EQUAL(1, LinkedList_is_empty(LL));
    TEST_ASSERT_EQUAL(0, LinkedList_size(LL));
}

// LinkedList_destroy(&LL)
void test_3() {
    TEST_MESSAGE("Test: LinkedList_destroy(&LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_first(LL, &data1);
    LinkedList_add_first(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);

    LinkedList_destroy(&LL);
    TEST_ASSERT_EQUAL(NULL, LL);
}

// LinkedList_is_empty(LL)
void test_4() {
    TEST_MESSAGE("Test: LinkedList_is_empty(): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, LinkedList_is_empty(LL));
    LinkedList_add_first(LL, &data1);
    LinkedList_add_first(LL, &data2);
    TEST_ASSERT_EQUAL(0, LinkedList_is_empty(LL));
}

// LinkedList_is_sorted(LL)
void test_5() {
    TEST_MESSAGE("Test: LinkedList_is_sorted(LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data3);
    LinkedList_add_last(LL, &data4);
    TEST_ASSERT_EQUAL(0, LinkedList_is_sorted(LL));
    LinkedList_sort_asc(LL, _compare_int);
    TEST_ASSERT_EQUAL(1, LinkedList_is_sorted(LL));
    LinkedList_sort_desc(LL, _compare_int);
    TEST_ASSERT_EQUAL(1, LinkedList_is_sorted(LL));
}

// LinkedList_sort_order(LL)
void test_6() {
    TEST_MESSAGE("Test: LinkedList_sort_order(LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data3);
    LinkedList_add_last(LL, &data4);
    TEST_ASSERT_EQUAL(0, LinkedList_sort_order(LL));
    LinkedList_sort_asc(LL, _compare_int);
    TEST_ASSERT_EQUAL(1, LinkedList_sort_order(LL));
    LinkedList_sort_desc(LL, _compare_int);
    TEST_ASSERT_EQUAL(-1, LinkedList_sort_order(LL));
}

// LinkedList_add_first(LL)
void test_7() {
    TEST_MESSAGE("Test: LinkedList_add_first(LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_first(LL, &data1);
    LinkedList_add_first(LL, &data2);
    TEST_ASSERT_EQUAL(&data2, LinkedList_first_element(LL));
    TEST_ASSERT_EQUAL(0,  LinkedList_sort_order(LL));
}

// LinkedList_add_last(LL)
void test_8() {
    TEST_MESSAGE("Test: LinkedList_add_last(LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    TEST_ASSERT_EQUAL(&data1, LinkedList_first_element(LL));
    TEST_ASSERT_EQUAL(0,  LinkedList_sort_order(LL));
}

// LinkedList_remove_first(LL)
void test_9() {
    TEST_MESSAGE("Test: LinkedList_remove_first(LL): ");
    LinkedList *LL = LinkedList_create();
    int data0 = 42, data1 = 99, data2 = 55;
    LinkedList_add_last(LL, &data0);
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);

    size_t size_before = LinkedList_size(LL);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(&data0, LinkedList_get(LL, 0));
    TEST_ASSERT_EQUAL(&data1, LinkedList_get(LL, 1));
    TEST_ASSERT_EQUAL(&data2, LinkedList_get(LL, 2));

    LinkedList_remove_first(LL);
    size_t size_after = LinkedList_size(LL);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, LinkedList_contains(LL, &data0));
    TEST_ASSERT_EQUAL(&data1, LinkedList_get(LL, 0));
    TEST_ASSERT_EQUAL(&data2, LinkedList_get(LL, 1));
}

// LinkedList_remove_last(LL)
void test_10() {
    TEST_MESSAGE("Test: LinkedList_remove_last(LL): ");
    LinkedList *LL = LinkedList_create();
    int data0 = 42, data1 = 99, data2 = 55;
    LinkedList_add_last(LL, &data0);
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);

    size_t size_before = LinkedList_size(LL);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(&data0, LinkedList_get(LL, 0));
    TEST_ASSERT_EQUAL(&data1, LinkedList_get(LL, 1));
    TEST_ASSERT_EQUAL(&data2, LinkedList_get(LL, 2));

    LinkedList_remove_last(LL);
    size_t size_after = LinkedList_size(LL);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, LinkedList_contains(LL, &data2));
    TEST_ASSERT_EQUAL(&data0, LinkedList_get(LL, 0));
    TEST_ASSERT_EQUAL(&data1, LinkedList_get(LL, 1));
}

// LinkedList_remove_at(LL, index)
void test_11() {
    TEST_MESSAGE("Test: LinkedList_remove_at(LL, index): ");
    LinkedList *LL = LinkedList_create();
    int data0 = 42, data1 = 99, data2 = 55;
    LinkedList_add_last(LL, &data0);
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);

    size_t size_before = LinkedList_size(LL);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(&data0, LinkedList_get(LL, 0));
    TEST_ASSERT_EQUAL(&data1, LinkedList_get(LL, 1));
    TEST_ASSERT_EQUAL(&data2, LinkedList_get(LL, 2));

    LinkedList_remove_at(LL, 1);
    size_t size_after = LinkedList_size(LL);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, LinkedList_contains(LL, &data1));
    TEST_ASSERT_EQUAL(&data0, LinkedList_get(LL, 0));
    TEST_ASSERT_EQUAL(&data2, LinkedList_get(LL, 1));
}

// LinkedList_remove(LL, data, type_compare_func)
void test_12() {
    TEST_MESSAGE("Test: LinkedList_remove(LL, data, type_compare_func): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_first(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_first(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_first(LL, &data1);

    size_t size_before = LinkedList_size(LL);
    TEST_ASSERT_EQUAL(6, size_before);
    TEST_ASSERT_EQUAL(&data1, LinkedList_get(LL, 0));
    TEST_ASSERT_EQUAL(&data2, LinkedList_get(LL, 1));

    LinkedList_remove(LL, &data1, _compare_int);
    size_t size_after = LinkedList_size(LL);
    TEST_ASSERT_EQUAL(5, size_after);
    TEST_ASSERT_EQUAL(0, LinkedList_contains(LL, &data1));
}

// LinkedList_remove_all(LL, data, type_compare_func)
void test_13() {
    TEST_MESSAGE("Test: LinkedList_remove_all(LL, data, type_compare_func): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = 99;
    LinkedList_add_first(LL, &data1);
    LinkedList_add_first(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data3);
    LinkedList_add_last(LL, &data3);

    LinkedList_remove_all(LL, &data2, _compare_int);
    TEST_ASSERT_EQUAL(0, LinkedList_contains(LL, &data2));
    TEST_ASSERT_EQUAL(0, LinkedList_contains(LL, &data3));
    TEST_ASSERT_EQUAL(1, LinkedList_size(LL));
}

// LinkedList_size(LL)
void test_14() {
    TEST_MESSAGE("Test: LinkedList_size(LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42;
    int data2 = 99;
    LinkedList_add_first(LL, &data1);
    LinkedList_add_last(LL, &data2);
    TEST_ASSERT_EQUAL(2, LinkedList_size(LL));
}

// LinkedList_first_element(LL)
void test_15() {
    TEST_MESSAGE("Test: LinkedList_first_element(LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_first(LL, &data1);
    LinkedList_add_first(LL, &data2);
    TEST_ASSERT_EQUAL(&data2, LinkedList_first_element(LL));
}

// LinkedList_last_element(LL)
void test_16() {
    TEST_MESSAGE("Test: LinkedList_last_element(LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    TEST_ASSERT_EQUAL(&data2, LinkedList_last_element(LL));
}

// LinkedList_get(LL, index)
void test_17() {
    TEST_MESSAGE("Test: LinkedList_get(LL, index): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_first(LL, &data1);
    LinkedList_add_first(LL, &data2);
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    size_t index = LinkedList_size(LL) - 1;
    TEST_ASSERT_EQUAL(&data2, LinkedList_get(LL, 0));
    TEST_ASSERT_EQUAL(&data2, LinkedList_get(LL, index));
}

// Consistence between LinkedList_first_element(LL) && LinkedList_get(LL, 0)
void test_18() {
    TEST_MESSAGE("Test: Consistence between LinkedList_first_element(LL) && LinkedList_get(LL, 0): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_first(LL, &data1);
    LinkedList_add_first(LL, &data2);
    TEST_ASSERT_EQUAL(LinkedList_get(LL, 0), LinkedList_first_element(LL));
}

// Consistence between LinkedList_last_element(LL) && LinkedList_get(LL, size-1)
void test_19() {
    TEST_MESSAGE("Test: Consistence between LinkedList_last_element(LL) && LinkedList_get(LL, size-1): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    size_t index = LinkedList_size(LL) - 1;
    TEST_ASSERT_EQUAL(LinkedList_get(LL, index), LinkedList_last_element(LL));
}

// LinkedList_count(LL, data)
void test_20() {
    TEST_MESSAGE("Test: LinkedList_count(LL, data): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_first(LL, &data1);
    LinkedList_add_first(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_first(LL, &data2);
    LinkedList_add_last(LL, &data2);
    int count = LinkedList_count(LL, &data2);
    TEST_ASSERT_EQUAL(5, count);
}

// LinkedList_contains(LL, data)
void test_21() {
    TEST_MESSAGE("Test: LinkedList_contains(LL, data): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99;
    LinkedList_add_first(LL, &data1);
    LinkedList_add_first(LL, &data2);
    bool contains = LinkedList_contains(LL, &data2);
    TEST_ASSERT_EQUAL(1, contains);
}

// LinkedList_insert_at(LL, data, index)
void test_22() {
    TEST_MESSAGE("Test: LinkedList_insert_at(LL, data, index): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data4 = -1, data5 = 10, data0 = 357, data3 = -761, data6 = 4242;
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data4);
    LinkedList_add_last(LL, &data5);

    LinkedList_insert_at(LL, &data0, 0);
    TEST_ASSERT_EQUAL(5, LinkedList_size(LL));
    TEST_ASSERT_EQUAL(&data0, LinkedList_get(LL, 0));

    LinkedList_insert_at(LL, &data3, 3);
    TEST_ASSERT_EQUAL(6, LinkedList_size(LL));
    TEST_ASSERT_EQUAL(&data3, LinkedList_get(LL, 3));

    LinkedList_insert_at(LL, &data6, 6);
    TEST_ASSERT_EQUAL(7, LinkedList_size(LL));
    TEST_ASSERT_EQUAL(&data6, LinkedList_get(LL, 6));

    TEST_ASSERT_EQUAL(0, LinkedList_is_sorted(LL));
}

// LinkedList_clone(LL)
void test_23() {
    TEST_MESSAGE("Test: LinkedList_clone(LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data3);
    LinkedList_add_last(LL, &data4);

    LinkedList *clone = LinkedList_clone(LL);

    TEST_ASSERT_EQUAL(LinkedList_size(clone), LinkedList_size(LL));
    TEST_ASSERT_EQUAL(LinkedList_is_sorted(clone), LinkedList_is_sorted(LL));
    TEST_ASSERT_EQUAL(LinkedList_sort_order(clone), LinkedList_sort_order(LL));
    TEST_ASSERT_EQUAL(LinkedList_first_element(clone), LinkedList_first_element(LL));
    TEST_ASSERT_EQUAL(LinkedList_get(clone, 2), LinkedList_get(LL, 2));
    TEST_ASSERT_EQUAL(LinkedList_last_element(clone), LinkedList_last_element(LL));
}

// LinkedList_concat(LL1, LL2)
void test_24() {
    TEST_MESSAGE("Test: LinkedList_concat(LL1, LL2): ");
    LinkedList *LL1 = LinkedList_create();
    LinkedList *LL2 = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    LinkedList_add_last(LL1, &data1);
    LinkedList_add_last(LL1, &data2);
    LinkedList_add_last(LL2, &data3);
    LinkedList_add_last(LL2, &data4);
    LinkedList *LL_new = LinkedList_concat(LL1, LL2);
    TEST_ASSERT_EQUAL(&data1, LinkedList_first_element(LL_new));
    TEST_ASSERT_EQUAL(&data4, LinkedList_last_element(LL_new));
    LinkedList *LL_new2 = LinkedList_concat(LL2, LL1);
    TEST_ASSERT_EQUAL(&data3, LinkedList_first_element(LL_new2));
    TEST_ASSERT_EQUAL(&data2, LinkedList_last_element(LL_new2));
}

// LinkedList_reverse(LL)
void test_25() {
    TEST_MESSAGE("Test: LinkedList_reverse(LL): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data3);
    LinkedList_add_last(LL, &data4);
    LinkedList *LL_reverse = LinkedList_reverse(LL);
    TEST_ASSERT_EQUAL(LinkedList_first_element(LL), LinkedList_last_element(LL_reverse));
    TEST_ASSERT_EQUAL(LinkedList_last_element(LL), LinkedList_first_element(LL_reverse));
    TEST_ASSERT_EQUAL(LinkedList_sort_order(LL), (-1)*LinkedList_sort_order(LL_reverse));
}

// LinkedList_is_equals_strict(LL1, LL2)
void test_26() {
    TEST_MESSAGE("Test: LinkedList_is_equals_strict(LL1, LL2): ");
    LinkedList *LL1 = LinkedList_create();
    LinkedList *LL2 = LinkedList_create();
    LinkedList *LL3 = LinkedList_create();
    LinkedList *LL4 = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    int data5 = 42, data6 = 99, data7 = -1, data8 = 10;

    LinkedList_add_last(LL1, &data1);
    LinkedList_add_last(LL1, &data2);
    LinkedList_add_last(LL1, &data3);
    LinkedList_add_last(LL1, &data4);

    LinkedList_add_last(LL2, &data1);
    LinkedList_add_last(LL2, &data2);
    LinkedList_add_last(LL2, &data3);
    LinkedList_add_last(LL2, &data4);

    LinkedList_add_last(LL3, &data2);
    LinkedList_add_last(LL3, &data3);
    LinkedList_add_last(LL3, &data4);

    LinkedList_add_last(LL4, &data5);
    LinkedList_add_last(LL4, &data6);
    LinkedList_add_last(LL4, &data7);
    LinkedList_add_last(LL4, &data8);

    TEST_ASSERT_EQUAL(1, LinkedList_is_equals_strict(LL1, LL2));
    TEST_ASSERT_EQUAL(0, LinkedList_is_equals_strict(LL1, LL3));
    TEST_ASSERT_EQUAL(0, LinkedList_is_equals_strict(LL1, LL4));
    TEST_ASSERT_EQUAL(0, LinkedList_is_equals_strict(LL2, LL3));
    TEST_ASSERT_EQUAL(1, LinkedList_is_equals_strict(LL3, LL3));
}

// LinkedList_is_equals(LL1, LL2, _compare_func)
void test_27() {
    TEST_MESSAGE("Test: LinkedList_is_equals(LL1, LL2, _compare_func): ");
    LinkedList *LL1 = LinkedList_create();
    LinkedList *LL2 = LinkedList_create();
    LinkedList *LL3 = LinkedList_create();
    LinkedList *LL4 = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    int data5 = 42, data6 = 99, data7 = -1, data8 = 10;

    LinkedList_add_last(LL1, &data1);
    LinkedList_add_last(LL1, &data2);
    LinkedList_add_last(LL1, &data3);
    LinkedList_add_last(LL1, &data4);

    LinkedList_add_last(LL2, &data1);
    LinkedList_add_last(LL2, &data2);
    LinkedList_add_last(LL2, &data3);
    LinkedList_add_last(LL2, &data4);

    LinkedList_add_last(LL3, &data2);
    LinkedList_add_last(LL3, &data3);
    LinkedList_add_last(LL3, &data4);

    LinkedList_add_last(LL4, &data5);
    LinkedList_add_last(LL4, &data6);
    LinkedList_add_last(LL4, &data7);
    LinkedList_add_last(LL4, &data8);

    TEST_ASSERT_EQUAL(1, LinkedList_is_equals(LL1, LL2, _compare_int));
    TEST_ASSERT_EQUAL(0, LinkedList_is_equals(LL1, LL3, _compare_int));
    TEST_ASSERT_EQUAL(1, LinkedList_is_equals(LL1, LL4, _compare_int));
    TEST_ASSERT_EQUAL(0, LinkedList_is_equals(LL2, LL3, _compare_int));
    TEST_ASSERT_EQUAL(1, LinkedList_is_equals(LL3, LL3, _compare_int));
}

// LinkedList_sort_asc(LL, _compare_func)
void test_28() {
    TEST_MESSAGE("Test: LinkedList_sort_asc(LL, _compare_func): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data3);
    LinkedList_add_last(LL, &data4);

    TEST_ASSERT_EQUAL(0, LinkedList_is_sorted(LL));
    TEST_ASSERT_EQUAL(0, LinkedList_sort_order(LL));

    LinkedList_sort_asc(LL, _compare_int);
    TEST_ASSERT_EQUAL(1, LinkedList_is_sorted(LL));
    TEST_ASSERT_EQUAL(1, LinkedList_sort_order(LL));
    TEST_ASSERT_EQUAL(&data3, LinkedList_first_element(LL));
    TEST_ASSERT_EQUAL(&data2, LinkedList_last_element(LL));
}

// LinkedList_sort_desc(LL, _compare_func)
void test_29() {
    TEST_MESSAGE("Test: LinkedList_sort_desc(LL, _compare_func): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data3);
    LinkedList_add_last(LL, &data4);

    TEST_ASSERT_EQUAL(0, LinkedList_is_sorted(LL));
    TEST_ASSERT_EQUAL(0, LinkedList_sort_order(LL));

    LinkedList_sort_desc(LL, _compare_int);
    TEST_ASSERT_EQUAL(1, LinkedList_is_sorted(LL));
    TEST_ASSERT_EQUAL(-1, LinkedList_sort_order(LL));
    TEST_ASSERT_EQUAL(&data2, LinkedList_first_element(LL));
    TEST_ASSERT_EQUAL(&data3, LinkedList_last_element(LL));
}

// LinkedList_sorted_insertion(LL, _compare_func, data)
void test_30() {
    TEST_MESSAGE("Test: LinkedList_sorted_insert(LL, _compare_func, data): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data4 = -1, data5 = 10, data0 = -35, data3 = 29, data6 = 888;

    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data4);
    LinkedList_add_last(LL, &data5);

    LinkedList_sort_asc(LL, _compare_int);

    LinkedList_sorted_insert(LL, &data0, _compare_int);
    TEST_ASSERT_EQUAL(&data0, LinkedList_get(LL, 0));
    LinkedList_sorted_insert(LL, &data3, _compare_int);
    TEST_ASSERT_EQUAL(&data3, LinkedList_get(LL, 3));
    LinkedList_sorted_insert(LL, &data6, _compare_int);
    TEST_ASSERT_EQUAL(&data6, LinkedList_get(LL, 6));
}

// LinkedList_min(LL, _compare_func)
void test_31() {
    TEST_MESSAGE("Test: LinkedList_min(LL, _compare_func): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data3);
    LinkedList_add_last(LL, &data4);

    TEST_ASSERT_EQUAL(&data3, LinkedList_min(LL, _compare_int));
    LinkedList_sort_desc(LL, _compare_int);
    TEST_ASSERT_EQUAL(&data3, LinkedList_min(LL, _compare_int));
    LinkedList_sort_asc(LL, _compare_int);
    TEST_ASSERT_EQUAL(&data3, LinkedList_min(LL, _compare_int));
}

// LinkedList_max(LL, _compare_func)
void test_32() {
    TEST_MESSAGE("Test: LinkedList_max(LL, _compare_func): ");
    LinkedList *LL = LinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    LinkedList_add_last(LL, &data1);
    LinkedList_add_last(LL, &data2);
    LinkedList_add_last(LL, &data3);
    LinkedList_add_last(LL, &data4);

    TEST_ASSERT_EQUAL(&data2, LinkedList_max(LL, _compare_int));
    LinkedList_sort_desc(LL, _compare_int);
    TEST_ASSERT_EQUAL(&data2, LinkedList_max(LL, _compare_int));
    LinkedList_sort_asc(LL, _compare_int);
    TEST_ASSERT_EQUAL(&data2, LinkedList_max(LL, _compare_int));
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
    return UNITY_END();
}
