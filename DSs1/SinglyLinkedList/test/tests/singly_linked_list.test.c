#include "../../main/include/unity.h"
#include "../../main/include/singly_linked_list.h"

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

// SinglyLinkedList_create()
void test_1() {
    TEST_MESSAGE("Test: SinglyLinkedList_create(): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    bool is_empty = SinglyLinkedList_is_empty(SLL);
    TEST_ASSERT_EQUAL(1, is_empty);
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_sort_order(SLL));
}

// SinglyLinkedList_clean(SLL)
void test_2() {
    TEST_MESSAGE("Test: SinglyLinkedList_clean(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);

    SinglyLinkedList_clean(SLL);
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_empty(SLL));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_size(SLL));
}

// SinglyLinkedList_destroy(&SLL)
void test_3() {
    TEST_MESSAGE("Test: SinglyLinkedList_destroy(&SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);

    SinglyLinkedList_destroy(&SLL);
    TEST_ASSERT_EQUAL(NULL, SLL);
}

// SinglyLinkedList_is_empty(SLL)
void test_4() {
    TEST_MESSAGE("Test: SinglyLinkedList_is_empty(): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_empty(SLL));
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_empty(SLL));
}

// SinglyLinkedList_is_sorted(SLL)
void test_5() {
    TEST_MESSAGE("Test: SinglyLinkedList_is_sorted(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data3);
    SinglyLinkedList_add_last(SLL, &data4);
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_sorted(SLL));
    SinglyLinkedList_sort_asc(SLL, _compare_int);
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_sorted(SLL));
    SinglyLinkedList_sort_desc(SLL, _compare_int);
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_sorted(SLL));
}

// SinglyLinkedList_sort_order(SLL)
void test_6() {
    TEST_MESSAGE("Test: SinglyLinkedList_sort_order(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data3);
    SinglyLinkedList_add_last(SLL, &data4);
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_sort_order(SLL));
    SinglyLinkedList_sort_asc(SLL, _compare_int);
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_sort_order(SLL));
    SinglyLinkedList_sort_desc(SLL, _compare_int);
    TEST_ASSERT_EQUAL(-1, SinglyLinkedList_sort_order(SLL));
}

// SinglyLinkedList_add_first(SLL)
void test_7() {
    TEST_MESSAGE("Test: SinglyLinkedList_add_first(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_first_element(SLL));
    TEST_ASSERT_EQUAL(0,  SinglyLinkedList_sort_order(SLL));
}

// SinglyLinkedList_add_last(SLL)
void test_8() {
    TEST_MESSAGE("Test: SinglyLinkedList_add_last(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    TEST_ASSERT_EQUAL(&data1, SinglyLinkedList_first_element(SLL));
    TEST_ASSERT_EQUAL(0,  SinglyLinkedList_sort_order(SLL));
}

// SinglyLinkedList_remove_first(SLL)
void test_9() {
    TEST_MESSAGE("Test: SinglyLinkedList_remove_first(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data0 = -1, data1 = 42, data2 = 99;
    SinglyLinkedList_add_last(SLL, &data0);
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);

    size_t size_before = SinglyLinkedList_size(SLL);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(&data0, SinglyLinkedList_get(SLL, 0));
    TEST_ASSERT_EQUAL(&data1, SinglyLinkedList_get(SLL, 1));
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_get(SLL, 2));

    SinglyLinkedList_remove_first(SLL);
    size_t size_after = SinglyLinkedList_size(SLL);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_contains(SLL, &data0));
    TEST_ASSERT_EQUAL(&data1, SinglyLinkedList_get(SLL, 0));
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_get(SLL, 1));
}

