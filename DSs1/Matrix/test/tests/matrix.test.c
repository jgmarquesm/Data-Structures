#include "../../main/include/unity.h"
#include "../../main/include/matrix.h"

#define ROWS 3
#define COLS 3
#define SIZE_OF_TYPE sizeof(int)

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

void setUp(){}

void tearDown(){}

// Matrix_create(number_of_rows, number_of_cols, size_of_type)
void test_1() {
    TEST_MESSAGE("Test: Matrix_create(number_of_rows, number_of_cols, size_of_type): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    TEST_ASSERT_EQUAL(1, Matrix_is_empty(matrix));
    TEST_ASSERT_EQUAL(0, Matrix_size(matrix));
}

// Matrix_clean(matrix)
void test_2() {
    TEST_MESSAGE("Test: Matrix_clean(matrix): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);
    Matrix_insert_at(matrix, 0, 2, &data2);
    Matrix_insert_at(matrix, 1, 0, &data2);
    Matrix_insert_at(matrix, 1, 1, &data1);
    Matrix_insert_at(matrix, 1, 2, &data1);
    Matrix_insert_at(matrix, 2, 0, &data1);
    Matrix_insert_at(matrix, 2, 1, &data2);
    Matrix_insert_at(matrix, 2, 2, &data1);

    Matrix_clean(matrix);
    TEST_ASSERT_EQUAL(1, Matrix_is_empty(matrix));
    TEST_ASSERT_EQUAL(0, Matrix_size(matrix));
}

// Matrix_delete(&matrix)
void test_3() {
    TEST_MESSAGE("Test: Matrix_delete(&matrix): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);
    Matrix_insert_at(matrix, 0, 2, &data2);
    Matrix_insert_at(matrix, 1, 0, &data2);
    Matrix_insert_at(matrix, 1, 1, &data1);
    Matrix_insert_at(matrix, 1, 2, &data1);
    Matrix_insert_at(matrix, 2, 0, &data1);
    Matrix_insert_at(matrix, 2, 1, &data2);
    Matrix_insert_at(matrix, 2, 2, &data1);

    Matrix_delete(&matrix);
    TEST_ASSERT_EQUAL(NULL, matrix);
}

// Matrix_rows(matrix)
void test_4() {
    TEST_MESSAGE("Test: Matrix_rows(matrix): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    TEST_ASSERT_EQUAL(ROWS, Matrix_rows(matrix));
}

// Matrix_cols(matrix)
void test_5() {
    TEST_MESSAGE("Test: Matrix_cols(matrix): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    TEST_ASSERT_EQUAL(COLS, Matrix_cols(matrix));
}

// Matrix_size(matrix)
void test_6() {
    TEST_MESSAGE("Test: Matrix_size(matrix): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(0, Matrix_size(matrix));
    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);
    Matrix_insert_at(matrix, 0, 2, &data2);
    Matrix_insert_at(matrix, 1, 0, &data2);
    TEST_ASSERT_EQUAL(4, Matrix_size(matrix));
    Matrix_insert_at(matrix, 1, 1, &data1);
    Matrix_insert_at(matrix, 1, 2, &data1);
    Matrix_insert_at(matrix, 2, 0, &data1);
    Matrix_insert_at(matrix, 2, 1, &data2);
    Matrix_insert_at(matrix, 2, 2, &data1);
    TEST_ASSERT_EQUAL(9, Matrix_size(matrix));
}

// Matrix_is_empty(matrix)
void test_7() {
    TEST_MESSAGE("Test: Matrix_is_empty(matrix): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    TEST_ASSERT_EQUAL(1, Matrix_is_empty(matrix));
    TEST_ASSERT_EQUAL(0, Matrix_size(matrix));
    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);
    Matrix_insert_at(matrix, 0, 2, &data2);
    Matrix_insert_at(matrix, 1, 0, &data2);
    Matrix_insert_at(matrix, 1, 1, &data1);
    Matrix_insert_at(matrix, 1, 2, &data1);
    Matrix_insert_at(matrix, 2, 0, &data1);
    Matrix_insert_at(matrix, 2, 1, &data2);
    Matrix_insert_at(matrix, 2, 2, &data1);
    TEST_ASSERT_EQUAL(9, Matrix_size(matrix));
    TEST_ASSERT_EQUAL(0, Matrix_is_empty(matrix));
}

// Matrix_is_full(matrix)
void test_8() {
    TEST_MESSAGE("Test: Matrix_is_full(matrix): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);

    TEST_ASSERT_EQUAL(0, Matrix_is_full(matrix));
    TEST_ASSERT_EQUAL(1, Matrix_rows(matrix) * Matrix_cols(matrix) != Matrix_size(matrix));

    Matrix_insert_at(matrix, 0, 2, &data2);
    Matrix_insert_at(matrix, 1, 0, &data2);
    Matrix_insert_at(matrix, 1, 1, &data1);
    Matrix_insert_at(matrix, 1, 2, &data1);
    Matrix_insert_at(matrix, 2, 0, &data1);
    Matrix_insert_at(matrix, 2, 1, &data2);
    Matrix_insert_at(matrix, 2, 2, &data1);
    TEST_ASSERT_EQUAL(9, Matrix_size(matrix));
    TEST_ASSERT_EQUAL(1, Matrix_is_full(matrix));
    TEST_ASSERT_EQUAL(Matrix_rows(matrix) * Matrix_cols(matrix), Matrix_size(matrix));
}

// Matrix_insert_at(matrix, row, col, data)
void test_9() {
    TEST_MESSAGE("Test: Matrix_insert_at(matrix, row, col, data): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99, data0 = 357, data3 = -761;
    Matrix_insert_at(matrix, 0, 0, &data0);
    Matrix_insert_at(matrix, 0, 1, &data1);
    Matrix_insert_at(matrix, 0, 2, &data2);

    TEST_ASSERT_EQUAL(3, Matrix_size(matrix));
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Matrix_get_at(matrix, 0, 0)));

    Matrix_insert_at(matrix, 1, 0, &data3);
    TEST_ASSERT_EQUAL(4, Matrix_size(matrix));
    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Matrix_get_at(matrix, 1, 0)));
}

// Matrix_set(matrix, row, col, data)
void test_10() {
    TEST_MESSAGE("Test: Matrix_set(matrix, row, col, data): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99, data0 = 357, data3 = -761;
    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);
    Matrix_insert_at(matrix, 0, 2, &data3);

    TEST_ASSERT_EQUAL(3, Matrix_size(matrix));
    TEST_ASSERT_EQUAL(_convert_to_int(&data3), _convert_to_int(Matrix_get_at(matrix, 0, 2)));

    Matrix_set(matrix, 0, 2, &data0);
    TEST_ASSERT_EQUAL(3, Matrix_size(matrix));
    TEST_ASSERT_EQUAL(_convert_to_int(&data0), _convert_to_int(Matrix_get_at(matrix, 0, 2)));
}

// Matrix_get_at(matrix, row, col)
void test_11() {
    TEST_MESSAGE("Test: Matrix_get_at(matrix, row, col): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);
    Matrix_insert_at(matrix, 0, 2, &data1);
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Matrix_get_at(matrix, 0, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data2), _convert_to_int(Matrix_get_at(matrix, 0, 1)));
    TEST_ASSERT_EQUAL(_convert_to_int(&data1), _convert_to_int(Matrix_get_at(matrix, 0, 2)));
}

// Matrix_clone(matrix)
void test_12() {
    TEST_MESSAGE("Test: Matrix_clone(matrix): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);
    Matrix_insert_at(matrix, 0, 2, &data3);
    Matrix_insert_at(matrix, 1, 0, &data1);
    Matrix_insert_at(matrix, 1, 1, &data2);
    Matrix_insert_at(matrix, 1, 2, &data3);
    Matrix_insert_at(matrix, 2, 0, &data1);
    Matrix_insert_at(matrix, 2, 1, &data2);
    Matrix_insert_at(matrix, 2, 2, &data4);

    Matrix *clone = Matrix_clone(matrix);

    TEST_ASSERT_EQUAL(Matrix_size(clone), Matrix_size(matrix));
    TEST_ASSERT_EQUAL(_convert_to_int(Matrix_get_at(clone, 0, 0)), _convert_to_int(Matrix_get_at(matrix, 0, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(Matrix_get_at(clone, 1, 1)), _convert_to_int(Matrix_get_at(matrix, 1, 1)));
    TEST_ASSERT_EQUAL(_convert_to_int(Matrix_get_at(clone, 2, 2)), _convert_to_int(Matrix_get_at(matrix, 2, 2)));
}

// Matrix_sub(matrix, initial_index, final_index)
void test_13() {
    TEST_MESSAGE("Test: Matrix_sub(matrix, initial_index, final_index): ");
    long initial_row = 1;
    long initial_col = 1;
    long final_row = 2;
    long final_col = 2;
    long sub_max_size = (final_row - initial_row + 1) * (final_col - initial_col + 1);
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;

    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);
    Matrix_insert_at(matrix, 0, 2, &data3);
    Matrix_insert_at(matrix, 1, 0, &data1);
    Matrix_insert_at(matrix, 1, 1, &data2);
    Matrix_insert_at(matrix, 1, 2, &data3);
    Matrix_insert_at(matrix, 2, 0, &data1);
    Matrix_insert_at(matrix, 2, 1, &data2);
    Matrix_insert_at(matrix, 2, 2, &data4);

    Matrix *sub_matrix = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    TEST_ASSERT_EQUAL(_convert_to_int(Matrix_get_at(matrix, initial_row, initial_col)), _convert_to_int(Matrix_get_at(sub_matrix, 0, 0)));
    TEST_ASSERT_EQUAL(_convert_to_int(Matrix_get_at(matrix, final_row, final_col)), _convert_to_int(Matrix_get_at(sub_matrix, 1, 1)));
    TEST_ASSERT_EQUAL(Matrix_size(sub_matrix), sub_max_size);
}

// Matrix_contains(matrix, data, _compare_int)
void test_14() {
    TEST_MESSAGE("Test: Matrix_contains(matrix, data, _compare_int): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99, data3 = 55;
    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);
    Matrix_insert_at(matrix, 0, 2, &data1);
    Matrix_insert_at(matrix, 1, 0, &data1);
    Matrix_insert_at(matrix, 1, 1, &data2);
    Matrix_insert_at(matrix, 1, 2, &data1);
    Matrix_insert_at(matrix, 2, 0, &data1);
    Matrix_insert_at(matrix, 2, 1, &data2);
    Matrix_insert_at(matrix, 2, 2, &data1);
    TEST_ASSERT_EQUAL(1, Matrix_contains(matrix, &data2, _compare_int));
    TEST_ASSERT_EQUAL(0, Matrix_contains(matrix, &data3, _compare_int));
}

// Matrix_count(matrix, data, _compare_int)
void test_15() {
    TEST_MESSAGE("Test: Matrix_count(matrix, data, _compare_int): ");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99;
    Matrix_insert_at(matrix, 0, 0, &data1);
    Matrix_insert_at(matrix, 0, 1, &data2);
    Matrix_insert_at(matrix, 0, 2, &data2);
    Matrix_insert_at(matrix, 1, 0, &data2);
    Matrix_insert_at(matrix, 1, 1, &data2);
    Matrix_insert_at(matrix, 1, 2, &data2);
    Matrix_insert_at(matrix, 2, 0, &data2);
    Matrix_insert_at(matrix, 2, 1, &data2);
    Matrix_insert_at(matrix, 2, 2, &data2);

    TEST_ASSERT_EQUAL(8, Matrix_count(matrix, &data2, _compare_int));
}

// Matrix_is_equals(matrix1, matrix2, _compare_func)
void test_16() {
    TEST_MESSAGE("Test: Matrix_is_equals(matrix1, matrix2, _compare_func): ");
    Matrix *matrix1 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    Matrix *matrix2 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE);
    Matrix *matrix3 = Matrix_create(ROWS-1, COLS-1, SIZE_OF_TYPE);
    int data1 = 42, data2 = 99, data3 = -1, data4 = 10;
    int data5 = 42, data6 = 99, data7 = -1, data8 = 10;

    Matrix_insert_at(matrix1, 0, 0, &data1);
    Matrix_insert_at(matrix1, 0, 1, &data2);
    Matrix_insert_at(matrix1, 0, 2, &data3);
    Matrix_insert_at(matrix1, 1, 0, &data4);
    Matrix_insert_at(matrix1, 1, 1, &data1);
    Matrix_insert_at(matrix1, 1, 2, &data2);
    Matrix_insert_at(matrix1, 2, 0, &data3);
    Matrix_insert_at(matrix1, 2, 1, &data4);
    Matrix_insert_at(matrix1, 2, 2, &data5);

    Matrix_insert_at(matrix2, 0, 0, &data5);
    Matrix_insert_at(matrix2, 0, 1, &data6);
    Matrix_insert_at(matrix2, 0, 2, &data7);
    Matrix_insert_at(matrix2, 1, 0, &data8);
    Matrix_insert_at(matrix2, 1, 1, &data5);
    Matrix_insert_at(matrix2, 1, 2, &data6);
    Matrix_insert_at(matrix2, 2, 0, &data7);
    Matrix_insert_at(matrix2, 2, 1, &data8);
    Matrix_insert_at(matrix2, 2, 2, &data1);

    Matrix_insert_at(matrix3, 0, 0, &data2);
    Matrix_insert_at(matrix3, 0, 1, &data3);
    Matrix_insert_at(matrix3, 1, 0, &data4);
    Matrix_insert_at(matrix3, 1, 1, &data5);

    TEST_ASSERT_EQUAL(1, Matrix_is_equals(matrix1, matrix2, _compare_int));
    TEST_ASSERT_EQUAL(0, Matrix_is_equals(matrix1, matrix3, _compare_int));
    TEST_ASSERT_EQUAL(0, Matrix_is_equals(matrix2, matrix3, _compare_int));
    TEST_ASSERT_EQUAL(1, Matrix_is_equals(matrix3, matrix3, _compare_int));
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
    RUN_TEST(test_10);
    RUN_TEST(test_11);
    RUN_TEST(test_12);
    RUN_TEST(test_13);
    RUN_TEST(test_14);
    RUN_TEST(test_15);
    RUN_TEST(test_16);
    return UNITY_END();
}

