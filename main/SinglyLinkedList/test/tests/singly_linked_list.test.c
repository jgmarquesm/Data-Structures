#include "../../main/include/unity.h"
#include "../../main/include/singly_linked_list.h"

#define TYPE int
#define UNSORTED 0
#define ASC 1
#define DESC -1
#define NEW_SLL SinglyLinkedList_create()

void setUp(){}

void tearDown(){}

TYPE _convert_to_TYPE(void *data){
    return *((TYPE *)data);
}

int _compare_TYPE(void *data1, void *data2){
    TYPE d1 = _convert_to_TYPE(data1), d2 = _convert_to_TYPE(data2);
    return d2 - d1;
}

void test_SinglyLinkedList_create_1() {
    SinglyLinkedList *SLL = NULL;

    SLL = NEW_SLL;
    TEST_ASSERT_NOT_NULL(SLL);
    TEST_ASSERT_TRUE(SinglyLinkedList_is_empty(SLL));
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_clean_1() {
    TEST_MESSAGE("Case 1 --> Non NULL SinglyLinkedList:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_first(SLL, &d1);
    SinglyLinkedList_add_first(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    TEST_ASSERT_FALSE(SinglyLinkedList_is_empty(SLL));

    bool cleaned = SinglyLinkedList_clean(SLL);
    TEST_ASSERT_TRUE(cleaned);
    TEST_ASSERT_TRUE(SinglyLinkedList_is_empty(SLL));
}

void test_SinglyLinkedList_clean_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    bool cleaned = SinglyLinkedList_clean(SLL);
    TEST_ASSERT_FALSE(cleaned);
}

void test_SinglyLinkedList_destroy_1() {
    TEST_MESSAGE("Case 1 --> Non NULL SinglyLinkedList:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_first(SLL, &d1);
    SinglyLinkedList_add_first(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);

    bool destroyed = SinglyLinkedList_destroy(&SLL);
    TEST_ASSERT_TRUE(destroyed);
    TEST_ASSERT_NULL(SLL);
}

void test_SinglyLinkedList_destroy_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    bool destroyed = SinglyLinkedList_destroy(&SLL);
    TEST_ASSERT_FALSE(destroyed);
}

void test_SinglyLinkedList_is_empty_1() {
    TEST_MESSAGE("Case 1--> Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    TEST_ASSERT_TRUE(SinglyLinkedList_is_empty(SLL));
}

void test_SinglyLinkedList_is_empty_2() {
    TEST_MESSAGE("Case 2--> Non Empty SinglyLinkedList:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_empty(SLL));
}

void test_SinglyLinkedList_is_empty_3() {
    TEST_MESSAGE("Case 3--> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    TEST_ASSERT_TRUE(SinglyLinkedList_is_empty(SLL));
}

void test_SinglyLinkedList_is_sorted_1() {
    TEST_MESSAGE("Case 1--> Unsorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d5);
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_is_sorted_2() {
    TEST_MESSAGE("Case 2--> Ascending Sorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d5);
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_sort_asc(SLL, _compare_TYPE);

    TEST_ASSERT_TRUE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(ASC, SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_is_sorted_3() {
    TEST_MESSAGE("Case 3--> Descending Sorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d5);
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_sort_desc(SLL, _compare_TYPE);

    TEST_ASSERT_TRUE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(DESC, SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_is_sorted_4() {
    TEST_MESSAGE("Case 4--> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(SLL));
}

void test_SinglyLinkedList_sort_order_1() {
    TEST_MESSAGE("Case 1--> Unsorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d5);
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);

    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_sort_order_2() {
    TEST_MESSAGE("Case 2--> Ascending Sorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d5);
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_sort_asc(SLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(ASC, SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_sort_order_3() {
    TEST_MESSAGE("Case 3--> Descending Sorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d5);
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_sort_desc(SLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(DESC, SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_sort_order_4() {
    TEST_MESSAGE("Case 4--> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_add_first_1() {
    TEST_MESSAGE("Case 1 --> Adding on a Unsorted SinglyLinkedList:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_first(SLL, &d1);
    SinglyLinkedList_add_first(SLL, &d2);

    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_first_element(SLL));
    TEST_ASSERT_EQUAL(0,  SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_add_first_2() {
    TEST_MESSAGE("Case 2 --> Adding on a Sorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_first(SLL, &d1);
    SinglyLinkedList_add_first(SLL, &d2);
    SinglyLinkedList_sort_asc(SLL, _compare_TYPE);

    bool added = SinglyLinkedList_add_first(SLL, &d3);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_first_element(SLL));
    TEST_ASSERT_EQUAL(UNSORTED,  SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_add_first_3() {
    TEST_MESSAGE("Case 3 --> NULL SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NULL;

    bool added = SinglyLinkedList_add_first(SLL, &d1);
    TEST_ASSERT_FALSE(added);
}

void test_SinglyLinkedList_add_first_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    SinglyLinkedList *SLL = NEW_SLL;

    bool added = SinglyLinkedList_add_first(SLL, NULL);
    TEST_ASSERT_FALSE(added);
}

void test_SinglyLinkedList_add_first_5() {
    TEST_MESSAGE("Case 5 --> Adding NULL data on a Sorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_first(SLL, &d1);
    SinglyLinkedList_add_first(SLL, &d2);
    SinglyLinkedList_sort_asc(SLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));

    bool added = SinglyLinkedList_add_first(SLL, NULL);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_first_element(SLL));
    TEST_ASSERT_EQUAL(ASC,  SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_add_last_1() {
    TEST_MESSAGE("Case 1 --> Adding on a Unsorted SinglyLinkedList:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);

    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_last_element(SLL));
    TEST_ASSERT_EQUAL(0,  SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_add_last_2() {
    TEST_MESSAGE("Case 2 --> Adding on a Sorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_sort_asc(SLL, _compare_TYPE);

    bool added = SinglyLinkedList_add_last(SLL, &d3);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_last_element(SLL));
    TEST_ASSERT_EQUAL(UNSORTED,  SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_add_last_3() {
    TEST_MESSAGE("Case 3 --> NULL SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NULL;

    bool added = SinglyLinkedList_add_last(SLL, &d1);
    TEST_ASSERT_FALSE(added);
}

void test_SinglyLinkedList_add_last_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    SinglyLinkedList *SLL = NEW_SLL;

    bool added = SinglyLinkedList_add_last(SLL, NULL);
    TEST_ASSERT_FALSE(added);
}

void test_SinglyLinkedList_add_last_5() {
    TEST_MESSAGE("Case 5 --> Adding NULL data on a Sorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_sort_asc(SLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));

    bool added = SinglyLinkedList_add_last(SLL, NULL);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_last_element(SLL));
    TEST_ASSERT_EQUAL(ASC,  SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_remove_first_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList");
    TYPE d1, d2, d3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);

    TEST_ASSERT_EQUAL(3, SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_first_element(SLL));

    SinglyLinkedList_remove_first(SLL);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d1));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_first_element(SLL));
}

void test_SinglyLinkedList_remove_first_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList");
    SinglyLinkedList *SLL = NULL;

    void *removed = SinglyLinkedList_remove_first(SLL);
    TEST_ASSERT_NULL(removed);
}

void test_SinglyLinkedList_remove_first_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList");
    SinglyLinkedList *SLL = NEW_SLL;

    void *removed = SinglyLinkedList_remove_first(SLL);
    TEST_ASSERT_NULL(removed);
}

void test_SinglyLinkedList_remove_last_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList");
    TYPE d1, d2, d3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);

    TEST_ASSERT_EQUAL(3, SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_last_element(SLL));

    SinglyLinkedList_remove_last(SLL);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d3));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_last_element(SLL));
}

void test_SinglyLinkedList_remove_last_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList");
    SinglyLinkedList *SLL = NULL;

    void *removed = SinglyLinkedList_remove_last(SLL);
    TEST_ASSERT_NULL(removed);
}

void test_SinglyLinkedList_remove_last_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList");
    SinglyLinkedList *SLL = NEW_SLL;

    void *removed = SinglyLinkedList_remove_last(SLL);
    TEST_ASSERT_NULL(removed);
}

void test_SinglyLinkedList_remove_at_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList and valid index:");
    TYPE d1, d2, d3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);

    TEST_ASSERT_EQUAL(3, SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_get(SLL, 1));
    TEST_ASSERT_TRUE(SinglyLinkedList_contains(SLL, &d2));

    void *removed = SinglyLinkedList_remove_at(SLL, 1);
    TEST_ASSERT_EQUAL(&d2, removed);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d2));
}

void test_SinglyLinkedList_remove_at_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    void *removed = SinglyLinkedList_remove_at(SLL, 1);
    TEST_ASSERT_NULL(removed);
}

void test_SinglyLinkedList_remove_at_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    void *removed = SinglyLinkedList_remove_at(SLL, 1);
    TEST_ASSERT_NULL(removed);
}

void test_SinglyLinkedList_remove_at_4() {
    TEST_MESSAGE("Case 4 --> Index < 0:");
    TYPE d1, d2, d3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);

    TEST_ASSERT_EQUAL(3, SinglyLinkedList_size(SLL));

    void *removed = SinglyLinkedList_remove_at(SLL, -1);
    TEST_ASSERT_NULL(removed);
    TEST_ASSERT_EQUAL(3, SinglyLinkedList_size(SLL));
}

void test_SinglyLinkedList_remove_at_5() {
    TEST_MESSAGE("Case 5 --> size <= Index:");
    TYPE d1, d2, d3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);

    TEST_ASSERT_EQUAL(3, SinglyLinkedList_size(SLL));

    void *removed = SinglyLinkedList_remove_at(SLL, SinglyLinkedList_size(SLL));
    void *removed_2 = SinglyLinkedList_remove_at(SLL, SinglyLinkedList_size(SLL) + 1);
    TEST_ASSERT_NULL(removed);
    TEST_ASSERT_NULL(removed_2);
    TEST_ASSERT_EQUAL(3, SinglyLinkedList_size(SLL));
}

void test_SinglyLinkedList_remove_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList and Non NULL Data:");
    TYPE d1 = 1, d2 = 2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);

    TEST_ASSERT_EQUAL(6, SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_get(SLL, 0));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_get(SLL, 1));

    bool removed = SinglyLinkedList_remove(SLL, &d1, _compare_TYPE);
    TEST_ASSERT_TRUE(removed);
    TEST_ASSERT_EQUAL(5, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d1));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_get(SLL, 0));
}

void test_SinglyLinkedList_remove_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NULL;

    bool removed = SinglyLinkedList_remove(SLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
}

void test_SinglyLinkedList_remove_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;

    bool removed = SinglyLinkedList_remove(SLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
}

void test_SinglyLinkedList_remove_4() {
    TEST_MESSAGE("Case 4 --> NULL data:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));

    bool removed = SinglyLinkedList_remove(SLL, NULL, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));
}

void test_SinglyLinkedList_remove_5() {
    TEST_MESSAGE("Case 5 --> Data not in SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);

    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d3));

    bool removed = SinglyLinkedList_remove(SLL, &d3, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
}

void test_SinglyLinkedList_remove_all_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList and Non NULL Data:");
    TYPE d1 = 1, d2 = 2, d2_2 = 2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2_2);
    SinglyLinkedList_add_last(SLL, &d2_2);
    TEST_ASSERT_EQUAL(7, SinglyLinkedList_size(SLL));

    size_t removed = SinglyLinkedList_remove_all(SLL, &d2, _compare_TYPE);
    TEST_ASSERT_EQUAL(6, removed);
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d2));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d2_2));
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));
}

