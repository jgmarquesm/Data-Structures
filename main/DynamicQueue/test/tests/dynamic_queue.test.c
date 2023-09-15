#include "../../main/include/unity.h"
#include "../../main/include/dynamic_queue.h"

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

// Queue_create()
void test_1() {
    TEST_MESSAGE("Test: Queue_create(): ");
    Queue *queue = Queue_create();
    bool is_empty = Queue_is_empty(queue);
    TEST_ASSERT_EQUAL(1, is_empty);
    TEST_ASSERT_EQUAL(0, Queue_size(queue));
}

// Queue_clean(S)
void test_2() {
    TEST_MESSAGE("Test: Queue_clean(S): ");
    Queue *queue = Queue_create();
    int data1 = 42, data2 = 99;
    Queue_enqueue(queue, &data1);
    Queue_enqueue(queue, &data2);
    Queue_enqueue(queue, &data2);
    Queue_enqueue(queue, &data2);
    Queue_enqueue(queue, &data2);

    Queue_clean(queue);
    TEST_ASSERT_EQUAL(1, Queue_is_empty(queue));
    TEST_ASSERT_EQUAL(0, Queue_size(queue));
}

// Queue_destroy(&S)
void test_3() {
    TEST_MESSAGE("Test: Queue_destroy(&S): ");
    Queue *queue = Queue_create();
    int data1 = 42, data2 = 99;
    Queue_enqueue(queue, &data1);
    Queue_enqueue(queue, &data2);
    Queue_enqueue(queue, &data2);
    Queue_enqueue(queue, &data2);
    Queue_enqueue(queue, &data2);

    Queue_destroy(&queue);
    TEST_ASSERT_EQUAL(NULL, queue);
}

// Queue_is_empty(S)
void test_4() {
    TEST_MESSAGE("Test: Queue_is_empty(S): ");
    Queue *queue = Queue_create();
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, Queue_is_empty(queue));
    TEST_ASSERT_EQUAL(0, Queue_size(queue));
    Queue_enqueue(queue, &data1);
    Queue_enqueue(queue, &data2);
    TEST_ASSERT_EQUAL(0, Queue_is_empty(queue));
    TEST_ASSERT_EQUAL(2, Queue_size(queue));
}

// Queue_enqueue(S, data)
void test_5() {
    TEST_MESSAGE("Test: Queue_enqueue(S, data): ");
    Queue *queue = Queue_create();
    int data1 = 42, data2 = 99;
    Queue_enqueue(queue, &data1);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Queue_peek(queue)));
    Queue_enqueue(queue, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Queue_peek(queue)));
}

// Queue_peek(S)
void test_6() {
    TEST_MESSAGE("Test: Queue_peek(S): ");
    Queue *queue = Queue_create();
    int data1 = 42, data2 = 99, data3 = 43, data4 = 55;
    Queue_enqueue(queue, &data1);
    Queue_enqueue(queue, &data2);
    Queue_enqueue(queue, &data3);
    Queue_enqueue(queue, &data4);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Queue_peek(queue)));
}

// Queue_dequeue(S)
void test_7() {
    TEST_MESSAGE("Test: Queue_dequeue(S): ");
    Queue *queue = Queue_create();
    int data0 = 42, data1 = 99, data2 = 55;
    Queue_enqueue(queue, &data0);
    Queue_enqueue(queue, &data1);
    Queue_enqueue(queue, &data2);

    TEST_ASSERT_EQUAL(3, Queue_size(queue));
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Queue_peek(queue)));

    Queue_dequeue(queue);
    TEST_ASSERT_EQUAL(2, Queue_size(queue));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Queue_peek(queue)));
}

// Queue_size(S)
void test_8() {
    TEST_MESSAGE("Test: Queue_size(S): ");
    Queue *queue = Queue_create();
    int data1 = 42;
    int data2 = 99;
    Queue_enqueue(queue, &data1);
    Queue_enqueue(queue, &data2);
    TEST_ASSERT_EQUAL(2, Queue_size(queue));
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
    return UNITY_END();
}
