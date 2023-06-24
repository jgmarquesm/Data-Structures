#include "../../main/include/unity.h"
#include "../../main/include/static_queue.h"

#define CAPACITY 5
#define SIZE_OF_TYPE sizeof(int)

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

// StaticQueue_create(capacity, size_of_type)
void test_1() {
    TEST_MESSAGE("Test: StaticQueue_create(capacity, size_of_type): ");
    StaticQueue *SQ = StaticQueue_create(CAPACITY, SIZE_OF_TYPE);
    bool is_empty = StaticQueue_is_empty(SQ);
    TEST_ASSERT_EQUAL(1, is_empty);
    TEST_ASSERT_EQUAL(0, StaticQueue_size(SQ));
}

// StaticQueue_clean(SQ)
void test_2() {
    TEST_MESSAGE("Test: StaticQueue_clean(SQ): ");
    StaticQueue *SQ = StaticQueue_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    StaticQueue_enqueue(SQ, &data1);
    StaticQueue_enqueue(SQ, &data2);
    StaticQueue_enqueue(SQ, &data2);
    StaticQueue_enqueue(SQ, &data2);
    StaticQueue_enqueue(SQ, &data2);

    StaticQueue_clean(SQ);
    TEST_ASSERT_EQUAL(1, StaticQueue_is_empty(SQ));
    TEST_ASSERT_EQUAL(0, StaticQueue_size(SQ));
}

// StaticQueue_destroy(&SQ)
void test_3() {
    TEST_MESSAGE("Test: StaticQueue_destroy(&SQ): ");
    StaticQueue *SQ = StaticQueue_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    StaticQueue_enqueue(SQ, &data1);
    StaticQueue_enqueue(SQ, &data2);
    StaticQueue_enqueue(SQ, &data2);
    StaticQueue_enqueue(SQ, &data2);
    StaticQueue_enqueue(SQ, &data2);

    StaticQueue_destroy(&SQ);
    TEST_ASSERT_EQUAL(NULL, SQ);
}

// StaticQueue_is_empty(SQ)
void test_4() {
    TEST_MESSAGE("Test: StaticQueue_is_empty(SQ): ");
    StaticQueue *SQ = StaticQueue_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, StaticQueue_is_empty(SQ));
    TEST_ASSERT_EQUAL(0, StaticQueue_size(SQ));
    StaticQueue_enqueue(SQ, &data1);
    StaticQueue_enqueue(SQ, &data2);
    TEST_ASSERT_EQUAL(0, StaticQueue_is_empty(SQ));
    TEST_ASSERT_EQUAL(2, StaticQueue_size(SQ));
}

// StaticQueue_is_full(SQ)
void test_5() {
    TEST_MESSAGE("Test: StaticQueue_is_full(SQ): ");
    StaticQueue *SQ = StaticQueue_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    StaticQueue_enqueue(SQ, &data1);
    StaticQueue_enqueue(SQ, &data2);
    TEST_ASSERT_EQUAL(0, StaticQueue_is_full(SQ));
    TEST_ASSERT_EQUAL(1, CAPACITY != StaticQueue_size(SQ));
    StaticQueue_enqueue(SQ, &data1);
    StaticQueue_enqueue(SQ, &data2);
    StaticQueue_enqueue(SQ, &data2);
    TEST_ASSERT_EQUAL(1, StaticQueue_is_full(SQ));
    TEST_ASSERT_EQUAL(CAPACITY, StaticQueue_size(SQ));
}

// StaticQueue_enqueue(SQ, data)
void test_6() {
    TEST_MESSAGE("Test: StaticQueue_enqueue(SQ, data): ");
    StaticQueue *SQ = StaticQueue_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    StaticQueue_enqueue(SQ, &data1);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(StaticQueue_peek(SQ)));
    StaticQueue_enqueue(SQ, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(StaticQueue_peek(SQ)));
}

// StaticQueue_peek(SQ)
void test_7() {
    TEST_MESSAGE("Test: StaticQueue_peek(SQ): ");
    StaticQueue *SQ = StaticQueue_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99, data3 = 43, data4 = 100;
    StaticQueue_enqueue(SQ, &data1);
    StaticQueue_enqueue(SQ, &data2);
    StaticQueue_enqueue(SQ, &data3);
    StaticQueue_enqueue(SQ, &data4);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(StaticQueue_peek(SQ)));
}

// StaticQueue_dequeue(SQ)
void test_8() {
    TEST_MESSAGE("Test: StaticQueue_dequeue(SQ): ");
    StaticQueue *SQ = StaticQueue_create(CAPACITY, SIZE_OF_TYPE);
    int data0 = 42, data1 = 99, data2 = 55;
    StaticQueue_enqueue(SQ, &data0);
    StaticQueue_enqueue(SQ, &data1);
    StaticQueue_enqueue(SQ, &data2);

    TEST_ASSERT_EQUAL(3, StaticQueue_size(SQ));
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(StaticQueue_peek(SQ)));

    StaticQueue_dequeue(SQ);
    TEST_ASSERT_EQUAL(2, StaticQueue_size(SQ));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(StaticQueue_peek(SQ)));
}

// StaticQueue_size(SQ)
void test_9() {
    TEST_MESSAGE("Test: StaticQueue_size(SQ): ");
    StaticQueue *SQ = StaticQueue_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42;
    int data2 = 99;
    StaticQueue_enqueue(SQ, &data1);
    StaticQueue_enqueue(SQ, &data2);
    TEST_ASSERT_EQUAL(2, StaticQueue_size(SQ));
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
    RUN_TEST(test_9);
    return UNITY_END();
}
