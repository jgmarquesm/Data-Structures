#include "../include/matrix.h"
#include "../include/array.h"
#include <stdlib.h>
#include <stdio.h>

#define UNSORTED 0
#define ASC 1
#define DESC -1

typedef struct _matrix {
    Array *data;
    long number_of_rows;
    long number_of_cols;
    long size;
    int sort_order;
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

Matrix *Matrix_crete(const long rows, const long cols, unsigned int size_of_type) {
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
    matrix->sort_order = UNSORTED;
    matrix->size_of_type = size_of_type;
    return matrix;
}

void Matrix_clean(Matrix *matrix) {
    Array_clean(matrix->data);
    matrix->size_of_type = 0;
    matrix->size = 0;
    matrix->sort_order = UNSORTED;
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

int Matrix_sort_order(const Matrix *matrix) {
    return matrix->sort_order;
}

bool Matrix_is_empty(const Matrix *matrix) {
    return matrix->size == 0;
}

bool Matrix_is_full(const Matrix *matrix) {
    return matrix->size == (matrix->number_of_rows * matrix->number_of_cols);
}

bool Matrix_is_sorted(const Matrix *matrix) {
    return matrix->sort_order == ASC || matrix->sort_order == DESC;
}

void *Matrix_first_element(const Matrix *matrix) {
    if (Matrix_is_empty(matrix->data)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_first_element'.\n");
        fprintf(stderr, "ERROR: Matrix is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (matrix->data == NULL) {
        fprintf(stderr, "\nERROR: on function 'Matrix_first_element'.\n");
        fprintf(stderr, "ERROR: Matrix is NULL.\n");
        exit(EXIT_FAILURE);
    }
    Array_first_element(matrix->data);
}

void *Matrix_last_element(const Matrix *matrix) {
    if (Matrix_is_empty(matrix->data)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_last_element'.\n");
        fprintf(stderr, "ERROR: Matrix is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (matrix->data == NULL) {
        fprintf(stderr, "\nERROR: on function 'Matrix_last_element'.\n");
        fprintf(stderr, "ERROR: Matrix is NULL.\n");
        exit(EXIT_FAILURE);
    }
    Array_last_element(matrix->data);
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

void Matrix_add_first(Matrix *matrix, void *data) {
    if (Matrix_is_full(matrix)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_add_first'.\n");
        fprintf(stderr, "ERROR: Matrix is full.\n");
        exit(EXIT_FAILURE);
    }
    Array_add_first(matrix->data, data);
    matrix->sort_order = UNSORTED;
    matrix->size++;
}

void Matrix_add_last(Matrix *matrix, void *data) {
    if (Matrix_is_full(matrix)) {
        fprintf(stderr, "\nERROR: on function 'Matrix_add_last'.\n");
        fprintf(stderr, "ERROR: Matrix is full.\n");
        exit(EXIT_FAILURE);
    }
    Array_add_last(matrix->data, data);
    matrix->sort_order = UNSORTED;
    matrix->size++;
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
    matrix->sort_order = UNSORTED;
    matrix->size++;
}

void Matrix_set(Matrix *matrix, void *data, const long row, const long col) {
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
    matrix->sort_order = UNSORTED;
}


