#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>

// See: https://modelingwithdata.org/arch/00000022.htm
#define function_declaration(type, name) \
         type variadic_##name(variadic_type_##name args)
#define variadic_declare(type, name, ...) \
        typedef struct {            \
                    __VA_ARGS__         \
                } variadic_type_##name;     \
    function_declaration(type, name);
#define set_var(arg, value) arg = args.arg ? args.arg : (value);
#define function_link(name,...) \
        variadic_##name((variadic_type_##name) {__VA_ARGS__})

typedef struct _exception_response {
    bool throws;
    char *error_message;
    bool suppress;
} ExceptionResponse;

ExceptionResponse *ExceptionHandler_is_non_positive(char *function, char *field, long value, bool includesZero, bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_non_positive, char *function; char *field; long value; bool includesZero; bool suppress;)
#define ExceptionHandler_is_non_positive(...) function_link(ExceptionHandler_is_non_positive,__VA_ARGS__)

ExceptionResponse *ExceptionHandler_is_null(char *function, char *field, void *value, bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_null, char *function; char *field; void *value; bool suppress;)
#define ExceptionHandler_is_null(...) function_link(ExceptionHandler_is_null,__VA_ARGS__)

ExceptionResponse *ExceptionHandler_is_empty(char *function, char *field, void *value, bool (*is_empty_function)(void *data), bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_empty, char *function; char *field; void *value; bool (*function_to_apply)(void *data); bool suppress;)
#define ExceptionHandler_is_empty(...) function_link(ExceptionHandler_is_empty,__VA_ARGS__)

ExceptionResponse *ExceptionHandler_is_full(char *function, char *field, void *value, bool (*is_full_function)(void *data), bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_full, char *function; char *field; void *value; bool (*function_to_apply)(void *data); bool suppress;)
#define ExceptionHandler_is_full(...) function_link(ExceptionHandler_is_full,__VA_ARGS__)

ExceptionResponse *ExceptionHandler_is_not_sorted(char *function, char *field, void *value, bool (*is_sorted_function)(void *data), bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_not_sorted, char *function; char *field; void *value; bool (*function_to_apply)(void *data); bool suppress;)
#define ExceptionHandler_is_not_sorted(...) function_link(ExceptionHandler_is_not_sorted,__VA_ARGS__)

ExceptionResponse *ExceptionHandler_is_out_of_bounds(char *function, char *field, long value, long max_index, bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_out_of_bounds, char *function; char *field; long value; long max_index; bool suppress;)
#define ExceptionHandler_is_out_of_bounds(...) function_link(ExceptionHandler_is_out_of_bounds,__VA_ARGS__)

bool anyThrows(int argc, ExceptionResponse *er, ...);

#endif
