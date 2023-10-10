#include "../../main/include/unity.h"
#include "../../main/include/static_queue.h"

#define CAPACITY 5
#define TYPE int
#define SIZE_OF_TYPE sizeof(TYPE)
#define NEW_QUEUE StaticQueue_create(CAPACITY, SIZE_OF_TYPE)

void setUp(){}

void tearDown(){}

void test_StaticQueue_create() {
    StaticQueue *queue = NULL;
    TEST_ASSERT_NULL(queue);
    queue = NEW_QUEUE;
    TEST_ASSERT_NOT_NULL(queue);
}

void test_StaticQueue_clean_1() {
    TEST_MESSAGE("Case --> 1 Queue != NULL:");
    StaticQueue *queue = NEW_QUEUE;

    bool cleaned = StaticQueue_clean(queue);
    TEST_ASSERT_TRUE(cleaned);
}

void test_StaticQueue_clean_2() {
    TEST_MESSAGE("Case --> 2 Queue == NULL:");
    StaticQueue *queue = NULL;

    bool cleaned = StaticQueue_clean(queue);
    TEST_ASSERT_FALSE(cleaned);
}

void test_StaticQueue_destroy_1() {
    TEST_MESSAGE("Case --> 1 Queue != NULL:");
    StaticQueue *queue = NEW_QUEUE;

    TEST_ASSERT_NOT_NULL(queue);
    bool destroyed = StaticQueue_destroy(&queue);
    TEST_ASSERT_TRUE(destroyed);
    TEST_ASSERT_NULL(queue);
}

void test_StaticQueue_destroy_2() {
    TEST_MESSAGE("Case --> 2 Queue == NULL:");
    StaticQueue *queue = NULL;

    bool destroyed = StaticQueue_destroy(&queue);
    TEST_ASSERT_FALSE(destroyed);
}

void test_StaticQueue_is_empty_1() {
    TEST_MESSAGE("Case 1 --> Non Empty StaticQueue:");
    TYPE d1, d2;
    StaticQueue *queue = NEW_QUEUE;
    StaticQueue_enqueue(queue, &d1);
    StaticQueue_enqueue(queue, &d2);

    TEST_ASSERT_FALSE(StaticQueue_is_empty(queue));
    TEST_ASSERT_EQUAL(2, StaticQueue_size(queue));
}

void test_StaticQueue_is_empty_2() {
    TEST_MESSAGE("Case 2 --> Empty StaticQueue:");
    StaticQueue *queue = NEW_QUEUE;

    TEST_ASSERT_TRUE(StaticQueue_is_empty(queue));
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, StaticQueue_size(queue));
}

void test_StaticQueue_is_empty_3() {
    TEST_MESSAGE("Case 3 --> NULL StaticQueue:");
    StaticQueue *queue = NULL;

    TEST_ASSERT_TRUE(StaticQueue_is_empty(queue));
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, StaticQueue_size(queue));
}

void test_StaticQueue_is_full_1() {
    TEST_MESSAGE("Case 1 --> Non Full StaticQueue:");
    TYPE d1, d2;
    StaticQueue *queue = NEW_QUEUE;
    StaticQueue_enqueue(queue, &d1);
    StaticQueue_enqueue(queue, &d2);

    TEST_ASSERT_FALSE(StaticQueue_is_full(queue));
    TEST_ASSERT_EQUAL(2, StaticQueue_size(queue));
}

void test_StaticQueue_is_full_2() {
    TEST_MESSAGE("Case 2 --> Full StaticQueue:");
    TYPE d1, d2;
    StaticQueue *queue = NEW_QUEUE;
    StaticQueue_enqueue(queue, &d1);
    StaticQueue_enqueue(queue, &d1);
    StaticQueue_enqueue(queue, &d2);
    StaticQueue_enqueue(queue, &d2);
    StaticQueue_enqueue(queue, &d2);

    TEST_ASSERT_TRUE(StaticQueue_is_full(queue));
    TEST_ASSERT_EQUAL(5, StaticQueue_size(queue));
}

void test_StaticQueue_is_full_3() {
    TEST_MESSAGE("Case 3 --> Empty StaticQueue:");
    StaticQueue *queue = NEW_QUEUE;

    TEST_ASSERT_FALSE(StaticQueue_is_full(queue));
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, StaticQueue_size(queue));
}

void test_StaticQueue_is_full_4() {
    TEST_MESSAGE("Case 4 --> NULL StaticQueue:");
    StaticQueue *queue = NULL;

    TEST_ASSERT_FALSE(StaticQueue_is_full(queue));
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, StaticQueue_size(queue));
}

void test_StaticQueue_enqueue_1() {
    TEST_MESSAGE("Case 1 --> Non NULL StaticQueue and Non NULL Data:");
    TYPE d1 = 1, d2 = 2;
    StaticQueue *queue = NEW_QUEUE;

    bool enqueued = StaticQueue_enqueue(queue, &d1);
    TEST_ASSERT_TRUE(enqueued);
    TEST_ASSERT_EQUAL(d1, *((TYPE *) StaticQueue_peek(queue)));
    TEST_ASSERT_EQUAL(1, StaticQueue_size(queue));

    bool enqueued_2 = StaticQueue_enqueue(queue, &d2);
    TEST_ASSERT_TRUE(enqueued_2);
    TEST_ASSERT_EQUAL(d1, *((TYPE *) StaticQueue_peek(queue)));
    TEST_ASSERT_EQUAL(2, StaticQueue_size(queue));
}

void test_StaticQueue_enqueue_2() {
    TEST_MESSAGE("Case 2 --> NULL StaticQueue:");
    TYPE d1;
    StaticQueue *queue = NULL;

    bool enqueued = StaticQueue_enqueue(queue, &d1);
    TEST_ASSERT_FALSE(enqueued);
    TEST_ASSERT_NULL(StaticQueue_peek(queue));
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, StaticQueue_size(queue));
}

