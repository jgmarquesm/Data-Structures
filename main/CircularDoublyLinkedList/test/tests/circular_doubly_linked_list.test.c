#include "../../main/include/unity.h"
#include "../../main/include/circular_doubly_linked_list.h"

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

// CircularLinkedList_create()
void test_1() {
    TEST_MESSAGE("Test: CircularLinkedList_create(): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    bool is_empty = CircularLinkedList_is_empty(CLL);
    TEST_ASSERT_EQUAL(1, is_empty);
    TEST_ASSERT_EQUAL(0, CircularLinkedList_size(CLL));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_sorted(CLL));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_sort_order(CLL));
}

// CircularLinkedList_clean(CLL)
void test_2() {
    TEST_MESSAGE("Test: CircularLinkedList_clean(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);

    CircularLinkedList_clean(CLL);
    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_empty(CLL));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_size(CLL));
}

// CircularLinkedList_destroy(&CLL)
void test_3() {
    TEST_MESSAGE("Test: CircularLinkedList_destroy(&CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);

    CircularLinkedList_destroy(&CLL);
    TEST_ASSERT_EQUAL(NULL, CLL);
}

// CircularLinkedList_is_empty(CLL)
void test_4() {
    TEST_MESSAGE("Test: CircularLinkedList_is_empty(): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_empty(CLL));
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_empty(CLL));
}

// CircularLinkedList_is_sorted(CLL)
void test_5() {
    TEST_MESSAGE("Test: CircularLinkedList_is_sorted(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data3);
    CircularLinkedList_add_last(CLL, &data4);
    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_sorted(CLL));
    CircularLinkedList_sort_asc(&CLL, _compare_int);
    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_sorted(CLL));
    CircularLinkedList_sort_desc(&CLL, _compare_int);
    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_sorted(CLL));
}

// CircularLinkedList_sort_order(CLL)
void test_6() {
    TEST_MESSAGE("Test: CircularLinkedList_sort_order(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data3);
    CircularLinkedList_add_last(CLL, &data4);
    TEST_ASSERT_EQUAL(0, CircularLinkedList_sort_order(CLL));
    CircularLinkedList_sort_asc(&CLL, _compare_int);
    TEST_ASSERT_EQUAL(1, CircularLinkedList_sort_order(CLL));
    CircularLinkedList_sort_desc(&CLL, _compare_int);
    TEST_ASSERT_EQUAL(-1, CircularLinkedList_sort_order(CLL));
}

// CircularLinkedList_add_first(CLL)
void test_7() {
    TEST_MESSAGE("Test: CircularLinkedList_add_first(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_first_element(CLL));
}

// CircularLinkedList_add_last(CLL)
void test_8() {
    TEST_MESSAGE("Test: CircularLinkedList_add_last(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    TEST_ASSERT_EQUAL(&data1, CircularLinkedList_first_element(CLL));
}

// CircularLinkedList_remove_first(CLL)
void test_9() {
    TEST_MESSAGE("Test: CircularLinkedList_remove_first(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data0 = -1, data1 = 42, data2 = 99;
    CircularLinkedList_add_last(CLL, &data0);
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);

    size_t size_before = CircularLinkedList_size(CLL);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(&data0, CircularLinkedList_get(CLL, 0));
    TEST_ASSERT_EQUAL(&data1, CircularLinkedList_get(CLL, 1));
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_get(CLL, 2));

    CircularLinkedList_remove_first(CLL);
    size_t size_after = CircularLinkedList_size(CLL);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, CircularLinkedList_contains(CLL, &data0));
    TEST_ASSERT_EQUAL(&data1, CircularLinkedList_get(CLL, 0));
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_get(CLL, 1));
}

