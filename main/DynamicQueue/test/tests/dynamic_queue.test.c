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

// Stack_create()
void test_1() {
    TEST_MESSAGE("Test: Stack_create(): ");
    Stack *S = Stack_create();
    bool is_empty = Stack_is_empty(S);
    TEST_ASSERT_EQUAL(1, is_empty);
    TEST_ASSERT_EQUAL(0, Stack_size(S));
}

// Stack_clean(S)
void test_2() {
    TEST_MESSAGE("Test: Stack_clean(S): ");
    Stack *S = Stack_create();
    int data1 = 42, data2 = 99;
    Stack_enqueue(S, &data1);
    Stack_enqueue(S, &data2);
    Stack_enqueue(S, &data2);
    Stack_enqueue(S, &data2);
    Stack_enqueue(S, &data2);

    Stack_clean(S);
    TEST_ASSERT_EQUAL(1, Stack_is_empty(S));
    TEST_ASSERT_EQUAL(0, Stack_size(S));
}

// Stack_destroy(&S)
void test_3() {
    TEST_MESSAGE("Test: Stack_destroy(&S): ");
    Stack *S = Stack_create();
    int data1 = 42, data2 = 99;
    Stack_enqueue(S, &data1);
    Stack_enqueue(S, &data2);
    Stack_enqueue(S, &data2);
    Stack_enqueue(S, &data2);
    Stack_enqueue(S, &data2);

    Stack_destroy(&S);
    TEST_ASSERT_EQUAL(NULL, S);
}

// Stack_is_empty(S)
void test_4() {
    TEST_MESSAGE("Test: Stack_is_empty(S): ");
    Stack *S = Stack_create();
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, Stack_is_empty(S));
    TEST_ASSERT_EQUAL(0, Stack_size(S));
    Stack_enqueue(S, &data1);
    Stack_enqueue(S, &data2);
    TEST_ASSERT_EQUAL(0, Stack_is_empty(S));
    TEST_ASSERT_EQUAL(2, Stack_size(S));
}

// Stack_enqueue(S, data)
void test_5() {
    TEST_MESSAGE("Test: Stack_enqueue(S, data): ");
    Stack *S = Stack_create();
    int data1 = 42, data2 = 99;
    Stack_enqueue(S, &data1);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Stack_peek(S)));
    Stack_enqueue(S, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Stack_peek(S)));
}

// Stack_peek(S)
void test_6() {
    TEST_MESSAGE("Test: Stack_peek(S): ");
    Stack *S = Stack_create();
    int data1 = 42, data2 = 99, data3 = 43, data4 = 55;
    Stack_enqueue(S, &data1);
    Stack_enqueue(S, &data2);
    Stack_enqueue(S, &data3);
    Stack_enqueue(S, &data4);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Stack_peek(S)));
}

// Stack_dequeue(S)
void test_7() {
    TEST_MESSAGE("Test: Stack_dequeue(S): ");
    Stack *S = Stack_create();
    int data0 = 42, data1 = 99, data2 = 55;
    Stack_enqueue(S, &data0);
    Stack_enqueue(S, &data1);
    Stack_enqueue(S, &data2);

    TEST_ASSERT_EQUAL(3, Stack_size(S));
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Stack_peek(S)));

    Stack_dequeue(S);
    TEST_ASSERT_EQUAL(2, Stack_size(S));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Stack_peek(S)));
}

// Stack_size(S)
void test_8() {
    TEST_MESSAGE("Test: Stack_size(S): ");
    Stack *S = Stack_create();
    int data1 = 42;
    int data2 = 99;
    Stack_enqueue(S, &data1);
    Stack_enqueue(S, &data2);
    TEST_ASSERT_EQUAL(2, Stack_size(S));
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
