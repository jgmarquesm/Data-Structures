#include "../../main/include/unity.h"
#include "../../main/include/static_stack.h"

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

// StaticStack_create(capacity, size_of_type)
void test_1() {
    TEST_MESSAGE("Test: StaticStack_create(capacity, size_of_type): ");
    StaticStack *ss = StaticStack_create(CAPACITY, SIZE_OF_TYPE);
    bool is_empty = StaticStack_is_empty(ss);
    TEST_ASSERT_EQUAL(1, is_empty);
    TEST_ASSERT_EQUAL(0, StaticStack_size(ss));
}

// StaticStack_clean(ss)
void test_2() {
    TEST_MESSAGE("Test: StaticStack_clean(ss): ");
    StaticStack *ss = StaticStack_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    StaticStack_push(ss, &data1);
    StaticStack_push(ss, &data2);
    StaticStack_push(ss, &data2);
    StaticStack_push(ss, &data2);
    StaticStack_push(ss, &data2);

    StaticStack_clean(ss);
    TEST_ASSERT_EQUAL(1, StaticStack_is_empty(ss));
    TEST_ASSERT_EQUAL(0, StaticStack_size(ss));
}

// StaticStack_destroy(&ss)
void test_3() {
    TEST_MESSAGE("Test: StaticStack_destroy(&ss): ");
    StaticStack *ss = StaticStack_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    StaticStack_push(ss, &data1);
    StaticStack_push(ss, &data2);
    StaticStack_push(ss, &data2);
    StaticStack_push(ss, &data2);
    StaticStack_push(ss, &data2);

    StaticStack_destroy(&ss);
    TEST_ASSERT_EQUAL(NULL, ss);
}

// StaticStack_is_empty(ss)
void test_4() {
    TEST_MESSAGE("Test: StaticStack_is_empty(ss): ");
    StaticStack *ss = StaticStack_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, StaticStack_is_empty(ss));
    TEST_ASSERT_EQUAL(0, StaticStack_size(ss));
    StaticStack_push(ss, &data1);
    StaticStack_push(ss, &data2);
    TEST_ASSERT_EQUAL(0, StaticStack_is_empty(ss));
    TEST_ASSERT_EQUAL(2, StaticStack_size(ss));
}

// StaticStack_is_full(ss)
void test_5() {
    TEST_MESSAGE("Test: StaticStack_is_full(ss): ");
    StaticStack *ss = StaticStack_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    StaticStack_push(ss, &data1);
    StaticStack_push(ss, &data2);
    TEST_ASSERT_EQUAL(0, StaticStack_is_full(ss));
    TEST_ASSERT_EQUAL(1, CAPACITY != StaticStack_size(ss));
    StaticStack_push(ss, &data1);
    StaticStack_push(ss, &data2);
    StaticStack_push(ss, &data2);
    TEST_ASSERT_EQUAL(1, StaticStack_is_full(ss));
    TEST_ASSERT_EQUAL(CAPACITY, StaticStack_size(ss));
}

// StaticStack_push(ss, data)
void test_6() {
    TEST_MESSAGE("Test: StaticStack_push(ss, data): ");
    StaticStack *ss = StaticStack_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    StaticStack_push(ss, &data1);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(StaticStack_peek(ss)));
    StaticStack_push(ss, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(StaticStack_peek(ss)));
}

// StaticStack_peek(ss)
void test_7() {
    TEST_MESSAGE("Test: StaticStack_peek(ss): ");
    StaticStack *ss = StaticStack_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    StaticStack_push(ss, &data1);
    StaticStack_push(ss, &data2);
    StaticStack_push(ss, &data1);
    StaticStack_push(ss, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(StaticStack_peek(ss)));
}

// StaticStack_pop(ss)
void test_8() {
    TEST_MESSAGE("Test: StaticStack_pop(ss): ");
    StaticStack *ss = StaticStack_create(CAPACITY, SIZE_OF_TYPE);
    int data0 = 42, data1 = 99, data2 = 55;
    StaticStack_push(ss, &data0);
    StaticStack_push(ss, &data1);
    StaticStack_push(ss, &data2);

    TEST_ASSERT_EQUAL(3, StaticStack_size(ss));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(StaticStack_peek(ss)));

    StaticStack_pop(ss);
    TEST_ASSERT_EQUAL(2, StaticStack_size(ss));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(StaticStack_peek(ss)));
}

// StaticStack_size(ss)
void test_9() {
    TEST_MESSAGE("Test: StaticStack_size(ss): ");
    StaticStack *ss = StaticStack_create(CAPACITY, SIZE_OF_TYPE);
    int data1 = 42;
    int data2 = 99;
    StaticStack_push(ss, &data1);
    StaticStack_push(ss, &data2);
    TEST_ASSERT_EQUAL(2, StaticStack_size(ss));
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
