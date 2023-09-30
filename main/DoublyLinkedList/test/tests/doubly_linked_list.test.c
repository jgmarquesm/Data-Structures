#include "../../main/include/unity.h"
#include "../../main/include/doubly_linked_list.h"

#define TYPE int
#define UNSORTED 0
#define ASC 1
#define DESC -1
#define NEW_DLL DoublyLinkedList_create()

void setUp(){}

void tearDown(){}

TYPE _convert_to_TYPE(void *data){
    return *((TYPE *)data);
}

int _compare_TYPE(void *data1, void *data2){
    TYPE d1 = _convert_to_TYPE(data1), d2 = _convert_to_TYPE(data2);
    return d2 - d1;
}

void test_DoublyLinkedList_create_1() {
    DoublyLinkedList *DLL = NULL;

    DLL = NEW_DLL;
    TEST_ASSERT_NOT_NULL(DLL);
    TEST_ASSERT_TRUE(DoublyLinkedList_is_empty(DLL));
    TEST_ASSERT_EQUAL(0, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_clean_1() {
    TEST_MESSAGE("Case 1 --> Non NULL DoublyLinkedList:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_first(DLL, &d1);
    DoublyLinkedList_add_first(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    TEST_ASSERT_FALSE(DoublyLinkedList_is_empty(DLL));

    bool cleaned = DoublyLinkedList_clean(DLL);
    TEST_ASSERT_TRUE(cleaned);
    TEST_ASSERT_TRUE(DoublyLinkedList_is_empty(DLL));
}

void test_DoublyLinkedList_clean_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    bool cleaned = DoublyLinkedList_clean(DLL);
    TEST_ASSERT_FALSE(cleaned);
}

void test_DoublyLinkedList_destroy_1() {
    TEST_MESSAGE("Case 1 --> Non NULL DoublyLinkedList:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_first(DLL, &d1);
    DoublyLinkedList_add_first(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);

    bool destroyed = DoublyLinkedList_destroy(&DLL);
    TEST_ASSERT_TRUE(destroyed);
    TEST_ASSERT_NULL(DLL);
}

void test_DoublyLinkedList_destroy_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    bool destroyed = DoublyLinkedList_destroy(&DLL);
    TEST_ASSERT_FALSE(destroyed);
}

void test_DoublyLinkedList_is_empty_1() {
    TEST_MESSAGE("Case 1--> Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    TEST_ASSERT_TRUE(DoublyLinkedList_is_empty(DLL));
}

void test_DoublyLinkedList_is_empty_2() {
    TEST_MESSAGE("Case 2--> Non Empty DoublyLinkedList:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_empty(DLL));
}

void test_DoublyLinkedList_is_empty_3() {
    TEST_MESSAGE("Case 3--> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    TEST_ASSERT_TRUE(DoublyLinkedList_is_empty(DLL));
}

void test_DoublyLinkedList_is_sorted_1() {
    TEST_MESSAGE("Case 1--> Unsorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d5);
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_is_sorted_2() {
    TEST_MESSAGE("Case 2--> Ascending Sorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d5);
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_sort_asc(DLL, _compare_TYPE);

    TEST_ASSERT_TRUE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(ASC, DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_is_sorted_3() {
    TEST_MESSAGE("Case 3--> Descending Sorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d5);
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_sort_desc(DLL, _compare_TYPE);

    TEST_ASSERT_TRUE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(DESC, DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_is_sorted_4() {
    TEST_MESSAGE("Case 4--> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(DLL));
}

void test_DoublyLinkedList_sort_order_1() {
    TEST_MESSAGE("Case 1--> Unsorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d5);
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);

    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_sort_order_2() {
    TEST_MESSAGE("Case 2--> Ascending Sorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d5);
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_sort_asc(DLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(ASC, DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_sort_order_3() {
    TEST_MESSAGE("Case 3--> Descending Sorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d5);
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_sort_desc(DLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(DESC, DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_sort_order_4() {
    TEST_MESSAGE("Case 4--> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_add_first_1() {
    TEST_MESSAGE("Case 1 --> Adding on a Unsorted DoublyLinkedList:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_first(DLL, &d1);
    DoublyLinkedList_add_first(DLL, &d2);

    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_first_element(DLL));
    TEST_ASSERT_EQUAL(0,  DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_add_first_2() {
    TEST_MESSAGE("Case 2 --> Adding on a Sorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_first(DLL, &d1);
    DoublyLinkedList_add_first(DLL, &d2);
    DoublyLinkedList_sort_asc(DLL, _compare_TYPE);

    bool added = DoublyLinkedList_add_first(DLL, &d3);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_first_element(DLL));
    TEST_ASSERT_EQUAL(UNSORTED,  DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_add_first_3() {
    TEST_MESSAGE("Case 3 --> NULL DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NULL;

    bool added = DoublyLinkedList_add_first(DLL, &d1);
    TEST_ASSERT_FALSE(added);
}

void test_DoublyLinkedList_add_first_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    DoublyLinkedList *DLL = NEW_DLL;

    bool added = DoublyLinkedList_add_first(DLL, NULL);
    TEST_ASSERT_FALSE(added);
}

void test_DoublyLinkedList_add_first_5() {
    TEST_MESSAGE("Case 5 --> Adding NULL data on a Sorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_first(DLL, &d1);
    DoublyLinkedList_add_first(DLL, &d2);
    DoublyLinkedList_sort_asc(DLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));

    bool added = DoublyLinkedList_add_first(DLL, NULL);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_first_element(DLL));
    TEST_ASSERT_EQUAL(ASC,  DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_add_last_1() {
    TEST_MESSAGE("Case 1 --> Adding on a Unsorted DoublyLinkedList:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);

    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_last_element(DLL));
    TEST_ASSERT_EQUAL(0,  DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_add_last_2() {
    TEST_MESSAGE("Case 2 --> Adding on a Sorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_sort_asc(DLL, _compare_TYPE);

    bool added = DoublyLinkedList_add_last(DLL, &d3);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_last_element(DLL));
    TEST_ASSERT_EQUAL(UNSORTED,  DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_add_last_3() {
    TEST_MESSAGE("Case 3 --> NULL DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NULL;

    bool added = DoublyLinkedList_add_last(DLL, &d1);
    TEST_ASSERT_FALSE(added);
}

void test_DoublyLinkedList_add_last_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    DoublyLinkedList *DLL = NEW_DLL;

    bool added = DoublyLinkedList_add_last(DLL, NULL);
    TEST_ASSERT_FALSE(added);
}

void test_DoublyLinkedList_add_last_5() {
    TEST_MESSAGE("Case 5 --> Adding NULL data on a Sorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_sort_asc(DLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));

    bool added = DoublyLinkedList_add_last(DLL, NULL);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_last_element(DLL));
    TEST_ASSERT_EQUAL(ASC,  DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_remove_first_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList");
    TYPE d1, d2, d3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);

    TEST_ASSERT_EQUAL(3, DoublyLinkedList_size(DLL));
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_first_element(DLL));

    DoublyLinkedList_remove_first(DLL);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d1));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_first_element(DLL));
}

void test_DoublyLinkedList_remove_first_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList");
    DoublyLinkedList *DLL = NULL;

    void *removed = DoublyLinkedList_remove_first(DLL);
    TEST_ASSERT_NULL(removed);
}

void test_DoublyLinkedList_remove_first_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList");
    DoublyLinkedList *DLL = NEW_DLL;

    void *removed = DoublyLinkedList_remove_first(DLL);
    TEST_ASSERT_NULL(removed);
}

void test_DoublyLinkedList_remove_last_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList");
    TYPE d1, d2, d3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);

    TEST_ASSERT_EQUAL(3, DoublyLinkedList_size(DLL));
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_last_element(DLL));

    DoublyLinkedList_remove_last(DLL);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d3));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_last_element(DLL));
}

void test_DoublyLinkedList_remove_last_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList");
    DoublyLinkedList *DLL = NULL;

    void *removed = DoublyLinkedList_remove_last(DLL);
    TEST_ASSERT_NULL(removed);
}

void test_DoublyLinkedList_remove_last_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList");
    DoublyLinkedList *DLL = NEW_DLL;

    void *removed = DoublyLinkedList_remove_last(DLL);
    TEST_ASSERT_NULL(removed);
}

void test_DoublyLinkedList_remove_at_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList and valid index:");
    TYPE d1, d2, d3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);

    TEST_ASSERT_EQUAL(3, DoublyLinkedList_size(DLL));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_get(DLL, 1));
    TEST_ASSERT_TRUE(DoublyLinkedList_contains(DLL, &d2));

    void *removed = DoublyLinkedList_remove_at(DLL, 1);
    TEST_ASSERT_EQUAL(&d2, removed);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d2));
}

void test_DoublyLinkedList_remove_at_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    void *removed = DoublyLinkedList_remove_at(DLL, 1);
    TEST_ASSERT_NULL(removed);
}

void test_DoublyLinkedList_remove_at_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    void *removed = DoublyLinkedList_remove_at(DLL, 1);
    TEST_ASSERT_NULL(removed);
}

void test_DoublyLinkedList_remove_at_4() {
    TEST_MESSAGE("Case 4 --> Index < 0:");
    TYPE d1, d2, d3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);

    TEST_ASSERT_EQUAL(3, DoublyLinkedList_size(DLL));

    void *removed = DoublyLinkedList_remove_at(DLL, -1);
    TEST_ASSERT_NULL(removed);
    TEST_ASSERT_EQUAL(3, DoublyLinkedList_size(DLL));
}

void test_DoublyLinkedList_remove_at_5() {
    TEST_MESSAGE("Case 5 --> size <= Index:");
    TYPE d1, d2, d3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);

    TEST_ASSERT_EQUAL(3, DoublyLinkedList_size(DLL));

    void *removed = DoublyLinkedList_remove_at(DLL, DoublyLinkedList_size(DLL));
    void *removed_2 = DoublyLinkedList_remove_at(DLL, DoublyLinkedList_size(DLL) + 1);
    TEST_ASSERT_NULL(removed);
    TEST_ASSERT_NULL(removed_2);
    TEST_ASSERT_EQUAL(3, DoublyLinkedList_size(DLL));
}

void test_DoublyLinkedList_remove_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList and Non NULL Data:");
    TYPE d1 = 1, d2 = 2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);

    TEST_ASSERT_EQUAL(6, DoublyLinkedList_size(DLL));
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_get(DLL, 0));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_get(DLL, 1));

    bool removed = DoublyLinkedList_remove(DLL, &d1, _compare_TYPE);
    TEST_ASSERT_TRUE(removed);
    TEST_ASSERT_EQUAL(5, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d1));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_get(DLL, 0));
}

void test_DoublyLinkedList_remove_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NULL;

    bool removed = DoublyLinkedList_remove(DLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
}

void test_DoublyLinkedList_remove_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;

    bool removed = DoublyLinkedList_remove(DLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
}

void test_DoublyLinkedList_remove_4() {
    TEST_MESSAGE("Case 4 --> NULL data:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));

    bool removed = DoublyLinkedList_remove(DLL, NULL, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));
}

void test_DoublyLinkedList_remove_5() {
    TEST_MESSAGE("Case 5 --> Data not in DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);

    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d3));

    bool removed = DoublyLinkedList_remove(DLL, &d3, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
}

void test_DoublyLinkedList_remove_all_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList and Non NULL Data:");
    TYPE d1 = 1, d2 = 2, d2_2 = 2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2_2);
    DoublyLinkedList_add_last(DLL, &d2_2);
    TEST_ASSERT_EQUAL(7, DoublyLinkedList_size(DLL));

    size_t removed = DoublyLinkedList_remove_all(DLL, &d2, _compare_TYPE);
    TEST_ASSERT_EQUAL(6, removed);
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d2));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d2_2));
    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));
}

