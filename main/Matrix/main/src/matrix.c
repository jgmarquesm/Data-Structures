#include <stdlib.h>
#include <stdio.h>
#include "../include/array.h"
//#--ADD_TO_INCLUDE
#include "../include/matrix.h"

typedef struct _matrix {
    Array *data;
    long number_of_rows;
    long number_of_cols;
    long size;
    unsigned int size_of_type;
} Matrix;

long _get_index(const long row, const long col, const long number_of_rows) {
    return row * number_of_rows + col;
}

long _get_row(const long index, const long number_of_rows) {
    return index / number_of_rows;
}

long _get_col(const long index, const long number_of_rows) {
    return index % number_of_rows;
}

Matrix *Matrix_create(const long rows, const long cols, unsigned int size_of_type) {
    if (anyThrows(
            2,
            ExceptionHandler_is_non_positive("Matrix_create", "Rows", rows, true, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_non_positive("Matrix_create", "Columns", cols, true, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Matrix *matrix = (Matrix *) calloc(1, sizeof(Matrix));
    matrix->data = Array_create(rows*cols, size_of_type);
    matrix->number_of_rows = rows;
    matrix->number_of_cols = cols;
    matrix->size = 0;
    matrix->size_of_type = size_of_type;
    return matrix;
}

void Matrix_clean(Matrix *matrix) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Matrix_clean", "Matrix", matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    Array_clean(matrix->data);
    matrix->size_of_type = 0;
    matrix->size = 0;
}

void Matrix_delete(Matrix **matrix_ref) {
    Matrix *matrix = *matrix_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Matrix_delete", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    Matrix_clean(matrix);
    free(matrix);
    *matrix_ref= NULL;
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

long Matrix_size(const Matrix *matrix) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Matrix_size", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Matrix_size", "Matrix", (void *) matrix, Matrix_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    return matrix->size;
}

bool Matrix_is_empty(void *matrix) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Matrix_is_empty", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR)
        )
    ) return true;
    return ((Matrix *) matrix)->size == 0;
}

bool Matrix_is_full(void *matrix) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Matrix_is_full", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Matrix_is_full", "Matrix", (void *) matrix, Matrix_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    return ((Matrix *) matrix)->size == (((Matrix *) matrix)->number_of_rows * ((Matrix *) matrix)->number_of_cols);
}

void *Matrix_get_at(const Matrix *matrix, const long row, const long col) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("Matrix_get_at", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Matrix_get_at", "Matrix", (void *) matrix, Matrix_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_get_at", "Matrix", row, matrix->number_of_rows-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_get_at", "Matrix", col, matrix->number_of_cols-1, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    long index = _get_index(row, col, matrix->number_of_rows);
    return Array_get_at(matrix->data, index);
}

void Matrix_insert_at(Matrix *matrix, const long row, const long col, void *data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("Matrix_insert_at", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Matrix_insert_at", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_insert_at", "Matrix", row, matrix->number_of_rows-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_insert_at", "Matrix", col, matrix->number_of_cols-1, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    long index = _get_index(row, col, matrix->number_of_rows);
    Array_insert_at(matrix->data, data, index);
    matrix->size++;
}

void Matrix_set(Matrix *matrix, const long row, const long col, void *data) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("Matrix_set", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Matrix_set", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_set", "Matrix", row, matrix->number_of_rows-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_set", "Matrix", col, matrix->number_of_cols-1, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    long index = _get_index(row, col, matrix->number_of_rows);
    Array_set(matrix->data, data, index);
}

// TODO: Tratar os casos em que a matriz não está cheia para executar o método corretamente nesse cenário
void Matrix_print(const Matrix *matrix, void (*type_print_function)(void * data)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Matrix_print", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Matrix_print", "Matrix", (void *) matrix, Matrix_is_empty, SUPPRESS_PRINT_ERROR)
        ) || !Matrix_is_full((void *) matrix)
    ) return;
    puts("[");
    for (long i = 0; i < matrix->number_of_rows; i++) {
        printf("[");
        for(long j = 0; j < matrix->number_of_cols-1; j++) {
            void *data = Matrix_get_at(matrix, i, j);
            type_print_function(data);
            printf(", ");
        }
        type_print_function(Matrix_get_at(matrix, i, matrix->number_of_cols-1));
        puts("],");
    }
    puts("]");
}

