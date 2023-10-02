#include "../../main/include/unity.h"
#include "../../main/include/dynamic_stack.h"

#define TYPE int
#define NEW_STACK DynamicStack_create()

void setUp(){}

void tearDown(){}

void test_DynamicStack_create() {
    DynamicStack *stack = NULL;
    TEST_ASSERT_NULL(stack);
    stack = NEW_STACK;
    TEST_ASSERT_NOT_NULL(stack);
}

void test_DynamicStack_clean_1() {
    TEST_MESSAGE("Case --> 1 Stack != NULL:");
    DynamicStack *stack = NEW_STACK;

    bool cleaned = DynamicStack_clean(stack);
    TEST_ASSERT_TRUE(cleaned);
}

void test_DynamicStack_clean_2() {
    TEST_MESSAGE("Case --> 2 Stack == NULL:");
    DynamicStack *stack = NULL;

    bool cleaned = DynamicStack_clean(stack);
    TEST_ASSERT_FALSE(cleaned);
}

void test_DynamicStack_destroy_1() {
    TEST_MESSAGE("Case --> 1 Stack != NULL:");
    DynamicStack *stack = NEW_STACK;

    TEST_ASSERT_NOT_NULL(stack);
    bool destroyed = DynamicStack_destroy(&stack);
    TEST_ASSERT_TRUE(destroyed);
    TEST_ASSERT_NULL(stack);
}

void test_DynamicStack_destroy_2() {
    TEST_MESSAGE("Case --> 2 Stack == NULL:");
    DynamicStack *stack = NULL;

    bool destroyed = DynamicStack_destroy(&stack);
    TEST_ASSERT_FALSE(destroyed);
}

void test_DynamicStack_is_empty_1() {
    TEST_MESSAGE("Case 1 --> Non Empty DynamicStack:");
    TYPE d1, d2;
    DynamicStack *stack = NEW_STACK;
    DynamicStack_push(stack, &d1);
    DynamicStack_push(stack, &d2);

    TEST_ASSERT_FALSE(DynamicStack_is_empty(stack));
    TEST_ASSERT_EQUAL(2, DynamicStack_size(stack));
}

void test_DynamicStack_is_empty_2() {
    TEST_MESSAGE("Case 2 --> Empty DynamicStack:");
    DynamicStack *stack = NEW_STACK;

    TEST_ASSERT_TRUE(DynamicStack_is_empty(stack));
    TEST_ASSERT_EQUAL(0, DynamicStack_size(stack));
}

void test_DynamicStack_is_empty_3() {
    TEST_MESSAGE("Case 3 --> NULL DynamicStack:");
    DynamicStack *stack = NULL;

    TEST_ASSERT_TRUE(DynamicStack_is_empty(stack));
    TEST_ASSERT_EQUAL(0, DynamicStack_size(stack));
}

void test_DynamicStack_push_1() {
    TEST_MESSAGE("Case 1 --> Non NULL DynamicStack and Non NULL Data:");
    TYPE d1, d2;
    DynamicStack *stack = NEW_STACK;

    bool pushed = DynamicStack_push(stack, &d1);
    TEST_ASSERT_TRUE(pushed);
    TEST_ASSERT_EQUAL(&d1, DynamicStack_peek(stack));
    TEST_ASSERT_EQUAL(1, DynamicStack_size(stack));

    bool pushed_2 = DynamicStack_push(stack, &d2);
    TEST_ASSERT_TRUE(pushed_2);
    TEST_ASSERT_EQUAL(&d2, DynamicStack_peek(stack));
    TEST_ASSERT_EQUAL(2, DynamicStack_size(stack));
}

void test_DynamicStack_push_2() {
    TEST_MESSAGE("Case 2 --> NULL DynamicStack:");
    TYPE d1;
    DynamicStack *stack = NULL;

    bool pushed = DynamicStack_push(stack, &d1);
    TEST_ASSERT_FALSE(pushed);
    TEST_ASSERT_NULL(DynamicStack_peek(stack));
    TEST_ASSERT_EQUAL(0, DynamicStack_size(stack));
}

void test_DynamicStack_push_3() {
    TEST_MESSAGE("Case 3 --> NULL Data:");
    DynamicStack *stack = NEW_STACK;

    bool pushed = DynamicStack_push(stack, NULL);
    TEST_ASSERT_FALSE(pushed);
    TEST_ASSERT_NULL(DynamicStack_peek(stack));
    TEST_ASSERT_EQUAL(0, DynamicStack_size(stack));
}

