#include "../../main/include/unity.h"
#include "../../main/include/circular_doubly_linked_list.h"

#define TYPE int
#define NEW_CDLL CircularDoublyLinkedList_create()
#define EMPTY_SIZE 0

void setUp(){}

void tearDown(){}

TYPE _convert_to_TYPE(void *data){
    return *((TYPE *)data);
}

int _compare_TYPE(void *data1, void *data2){
    TYPE d1 = _convert_to_TYPE(data1), d2 = _convert_to_TYPE(data2);
    return d2 - d1;
}

void test_CircularDoublyLinkedList_create_1() {
    CircularDoublyLinkedList *CDLL = NULL;

    CDLL = NEW_CDLL;
    TEST_ASSERT_NOT_NULL(CDLL);
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_empty(CDLL));
    TEST_ASSERT_EQUAL(EMPTY_SIZE, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_clean_1() {
    TEST_MESSAGE("Case 1 --> Non NULL CircularDoublyLinkedList:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_first(CDLL, &d1);
    CircularDoublyLinkedList_add_first(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_empty(CDLL));

    bool cleaned = CircularDoublyLinkedList_clean(CDLL);
    TEST_ASSERT_TRUE(cleaned);
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_empty(CDLL));
}

void test_CircularDoublyLinkedList_clean_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    bool cleaned = CircularDoublyLinkedList_clean(CDLL);
    TEST_ASSERT_FALSE(cleaned);
}

void test_CircularDoublyLinkedList_destroy_1() {
    TEST_MESSAGE("Case 1 --> Non NULL CircularDoublyLinkedList:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_first(CDLL, &d1);
    CircularDoublyLinkedList_add_first(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    bool destroyed = CircularDoublyLinkedList_destroy(&CDLL);
    TEST_ASSERT_TRUE(destroyed);
    TEST_ASSERT_NULL(CDLL);
}

void test_CircularDoublyLinkedList_destroy_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    bool destroyed = CircularDoublyLinkedList_destroy(&CDLL);
    TEST_ASSERT_FALSE(destroyed);
}

void test_CircularDoublyLinkedList_is_empty_1() {
    TEST_MESSAGE("Case 1--> Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_empty(CDLL));
}

void test_CircularDoublyLinkedList_is_empty_2() {
    TEST_MESSAGE("Case 2--> Non Empty CircularDoublyLinkedList:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_empty(CDLL));
}

void test_CircularDoublyLinkedList_is_empty_3() {
    TEST_MESSAGE("Case 3--> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_empty(CDLL));
}

void test_CircularDoublyLinkedList_is_sorted_1() {
    TEST_MESSAGE("Case 1--> Unsorted CircularDoublyLinkedList:");
    TYPE d1, d2, d3, d4, d5;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d5);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_is_sorted_2() {
    TEST_MESSAGE("Case 2--> Ascending Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d5);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);

    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__ASC__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_is_sorted_3() {
    TEST_MESSAGE("Case 3--> Descending Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d5);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_sort_desc(&CDLL, _compare_TYPE);

    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__DESC__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_is_sorted_4() {
    TEST_MESSAGE("Case 4--> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(CDLL));
}

void test_CircularDoublyLinkedList_sort_order_1() {
    TEST_MESSAGE("Case 1--> Unsorted CircularDoublyLinkedList:");
    TYPE d1, d2, d3, d4, d5;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d5);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);

    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_sort_order_2() {
    TEST_MESSAGE("Case 2--> Ascending Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d5);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(__ASC__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_sort_order_3() {
    TEST_MESSAGE("Case 3--> Descending Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d5);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_sort_desc(&CDLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(__DESC__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_sort_order_4() {
    TEST_MESSAGE("Case 4--> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_add_first_1() {
    TEST_MESSAGE("Case 1 --> Adding on a Unsorted CircularDoublyLinkedList:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_first(CDLL, &d1);
    CircularDoublyLinkedList_add_first(CDLL, &d2);

    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_first_element(CDLL));
    TEST_ASSERT_EQUAL(__UNSORTED__,  CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_add_first_2() {
    TEST_MESSAGE("Case 2 --> Adding on a Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_first(CDLL, &d1);
    CircularDoublyLinkedList_add_first(CDLL, &d2);
    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);

    bool added = CircularDoublyLinkedList_add_first(CDLL, &d3);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_first_element(CDLL));
    TEST_ASSERT_EQUAL(__UNSORTED__,  CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_add_first_3() {
    TEST_MESSAGE("Case 3 --> NULL CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NULL;

    bool added = CircularDoublyLinkedList_add_first(CDLL, &d1);
    TEST_ASSERT_FALSE(added);
}

void test_CircularDoublyLinkedList_add_first_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    bool added = CircularDoublyLinkedList_add_first(CDLL, NULL);
    TEST_ASSERT_FALSE(added);
}

void test_CircularDoublyLinkedList_add_first_5() {
    TEST_MESSAGE("Case 5 --> Adding NULL data on a Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_first(CDLL, &d1);
    CircularDoublyLinkedList_add_first(CDLL, &d2);
    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));

    bool added = CircularDoublyLinkedList_add_first(CDLL, NULL);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_first_element(CDLL));
    TEST_ASSERT_EQUAL(__ASC__,  CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_add_last_1() {
    TEST_MESSAGE("Case 1 --> Adding on a Unsorted CircularDoublyLinkedList:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_last_element(CDLL));
    TEST_ASSERT_EQUAL(__UNSORTED__,  CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_add_last_2() {
    TEST_MESSAGE("Case 2 --> Adding on a Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);

    bool added = CircularDoublyLinkedList_add_last(CDLL, &d3);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_last_element(CDLL));
    TEST_ASSERT_EQUAL(__UNSORTED__,  CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_add_last_3() {
    TEST_MESSAGE("Case 3 --> NULL CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NULL;

    bool added = CircularDoublyLinkedList_add_last(CDLL, &d1);
    TEST_ASSERT_FALSE(added);
}

void test_CircularDoublyLinkedList_add_last_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    bool added = CircularDoublyLinkedList_add_last(CDLL, NULL);
    TEST_ASSERT_FALSE(added);
}

void test_CircularDoublyLinkedList_add_last_5() {
    TEST_MESSAGE("Case 5 --> Adding NULL data on a Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));

    bool added = CircularDoublyLinkedList_add_last(CDLL, NULL);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_last_element(CDLL));
    TEST_ASSERT_EQUAL(__ASC__,  CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_remove_first_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList");
    TYPE d1, d2, d3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);

    TEST_ASSERT_EQUAL(3, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_first_element(CDLL));

    CircularDoublyLinkedList_remove_first(CDLL);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d1));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_first_element(CDLL));
}

void test_CircularDoublyLinkedList_remove_first_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList");
    CircularDoublyLinkedList *CDLL = NULL;

    void *removed = CircularDoublyLinkedList_remove_first(CDLL);
    TEST_ASSERT_NULL(removed);
}

void test_CircularDoublyLinkedList_remove_first_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    void *removed = CircularDoublyLinkedList_remove_first(CDLL);
    TEST_ASSERT_NULL(removed);
}

void test_CircularDoublyLinkedList_remove_last_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList");
    TYPE d1, d2, d3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);

    TEST_ASSERT_EQUAL(3, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_last_element(CDLL));

    CircularDoublyLinkedList_remove_last(CDLL);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d3));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_last_element(CDLL));
}

void test_CircularDoublyLinkedList_remove_last_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList");
    CircularDoublyLinkedList *CDLL = NULL;

    void *removed = CircularDoublyLinkedList_remove_last(CDLL);
    TEST_ASSERT_NULL(removed);
}

void test_CircularDoublyLinkedList_remove_last_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    void *removed = CircularDoublyLinkedList_remove_last(CDLL);
    TEST_ASSERT_NULL(removed);
}

void test_CircularDoublyLinkedList_remove_at_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList and valid index:");
    TYPE d1, d2, d3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);

    TEST_ASSERT_EQUAL(3, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_get(CDLL, 1));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_contains(CDLL, &d2));

    void *removed = CircularDoublyLinkedList_remove_at(CDLL, 1);
    TEST_ASSERT_EQUAL(&d2, removed);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d2));
}

void test_CircularDoublyLinkedList_remove_at_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    void *removed = CircularDoublyLinkedList_remove_at(CDLL, 1);
    TEST_ASSERT_NULL(removed);
}

void test_CircularDoublyLinkedList_remove_at_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    void *removed = CircularDoublyLinkedList_remove_at(CDLL, 1);
    TEST_ASSERT_NULL(removed);
}

