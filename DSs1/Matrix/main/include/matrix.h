#ifndef MATRIX_H
#define MATRIX_H

typedef struct _matrix Matrix;

Matrix *Matrix_crete(const long rows, const long cols, unsigned int size_of_type);

void Matrix_clean(Matrix *matrix);

void Matrix_delete(Matrix **matrix_ref);

long Matrix_rows(const Matrix *matrix);

long Matrix_cols(const Matrix *matrix);

long Matrix_size(const Matrix *matrix);

int Matrix_sort_order(const Matrix *matrix);

bool Matrix_is_empty(const Matrix *matrix);

bool Matrix_is_full(const Matrix *matrix);

bool Matrix_is_sorted(const Matrix *matrix);

void *Matrix_first_element(const Matrix *matrix);

void *Matrix_last_element(const Matrix *matrix);

void *Matrix_get_at(const Matrix *matrix, const long row, const long col);

void Matrix_add_first(Matrix *matrix, void *data);

void Matrix_add_last(Matrix *matrix, void *data);

void Matrix_insert_at(Matrix *matrix, const long row, const long col, void *data);

void Matrix_set(Matrix *matrix, void *data, const long row, const long col);

#endif
