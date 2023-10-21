#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>

#define __SUPPRESS_PRINT_ERROR__ false

// See: https://modelingwithdata.org/arch/00000022.htm
#define function_declaration(type, name) \
         type variadic_##name(variadic_type_##name args)
#define variadic_declare(type, name, ...) \
        typedef struct {            \
                    __VA_ARGS__         \
                } variadic_type_##name;     \
    function_declaration(type, name);
#define set_var(arg, value) arg = args.arg ? args.arg : (value);
#define function_link(name, ...) \
        variadic_##name((variadic_type_##name) {__VA_ARGS__})

typedef struct _exception_response {
    bool throws;
    char *error_message;
    bool suppress;
} ExceptionResponse;

/**
 *
 * @param throws
 * @param error_message
 * @param suppress
 * @return
 */
ExceptionResponse *ExceptionHandler_create(bool throws, char *error_message, bool suppress);
/**
 *
 * @param function_name
 * @param field_name
 * @param error_message_core
 * @return The error message
 */
char *ExceptionHandler_build_error_message(const char *function_name, const char* field_name, const char *error_message_core);
/**
 *
 * @param function -> Function that throws (or not) the Exception.
 * @param field -> Field Name to verify the condition of throw.
 * @param value -> Value of the Field to verify the condition of throw.
 * @param includesZero (Optional parameter. Default Value: false) flag to include zero as positive. If false, zero is non positive, else zero is positive.
 * @param suppress -> (Optional parameter. Default Value: false) Flag to suppress the print of error message if exception throws.
 * @return An ExceptionResponse that throws if Value satisfies the condition of throw;\n An ExceptionResponse that not throws if Value does not satisfies the condition of throw.
 *
 * @remark
 * Condition of Throw:\n
 * ((value == 0 && !includesZero) || value \< 0) == true
 */
ExceptionResponse *ExceptionHandler_is_non_positive(char *function, char *field, long value, bool includesZero, bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_non_positive, char *function; char *field; long value; bool includesZero; bool suppress;)
#define ExceptionHandler_is_non_positive(...) function_link(ExceptionHandler_is_non_positive, __VA_ARGS__)
/**
 *
 * @param function -> Function that throws (or not) the Exception.
 * @param field -> Field Name to verify the condition of throw.
 * @param value -> Value of the Field to verify the condition of throw.
 * @param suppress -> (Optional parameter. Default Value: false) Flag to suppress the print of error message if exception throws.
 * @return An ExceptionResponse that throws if Value satisfies the condition of throw;\n An ExceptionResponse that not throws if Value does not satisfies the condition of throw.
 *
 * @remark
 * Condition of Throw:\n
 * value == NULL
 */
ExceptionResponse *ExceptionHandler_is_null(char *function, char *field, void *value, bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_null, char *function; char *field; void *value; bool suppress;)
#define ExceptionHandler_is_null(...) function_link(ExceptionHandler_is_null, __VA_ARGS__)
/**
 *
 * @param function -> Function that throws (or not) the Exception.
 * @param field -> Field Name to verify the condition of throw.
 * @param value -> Value of the Field to verify the condition of throw.
 * @param is_empty_function -> Function that verifies the Emptiness. Like: bool (*is_empty_function)(void *data)
 * @param suppress -> (Optional parameter. Default Value: false) Flag to suppress the print of error message if exception throws.
 * @return An ExceptionResponse that throws if Value satisfies the condition of throw;\n An ExceptionResponse that not throws if Value does not satisfies the condition of throw.
 *
 * @remark
 * Condition of Throw:\n
 * is_empty_function(value) == true
 */
ExceptionResponse *ExceptionHandler_is_empty(char *function, char *field, void *value, bool (*is_empty_function)(void *data), bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_empty, char *function; char *field; void *value; bool (*function_to_apply)(void *data); bool suppress;)
#define ExceptionHandler_is_empty(...) function_link(ExceptionHandler_is_empty, __VA_ARGS__)
/**
 *
 * @param function -> Function that throws (or not) the Exception.
 * @param field -> Field Name to verify the condition of throw.
 * @param value -> Value of the Field to verify the condition of throw.
 * @param is_full_function -> Function that verifies the Fullness. Like: bool (*is_full_function)(void *data)
 * @param suppress -> (Optional parameter. Default Value: false) Flag to suppress the print of error message if exception throws.
 * @return An ExceptionResponse that throws if Value satisfies the condition of throw;\n An ExceptionResponse that not throws if Value does not satisfies the condition of throw.
 *
 * @remark
 * Condition of Throw:\n
 * is_full_function(value) == true
 */
ExceptionResponse *ExceptionHandler_is_full(char *function, char *field, void *value, bool (*is_full_function)(void *data), bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_full, char *function; char *field; void *value; bool (*function_to_apply)(void *data); bool suppress;)
#define ExceptionHandler_is_full(...) function_link(ExceptionHandler_is_full, __VA_ARGS__)
/**
 *
 * @param function -> Function that throws (or not) the Exception.
 * @param field -> Field Name to verify the condition of throw.
 * @param value -> Value of the Field to verify the condition of throw.
 * @param is_sorted_function -> Function that verifies the Assortment. Like: bool (*is_sorted_function)(void *data)
 * @param suppress -> (Optional parameter. Default Value: false) Flag to suppress the print of error message if exception throws.
 * @return An ExceptionResponse that throws if Value satisfies the condition of throw;\n An ExceptionResponse that not throws if Value does not satisfies the condition of throw.
 *
 * @remark
 * Condition of Throw:\n
 * is_sorted_function(value) == false
 */
ExceptionResponse *ExceptionHandler_is_not_sorted(char *function, char *field, void *value, bool (*is_sorted_function)(void *data), bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_not_sorted, char *function; char *field; void *value; bool (*function_to_apply)(void *data); bool suppress;)
#define ExceptionHandler_is_not_sorted(...) function_link(ExceptionHandler_is_not_sorted, __VA_ARGS__)
/**
 *
 * @param function -> Function that throws (or not) the Exception.
 * @param field -> Field Name to verify the condition of throw.
 * @param value -> Value of the Field to verify the condition of throw.
 * @param max_index -> Max index allowed.
 * @param suppress -> (Optional parameter. Default Value: false) Flag to suppress the print of error message if exception throws.
 * @return An ExceptionResponse that throws if Value satisfies the condition of throw;\n An ExceptionResponse that not throws if Value does not satisfies the condition of throw.
 *
 * @remark
 * Condition of Throw:\n
 * (value \< 0 || value > max_index) == true
 */
ExceptionResponse *ExceptionHandler_is_out_of_bounds(char *function, char *field, long value, long max_index, bool suppress);
variadic_declare(ExceptionResponse *, ExceptionHandler_is_out_of_bounds, char *function; char *field; long value; long max_index; bool suppress;)
#define ExceptionHandler_is_out_of_bounds(...) function_link(ExceptionHandler_is_out_of_bounds, __VA_ARGS__)
/**
 *
 * @param argc -> Number of ExceptionHandlers to verify if throws.
 * @param er -> First ExceptionHandler to verify (required)
 * @param ... -> Others (how many you want) ExceptionHandlers to verify
 * @return true if any of them throws;\n false if none throws.
 */
bool anyThrows(int argc, ExceptionResponse *er, ...);

#endif
