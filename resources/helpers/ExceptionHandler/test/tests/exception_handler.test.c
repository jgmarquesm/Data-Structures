#include "../../main/include/unity.h"
#include "../../main/include/exception_handler.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define FUNCTION "std_function"
#define FIELD "std_field"
#define NOT_NULL ((void *) 1)
#define THROWS true
#define NOT_THROWS false
#define NOT_THROWS_MSG ""
#define NEGATIVE_THROWS_MSG "\nERROR: on function 'std_function'.\nERROR MESSAGE: std_field must be positive.\n"
#define NULL_THROWS_MSG "\nERROR: on function 'std_function'.\nERROR MESSAGE: std_field is NULL.\n"
#define EMPTY_THROWS_MSG "\nERROR: on function 'std_function'.\nERROR MESSAGE: std_field is empty.\n"
#define FULL_THROWS_MSG "\nERROR: on function 'std_function'.\nERROR MESSAGE: std_field is full.\n"
#define NOT_SORTED_THROWS_MSG "\nERROR: on function 'std_function'.\nERROR MESSAGE: std_field is not sorted.\n"
#define OUT_OF_BOUNDS_THROWS_MSG "\nERROR: on function 'std_function'.\nERROR MESSAGE: std_field is Out Of Bounds.\n"
#define VALUE_NEGATIVE_1 -1
#define VALUE_0 0
#define VALUE_1 1
#define MAX_INDEX 2
#define INDEX_FIVE 5
#define INCLUDES_ZERO true
#define NOT_INCLUDES_ZERO false

bool MOCK_is_empty_or_is_full_or_is_sorted(void *data) {
    return data == NULL;
}

void setUp(){}

void tearDown(){}