void test_DynamicStack_peek_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DynamicStack:");
    TYPE d1, d2, d3, d4;
    DynamicStack *stack = NEW_STACK;

    DynamicStack_push(stack, &d1);
    TEST_ASSERT_EQUAL(&d1, DynamicStack_peek(stack));
    TEST_ASSERT_EQUAL(1, DynamicStack_size(stack));

    DynamicStack_push(stack, &d2);
    DynamicStack_push(stack, &d3);
    DynamicStack_push(stack, &d4);
    TEST_ASSERT_EQUAL(4, DynamicStack_size(stack));
    TEST_ASSERT_EQUAL(&d4, DynamicStack_peek(stack));
}

void test_DynamicStack_peek_2() {
    TEST_MESSAGE("Case 2 --> NULL DynamicStack:");
    DynamicStack *stack = NULL;

    TEST_ASSERT_NULL(DynamicStack_peek(stack));
}

void test_DynamicStack_peek_3() {
    TEST_MESSAGE("Case 3 --> Empty DynamicStack:");
    DynamicStack *stack = NEW_STACK;

    TEST_ASSERT_NULL(DynamicStack_peek(stack));
}

void test_DynamicStack_pop_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DynamicStack:");
    TYPE d1, d2, d3;
    DynamicStack *stack = NEW_STACK;
    DynamicStack_push(stack, &d1);
    DynamicStack_push(stack, &d2);
    DynamicStack_push(stack, &d3);

    TEST_ASSERT_EQUAL(3, DynamicStack_size(stack));
    TEST_ASSERT_EQUAL(&d3, DynamicStack_peek(stack));

    void *popped = DynamicStack_pop(stack);
    TEST_ASSERT_EQUAL(&d3, popped);
    TEST_ASSERT_EQUAL(2, DynamicStack_size(stack));
    TEST_ASSERT_EQUAL(&d2, DynamicStack_peek(stack));
}

void test_DynamicStack_pop_2() {
    TEST_MESSAGE("Case 2 --> NULL DynamicStack:");
    DynamicStack *stack = NEW_STACK;

    void *popped = DynamicStack_pop(stack);
    TEST_ASSERT_NULL(popped);
}

void test_DynamicStack_pop_3() {
    TEST_MESSAGE("Case 3 --> Empty DynamicStack:");
    DynamicStack *stack = NEW_STACK;

    void *popped = DynamicStack_pop(stack);
    TEST_ASSERT_NULL(popped);
}

void test_DynamicStack_size_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DynamicStack:");
    TYPE d1, d2, d3, d4;
    DynamicStack *stack = NEW_STACK;

    DynamicStack_push(stack, &d1);
    DynamicStack_push(stack, &d2);
    DynamicStack_push(stack, &d3);
    DynamicStack_push(stack, &d4);
    TEST_ASSERT_EQUAL(4, DynamicStack_size(stack));

    DynamicStack_pop(stack);
    DynamicStack_pop(stack);
    TEST_ASSERT_EQUAL(2, DynamicStack_size(stack));
}

void test_DynamicStack_size_2() {
    TEST_MESSAGE("Case 2 --> NULL DynamicStack:");
    DynamicStack *stack = NULL;

    TEST_ASSERT_EQUAL(0, DynamicStack_size(stack));
}

void test_DynamicStack_size_3() {
    TEST_MESSAGE("Case 3 --> Empty DynamicStack:");
    DynamicStack *stack = NULL;

    TEST_ASSERT_EQUAL(0, DynamicStack_size(stack));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_DynamicStack_create);
    RUN_TEST(test_DynamicStack_clean_1);
    RUN_TEST(test_DynamicStack_clean_2);
    RUN_TEST(test_DynamicStack_destroy_1);
    RUN_TEST(test_DynamicStack_destroy_2);
    RUN_TEST(test_DynamicStack_is_empty_1);
    RUN_TEST(test_DynamicStack_is_empty_2);
    RUN_TEST(test_DynamicStack_is_empty_3);
    RUN_TEST(test_DynamicStack_push_1);
    RUN_TEST(test_DynamicStack_push_2);
    RUN_TEST(test_DynamicStack_push_3);
    RUN_TEST(test_DynamicStack_peek_1);
    RUN_TEST(test_DynamicStack_peek_2);
    RUN_TEST(test_DynamicStack_peek_3);
    RUN_TEST(test_DynamicStack_pop_1);
    RUN_TEST(test_DynamicStack_pop_2);
    RUN_TEST(test_DynamicStack_pop_3);
    RUN_TEST(test_DynamicStack_size_1);
    RUN_TEST(test_DynamicStack_size_2);
    RUN_TEST(test_DynamicStack_size_3);
    return UNITY_END();
}