void test_CircularDoublyLinkedList_remove_at_4() {
    TEST_MESSAGE("Case 4 --> Index < 0:");
    TYPE d1, d2, d3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);

    TEST_ASSERT_EQUAL(3, CircularDoublyLinkedList_size(CDLL));

    void *removed = CircularDoublyLinkedList_remove_at(CDLL, -1);
    TEST_ASSERT_NULL(removed);
    TEST_ASSERT_EQUAL(3, CircularDoublyLinkedList_size(CDLL));
}

void test_CircularDoublyLinkedList_remove_at_5() {
    TEST_MESSAGE("Case 5 --> size <= Index:");
    TYPE d1, d2, d3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);

    TEST_ASSERT_EQUAL(3, CircularDoublyLinkedList_size(CDLL));

    void *removed = CircularDoublyLinkedList_remove_at(CDLL, CircularDoublyLinkedList_size(CDLL));
    void *removed_2 = CircularDoublyLinkedList_remove_at(CDLL, CircularDoublyLinkedList_size(CDLL) + 1);
    TEST_ASSERT_NULL(removed);
    TEST_ASSERT_NULL(removed_2);
    TEST_ASSERT_EQUAL(3, CircularDoublyLinkedList_size(CDLL));
}

void test_CircularDoublyLinkedList_remove_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList and Non NULL Data:");
    TYPE d1 = 1, d2 = 2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    TEST_ASSERT_EQUAL(6, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_get(CDLL, 0));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_get(CDLL, 1));

    bool removed = CircularDoublyLinkedList_remove(CDLL, &d1, _compare_TYPE);
    TEST_ASSERT_TRUE(removed);
    TEST_ASSERT_EQUAL(5, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d1));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_get(CDLL, 0));
}

void test_CircularDoublyLinkedList_remove_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NULL;

    bool removed = CircularDoublyLinkedList_remove(CDLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
}

void test_CircularDoublyLinkedList_remove_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    bool removed = CircularDoublyLinkedList_remove(CDLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
}

void test_CircularDoublyLinkedList_remove_4() {
    TEST_MESSAGE("Case 4 --> NULL data:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));

    bool removed = CircularDoublyLinkedList_remove(CDLL, NULL, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));
}

void test_CircularDoublyLinkedList_remove_5() {
    TEST_MESSAGE("Case 5 --> Data not in CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d3));

    bool removed = CircularDoublyLinkedList_remove(CDLL, &d3, _compare_TYPE);
    TEST_ASSERT_FALSE(removed);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
}

void test_CircularDoublyLinkedList_remove_all_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList and Non NULL Data:");
    TYPE d1 = 1, d2 = 2, d2_2 = 2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2_2);
    CircularDoublyLinkedList_add_last(CDLL, &d2_2);
    TEST_ASSERT_EQUAL(7, CircularDoublyLinkedList_size(CDLL));

    size_t removed = CircularDoublyLinkedList_remove_all(CDLL, &d2, _compare_TYPE);
    TEST_ASSERT_EQUAL(6, removed);
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d2));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d2_2));
    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));
}

void test_CircularDoublyLinkedList_remove_all_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NULL;

    size_t removed = CircularDoublyLinkedList_remove_all(CDLL, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
}

void test_CircularDoublyLinkedList_remove_all_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    size_t removed = CircularDoublyLinkedList_remove_all(CDLL, &d1, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
}

void test_CircularDoublyLinkedList_remove_all_4() {
    TEST_MESSAGE("Case 4 --> NULL data:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));

    size_t removed = CircularDoublyLinkedList_remove_all(CDLL, NULL, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));
}

void test_CircularDoublyLinkedList_remove_all_5() {
    TEST_MESSAGE("Case 5 --> Data not in CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d3));

    size_t removed = CircularDoublyLinkedList_remove_all(CDLL, &d3, _compare_TYPE);
    TEST_ASSERT_EQUAL(0, removed);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
}

void test_CircularDoublyLinkedList_size_1() {
    TEST_MESSAGE("Case 1 --> Non NULL CircularDoublyLinkedList:");
    TYPE d1, d2, d3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    TEST_ASSERT_EQUAL(3, CircularDoublyLinkedList_size(CDLL));
}

void test_CircularDoublyLinkedList_size_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;
    TEST_ASSERT_EQUAL(EMPTY_SIZE, CircularDoublyLinkedList_size(CDLL));
}

void test_CircularDoublyLinkedList_size_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    TEST_ASSERT_EQUAL(EMPTY_SIZE, CircularDoublyLinkedList_size(CDLL));
}

void test_CircularDoublyLinkedList_first_element_1() {
    TEST_MESSAGE("Case 1: Non NULL Non Empty CircularDoublyLinkedList:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_first(CDLL, &d1);
    CircularDoublyLinkedList_add_first(CDLL, &d2);

    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_first_element(CDLL));
}