void test_SinglyLinkedList_remove_all_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NULL;

    size_t removed = SinglyLinkedList_remove_all(SLL, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
}

void test_SinglyLinkedList_remove_all_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;

    size_t removed = SinglyLinkedList_remove_all(SLL, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
}

void test_SinglyLinkedList_remove_all_4() {
    TEST_MESSAGE("Case 4 --> NULL data:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));

    size_t removed = SinglyLinkedList_remove_all(SLL, NULL, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));
}

void test_SinglyLinkedList_remove_all_5() {
    TEST_MESSAGE("Case 5 --> Data not in SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);

    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d3));

    size_t removed = SinglyLinkedList_remove_all(SLL, &d3, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
}

void test_SinglyLinkedList_size_1() {
    TEST_MESSAGE("Case 1 --> Non NULL SinglyLinkedList:");
    TYPE d1, d2, d3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    TEST_ASSERT_EQUAL(3, SinglyLinkedList_size(SLL));
}

void test_SinglyLinkedList_size_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_size(SLL));
}

void test_SinglyLinkedList_size_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;
    TEST_ASSERT_EQUAL(0, SinglyLinkedList_size(SLL));
}

void test_SinglyLinkedList_first_element_1() {
    TEST_MESSAGE("Case 1: Non NULL Non Empty SinglyLinkedList:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_first(SLL, &d1);
    SinglyLinkedList_add_first(SLL, &d2);

    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_first_element(SLL));
}