// SinglyLinkedList_remove_last(SLL)
void test_10() {
    TEST_MESSAGE("Test: SinglyLinkedList_remove_last(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data0 = -1, data1 = 42, data2 = 99;
    SinglyLinkedList_add_last(SLL, &data0);
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);

    size_t size_before = SinglyLinkedList_size(SLL);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(&data0, SinglyLinkedList_get(SLL, 0));
    TEST_ASSERT_EQUAL(&data1, SinglyLinkedList_get(SLL, 1));
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_get(SLL, 2));

    SinglyLinkedList_remove_last(SLL);
    size_t size_after = SinglyLinkedList_size(SLL);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_contains(SLL, &data2));
    TEST_ASSERT_EQUAL(&data0, SinglyLinkedList_get(SLL, 0));
    TEST_ASSERT_EQUAL(&data1, SinglyLinkedList_get(SLL, 1));
}

// SinglyLinkedList_remove_at(SLL, index)
void test_11() {
    TEST_MESSAGE("Test: SinglyLinkedList_remove_at(SLL, index): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data0 = -1, data1 = 42, data2 = 99;
    SinglyLinkedList_add_last(SLL, &data0);
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);

    size_t size_before = SinglyLinkedList_size(SLL);
    TEST_ASSERT_EQUAL(3, size_before);
    TEST_ASSERT_EQUAL(&data0, SinglyLinkedList_get(SLL, 0));
    TEST_ASSERT_EQUAL(&data1, SinglyLinkedList_get(SLL, 1));
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_get(SLL, 2));

    SinglyLinkedList_remove_at(SLL, 1);
    size_t size_after = SinglyLinkedList_size(SLL);
    TEST_ASSERT_EQUAL(2, size_after);
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_contains(SLL, &data1));
    TEST_ASSERT_EQUAL(&data0, SinglyLinkedList_get(SLL, 0));
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_get(SLL, 1));
}

// SinglyLinkedList_remove(SLL, data, type_compare_func)
void test_12() {
    TEST_MESSAGE("Test: SinglyLinkedList_remove(SLL, data, type_compare_func): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_first(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);

    size_t size_before = SinglyLinkedList_size(SLL);
    TEST_ASSERT_EQUAL(6, size_before);
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_get(SLL, 1));

    SinglyLinkedList_remove(SLL, &data1, _compare_int);
    size_t size_after = SinglyLinkedList_size(SLL);
    TEST_ASSERT_EQUAL(5, size_after);
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_contains(SLL, &data1));
}

// SinglyLinkedList_remove_all(SLL, data, type_compare_func)
void test_13() {
    TEST_MESSAGE("Test: SinglyLinkedList_remove_all(SLL, data, type_compare_func): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data3);
    SinglyLinkedList_add_last(SLL, &data3);

    SinglyLinkedList_remove_all(SLL, &data2, _compare_int);
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_contains(SLL, &data2));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_contains(SLL, &data3));
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));
}

