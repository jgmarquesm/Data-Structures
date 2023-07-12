#include "../include/matrix.h"
#include "../include/array.h"
#include <stdlib.h>
#include <stdio.h>

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
    if (rows <= 0) {
        fprintf(stderr, "\nERROR: on function 'Matrix_create'.\n");
        fprintf(stderr, "ERROR: rows must be greater then 0. Current value: %ld.\n", rows);
        exit(EXIT_FAILURE);
    }
    if (cols <= 0) {
        fprintf(stderr, "\nERROR: on function 'Matrix_create'.\n");
        fprintf(stderr, "ERROR: cols must be greater then 0. Current value: %ld.\n", cols);
        exit(EXIT_FAILURE);
    }
    Matrix *matrix = (Matrix *) calloc(1, sizeof(Matrix));
    matrix->data = Array_create(rows*cols, size_of_type);
    matrix->number_of_rows = rows;
    matrix->number_of_cols = cols;
    matrix->size = 0;
    matrix->size_of_type = size_of_type;
    return matrix;
}

void Matrix_clean(Matrix *matrix) {
    Array_clean(matrix->data);
    matrix->size_of_type = 0;
    matrix->size = 0;
}

void Matrix_delete(Matrix **matrix_ref) {
    Matrix *matrix = *matrix_ref;
    Matrix_clean(matrix);
    free(matrix);
    *matrix_ref= NULL;
}

long Matrix_rows(const Matrix *matrix) {
    return matrix->number_of_rows;
}

long Matrix_cols(const Matrix *matrix) {
    return matrix->number_of_cols;
}

long Matrix_size(const Matrix *matrix) {
    return matrix->size;
}

bool Matrix_is_empty(const Matrix *matrix) {
    return matrix->size == 0;
}

bool Matrix_is_full(const Matrix *matrix) {
    return matrix->size == (matrix->number_of_rows * matrix->number_of_cols);
}