void test_SinglyLinkedList_first_element_2() {
    TEST_MESSAGE("Case 2: NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    TEST_ASSERT_NULL(SinglyLinkedList_first_element(SLL));
}

void test_SinglyLinkedList_first_element_3() {
    TEST_MESSAGE("Case 3: Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    TEST_ASSERT_NULL(SinglyLinkedList_first_element(SLL));
}

void test_SinglyLinkedList_last_element_1() {
    TEST_MESSAGE("Case 1: Non NULL Non Empty SinglyLinkedList:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);

    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_last_element(SLL));
}

void test_SinglyLinkedList_last_element_2() {
    TEST_MESSAGE("Case 2: NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    TEST_ASSERT_NULL(SinglyLinkedList_last_element(SLL));
}

void test_SinglyLinkedList_last_element_3() {
    TEST_MESSAGE("Case 3: Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    TEST_ASSERT_NULL(SinglyLinkedList_last_element(SLL));
}

void test_SinglyLinkedList_get_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList and valid index:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_add_last(SLL, &d4);

    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_get(SLL, 0));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_get(SLL, 1));
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_get(SLL, 2));
    TEST_ASSERT_EQUAL(&d4, SinglyLinkedList_get(SLL, 3));
}

void test_SinglyLinkedList_get_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    TEST_ASSERT_NULL(SinglyLinkedList_get(SLL, 0));
}

void test_SinglyLinkedList_get_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    TEST_ASSERT_NULL(SinglyLinkedList_get(SLL, 0));
}

void test_SinglyLinkedList_get_4() {
    TEST_MESSAGE("Case 4 --> Index < 0:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    TEST_ASSERT_NULL(SinglyLinkedList_get(SLL, -1));
}

void test_SinglyLinkedList_get_5() {
    TEST_MESSAGE("Case 5 --> size <= Index:");
    TYPE d1, d2, d3;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);

    TEST_ASSERT_NULL(SinglyLinkedList_get(SLL, SinglyLinkedList_size(SLL)));
    TEST_ASSERT_NULL(SinglyLinkedList_get(SLL, SinglyLinkedList_size(SLL) + 1));
}

void test_consistence_between_first_element_and_get_at_0() {
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_add_last(SLL, &d4);

    TEST_ASSERT_EQUAL(SinglyLinkedList_get(SLL, 0), SinglyLinkedList_first_element(SLL));
}

void test_consistence_between_last_element_and_get_at_size_minus_1() {
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_add_last(SLL, &d4);

    size_t index = SinglyLinkedList_size(SLL) - 1;
    TEST_ASSERT_EQUAL(SinglyLinkedList_get(SLL, index), SinglyLinkedList_last_element(SLL));
}

void test_SinglyLinkedList_count_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList and Non NULL Data:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d2);

    TYPE count = SinglyLinkedList_count(SLL, &d2);
    TEST_ASSERT_EQUAL(5, count);
}

void test_SinglyLinkedList_count_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NULL;

    TYPE count = SinglyLinkedList_count(SLL, &d1);
    TEST_ASSERT_EQUAL(0, count);
}

void test_SinglyLinkedList_count_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;

    TYPE count = SinglyLinkedList_count(SLL, &d1);
    TEST_ASSERT_EQUAL(0, count);
}

void test_SinglyLinkedList_count_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    TYPE count = SinglyLinkedList_count(SLL, NULL);
    TEST_ASSERT_EQUAL(0, count);
}

void test_SinglyLinkedList_count_5() {
    TEST_MESSAGE("Case 5 --> Data not in SinglyLinkedList");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    TYPE count = SinglyLinkedList_count(SLL, &d2);
    TEST_ASSERT_EQUAL(0, count);
}

void test_SinglyLinkedList_contains_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList and Non NULL Data:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);

    bool contains = SinglyLinkedList_contains(SLL, &d2);
    TEST_ASSERT_TRUE(contains);
}

void test_SinglyLinkedList_contains_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NULL;

    bool contains = SinglyLinkedList_contains(SLL, &d1);
    TEST_ASSERT_FALSE(contains);
}

void test_SinglyLinkedList_contains_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;

    bool contains = SinglyLinkedList_contains(SLL, &d1);
    TEST_ASSERT_FALSE(contains);
}

void test_SinglyLinkedList_contains_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    bool contains = SinglyLinkedList_contains(SLL, NULL);
    TEST_ASSERT_FALSE(contains);
}

void test_SinglyLinkedList_contains_5() {
    TEST_MESSAGE("Case 5 --> Data not in SinglyLinkedList");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    bool contains = SinglyLinkedList_contains(SLL, &d2);
    TEST_ASSERT_FALSE(contains);
}

void test_SinglyLinkedList_insert_at_1() {
    TEST_MESSAGE("Case 1 --> Unsorted SinglyLinkedList and valid index");
    TYPE d1, d2, d3, d4, d5;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d5);

    TEST_ASSERT_EQUAL(4, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d3));
    TEST_ASSERT_EQUAL(&d4, SinglyLinkedList_get(SLL, 2));

    bool added = SinglyLinkedList_insert_at(SLL, &d3, 2);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(5, SinglyLinkedList_size(SLL));
    TEST_ASSERT_TRUE(SinglyLinkedList_contains(SLL, &d3));
    TEST_ASSERT_NOT_EQUAL(&d4, SinglyLinkedList_get(SLL, 2));
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_get(SLL, 2));
}

void test_SinglyLinkedList_insert_at_2() {
    TEST_MESSAGE("Case 2 --> Ascending Sorted SinglyLinkedList and valid index");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d5);

    SinglyLinkedList_sort_asc(SLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(4, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d3));
    TEST_ASSERT_EQUAL(&d4, SinglyLinkedList_get(SLL, 2));
    TEST_ASSERT_TRUE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(ASC, SinglyLinkedList_sort_order(SLL));

    bool added = SinglyLinkedList_insert_at(SLL, &d3, 2);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(5, SinglyLinkedList_size(SLL));
    TEST_ASSERT_TRUE(SinglyLinkedList_contains(SLL, &d3));
    TEST_ASSERT_NOT_EQUAL(&d4, SinglyLinkedList_get(SLL, 2));
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_get(SLL, 2));
    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_insert_at_3() {
    TEST_MESSAGE("Case 2 --> Descending Sorted SinglyLinkedList and valid index");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d5);

    SinglyLinkedList_sort_desc(SLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(4, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d3));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_get(SLL, 2));
    TEST_ASSERT_TRUE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(DESC, SinglyLinkedList_sort_order(SLL));

    bool added = SinglyLinkedList_insert_at(SLL, &d3, 2);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(5, SinglyLinkedList_size(SLL));
    TEST_ASSERT_TRUE(SinglyLinkedList_contains(SLL, &d3));
    TEST_ASSERT_NOT_EQUAL(&d2, SinglyLinkedList_get(SLL, 2));
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_get(SLL, 2));
    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(SLL));
}

