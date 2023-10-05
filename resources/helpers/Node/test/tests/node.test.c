#include "../../main/include/unity.h"
#include "../../main/include/node.h"

#define TYPE int

void setUp(){}

void tearDown(){}

void test_Node_create_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Data:");
    Node *node = NULL;
    TYPE d;

    TEST_ASSERT_EQUAL(NULL, node);

    node = Node_create(&d);
    TEST_ASSERT_NOT_EQUAL(NULL, node);

    TYPE *data_ = Node_get_data(node);
    TEST_ASSERT_EQUAL(&d, data_);
    TEST_ASSERT_EQUAL(d, *data_);
}

void test_Node_create_2() {
    TEST_MESSAGE("Case 2 --> NULL Data:");
    Node *node = NULL;
    TEST_ASSERT_NULL(node);

    node = Node_create(NULL);
    TEST_ASSERT_NULL(node);
}

void test_Node_destroy_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Node:");
    TYPE d;
    Node *node = NULL;
    TEST_ASSERT_EQUAL(NULL, node);

    node = Node_create(&d);
    TEST_ASSERT_NOT_EQUAL(NULL, node);

    bool destroyed = Node_destroy(&node);
    TEST_ASSERT_TRUE(destroyed);
    TEST_ASSERT_EQUAL(NULL, node);
}

void test_Node_destroy_2() {
    TEST_MESSAGE("Case 2 --> NULL Node:");
    Node *node = NULL;
    TEST_ASSERT_FALSE(Node_destroy(&node));
}

void test_Node_next_getter_and_setter_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Node:");
    TYPE d1, d2;
    Node *node = Node_create(&d1), *next = NULL, *next_ = NULL;

    TEST_ASSERT_EQUAL(NULL, next);
    next = Node_create(&d2);
    TEST_ASSERT_NOT_EQUAL(NULL, next);

    Node_set_next(node, next);
    next_ = Node_get_next(node);
    TEST_ASSERT_EQUAL(next, next_);
}

void test_Node_next_getter_and_setter_2() {
    TEST_MESSAGE("Case 2 --> NULL Node:");
    TYPE d1;
    Node *node = NULL, *next = Node_create(&d1);
    Node *got = Node_get_next(node);
    TEST_ASSERT_NULL(got);

    bool set = Node_set_next(node, next);
    Node *got_after = Node_get_next(node);
    TEST_ASSERT_FALSE(set);
    TEST_ASSERT_NULL(got_after);
}

void test_Node_next_getter_and_setter_3() {
    TEST_MESSAGE("Case 3 --> NULL Node::Next:");
    TYPE d1;
    Node *node = Node_create(&d1);

    bool set = Node_set_next(node, NULL);
    TEST_ASSERT_TRUE(set);

    Node *got = Node_get_next(node);
    TEST_ASSERT_NULL(got);
}

void test_Node_prev_getter_and_setter_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Node:");
    TYPE d1, d2;
    Node *node = Node_create(&d1), *prev = NULL, *prev_ = NULL;

    TEST_ASSERT_EQUAL(NULL, prev);
    prev = Node_create(&d2);
    TEST_ASSERT_NOT_EQUAL(NULL, prev);

    Node_set_prev(node, prev);
    prev_ = Node_get_prev(node);
    TEST_ASSERT_EQUAL(prev, prev_);
}

void test_Node_prev_getter_and_setter_2() {
    TEST_MESSAGE("Case 2 --> NULL Node:");
    TYPE d1;
    Node *node = NULL, *prev = Node_create(&d1);
    Node *got = Node_get_prev(node);
    TEST_ASSERT_NULL(got);

    bool set = Node_set_prev(node, prev);
    Node *got_after = Node_get_prev(node);
    TEST_ASSERT_FALSE(set);
    TEST_ASSERT_NULL(got_after);
}

void test_Node_prev_getter_and_setter_3() {
    TEST_MESSAGE("Case 3 --> NULL Node::Prev:");
    TYPE d1;
    Node *node = Node_create(&d1);

    bool set = Node_set_prev(node, NULL);
    TEST_ASSERT_TRUE(set);

    Node *got = Node_get_prev(node);
    TEST_ASSERT_NULL(got);
}

void test_Node_data_getter_and_setter_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Node && Non NULL Data:");
    TYPE d1, d2, d3;
    TYPE d11, d22, d33;
    Node *prev = Node_create(&d1), *node = Node_create(&d2), *next = Node_create(&d3);
    Node_set_next(node, next);
    Node_set_prev(node, prev);

    TYPE *data_prev = Node_get_data(prev);
    TYPE *data_node = Node_get_data(node);
    TYPE *data_next = Node_get_data(next);
    TEST_ASSERT_EQUAL(&d1, data_prev);
    TEST_ASSERT_EQUAL(&d2, data_node);
    TEST_ASSERT_EQUAL(&d3, data_next);

    Node_set_data(prev, &d33);
    Node_set_data(node, &d11);
    Node_set_data(next, &d22);

    data_prev = Node_get_data(prev);
    data_node = Node_get_data(node);
    data_next = Node_get_data(next);
    TEST_ASSERT_EQUAL(&d33, data_prev);
    TEST_ASSERT_EQUAL(&d11, data_node);
    TEST_ASSERT_EQUAL(&d22, data_next);
}

void test_Node_data_getter_and_setter_2() {
    TEST_MESSAGE("Case 2 --> NULL Node:");
    TYPE d1;
    Node *node = NULL;

    void *got = Node_get_data(node);
    TEST_ASSERT_NULL(got);

    bool set = Node_set_data(node, &d1);
    TEST_ASSERT_FALSE(set);
    void *got_after = Node_get_data(node);
    TEST_ASSERT_NULL(got_after);
}

void test_Node_data_getter_and_setter_3() {
    TEST_MESSAGE("Case 3 --> NULL Data:");
    TYPE d1;
    Node *node = Node_create(&d1);

    void *got = Node_get_data(node);
    TEST_ASSERT_EQUAL(&d1, got);

    bool set = Node_set_data(node, NULL);
    void *got_after = Node_get_data(node);
    TEST_ASSERT_FALSE(set);
    TEST_ASSERT_EQUAL(&d1, got_after);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_Node_create_1);
    RUN_TEST(test_Node_create_2);
    RUN_TEST(test_Node_destroy_1);
    RUN_TEST(test_Node_destroy_2);
    RUN_TEST(test_Node_next_getter_and_setter_1);
    RUN_TEST(test_Node_next_getter_and_setter_2);
    RUN_TEST(test_Node_next_getter_and_setter_3);
    RUN_TEST(test_Node_prev_getter_and_setter_1);
    RUN_TEST(test_Node_prev_getter_and_setter_2);
    RUN_TEST(test_Node_prev_getter_and_setter_3);
    RUN_TEST(test_Node_data_getter_and_setter_1);
    RUN_TEST(test_Node_data_getter_and_setter_2);
    RUN_TEST(test_Node_data_getter_and_setter_3);
    return UNITY_END();
}