// SinglyLinkedList_size(SLL)
void test_14() {
    TEST_MESSAGE("Test: SinglyLinkedList_size(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42;
    int data2 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
}

// SinglyLinkedList_first_element(SLL)
void test_15() {
    TEST_MESSAGE("Test: SinglyLinkedList_first_element(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_first_element(SLL));
}

// SinglyLinkedList_last_element(SLL)
void test_16() {
    TEST_MESSAGE("Test: SinglyLinkedList_last_element(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_last_element(SLL));
}

// SinglyLinkedList_get(SLL, index)
void test_17() {
    TEST_MESSAGE("Test: SinglyLinkedList_get(SLL, index): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    size_t index = SinglyLinkedList_size(SLL) - 1;
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_get(SLL, 0));
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_get(SLL, index));
}

// Consistence between SinglyLinkedList_first_element(SLL) && SinglyLinkedList_get(SLL, 0)
void test_18() {
    TEST_MESSAGE("Test: Consistence between SinglyLinkedList_first_element(SLL) && SinglyLinkedList_get(SLL, 0): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    TEST_ASSERT_EQUAL(SinglyLinkedList_get(SLL, 0), SinglyLinkedList_first_element(SLL));
}

// Consistence between SinglyLinkedList_last_element(SLL) && SinglyLinkedList_get(SLL, size-1)
void test_19() {
    TEST_MESSAGE("Test: Consistence between SinglyLinkedList_last_element(SLL) && SinglyLinkedList_get(SLL, size-1): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    size_t index = SinglyLinkedList_size(SLL) - 1;
    TEST_ASSERT_EQUAL(SinglyLinkedList_get(SLL, index), SinglyLinkedList_last_element(SLL));
}

// SinglyLinkedList_count(SLL, data)
void test_20() {
    TEST_MESSAGE("Test: SinglyLinkedList_count(SLL, data): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_first(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data2);
    int count = SinglyLinkedList_count(SLL, &data2);
    TEST_ASSERT_EQUAL(5, count);
}

// SinglyLinkedList_contains(SLL, data)
void test_21() {
    TEST_MESSAGE("Test: SinglyLinkedList_contains(SLL, data): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99;
    SinglyLinkedList_add_first(SLL, &data1);
    SinglyLinkedList_add_first(SLL, &data2);
    bool contains = SinglyLinkedList_contains(SLL, &data2);
    TEST_ASSERT_EQUAL(1, contains);
}

// SinglyLinkedList_insert_at(SLL, data, index)
void test_22() {
    TEST_MESSAGE("Test: SinglyLinkedList_insert_at(SLL, data, index): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data4 = -1, data5 = 10, data0 = 357, data3 = -761, data6 = 4242;
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data4);
    SinglyLinkedList_add_last(SLL, &data5);

    SinglyLinkedList_insert_at(SLL, &data0, 0);
    TEST_ASSERT_EQUAL(5, SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(&data0, SinglyLinkedList_get(SLL, 0));

    SinglyLinkedList_insert_at(SLL, &data3, 3);
    TEST_ASSERT_EQUAL(6, SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(&data3, SinglyLinkedList_get(SLL, 3));

    SinglyLinkedList_insert_at(SLL, &data6, 6);
    TEST_ASSERT_EQUAL(7, SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(&data6, SinglyLinkedList_get(SLL, 6));

    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_sorted(SLL));
}

// SinglyLinkedList_clone(SLL)
void test_23() {
    TEST_MESSAGE("Test: SinglyLinkedList_clone(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data3);
    SinglyLinkedList_add_last(SLL, &data4);

    SinglyLinkedList *clone = SinglyLinkedList_clone(SLL);

    TEST_ASSERT_EQUAL(SinglyLinkedList_size(clone), SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(SinglyLinkedList_is_sorted(clone), SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(SinglyLinkedList_sort_order(clone), SinglyLinkedList_sort_order(SLL));
    TEST_ASSERT_EQUAL(SinglyLinkedList_first_element(clone), SinglyLinkedList_first_element(SLL));
    TEST_ASSERT_EQUAL(SinglyLinkedList_get(clone, 2), SinglyLinkedList_get(SLL, 2));
    TEST_ASSERT_EQUAL(SinglyLinkedList_last_element(clone), SinglyLinkedList_last_element(SLL));
}

// SinglyLinkedList_concat(SLL1, SLL2)
void test_24() {
    TEST_MESSAGE("Test: SinglyLinkedList_concat(SLL1, SLL2): ");
    SinglyLinkedList *SLL1 = SinglyLinkedList_create();
    SinglyLinkedList *SLL2 = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    SinglyLinkedList_add_last(SLL1, &data1);
    SinglyLinkedList_add_last(SLL1, &data2);
    SinglyLinkedList_add_last(SLL2, &data3);
    SinglyLinkedList_add_last(SLL2, &data4);
    SinglyLinkedList *SLL_new = SinglyLinkedList_concat(SLL1, SLL2);
    TEST_ASSERT_EQUAL(&data1, SinglyLinkedList_first_element(SLL_new));
    TEST_ASSERT_EQUAL(&data4, SinglyLinkedList_last_element(SLL_new));
    SinglyLinkedList *SLL_new2 = SinglyLinkedList_concat(SLL2, SLL1);
    TEST_ASSERT_EQUAL(&data3, SinglyLinkedList_first_element(SLL_new2));
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_last_element(SLL_new2));
}

// SinglyLinkedList_reverse(SLL)
void test_25() {
    TEST_MESSAGE("Test: SinglyLinkedList_reverse(SLL): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data3);
    SinglyLinkedList_add_last(SLL, &data4);
    SinglyLinkedList *SLL_reverse = SinglyLinkedList_reverse(SLL);
    TEST_ASSERT_EQUAL(SinglyLinkedList_first_element(SLL), SinglyLinkedList_last_element(SLL_reverse));
    TEST_ASSERT_EQUAL(SinglyLinkedList_last_element(SLL), SinglyLinkedList_first_element(SLL_reverse));
    TEST_ASSERT_EQUAL(SinglyLinkedList_sort_order(SLL), (-1)*SinglyLinkedList_sort_order(SLL_reverse));
}

// SinglyLinkedList_is_equals_strict(SLL1, SLL2)
void test_26() {
    TEST_MESSAGE("Test: SinglyLinkedList_is_equals_strict(SLL1, SLL2): ");
    SinglyLinkedList *SLL1 = SinglyLinkedList_create();
    SinglyLinkedList *SLL2 = SinglyLinkedList_create();
    SinglyLinkedList *SLL3 = SinglyLinkedList_create();
    SinglyLinkedList *SLL4 = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    int data5 = 42, data6 = 99, data7 = -1, data8 = 10;

    SinglyLinkedList_add_last(SLL1, &data1);
    SinglyLinkedList_add_last(SLL1, &data2);
    SinglyLinkedList_add_last(SLL1, &data3);
    SinglyLinkedList_add_last(SLL1, &data4);

    SinglyLinkedList_add_last(SLL2, &data1);
    SinglyLinkedList_add_last(SLL2, &data2);
    SinglyLinkedList_add_last(SLL2, &data3);
    SinglyLinkedList_add_last(SLL2, &data4);

    SinglyLinkedList_add_last(SLL3, &data2);
    SinglyLinkedList_add_last(SLL3, &data3);
    SinglyLinkedList_add_last(SLL3, &data4);

    SinglyLinkedList_add_last(SLL4, &data5);
    SinglyLinkedList_add_last(SLL4, &data6);
    SinglyLinkedList_add_last(SLL4, &data7);
    SinglyLinkedList_add_last(SLL4, &data8);

    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_equals_strict(SLL1, SLL2));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_equals_strict(SLL1, SLL3));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_equals_strict(SLL1, SLL4));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_equals_strict(SLL2, SLL3));
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_equals_strict(SLL3, SLL3));
}

// SinglyLinkedList_is_equals(SLL1, SLL2, _compare_func)
void test_27() {
    TEST_MESSAGE("Test: SinglyLinkedList_is_equals(SLL1, SLL2, _compare_func): ");
    SinglyLinkedList *SLL1 = SinglyLinkedList_create();
    SinglyLinkedList *SLL2 = SinglyLinkedList_create();
    SinglyLinkedList *SLL3 = SinglyLinkedList_create();
    SinglyLinkedList *SLL4 = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    int data5 = 42, data6 = 99, data7 = -1, data8 = 10;

    SinglyLinkedList_add_last(SLL1, &data1);
    SinglyLinkedList_add_last(SLL1, &data2);
    SinglyLinkedList_add_last(SLL1, &data3);
    SinglyLinkedList_add_last(SLL1, &data4);

    SinglyLinkedList_add_last(SLL2, &data1);
    SinglyLinkedList_add_last(SLL2, &data2);
    SinglyLinkedList_add_last(SLL2, &data3);
    SinglyLinkedList_add_last(SLL2, &data4);

    SinglyLinkedList_add_last(SLL3, &data2);
    SinglyLinkedList_add_last(SLL3, &data3);
    SinglyLinkedList_add_last(SLL3, &data4);

    SinglyLinkedList_add_last(SLL4, &data5);
    SinglyLinkedList_add_last(SLL4, &data6);
    SinglyLinkedList_add_last(SLL4, &data7);
    SinglyLinkedList_add_last(SLL4, &data8);

    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_equals(SLL1, SLL2, _compare_int));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_equals(SLL1, SLL3, _compare_int));
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_equals(SLL1, SLL4, _compare_int));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_equals(SLL2, SLL3, _compare_int));
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_equals(SLL3, SLL3, _compare_int));
}

// SinglyLinkedList_sort_asc(SLL, _compare_func)
void test_28() {
    TEST_MESSAGE("Test: SinglyLinkedList_sort_asc(SLL, _compare_func): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data3);
    SinglyLinkedList_add_last(SLL, &data4);

    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_sort_order(SLL));

    SinglyLinkedList_sort_asc(SLL, _compare_int);
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_sort_order(SLL));
    TEST_ASSERT_EQUAL(&data3, SinglyLinkedList_first_element(SLL));
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_last_element(SLL));
}