void test_SinglyLinkedList_insert_at_4() {
    TEST_MESSAGE("Case 4 --> Insert at 0:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d2);

    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d1));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_get(SLL, 0));

    bool added = SinglyLinkedList_insert_at(SLL, &d1, 0);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
    TEST_ASSERT_TRUE(SinglyLinkedList_contains(SLL, &d1));
    TEST_ASSERT_NOT_EQUAL(&d2, SinglyLinkedList_get(SLL, 0));
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_get(SLL, 0));
}

void test_SinglyLinkedList_insert_at_5() {
    TEST_MESSAGE("Case 5 --> Insert at index = size:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d2));
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_get(SLL, SinglyLinkedList_size(SLL) - 1));

    bool added = SinglyLinkedList_insert_at(SLL, &d2, SinglyLinkedList_size(SLL));
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(2, SinglyLinkedList_size(SLL));
    TEST_ASSERT_TRUE(SinglyLinkedList_contains(SLL, &d2));
    TEST_ASSERT_NOT_EQUAL(&d1, SinglyLinkedList_get(SLL, SinglyLinkedList_size(SLL) - 1));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_get(SLL, SinglyLinkedList_size(SLL) - 1));
}

void test_SinglyLinkedList_insert_at_6() {
    TEST_MESSAGE("Case 6 --> NULL SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NULL;

    bool added = SinglyLinkedList_insert_at(SLL, &d1, 0);
    TEST_ASSERT_FALSE(added);
}

void test_SinglyLinkedList_insert_at_7() {
    TEST_MESSAGE("Case 7 --> NULL Data:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    bool added = SinglyLinkedList_insert_at(SLL, NULL, 0);
    TEST_ASSERT_FALSE(added);
}

void test_SinglyLinkedList_insert_at_8() {
    TEST_MESSAGE("Case 8 --> Empty SinglyLinkedList and index = 0:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;

    bool added = SinglyLinkedList_insert_at(SLL, &d1, 0);
    TEST_ASSERT_TRUE(added);
}

void test_SinglyLinkedList_insert_at_9() {
    TEST_MESSAGE("Case 9 --> Empty SinglyLinkedList and index != 0:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;

    bool added = SinglyLinkedList_insert_at(SLL, &d1, 1);
    TEST_ASSERT_FALSE(added);
}

void test_SinglyLinkedList_insert_at_10() {
    TEST_MESSAGE("Case 10 --> Index < 0:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d2));

    bool added = SinglyLinkedList_insert_at(SLL, &d2, -1);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d2));
}

void test_SinglyLinkedList_insert_at_11() {
    TEST_MESSAGE("Case 11 --> size < Index:");
    TYPE d1, d2;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);

    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d2));

    bool added = SinglyLinkedList_insert_at(SLL, &d2, SinglyLinkedList_size(SLL) + 1);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(1, SinglyLinkedList_size(SLL));
    TEST_ASSERT_FALSE(SinglyLinkedList_contains(SLL, &d2));
}

void test_SinglyLinkedList_clone_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_add_last(SLL, &d4);

    SinglyLinkedList *clone = SinglyLinkedList_clone(SLL);

    TEST_ASSERT_EQUAL(SinglyLinkedList_size(clone), SinglyLinkedList_size(SLL));
    TEST_ASSERT_EQUAL(SinglyLinkedList_sort_order(clone), SinglyLinkedList_sort_order(SLL));
    TEST_ASSERT_TRUE(SinglyLinkedList_is_equals_strict(SLL, clone));
}

void test_SinglyLinkedList_clone_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    SinglyLinkedList *clone = SinglyLinkedList_clone(SLL);

    TEST_ASSERT_NULL(clone);
}

void test_SinglyLinkedList_clone_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    SinglyLinkedList *clone = SinglyLinkedList_clone(SLL);

    TEST_ASSERT_NULL(clone);
}

void test_SinglyLinkedList_concat_1() {
    TEST_MESSAGE("Case 1 --> 2 Non NULL SinglyLinkedList:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList *SLL2 = NEW_SLL;
    SinglyLinkedList_add_last(SLL2, &d3);
    SinglyLinkedList_add_last(SLL2, &d4);
    size_t concatenated_size = SinglyLinkedList_size(SLL1) + SinglyLinkedList_size(SLL2);

    SinglyLinkedList *concatenated = SinglyLinkedList_concat(SLL1, SLL2);
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d4, SinglyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(concatenated_size, SinglyLinkedList_size(concatenated));

    SinglyLinkedList *concatenated_2 = SinglyLinkedList_concat(SLL2, SLL1);
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_first_element(concatenated_2));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_last_element(concatenated_2));
    TEST_ASSERT_EQUAL(concatenated_size, SinglyLinkedList_size(concatenated_2));
}