void test_DoublyLinkedList_remove_all_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NULL;

    size_t removed = DoublyLinkedList_remove_all(DLL, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
}

void test_DoublyLinkedList_remove_all_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;

    size_t removed = DoublyLinkedList_remove_all(DLL, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
}

void test_DoublyLinkedList_remove_all_4() {
    TEST_MESSAGE("Case 4 --> NULL data:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));

    size_t removed = DoublyLinkedList_remove_all(DLL, NULL, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));
}

void test_DoublyLinkedList_remove_all_5() {
    TEST_MESSAGE("Case 5 --> Data not in DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);

    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d3));

    size_t removed = DoublyLinkedList_remove_all(DLL, &d3, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
}

void test_DoublyLinkedList_size_1() {
    TEST_MESSAGE("Case 1 --> Non NULL DoublyLinkedList:");
    TYPE d1, d2, d3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    TEST_ASSERT_EQUAL(3, DoublyLinkedList_size(DLL));
}

void test_DoublyLinkedList_size_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;
    TEST_ASSERT_EQUAL(0, DoublyLinkedList_size(DLL));
}

void test_DoublyLinkedList_size_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;
    TEST_ASSERT_EQUAL(0, DoublyLinkedList_size(DLL));
}

void test_DoublyLinkedList_first_element_1() {
    TEST_MESSAGE("Case 1: Non NULL Non Empty DoublyLinkedList:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_first(DLL, &d1);
    DoublyLinkedList_add_first(DLL, &d2);

    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_first_element(DLL));
}