// CircularLinkedList_remove_last(CLL)
void test_10() {
    TEST_MESSAGE("Test: CircularLinkedList_remove_last(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data0 = -1, data1 = 42, data2 = 99;
    CircularLinkedList_add_last(CLL, &data0);
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);

    size_t size_before = CircularLinkedList_size(CLL);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(&data0, CircularLinkedList_get(CLL, 0));
    TEST_ASSERT_EQUAL(&data1, CircularLinkedList_get(CLL, 1));
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_get(CLL, 2));

    CircularLinkedList_remove_last(CLL);
    size_t size_after = CircularLinkedList_size(CLL);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, CircularLinkedList_contains(CLL, &data2));
    TEST_ASSERT_EQUAL(&data0, CircularLinkedList_get(CLL, 0));
    TEST_ASSERT_EQUAL(&data1, CircularLinkedList_get(CLL, 1));
}

// CircularLinkedList_remove_at(CLL, index)
void test_11() {
    TEST_MESSAGE("Test: CircularLinkedList_remove_at(CLL, index): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data0 = -1, data1 = 42, data2 = 99;
    CircularLinkedList_add_last(CLL, &data0);
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);

    size_t size_before = CircularLinkedList_size(CLL);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(&data0, CircularLinkedList_get(CLL, 0));
    TEST_ASSERT_EQUAL(&data1, CircularLinkedList_get(CLL, 1));
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_get(CLL, 2));

    CircularLinkedList_remove_at(CLL, 1);
    size_t size_after = CircularLinkedList_size(CLL);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, CircularLinkedList_contains(CLL, &data1));
    TEST_ASSERT_EQUAL(&data0, CircularLinkedList_get(CLL, 0));
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_get(CLL, 1));
}

// CircularLinkedList_remove(CLL, data, type_compare_func)
void test_12() {
    TEST_MESSAGE("Test: CircularLinkedList_remove(CLL, data, type_compare_func): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_first(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);

    size_t size_before = CircularLinkedList_size(CLL);
    TEST_ASSERT_EQUAL(6, size_before);
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_get(CLL, 1));

    CircularLinkedList_remove(CLL, &data1, _compare_int);
    size_t size_after = CircularLinkedList_size(CLL);
    TEST_ASSERT_EQUAL(5, size_after);
    TEST_ASSERT_EQUAL(0, CircularLinkedList_contains(CLL, &data1));
}

// CircularLinkedList_remove_all(CLL, data, type_compare_func)
void test_13() {
    TEST_MESSAGE("Test: CircularLinkedList_remove_all(CLL, data, type_compare_func): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data3);
    CircularLinkedList_add_last(CLL, &data3);

    CircularLinkedList_remove_all(CLL, &data2, _compare_int);
    TEST_ASSERT_EQUAL(0, CircularLinkedList_contains(CLL, &data2));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_contains(CLL, &data3));
    TEST_ASSERT_EQUAL(1, CircularLinkedList_size(CLL));
}