void test_SinglyLinkedList_concat_2() {
    TEST_MESSAGE("Case 2 --> First SinglyLinkedList = NULL:");
    SinglyLinkedList *SLL1 = NULL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList *concatenated = SinglyLinkedList_concat(SLL1, SLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_SinglyLinkedList_concat_3() {
    TEST_MESSAGE("Case 3 --> Second SinglyLinkedList = NULL:");
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NULL;

    SinglyLinkedList *concatenated = SinglyLinkedList_concat(SLL1, SLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_SinglyLinkedList_concat_4() {
    TEST_MESSAGE("Case 4 --> Both SinglyLinkedList = NULL:");
    SinglyLinkedList *SLL1 = NULL;
    SinglyLinkedList *SLL2 = NULL;

    SinglyLinkedList *concatenated = SinglyLinkedList_concat(SLL1, SLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_SinglyLinkedList_concat_5() {
    TEST_MESSAGE("Case 5 --> First SinglyLinkedList is Empty:");
    TYPE d1, d2;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;
    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);

    SinglyLinkedList *concatenated = SinglyLinkedList_concat(SLL1, SLL2);
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(SinglyLinkedList_size(SLL2), SinglyLinkedList_size(concatenated));
    TEST_ASSERT_TRUE(SinglyLinkedList_is_equals_strict(SLL2, concatenated));
}

void test_SinglyLinkedList_concat_6() {
    TEST_MESSAGE("Case 6 --> Second SinglyLinkedList is Empty:");
    TYPE d1, d2;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList *concatenated = SinglyLinkedList_concat(SLL1, SLL2);
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(SinglyLinkedList_size(SLL1), SinglyLinkedList_size(concatenated));
    TEST_ASSERT_TRUE(SinglyLinkedList_is_equals_strict(SLL1, concatenated));
}

void test_SinglyLinkedList_concat_7() {
    TEST_MESSAGE("Case 7 --> Both SinglyLinkedList are Empty:");
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList *concatenated = SinglyLinkedList_concat(SLL1, SLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_SinglyLinkedList_concat_8() {
    TEST_MESSAGE("Case 8 --> 2 Sorted SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_sort_asc(SLL1, _compare_TYPE);

    SinglyLinkedList *SLL2 = NEW_SLL;
    SinglyLinkedList_add_last(SLL2, &d3);
    SinglyLinkedList_add_last(SLL2, &d4);
    SinglyLinkedList_sort_desc(SLL2, _compare_TYPE);

    size_t concatenated_size = SinglyLinkedList_size(SLL1) + SinglyLinkedList_size(SLL2);

    SinglyLinkedList *concatenated = SinglyLinkedList_concat(SLL1, SLL2);
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(concatenated_size, SinglyLinkedList_size(concatenated));
    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(concatenated));
    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(concatenated));

    SinglyLinkedList *concatenated_2 = SinglyLinkedList_concat(SLL2, SLL1);
    TEST_ASSERT_EQUAL(&d4, SinglyLinkedList_first_element(concatenated_2));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_last_element(concatenated_2));
    TEST_ASSERT_EQUAL(concatenated_size, SinglyLinkedList_size(concatenated_2));
    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(concatenated_2));
    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(concatenated_2));

    SinglyLinkedList *concatenated_3 = SinglyLinkedList_concat(SLL1, SLL1);
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_first_element(concatenated_3));
    TEST_ASSERT_EQUAL(&d2, SinglyLinkedList_last_element(concatenated_3));
    TEST_ASSERT_EQUAL(concatenated_size, SinglyLinkedList_size(concatenated_3));
    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(concatenated_3));
    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(concatenated_3));

    SinglyLinkedList *concatenated_4 = SinglyLinkedList_concat(SLL2, SLL2);
    TEST_ASSERT_EQUAL(&d4, SinglyLinkedList_first_element(concatenated_4));
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_last_element(concatenated_4));
    TEST_ASSERT_EQUAL(concatenated_size, SinglyLinkedList_size(concatenated_4));
    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(concatenated_4));
    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(concatenated_4));
}

void test_SinglyLinkedList_reverse_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL = NEW_SLL;
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_add_last(SLL, &d4);
    size_t size = SinglyLinkedList_size(SLL);

    SinglyLinkedList *reversed = SinglyLinkedList_reverse(SLL);
    for (long i = 0, j = size - 1; i < size && j >= 0; i++, j--) {
        TEST_ASSERT_EQUAL(SinglyLinkedList_get(SLL, i), SinglyLinkedList_get(reversed, j));
    }
    TEST_ASSERT_EQUAL(SinglyLinkedList_sort_order(SLL), (-1)*SinglyLinkedList_sort_order(reversed));
}

void test_SinglyLinkedList_reverse_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    SinglyLinkedList *reversed = SinglyLinkedList_reverse(SLL);
    TEST_ASSERT_NULL(reversed);
}

void test_SinglyLinkedList_reverse_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    SinglyLinkedList *reversed = SinglyLinkedList_reverse(SLL);
    TEST_ASSERT_NULL(reversed);
}

void test_SinglyLinkedList_is_equals_strict_1() {
    TEST_MESSAGE("Case 1 --> Same Data Pointers:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);

    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);
    SinglyLinkedList_add_last(SLL2, &d3);
    SinglyLinkedList_add_last(SLL2, &d4);

    for (long i = 0; i < SinglyLinkedList_size(SLL1); i++) {
        TEST_ASSERT_EQUAL(SinglyLinkedList_get(SLL1, i), SinglyLinkedList_get(SLL2, i));
    }
    TEST_ASSERT_TRUE(SinglyLinkedList_is_equals_strict(SLL1, SLL2));
}

void test_SinglyLinkedList_is_equals_strict_2() {
    TEST_MESSAGE("Case 2 --> First SinglyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NULL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);
    SinglyLinkedList_add_last(SLL2, &d3);
    SinglyLinkedList_add_last(SLL2, &d4);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals_strict(SLL1, SLL2));
}

void test_SinglyLinkedList_is_equals_strict_3() {
    TEST_MESSAGE("Case 3 --> Second SinglyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NULL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals_strict(SLL1, SLL2));
}

void test_SinglyLinkedList_is_equals_strict_4() {
    TEST_MESSAGE("Case 4 --> First SinglyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);
    SinglyLinkedList_add_last(SLL2, &d3);
    SinglyLinkedList_add_last(SLL2, &d4);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals_strict(SLL1, SLL2));
}

void test_SinglyLinkedList_is_equals_strict_5() {
    TEST_MESSAGE("Case 5 --> Second SinglyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals_strict(SLL1, SLL2));
}

void test_SinglyLinkedList_is_equals_strict_6() {
    TEST_MESSAGE("Case 6 --> Same Data Pointers, but one of then is Sorted:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);
    SinglyLinkedList_sort_asc(SLL1, _compare_TYPE);

    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);
    SinglyLinkedList_add_last(SLL2, &d3);
    SinglyLinkedList_add_last(SLL2, &d4);

    for (long i = 0; i < SinglyLinkedList_size(SLL1); i++) {
        TEST_ASSERT_EQUAL(SinglyLinkedList_get(SLL1, i), SinglyLinkedList_get(SLL2, i));
    }
    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals_strict(SLL1, SLL2));
}

void test_SinglyLinkedList_is_equals_strict_7() {
    TEST_MESSAGE("Case 7 --> Same Data (content, not pointers):");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    TYPE d11 = 1, d22 = 2, d33 = 3, d44 = 4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);

    SinglyLinkedList_add_last(SLL2, &d11);
    SinglyLinkedList_add_last(SLL2, &d22);
    SinglyLinkedList_add_last(SLL2, &d33);
    SinglyLinkedList_add_last(SLL2, &d44);

    for (long i = 0; i < SinglyLinkedList_size(SLL1); i++) {
        TEST_ASSERT_EQUAL(_convert_to_TYPE(SinglyLinkedList_get(SLL1, i)), _convert_to_TYPE(SinglyLinkedList_get(SLL2, i)));
    }
    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals_strict(SLL1, SLL2));
}

