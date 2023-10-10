#include "../../main/include/unity.h"
#include "../../main/include/dynamic_queue.h"

#define TYPE int
#define NEW_QUEUE DynamicQueue_create()

void setUp(){}

void tearDown(){}

void test_DynamicQueue_create() {
    DynamicQueue *queue = NULL;
    TEST_ASSERT_NULL(queue);
    queue = NEW_QUEUE;
    TEST_ASSERT_NOT_NULL(queue);
}

void test_DynamicQueue_clean_1() {
    TEST_MESSAGE("Case --> 1 Queue != NULL:");
    DynamicQueue *queue = NEW_QUEUE;

    bool cleaned = DynamicQueue_clean(queue);
    TEST_ASSERT_TRUE(cleaned);
}

void test_DynamicQueue_clean_2() {
    TEST_MESSAGE("Case --> 2 Queue == NULL:");
    DynamicQueue *queue = NULL;

    bool cleaned = DynamicQueue_clean(queue);
    TEST_ASSERT_FALSE(cleaned);
}

void test_DynamicQueue_destroy_1() {
    TEST_MESSAGE("Case --> 1 Queue != NULL:");
    DynamicQueue *queue = NEW_QUEUE;

    TEST_ASSERT_NOT_NULL(queue);
    bool destroyed = DynamicQueue_destroy(&queue);
    TEST_ASSERT_TRUE(destroyed);
    TEST_ASSERT_NULL(queue);
}

void test_DynamicQueue_destroy_2() {
    TEST_MESSAGE("Case --> 2 Queue == NULL:");
    DynamicQueue *queue = NULL;

    bool destroyed = DynamicQueue_destroy(&queue);
    TEST_ASSERT_FALSE(destroyed);
}

void test_DynamicQueue_is_empty_1() {
    TEST_MESSAGE("Case 1 --> Non Empty DynamicQueue:");
    TYPE d1, d2;
    DynamicQueue *queue = NEW_QUEUE;
    DynamicQueue_enqueue(queue, &d1);
    DynamicQueue_enqueue(queue, &d2);

    TEST_ASSERT_FALSE(DynamicQueue_is_empty(queue));
    TEST_ASSERT_EQUAL(2, DynamicQueue_size(queue));
}

void test_DynamicQueue_is_empty_2() {
    TEST_MESSAGE("Case 2 --> Empty DynamicQueue:");
    DynamicQueue *queue = NEW_QUEUE;

    TEST_ASSERT_TRUE(DynamicQueue_is_empty(queue));
    TEST_ASSERT_EQUAL(0, DynamicQueue_size(queue));
}

void test_DynamicQueue_is_empty_3() {
    TEST_MESSAGE("Case 3 --> NULL DynamicQueue:");
    DynamicQueue *queue = NULL;

    TEST_ASSERT_TRUE(DynamicQueue_is_empty(queue));
    TEST_ASSERT_EQUAL(0, DynamicQueue_size(queue));
}

void test_DynamicQueue_enqueue_1() {
    TEST_MESSAGE("Case 1 --> Non NULL DynamicQueue and Non NULL Data:");
    TYPE d1, d2;
    DynamicQueue *queue = NEW_QUEUE;

    bool enqueued = DynamicQueue_enqueue(queue, &d1);
    TEST_ASSERT_TRUE(enqueued);
    TEST_ASSERT_EQUAL(&d1, DynamicQueue_peek(queue));
    TEST_ASSERT_EQUAL(1, DynamicQueue_size(queue));

    bool enqueued_2 = DynamicQueue_enqueue(queue, &d2);
    TEST_ASSERT_TRUE(enqueued_2);
    TEST_ASSERT_EQUAL(&d1, DynamicQueue_peek(queue));
    TEST_ASSERT_EQUAL(2, DynamicQueue_size(queue));
}

void test_DynamicQueue_enqueue_2() {
    TEST_MESSAGE("Case 2 --> NULL DynamicQueue:");
    TYPE d1;
    DynamicQueue *queue = NULL;

    bool enqueued = DynamicQueue_enqueue(queue, &d1);
    TEST_ASSERT_FALSE(enqueued);
    TEST_ASSERT_NULL(DynamicQueue_peek(queue));
    TEST_ASSERT_EQUAL(0, DynamicQueue_size(queue));
}

void test_DynamicQueue_enqueue_3() {
    TEST_MESSAGE("Case 3 --> NULL Data:");
    DynamicQueue *queue = NEW_QUEUE;

    bool enqueued = DynamicQueue_enqueue(queue, NULL);
    TEST_ASSERT_FALSE(enqueued);
    TEST_ASSERT_NULL(DynamicQueue_peek(queue));
    TEST_ASSERT_EQUAL(0, DynamicQueue_size(queue));
}