void test_ExceptionHandler_is_non_positive_1() {
    TEST_MESSAGE("Case 1 --> value = -1, includesZero = false:");
    ExceptionResponse *er = ExceptionHandler_is_non_positive(FUNCTION, FIELD, VALUE_NEGATIVE_1, NOT_INCLUDES_ZERO, __SUPPRESS_PRINT_ERROR__);
    int message_comparison = strcmp(NEGATIVE_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_non_positive_2() {
    TEST_MESSAGE("Case 2 --> value = -1, includesZero = true:");
    ExceptionResponse *er = ExceptionHandler_is_non_positive(FUNCTION, FIELD, VALUE_NEGATIVE_1, INCLUDES_ZERO, __SUPPRESS_PRINT_ERROR__);
    int message_comparison = strcmp(NEGATIVE_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_non_positive_3() {
    TEST_MESSAGE("Case 3 --> value =  0, includesZero = false:");
    ExceptionResponse *er = ExceptionHandler_is_non_positive(FUNCTION, FIELD, VALUE_0, NOT_INCLUDES_ZERO, __SUPPRESS_PRINT_ERROR__);
    int message_comparison = strcmp(NEGATIVE_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_non_positive_4() {
    TEST_MESSAGE("Case 4 --> value =  0, includesZero = true:");
    ExceptionResponse *er = ExceptionHandler_is_non_positive(FUNCTION, FIELD, VALUE_0, INCLUDES_ZERO);
    int message_comparison = strcmp(NOT_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(NOT_THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_non_positive_5() {
    TEST_MESSAGE("Case 5 --> value =  1, includesZero = false:");
    ExceptionResponse *er = ExceptionHandler_is_non_positive(FUNCTION, FIELD, VALUE_1, NOT_INCLUDES_ZERO);
    int message_comparison = strcmp(NOT_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(NOT_THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_non_positive_6() {
    TEST_MESSAGE("Case 6 --> value =  1, includesZero = true:");
    ExceptionResponse *er = ExceptionHandler_is_non_positive(FUNCTION, FIELD, VALUE_1, INCLUDES_ZERO);
    int message_comparison = strcmp(NOT_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(NOT_THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_null_1() {
    TEST_MESSAGE("Case 1 --> value = NULL:");
    ExceptionResponse *er = ExceptionHandler_is_null(FUNCTION, FIELD, NULL, __SUPPRESS_PRINT_ERROR__);
    int message_comparison = strcmp(NULL_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_null_2() {
    TEST_MESSAGE("Case 2 --> value = NOT_NULL:");
    ExceptionResponse *er = ExceptionHandler_is_null(FUNCTION, FIELD, NOT_NULL);
    int message_comparison = strcmp(NOT_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(NOT_THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_empty_1() {
    TEST_MESSAGE("Case 1 --> EMPTY:");
    ExceptionResponse *er = ExceptionHandler_is_empty(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__);
    int message_comparison = strcmp(EMPTY_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_empty_2() {
    TEST_MESSAGE("Case 2 --> NOT_EMPTY:");
    ExceptionResponse *er = ExceptionHandler_is_empty(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted);
    int message_comparison = strcmp(NOT_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(NOT_THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_full_1() {
    TEST_MESSAGE("Case 1 --> FULL:");
    ExceptionResponse *er = ExceptionHandler_is_full(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__);
    int message_comparison = strcmp(FULL_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_full_2() {
    TEST_MESSAGE("Case 2 --> NOT_FULL:");
    ExceptionResponse *er = ExceptionHandler_is_full(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted);
    int message_comparison = strcmp(NOT_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(NOT_THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_not_sorted_1() {
    TEST_MESSAGE("Case 1 --> FULL:");
    ExceptionResponse *er = ExceptionHandler_is_not_sorted(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__);
    int message_comparison = strcmp(NOT_SORTED_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_not_sorted_2() {
    TEST_MESSAGE("Case 2 --> NOT_FULL:");
    ExceptionResponse *er = ExceptionHandler_is_not_sorted(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted);
    int message_comparison = strcmp(NOT_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(NOT_THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_out_of_bounds_1() {
    TEST_MESSAGE("Case 1 --> Negative index:");
    ExceptionResponse *er = ExceptionHandler_is_out_of_bounds(FUNCTION, FIELD, VALUE_NEGATIVE_1, MAX_INDEX, __SUPPRESS_PRINT_ERROR__);
    int message_comparison = strcmp(OUT_OF_BOUNDS_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_out_of_bounds_2() {
    TEST_MESSAGE("Case 2 --> Valid index:");
    ExceptionResponse *er = ExceptionHandler_is_out_of_bounds(FUNCTION, FIELD, VALUE_1, MAX_INDEX);
    int message_comparison = strcmp(NOT_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(NOT_THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_ExceptionHandler_is_out_of_bounds_3() {
    TEST_MESSAGE("Case 3 --> Index higher than max index allowed:");
    ExceptionResponse *er = ExceptionHandler_is_out_of_bounds(FUNCTION, FIELD, INDEX_FIVE, MAX_INDEX, __SUPPRESS_PRINT_ERROR__);
    int message_comparison = strcmp(OUT_OF_BOUNDS_THROWS_MSG, er->error_message);
    TEST_ASSERT_EQUAL(THROWS, er->throws);
    TEST_ASSERT_EQUAL(0, message_comparison);
}

void test_anyThrows_1_ExceptionHandler_1() {
    TEST_MESSAGE("Case 1 --> argc = 1, { ExceptionHandler->throws = false }:");
    bool any_throws = anyThrows(1, ExceptionHandler_is_empty(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted));
    TEST_ASSERT_EQUAL(NOT_THROWS, any_throws);
}

void test_anyThrows_1_ExceptionHandler_2() {
    TEST_MESSAGE("Case 2 --> argc = 1, { ExceptionHandler->throws = true }:");
    bool any_throws = anyThrows(1, ExceptionHandler_is_empty(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__));
    TEST_ASSERT_EQUAL(THROWS, any_throws);
}

void test_anyThrows_2_ExceptionHandlers_1() {
    ExceptionResponse *er_not_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted);

    TEST_MESSAGE("Case 1 --> argc = 2, { ExceptionHandler->throws = false, ExceptionHandler->throws = false }:");
    bool any_throws = anyThrows(2, er_not_throws, er_not_throws);
    TEST_ASSERT_EQUAL(NOT_THROWS, any_throws);
}

void test_anyThrows_2_ExceptionHandlers_2() {
    ExceptionResponse *er_not_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted);
    ExceptionResponse *er_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__);

    TEST_MESSAGE("Case 2 --> argc = 2, { ExceptionHandler->throws = true, ExceptionHandler->throws = false }:");
    bool any_throws = anyThrows(2, er_throws, er_not_throws);
    TEST_ASSERT_EQUAL(THROWS, any_throws);
}

void test_anyThrows_2_ExceptionHandlers_3() {
    ExceptionResponse *er_not_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted);
    ExceptionResponse *er_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__);

    TEST_MESSAGE("Case 3 --> argc = 2, { ExceptionHandler->throws = false, ExceptionHandler->throws = true }:");
    bool any_throws = anyThrows(2, er_not_throws, er_throws);
    TEST_ASSERT_EQUAL(THROWS, any_throws);
}

void test_anyThrows_2_ExceptionHandlers_4() {
    ExceptionResponse *er_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__);

    TEST_MESSAGE("Case 4 --> argc = 2, { ExceptionHandler->throws = true, ExceptionHandler->throws = true }:");
    bool any_throws = anyThrows(2, er_throws, er_throws);
    TEST_ASSERT_EQUAL(THROWS, any_throws);
}

void test_anyThrows_3_ExceptionHandlers_1() {
    ExceptionResponse *er_not_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted);

    TEST_MESSAGE("Case 1 --> argc = 3, { ExceptionHandler->throws = false, ExceptionHandler->throws = false, ExceptionHandler->throws = false }:");
    bool any_throws = anyThrows(3, er_not_throws, er_not_throws, er_not_throws);
    TEST_ASSERT_EQUAL(NOT_THROWS, any_throws);
}

void test_anyThrows_3_ExceptionHandlers_2() {
    ExceptionResponse *er_not_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted);
    ExceptionResponse *er_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__);

    TEST_MESSAGE("Case 2 --> argc = 3, { ExceptionHandler->throws = true, ExceptionHandler->throws = false, ExceptionHandler->throws = false }:");
    bool any_throws = anyThrows(3, er_throws, er_not_throws, er_not_throws);
    TEST_ASSERT_EQUAL(THROWS, any_throws);
}

void test_anyThrows_3_ExceptionHandlers_3() {
    ExceptionResponse *er_not_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted);
    ExceptionResponse *er_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__);

    TEST_MESSAGE("Case 3 --> argc = 3, { ExceptionHandler->throws = false, ExceptionHandler->throws = true, ExceptionHandler->throws = false }:");
    bool any_throws = anyThrows(3, er_not_throws, er_throws, er_not_throws);
    TEST_ASSERT_EQUAL(THROWS, any_throws);
}

void test_anyThrows_3_ExceptionHandlers_4() {
    ExceptionResponse *er_not_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NOT_NULL, MOCK_is_empty_or_is_full_or_is_sorted);
    ExceptionResponse *er_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__);

    TEST_MESSAGE("Case 4 --> argc = 3, { ExceptionHandler->throws = false, ExceptionHandler->throws = false, ExceptionHandler->throws = true }:");
    bool any_throws = anyThrows(3, er_not_throws, er_throws, er_throws);
    TEST_ASSERT_EQUAL(THROWS, any_throws);
}

void test_anyThrows_3_ExceptionHandlers_5() {
    ExceptionResponse *er_throws = ExceptionHandler_is_empty(FUNCTION, FIELD, NULL, MOCK_is_empty_or_is_full_or_is_sorted, __SUPPRESS_PRINT_ERROR__);

    TEST_MESSAGE("Case 5 --> argc = 3, { ExceptionHandler->throws = true, ExceptionHandler->throws = true, ExceptionHandler->throws = true }:");
    bool any_throws = anyThrows(3, er_throws, er_throws, er_throws);
    TEST_ASSERT_EQUAL(THROWS, any_throws);
}


int main() {
    UNITY_BEGIN();
    RUN_TEST(test_ExceptionHandler_is_non_positive_1);
    RUN_TEST(test_ExceptionHandler_is_non_positive_2);
    RUN_TEST(test_ExceptionHandler_is_non_positive_3);
    RUN_TEST(test_ExceptionHandler_is_non_positive_4);
    RUN_TEST(test_ExceptionHandler_is_non_positive_5);
    RUN_TEST(test_ExceptionHandler_is_non_positive_6);
    RUN_TEST(test_ExceptionHandler_is_null_1);
    RUN_TEST(test_ExceptionHandler_is_null_2);
    RUN_TEST(test_ExceptionHandler_is_empty_1);
    RUN_TEST(test_ExceptionHandler_is_empty_2);
    RUN_TEST(test_ExceptionHandler_is_full_1);
    RUN_TEST(test_ExceptionHandler_is_full_2);
    RUN_TEST(test_ExceptionHandler_is_not_sorted_1);
    RUN_TEST(test_ExceptionHandler_is_not_sorted_2);
    RUN_TEST(test_ExceptionHandler_is_out_of_bounds_1);
    RUN_TEST(test_ExceptionHandler_is_out_of_bounds_2);
    RUN_TEST(test_ExceptionHandler_is_out_of_bounds_3);
    RUN_TEST(test_anyThrows_1_ExceptionHandler_1);
    RUN_TEST(test_anyThrows_1_ExceptionHandler_2);
    RUN_TEST(test_anyThrows_2_ExceptionHandlers_1);
    RUN_TEST(test_anyThrows_2_ExceptionHandlers_2);
    RUN_TEST(test_anyThrows_2_ExceptionHandlers_3);
    RUN_TEST(test_anyThrows_2_ExceptionHandlers_4);
    RUN_TEST(test_anyThrows_3_ExceptionHandlers_1);
    RUN_TEST(test_anyThrows_3_ExceptionHandlers_2);
    RUN_TEST(test_anyThrows_3_ExceptionHandlers_3);
    RUN_TEST(test_anyThrows_3_ExceptionHandlers_4);
    RUN_TEST(test_anyThrows_3_ExceptionHandlers_5);
    return UNITY_END();
}

