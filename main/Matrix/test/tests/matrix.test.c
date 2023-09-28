#include "../../main/include/unity.h"
#include "../../main/include/matrix.h"

#define TYPE int
#define ROWS 3
#define COLS 3
#define SIZE_OF_TYPE sizeof(TYPE)
#define default_value 0

TYPE _convert_to_TYPE(void *data){
    return *((TYPE *)data);
}

int _compare_TYPE(void *data1, void *data2){
    TYPE d1 = _convert_to_TYPE(data1), d2 = _convert_to_TYPE(data2);
    return d2 - d1;
}

void _verify_Matrix_values(TYPE data, Matrix *matrix) {
    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            TEST_ASSERT_EQUAL(data, *((TYPE *) Matrix_get_at(matrix, i, j)));
        }
    }
}

void _verify_Matrix_values_ptr(void* data, Matrix *matrix) {
    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            TEST_ASSERT_EQUAL(data, Matrix_get_at(matrix, i, j));
        }
    }
}

void setUp(){}

void tearDown(){}

void test_Matrix_create_1() {
    TEST_MESSAGE("Case 1 --> rows = 3, cols = 3 and &default_data != NULL:");
    TYPE default_data = default_data;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    TEST_ASSERT_NOT_NULL(matrix);
    _verify_Matrix_values(default_data, matrix);
}

void test_Matrix_create_2() {
    TEST_MESSAGE("Case 2 --> rows = -3, cols = 3 and &default_data != NULL:");
    TYPE default_data = default_data;
    Matrix *matrix = Matrix_create(-ROWS, COLS, SIZE_OF_TYPE, &default_data);

    TEST_ASSERT_NULL(matrix);
}

void test_Matrix_create_3() {
    TEST_MESSAGE("Case 3 --> rows = 3, cols = -3 and &default_data != NULL:");
    TYPE default_data = default_data;
    Matrix *matrix = Matrix_create(ROWS, -COLS, SIZE_OF_TYPE, &default_data);

    TEST_ASSERT_NULL(matrix);
}

void test_Matrix_create_4() {
    TEST_MESSAGE("Case 4 --> rows = 3, cols = 3 and &default_data = NULL:");
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, NULL);

    TEST_ASSERT_NULL(matrix);
}

void test_Matrix_clean_1() {
    TEST_MESSAGE("Case 1 --> Matrix != NULL:");
    TYPE default_data = default_value, new_value = 1;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            Matrix_set_at(matrix, i, j, &new_value);
        }
    }
    _verify_Matrix_values(new_value, matrix);

    bool cleaned = Matrix_clean(matrix);
    TEST_ASSERT_EQUAL(true, cleaned);
    _verify_Matrix_values(default_data, matrix);
}

void test_Matrix_clean_2() {
    TEST_MESSAGE("Case 2 --> Matrix = NULL:");
    Matrix *matrix = NULL;

    bool cleaned = Matrix_clean(matrix);
    TEST_ASSERT_EQUAL(false, cleaned);
}

void test_Matrix_delete_1() {
    TEST_MESSAGE("Case 1 --> Matrix != NULL:");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    _verify_Matrix_values(default_data, matrix);

    bool deleted = Matrix_delete(&matrix);
    TEST_ASSERT_EQUAL(true, deleted);
    TEST_ASSERT_NULL(matrix);
    _verify_Matrix_values_ptr(NULL, matrix);
}

void test_Matrix_delete_2() {
    TEST_MESSAGE("Case 2 --> Matrix = NULL:");
    Matrix *matrix = NULL;

    bool deleted = Matrix_delete(&matrix);
    TEST_ASSERT_EQUAL(false, deleted);
}

void test_Matrix_rows_1() {
    TEST_MESSAGE("Case 1 --> Matrix != NULL:");
    int default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    TEST_ASSERT_EQUAL(ROWS, Matrix_rows(matrix));
}