void test_DoublyLinkedList_first_element_2() {
    TEST_MESSAGE("Case 2: NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    TEST_ASSERT_NULL(DoublyLinkedList_first_element(DLL));
}

void test_DoublyLinkedList_first_element_3() {
    TEST_MESSAGE("Case 3: Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    TEST_ASSERT_NULL(DoublyLinkedList_first_element(DLL));
}

void test_DoublyLinkedList_last_element_1() {
    TEST_MESSAGE("Case 1: Non NULL Non Empty DoublyLinkedList:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);

    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_last_element(DLL));
}

void test_DoublyLinkedList_last_element_2() {
    TEST_MESSAGE("Case 2: NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    TEST_ASSERT_NULL(DoublyLinkedList_last_element(DLL));
}

void test_DoublyLinkedList_last_element_3() {
    TEST_MESSAGE("Case 3: Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    TEST_ASSERT_NULL(DoublyLinkedList_last_element(DLL));
}

void test_DoublyLinkedList_get_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList and valid index:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_add_last(DLL, &d4);

    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_get(DLL, 0));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_get(DLL, 1));
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_get(DLL, 2));
    TEST_ASSERT_EQUAL(&d4, DoublyLinkedList_get(DLL, 3));
}

void test_DoublyLinkedList_get_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    TEST_ASSERT_NULL(DoublyLinkedList_get(DLL, 0));
}

void test_DoublyLinkedList_get_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    TEST_ASSERT_NULL(DoublyLinkedList_get(DLL, 0));
}

void test_DoublyLinkedList_get_4() {
    TEST_MESSAGE("Case 4 --> Index < 0:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    TEST_ASSERT_NULL(DoublyLinkedList_get(DLL, -1));
}

void test_DoublyLinkedList_get_5() {
    TEST_MESSAGE("Case 5 --> size <= Index:");
    TYPE d1, d2, d3;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);

    TEST_ASSERT_NULL(DoublyLinkedList_get(DLL, DoublyLinkedList_size(DLL)));
    TEST_ASSERT_NULL(DoublyLinkedList_get(DLL, DoublyLinkedList_size(DLL) + 1));
}

void test_consistence_between_first_element_and_get_at_0() {
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_add_last(DLL, &d4);

    TEST_ASSERT_EQUAL(DoublyLinkedList_get(DLL, 0), DoublyLinkedList_first_element(DLL));
}

void test_consistence_between_last_element_and_get_at_size_minus_1() {
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_add_last(DLL, &d4);

    size_t index = DoublyLinkedList_size(DLL) - 1;
    TEST_ASSERT_EQUAL(DoublyLinkedList_get(DLL, index), DoublyLinkedList_last_element(DLL));
}

void test_DoublyLinkedList_count_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList and Non NULL Data:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d2);

    TYPE count = DoublyLinkedList_count(DLL, &d2);
    TEST_ASSERT_EQUAL(5, count);
}

void test_DoublyLinkedList_count_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NULL;

    TYPE count = DoublyLinkedList_count(DLL, &d1);
    TEST_ASSERT_EQUAL(0, count);
}

void test_DoublyLinkedList_count_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;

    TYPE count = DoublyLinkedList_count(DLL, &d1);
    TEST_ASSERT_EQUAL(0, count);
}

void test_DoublyLinkedList_count_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    TYPE count = DoublyLinkedList_count(DLL, NULL);
    TEST_ASSERT_EQUAL(0, count);
}

void test_DoublyLinkedList_count_5() {
    TEST_MESSAGE("Case 5 --> Data not in DoublyLinkedList");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    TYPE count = DoublyLinkedList_count(DLL, &d2);
    TEST_ASSERT_EQUAL(0, count);
}

void test_DoublyLinkedList_contains_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList and Non NULL Data:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);

    bool contains = DoublyLinkedList_contains(DLL, &d2);
    TEST_ASSERT_TRUE(contains);
}

void test_DoublyLinkedList_contains_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NULL;

    bool contains = DoublyLinkedList_contains(DLL, &d1);
    TEST_ASSERT_FALSE(contains);
}

void test_DoublyLinkedList_contains_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;

    bool contains = DoublyLinkedList_contains(DLL, &d1);
    TEST_ASSERT_FALSE(contains);
}

void test_DoublyLinkedList_contains_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    bool contains = DoublyLinkedList_contains(DLL, NULL);
    TEST_ASSERT_FALSE(contains);
}

void test_DoublyLinkedList_contains_5() {
    TEST_MESSAGE("Case 5 --> Data not in DoublyLinkedList");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    bool contains = DoublyLinkedList_contains(DLL, &d2);
    TEST_ASSERT_FALSE(contains);
}

void test_DoublyLinkedList_insert_at_1() {
    TEST_MESSAGE("Case 1 --> Unsorted DoublyLinkedList and valid index");
    TYPE d1, d2, d3, d4, d5;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d5);

    TEST_ASSERT_EQUAL(4, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d3));
    TEST_ASSERT_EQUAL(&d4, DoublyLinkedList_get(DLL, 2));

    bool added = DoublyLinkedList_insert_at(DLL, &d3, 2);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(5, DoublyLinkedList_size(DLL));
    TEST_ASSERT_TRUE(DoublyLinkedList_contains(DLL, &d3));
    TEST_ASSERT_NOT_EQUAL(&d4, DoublyLinkedList_get(DLL, 2));
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_get(DLL, 2));
}

void test_DoublyLinkedList_insert_at_2() {
    TEST_MESSAGE("Case 2 --> Ascending Sorted DoublyLinkedList and valid index");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d5);

    DoublyLinkedList_sort_asc(DLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(4, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d3));
    TEST_ASSERT_EQUAL(&d4, DoublyLinkedList_get(DLL, 2));
    TEST_ASSERT_TRUE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(ASC, DoublyLinkedList_sort_order(DLL));

    bool added = DoublyLinkedList_insert_at(DLL, &d3, 2);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(5, DoublyLinkedList_size(DLL));
    TEST_ASSERT_TRUE(DoublyLinkedList_contains(DLL, &d3));
    TEST_ASSERT_NOT_EQUAL(&d4, DoublyLinkedList_get(DLL, 2));
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_get(DLL, 2));
    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_insert_at_3() {
    TEST_MESSAGE("Case 2 --> Descending Sorted DoublyLinkedList and valid index");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d5);

    DoublyLinkedList_sort_desc(DLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(4, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d3));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_get(DLL, 2));
    TEST_ASSERT_TRUE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(DESC, DoublyLinkedList_sort_order(DLL));

    bool added = DoublyLinkedList_insert_at(DLL, &d3, 2);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(5, DoublyLinkedList_size(DLL));
    TEST_ASSERT_TRUE(DoublyLinkedList_contains(DLL, &d3));
    TEST_ASSERT_NOT_EQUAL(&d2, DoublyLinkedList_get(DLL, 2));
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_get(DLL, 2));
    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(DLL));
}

