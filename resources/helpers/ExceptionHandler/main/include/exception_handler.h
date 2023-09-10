#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct _exception_response {
    bool throws;
    char *error_message;
} ExceptionResponse;

ExceptionResponse *ExceptionHandler_is_non_positive(char *function, char *field, long value, bool includesZero);

ExceptionResponse *ExceptionHandler_is_null(char *function, char *field, void *value);

ExceptionResponse *ExceptionHandler_is_empty(char *function, char *field, void *value, bool (*is_empty_function)(void *data));

ExceptionResponse *ExceptionHandler_is_full(char *function, char *field, void *value, bool (*is_full_function)(void *data));

ExceptionResponse *ExceptionHandler_is_not_sorted(char *function, char *field, void *value, bool (*is_sorted_function)(void *data));

ExceptionResponse *ExceptionHandler_is_out_of_bounds(char *function, char *field, long wanted_index, long max_index);

bool anyThrows(int argc, ExceptionResponse *er, ...);

#endif