void test_Matrix_rows_2() {
    TEST_MESSAGE("Case 2 --> Matrix = NULL:");
    Matrix *matrix = NULL;
    TEST_ASSERT_EQUAL(0, Matrix_rows(matrix));
}

void test_Matrix_cols_1() {
    TEST_MESSAGE("Case 1 --> Matrix != NULL:");
    int default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    TEST_ASSERT_EQUAL(ROWS, Matrix_cols(matrix));
}

void test_Matrix_cols_2() {
    TEST_MESSAGE("Case 2 --> Matrix = NULL:");
    Matrix *matrix = NULL;
    TEST_ASSERT_EQUAL(0, Matrix_cols(matrix));
}

void test_Matrix_get_at_1() {
    TEST_MESSAGE("Case 1 --> Matrix != NULL, 0 <= row < ROWS, 0 <= col < COLS");
    TYPE default_data = default_value, new_value = 1;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {

            TEST_ASSERT_EQUAL(default_data, *((TYPE *) Matrix_get_at(matrix, i, j)));

            Matrix_set_at(matrix, i, j, &new_value);

            TEST_ASSERT_EQUAL(new_value, *((TYPE *) Matrix_get_at(matrix, i, j)));
        }
    }
}

void test_Matrix_get_at_2() {
    TEST_MESSAGE("Case 2 --> Matrix = NULL, 0 <= row < ROWS, 0 <= col < COLS");
    Matrix *matrix = NULL;

    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            TEST_ASSERT_NULL(Matrix_get_at(matrix, i, j));
        }
    }
}

void test_Matrix_get_at_3() {
    TEST_MESSAGE("Case 3 --> Matrix != NULL, row < 0 , 0 <= col < COLS");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long j = 0; j < COLS; j++) {
        TEST_ASSERT_NULL(Matrix_get_at(matrix, -1, j));
    }
}

void test_Matrix_get_at_4() {
    TEST_MESSAGE("Case 4 --> Matrix != NULL, ROWS < row, 0 <= col < COLS");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long j = 0; j < COLS; j++) {
        TEST_ASSERT_NULL(Matrix_get_at(matrix, ROWS+1, j));
    }
}

void test_Matrix_get_at_5() {
    TEST_MESSAGE("Case 5 --> Matrix != NULL, 0 <= row < ROWS , col < 0");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        TEST_ASSERT_NULL(Matrix_get_at(matrix, i, -1));
    }
}

void test_Matrix_get_at_6() {
    TEST_MESSAGE("Case 6 --> Matrix != NULL, 0 <= row < ROWS, COLS < col");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        TEST_ASSERT_NULL(Matrix_get_at(matrix, i, COLS+1));
    }
}

void test_Matrix_get_at_7() {
    TEST_MESSAGE("Case 7 --> Matrix != NULL, row = ROWS, 0 <= col < COLS");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long j = 0; j < COLS; j++) {
        TEST_ASSERT_NULL(Matrix_get_at(matrix, ROWS, j));
    }
}

void test_Matrix_get_at_8() {
    TEST_MESSAGE("Case 8 --> Matrix != NULL, 0 <= row < ROWS, col = COLS");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        TEST_ASSERT_NULL(Matrix_get_at(matrix, i, COLS));
    }
}

void test_Matrix_set_at_1() {
    TEST_MESSAGE("Case 1 --> Matrix != NULL, 0 <= row < ROWS, 0 <= col < COLS, New Data != NULL");
    TYPE default_data = default_value, new_value = 1;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            TEST_ASSERT_TRUE(Matrix_set_at(matrix, i, j, &new_value));
        }
    }
}

void test_Matrix_set_at_2() {
    TEST_MESSAGE("Case 2 --> Matrix != NULL, 0 <= row < ROWS, 0 <= col < COLS, New Data = NULL");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            TEST_ASSERT_FALSE(Matrix_set_at(matrix, i, j, NULL));
        }
    }
}