void test_SinglyLinkedList_is_equals_strict_8() {
    TEST_MESSAGE("Case 8 --> Different sizes:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);

    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);
    SinglyLinkedList_add_last(SLL2, &d3);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals_strict(SLL1, SLL2));
}

void test_SinglyLinkedList_is_equals_1() {
    TEST_MESSAGE("Case 1 --> Same Data Pointers:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);

    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);
    SinglyLinkedList_add_last(SLL2, &d3);
    SinglyLinkedList_add_last(SLL2, &d4);

    for (long i = 0; i < SinglyLinkedList_size(SLL1); i++) {
        TEST_ASSERT_EQUAL(SinglyLinkedList_get(SLL1, i), SinglyLinkedList_get(SLL2, i));
    }
    TEST_ASSERT_TRUE(SinglyLinkedList_is_equals(SLL1, SLL2, _compare_TYPE));
}

void test_SinglyLinkedList_is_equals_2() {
    TEST_MESSAGE("Case 2 --> First SinglyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NULL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);
    SinglyLinkedList_add_last(SLL2, &d3);
    SinglyLinkedList_add_last(SLL2, &d4);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals(SLL1, SLL2, _compare_TYPE));
}

void test_SinglyLinkedList_is_equals_3() {
    TEST_MESSAGE("Case 3 --> Second SinglyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NULL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals(SLL1, SLL2, _compare_TYPE));
}

void test_SinglyLinkedList_is_equals_4() {
    TEST_MESSAGE("Case 4 --> First SinglyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);
    SinglyLinkedList_add_last(SLL2, &d3);
    SinglyLinkedList_add_last(SLL2, &d4);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals(SLL1, SLL2, _compare_TYPE));
}

void test_SinglyLinkedList_is_equals_5() {
    TEST_MESSAGE("Case 5 --> Second SinglyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals(SLL1, SLL2, _compare_TYPE));
}

void test_SinglyLinkedList_is_equals_6() {
    TEST_MESSAGE("Case 6 --> Same Data Pointers, but one of then is Sorted:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);
    SinglyLinkedList_sort_asc(SLL1, _compare_TYPE);

    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);
    SinglyLinkedList_add_last(SLL2, &d3);
    SinglyLinkedList_add_last(SLL2, &d4);

    for (long i = 0; i < SinglyLinkedList_size(SLL1); i++) {
        TEST_ASSERT_EQUAL(SinglyLinkedList_get(SLL1, i), SinglyLinkedList_get(SLL2, i));
    }
    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals(SLL1, SLL2, _compare_TYPE));
}

void test_SinglyLinkedList_is_equals_7() {
    TEST_MESSAGE("Case 7 --> Same Data (content, not pointers):");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    TYPE d11 = 1, d22 = 2, d33 = 3, d44 = 4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);

    SinglyLinkedList_add_last(SLL2, &d11);
    SinglyLinkedList_add_last(SLL2, &d22);
    SinglyLinkedList_add_last(SLL2, &d33);
    SinglyLinkedList_add_last(SLL2, &d44);

    for (long i = 0; i < SinglyLinkedList_size(SLL1); i++) {
        TEST_ASSERT_EQUAL(_convert_to_TYPE(SinglyLinkedList_get(SLL1, i)), _convert_to_TYPE(SinglyLinkedList_get(SLL2, i)));
    }
    TEST_ASSERT_TRUE(SinglyLinkedList_is_equals(SLL1, SLL2, _compare_TYPE));
}

void test_SinglyLinkedList_is_equals_8() {
    TEST_MESSAGE("Case 8 --> Different sizes:");
    TYPE d1, d2, d3, d4;
    SinglyLinkedList *SLL1 = NEW_SLL;
    SinglyLinkedList *SLL2 = NEW_SLL;

    SinglyLinkedList_add_last(SLL1, &d1);
    SinglyLinkedList_add_last(SLL1, &d2);
    SinglyLinkedList_add_last(SLL1, &d3);
    SinglyLinkedList_add_last(SLL1, &d4);

    SinglyLinkedList_add_last(SLL2, &d1);
    SinglyLinkedList_add_last(SLL2, &d2);
    SinglyLinkedList_add_last(SLL2, &d3);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_equals(SLL1, SLL2, _compare_TYPE));
}

void test_SinglyLinkedList_sort_asc_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    SinglyLinkedList *SLL = NEW_SLL;

    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_add_last(SLL, &d2);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(SLL));

    bool sorted = SinglyLinkedList_sort_asc(SLL, _compare_TYPE);
    TEST_ASSERT_TRUE(sorted);
    TEST_ASSERT_TRUE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(ASC, SinglyLinkedList_sort_order(SLL));
    for (long i = 0; i < SinglyLinkedList_size(SLL); i++) {
        TEST_ASSERT_EQUAL(i+1, _convert_to_TYPE(SinglyLinkedList_get(SLL, i)));
    }
}