void test_CircularDoublyLinkedList_first_element_2() {
    TEST_MESSAGE("Case 2: NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    TEST_ASSERT_NULL(CircularDoublyLinkedList_first_element(CDLL));
}

void test_CircularDoublyLinkedList_first_element_3() {
    TEST_MESSAGE("Case 3: Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    TEST_ASSERT_NULL(CircularDoublyLinkedList_first_element(CDLL));
}

void test_CircularDoublyLinkedList_last_element_1() {
    TEST_MESSAGE("Case 1: Non NULL Non Empty CircularDoublyLinkedList:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_last_element(CDLL));
}

void test_CircularDoublyLinkedList_last_element_2() {
    TEST_MESSAGE("Case 2: NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    TEST_ASSERT_NULL(CircularDoublyLinkedList_last_element(CDLL));
}

void test_CircularDoublyLinkedList_last_element_3() {
    TEST_MESSAGE("Case 3: Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    TEST_ASSERT_NULL(CircularDoublyLinkedList_last_element(CDLL));
}

void test_CircularDoublyLinkedList_get_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList and valid index:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d4);

    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_get(CDLL, 0));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_get(CDLL, 1));
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_get(CDLL, 2));
    TEST_ASSERT_EQUAL(&d4, CircularDoublyLinkedList_get(CDLL, 3));
}

void test_CircularDoublyLinkedList_get_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    TEST_ASSERT_NULL(CircularDoublyLinkedList_get(CDLL, 0));
}

void test_CircularDoublyLinkedList_get_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    TEST_ASSERT_NULL(CircularDoublyLinkedList_get(CDLL, 0));
}

void test_CircularDoublyLinkedList_get_4() {
    TEST_MESSAGE("Case 4 --> Index < 0:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    TEST_ASSERT_NULL(CircularDoublyLinkedList_get(CDLL, -1));
}

void test_CircularDoublyLinkedList_get_5() {
    TEST_MESSAGE("Case 5 --> size <= Index:");
    TYPE d1, d2, d3;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);

    TEST_ASSERT_NULL(CircularDoublyLinkedList_get(CDLL, CircularDoublyLinkedList_size(CDLL)));
    TEST_ASSERT_NULL(CircularDoublyLinkedList_get(CDLL, CircularDoublyLinkedList_size(CDLL) + 1));
}

void test_consistence_between_first_element_and_get_at_0() {
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d4);

    TEST_ASSERT_EQUAL(CircularDoublyLinkedList_get(CDLL, 0), CircularDoublyLinkedList_first_element(CDLL));
}

void test_consistence_between_last_element_and_get_at_size_minus_1() {
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d4);

    size_t index = CircularDoublyLinkedList_size(CDLL) - 1;
    TEST_ASSERT_EQUAL(CircularDoublyLinkedList_get(CDLL, index), CircularDoublyLinkedList_last_element(CDLL));
}

void test_CircularDoublyLinkedList_count_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList and Non NULL Data:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    TYPE count = CircularDoublyLinkedList_count(CDLL, &d2);
    TEST_ASSERT_EQUAL(5, count);
}

void test_CircularDoublyLinkedList_count_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NULL;

    size_t count = CircularDoublyLinkedList_count(CDLL, &d1);
    TEST_ASSERT_EQUAL(0, count);
}

void test_CircularDoublyLinkedList_count_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    size_t count = CircularDoublyLinkedList_count(CDLL, &d1);
    TEST_ASSERT_EQUAL(0, count);
}

void test_CircularDoublyLinkedList_count_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    size_t count = CircularDoublyLinkedList_count(CDLL, NULL);
    TEST_ASSERT_EQUAL(0, count);
}

void test_CircularDoublyLinkedList_count_5() {
    TEST_MESSAGE("Case 5 --> Data not in CircularDoublyLinkedList");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    size_t count = CircularDoublyLinkedList_count(CDLL, &d2);
    TEST_ASSERT_EQUAL(0, count);
}

void test_CircularDoublyLinkedList_contains_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList and Non NULL Data:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    bool contains = CircularDoublyLinkedList_contains(CDLL, &d2);
    TEST_ASSERT_TRUE(contains);
}

void test_CircularDoublyLinkedList_contains_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NULL;

    bool contains = CircularDoublyLinkedList_contains(CDLL, &d1);
    TEST_ASSERT_FALSE(contains);
}

void test_CircularDoublyLinkedList_contains_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    bool contains = CircularDoublyLinkedList_contains(CDLL, &d1);
    TEST_ASSERT_FALSE(contains);
}

void test_CircularDoublyLinkedList_contains_4() {
    TEST_MESSAGE("Case 4 --> NULL Data:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    bool contains = CircularDoublyLinkedList_contains(CDLL, NULL);
    TEST_ASSERT_FALSE(contains);
}

void test_CircularDoublyLinkedList_contains_5() {
    TEST_MESSAGE("Case 5 --> Data not in CircularDoublyLinkedList");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    bool contains = CircularDoublyLinkedList_contains(CDLL, &d2);
    TEST_ASSERT_FALSE(contains);
}

void test_CircularDoublyLinkedList_insert_at_1() {
    TEST_MESSAGE("Case 1 --> Unsorted CircularDoublyLinkedList and valid index");
    TYPE d1, d2, d3, d4, d5;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d5);

    TEST_ASSERT_EQUAL(4, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d3));
    TEST_ASSERT_EQUAL(&d4, CircularDoublyLinkedList_get(CDLL, 2));

    bool added = CircularDoublyLinkedList_insert_at(CDLL, &d3, 2);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(5, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_contains(CDLL, &d3));
    TEST_ASSERT_NOT_EQUAL(&d4, CircularDoublyLinkedList_get(CDLL, 2));
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_get(CDLL, 2));
}

void test_CircularDoublyLinkedList_insert_at_2() {
    TEST_MESSAGE("Case 2 --> Ascending Sorted CircularDoublyLinkedList and valid index");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d5);

    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(4, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d3));
    TEST_ASSERT_EQUAL(&d4, CircularDoublyLinkedList_get(CDLL, 2));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__ASC__, CircularDoublyLinkedList_sort_order(CDLL));

    bool added = CircularDoublyLinkedList_insert_at(CDLL, &d3, 2);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(5, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_contains(CDLL, &d3));
    TEST_ASSERT_NOT_EQUAL(&d4, CircularDoublyLinkedList_get(CDLL, 2));
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_get(CDLL, 2));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_insert_at_3() {
    TEST_MESSAGE("Case 2 --> Descending Sorted CircularDoublyLinkedList and valid index");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d5);

    CircularDoublyLinkedList_sort_desc(&CDLL, _compare_TYPE);

    TEST_ASSERT_EQUAL(4, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d3));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_get(CDLL, 2));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__DESC__, CircularDoublyLinkedList_sort_order(CDLL));

    bool added = CircularDoublyLinkedList_insert_at(CDLL, &d3, 2);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(5, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_contains(CDLL, &d3));
    TEST_ASSERT_NOT_EQUAL(&d2, CircularDoublyLinkedList_get(CDLL, 2));
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_get(CDLL, 2));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_insert_at_4() {
    TEST_MESSAGE("Case 4 --> Insert at 0:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d1));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_get(CDLL, 0));

    bool added = CircularDoublyLinkedList_insert_at(CDLL, &d1, 0);
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_contains(CDLL, &d1));
    TEST_ASSERT_NOT_EQUAL(&d2, CircularDoublyLinkedList_get(CDLL, 0));
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_get(CDLL, 0));
}