void test_Matrix_set_at_3() {
    TEST_MESSAGE("Case 3 --> Matrix = NULL, 0 <= row < ROWS, 0 <= col < COLS, New Data != NULL");
    TYPE new_value = 1;
    Matrix *matrix = NULL;

    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            TEST_ASSERT_FALSE(Matrix_set_at(matrix, i, j, &new_value));
        }
    }
}

void test_Matrix_set_at_4() {
    TEST_MESSAGE("Case 4 --> Matrix != NULL, row < 0 , 0 <= col < COLS, New Data != NULL");
    TYPE default_data = default_value, new_value = 1;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long j = 0; j < COLS; j++) {
        TEST_ASSERT_FALSE(Matrix_set_at(matrix, -1, j, &new_value));
    }
}

void test_Matrix_set_at_5() {
    TEST_MESSAGE("Case 5 --> Matrix != NULL, ROWS < row, 0 <= col < COLS, New Data != NULL");
    TYPE default_data = default_value, new_value = 1;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long j = 0; j < COLS; j++) {
        TEST_ASSERT_FALSE(Matrix_set_at(matrix, ROWS+1, j, &new_value));
    }
}

void test_Matrix_set_at_6() {
    TEST_MESSAGE("Case 6 --> Matrix != NULL, 0 <= row < ROWS , col < 0, New Data != NULL");
    TYPE default_data = default_value, new_value = 1;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        TEST_ASSERT_FALSE(Matrix_set_at(matrix, i, -1, &new_value));
    }
}

void test_Matrix_set_at_7() {
    TEST_MESSAGE("Case 7 --> Matrix != NULL, 0 <= row < ROWS, COLS < col, New Data != NULL");
    TYPE default_data = default_value, new_value = 1;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        TEST_ASSERT_FALSE(Matrix_set_at(matrix, i, COLS+1, &new_value));
    }
}

void test_Matrix_set_at_8() {
    TEST_MESSAGE("Case 8 --> Matrix != NULL, row = ROWS, 0 <= col < COLS, New Data != NULL");
    TYPE default_data = default_value, new_value = 1;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long j = 0; j < COLS; j++) {
        TEST_ASSERT_FALSE(Matrix_set_at(matrix, ROWS, j, &new_value));
    }
}

void test_Matrix_set_at_9() {
    TEST_MESSAGE("Case 9 --> Matrix != NULL, 0 <= row < ROWS, col = COLS, New Data != NULL");
    TYPE default_data = default_value, new_value = 1;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        TEST_ASSERT_FALSE(Matrix_set_at(matrix, i, COLS, &new_value));
    }
}

void test_Matrix_clone_1() {
    TEST_MESSAGE("Case 1 --> Matrix != NULL:");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    Matrix *clone = Matrix_clone(matrix);

    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            TEST_ASSERT_EQUAL(*((TYPE *) Matrix_get_at(matrix, i, j)), *((TYPE *) Matrix_get_at(clone, i, j)));
        }
    }
}

void test_Matrix_clone_2() {
    TEST_MESSAGE("Case 2 --> Matrix = NULL:");
    Matrix *matrix = NULL;
    Matrix *clone = Matrix_clone(matrix);

    TEST_ASSERT_NULL(clone);
}

void test_Matrix_sub_1() {
    TEST_MESSAGE("Case 1 --> Matrix != NULL,  Valid indexes: ");
    long initial_row = 1, initial_col = 1;
    long final_row = 2, final_col = 2;
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    TYPE d1 = 1, d2 = 2, d3 = 3, d4 = 4;

    Matrix_set_at(matrix, initial_row, initial_col, &d1);
    Matrix_set_at(matrix, initial_row, final_col, &d2);
    Matrix_set_at(matrix, final_row, initial_col, &d3);
    Matrix_set_at(matrix, final_row, final_col, &d4);

    Matrix *sub = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    for (long i = 0; i < Matrix_rows(sub); i++) {
        for (long j = 0; j < Matrix_cols(sub); j++) {
            TYPE matrix_elem = *((TYPE *) Matrix_get_at(matrix, i+initial_row, j+initial_col));
            TYPE sub_elem = *((TYPE *) Matrix_get_at(sub, i, j));
            TEST_ASSERT_EQUAL(matrix_elem, sub_elem);
        }
    }
}