// TODO: Tratar os casos em que a matriz não está cheia para executar o método corretamente nesse cenário
Matrix *Matrix_clone(const Matrix *matrix) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Matrix_clone", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Matrix_clone", "Matrix", (void *) matrix, Matrix_is_empty, SUPPRESS_PRINT_ERROR)
        ) || !Matrix_is_full((void *) matrix)
    ) return NULL;
    Matrix *clone = Matrix_create(matrix->number_of_rows, matrix->number_of_cols, matrix->size_of_type);
    for (int i = 0; i < matrix->number_of_rows; i++) {
        for (long j = 0; j < matrix->number_of_cols; j++) {
            void *data = Matrix_get_at(matrix, i, j);
            Matrix_insert_at(clone, i, j, data);
        }
    }
    return clone;
}

// TODO: Tratar os casos em que a matriz não está cheia para executar o método corretamente nesse cenário
Matrix *Matrix_sub(const Matrix *matrix, const long initial_row, const long initial_col, const long final_row, const long final_col) {
    if (anyThrows(
            6,
            ExceptionHandler_is_null("Matrix_sub", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Matrix_sub", "Matrix", (void *) matrix, Matrix_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_sub", "Final Row", final_row, matrix->number_of_rows-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_sub", "Final Column", final_col, matrix->number_of_cols-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_sub", "Initial Row", initial_row, final_row-1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_out_of_bounds("Matrix_sub", "Initial Column", initial_row, final_col-1, SUPPRESS_PRINT_ERROR)
        ) || !Matrix_is_full((void *) matrix)
    ) return NULL;
    long rows = final_row - initial_row + 1;
    long cols = final_col - initial_col + 1;
    Matrix *sub = Matrix_create(rows, cols, matrix->size_of_type);
    for (long i = initial_row; i <= final_row; i++) {
        for (long j = initial_col; j <= final_col; j++) {
            void *data = Matrix_get_at(matrix, i, j);
            Matrix_insert_at(sub, i-initial_row, j-initial_col, data);
        }
    }
    return sub;
}

// TODO: Tratar os casos em que a matriz não está cheia para executar o método corretamente nesse cenário
bool Matrix_contains(const Matrix *matrix, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("Matrix_contains", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Matrix_contains", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Matrix_contains", "Matrix", (void *) matrix, Matrix_is_empty, SUPPRESS_PRINT_ERROR)
        ) || !Matrix_is_full((void *) matrix)
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

// TODO: Tratar os casos em que a matriz não está cheia para executar o método corretamente nesse cenário
long Matrix_count(const Matrix *matrix, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Matrix_count", "Matrix", (void *) matrix, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Matrix_count", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Matrix_count", "Matrix", (void *) matrix, Matrix_is_empty, SUPPRESS_PRINT_ERROR)
        ) || !Matrix_is_full((void *) matrix)
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

// TODO: Tratar os casos em que a matriz não está cheia para executar o método corretamente nesse cenário
bool Matrix_is_equals(const Matrix *matrix1, Matrix *matrix2, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Matrix_is_equals", "Matrix 1", (void *) matrix1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Matrix_is_equals", "Matrix 2", (void *) matrix2, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Matrix_is_equals", "Matrix 1", (void *) matrix1, Matrix_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("Matrix_is_equals", "Matrix 2", (void *) matrix2, Matrix_is_empty, SUPPRESS_PRINT_ERROR)
        ) || !Matrix_is_full((void *) matrix1) || !Matrix_is_full((void *) matrix2)
    ) return false;
    if (matrix1->size_of_type != matrix2->size_of_type) {
        return false;
    }
    if (matrix1->size != matrix2->size) {
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