void test_CircularDoublyLinkedList_insert_at_5() {
    TEST_MESSAGE("Case 5 --> Insert at index = size:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d2));
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_get(CDLL, CircularDoublyLinkedList_size(CDLL) - 1));

    bool added = CircularDoublyLinkedList_insert_at(CDLL, &d2, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_TRUE(added);
    TEST_ASSERT_EQUAL(2, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_contains(CDLL, &d2));
    TEST_ASSERT_NOT_EQUAL(&d1, CircularDoublyLinkedList_get(CDLL, CircularDoublyLinkedList_size(CDLL) - 1));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_get(CDLL, CircularDoublyLinkedList_size(CDLL) - 1));
}

void test_CircularDoublyLinkedList_insert_at_6() {
    TEST_MESSAGE("Case 6 --> NULL CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NULL;

    bool added = CircularDoublyLinkedList_insert_at(CDLL, &d1, 0);
    TEST_ASSERT_FALSE(added);
}

void test_CircularDoublyLinkedList_insert_at_7() {
    TEST_MESSAGE("Case 7 --> NULL Data:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    bool added = CircularDoublyLinkedList_insert_at(CDLL, NULL, 0);
    TEST_ASSERT_FALSE(added);
}

void test_CircularDoublyLinkedList_insert_at_8() {
    TEST_MESSAGE("Case 8 --> Empty CircularDoublyLinkedList and index = 0:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    bool added = CircularDoublyLinkedList_insert_at(CDLL, &d1, 0);
    TEST_ASSERT_TRUE(added);
}

void test_CircularDoublyLinkedList_insert_at_9() {
    TEST_MESSAGE("Case 9 --> Empty CircularDoublyLinkedList and index != 0:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    bool added = CircularDoublyLinkedList_insert_at(CDLL, &d1, 1);
    TEST_ASSERT_FALSE(added);
}

void test_CircularDoublyLinkedList_insert_at_10() {
    TEST_MESSAGE("Case 10 --> Index < 0:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d2));

    bool added = CircularDoublyLinkedList_insert_at(CDLL, &d2, -1);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d2));
}

void test_CircularDoublyLinkedList_insert_at_11() {
    TEST_MESSAGE("Case 11 --> size < Index:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);

    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d2));

    bool added = CircularDoublyLinkedList_insert_at(CDLL, &d2, CircularDoublyLinkedList_size(CDLL) + 1);
    TEST_ASSERT_FALSE(added);
    TEST_ASSERT_EQUAL(1, CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_contains(CDLL, &d2));
}

void test_CircularDoublyLinkedList_clone_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d4);

    CircularDoublyLinkedList *clone = CircularDoublyLinkedList_clone(CDLL);

    TEST_ASSERT_EQUAL(CircularDoublyLinkedList_size(clone), CircularDoublyLinkedList_size(CDLL));
    TEST_ASSERT_EQUAL(CircularDoublyLinkedList_sort_order(clone), CircularDoublyLinkedList_sort_order(CDLL));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_equals_strict(CDLL, clone));
}

void test_CircularDoublyLinkedList_clone_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    CircularDoublyLinkedList *clone = CircularDoublyLinkedList_clone(CDLL);

    TEST_ASSERT_NULL(clone);
}

void test_CircularDoublyLinkedList_clone_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    CircularDoublyLinkedList *clone = CircularDoublyLinkedList_clone(CDLL);

    TEST_ASSERT_NULL(clone);
}

void test_CircularDoublyLinkedList_concat_1() {
    TEST_MESSAGE("Case 1 --> 2 Non NULL CircularDoublyLinkedList:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL2, &d3);
    CircularDoublyLinkedList_add_last(CDLL2, &d4);
    size_t concatenated_size = CircularDoublyLinkedList_size(CDLL1) + CircularDoublyLinkedList_size(CDLL2);

    CircularDoublyLinkedList *concatenated = CircularDoublyLinkedList_concat(CDLL1, CDLL2);
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d4, CircularDoublyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(concatenated_size, CircularDoublyLinkedList_size(concatenated));

    CircularDoublyLinkedList *concatenated_2 = CircularDoublyLinkedList_concat(CDLL2, CDLL1);
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_first_element(concatenated_2));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_last_element(concatenated_2));
    TEST_ASSERT_EQUAL(concatenated_size, CircularDoublyLinkedList_size(concatenated_2));
}