void test_DoublyLinkedList_insert_at_4() {
    TEST_MESSAGE("Case 4 --> Insert at 0:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d2);

    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d1));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_get(DLL, 0));

    bool added = DoublyLinkedList_insert_at(DLL, &d1, 0);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
    TEST_ASSERT_TRUE(DoublyLinkedList_contains(DLL, &d1));
    TEST_ASSERT_NOT_EQUAL(&d2, DoublyLinkedList_get(DLL, 0));
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_get(DLL, 0));
}

void test_DoublyLinkedList_insert_at_5() {
    TEST_MESSAGE("Case 5 --> Insert at index = size:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d2));
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_get(DLL, DoublyLinkedList_size(DLL) - 1));

    bool added = DoublyLinkedList_insert_at(DLL, &d2, DoublyLinkedList_size(DLL));
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(2, DoublyLinkedList_size(DLL));
    TEST_ASSERT_TRUE(DoublyLinkedList_contains(DLL, &d2));
    TEST_ASSERT_NOT_EQUAL(&d1, DoublyLinkedList_get(DLL, DoublyLinkedList_size(DLL) - 1));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_get(DLL, DoublyLinkedList_size(DLL) - 1));
}

void test_DoublyLinkedList_insert_at_6() {
    TEST_MESSAGE("Case 6 --> NULL DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NULL;

    bool added = DoublyLinkedList_insert_at(DLL, &d1, 0);
    TEST_ASSERT_FALSE(added);
}

void test_DoublyLinkedList_insert_at_7() {
    TEST_MESSAGE("Case 7 --> NULL Data:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    bool added = DoublyLinkedList_insert_at(DLL, NULL, 0);
    TEST_ASSERT_FALSE(added);
}

void test_DoublyLinkedList_insert_at_8() {
    TEST_MESSAGE("Case 8 --> Empty DoublyLinkedList and index = 0:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;

    bool added = DoublyLinkedList_insert_at(DLL, &d1, 0);
    TEST_ASSERT_TRUE(added);
}

void test_DoublyLinkedList_insert_at_9() {
    TEST_MESSAGE("Case 9 --> Empty DoublyLinkedList and index != 0:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;

    bool added = DoublyLinkedList_insert_at(DLL, &d1, 1);
    TEST_ASSERT_FALSE(added);
}

void test_DoublyLinkedList_insert_at_10() {
    TEST_MESSAGE("Case 10 --> Index < 0:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d2));

    bool added = DoublyLinkedList_insert_at(DLL, &d2, -1);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d2));
}

void test_DoublyLinkedList_insert_at_11() {
    TEST_MESSAGE("Case 11 --> size < Index:");
    TYPE d1, d2;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);

    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d2));

    bool added = DoublyLinkedList_insert_at(DLL, &d2, DoublyLinkedList_size(DLL) + 1);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(1, DoublyLinkedList_size(DLL));
    TEST_ASSERT_FALSE(DoublyLinkedList_contains(DLL, &d2));
}

void test_DoublyLinkedList_clone_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_add_last(DLL, &d4);

    DoublyLinkedList *clone = DoublyLinkedList_clone(DLL);

    TEST_ASSERT_EQUAL(DoublyLinkedList_size(clone), DoublyLinkedList_size(DLL));
    TEST_ASSERT_EQUAL(DoublyLinkedList_sort_order(clone), DoublyLinkedList_sort_order(DLL));
    TEST_ASSERT_TRUE(DoublyLinkedList_is_equals_strict(DLL, clone));
}

void test_DoublyLinkedList_clone_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    DoublyLinkedList *clone = DoublyLinkedList_clone(DLL);

    TEST_ASSERT_NULL(clone);
}

void test_DoublyLinkedList_clone_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    DoublyLinkedList *clone = DoublyLinkedList_clone(DLL);

    TEST_ASSERT_NULL(clone);
}

void test_DoublyLinkedList_concat_1() {
    TEST_MESSAGE("Case 1 --> 2 Non NULL DoublyLinkedList:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList *DLL2 = NEW_DLL;
    DoublyLinkedList_add_last(DLL2, &d3);
    DoublyLinkedList_add_last(DLL2, &d4);
    size_t concatenated_size = DoublyLinkedList_size(DLL1) + DoublyLinkedList_size(DLL2);

    DoublyLinkedList *concatenated = DoublyLinkedList_concat(DLL1, DLL2);
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d4, DoublyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(concatenated_size, DoublyLinkedList_size(concatenated));

    DoublyLinkedList *concatenated_2 = DoublyLinkedList_concat(DLL2, DLL1);
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_first_element(concatenated_2));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_last_element(concatenated_2));
    TEST_ASSERT_EQUAL(concatenated_size, DoublyLinkedList_size(concatenated_2));
}

