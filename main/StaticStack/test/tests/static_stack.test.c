#include "../../main/include/unity.h"
#include "../../main/include/static_stack.h"

#define CAPACITY 5
#define TYPE int
#define SIZE_OF_TYPE sizeof(TYPE)
#define NEW_STACK StaticStack_create(CAPACITY, SIZE_OF_TYPE)

void setUp(){}

void tearDown(){}

void test_StaticStack_create() {
    StaticStack *stack = NULL;
    TEST_ASSERT_NULL(stack);
    stack = NEW_STACK;
    TEST_ASSERT_NOT_NULL(stack);
}

void test_StaticStack_clean_1() {
    TEST_MESSAGE("Case --> 1 Stack != NULL:");
    StaticStack *stack = NEW_STACK;

    bool cleaned = StaticStack_clean(stack);
    TEST_ASSERT_TRUE(cleaned);
}

void test_StaticStack_clean_2() {
    TEST_MESSAGE("Case --> 2 Stack == NULL:");
    StaticStack *stack = NULL;

    bool cleaned = StaticStack_clean(stack);
    TEST_ASSERT_FALSE(cleaned);
}

void test_StaticStack_destroy_1() {
    TEST_MESSAGE("Case --> 1 Stack != NULL:");
    StaticStack *stack = NEW_STACK;

    TEST_ASSERT_NOT_NULL(stack);
    bool destroyed = StaticStack_destroy(&stack);
    TEST_ASSERT_TRUE(destroyed);
    TEST_ASSERT_NULL(stack);
}

void test_StaticStack_destroy_2() {
    TEST_MESSAGE("Case --> 2 Stack == NULL:");
    StaticStack *stack = NULL;

    bool destroyed = StaticStack_destroy(&stack);
    TEST_ASSERT_FALSE(destroyed);
}

void test_StaticStack_is_empty_1() {
    TEST_MESSAGE("Case 1 --> Non Empty StaticStack:");
    TYPE d1, d2;
    StaticStack *stack = NEW_STACK;
    StaticStack_push(stack, &d1);
    StaticStack_push(stack, &d2);

    TEST_ASSERT_FALSE(StaticStack_is_empty(stack));
    TEST_ASSERT_EQUAL(2, StaticStack_size(stack));
}

void test_StaticStack_is_empty_2() {
    TEST_MESSAGE("Case 2 --> Empty StaticStack:");
    StaticStack *stack = NEW_STACK;

    TEST_ASSERT_TRUE(StaticStack_is_empty(stack));
    TEST_ASSERT_EQUAL(0, StaticStack_size(stack));
}

void test_StaticStack_is_empty_3() {
    TEST_MESSAGE("Case 3 --> NULL StaticStack:");
    StaticStack *stack = NULL;

    TEST_ASSERT_TRUE(StaticStack_is_empty(stack));
    TEST_ASSERT_EQUAL(0, StaticStack_size(stack));
}

void test_StaticStack_is_full_1() {
    TEST_MESSAGE("Case 1 --> Non Full StaticStack:");
    TYPE d1, d2;
    StaticStack *stack = NEW_STACK;
    StaticStack_push(stack, &d1);
    StaticStack_push(stack, &d2);

    TEST_ASSERT_FALSE(StaticStack_is_full(stack));
    TEST_ASSERT_EQUAL(2, StaticStack_size(stack));
}

void test_StaticStack_is_full_2() {
    TEST_MESSAGE("Case 2 --> Full StaticStack:");
    TYPE d1, d2;
    StaticStack *stack = NEW_STACK;
    StaticStack_push(stack, &d1);
    StaticStack_push(stack, &d1);
    StaticStack_push(stack, &d2);
    StaticStack_push(stack, &d2);
    StaticStack_push(stack, &d2);

    TEST_ASSERT_TRUE(StaticStack_is_full(stack));
    TEST_ASSERT_EQUAL(5, StaticStack_size(stack));
}

void test_StaticStack_is_full_3() {
    TEST_MESSAGE("Case 3 --> Empty StaticStack:");
    StaticStack *stack = NEW_STACK;

    TEST_ASSERT_FALSE(StaticStack_is_full(stack));
    TEST_ASSERT_EQUAL(0, StaticStack_size(stack));
}

void test_StaticStack_is_full_4() {
    TEST_MESSAGE("Case 4 --> NULL StaticStack:");
    StaticStack *stack = NULL;

    TEST_ASSERT_FALSE(StaticStack_is_full(stack));
    TEST_ASSERT_EQUAL(0, StaticStack_size(stack));
}

void test_StaticStack_push_1() {
    TEST_MESSAGE("Case 1 --> Non NULL StaticStack and Non NULL Data:");
    TYPE d1 = 1, d2 = 2;
    StaticStack *stack = NEW_STACK;

    bool pushed = StaticStack_push(stack, &d1);
    TEST_ASSERT_TRUE(pushed);
    TEST_ASSERT_EQUAL(d1, *((int *) StaticStack_peek(stack)));
    TEST_ASSERT_EQUAL(1, StaticStack_size(stack));

    bool pushed_2 = StaticStack_push(stack, &d2);
    TEST_ASSERT_TRUE(pushed_2);
    TEST_ASSERT_EQUAL(d2, *((int *) StaticStack_peek(stack)));
    TEST_ASSERT_EQUAL(2, StaticStack_size(stack));
}