// CircularLinkedList_size(CLL)
void test_14() {
    TEST_MESSAGE("Test: CircularLinkedList_size(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42;
    int data2 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    TEST_ASSERT_EQUAL(2, CircularLinkedList_size(CLL));
}

// CircularLinkedList_first_element(CLL)
void test_15() {
    TEST_MESSAGE("Test: CircularLinkedList_first_element(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_first_element(CLL));
}

// CircularLinkedList_last_element(CLL)
void test_16() {
    TEST_MESSAGE("Test: CircularLinkedList_last_element(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_last_element(CLL));
}

// CircularLinkedList_get(CLL, index)
void test_17() {
    TEST_MESSAGE("Test: CircularLinkedList_get(CLL, index): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    size_t index = CircularLinkedList_size(CLL) - 1;
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_get(CLL, 0));
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_get(CLL, index));
}

// Consistence between CircularLinkedList_first_element(CLL) && CircularLinkedList_get(CLL, 0)
void test_18() {
    TEST_MESSAGE("Test: Consistence between CircularLinkedList_first_element(CLL) && CircularLinkedList_get(CLL, 0): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    TEST_ASSERT_EQUAL(CircularLinkedList_get(CLL, 0), CircularLinkedList_first_element(CLL));
}

// Consistence between CircularLinkedList_last_element(CLL) && CircularLinkedList_get(CLL, size-1)
void test_19() {
    TEST_MESSAGE("Test: Consistence between CircularLinkedList_last_element(CLL) && CircularLinkedList_get(CLL, size-1): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    size_t index = CircularLinkedList_size(CLL) - 1;
    TEST_ASSERT_EQUAL(CircularLinkedList_get(CLL, index), CircularLinkedList_last_element(CLL));
}

// CircularLinkedList_count(CLL, data)
void test_20() {
    TEST_MESSAGE("Test: CircularLinkedList_count(CLL, data): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_first(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data2);
    int count = CircularLinkedList_count(CLL, &data2);
    TEST_ASSERT_EQUAL(5, count);
}

// CircularLinkedList_contains(CLL, data)
void test_21() {
    TEST_MESSAGE("Test: CircularLinkedList_contains(CLL, data): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99;
    CircularLinkedList_add_first(CLL, &data1);
    CircularLinkedList_add_first(CLL, &data2);
    bool contains = CircularLinkedList_contains(CLL, &data2);
    TEST_ASSERT_EQUAL(1, contains);
}

// CircularLinkedList_insert_at(CLL, data, index)
void test_22() {
    TEST_MESSAGE("Test: CircularLinkedList_insert_at(CLL, data, index): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data4 = -1, data5 = 10, data0 = 357, data3 = -761, data6 = 4242;
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data4);
    CircularLinkedList_add_last(CLL, &data5);

    CircularLinkedList_insert_at(CLL, &data0, 0);
    TEST_ASSERT_EQUAL(5, CircularLinkedList_size(CLL));
    TEST_ASSERT_EQUAL(&data0, CircularLinkedList_get(CLL, 0));

    CircularLinkedList_insert_at(CLL, &data3, 3);
    TEST_ASSERT_EQUAL(6, CircularLinkedList_size(CLL));
    TEST_ASSERT_EQUAL(&data3, CircularLinkedList_get(CLL, 3));

    CircularLinkedList_insert_at(CLL, &data6, 6);
    TEST_ASSERT_EQUAL(7, CircularLinkedList_size(CLL));
    TEST_ASSERT_EQUAL(&data6, CircularLinkedList_get(CLL, 6));

    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_sorted(CLL));
}

// CircularLinkedList_clone(CLL)
void test_23() {
    TEST_MESSAGE("Test: CircularLinkedList_clone(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data3);
    CircularLinkedList_add_last(CLL, &data4);

    CircularLinkedList *clone = CircularLinkedList_clone(CLL);

    TEST_ASSERT_EQUAL(CircularLinkedList_size(clone), CircularLinkedList_size(CLL));
    TEST_ASSERT_EQUAL(CircularLinkedList_is_sorted(clone), CircularLinkedList_is_sorted(CLL));
    TEST_ASSERT_EQUAL(CircularLinkedList_sort_order(clone), CircularLinkedList_sort_order(CLL));
    TEST_ASSERT_EQUAL(CircularLinkedList_first_element(clone), CircularLinkedList_first_element(CLL));
    TEST_ASSERT_EQUAL(CircularLinkedList_get(clone, 2), CircularLinkedList_get(CLL, 2));
    TEST_ASSERT_EQUAL(CircularLinkedList_last_element(clone), CircularLinkedList_last_element(CLL));
}

// CircularLinkedList_concat(CLL1, CLL2)
void test_24() {
    TEST_MESSAGE("Test: CircularLinkedList_concat(CLL1, CLL2): ");
    CircularLinkedList *CLL1 = CircularLinkedList_create();
    CircularLinkedList *CLL2 = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    CircularLinkedList_add_last(CLL1, &data1);
    CircularLinkedList_add_last(CLL1, &data2);
    CircularLinkedList_add_last(CLL2, &data3);
    CircularLinkedList_add_last(CLL2, &data4);
    CircularLinkedList *CLL_new = CircularLinkedList_concat(CLL1, CLL2);
    TEST_ASSERT_EQUAL(&data1, CircularLinkedList_first_element(CLL_new));
    TEST_ASSERT_EQUAL(&data4, CircularLinkedList_last_element(CLL_new));
    CircularLinkedList *CLL_new2 = CircularLinkedList_concat(CLL2, CLL1);
    TEST_ASSERT_EQUAL(&data3, CircularLinkedList_first_element(CLL_new2));
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_last_element(CLL_new2));
}

// CircularLinkedList_reverse(CLL)
void test_25() {
    TEST_MESSAGE("Test: CircularLinkedList_reverse(CLL): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data3);
    CircularLinkedList_add_last(CLL, &data4);
    CircularLinkedList *CLL_reverse = CircularLinkedList_reverse(CLL);
    TEST_ASSERT_EQUAL(CircularLinkedList_first_element(CLL), CircularLinkedList_last_element(CLL_reverse));
    TEST_ASSERT_EQUAL(CircularLinkedList_last_element(CLL), CircularLinkedList_first_element(CLL_reverse));
    TEST_ASSERT_EQUAL(CircularLinkedList_sort_order(CLL), (-1)*CircularLinkedList_sort_order(CLL_reverse));
}

// CircularLinkedList_is_equals_strict(CLL1, CLL2)
void test_26() {
    TEST_MESSAGE("Test: CircularLinkedList_is_equals_strict(CLL1, CLL2): ");
    CircularLinkedList *CLL1 = CircularLinkedList_create();
    CircularLinkedList *CLL2 = CircularLinkedList_create();
    CircularLinkedList *CLL3 = CircularLinkedList_create();
    CircularLinkedList *CLL4 = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    int data5 = 42, data6 = 99, data7 = -1, data8 = 10;

    CircularLinkedList_add_last(CLL1, &data1);
    CircularLinkedList_add_last(CLL1, &data2);
    CircularLinkedList_add_last(CLL1, &data3);
    CircularLinkedList_add_last(CLL1, &data4);

    CircularLinkedList_add_last(CLL2, &data1);
    CircularLinkedList_add_last(CLL2, &data2);
    CircularLinkedList_add_last(CLL2, &data3);
    CircularLinkedList_add_last(CLL2, &data4);

    CircularLinkedList_add_last(CLL3, &data2);
    CircularLinkedList_add_last(CLL3, &data3);
    CircularLinkedList_add_last(CLL3, &data4);

    CircularLinkedList_add_last(CLL4, &data5);
    CircularLinkedList_add_last(CLL4, &data6);
    CircularLinkedList_add_last(CLL4, &data7);
    CircularLinkedList_add_last(CLL4, &data8);

    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_equals_strict(CLL1, CLL2));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_equals_strict(CLL1, CLL3));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_equals_strict(CLL1, CLL4));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_equals_strict(CLL2, CLL3));
    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_equals_strict(CLL3, CLL3));
}

// CircularLinkedList_is_equals(CLL1, CLL2, _compare_func)
void test_27() {
    TEST_MESSAGE("Test: CircularLinkedList_is_equals(CLL1, CLL2, _compare_func): ");
    CircularLinkedList *CLL1 = CircularLinkedList_create();
    CircularLinkedList *CLL2 = CircularLinkedList_create();
    CircularLinkedList *CLL3 = CircularLinkedList_create();
    CircularLinkedList *CLL4 = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    int data5 = 42, data6 = 99, data7 = -1, data8 = 10;

    CircularLinkedList_add_last(CLL1, &data1);
    CircularLinkedList_add_last(CLL1, &data2);
    CircularLinkedList_add_last(CLL1, &data3);
    CircularLinkedList_add_last(CLL1, &data4);

    CircularLinkedList_add_last(CLL2, &data1);
    CircularLinkedList_add_last(CLL2, &data2);
    CircularLinkedList_add_last(CLL2, &data3);
    CircularLinkedList_add_last(CLL2, &data4);

    CircularLinkedList_add_last(CLL3, &data2);
    CircularLinkedList_add_last(CLL3, &data3);
    CircularLinkedList_add_last(CLL3, &data4);

    CircularLinkedList_add_last(CLL4, &data5);
    CircularLinkedList_add_last(CLL4, &data6);
    CircularLinkedList_add_last(CLL4, &data7);
    CircularLinkedList_add_last(CLL4, &data8);

    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_equals(CLL1, CLL2, _compare_int));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_equals(CLL1, CLL3, _compare_int));
    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_equals(CLL1, CLL4, _compare_int));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_equals(CLL2, CLL3, _compare_int));
    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_equals(CLL3, CLL3, _compare_int));
}