void *Matrix_get_at(const Matrix *matrix, const long row, const long col) {
    if (row >= matrix->number_of_rows || row < 0) {
        fprintf(stderr, "\nERROR: on function 'Matrix_get_at'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid row: %ld. Try an row within [0, %ld].\n", row, matrix->number_of_rows - 1);
        exit(EXIT_FAILURE);
    }
    if (col >= matrix->number_of_cols || col < 0) {
        fprintf(stderr, "\nERROR: on function 'Matrix_get_at'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid col: %ld. Try an col within [0, %ld].\n", col, matrix->number_of_cols - 1);
        exit(EXIT_FAILURE);
    }
    if (Matrix_is_empty(matrix)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_get_at'.\n");
        fprintf(stderr, "ERROR: Matrix is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (matrix == NULL) {
        fprintf(stderr, "\nERROR: on function 'Matrix_get_at'.\n");
        fprintf(stderr, "ERROR: Matrix is NULL.\n");
        exit(EXIT_FAILURE);
    }
    long index = _get_index(row, col, matrix->number_of_rows);
    return Array_get_at(matrix->data, index);
}

void Matrix_insert_at(Matrix *matrix, const long row, const long col, void *data) {
    if (row >= matrix->number_of_rows || row < 0) {
        fprintf(stderr, "\nERROR: on function 'Matrix_insert_at'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid row: %ld. Try an row within [0, %ld].\n", row, matrix->number_of_rows - 1);
        exit(EXIT_FAILURE);
    }
    if (col >= matrix->number_of_cols || col < 0) {
        fprintf(stderr, "\nERROR: on function 'Matrix_insert_at'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid col: %ld. Try an col within [0, %ld].\n", col, matrix->number_of_cols - 1);
        exit(EXIT_FAILURE);
    }
    if (matrix == NULL) {
        fprintf(stderr, "\nERROR: on function 'Matrix_insert_at'.\n");
        fprintf(stderr, "ERROR: Matrix is NULL.\n");
        exit(EXIT_FAILURE);
    }
    long index = _get_index(row, col, matrix->number_of_rows);
    Array_insert_at(matrix->data, data, index);
    matrix->size++;
}

void Matrix_set(Matrix *matrix, const long row, const long col, void *data) {
    if (row >= matrix->number_of_rows || row < 0) {
        fprintf(stderr, "\nERROR: on function 'Matrix_set'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid row: %ld. Try an row within [0, %ld].\n", row, matrix->number_of_rows - 1);
        exit(EXIT_FAILURE);
    }
    if (col >= matrix->number_of_cols || col < 0) {
        fprintf(stderr, "\nERROR: on function 'Matrix_set'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid col: %ld. Try an col within [0, %ld].\n", col, matrix->number_of_cols - 1);
        exit(EXIT_FAILURE);
    }
    if (matrix == NULL) {
        fprintf(stderr, "\nERROR: on function 'Matrix_set'.\n");
        fprintf(stderr, "ERROR: Matrix is NULL.\n");
        exit(EXIT_FAILURE);
    }
    long index = _get_index(row, col, matrix->number_of_rows);
    Array_set(matrix->data, data, index);
}

// TODO: Tratar os casos em que a matriz não está cheia para executar o método corretamente nesse cenário
void Matrix_print(const Matrix *matrix, void (*type_print_function)(void * data)) {
    if (!Matrix_is_full(matrix)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_print'.\n");
        fprintf(stderr, "ERROR MESSAGE: Matrix must be full.\n");
        exit(EXIT_FAILURE);
    }
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
    if (Matrix_is_empty(matrix)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_clone'.\n");
        fprintf(stderr, "ERROR: Matrix is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (matrix == NULL) {
        fprintf(stderr, "\nERROR: on function 'Matrix_clone'.\n");
        fprintf(stderr, "ERROR: Matrix is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (!Matrix_is_full(matrix)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_clone'.\n");
        fprintf(stderr, "ERROR MESSAGE: Matrix must be full.\n");
        exit(EXIT_FAILURE);
    }
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
    if (Matrix_is_empty(matrix)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_sub'.\n");
        fprintf(stderr, "ERROR: Matrix is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (matrix == NULL) {
        fprintf(stderr, "\nERROR: on function 'Matrix_sub'.\n");
        fprintf(stderr, "ERROR: Matrix is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (initial_row >= final_row) {
        fprintf(stderr, "\nERROR: on function 'Matrix_sub'.\n");
        fprintf(stderr, "ERROR: initial_row greater or equal than final_row: %ld >= %ld.\n", initial_row, final_row);
        exit(EXIT_FAILURE);
    }
    if (initial_col >= final_col) {
        fprintf(stderr, "\nERROR: on function 'Matrix_sub'.\n");
        fprintf(stderr, "ERROR: initial_col greater or equal than final_col: %ld >= %ld.\n", initial_col, final_col);
        exit(EXIT_FAILURE);
    }
    if (initial_row < 0) {
        fprintf(stderr, "\nERROR: on function 'Matrix_sub'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid row: %ld. Try an row within [0, %ld].\n", initial_row, matrix->number_of_rows - 1);
        exit(EXIT_FAILURE);
    }
    if (initial_col < 0) {
        fprintf(stderr, "\nERROR: on function 'Matrix_sub'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid col: %ld. Try an col within [0, %ld].\n", initial_col, matrix->number_of_cols - 1);
        exit(EXIT_FAILURE);
    }
    if (final_row >= matrix->number_of_rows) {
        fprintf(stderr, "\nERROR: on function 'Matrix_sub'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid row: %ld. Try an row within [0, %ld].\n", final_row, matrix->number_of_rows - 1);
        exit(EXIT_FAILURE);
    }
    if (final_col >= matrix->number_of_cols) {
        fprintf(stderr, "\nERROR: on function 'Matrix_sub'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid col: %ld. Try an col within [0, %ld].\n", final_col, matrix->number_of_cols - 1);
        exit(EXIT_FAILURE);
    }
    if (!Matrix_is_full(matrix)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_sub'.\n");
        fprintf(stderr, "ERROR MESSAGE: Matrix must be full.\n");
        exit(EXIT_FAILURE);
    }
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
    if (matrix == NULL) {
        fprintf(stderr, "\nERROR: on function 'Matrix_contains'.\n");
        fprintf(stderr, "ERROR: Matrix is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (Matrix_is_empty(matrix)) {
        return false;
    }
    if (!Matrix_is_full(matrix)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_contains'.\n");
        fprintf(stderr, "ERROR MESSAGE: Matrix must be full.\n");
        exit(EXIT_FAILURE);
    }
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
    if (matrix == NULL) {
        fprintf(stderr, "\nERROR: on function 'Matrix_count'.\n");
        fprintf(stderr, "ERROR: Matrix is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (Matrix_is_empty(matrix)) {
        return 0;
    }
    if (!Matrix_is_full(matrix)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_count'.\n");
        fprintf(stderr, "ERROR MESSAGE: Matrix must be full.\n");
        exit(EXIT_FAILURE);
    }
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
    if (matrix1 == NULL || matrix2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'Matrix_equals'.\n");
        fprintf(stderr, "ERROR: Matrix is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (Matrix_is_empty(matrix1) || Matrix_is_empty(matrix2)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_equals'.\n");
        fprintf(stderr, "ERROR: Matrix is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (!Matrix_is_full(matrix1) || !Matrix_is_full(matrix2)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_is_equals'.\n");
        fprintf(stderr, "ERROR MESSAGE: Matrix must be full.\n");
        exit(EXIT_FAILURE);
    }
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