void test_DoublyLinkedList_concat_2() {
    TEST_MESSAGE("Case 2 --> First DoublyLinkedList = NULL:");
    DoublyLinkedList *DLL1 = NULL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList *concatenated = DoublyLinkedList_concat(DLL1, DLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_DoublyLinkedList_concat_3() {
    TEST_MESSAGE("Case 3 --> Second DoublyLinkedList = NULL:");
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NULL;

    DoublyLinkedList *concatenated = DoublyLinkedList_concat(DLL1, DLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_DoublyLinkedList_concat_4() {
    TEST_MESSAGE("Case 4 --> Both DoublyLinkedList = NULL:");
    DoublyLinkedList *DLL1 = NULL;
    DoublyLinkedList *DLL2 = NULL;

    DoublyLinkedList *concatenated = DoublyLinkedList_concat(DLL1, DLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_DoublyLinkedList_concat_5() {
    TEST_MESSAGE("Case 5 --> First DoublyLinkedList is Empty:");
    TYPE d1, d2;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;
    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);

    DoublyLinkedList *concatenated = DoublyLinkedList_concat(DLL1, DLL2);
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(DoublyLinkedList_size(DLL2), DoublyLinkedList_size(concatenated));
    TEST_ASSERT_TRUE(DoublyLinkedList_is_equals_strict(DLL2, concatenated));
}

void test_DoublyLinkedList_concat_6() {
    TEST_MESSAGE("Case 6 --> Second DoublyLinkedList is Empty:");
    TYPE d1, d2;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList *concatenated = DoublyLinkedList_concat(DLL1, DLL2);
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(DoublyLinkedList_size(DLL1), DoublyLinkedList_size(concatenated));
    TEST_ASSERT_TRUE(DoublyLinkedList_is_equals_strict(DLL1, concatenated));
}

void test_DoublyLinkedList_concat_7() {
    TEST_MESSAGE("Case 7 --> Both DoublyLinkedList are Empty:");
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList *concatenated = DoublyLinkedList_concat(DLL1, DLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_DoublyLinkedList_concat_8() {
    TEST_MESSAGE("Case 8 --> 2 Sorted DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_sort_asc(DLL1, _compare_TYPE);

    DoublyLinkedList *DLL2 = NEW_DLL;
    DoublyLinkedList_add_last(DLL2, &d3);
    DoublyLinkedList_add_last(DLL2, &d4);
    DoublyLinkedList_sort_desc(DLL2, _compare_TYPE);

    size_t concatenated_size = DoublyLinkedList_size(DLL1) + DoublyLinkedList_size(DLL2);

    DoublyLinkedList *concatenated = DoublyLinkedList_concat(DLL1, DLL2);
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(concatenated_size, DoublyLinkedList_size(concatenated));
    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(concatenated));
    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(concatenated));

    DoublyLinkedList *concatenated_2 = DoublyLinkedList_concat(DLL2, DLL1);
    TEST_ASSERT_EQUAL(&d4, DoublyLinkedList_first_element(concatenated_2));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_last_element(concatenated_2));
    TEST_ASSERT_EQUAL(concatenated_size, DoublyLinkedList_size(concatenated_2));
    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(concatenated_2));
    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(concatenated_2));

    DoublyLinkedList *concatenated_3 = DoublyLinkedList_concat(DLL1, DLL1);
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_first_element(concatenated_3));
    TEST_ASSERT_EQUAL(&d2, DoublyLinkedList_last_element(concatenated_3));
    TEST_ASSERT_EQUAL(concatenated_size, DoublyLinkedList_size(concatenated_3));
    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(concatenated_3));
    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(concatenated_3));

    DoublyLinkedList *concatenated_4 = DoublyLinkedList_concat(DLL2, DLL2);
    TEST_ASSERT_EQUAL(&d4, DoublyLinkedList_first_element(concatenated_4));
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_last_element(concatenated_4));
    TEST_ASSERT_EQUAL(concatenated_size, DoublyLinkedList_size(concatenated_4));
    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(concatenated_4));
    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(concatenated_4));
}

void test_DoublyLinkedList_reverse_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL = NEW_DLL;
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_add_last(DLL, &d4);
    size_t size = DoublyLinkedList_size(DLL);

    DoublyLinkedList *reversed = DoublyLinkedList_reverse(DLL);
    for (long i = 0, j = size - 1; i < size && j >= 0; i++, j--) {
        TEST_ASSERT_EQUAL(DoublyLinkedList_get(DLL, i), DoublyLinkedList_get(reversed, j));
    }
    TEST_ASSERT_EQUAL(DoublyLinkedList_sort_order(DLL), (-1)*DoublyLinkedList_sort_order(reversed));
}

void test_DoublyLinkedList_reverse_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    DoublyLinkedList *reversed = DoublyLinkedList_reverse(DLL);
    TEST_ASSERT_NULL(reversed);
}

void test_DoublyLinkedList_reverse_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    DoublyLinkedList *reversed = DoublyLinkedList_reverse(DLL);
    TEST_ASSERT_NULL(reversed);
}

void test_DoublyLinkedList_is_equals_strict_1() {
    TEST_MESSAGE("Case 1 --> Same Data Pointers:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);

    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);
    DoublyLinkedList_add_last(DLL2, &d3);
    DoublyLinkedList_add_last(DLL2, &d4);

    for (long i = 0; i < DoublyLinkedList_size(DLL1); i++) {
        TEST_ASSERT_EQUAL(DoublyLinkedList_get(DLL1, i), DoublyLinkedList_get(DLL2, i));
    }
    TEST_ASSERT_TRUE(DoublyLinkedList_is_equals_strict(DLL1, DLL2));
}

void test_DoublyLinkedList_is_equals_strict_2() {
    TEST_MESSAGE("Case 2 --> First DoublyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NULL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);
    DoublyLinkedList_add_last(DLL2, &d3);
    DoublyLinkedList_add_last(DLL2, &d4);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals_strict(DLL1, DLL2));
}

void test_DoublyLinkedList_is_equals_strict_3() {
    TEST_MESSAGE("Case 3 --> Second DoublyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NULL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals_strict(DLL1, DLL2));
}

void test_DoublyLinkedList_is_equals_strict_4() {
    TEST_MESSAGE("Case 4 --> First DoublyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);
    DoublyLinkedList_add_last(DLL2, &d3);
    DoublyLinkedList_add_last(DLL2, &d4);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals_strict(DLL1, DLL2));
}

void test_DoublyLinkedList_is_equals_strict_5() {
    TEST_MESSAGE("Case 5 --> Second DoublyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals_strict(DLL1, DLL2));
}

void test_DoublyLinkedList_is_equals_strict_6() {
    TEST_MESSAGE("Case 6 --> Same Data Pointers, but one of then is Sorted:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);
    DoublyLinkedList_sort_asc(DLL1, _compare_TYPE);

    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);
    DoublyLinkedList_add_last(DLL2, &d3);
    DoublyLinkedList_add_last(DLL2, &d4);

    for (long i = 0; i < DoublyLinkedList_size(DLL1); i++) {
        TEST_ASSERT_EQUAL(DoublyLinkedList_get(DLL1, i), DoublyLinkedList_get(DLL2, i));
    }
    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals_strict(DLL1, DLL2));
}

void test_DoublyLinkedList_is_equals_strict_7() {
    TEST_MESSAGE("Case 7 --> Same Data (content, not pointers):");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    TYPE d11 = 1, d22 = 2, d33 = 3, d44 = 4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);

    DoublyLinkedList_add_last(DLL2, &d11);
    DoublyLinkedList_add_last(DLL2, &d22);
    DoublyLinkedList_add_last(DLL2, &d33);
    DoublyLinkedList_add_last(DLL2, &d44);

    for (long i = 0; i < DoublyLinkedList_size(DLL1); i++) {
        TEST_ASSERT_EQUAL(_convert_to_TYPE(DoublyLinkedList_get(DLL1, i)), _convert_to_TYPE(DoublyLinkedList_get(DLL2, i)));
    }
    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals_strict(DLL1, DLL2));
}