void test_CircularDoublyLinkedList_concat_2() {
    TEST_MESSAGE("Case 2 --> First CircularDoublyLinkedList = NULL:");
    CircularDoublyLinkedList *CDLL1 = NULL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList *concatenated = CircularDoublyLinkedList_concat(CDLL1, CDLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_CircularDoublyLinkedList_concat_3() {
    TEST_MESSAGE("Case 3 --> Second CircularDoublyLinkedList = NULL:");
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NULL;

    CircularDoublyLinkedList *concatenated = CircularDoublyLinkedList_concat(CDLL1, CDLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_CircularDoublyLinkedList_concat_4() {
    TEST_MESSAGE("Case 4 --> Both CircularDoublyLinkedList = NULL:");
    CircularDoublyLinkedList *CDLL1 = NULL;
    CircularDoublyLinkedList *CDLL2 = NULL;

    CircularDoublyLinkedList *concatenated = CircularDoublyLinkedList_concat(CDLL1, CDLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_CircularDoublyLinkedList_concat_5() {
    TEST_MESSAGE("Case 5 --> First CircularDoublyLinkedList is Empty:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);

    CircularDoublyLinkedList *concatenated = CircularDoublyLinkedList_concat(CDLL1, CDLL2);
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(CircularDoublyLinkedList_size(CDLL2), CircularDoublyLinkedList_size(concatenated));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_equals_strict(CDLL2, concatenated));
}

void test_CircularDoublyLinkedList_concat_6() {
    TEST_MESSAGE("Case 6 --> Second CircularDoublyLinkedList is Empty:");
    TYPE d1, d2;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList *concatenated = CircularDoublyLinkedList_concat(CDLL1, CDLL2);
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(CircularDoublyLinkedList_size(CDLL1), CircularDoublyLinkedList_size(concatenated));
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_equals_strict(CDLL1, concatenated));
}

void test_CircularDoublyLinkedList_concat_7() {
    TEST_MESSAGE("Case 7 --> Both CircularDoublyLinkedList are Empty:");
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList *concatenated = CircularDoublyLinkedList_concat(CDLL1, CDLL2);
    TEST_ASSERT_NULL(concatenated);
}

void test_CircularDoublyLinkedList_concat_8() {
    TEST_MESSAGE("Case 8 --> 2 Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_sort_asc(&CDLL1, _compare_TYPE);

    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL2, &d3);
    CircularDoublyLinkedList_add_last(CDLL2, &d4);
    CircularDoublyLinkedList_sort_desc(&CDLL2, _compare_TYPE);

    size_t concatenated_size = CircularDoublyLinkedList_size(CDLL1) + CircularDoublyLinkedList_size(CDLL2);

    CircularDoublyLinkedList *concatenated = CircularDoublyLinkedList_concat(CDLL1, CDLL2);
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_first_element(concatenated));
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_last_element(concatenated));
    TEST_ASSERT_EQUAL(concatenated_size, CircularDoublyLinkedList_size(concatenated));
    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(concatenated));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(concatenated));

    CircularDoublyLinkedList *concatenated_2 = CircularDoublyLinkedList_concat(CDLL2, CDLL1);
    TEST_ASSERT_EQUAL(&d4, CircularDoublyLinkedList_first_element(concatenated_2));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_last_element(concatenated_2));
    TEST_ASSERT_EQUAL(concatenated_size, CircularDoublyLinkedList_size(concatenated_2));
    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(concatenated_2));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(concatenated_2));

    CircularDoublyLinkedList *concatenated_3 = CircularDoublyLinkedList_concat(CDLL1, CDLL1);
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_first_element(concatenated_3));
    TEST_ASSERT_EQUAL(&d2, CircularDoublyLinkedList_last_element(concatenated_3));
    TEST_ASSERT_EQUAL(concatenated_size, CircularDoublyLinkedList_size(concatenated_3));
    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(concatenated_3));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(concatenated_3));

    CircularDoublyLinkedList *concatenated_4 = CircularDoublyLinkedList_concat(CDLL2, CDLL2);
    TEST_ASSERT_EQUAL(&d4, CircularDoublyLinkedList_first_element(concatenated_4));
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_last_element(concatenated_4));
    TEST_ASSERT_EQUAL(concatenated_size, CircularDoublyLinkedList_size(concatenated_4));
    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(concatenated_4));
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(concatenated_4));
}

void test_CircularDoublyLinkedList_reverse_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    size_t size = CircularDoublyLinkedList_size(CDLL);
    int sort_order = CircularDoublyLinkedList_sort_order(CDLL);

   CircularDoublyLinkedList_reverse(&CDLL);
    for (long i = 0, j = size - 1; i < size && j >= 0; i++, j--) {
        TEST_ASSERT_EQUAL(j+1, _convert_to_TYPE(CircularDoublyLinkedList_get(CDLL, j)));
    }
    TEST_ASSERT_EQUAL((-1)*sort_order, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_reverse_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    bool reversed = CircularDoublyLinkedList_reverse(&CDLL);
    TEST_ASSERT_FALSE(reversed);
}

void test_CircularDoublyLinkedList_reverse_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    bool reversed = CircularDoublyLinkedList_reverse(&CDLL);
    TEST_ASSERT_FALSE(reversed);
}

void test_CircularDoublyLinkedList_reverse_4() {
    TEST_MESSAGE("Case 4 --> Ascending Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);
    size_t size = CircularDoublyLinkedList_size(CDLL);

    CircularDoublyLinkedList_reverse(&CDLL);
    for (long i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL(i+1, *((int *) CircularDoublyLinkedList_get(CDLL, i)));
    }
    TEST_ASSERT_EQUAL(__DESC__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_reverse_5() {
    TEST_MESSAGE("Case 5 --> Descending Sorted CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_sort_desc(&CDLL, _compare_TYPE);
    size_t size = CircularDoublyLinkedList_size(CDLL);

    CircularDoublyLinkedList_reverse(&CDLL);
    for (long i = 0, j = size - 1; i < size && j >= 0; i++, j--) {
        TEST_ASSERT_EQUAL(j+1, *((int *) CircularDoublyLinkedList_get(CDLL, i)));
    }
    TEST_ASSERT_EQUAL(__ASC__, CircularDoublyLinkedList_sort_order(CDLL));
}

void test_CircularDoublyLinkedList_is_equals_strict_1() {
    TEST_MESSAGE("Case 1 --> Same Data Pointers:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);

    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);
    CircularDoublyLinkedList_add_last(CDLL2, &d3);
    CircularDoublyLinkedList_add_last(CDLL2, &d4);

    for (long i = 0; i < CircularDoublyLinkedList_size(CDLL1); i++) {
        TEST_ASSERT_EQUAL(CircularDoublyLinkedList_get(CDLL1, i), CircularDoublyLinkedList_get(CDLL2, i));
    }
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_equals_strict(CDLL1, CDLL2));
}

void test_CircularDoublyLinkedList_is_equals_strict_2() {
    TEST_MESSAGE("Case 2 --> First CircularDoublyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NULL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);
    CircularDoublyLinkedList_add_last(CDLL2, &d3);
    CircularDoublyLinkedList_add_last(CDLL2, &d4);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals_strict(CDLL1, CDLL2));
}

void test_CircularDoublyLinkedList_is_equals_strict_3() {
    TEST_MESSAGE("Case 3 --> Second CircularDoublyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NULL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals_strict(CDLL1, CDLL2));
}

void test_CircularDoublyLinkedList_is_equals_strict_4() {
    TEST_MESSAGE("Case 4 --> First CircularDoublyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);
    CircularDoublyLinkedList_add_last(CDLL2, &d3);
    CircularDoublyLinkedList_add_last(CDLL2, &d4);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals_strict(CDLL1, CDLL2));
}

void test_CircularDoublyLinkedList_is_equals_strict_5() {
    TEST_MESSAGE("Case 5 --> Second CircularDoublyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals_strict(CDLL1, CDLL2));
}

void test_CircularDoublyLinkedList_is_equals_strict_6() {
    TEST_MESSAGE("Case 6 --> Same Data Pointers, but one of then is Sorted:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);
    CircularDoublyLinkedList_sort_asc(&CDLL1, _compare_TYPE);

    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);
    CircularDoublyLinkedList_add_last(CDLL2, &d3);
    CircularDoublyLinkedList_add_last(CDLL2, &d4);

    for (long i = 0; i < CircularDoublyLinkedList_size(CDLL1); i++) {
        TEST_ASSERT_EQUAL(CircularDoublyLinkedList_get(CDLL1, i), CircularDoublyLinkedList_get(CDLL2, i));
    }
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals_strict(CDLL1, CDLL2));
}

void test_CircularDoublyLinkedList_is_equals_strict_7() {
    TEST_MESSAGE("Case 7 --> Same Data (content, not pointers):");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    TYPE d11 = 1, d22 = 2, d33 = 3, d44 = 4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);

    CircularDoublyLinkedList_add_last(CDLL2, &d11);
    CircularDoublyLinkedList_add_last(CDLL2, &d22);
    CircularDoublyLinkedList_add_last(CDLL2, &d33);
    CircularDoublyLinkedList_add_last(CDLL2, &d44);

    for (long i = 0; i < CircularDoublyLinkedList_size(CDLL1); i++) {
        TEST_ASSERT_EQUAL(_convert_to_TYPE(CircularDoublyLinkedList_get(CDLL1, i)), _convert_to_TYPE(CircularDoublyLinkedList_get(CDLL2, i)));
    }
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals_strict(CDLL1, CDLL2));
}

void test_CircularDoublyLinkedList_is_equals_strict_8() {
    TEST_MESSAGE("Case 8 --> Different sizes:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);

    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);
    CircularDoublyLinkedList_add_last(CDLL2, &d3);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals_strict(CDLL1, CDLL2));
}

void test_CircularDoublyLinkedList_is_equals_1() {
    TEST_MESSAGE("Case 1 --> Same Data Pointers:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);

    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);
    CircularDoublyLinkedList_add_last(CDLL2, &d3);
    CircularDoublyLinkedList_add_last(CDLL2, &d4);

    for (long i = 0; i < CircularDoublyLinkedList_size(CDLL1); i++) {
        TEST_ASSERT_EQUAL(CircularDoublyLinkedList_get(CDLL1, i), CircularDoublyLinkedList_get(CDLL2, i));
    }
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_equals(CDLL1, CDLL2, _compare_TYPE));
}