// CircularLinkedList_sort_asc(CLL, _compare_func)
void test_28() {
    TEST_MESSAGE("Test: CircularLinkedList_sort_asc(CLL, _compare_func): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data3);
    CircularLinkedList_add_last(CLL, &data4);

    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_sorted(CLL));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_sort_order(CLL));

    CircularLinkedList_sort_asc(&CLL, _compare_int);
    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_sorted(CLL));
    TEST_ASSERT_EQUAL(1, CircularLinkedList_sort_order(CLL));
    TEST_ASSERT_EQUAL(&data3, CircularLinkedList_first_element(CLL));
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_last_element(CLL));
}

// CircularLinkedList_sort_desc(CLL, _compare_func)
void test_29() {
    TEST_MESSAGE("Test: CircularLinkedList_sort_desc(CLL, _compare_func): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data3);
    CircularLinkedList_add_last(CLL, &data4);

    TEST_ASSERT_EQUAL(0, CircularLinkedList_is_sorted(CLL));
    TEST_ASSERT_EQUAL(0, CircularLinkedList_sort_order(CLL));

    CircularLinkedList_sort_desc(&CLL, _compare_int);
    TEST_ASSERT_EQUAL(1, CircularLinkedList_is_sorted(CLL));
    TEST_ASSERT_EQUAL(-1, CircularLinkedList_sort_order(CLL));
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_first_element(CLL));
    TEST_ASSERT_EQUAL(&data3, CircularLinkedList_last_element(CLL));
}