void test_DoublyLinkedList_is_equals_strict_8() {
    TEST_MESSAGE("Case 8 --> Different sizes:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);

    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);
    DoublyLinkedList_add_last(DLL2, &d3);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals_strict(DLL1, DLL2));
}

void test_DoublyLinkedList_is_equals_1() {
    TEST_MESSAGE("Case 1 --> Same Data Pointers:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);

    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);
    DoublyLinkedList_add_last(DLL2, &d3);
    DoublyLinkedList_add_last(DLL2, &d4);

    for (long i = 0; i < DoublyLinkedList_size(DLL1); i++) {
        TEST_ASSERT_EQUAL(DoublyLinkedList_get(DLL1, i), DoublyLinkedList_get(DLL2, i));
    }
    TEST_ASSERT_TRUE(DoublyLinkedList_is_equals(DLL1, DLL2, _compare_TYPE));
}

void test_DoublyLinkedList_is_equals_2() {
    TEST_MESSAGE("Case 2 --> First DoublyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NULL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);
    DoublyLinkedList_add_last(DLL2, &d3);
    DoublyLinkedList_add_last(DLL2, &d4);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals(DLL1, DLL2, _compare_TYPE));
}

void test_DoublyLinkedList_is_equals_3() {
    TEST_MESSAGE("Case 3 --> Second DoublyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NULL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals(DLL1, DLL2, _compare_TYPE));
}

void test_DoublyLinkedList_is_equals_4() {
    TEST_MESSAGE("Case 4 --> First DoublyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);
    DoublyLinkedList_add_last(DLL2, &d3);
    DoublyLinkedList_add_last(DLL2, &d4);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals(DLL1, DLL2, _compare_TYPE));
}

void test_DoublyLinkedList_is_equals_5() {
    TEST_MESSAGE("Case 5 --> Second DoublyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals(DLL1, DLL2, _compare_TYPE));
}

void test_DoublyLinkedList_is_equals_6() {
    TEST_MESSAGE("Case 6 --> Same Data Pointers, but one of then is Sorted:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);
    DoublyLinkedList_sort_asc(DLL1, _compare_TYPE);

    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);
    DoublyLinkedList_add_last(DLL2, &d3);
    DoublyLinkedList_add_last(DLL2, &d4);

    for (long i = 0; i < DoublyLinkedList_size(DLL1); i++) {
        TEST_ASSERT_EQUAL(DoublyLinkedList_get(DLL1, i), DoublyLinkedList_get(DLL2, i));
    }
    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals(DLL1, DLL2, _compare_TYPE));
}

void test_DoublyLinkedList_is_equals_7() {
    TEST_MESSAGE("Case 7 --> Same Data (content, not pointers):");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    TYPE d11 = 1, d22 = 2, d33 = 3, d44 = 4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);

    DoublyLinkedList_add_last(DLL2, &d11);
    DoublyLinkedList_add_last(DLL2, &d22);
    DoublyLinkedList_add_last(DLL2, &d33);
    DoublyLinkedList_add_last(DLL2, &d44);

    for (long i = 0; i < DoublyLinkedList_size(DLL1); i++) {
        TEST_ASSERT_EQUAL(_convert_to_TYPE(DoublyLinkedList_get(DLL1, i)), _convert_to_TYPE(DoublyLinkedList_get(DLL2, i)));
    }
    TEST_ASSERT_TRUE(DoublyLinkedList_is_equals(DLL1, DLL2, _compare_TYPE));
}

void test_DoublyLinkedList_is_equals_8() {
    TEST_MESSAGE("Case 8 --> Different sizes:");
    TYPE d1, d2, d3, d4;
    DoublyLinkedList *DLL1 = NEW_DLL;
    DoublyLinkedList *DLL2 = NEW_DLL;

    DoublyLinkedList_add_last(DLL1, &d1);
    DoublyLinkedList_add_last(DLL1, &d2);
    DoublyLinkedList_add_last(DLL1, &d3);
    DoublyLinkedList_add_last(DLL1, &d4);

    DoublyLinkedList_add_last(DLL2, &d1);
    DoublyLinkedList_add_last(DLL2, &d2);
    DoublyLinkedList_add_last(DLL2, &d3);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_equals(DLL1, DLL2, _compare_TYPE));
}

void test_DoublyLinkedList_sort_asc_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    DoublyLinkedList *DLL = NEW_DLL;

    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_add_last(DLL, &d2);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(DLL));

    bool sorted = DoublyLinkedList_sort_asc(DLL, _compare_TYPE);
    TEST_ASSERT_TRUE(sorted);
    TEST_ASSERT_TRUE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(ASC, DoublyLinkedList_sort_order(DLL));
    for (long i = 0; i < DoublyLinkedList_size(DLL); i++) {
        TEST_ASSERT_EQUAL(i+1, _convert_to_TYPE(DoublyLinkedList_get(DLL, i)));
    }
}