void test_Matrix_sub_2() {
    TEST_MESSAGE("Case 2 --> Matrix = NULL: ");
    long initial_row = 1, initial_col = 1;
    long final_row = 2, final_col = 2;
    Matrix *matrix = NULL;

    Matrix *sub = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    TEST_ASSERT_NULL(sub);
}

void test_Matrix_sub_3() {
    TEST_MESSAGE("Case 3 --> final row < 0:");
    long final_row = -1, final_col = 2;
    long initial_row = 1, initial_col = 1;
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    Matrix *sub = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    TEST_ASSERT_NULL(sub);
}

void test_Matrix_sub_4() {
    TEST_MESSAGE("Case 4 --> final row > ROWS:");
    long final_row = ROWS+1, final_col = 2;
    long initial_row = 1, initial_col = 1;
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    Matrix *sub = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    TEST_ASSERT_NULL(sub);
}

void test_Matrix_sub_5() {
    TEST_MESSAGE("Case 5 --> final column < 0:");
    long final_row = 2, final_col = -1;
    long initial_row = 1, initial_col = 1;
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    Matrix *sub = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    TEST_ASSERT_NULL(sub);
}

void test_Matrix_sub_6() {
    TEST_MESSAGE("Case 6 --> final column > COLS:");
    long final_row = 2, final_col = COLS+1;
    long initial_row = 1, initial_col = 1;
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    Matrix *sub = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    TEST_ASSERT_NULL(sub);
}

void test_Matrix_sub_7() {
    TEST_MESSAGE("Case 7 --> initial row < 0:");
    long final_row = 2, final_col = 2;
    long initial_row = -1, initial_col = 1;
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    Matrix *sub = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    TEST_ASSERT_NULL(sub);
}

void test_Matrix_sub_8() {
    TEST_MESSAGE("Case 8 --> initial row > final row:");
    long final_row = 2, final_col = 2;
    long initial_row = final_row+1, initial_col = 1;
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    Matrix *sub = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    TEST_ASSERT_NULL(sub);
}

void test_Matrix_sub_9() {
    TEST_MESSAGE("Case 9 --> initial column < 0:");
    long final_row = 2, final_col = 2;
    long initial_row = 1, initial_col = -1;
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    Matrix *sub = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    TEST_ASSERT_NULL(sub);
}

void test_Matrix_sub_10() {
    TEST_MESSAGE("Case 10 --> initial column > final column:");
    long final_row = 2, final_col = 2;
    long initial_row = 1, initial_col = final_col+1;
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    Matrix *sub = Matrix_sub(matrix, initial_row, initial_col, final_row, final_col);

    TEST_ASSERT_NULL(sub);
}

void test_Matrix_contains_1() {
    TEST_MESSAGE("Case 1--> Matrix != NULL, Data != NULL and Matrix contains the Data:");
    TYPE default_data = default_value, item = 99;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    Matrix_set_at(matrix, 1, 1, &item);

    TEST_ASSERT_TRUE(Matrix_contains(matrix, &item, _compare_TYPE));
}

void test_Matrix_contains_2() {
    TEST_MESSAGE("Case 2--> Matrix != NULL, Data != NULL and Matrix does not contain the Data:");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            TYPE item = (i * j) + 1;
            Matrix_set_at(matrix, i, j, &item);
        }
    }

    TEST_ASSERT_FALSE(Matrix_contains(matrix, &default_data, _compare_TYPE));
}

void test_Matrix_contains_3() {
    TEST_MESSAGE("Case 3--> Matrix = NULL:");
    TYPE default_data = default_value;
    Matrix *matrix = NULL;

    TEST_ASSERT_FALSE(Matrix_contains(matrix, &default_data, _compare_TYPE));
}

