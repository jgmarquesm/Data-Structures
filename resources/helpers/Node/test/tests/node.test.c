#include "../../main/include/unity.h"
#include "../../main/include/node.h"

#define TYPE int

void setUp(){}

void tearDown(){}

void test_Node_create() {
    Node *node = NULL;
    TYPE d;

    TEST_ASSERT_EQUAL(NULL, node);

    node = Node_create(&d);
    TEST_ASSERT_NOT_EQUAL(NULL, node);

    TYPE *data_ = Node_get_data(node);
    TEST_ASSERT_EQUAL(&d, data_);
    TEST_ASSERT_EQUAL(d, *data_);
}

void test_Node_destroy() {
    TYPE d;
    Node *node = NULL;
    TEST_ASSERT_EQUAL(NULL, node);
    node = Node_create(&d);
    TEST_ASSERT_NOT_EQUAL(NULL, node);
    Node_destroy(&node);
    TEST_ASSERT_EQUAL(NULL, node);
}

void test_Node_next_getter_and_setter() {
    TYPE d1, d2;
    Node *node = Node_create(&d1), *next = NULL, *next_ = NULL;

    TEST_ASSERT_EQUAL(NULL, next);
    next = Node_create(&d2);
    TEST_ASSERT_NOT_EQUAL(NULL, next);

    Node_set_next(node, next);
    next_ = Node_get_next(node);
    TEST_ASSERT_EQUAL(next, next_);
}

void test_Node_prev_getter_and_setter() {
    TYPE d1, d2;
    Node *node = Node_create(&d1), *prev = NULL, *prev_ = NULL;

    TEST_ASSERT_EQUAL(NULL, prev);
    prev = Node_create(&d2);
    TEST_ASSERT_NOT_EQUAL(NULL, prev);

    Node_set_prev(node, prev);
    prev_ = Node_get_prev(node);
    TEST_ASSERT_EQUAL(prev, prev_);
}

void test_Node_data_getter_and_setter() {
    TYPE d1, d2, d3;
    TYPE d11, d22, d33;
    Node *prev = Node_create(&d1), *node = Node_create(&d2), *next = Node_create(&d3);
    Node_set_next(node, next);
    Node_set_prev(node, prev);

    TYPE *data_prev = Node_get_data(prev);
    TYPE *data_node = Node_get_data(node);
    TYPE *data_next = Node_get_data(next);
    TEST_ASSERT_EQUAL(&d1, data_prev);
    TEST_ASSERT_EQUAL(d1, *data_prev);
    TEST_ASSERT_EQUAL(&d2, data_node);
    TEST_ASSERT_EQUAL(d2, *data_node);
    TEST_ASSERT_EQUAL(&d3, data_next);
    TEST_ASSERT_EQUAL(d3, *data_next);

    Node_set_data(prev, &d33);
    Node_set_data(node, &d11);
    Node_set_data(next, &d22);

    data_prev = Node_get_data(prev);
    data_node = Node_get_data(node);
    data_next = Node_get_data(next);
    TEST_ASSERT_EQUAL(&d33, data_prev);
    TEST_ASSERT_EQUAL(d33, *data_prev);
    TEST_ASSERT_EQUAL(&d11, data_node);
    TEST_ASSERT_EQUAL(d11, *data_node);
    TEST_ASSERT_EQUAL(&d22, data_next);
    TEST_ASSERT_EQUAL(d22, *data_next);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_Node_create);
    RUN_TEST(test_Node_destroy);
    RUN_TEST(test_Node_next_getter_and_setter);
    RUN_TEST(test_Node_prev_getter_and_setter);
    RUN_TEST(test_Node_data_getter_and_setter);
    return UNITY_END();
}