void test_DynamicQueue_peek_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DynamicQueue:");
    TYPE d1, d2, d3, d4;
    DynamicQueue *queue = NEW_QUEUE;

    DynamicQueue_enqueue(queue, &d1);
    TEST_ASSERT_EQUAL(&d1, DynamicQueue_peek(queue));
    TEST_ASSERT_EQUAL(1, DynamicQueue_size(queue));

    DynamicQueue_enqueue(queue, &d2);
    DynamicQueue_enqueue(queue, &d3);
    DynamicQueue_enqueue(queue, &d4);
    TEST_ASSERT_EQUAL(4, DynamicQueue_size(queue));
    TEST_ASSERT_EQUAL(&d1, DynamicQueue_peek(queue));
}

void test_DynamicQueue_peek_2() {
    TEST_MESSAGE("Case 2 --> NULL DynamicQueue:");
    DynamicQueue *queue = NULL;

    TEST_ASSERT_NULL(DynamicQueue_peek(queue));
}

void test_DynamicQueue_peek_3() {
    TEST_MESSAGE("Case 3 --> Empty DynamicQueue:");
    DynamicQueue *queue = NEW_QUEUE;

    TEST_ASSERT_NULL(DynamicQueue_peek(queue));
}

void test_DynamicQueue_dequeue_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DynamicQueue:");
    TYPE d1, d2, d3;
    DynamicQueue *queue = NEW_QUEUE;
    DynamicQueue_enqueue(queue, &d1);
    DynamicQueue_enqueue(queue, &d2);
    DynamicQueue_enqueue(queue, &d3);

    TEST_ASSERT_EQUAL(3, DynamicQueue_size(queue));
    TEST_ASSERT_EQUAL(&d1, DynamicQueue_peek(queue));

    void *data = DynamicQueue_dequeue(queue);
    TEST_ASSERT_EQUAL(&d1, data);
    TEST_ASSERT_EQUAL(2, DynamicQueue_size(queue));
    TEST_ASSERT_EQUAL(&d2, DynamicQueue_peek(queue));
}

void test_DynamicQueue_dequeue_2() {
    TEST_MESSAGE("Case 2 --> NULL DynamicQueue:");
    DynamicQueue *queue = NEW_QUEUE;

    void *data = DynamicQueue_dequeue(queue);
    TEST_ASSERT_NULL(data);
}

void test_DynamicQueue_dequeue_3() {
    TEST_MESSAGE("Case 3 --> Empty DynamicQueue:");
    DynamicQueue *queue = NEW_QUEUE;

    void *data = DynamicQueue_dequeue(queue);
    TEST_ASSERT_NULL(data);
}

void test_DynamicQueue_size_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Non Empty DynamicQueue:");
    TYPE d1, d2, d3, d4;
    DynamicQueue *queue = NEW_QUEUE;

    DynamicQueue_enqueue(queue, &d1);
    DynamicQueue_enqueue(queue, &d2);
    DynamicQueue_enqueue(queue, &d3);
    DynamicQueue_enqueue(queue, &d4);
    TEST_ASSERT_EQUAL(4, DynamicQueue_size(queue));

    DynamicQueue_dequeue(queue);
    DynamicQueue_dequeue(queue);
    TEST_ASSERT_EQUAL(2, DynamicQueue_size(queue));
}

void test_DynamicQueue_size_2() {
    TEST_MESSAGE("Case 2 --> NULL DynamicQueue:");
    DynamicQueue *queue = NULL;

    TEST_ASSERT_EQUAL(0, DynamicQueue_size(queue));
}

void test_DynamicQueue_size_3() {
    TEST_MESSAGE("Case 3 --> Empty DynamicQueue:");
    DynamicQueue *queue = NULL;

    TEST_ASSERT_EQUAL(0, DynamicQueue_size(queue));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_DynamicQueue_create);
    RUN_TEST(test_DynamicQueue_clean_1);
    RUN_TEST(test_DynamicQueue_clean_2);
    RUN_TEST(test_DynamicQueue_destroy_1);
    RUN_TEST(test_DynamicQueue_destroy_2);
    RUN_TEST(test_DynamicQueue_is_empty_1);
    RUN_TEST(test_DynamicQueue_is_empty_2);
    RUN_TEST(test_DynamicQueue_is_empty_3);
    RUN_TEST(test_DynamicQueue_enqueue_1);
    RUN_TEST(test_DynamicQueue_enqueue_2);
    RUN_TEST(test_DynamicQueue_enqueue_3);
    RUN_TEST(test_DynamicQueue_peek_1);
    RUN_TEST(test_DynamicQueue_peek_2);
    RUN_TEST(test_DynamicQueue_peek_3);
    RUN_TEST(test_DynamicQueue_dequeue_1);
    RUN_TEST(test_DynamicQueue_dequeue_2);
    RUN_TEST(test_DynamicQueue_dequeue_3);
    RUN_TEST(test_DynamicQueue_size_1);
    RUN_TEST(test_DynamicQueue_size_2);
    RUN_TEST(test_DynamicQueue_size_3);
    return UNITY_END();
}