void test_CircularDoublyLinkedList_is_equals_2() {
    TEST_MESSAGE("Case 2 --> First CircularDoublyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NULL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);
    CircularDoublyLinkedList_add_last(CDLL2, &d3);
    CircularDoublyLinkedList_add_last(CDLL2, &d4);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals(CDLL1, CDLL2, _compare_TYPE));
}

void test_CircularDoublyLinkedList_is_equals_3() {
    TEST_MESSAGE("Case 3 --> Second CircularDoublyLinkedList = NULL:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NULL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals(CDLL1, CDLL2, _compare_TYPE));
}

void test_CircularDoublyLinkedList_is_equals_4() {
    TEST_MESSAGE("Case 4 --> First CircularDoublyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);
    CircularDoublyLinkedList_add_last(CDLL2, &d3);
    CircularDoublyLinkedList_add_last(CDLL2, &d4);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals(CDLL1, CDLL2, _compare_TYPE));
}

void test_CircularDoublyLinkedList_is_equals_5() {
    TEST_MESSAGE("Case 5 --> Second CircularDoublyLinkedList is Empty:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals(CDLL1, CDLL2, _compare_TYPE));
}

void test_CircularDoublyLinkedList_is_equals_6() {
    TEST_MESSAGE("Case 6 --> Same Data Pointers, but one of then is Sorted:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);
    CircularDoublyLinkedList_sort_asc(&CDLL1, _compare_TYPE);

    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);
    CircularDoublyLinkedList_add_last(CDLL2, &d3);
    CircularDoublyLinkedList_add_last(CDLL2, &d4);

    for (long i = 0; i < CircularDoublyLinkedList_size(CDLL1); i++) {
        TEST_ASSERT_EQUAL(CircularDoublyLinkedList_get(CDLL1, i), CircularDoublyLinkedList_get(CDLL2, i));
    }
    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals(CDLL1, CDLL2, _compare_TYPE));
}

void test_CircularDoublyLinkedList_is_equals_7() {
    TEST_MESSAGE("Case 7 --> Same Data (content, not pointers):");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    TYPE d11 = 1, d22 = 2, d33 = 3, d44 = 4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);

    CircularDoublyLinkedList_add_last(CDLL2, &d11);
    CircularDoublyLinkedList_add_last(CDLL2, &d22);
    CircularDoublyLinkedList_add_last(CDLL2, &d33);
    CircularDoublyLinkedList_add_last(CDLL2, &d44);

    for (long i = 0; i < CircularDoublyLinkedList_size(CDLL1); i++) {
        TEST_ASSERT_EQUAL(_convert_to_TYPE(CircularDoublyLinkedList_get(CDLL1, i)), _convert_to_TYPE(CircularDoublyLinkedList_get(CDLL2, i)));
    }
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_equals(CDLL1, CDLL2, _compare_TYPE));
}

void test_CircularDoublyLinkedList_is_equals_8() {
    TEST_MESSAGE("Case 8 --> Different sizes:");
    TYPE d1, d2, d3, d4;
    CircularDoublyLinkedList *CDLL1 = NEW_CDLL;
    CircularDoublyLinkedList *CDLL2 = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL1, &d1);
    CircularDoublyLinkedList_add_last(CDLL1, &d2);
    CircularDoublyLinkedList_add_last(CDLL1, &d3);
    CircularDoublyLinkedList_add_last(CDLL1, &d4);

    CircularDoublyLinkedList_add_last(CDLL2, &d1);
    CircularDoublyLinkedList_add_last(CDLL2, &d2);
    CircularDoublyLinkedList_add_last(CDLL2, &d3);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_equals(CDLL1, CDLL2, _compare_TYPE));
}

void test_CircularDoublyLinkedList_sort_asc_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d2);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(CDLL));

    bool sorted = CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);
    TEST_ASSERT_TRUE(sorted);
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__ASC__, CircularDoublyLinkedList_sort_order(CDLL));
    for (long i = 0; i < CircularDoublyLinkedList_size(CDLL); i++) {
        TEST_ASSERT_EQUAL(i+1, _convert_to_TYPE(CircularDoublyLinkedList_get(CDLL, i)));
    }
}

void test_CircularDoublyLinkedList_sort_asc_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    bool sorted = CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_CircularDoublyLinkedList_sort_asc_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    bool sorted = CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_CircularDoublyLinkedList_sort_desc_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    size_t  size = CircularDoublyLinkedList_size(CDLL);

    TEST_ASSERT_FALSE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__UNSORTED__, CircularDoublyLinkedList_sort_order(CDLL));

    bool sorted = CircularDoublyLinkedList_sort_desc(&CDLL, _compare_TYPE);
    TEST_ASSERT_TRUE(sorted);
    TEST_ASSERT_TRUE(CircularDoublyLinkedList_is_sorted(CDLL));
    TEST_ASSERT_EQUAL(__DESC__, CircularDoublyLinkedList_sort_order(CDLL));
    for (long i = 0, j = size; i < size && j > 0; i++, j--) {
        TEST_ASSERT_EQUAL(j, _convert_to_TYPE(CircularDoublyLinkedList_get(CDLL, i)));
    }
}