void test_StaticStack_push_2() {
    TEST_MESSAGE("Case 2 --> NULL StaticStack:");
    TYPE d1;
    StaticStack *stack = NULL;

    bool pushed = StaticStack_push(stack, &d1);
    TEST_ASSERT_FALSE(pushed);
    TEST_ASSERT_NULL(StaticStack_peek(stack));
    TEST_ASSERT_EQUAL(0, StaticStack_size(stack));
}

void test_StaticStack_push_3() {
    TEST_MESSAGE("Case 3 --> NULL Data:");
    StaticStack *stack = NEW_STACK;

    bool pushed = StaticStack_push(stack, NULL);
    TEST_ASSERT_FALSE(pushed);
    TEST_ASSERT_NULL(StaticStack_peek(stack));
    TEST_ASSERT_EQUAL(0, StaticStack_size(stack));
}

void test_StaticStack_peek_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty StaticStack:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    StaticStack *stack = NEW_STACK;

    StaticStack_push(stack, &d1);
    TEST_ASSERT_EQUAL(d1, *((int *) StaticStack_peek(stack)));
    TEST_ASSERT_EQUAL(1, StaticStack_size(stack));

    StaticStack_push(stack, &d2);
    StaticStack_push(stack, &d3);
    StaticStack_push(stack, &d4);
    TEST_ASSERT_EQUAL(4, StaticStack_size(stack));
    TEST_ASSERT_EQUAL(d4, *((int *) StaticStack_peek(stack)));
}

void test_StaticStack_peek_2() {
    TEST_MESSAGE("Case 2 --> NULL StaticStack:");
    StaticStack *stack = NULL;

    TEST_ASSERT_NULL(StaticStack_peek(stack));
}

void test_StaticStack_peek_3() {
    TEST_MESSAGE("Case 3 --> Empty StaticStack:");
    StaticStack *stack = NEW_STACK;

    TEST_ASSERT_NULL(StaticStack_peek(stack));
}

void test_StaticStack_pop_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty StaticStack:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    StaticStack *stack = NEW_STACK;
    StaticStack_push(stack, &d1);
    StaticStack_push(stack, &d2);
    StaticStack_push(stack, &d3);

    TEST_ASSERT_EQUAL(3, StaticStack_size(stack));
    TEST_ASSERT_EQUAL(d3, *((int *) StaticStack_peek(stack)));

    void *popped = StaticStack_pop(stack);
    TEST_ASSERT_EQUAL(d3, *((int *) popped));
    TEST_ASSERT_EQUAL(2, StaticStack_size(stack));
    TEST_ASSERT_EQUAL(d2, *((int *) StaticStack_peek(stack)));
}

void test_StaticStack_pop_2() {
    TEST_MESSAGE("Case 2 --> NULL StaticStack:");
    StaticStack *stack = NEW_STACK;

    void *popped = StaticStack_pop(stack);
    TEST_ASSERT_NULL(popped);
}

void test_StaticStack_pop_3() {
    TEST_MESSAGE("Case 3 --> Empty StaticStack:");
    StaticStack *stack = NEW_STACK;

    void *popped = StaticStack_pop(stack);
    TEST_ASSERT_NULL(popped);
}

void test_StaticStack_size_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty StaticStack:");
    TYPE d1, d2, d3, d4;
    StaticStack *stack = NEW_STACK;

    StaticStack_push(stack, &d1);
    StaticStack_push(stack, &d2);
    StaticStack_push(stack, &d3);
    StaticStack_push(stack, &d4);
    TEST_ASSERT_EQUAL(4, StaticStack_size(stack));

    StaticStack_pop(stack);
    StaticStack_pop(stack);
    TEST_ASSERT_EQUAL(2, StaticStack_size(stack));
}

void test_StaticStack_size_2() {
    TEST_MESSAGE("Case 2 --> NULL StaticStack:");
    StaticStack *stack = NULL;

    TEST_ASSERT_EQUAL(0, StaticStack_size(stack));
}

void test_StaticStack_size_3() {
    TEST_MESSAGE("Case 3 --> Empty StaticStack:");
    StaticStack *stack = NULL;

    TEST_ASSERT_EQUAL(0, StaticStack_size(stack));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_StaticStack_create);
    RUN_TEST(test_StaticStack_clean_1);
    RUN_TEST(test_StaticStack_clean_2);
    RUN_TEST(test_StaticStack_destroy_1);
    RUN_TEST(test_StaticStack_destroy_2);
    RUN_TEST(test_StaticStack_is_empty_1);
    RUN_TEST(test_StaticStack_is_empty_2);
    RUN_TEST(test_StaticStack_is_empty_3);
    RUN_TEST(test_StaticStack_is_full_1);
    RUN_TEST(test_StaticStack_is_full_2);
    RUN_TEST(test_StaticStack_is_full_3);
    RUN_TEST(test_StaticStack_is_full_4);
    RUN_TEST(test_StaticStack_push_1);
    RUN_TEST(test_StaticStack_push_2);
    RUN_TEST(test_StaticStack_push_3);
    RUN_TEST(test_StaticStack_peek_1);
    RUN_TEST(test_StaticStack_peek_2);
    RUN_TEST(test_StaticStack_peek_3);
    RUN_TEST(test_StaticStack_pop_1);
    RUN_TEST(test_StaticStack_pop_2);
    RUN_TEST(test_StaticStack_pop_3);
    RUN_TEST(test_StaticStack_size_1);
    RUN_TEST(test_StaticStack_size_2);
    RUN_TEST(test_StaticStack_size_3);
    return UNITY_END();
}
