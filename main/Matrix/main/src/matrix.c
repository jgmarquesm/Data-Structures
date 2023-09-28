#include <stdlib.h>
#include <stdio.h>
#include "../include/array.h"
//#--ADD_TO_INCLUDE
#include "../include/matrix.h"

typedef struct _matrix {
    Array *data;
    long number_of_rows;
    long number_of_cols;
    void *default_data;
    unsigned int size_of_type;
} Matrix;

Matrix *Matrix_create(const long rows, const long cols, unsigned int size_of_type, void *default_data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_non_positive("Matrix_create", "Rows", rows, false, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_non_positive("Matrix_create", "Columns", cols, false, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Matrix_create", "Default Data", default_data, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Matrix *matrix = (Matrix *) calloc(1, sizeof(Matrix));

    Array *data = Array_create(rows, SIZE_OF_ARRAY_TYPE);

    for (long i = 0; i < rows; i++) {
        Array *_col = Array_create(cols, size_of_type);
        for (long j = 0; j < cols; j++) {
            Array_insert_at(_col, default_data, j);
        }
        Array_insert_at(data, _col, i);
    }

    matrix->data = data;
    matrix->number_of_rows = rows;
    matrix->number_of_cols = cols;
    matrix->default_data = default_data;
    matrix->size_of_type = size_of_type;
    return matrix;
}

bool Matrix_clean(Matrix *matrix) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Matrix_clean", "Matrix", matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    for (long i = 0; i < matrix->number_of_rows; i++) {
        for (long j = 0; j < matrix->number_of_cols; j++) {
            Matrix_set_at(matrix, i, j, matrix->default_data);
        }
    }
    return true;
}

bool Matrix_delete(Matrix **matrix_ref) {
    Matrix *matrix = *matrix_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Matrix_delete", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Array_delete(&(matrix->data));
    free(matrix);
    *matrix_ref= NULL;
    return true;
}

long Matrix_rows(const Matrix *matrix) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Matrix_rows", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    return matrix->number_of_rows;
}

long Matrix_cols(const Matrix *matrix) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Matrix_cols", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    return matrix->number_of_cols;
}

void *Matrix_get_at(const Matrix *matrix, const long row, const long col) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Matrix_get_at", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            2,
            ExceptionHandler_is_out_of_bounds("Matrix_get_at", "Row", row, matrix->number_of_rows-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_get_at", "Column", col, matrix->number_of_cols-1, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Array *row_ = Array_get_at(matrix->data, row);
    return Array_get_at(row_, col);
}

bool Matrix_set_at(Matrix *matrix, const long row, const long col, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Matrix_set", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Matrix_set", "Data", data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            2,
            ExceptionHandler_is_out_of_bounds("Matrix_set", "Row", row, matrix->number_of_rows-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_set", "Column", col, matrix->number_of_cols-1, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Array *row_ = Array_get_at(matrix->data, row);
    Array_set(row_, data, col);
    return true;
}

void Matrix_print(const Matrix *matrix, void (*type_print_function)(void * data)) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Matrix_print", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    puts("[");
    for (long i = 0; i < matrix->number_of_rows; i++) {
        Array *col_ = Array_get_at(matrix->data, i);
        Array_print(col_, type_print_function);
    }
    puts("]");
}

Matrix *Matrix_clone(const Matrix *matrix) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Matrix_clone", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Matrix *clone = Matrix_create(matrix->number_of_rows, matrix->number_of_cols, matrix->size_of_type, matrix->default_data);
    for (int i = 0; i < matrix->number_of_rows; i++) {
        for (long j = 0; j < matrix->number_of_cols; j++) {
            void *data = Matrix_get_at(matrix, i, j);
            Matrix_set_at(clone, i, j, data);
        }
    }
    return clone;
}

Matrix *Matrix_sub(const Matrix *matrix, const long initial_row, const long initial_col, const long final_row, const long final_col) {
    if (anyThrows(
            5,
            ExceptionHandler_is_null("Matrix_sub", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_sub", "Final Row", final_row, matrix->number_of_rows-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_sub", "Final Column", final_col, matrix->number_of_cols-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_sub", "Initial Row", initial_row, final_row-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_sub", "Initial Column", initial_row, final_col-1, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    long rows = final_row - initial_row + 1;
    long cols = final_col - initial_col + 1;
    Matrix *sub = Matrix_create(rows, cols, matrix->size_of_type, matrix->default_data);
    for (long i = initial_row; i <= final_row; i++) {
        for (long j = initial_col; j <= final_col; j++) {
            void *data = Matrix_get_at(matrix, i, j);
            Matrix_set_at(sub, i-initial_row, j-initial_col, data);
        }
    }
    return sub;
}

bool Matrix_contains(const Matrix *matrix, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Matrix_contains", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Matrix_contains", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    for (long i = 0; i < matrix->number_of_rows; i++) {
        for (long j = 0; j < matrix->number_of_cols; j++){
            void *ij_data = Matrix_get_at(matrix, i, j);
            if (type_compare_function(ij_data, data) == 0) {
                return true;
            }
        }
    }
    return false;
}

long Matrix_count(const Matrix *matrix, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Matrix_count", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Matrix_count", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    long count = 0;
    for (long i = 0; i < matrix->number_of_rows; i++) {
        for (long j = 0; j < matrix->number_of_cols; j++) {
            void *ij_data = Matrix_get_at(matrix, i, j);
            if (type_compare_function(ij_data, data) == 0) {
                count++;
            }
        }
    }
    return count;
}

bool Matrix_is_equals(const Matrix *matrix1, Matrix *matrix2, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Matrix_is_equals", "Matrix 1", (void *) matrix1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Matrix_is_equals", "Matrix 2", (void *) matrix2, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    if (matrix1->size_of_type != matrix2->size_of_type) {
        return false;
    }
    for (long i = 0; i < matrix1->number_of_rows; i++) {
        for (long j = 0; j< matrix1->number_of_cols; j++) {
            void *data1 = Matrix_get_at(matrix1, i, j);
            void *data2 = Matrix_get_at(matrix2, i, j);
            if (type_compare_function(data1 ,data2) != 0) {
                return false;
            }
        }
    }
    return true;
}