void test_CircularDoublyLinkedList_sort_desc_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    bool sorted = CircularDoublyLinkedList_sort_desc(&CDLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_CircularDoublyLinkedList_sort_desc_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    bool sorted = CircularDoublyLinkedList_sort_desc(&CDLL, _compare_TYPE);
    TEST_ASSERT_FALSE(sorted);
}

void test_CircularDoublyLinkedList_sorted_insert_1() {
    TEST_MESSAGE("Case 1 --> Sorted CircularDoublyLinkedList:");
    TYPE d0 = 0, d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5, d6 = 6;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL, &d5);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d4);

    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);

    CircularDoublyLinkedList_sorted_insert(CDLL, &d0, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d0, CircularDoublyLinkedList_get(CDLL, 0));
    CircularDoublyLinkedList_sorted_insert(CDLL, &d3, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d3, CircularDoublyLinkedList_get(CDLL, 3));
    CircularDoublyLinkedList_sorted_insert(CDLL, &d6, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d6, CircularDoublyLinkedList_get(CDLL, 6));
}

void test_CircularDoublyLinkedList_sorted_insert_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NULL;

    bool inserted = CircularDoublyLinkedList_sorted_insert(CDLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(inserted);
}

void test_CircularDoublyLinkedList_sorted_insert_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    TYPE d1;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    bool inserted = CircularDoublyLinkedList_sorted_insert(CDLL, &d1, _compare_TYPE);
    TEST_ASSERT_FALSE(inserted);
}

void test_CircularDoublyLinkedList_sorted_insert_4() {
    TEST_MESSAGE("Case 4 --> Unsorted CircularDoublyLinkedList:");
    TYPE d0 = 0, d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);

    bool inserted = CircularDoublyLinkedList_sorted_insert(CDLL, &d0, _compare_TYPE);
    TEST_ASSERT_FALSE(inserted);
    TEST_ASSERT_EQUAL(&d4, CircularDoublyLinkedList_get(CDLL, 0));
}

void test_CircularDoublyLinkedList_sorted_insert_5() {
    TEST_MESSAGE("Case 5 --> NULL Data:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL, &d4);
    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);

    bool inserted = CircularDoublyLinkedList_sorted_insert(CDLL, NULL, _compare_TYPE);
    TEST_ASSERT_FALSE(inserted);
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_get(CDLL, 0));
}

void test_CircularDoublyLinkedList_min_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d4);

    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_min(CDLL, _compare_TYPE));

    CircularDoublyLinkedList_sort_desc(&CDLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_min(CDLL, _compare_TYPE));

    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d1, CircularDoublyLinkedList_min(CDLL, _compare_TYPE));
}

void test_CircularDoublyLinkedList_min_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    TEST_ASSERT_NULL(CircularDoublyLinkedList_min(CDLL, _compare_TYPE));
}

void test_CircularDoublyLinkedList_min_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    TEST_ASSERT_NULL(CircularDoublyLinkedList_min(CDLL, _compare_TYPE));
}

void test_CircularDoublyLinkedList_max_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty CircularDoublyLinkedList:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    CircularDoublyLinkedList_add_last(CDLL, &d1);
    CircularDoublyLinkedList_add_last(CDLL, &d2);
    CircularDoublyLinkedList_add_last(CDLL, &d3);
    CircularDoublyLinkedList_add_last(CDLL, &d4);

    TEST_ASSERT_EQUAL(&d4, CircularDoublyLinkedList_max(CDLL, _compare_TYPE));

    CircularDoublyLinkedList_sort_desc(&CDLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d4, CircularDoublyLinkedList_max(CDLL, _compare_TYPE));

    CircularDoublyLinkedList_sort_asc(&CDLL, _compare_TYPE);
    TEST_ASSERT_EQUAL(&d4, CircularDoublyLinkedList_max(CDLL, _compare_TYPE));
}

