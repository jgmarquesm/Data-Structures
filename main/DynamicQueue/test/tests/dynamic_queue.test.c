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

// DynamicQueue_create()
void test_1() {
    TEST_MESSAGE("Test: DynamicQueue_create(): ");
    DynamicQueue *queue = DynamicQueue_create();
    bool is_empty = DynamicQueue_is_empty(queue);
    TEST_ASSERT_EQUAL(1, is_empty);
    TEST_ASSERT_EQUAL(0, DynamicQueue_size(queue));
}

// DynamicQueue_clean(S)
void test_2() {
    TEST_MESSAGE("Test: DynamicQueue_clean(S): ");
    DynamicQueue *queue = DynamicQueue_create();
    int data1 = 42, data2 = 99;
    DynamicQueue_enqueue(queue, &data1);
    DynamicQueue_enqueue(queue, &data2);
    DynamicQueue_enqueue(queue, &data2);
    DynamicQueue_enqueue(queue, &data2);
    DynamicQueue_enqueue(queue, &data2);

    DynamicQueue_clean(queue);
    TEST_ASSERT_EQUAL(1, DynamicQueue_is_empty(queue));
    TEST_ASSERT_EQUAL(0, DynamicQueue_size(queue));
}

// DynamicQueue_destroy(&S)
void test_3() {
    TEST_MESSAGE("Test: DynamicQueue_destroy(&S): ");
    DynamicQueue *queue = DynamicQueue_create();
    int data1 = 42, data2 = 99;
    DynamicQueue_enqueue(queue, &data1);
    DynamicQueue_enqueue(queue, &data2);
    DynamicQueue_enqueue(queue, &data2);
    DynamicQueue_enqueue(queue, &data2);
    DynamicQueue_enqueue(queue, &data2);

    DynamicQueue_destroy(&queue);
    TEST_ASSERT_EQUAL(NULL, queue);
}

// DynamicQueue_is_empty(S)
void test_4() {
    TEST_MESSAGE("Test: DynamicQueue_is_empty(S): ");
    DynamicQueue *queue = DynamicQueue_create();
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, DynamicQueue_is_empty(queue));
    TEST_ASSERT_EQUAL(0, DynamicQueue_size(queue));
    DynamicQueue_enqueue(queue, &data1);
    DynamicQueue_enqueue(queue, &data2);
    TEST_ASSERT_EQUAL(0, DynamicQueue_is_empty(queue));
    TEST_ASSERT_EQUAL(2, DynamicQueue_size(queue));
}

// DynamicQueue_enqueue(S, data)
void test_5() {
    TEST_MESSAGE("Test: DynamicQueue_enqueue(S, data): ");
    DynamicQueue *queue = DynamicQueue_create();
    int data1 = 42, data2 = 99;
    DynamicQueue_enqueue(queue, &data1);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(DynamicQueue_peek(queue)));
    DynamicQueue_enqueue(queue, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(DynamicQueue_peek(queue)));
}

// DynamicQueue_peek(S)
void test_6() {
    TEST_MESSAGE("Test: DynamicQueue_peek(S): ");
    DynamicQueue *queue = DynamicQueue_create();
    int data1 = 42, data2 = 99, data3 = 43, data4 = 55;
    DynamicQueue_enqueue(queue, &data1);
    DynamicQueue_enqueue(queue, &data2);
    DynamicQueue_enqueue(queue, &data3);
    DynamicQueue_enqueue(queue, &data4);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(DynamicQueue_peek(queue)));
}

// DynamicQueue_dequeue(S)
void test_7() {
    TEST_MESSAGE("Test: DynamicQueue_dequeue(S): ");
    DynamicQueue *queue = DynamicQueue_create();
    int data0 = 42, data1 = 99, data2 = 55;
    DynamicQueue_enqueue(queue, &data0);
    DynamicQueue_enqueue(queue, &data1);
    DynamicQueue_enqueue(queue, &data2);

    TEST_ASSERT_EQUAL(3, DynamicQueue_size(queue));
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(DynamicQueue_peek(queue)));

    DynamicQueue_dequeue(queue);
    TEST_ASSERT_EQUAL(2, DynamicQueue_size(queue));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(DynamicQueue_peek(queue)));
}

// DynamicQueue_size(S)
void test_8() {
    TEST_MESSAGE("Test: DynamicQueue_size(S): ");
    DynamicQueue *queue = DynamicQueue_create();
    int data1 = 42;
    int data2 = 99;
    DynamicQueue_enqueue(queue, &data1);
    DynamicQueue_enqueue(queue, &data2);
    TEST_ASSERT_EQUAL(2, DynamicQueue_size(queue));
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