void test_StaticQueue_enqueue_3() {
    TEST_MESSAGE("Case 3 --> NULL Data:");
    StaticQueue *queue = NEW_QUEUE;

    bool enqueued = StaticQueue_enqueue(queue, NULL);
    TEST_ASSERT_FALSE(enqueued);
    TEST_ASSERT_NULL(StaticQueue_peek(queue));
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, StaticQueue_size(queue));
}

void test_StaticQueue_peek_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty StaticQueue:");
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;
    StaticQueue *queue = NEW_QUEUE;

    StaticQueue_enqueue(queue, &d1);
    TEST_ASSERT_EQUAL(d1, *((TYPE *) StaticQueue_peek(queue)));
    TEST_ASSERT_EQUAL(1, StaticQueue_size(queue));

    StaticQueue_enqueue(queue, &d2);
    StaticQueue_enqueue(queue, &d3);
    StaticQueue_enqueue(queue, &d4);
    TEST_ASSERT_EQUAL(4, StaticQueue_size(queue));
    TEST_ASSERT_EQUAL(d1, *((TYPE *) StaticQueue_peek(queue)));
}

void test_StaticQueue_peek_2() {
    TEST_MESSAGE("Case 2 --> NULL StaticQueue:");
    StaticQueue *queue = NULL;

    TEST_ASSERT_NULL(StaticQueue_peek(queue));
}

void test_StaticQueue_peek_3() {
    TEST_MESSAGE("Case 3 --> Empty StaticQueue:");
    StaticQueue *queue = NEW_QUEUE;

    TEST_ASSERT_NULL(StaticQueue_peek(queue));
}

void test_StaticQueue_dequeue_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty StaticQueue:");
    TYPE d1 = 1, d2 = 2, d3 = 3;
    StaticQueue *queue = NEW_QUEUE;
    StaticQueue_enqueue(queue, &d1);
    StaticQueue_enqueue(queue, &d2);
    StaticQueue_enqueue(queue, &d3);

    TEST_ASSERT_EQUAL(3, StaticQueue_size(queue));
    TEST_ASSERT_EQUAL(d1, *((TYPE *) StaticQueue_peek(queue)));

    bool dequeued = StaticQueue_dequeue(queue);
    TEST_ASSERT_TRUE(dequeued);
    TEST_ASSERT_EQUAL(2, StaticQueue_size(queue));
    TEST_ASSERT_EQUAL(d2, *((TYPE *) StaticQueue_peek(queue)));
}

void test_StaticQueue_dequeue_2() {
    TEST_MESSAGE("Case 2 --> NULL StaticQueue:");
    StaticQueue *queue = NEW_QUEUE;

    bool dequeued = StaticQueue_dequeue(queue);
    TEST_ASSERT_FALSE(dequeued);
}

void test_StaticQueue_dequeue_3() {
    TEST_MESSAGE("Case 3 --> Empty StaticQueue:");
    StaticQueue *queue = NEW_QUEUE;

    bool dequeued = StaticQueue_dequeue(queue);
    TEST_ASSERT_FALSE(dequeued);
}

void test_StaticQueue_size_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty StaticQueue:");
    TYPE d1, d2, d3, d4;
    StaticQueue *queue = NEW_QUEUE;

    StaticQueue_enqueue(queue, &d1);
    StaticQueue_enqueue(queue, &d2);
    StaticQueue_enqueue(queue, &d3);
    StaticQueue_enqueue(queue, &d4);
    TEST_ASSERT_EQUAL(4, StaticQueue_size(queue));

    StaticQueue_dequeue(queue);
    StaticQueue_dequeue(queue);
    TEST_ASSERT_EQUAL(2, StaticQueue_size(queue));
}

void test_StaticQueue_size_2() {
    TEST_MESSAGE("Case 2 --> NULL StaticQueue:");
    StaticQueue *queue = NULL;

    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, StaticQueue_size(queue));
}

void test_StaticQueue_size_3() {
    TEST_MESSAGE("Case 3 --> Empty StaticQueue:");
    StaticQueue *queue = NULL;

    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, StaticQueue_size(queue));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_StaticQueue_create);
    RUN_TEST(test_StaticQueue_clean_1);
    RUN_TEST(test_StaticQueue_clean_2);
    RUN_TEST(test_StaticQueue_destroy_1);
    RUN_TEST(test_StaticQueue_destroy_2);
    RUN_TEST(test_StaticQueue_is_empty_1);
    RUN_TEST(test_StaticQueue_is_empty_2);
    RUN_TEST(test_StaticQueue_is_empty_3);
    RUN_TEST(test_StaticQueue_is_full_1);
    RUN_TEST(test_StaticQueue_is_full_2);
    RUN_TEST(test_StaticQueue_is_full_3);
    RUN_TEST(test_StaticQueue_is_full_4);
    RUN_TEST(test_StaticQueue_enqueue_1);
    RUN_TEST(test_StaticQueue_enqueue_2);
    RUN_TEST(test_StaticQueue_enqueue_3);
    RUN_TEST(test_StaticQueue_peek_1);
    RUN_TEST(test_StaticQueue_peek_2);
    RUN_TEST(test_StaticQueue_peek_3);
    RUN_TEST(test_StaticQueue_dequeue_1);
    RUN_TEST(test_StaticQueue_dequeue_2);
    RUN_TEST(test_StaticQueue_dequeue_3);
    RUN_TEST(test_StaticQueue_size_1);
    RUN_TEST(test_StaticQueue_size_2);
    RUN_TEST(test_StaticQueue_size_3);
    return UNITY_END();
}