void test_SinglyLinkedList_sort_asc_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    bool sorted = SinglyLinkedList_sort_asc(SLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_SinglyLinkedList_sort_asc_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    bool sorted = SinglyLinkedList_sort_asc(SLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_SinglyLinkedList_sort_desc_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    SinglyLinkedList *SLL = NEW_SLL;

    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_add_last(SLL, &d2);
    size_t  size = SinglyLinkedList_size(SLL);

    TEST_ASSERT_FALSE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(UNSORTED, SinglyLinkedList_sort_order(SLL));

    bool sorted = SinglyLinkedList_sort_desc(SLL, _compare_TYPE);
    TEST_ASSERT_TRUE(sorted);
    TEST_ASSERT_TRUE(SinglyLinkedList_is_sorted(SLL));
    TEST_ASSERT_EQUAL(DESC, SinglyLinkedList_sort_order(SLL));
    for (long i = 0, j = size; i < size && j > 0; i++, j--) {
        TEST_ASSERT_EQUAL(j, _convert_to_TYPE(SinglyLinkedList_get(SLL, i)));
    }
}

void test_SinglyLinkedList_sort_desc_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    bool sorted = SinglyLinkedList_sort_desc(SLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_SinglyLinkedList_sort_desc_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    bool sorted = SinglyLinkedList_sort_desc(SLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_SinglyLinkedList_sorted_insert_1() {
    TEST_MESSAGE("Case 1 --> Sorted SinglyLinkedList:");
    TYPE d0 = 0, d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5, d6 = 6;
    SinglyLinkedList *SLL = NEW_SLL;

    SinglyLinkedList_add_last(SLL, &d5);
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d4);

    SinglyLinkedList_sort_asc(SLL, _compare_TYPE);

    SinglyLinkedList_sorted_insert(SLL, &d0, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d0, SinglyLinkedList_get(SLL, 0));
    SinglyLinkedList_sorted_insert(SLL, &d3, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d3, SinglyLinkedList_get(SLL, 3));
    SinglyLinkedList_sorted_insert(SLL, &d6, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d6, SinglyLinkedList_get(SLL, 6));
}

void test_SinglyLinkedList_sorted_insert_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NULL;

    bool inserted = SinglyLinkedList_sorted_insert(SLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(inserted);
}

void test_SinglyLinkedList_sorted_insert_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    TYPE d1;
    SinglyLinkedList *SLL = NEW_SLL;

    bool inserted = SinglyLinkedList_sorted_insert(SLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(inserted);
}

void test_SinglyLinkedList_sorted_insert_4() {
    TEST_MESSAGE("Case 4 --> Unsorted SinglyLinkedList:");
    TYPE d0 = 0, d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    SinglyLinkedList *SLL = NEW_SLL;

    SinglyLinkedList_add_last(SLL, &d4);
    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);

    bool inserted = SinglyLinkedList_sorted_insert(SLL, &d0, _compare_TYPE);
    TEST_ASSERT_FALSE(inserted);
    TEST_ASSERT_EQUAL(&d4, SinglyLinkedList_get(SLL, 0));
}

void test_SinglyLinkedList_min_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    SinglyLinkedList *SLL = NEW_SLL;

    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_add_last(SLL, &d4);

    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_min(SLL, _compare_TYPE));

    SinglyLinkedList_sort_desc(SLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_min(SLL, _compare_TYPE));

    SinglyLinkedList_sort_asc(SLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d1, SinglyLinkedList_min(SLL, _compare_TYPE));
}

void test_SinglyLinkedList_min_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    TEST_ASSERT_NULL(SinglyLinkedList_min(SLL, _compare_TYPE));
}

void test_SinglyLinkedList_min_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    TEST_ASSERT_NULL(SinglyLinkedList_min(SLL, _compare_TYPE));
}

void test_SinglyLinkedList_max_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty SinglyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    SinglyLinkedList *SLL = NEW_SLL;

    SinglyLinkedList_add_last(SLL, &d1);
    SinglyLinkedList_add_last(SLL, &d2);
    SinglyLinkedList_add_last(SLL, &d3);
    SinglyLinkedList_add_last(SLL, &d4);

    TEST_ASSERT_EQUAL(&d4, SinglyLinkedList_max(SLL, _compare_TYPE));

    SinglyLinkedList_sort_desc(SLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d4, SinglyLinkedList_max(SLL, _compare_TYPE));

    SinglyLinkedList_sort_asc(SLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d4, SinglyLinkedList_max(SLL, _compare_TYPE));
}

void test_SinglyLinkedList_max_2() {
    TEST_MESSAGE("Case 2 --> NULL SinglyLinkedList:");
    SinglyLinkedList *SLL = NULL;

    TEST_ASSERT_NULL(SinglyLinkedList_max(SLL, _compare_TYPE));
}