void test_DoublyLinkedList_sort_asc_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    bool sorted = DoublyLinkedList_sort_asc(DLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_DoublyLinkedList_sort_asc_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    bool sorted = DoublyLinkedList_sort_asc(DLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_DoublyLinkedList_sort_desc_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    DoublyLinkedList *DLL = NEW_DLL;

    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_add_last(DLL, &d2);
    size_t  size = DoublyLinkedList_size(DLL);

    TEST_ASSERT_FALSE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(UNSORTED, DoublyLinkedList_sort_order(DLL));

    bool sorted = DoublyLinkedList_sort_desc(DLL, _compare_TYPE);
    TEST_ASSERT_TRUE(sorted);
    TEST_ASSERT_TRUE(DoublyLinkedList_is_sorted(DLL));
    TEST_ASSERT_EQUAL(DESC, DoublyLinkedList_sort_order(DLL));
    for (long i = 0, j = size; i < size && j > 0; i++, j--) {
        TEST_ASSERT_EQUAL(j, _convert_to_TYPE(DoublyLinkedList_get(DLL, i)));
    }
}

void test_DoublyLinkedList_sort_desc_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    bool sorted = DoublyLinkedList_sort_desc(DLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_DoublyLinkedList_sort_desc_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    bool sorted = DoublyLinkedList_sort_desc(DLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_DoublyLinkedList_sorted_insert_1() {
    TEST_MESSAGE("Case 1 --> Sorted DoublyLinkedList:");
    TYPE d0 = 0, d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5, d6 = 6;
    DoublyLinkedList *DLL = NEW_DLL;

    DoublyLinkedList_add_last(DLL, &d5);
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d4);

    DoublyLinkedList_sort_asc(DLL, _compare_TYPE);

    DoublyLinkedList_sorted_insert(DLL, &d0, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d0, DoublyLinkedList_get(DLL, 0));
    DoublyLinkedList_sorted_insert(DLL, &d3, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d3, DoublyLinkedList_get(DLL, 3));
    DoublyLinkedList_sorted_insert(DLL, &d6, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d6, DoublyLinkedList_get(DLL, 6));
}

void test_DoublyLinkedList_sorted_insert_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NULL;

    bool inserted = DoublyLinkedList_sorted_insert(DLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(inserted);
}

void test_DoublyLinkedList_sorted_insert_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    TYPE d1;
    DoublyLinkedList *DLL = NEW_DLL;

    bool inserted = DoublyLinkedList_sorted_insert(DLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(inserted);
}

void test_DoublyLinkedList_sorted_insert_4() {
    TEST_MESSAGE("Case 4 --> Unsorted DoublyLinkedList:");
    TYPE d0 = 0, d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    DoublyLinkedList *DLL = NEW_DLL;

    DoublyLinkedList_add_last(DLL, &d4);
    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);

    bool inserted = DoublyLinkedList_sorted_insert(DLL, &d0, _compare_TYPE);
    TEST_ASSERT_FALSE(inserted);
    TEST_ASSERT_EQUAL(&d4, DoublyLinkedList_get(DLL, 0));
}

void test_DoublyLinkedList_min_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    DoublyLinkedList *DLL = NEW_DLL;

    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_add_last(DLL, &d4);

    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_min(DLL, _compare_TYPE));

    DoublyLinkedList_sort_desc(DLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_min(DLL, _compare_TYPE));

    DoublyLinkedList_sort_asc(DLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d1, DoublyLinkedList_min(DLL, _compare_TYPE));
}

void test_DoublyLinkedList_min_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    TEST_ASSERT_NULL(DoublyLinkedList_min(DLL, _compare_TYPE));
}

void test_DoublyLinkedList_min_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    TEST_ASSERT_NULL(DoublyLinkedList_min(DLL, _compare_TYPE));
}

void test_DoublyLinkedList_max_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    DoublyLinkedList *DLL = NEW_DLL;

    DoublyLinkedList_add_last(DLL, &d1);
    DoublyLinkedList_add_last(DLL, &d2);
    DoublyLinkedList_add_last(DLL, &d3);
    DoublyLinkedList_add_last(DLL, &d4);

    TEST_ASSERT_EQUAL(&d4, DoublyLinkedList_max(DLL, _compare_TYPE));

    DoublyLinkedList_sort_desc(DLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d4, DoublyLinkedList_max(DLL, _compare_TYPE));

    DoublyLinkedList_sort_asc(DLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d4, DoublyLinkedList_max(DLL, _compare_TYPE));
}

void test_DoublyLinkedList_max_2() {
    TEST_MESSAGE("Case 2 --> NULL DoublyLinkedList:");
    DoublyLinkedList *DLL = NULL;

    TEST_ASSERT_NULL(DoublyLinkedList_max(DLL, _compare_TYPE));
}