// CircularLinkedList_sorted_insert(CLL, _compare_func, data)
void test_30() {
    TEST_MESSAGE("Test: CircularLinkedList_sorted_insert(CLL, _compare_func, data): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data4 = -1, data5 = 10, data0 = -35, data3 = 29, data6 = 888;

    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data4);
    CircularLinkedList_add_last(CLL, &data5);

    CircularLinkedList_sort_asc(&CLL, _compare_int);

    CircularLinkedList_sorted_insert(CLL, &data0, _compare_int);
    TEST_ASSERT_EQUAL(&data0, CircularLinkedList_get(CLL, 0));
    CircularLinkedList_sorted_insert(CLL, &data3, _compare_int);
    TEST_ASSERT_EQUAL(&data3, CircularLinkedList_get(CLL, 3));
    CircularLinkedList_sorted_insert(CLL, &data6, _compare_int);
    TEST_ASSERT_EQUAL(&data6, CircularLinkedList_get(CLL, 6));
}

// CircularLinkedList_min(CLL, _compare_func)
void test_31() {
    TEST_MESSAGE("Test: CircularLinkedList_min(CLL, _compare_func): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data3);
    CircularLinkedList_add_last(CLL, &data4);

    TEST_ASSERT_EQUAL(&data3, CircularLinkedList_min(CLL, _compare_int));
    CircularLinkedList_sort_desc(&CLL, _compare_int);
    TEST_ASSERT_EQUAL(&data3, CircularLinkedList_min(CLL, _compare_int));
    CircularLinkedList_sort_asc(&CLL, _compare_int);
    TEST_ASSERT_EQUAL(&data3, CircularLinkedList_min(CLL, _compare_int));
}

// CircularLinkedList_max(CLL, _compare_func)
void test_32() {
    TEST_MESSAGE("Test: CircularLinkedList_max(CLL, _compare_func): ");
    CircularLinkedList *CLL = CircularLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    CircularLinkedList_add_last(CLL, &data1);
    CircularLinkedList_add_last(CLL, &data2);
    CircularLinkedList_add_last(CLL, &data3);
    CircularLinkedList_add_last(CLL, &data4);

    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_max(CLL, _compare_int));
    CircularLinkedList_sort_desc(&CLL, _compare_int);
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_max(CLL, _compare_int));
    CircularLinkedList_sort_asc(&CLL, _compare_int);
    TEST_ASSERT_EQUAL(&data2, CircularLinkedList_max(CLL, _compare_int));
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