void test_CircularDoublyLinkedList_max_2() {
    TEST_MESSAGE("Case 2 --> NULL CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NULL;

    TEST_ASSERT_NULL(CircularDoublyLinkedList_max(CDLL, _compare_TYPE));
}

void test_CircularDoublyLinkedList_max_3() {
    TEST_MESSAGE("Case 3 --> Empty CircularDoublyLinkedList:");
    CircularDoublyLinkedList *CDLL = NEW_CDLL;

    TEST_ASSERT_NULL(CircularDoublyLinkedList_max(CDLL, _compare_TYPE));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_CircularDoublyLinkedList_create_1);
    RUN_TEST(test_CircularDoublyLinkedList_clean_1);
    RUN_TEST(test_CircularDoublyLinkedList_clean_2);
    RUN_TEST(test_CircularDoublyLinkedList_destroy_1);
    RUN_TEST(test_CircularDoublyLinkedList_destroy_2);
    RUN_TEST(test_CircularDoublyLinkedList_is_empty_1);
    RUN_TEST(test_CircularDoublyLinkedList_is_empty_2);
    RUN_TEST(test_CircularDoublyLinkedList_is_empty_3);
    RUN_TEST(test_CircularDoublyLinkedList_is_sorted_1);
    RUN_TEST(test_CircularDoublyLinkedList_is_sorted_2);
    RUN_TEST(test_CircularDoublyLinkedList_is_sorted_3);
    RUN_TEST(test_CircularDoublyLinkedList_is_sorted_4);
    RUN_TEST(test_CircularDoublyLinkedList_sort_order_1);
    RUN_TEST(test_CircularDoublyLinkedList_sort_order_2);
    RUN_TEST(test_CircularDoublyLinkedList_sort_order_3);
    RUN_TEST(test_CircularDoublyLinkedList_sort_order_4);
    RUN_TEST(test_CircularDoublyLinkedList_add_first_1);
    RUN_TEST(test_CircularDoublyLinkedList_add_first_2);
    RUN_TEST(test_CircularDoublyLinkedList_add_first_3);
    RUN_TEST(test_CircularDoublyLinkedList_add_first_4);
    RUN_TEST(test_CircularDoublyLinkedList_add_first_5);
    RUN_TEST(test_CircularDoublyLinkedList_add_last_1);
    RUN_TEST(test_CircularDoublyLinkedList_add_last_2);
    RUN_TEST(test_CircularDoublyLinkedList_add_last_3);
    RUN_TEST(test_CircularDoublyLinkedList_add_last_4);
    RUN_TEST(test_CircularDoublyLinkedList_add_last_5);
    RUN_TEST(test_CircularDoublyLinkedList_remove_first_1);
    RUN_TEST(test_CircularDoublyLinkedList_remove_first_2);
    RUN_TEST(test_CircularDoublyLinkedList_remove_first_3);
    RUN_TEST(test_CircularDoublyLinkedList_remove_last_1);
    RUN_TEST(test_CircularDoublyLinkedList_remove_last_2);
    RUN_TEST(test_CircularDoublyLinkedList_remove_last_3);
    RUN_TEST(test_CircularDoublyLinkedList_remove_at_1);
    RUN_TEST(test_CircularDoublyLinkedList_remove_at_2);
    RUN_TEST(test_CircularDoublyLinkedList_remove_at_3);
    RUN_TEST(test_CircularDoublyLinkedList_remove_at_4);
    RUN_TEST(test_CircularDoublyLinkedList_remove_at_5);
    RUN_TEST(test_CircularDoublyLinkedList_remove_1);
    RUN_TEST(test_CircularDoublyLinkedList_remove_2);
    RUN_TEST(test_CircularDoublyLinkedList_remove_3);
    RUN_TEST(test_CircularDoublyLinkedList_remove_4);
    RUN_TEST(test_CircularDoublyLinkedList_remove_5);
    RUN_TEST(test_CircularDoublyLinkedList_remove_all_1);
    RUN_TEST(test_CircularDoublyLinkedList_remove_all_2);
    RUN_TEST(test_CircularDoublyLinkedList_remove_all_3);
    RUN_TEST(test_CircularDoublyLinkedList_remove_all_4);
    RUN_TEST(test_CircularDoublyLinkedList_remove_all_5);
    RUN_TEST(test_CircularDoublyLinkedList_size_1);
    RUN_TEST(test_CircularDoublyLinkedList_size_2);
    RUN_TEST(test_CircularDoublyLinkedList_size_3);
    RUN_TEST(test_CircularDoublyLinkedList_first_element_1);
    RUN_TEST(test_CircularDoublyLinkedList_first_element_2);
    RUN_TEST(test_CircularDoublyLinkedList_first_element_3);
    RUN_TEST(test_CircularDoublyLinkedList_last_element_1);
    RUN_TEST(test_CircularDoublyLinkedList_last_element_2);
    RUN_TEST(test_CircularDoublyLinkedList_last_element_3);
    RUN_TEST(test_CircularDoublyLinkedList_get_1);
    RUN_TEST(test_CircularDoublyLinkedList_get_2);
    RUN_TEST(test_CircularDoublyLinkedList_get_3);
    RUN_TEST(test_CircularDoublyLinkedList_get_4);
    RUN_TEST(test_CircularDoublyLinkedList_get_5);
    RUN_TEST(test_consistence_between_first_element_and_get_at_0);
    RUN_TEST(test_consistence_between_last_element_and_get_at_size_minus_1);
    RUN_TEST(test_CircularDoublyLinkedList_count_1);
    RUN_TEST(test_CircularDoublyLinkedList_count_2);
    RUN_TEST(test_CircularDoublyLinkedList_count_3);
    RUN_TEST(test_CircularDoublyLinkedList_count_4);
    RUN_TEST(test_CircularDoublyLinkedList_count_5);
    RUN_TEST(test_CircularDoublyLinkedList_contains_1);
    RUN_TEST(test_CircularDoublyLinkedList_contains_2);
    RUN_TEST(test_CircularDoublyLinkedList_contains_3);
    RUN_TEST(test_CircularDoublyLinkedList_contains_4);
    RUN_TEST(test_CircularDoublyLinkedList_contains_5);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_1);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_2);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_3);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_4);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_5);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_6);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_7);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_8);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_9);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_10);
    RUN_TEST(test_CircularDoublyLinkedList_insert_at_11);
    RUN_TEST(test_CircularDoublyLinkedList_clone_1);
    RUN_TEST(test_CircularDoublyLinkedList_clone_2);
    RUN_TEST(test_CircularDoublyLinkedList_clone_3);
    RUN_TEST(test_CircularDoublyLinkedList_concat_1);
    RUN_TEST(test_CircularDoublyLinkedList_concat_2);
    RUN_TEST(test_CircularDoublyLinkedList_concat_3);
    RUN_TEST(test_CircularDoublyLinkedList_concat_4);
    RUN_TEST(test_CircularDoublyLinkedList_concat_5);
    RUN_TEST(test_CircularDoublyLinkedList_concat_6);
    RUN_TEST(test_CircularDoublyLinkedList_concat_7);
    RUN_TEST(test_CircularDoublyLinkedList_concat_8);
    RUN_TEST(test_CircularDoublyLinkedList_reverse_1);
    RUN_TEST(test_CircularDoublyLinkedList_reverse_2);
    RUN_TEST(test_CircularDoublyLinkedList_reverse_3);
    RUN_TEST(test_CircularDoublyLinkedList_reverse_4);
    RUN_TEST(test_CircularDoublyLinkedList_reverse_5);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_strict_1);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_strict_2);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_strict_3);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_strict_4);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_strict_5);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_strict_6);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_strict_7);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_strict_8);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_1);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_2);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_3);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_4);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_5);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_6);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_7);
    RUN_TEST(test_CircularDoublyLinkedList_is_equals_8);
    RUN_TEST(test_CircularDoublyLinkedList_sort_asc_1);
    RUN_TEST(test_CircularDoublyLinkedList_sort_asc_2);
    RUN_TEST(test_CircularDoublyLinkedList_sort_asc_3);
    RUN_TEST(test_CircularDoublyLinkedList_sort_desc_1);
    RUN_TEST(test_CircularDoublyLinkedList_sort_desc_2);
    RUN_TEST(test_CircularDoublyLinkedList_sort_desc_3);
    RUN_TEST(test_CircularDoublyLinkedList_sorted_insert_1);
    RUN_TEST(test_CircularDoublyLinkedList_sorted_insert_2);
    RUN_TEST(test_CircularDoublyLinkedList_sorted_insert_3);
    RUN_TEST(test_CircularDoublyLinkedList_sorted_insert_4);
    RUN_TEST(test_CircularDoublyLinkedList_min_1);
    RUN_TEST(test_CircularDoublyLinkedList_min_2);
    RUN_TEST(test_CircularDoublyLinkedList_min_3);
    RUN_TEST(test_CircularDoublyLinkedList_max_1);
    RUN_TEST(test_CircularDoublyLinkedList_max_2);
    RUN_TEST(test_CircularDoublyLinkedList_max_3);
    return UNITY_END();
}
