#include "../include/exception_handler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#--ADD_TO_INCLUDE


ExceptionResponse *ExceptionHandler_create(bool throws, char *error_message, bool suppress) {
    ExceptionResponse *exceptionResponse = (ExceptionResponse *) calloc(1, sizeof(ExceptionResponse));
    exceptionResponse->throws = throws;
    exceptionResponse->error_message = error_message;
    exceptionResponse->suppress = suppress;
    return exceptionResponse;
}

char *ExceptionHandler_build_error_message(const char *function_name, const char* field_name, const char *error_message_core) {
    const char *init_msg = "\nERROR: on function '";
    const char *middle_msg = "'.\nERROR MESSAGE: ";

    const int init_msg_len = strlen(init_msg);
    const int function_name_len = strlen(function_name);
    const int middle_msg_len = strlen(middle_msg);
    const int field_name_len = strlen(field_name);
    const int error_msg_core_len = strlen(error_message_core);

    char *error_message = (char *) malloc(init_msg_len+function_name_len+middle_msg_len+field_name_len+error_msg_core_len);

    memcpy(error_message, init_msg, init_msg_len);
    memcpy(error_message+init_msg_len, function_name, function_name_len);
    memcpy(error_message+init_msg_len+function_name_len, middle_msg, middle_msg_len);
    memcpy(error_message+init_msg_len+function_name_len+middle_msg_len, field_name, field_name_len);
    memcpy(error_message+init_msg_len+function_name_len+middle_msg_len+field_name_len, error_message_core, error_msg_core_len);

    return error_message;
}

ExceptionResponse *f1(char *function, char *field, long value, bool includesZero, bool suppress) {
    bool throws = false;
    char *error_message = "";
    if ((value == 0 && !includesZero) || value < 0) {
        throws = true;
        error_message = ExceptionHandler_build_error_message(function, field, " must be positive.\n");
    }
    return ExceptionHandler_create(throws, error_message, suppress);
}

ExceptionResponse *f2(char *function, char *field, void *value, bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (value == NULL) {
        throws = true;
        error_message = ExceptionHandler_build_error_message(function, field, " is NULL.\n");
    }
    return ExceptionHandler_create(throws, error_message, suppress);
}

ExceptionResponse *f3(char *function, char *field, void *value, bool (*is_empty_function)(void *data), bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (is_empty_function(value))  {
        throws = true;
        error_message = ExceptionHandler_build_error_message(function, field, " is empty.\n");
    }
    return ExceptionHandler_create(throws, error_message, suppress);
}

ExceptionResponse *f4(char *function, char *field, void *value, bool (*is_full_function)(void *data), bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (is_full_function(value)) {
        throws = true;
        error_message = ExceptionHandler_build_error_message(function, field, " is full.\n");
    }
    return ExceptionHandler_create(throws, error_message, suppress);
}

ExceptionResponse *f5(char *function, char *field, void *value, bool (*is_sorted_function)(void *data), bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (!is_sorted_function(value)) {
        throws = true;
        error_message = ExceptionHandler_build_error_message(function, field, " is not sorted.\n");
    }
    return ExceptionHandler_create(throws, error_message, suppress);
}

ExceptionResponse *f6(char *function, char *field, long value, long max_index, bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (value < 0 || value > max_index) {
        throws = true;
        error_message = ExceptionHandler_build_error_message(function, field, " is Out Of Bounds.\n");
    }
    return ExceptionHandler_create(throws, error_message, suppress);
}

function_declaration(ExceptionResponse *, ExceptionHandler_is_non_positive) {
    char *function = args.function;
    char *field = args.field;
    long value = args.value;
    bool set_var(includesZero, false)
    bool set_var(suppress, false)
    return f1(function, field, value, includesZero, suppress);
}

function_declaration(ExceptionResponse *, ExceptionHandler_is_null) {
    char *function = args.function;
    char *field = args.field;
    void *value = args.value;
    bool set_var(suppress, false)
    return f2(function, field, value, suppress);
}

function_declaration(ExceptionResponse *, ExceptionHandler_is_empty) {
    char *function = args.function;
    char *field = args.field;
    void *value = args.value;
    bool (* function_to_apply)(void *) = args.function_to_apply;
    bool set_var(suppress, false)
    return f3(function, field, value, function_to_apply, suppress);
}

function_declaration(ExceptionResponse *, ExceptionHandler_is_full) {
    char *function = args.function;
    char *field = args.field;
    void *value = args.value;
    bool (* function_to_apply)(void *) = args.function_to_apply;
    bool set_var(suppress, false)
    return f4(function, field, value, function_to_apply, suppress);
}

function_declaration(ExceptionResponse *, ExceptionHandler_is_not_sorted) {
    char *function = args.function;
    char *field = args.field;
    void *value = args.value;
    bool (* function_to_apply)(void *) = args.function_to_apply;
    bool set_var(suppress, false)
    return f5(function, field, value, function_to_apply, suppress);
}

function_declaration(ExceptionResponse *, ExceptionHandler_is_out_of_bounds) {
    char *function = args.function;
    char *field = args.field;
    long value = args.value;
    long max_index = args.max_index;
    bool set_var(suppress, false)
    return f6(function, field, value, max_index, suppress);
}

bool anyThrows(int argc, ExceptionResponse *er, ...) {
    if (er->throws) {
        if (!er->suppress) fprintf(stderr, "%s", er->error_message);
        return true;
    } else {
        if (argc == 1) return false;
        va_list args;
        va_start(args, er);
        ExceptionResponse *e;
        for (int i = 1; i < argc; i++) {
            e = va_arg(args, ExceptionResponse *);
            if (e->throws) {
                if (!e->suppress) fprintf(stderr, "%s", e->error_message);
                return true;
            }
        }
        va_end(args);
    }
    return false;
}
