#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

/**
 * As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
 * 1 - Type printing function: To print data correctly.\n
 * 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
 * 3 - Type comparison function: To compare correctly data.
 */
typedef struct _matrix Matrix;
/**
 *
 * @param matrix
 * @return
 */
long Matrix_rows(const Matrix *matrix);
/**
 *
 * @param matrix
 * @return
 */
long Matrix_cols(const Matrix *matrix);
/**
 *
 * @param matrix
 * @return
 */
long Matrix_size(const Matrix *matrix);
/**
 *
 * @param matrix
 * @return
 */
bool Matrix_is_empty(const Matrix *matrix);
/**
 *
 * @param matrix
 * @return
 */
bool Matrix_is_full(const Matrix *matrix);
/**
 *
 * @param rows
 * @param cols
 * @param size_of_type
 * @return
 */
Matrix *Matrix_create(const long rows, const long cols, unsigned int size_of_type);
/**
 *
 * @param matrix
 * @return
 */
Matrix *Matrix_clone(const Matrix *matrix);
/**
 *
 * @param matrix
 * @param initial_row
 * @param initial_col
 * @param final_row
 * @param final_col
 * @return
 */
Matrix *Matrix_sub(const Matrix *matrix, const long initial_row, const long initial_col, const long final_row, const long final_col);
/**
 *
 * @param matrix
 */
void Matrix_clean(Matrix *matrix);
/**
 *
 * @param matrix_ref
 */
void Matrix_delete(Matrix **matrix_ref);
/**
 *
 * @param matrix
 * @param row
 * @param col
 * @return
 */
void *Matrix_get_at(const Matrix *matrix, const long row, const long col);
/**
 *
 * @param matrix
 * @param row
 * @param col
 * @param data
 */
void Matrix_insert_at(Matrix *matrix, const long row, const long col, void *data);
/**
 *
 * @param matrix
 * @param row
 * @param col
 * @param data
 */
void Matrix_set(Matrix *matrix, const long row, const long col, void *data);
/**
 *
 * @param matrix
 * @param type_print_function
 */
void Matrix_print(const Matrix *matrix, void (*type_print_function)(void * data));
/**
 *
 * @param matrix
 * @param data
 * @param type_compare_function
 * @return
 */
bool Matrix_contains(const Matrix *matrix, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param matrix
 * @param data
 * @param type_compare_function
 * @return
 */
long Matrix_count(const Matrix *matrix, void *data, int (*type_compare_function)(void *data1, void *data2));
/**
 *
 * @param matrix1
 * @param matrix2
 * @param type_compare_function
 * @return
 */
bool Matrix_is_equals(const Matrix *matrix1, Matrix *matrix2, int (*type_compare_function)(void *data1, void *data2));

#endif