void test_DoublyLinkedList_max_3() {
    TEST_MESSAGE("Case 3 --> Empty DoublyLinkedList:");
    DoublyLinkedList *DLL = NEW_DLL;

    TEST_ASSERT_NULL(DoublyLinkedList_max(DLL, _compare_TYPE));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_DoublyLinkedList_create_1);
    RUN_TEST(test_DoublyLinkedList_clean_1);
    RUN_TEST(test_DoublyLinkedList_clean_2);
    RUN_TEST(test_DoublyLinkedList_destroy_1);
    RUN_TEST(test_DoublyLinkedList_destroy_2);
    RUN_TEST(test_DoublyLinkedList_is_empty_1);
    RUN_TEST(test_DoublyLinkedList_is_empty_2);
    RUN_TEST(test_DoublyLinkedList_is_empty_3);
    RUN_TEST(test_DoublyLinkedList_is_sorted_1);
    RUN_TEST(test_DoublyLinkedList_is_sorted_2);
    RUN_TEST(test_DoublyLinkedList_is_sorted_3);
    RUN_TEST(test_DoublyLinkedList_is_sorted_4);
    RUN_TEST(test_DoublyLinkedList_sort_order_1);
    RUN_TEST(test_DoublyLinkedList_sort_order_2);
    RUN_TEST(test_DoublyLinkedList_sort_order_3);
    RUN_TEST(test_DoublyLinkedList_sort_order_4);
    RUN_TEST(test_DoublyLinkedList_add_first_1);
    RUN_TEST(test_DoublyLinkedList_add_first_2);
    RUN_TEST(test_DoublyLinkedList_add_first_3);
    RUN_TEST(test_DoublyLinkedList_add_first_4);
    RUN_TEST(test_DoublyLinkedList_add_first_5);
    RUN_TEST(test_DoublyLinkedList_add_last_1);
    RUN_TEST(test_DoublyLinkedList_add_last_2);
    RUN_TEST(test_DoublyLinkedList_add_last_3);
    RUN_TEST(test_DoublyLinkedList_add_last_4);
    RUN_TEST(test_DoublyLinkedList_add_last_5);
    RUN_TEST(test_DoublyLinkedList_remove_first_1);
    RUN_TEST(test_DoublyLinkedList_remove_first_2);
    RUN_TEST(test_DoublyLinkedList_remove_first_3);
    RUN_TEST(test_DoublyLinkedList_remove_last_1);
    RUN_TEST(test_DoublyLinkedList_remove_last_2);
    RUN_TEST(test_DoublyLinkedList_remove_last_3);
    RUN_TEST(test_DoublyLinkedList_remove_at_1);
    RUN_TEST(test_DoublyLinkedList_remove_at_2);
    RUN_TEST(test_DoublyLinkedList_remove_at_3);
    RUN_TEST(test_DoublyLinkedList_remove_at_4);
    RUN_TEST(test_DoublyLinkedList_remove_at_5);
    RUN_TEST(test_DoublyLinkedList_remove_1);
    RUN_TEST(test_DoublyLinkedList_remove_2);
    RUN_TEST(test_DoublyLinkedList_remove_3);
    RUN_TEST(test_DoublyLinkedList_remove_4);
    RUN_TEST(test_DoublyLinkedList_remove_5);
    RUN_TEST(test_DoublyLinkedList_remove_all_1);
    RUN_TEST(test_DoublyLinkedList_remove_all_2);
    RUN_TEST(test_DoublyLinkedList_remove_all_3);
    RUN_TEST(test_DoublyLinkedList_remove_all_4);
    RUN_TEST(test_DoublyLinkedList_remove_all_5);
    RUN_TEST(test_DoublyLinkedList_size_1);
    RUN_TEST(test_DoublyLinkedList_size_2);
    RUN_TEST(test_DoublyLinkedList_size_3);
    RUN_TEST(test_DoublyLinkedList_first_element_1);
    RUN_TEST(test_DoublyLinkedList_first_element_2);
    RUN_TEST(test_DoublyLinkedList_first_element_3);
    RUN_TEST(test_DoublyLinkedList_last_element_1);
    RUN_TEST(test_DoublyLinkedList_last_element_2);
    RUN_TEST(test_DoublyLinkedList_last_element_3);
    RUN_TEST(test_DoublyLinkedList_get_1);
    RUN_TEST(test_DoublyLinkedList_get_2);
    RUN_TEST(test_DoublyLinkedList_get_3);
    RUN_TEST(test_DoublyLinkedList_get_4);
    RUN_TEST(test_DoublyLinkedList_get_5);
    RUN_TEST(test_consistence_between_first_element_and_get_at_0);
    RUN_TEST(test_consistence_between_last_element_and_get_at_size_minus_1);
    RUN_TEST(test_DoublyLinkedList_count_1);
    RUN_TEST(test_DoublyLinkedList_count_2);
    RUN_TEST(test_DoublyLinkedList_count_3);
    RUN_TEST(test_DoublyLinkedList_count_4);
    RUN_TEST(test_DoublyLinkedList_count_5);
    RUN_TEST(test_DoublyLinkedList_contains_1);
    RUN_TEST(test_DoublyLinkedList_contains_2);
    RUN_TEST(test_DoublyLinkedList_contains_3);
    RUN_TEST(test_DoublyLinkedList_contains_4);
    RUN_TEST(test_DoublyLinkedList_contains_5);
    RUN_TEST(test_DoublyLinkedList_insert_at_1);
    RUN_TEST(test_DoublyLinkedList_insert_at_2);
    RUN_TEST(test_DoublyLinkedList_insert_at_3);
    RUN_TEST(test_DoublyLinkedList_insert_at_4);
    RUN_TEST(test_DoublyLinkedList_insert_at_5);
    RUN_TEST(test_DoublyLinkedList_insert_at_6);
    RUN_TEST(test_DoublyLinkedList_insert_at_7);
    RUN_TEST(test_DoublyLinkedList_insert_at_8);
    RUN_TEST(test_DoublyLinkedList_insert_at_9);
    RUN_TEST(test_DoublyLinkedList_insert_at_10);
    RUN_TEST(test_DoublyLinkedList_insert_at_11);
    RUN_TEST(test_DoublyLinkedList_clone_1);
    RUN_TEST(test_DoublyLinkedList_clone_2);
    RUN_TEST(test_DoublyLinkedList_clone_3);
    RUN_TEST(test_DoublyLinkedList_concat_1);
    RUN_TEST(test_DoublyLinkedList_concat_2);
    RUN_TEST(test_DoublyLinkedList_concat_3);
    RUN_TEST(test_DoublyLinkedList_concat_4);
    RUN_TEST(test_DoublyLinkedList_concat_5);
    RUN_TEST(test_DoublyLinkedList_concat_6);
    RUN_TEST(test_DoublyLinkedList_concat_7);
    RUN_TEST(test_DoublyLinkedList_concat_8);
    RUN_TEST(test_DoublyLinkedList_reverse_1);
    RUN_TEST(test_DoublyLinkedList_reverse_2);
    RUN_TEST(test_DoublyLinkedList_reverse_3);
    RUN_TEST(test_DoublyLinkedList_is_equals_strict_1);
    RUN_TEST(test_DoublyLinkedList_is_equals_strict_2);
    RUN_TEST(test_DoublyLinkedList_is_equals_strict_3);
    RUN_TEST(test_DoublyLinkedList_is_equals_strict_4);
    RUN_TEST(test_DoublyLinkedList_is_equals_strict_5);
    RUN_TEST(test_DoublyLinkedList_is_equals_strict_6);
    RUN_TEST(test_DoublyLinkedList_is_equals_strict_7);
    RUN_TEST(test_DoublyLinkedList_is_equals_strict_8);
    RUN_TEST(test_DoublyLinkedList_is_equals_1);
    RUN_TEST(test_DoublyLinkedList_is_equals_2);
    RUN_TEST(test_DoublyLinkedList_is_equals_3);
    RUN_TEST(test_DoublyLinkedList_is_equals_4);
    RUN_TEST(test_DoublyLinkedList_is_equals_5);
    RUN_TEST(test_DoublyLinkedList_is_equals_6);
    RUN_TEST(test_DoublyLinkedList_is_equals_7);
    RUN_TEST(test_DoublyLinkedList_is_equals_8);
    RUN_TEST(test_DoublyLinkedList_sort_asc_1);
    RUN_TEST(test_DoublyLinkedList_sort_asc_2);
    RUN_TEST(test_DoublyLinkedList_sort_asc_3);
    RUN_TEST(test_DoublyLinkedList_sort_desc_1);
    RUN_TEST(test_DoublyLinkedList_sort_desc_2);
    RUN_TEST(test_DoublyLinkedList_sort_desc_3);
    RUN_TEST(test_DoublyLinkedList_sorted_insert_1);
    RUN_TEST(test_DoublyLinkedList_sorted_insert_2);
    RUN_TEST(test_DoublyLinkedList_sorted_insert_3);
    RUN_TEST(test_DoublyLinkedList_sorted_insert_4);
    RUN_TEST(test_DoublyLinkedList_min_1);
    RUN_TEST(test_DoublyLinkedList_min_2);
    RUN_TEST(test_DoublyLinkedList_min_3);
    RUN_TEST(test_DoublyLinkedList_max_1);
    RUN_TEST(test_DoublyLinkedList_max_2);
    RUN_TEST(test_DoublyLinkedList_max_3);
    return UNITY_END();
}