// SinglyLinkedList_sort_desc(SLL, _compare_func)
void test_29() {
    TEST_MESSAGE("Test: SinglyLinkedList_sort_desc(SLL, _compare_func): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data3);
    SinglyLinkedList_add_last(SLL, &data4);

    TEST_ASSERT_EQUAL(0, SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_sort_order(SLL));

    SinglyLinkedList_sort_desc(SLL, _compare_int);
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(-1, SinglyLinkedList_sort_order(SLL));
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_first_element(SLL));
    TEST_ASSERT_EQUAL(&data3, SinglyLinkedList_last_element(SLL));
}

// SinglyLinkedList_sorted_insert(SLL, _compare_func, data)
void test_30() {
    TEST_MESSAGE("Test: SinglyLinkedList_sorted_insert(SLL, _compare_func, data): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data4 = -1, data5 = 10, data0 = -35, data3 = 29, data6 = 888;

    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data4);
    SinglyLinkedList_add_last(SLL, &data5);

    SinglyLinkedList_sort_asc(SLL, _compare_int);

    SinglyLinkedList_sorted_insert(SLL, &data0, _compare_int);
    TEST_ASSERT_EQUAL(&data0, SinglyLinkedList_get(SLL, 0));
    SinglyLinkedList_sorted_insert(SLL, &data3, _compare_int);
    TEST_ASSERT_EQUAL(&data3, SinglyLinkedList_get(SLL, 3));
    SinglyLinkedList_sorted_insert(SLL, &data6, _compare_int);
    TEST_ASSERT_EQUAL(&data6, SinglyLinkedList_get(SLL, 6));
}