void test_Matrix_contains_4() {
    TEST_MESSAGE("Case 4--> Data = NULL:");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    TEST_ASSERT_FALSE(Matrix_contains(matrix, NULL, _compare_TYPE));

}

void test_Matrix_count_1() {
    TEST_MESSAGE("Case 1--> Matrix != NULL, Data != NULL and Matrix contains the Data:");
    TYPE default_data = default_value, item = 99;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            Matrix_set_at(matrix, i, j, &item);
        }
    }

    TEST_ASSERT_EQUAL(ROWS*COLS, Matrix_count(matrix, &item, _compare_TYPE));
}

void test_Matrix_count_2() {
    TEST_MESSAGE("Case 2--> Matrix != NULL, Data != NULL and Matrix does not contain the Data:");
    TYPE default_data = default_value, item = 99;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    TEST_ASSERT_EQUAL(0, Matrix_count(matrix, &item, _compare_TYPE));
}

void test_Matrix_count_3() {
    TEST_MESSAGE("Case 3--> Matrix = NULL:");
    TYPE default_data = default_value;
    Matrix *matrix = NULL;

    TEST_ASSERT_EQUAL(0, Matrix_count(matrix, &default_data, _compare_TYPE));
}

void test_Matrix_count_4() {
    TEST_MESSAGE("Case 4--> Data = NULL:");
    TYPE default_data = default_value;
    Matrix *matrix = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    TEST_ASSERT_EQUAL(0, Matrix_count(matrix, NULL, _compare_TYPE));

}

void test_Matrix_is_equals_1() {
    TEST_MESSAGE("Case 1 --> Matrix_1 == Matrix_2:");
    TYPE default_data = default_value;
    Matrix *matrix1 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            TYPE item = (i * j) + 1;
            Matrix_set_at(matrix1, i, j, &item);
        }
    }

    Matrix *matrix2 = Matrix_clone(matrix1);

    bool equals = Matrix_is_equals(matrix1, matrix2, _compare_TYPE);
    TEST_ASSERT_TRUE(equals);
}

void test_Matrix_is_equals_2() {
    TEST_MESSAGE("Case 2 --> Matrix_1 != Matrix_2:");
    TYPE default_data = default_value;
    Matrix *matrix1 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    for (long i = 0; i < ROWS; i++) {
        for (long j = 0; j < COLS; j++) {
            TYPE item = (i * j) + 1;
            Matrix_set_at(matrix1, i, j, &item);
        }
    }

    Matrix *matrix2 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    bool equals = Matrix_is_equals(matrix1, matrix2, _compare_TYPE);
    TEST_ASSERT_FALSE(equals);
}

void test_Matrix_is_equals_3() {
    TEST_MESSAGE("Case 3 --> Matrix_1 = NULL:");
    TYPE default_data = default_value;
    Matrix *matrix1 = NULL;
    Matrix *matrix2 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);

    bool equals = Matrix_is_equals(matrix1, matrix2, _compare_TYPE);
    TEST_ASSERT_FALSE(equals);
}

void test_Matrix_is_equals_4() {
    TEST_MESSAGE("Case 3 --> Matrix_2 = NULL:");
    TYPE default_data = default_value;
    Matrix *matrix1 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    Matrix *matrix2 = NULL;

    bool equals = Matrix_is_equals(matrix1, matrix2, _compare_TYPE);
    TEST_ASSERT_FALSE(equals);
}

void test_Matrix_is_equals_5() {
    TEST_MESSAGE("Case 5 --> Matrix1::ROWS != Matrix_2::ROWS:");
    TYPE default_data = default_value;
    Matrix *matrix1 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    Matrix *matrix2 = Matrix_create(ROWS+1, COLS, SIZE_OF_TYPE, &default_data);

    bool equals = Matrix_is_equals(matrix1, matrix2, _compare_TYPE);
    TEST_ASSERT_FALSE(equals);
}

