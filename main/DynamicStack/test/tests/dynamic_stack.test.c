#include "../../main/include/unity.h"
#include "../../main/include/dynamic_stack.h"

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

// DynamicStack_create()
void test_1() {
    TEST_MESSAGE("Test: DynamicStack_create(): ");
    DynamicStack *ss = DynamicStack_create();
    bool is_empty = DynamicStack_is_empty(ss);
    TEST_ASSERT_EQUAL(1, is_empty);
    TEST_ASSERT_EQUAL(0, DynamicStack_size(ss));
}

// DynamicStack_clean(ss)
void test_2() {
    TEST_MESSAGE("Test: DynamicStack_clean(ss): ");
    DynamicStack *ss = DynamicStack_create();
    int data1 = 42, data2 = 99;
    DynamicStack_push(ss, &data1);
    DynamicStack_push(ss, &data2);
    DynamicStack_push(ss, &data2);
    DynamicStack_push(ss, &data2);
    DynamicStack_push(ss, &data2);

    DynamicStack_clean(ss);
    TEST_ASSERT_EQUAL(1, DynamicStack_is_empty(ss));
    TEST_ASSERT_EQUAL(0, DynamicStack_size(ss));
}

// DynamicStack_destroy(&ss)
void test_3() {
    TEST_MESSAGE("Test: DynamicStack_destroy(&ss): ");
    DynamicStack *ss = DynamicStack_create();
    int data1 = 42, data2 = 99;
    DynamicStack_push(ss, &data1);
    DynamicStack_push(ss, &data2);
    DynamicStack_push(ss, &data2);
    DynamicStack_push(ss, &data2);
    DynamicStack_push(ss, &data2);

    DynamicStack_destroy(&ss);
    TEST_ASSERT_EQUAL(NULL, ss);
}

// DynamicStack_is_empty(ss)
void test_4() {
    TEST_MESSAGE("Test: DynamicStack_is_empty(ss): ");
    DynamicStack *ss = DynamicStack_create();
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, DynamicStack_is_empty(ss));
    TEST_ASSERT_EQUAL(0, DynamicStack_size(ss));
    DynamicStack_push(ss, &data1);
    DynamicStack_push(ss, &data2);
    TEST_ASSERT_EQUAL(0, DynamicStack_is_empty(ss));
    TEST_ASSERT_EQUAL(2, DynamicStack_size(ss));
}

// DynamicStack_push(ss, data)
void test_5() {
    TEST_MESSAGE("Test: DynamicStack_push(ss, data): ");
    DynamicStack *ss = DynamicStack_create();
    int data1 = 42, data2 = 99;
    DynamicStack_push(ss, &data1);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(DynamicStack_peek(ss)));
    DynamicStack_push(ss, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(DynamicStack_peek(ss)));
}

// DynamicStack_peek(ss)
void test_6() {
    TEST_MESSAGE("Test: DynamicStack_peek(ss): ");
    DynamicStack *ss = DynamicStack_create();
    int data1 = 42, data2 = 99;
    DynamicStack_push(ss, &data1);
    DynamicStack_push(ss, &data2);
    DynamicStack_push(ss, &data1);
    DynamicStack_push(ss, &data2);
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(DynamicStack_peek(ss)));
}

// DynamicStack_pop(ss)
void test_7() {
    TEST_MESSAGE("Test: DynamicStack_pop(ss): ");
    DynamicStack *ss = DynamicStack_create();
    int data0 = 42, data1 = 99, data2 = 55;
    DynamicStack_push(ss, &data0);
    DynamicStack_push(ss, &data1);
    DynamicStack_push(ss, &data2);

    TEST_ASSERT_EQUAL(3, DynamicStack_size(ss));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(DynamicStack_peek(ss)));

    DynamicStack_pop(ss);
    TEST_ASSERT_EQUAL(2, DynamicStack_size(ss));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(DynamicStack_peek(ss)));
}

// DynamicStack_size(ss)
void test_8() {
    TEST_MESSAGE("Test: DynamicStack_size(ss): ");
    DynamicStack *ss = DynamicStack_create();
    int data1 = 42;
    int data2 = 99;
    DynamicStack_push(ss, &data1);
    DynamicStack_push(ss, &data2);
    TEST_ASSERT_EQUAL(2, DynamicStack_size(ss));
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