// SinglyLinkedList_min(SLL, _compare_func)
void test_31() {
    TEST_MESSAGE("Test: SinglyLinkedList_min(SLL, _compare_func): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data3);
    SinglyLinkedList_add_last(SLL, &data4);

    TEST_ASSERT_EQUAL(&data3, SinglyLinkedList_min(SLL, _compare_int));
    SinglyLinkedList_sort_desc(SLL, _compare_int);
    TEST_ASSERT_EQUAL(&data3, SinglyLinkedList_min(SLL, _compare_int));
    SinglyLinkedList_sort_asc(SLL, _compare_int);
    TEST_ASSERT_EQUAL(&data3, SinglyLinkedList_min(SLL, _compare_int));
}

// SinglyLinkedList_max(SLL, _compare_func)
void test_32() {
    TEST_MESSAGE("Test: SinglyLinkedList_max(SLL, _compare_func): ");
    SinglyLinkedList *SLL = SinglyLinkedList_create();
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    SinglyLinkedList_add_last(SLL, &data1);
    SinglyLinkedList_add_last(SLL, &data2);
    SinglyLinkedList_add_last(SLL, &data3);
    SinglyLinkedList_add_last(SLL, &data4);

    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_max(SLL, _compare_int));
    SinglyLinkedList_sort_desc(SLL, _compare_int);
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_max(SLL, _compare_int));
    SinglyLinkedList_sort_asc(SLL, _compare_int);
    TEST_ASSERT_EQUAL(&data2, SinglyLinkedList_max(SLL, _compare_int));
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