void test_SinglyLinkedList_max_3() {
    TEST_MESSAGE("Case 3 --> Empty SinglyLinkedList:");
    SinglyLinkedList *SLL = NEW_SLL;

    TEST_ASSERT_NULL(SinglyLinkedList_max(SLL, _compare_TYPE));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_SinglyLinkedList_create_1);
    RUN_TEST(test_SinglyLinkedList_clean_1);
    RUN_TEST(test_SinglyLinkedList_clean_2);
    RUN_TEST(test_SinglyLinkedList_destroy_1);
    RUN_TEST(test_SinglyLinkedList_destroy_2);
    RUN_TEST(test_SinglyLinkedList_is_empty_1);
    RUN_TEST(test_SinglyLinkedList_is_empty_2);
    RUN_TEST(test_SinglyLinkedList_is_empty_3);
    RUN_TEST(test_SinglyLinkedList_is_sorted_1);
    RUN_TEST(test_SinglyLinkedList_is_sorted_2);
    RUN_TEST(test_SinglyLinkedList_is_sorted_3);
    RUN_TEST(test_SinglyLinkedList_is_sorted_4);
    RUN_TEST(test_SinglyLinkedList_sort_order_1);
    RUN_TEST(test_SinglyLinkedList_sort_order_2);
    RUN_TEST(test_SinglyLinkedList_sort_order_3);
    RUN_TEST(test_SinglyLinkedList_sort_order_4);
    RUN_TEST(test_SinglyLinkedList_add_first_1);
    RUN_TEST(test_SinglyLinkedList_add_first_2);
    RUN_TEST(test_SinglyLinkedList_add_first_3);
    RUN_TEST(test_SinglyLinkedList_add_first_4);
    RUN_TEST(test_SinglyLinkedList_add_first_5);
    RUN_TEST(test_SinglyLinkedList_add_last_1);
    RUN_TEST(test_SinglyLinkedList_add_last_2);
    RUN_TEST(test_SinglyLinkedList_add_last_3);
    RUN_TEST(test_SinglyLinkedList_add_last_4);
    RUN_TEST(test_SinglyLinkedList_add_last_5);
    RUN_TEST(test_SinglyLinkedList_remove_first_1);
    RUN_TEST(test_SinglyLinkedList_remove_first_2);
    RUN_TEST(test_SinglyLinkedList_remove_first_3);
    RUN_TEST(test_SinglyLinkedList_remove_last_1);
    RUN_TEST(test_SinglyLinkedList_remove_last_2);
    RUN_TEST(test_SinglyLinkedList_remove_last_3);
    RUN_TEST(test_SinglyLinkedList_remove_at_1);
    RUN_TEST(test_SinglyLinkedList_remove_at_2);
    RUN_TEST(test_SinglyLinkedList_remove_at_3);
    RUN_TEST(test_SinglyLinkedList_remove_at_4);
    RUN_TEST(test_SinglyLinkedList_remove_at_5);
    RUN_TEST(test_SinglyLinkedList_remove_1);
    RUN_TEST(test_SinglyLinkedList_remove_2);
    RUN_TEST(test_SinglyLinkedList_remove_3);
    RUN_TEST(test_SinglyLinkedList_remove_4);
    RUN_TEST(test_SinglyLinkedList_remove_5);
    RUN_TEST(test_SinglyLinkedList_remove_all_1);
    RUN_TEST(test_SinglyLinkedList_remove_all_2);
    RUN_TEST(test_SinglyLinkedList_remove_all_3);
    RUN_TEST(test_SinglyLinkedList_remove_all_4);
    RUN_TEST(test_SinglyLinkedList_remove_all_5);
    RUN_TEST(test_SinglyLinkedList_size_1);
    RUN_TEST(test_SinglyLinkedList_size_2);
    RUN_TEST(test_SinglyLinkedList_size_3);
    RUN_TEST(test_SinglyLinkedList_first_element_1);
    RUN_TEST(test_SinglyLinkedList_first_element_2);
    RUN_TEST(test_SinglyLinkedList_first_element_3);
    RUN_TEST(test_SinglyLinkedList_last_element_1);
    RUN_TEST(test_SinglyLinkedList_last_element_2);
    RUN_TEST(test_SinglyLinkedList_last_element_3);
    RUN_TEST(test_SinglyLinkedList_get_1);
    RUN_TEST(test_SinglyLinkedList_get_2);
    RUN_TEST(test_SinglyLinkedList_get_3);
    RUN_TEST(test_SinglyLinkedList_get_4);
    RUN_TEST(test_SinglyLinkedList_get_5);
    RUN_TEST(test_consistence_between_first_element_and_get_at_0);
    RUN_TEST(test_consistence_between_last_element_and_get_at_size_minus_1);
    RUN_TEST(test_SinglyLinkedList_count_1);
    RUN_TEST(test_SinglyLinkedList_count_2);
    RUN_TEST(test_SinglyLinkedList_count_3);
    RUN_TEST(test_SinglyLinkedList_count_4);
    RUN_TEST(test_SinglyLinkedList_count_5);
    RUN_TEST(test_SinglyLinkedList_contains_1);
    RUN_TEST(test_SinglyLinkedList_contains_2);
    RUN_TEST(test_SinglyLinkedList_contains_3);
    RUN_TEST(test_SinglyLinkedList_contains_4);
    RUN_TEST(test_SinglyLinkedList_contains_5);
    RUN_TEST(test_SinglyLinkedList_insert_at_1);
    RUN_TEST(test_SinglyLinkedList_insert_at_2);
    RUN_TEST(test_SinglyLinkedList_insert_at_3);
    RUN_TEST(test_SinglyLinkedList_insert_at_4);
    RUN_TEST(test_SinglyLinkedList_insert_at_5);
    RUN_TEST(test_SinglyLinkedList_insert_at_6);
    RUN_TEST(test_SinglyLinkedList_insert_at_7);
    RUN_TEST(test_SinglyLinkedList_insert_at_8);
    RUN_TEST(test_SinglyLinkedList_insert_at_9);
    RUN_TEST(test_SinglyLinkedList_insert_at_10);
    RUN_TEST(test_SinglyLinkedList_insert_at_11);
    RUN_TEST(test_SinglyLinkedList_clone_1);
    RUN_TEST(test_SinglyLinkedList_clone_2);
    RUN_TEST(test_SinglyLinkedList_clone_3);
    RUN_TEST(test_SinglyLinkedList_concat_1);
    RUN_TEST(test_SinglyLinkedList_concat_2);
    RUN_TEST(test_SinglyLinkedList_concat_3);
    RUN_TEST(test_SinglyLinkedList_concat_4);
    RUN_TEST(test_SinglyLinkedList_concat_5);
    RUN_TEST(test_SinglyLinkedList_concat_6);
    RUN_TEST(test_SinglyLinkedList_concat_7);
    RUN_TEST(test_SinglyLinkedList_concat_8);
    RUN_TEST(test_SinglyLinkedList_reverse_1);
    RUN_TEST(test_SinglyLinkedList_reverse_2);
    RUN_TEST(test_SinglyLinkedList_reverse_3);
    RUN_TEST(test_SinglyLinkedList_is_equals_strict_1);
    RUN_TEST(test_SinglyLinkedList_is_equals_strict_2);
    RUN_TEST(test_SinglyLinkedList_is_equals_strict_3);
    RUN_TEST(test_SinglyLinkedList_is_equals_strict_4);
    RUN_TEST(test_SinglyLinkedList_is_equals_strict_5);
    RUN_TEST(test_SinglyLinkedList_is_equals_strict_6);
    RUN_TEST(test_SinglyLinkedList_is_equals_strict_7);
    RUN_TEST(test_SinglyLinkedList_is_equals_strict_8);
    RUN_TEST(test_SinglyLinkedList_is_equals_1);
    RUN_TEST(test_SinglyLinkedList_is_equals_2);
    RUN_TEST(test_SinglyLinkedList_is_equals_3);
    RUN_TEST(test_SinglyLinkedList_is_equals_4);
    RUN_TEST(test_SinglyLinkedList_is_equals_5);
    RUN_TEST(test_SinglyLinkedList_is_equals_6);
    RUN_TEST(test_SinglyLinkedList_is_equals_7);
    RUN_TEST(test_SinglyLinkedList_is_equals_8);
    RUN_TEST(test_SinglyLinkedList_sort_asc_1);
    RUN_TEST(test_SinglyLinkedList_sort_asc_2);
    RUN_TEST(test_SinglyLinkedList_sort_asc_3);
    RUN_TEST(test_SinglyLinkedList_sort_desc_1);
    RUN_TEST(test_SinglyLinkedList_sort_desc_2);
    RUN_TEST(test_SinglyLinkedList_sort_desc_3);
    RUN_TEST(test_SinglyLinkedList_sorted_insert_1);
    RUN_TEST(test_SinglyLinkedList_sorted_insert_2);
    RUN_TEST(test_SinglyLinkedList_sorted_insert_3);
    RUN_TEST(test_SinglyLinkedList_sorted_insert_4);
    RUN_TEST(test_SinglyLinkedList_min_1);
    RUN_TEST(test_SinglyLinkedList_min_2);
    RUN_TEST(test_SinglyLinkedList_min_3);
    RUN_TEST(test_SinglyLinkedList_max_1);
    RUN_TEST(test_SinglyLinkedList_max_2);
    RUN_TEST(test_SinglyLinkedList_max_3);
    return UNITY_END();
}
