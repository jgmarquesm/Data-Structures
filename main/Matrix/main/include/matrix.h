#ifndef MATRIX_H
#define MATRIX_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#ifdef __DEFAULT_LONG__
    #undef __DEFAULT_LONG__
#endif
#ifdef __DEFAULT_BOOL__
    #undef __DEFAULT_BOOL__
#endif
#ifdef __NOT_DEFAULT_BOOL__
    #undef __NOT_DEFAULT_BOOL__
#endif
#ifdef __DEFAULT_PTR__
    #undef __DEFAULT_PTR__
#endif
#ifdef __TYPE_COMPARE_FUNCTION_NAME__
    #undef __TYPE_COMPARE_FUNCTION_NAME__
#endif
#ifdef __TYPE_COMPARE_FUNCTION_SIGNATURE__
    #undef __TYPE_COMPARE_FUNCTION_SIGNATURE__
#endif
#ifdef __TYPE_PRINT_FUNCTION_NAME__
    #undef __TYPE_PRINT_FUNCTION_NAME__
#endif
#ifdef __TYPE_PRINT_FUNCTION_SIGNATURE__
    #undef __TYPE_PRINT_FUNCTION_SIGNATURE__
#endif

#define __DEFAULT_LONG__ 0
#define __DEFAULT_BOOL__ false
#define __NOT_DEFAULT_BOOL__ true
#define __DEFAULT_PTR__ NULL
#define __TYPE_COMPARE_FUNCTION_NAME__ type_compare_func
#define __TYPE_COMPARE_FUNCTION_SIGNATURE__ int (*__TYPE_COMPARE_FUNCTION_NAME__)(void *data1, void *data2)
#define __TYPE_PRINT_FUNCTION_NAME__ type_print_func
#define __TYPE_PRINT_FUNCTION_SIGNATURE__ void (*__TYPE_PRINT_FUNCTION_NAME__)(void *data)

#define SIZE_OF_MATRIX_TYPE size_of_matrix_type

extern const size_t size_of_matrix_type;

/**
 * As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
 * 1 - Type printing function: To print data correctly.\n
 * 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
 * 3 - Type comparison function: To compare correctly data.
 */
typedef struct _matrix Matrix;
/**
 *
 * @param matrix -> Matrix to get the number of rows;
 * @return Matrix Number of rows.
 */
long Matrix_rows(const Matrix *matrix);
/**
 *
 * @param matrix -> Matrix to get the number of columns;
 * @return Matrix Number of cols.
 */
long Matrix_cols(const Matrix *matrix);
/**
 *
 * @param rows -> number of rows to be allocated
 * @param cols -> number of cols to be allocated
 * @param size_of_type -> size of data type to be allocated
 * @return A new Matrix with thw number of rows and cols passed and max number of elements equals to rows * cols
 */
Matrix *Matrix_create(const long rows, const long cols, unsigned int size_of_type, void *default_data);
/**
 *
 * @param matrix -> Matrix to be cloned
 * @return A clone of Array
 */
Matrix *Matrix_clone(const Matrix *matrix);
/**
 *
 * @param matrix -> Matrix to be taken a sub-Matrix
 * @param initial_row -> row that will be the row-0 of new Matrix
 * @param initial_col -> column that will be the column-0 of new Matrix
 * @param final_row -> row that will be the last row of new Matrix
 * @param final_col -> column that will be the last column of new Matrix
 * @return A sub-Array of Array
 */
Matrix *Matrix_sub(const Matrix *matrix, const long initial_row, const long initial_col, const long final_row, const long final_col);
/**
 * When calling this function it will clean all data from Matrix;
 * @param matrix -> The Matrix to be clean;
 */
bool Matrix_clean(Matrix *matrix);
/**
 * When calling this function, it will clean all data from Matrix and it will be deallocated;
 * @param matrix_ref -> The pointer of the Matrix to be deleted;
 */
bool Matrix_delete(Matrix **matrix_ref);
/**
 *
 * @param matrix -> Matrix to get data from position (row, col)
 * @param row -> row of data to be got
 * @param col -> col of data to be got
 * @return The data (void *) of position (row, col) of Matrix
 */
void *Matrix_get_at(const Matrix *matrix, const long row, const long col);
/**
 * When calling this function it will update the data of Matrix position (row, col)
 * @param matrix -> Matrix to update data
 * @param row -> Row to update data at
 * @param col -> Column to update data at
 * @param data -> Data to be set
 */
bool Matrix_set_at(Matrix *matrix, const long row, const long col, void *data);
/**
 *
 * @param matrix -> Matrix to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void Matrix_print(const Matrix *matrix, __TYPE_PRINT_FUNCTION_SIGNATURE__);
/**
 *
 * @param matrix -> Matrix to check if data is contained
 * @param data -> Data that will be checked if it is contained in Matrix
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if Array contains the data, false otherwise
 */
bool Matrix_contains(const Matrix *matrix, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param matrix -> Matrix to count number os occurrences of data
 * @param data -> Data that the number of occurrences will be returned
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return The number of occurrences of data in the Matrix
 */
long Matrix_count(const Matrix *matrix, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__);
/**
 *
 * @param matrix1 -> First Matrix to check equality
 * @param matrix2 -> Second Matrix to check equality
 * @param type_compare_function -> like: int (*type_compare_function)(void *data1, void *data2)
 * @return true if matrix1 == matrix2;\n false if matrix1 != matrix2
 */
bool Matrix_is_equals(const Matrix *matrix1, Matrix *matrix2, __TYPE_COMPARE_FUNCTION_SIGNATURE__);

#endif