void test_Matrix_is_equals_6() {
    TEST_MESSAGE("Case 6 --> Matrix1::COLS != Matrix_2::COLS:");
    TYPE default_data = default_value;
    Matrix *matrix1 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    Matrix *matrix2 = Matrix_create(ROWS, COLS+1, SIZE_OF_TYPE, &default_data);

    bool equals = Matrix_is_equals(matrix1, matrix2, _compare_TYPE);
    TEST_ASSERT_FALSE(equals);
}

void test_Matrix_is_equals_7() {
    TEST_MESSAGE("Case 7 --> Matrix1::TYPE != Matrix_2::TYPE:");
    TYPE default_data = default_value;
    Matrix *matrix1 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE, &default_data);
    Matrix *matrix2 = Matrix_create(ROWS, COLS, SIZE_OF_TYPE+4, &default_data);

    bool equals = Matrix_is_equals(matrix1, matrix2, _compare_TYPE);
    TEST_ASSERT_FALSE(equals);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_Matrix_create_1);
    RUN_TEST(test_Matrix_create_2);
    RUN_TEST(test_Matrix_create_3);
    RUN_TEST(test_Matrix_create_4);
    RUN_TEST(test_Matrix_clean_1);
    RUN_TEST(test_Matrix_clean_2);
    RUN_TEST(test_Matrix_delete_1);
    RUN_TEST(test_Matrix_delete_2);
    RUN_TEST(test_Matrix_rows_1);
    RUN_TEST(test_Matrix_rows_2);
    RUN_TEST(test_Matrix_cols_1);
    RUN_TEST(test_Matrix_cols_2);
    RUN_TEST(test_Matrix_get_at_1);
    RUN_TEST(test_Matrix_get_at_2);
    RUN_TEST(test_Matrix_get_at_3);
    RUN_TEST(test_Matrix_get_at_4);
    RUN_TEST(test_Matrix_get_at_5);
    RUN_TEST(test_Matrix_get_at_6);
    RUN_TEST(test_Matrix_get_at_7);
    RUN_TEST(test_Matrix_get_at_8);
    RUN_TEST(test_Matrix_set_at_1);
    RUN_TEST(test_Matrix_set_at_2);
    RUN_TEST(test_Matrix_set_at_3);
    RUN_TEST(test_Matrix_set_at_4);
    RUN_TEST(test_Matrix_set_at_5);
    RUN_TEST(test_Matrix_set_at_6);
    RUN_TEST(test_Matrix_set_at_7);
    RUN_TEST(test_Matrix_set_at_8);
    RUN_TEST(test_Matrix_set_at_9);
    RUN_TEST(test_Matrix_clone_1);
    RUN_TEST(test_Matrix_clone_2);
    RUN_TEST(test_Matrix_sub_1);
    RUN_TEST(test_Matrix_sub_2);
    RUN_TEST(test_Matrix_sub_3);
    RUN_TEST(test_Matrix_sub_4);
    RUN_TEST(test_Matrix_sub_5);
    RUN_TEST(test_Matrix_sub_6);
    RUN_TEST(test_Matrix_sub_7);
    RUN_TEST(test_Matrix_sub_8);
    RUN_TEST(test_Matrix_sub_9);
    RUN_TEST(test_Matrix_sub_10);
    RUN_TEST(test_Matrix_contains_1);
    RUN_TEST(test_Matrix_contains_2);
    RUN_TEST(test_Matrix_contains_3);
    RUN_TEST(test_Matrix_contains_4);
    RUN_TEST(test_Matrix_count_1);
    RUN_TEST(test_Matrix_count_2);
    RUN_TEST(test_Matrix_count_3);
    RUN_TEST(test_Matrix_count_4);
    RUN_TEST(test_Matrix_is_equals_1);
    RUN_TEST(test_Matrix_is_equals_2);
    RUN_TEST(test_Matrix_is_equals_3);
    RUN_TEST(test_Matrix_is_equals_4);
    RUN_TEST(test_Matrix_is_equals_5);
    RUN_TEST(test_Matrix_is_equals_6);
    RUN_TEST(test_Matrix_is_equals_7);
    return UNITY_END();
}

