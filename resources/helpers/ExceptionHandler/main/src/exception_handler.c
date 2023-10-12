#include "../include/exception_handler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#--ADD_TO_INCLUDE

char *_build_error_message(const char *function_name, const char* field_name, const char *final_part) {
    const char *i = "\nERROR: on function '";
    const char *m = "'.\nERROR MESSAGE: ";

    const int li = strlen(i);
    const int lfn = strlen(function_name);
    const int lm = strlen(m);
    const int lf = strlen(field_name);
    const int lfp = strlen(final_part);

    char *error_message = (char *) malloc(li+lfn+lm+lf+lfp);

    memcpy(error_message, i, li);
    memcpy(error_message+li, function_name, lfn);
    memcpy(error_message+li+lfn, m, lm);
    memcpy(error_message+li+lfn+lm, field_name, lf);
    memcpy(error_message+li+lfn+lm+lf, final_part, lfp);

    return error_message;
}

ExceptionResponse *_er_create(bool throws, char *error_message, bool suppress) {
    ExceptionResponse *exceptionResponse = (ExceptionResponse *) calloc(1, sizeof(ExceptionResponse));
    exceptionResponse->throws = throws;
    exceptionResponse->error_message = error_message;
    exceptionResponse->suppress = suppress;
    return exceptionResponse;
}

ExceptionResponse *f1(char *function, char *field, long value, bool includesZero, bool suppress) {
    bool throws = false;
    char *error_message = "";
    if ((value == 0 && !includesZero) || value < 0) {
        throws = true;
        error_message = _build_error_message(function, field, " must be positive.\n");
    }
    return _er_create(throws, error_message, suppress);
}

ExceptionResponse *f2(char *function, char *field, void *value, bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (value == NULL) {
        throws = true;
        error_message = _build_error_message(function, field, " is NULL.\n");
    }
    return _er_create(throws, error_message, suppress);
}

ExceptionResponse *f3(char *function, char *field, void *value, bool (*is_empty_function)(void *data), bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (is_empty_function(value))  {
        throws = true;
        error_message = _build_error_message(function, field, " is empty.\n");
    }
    return _er_create(throws, error_message, suppress);
}

ExceptionResponse *f4(char *function, char *field, void *value, bool (*is_full_function)(void *data), bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (is_full_function(value)) {
        throws = true;
        error_message = _build_error_message(function, field, " is full.\n");
    }
    return _er_create(throws, error_message, suppress);
}

ExceptionResponse *f5(char *function, char *field, void *value, bool (*is_sorted_function)(void *data), bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (!is_sorted_function(value)) {
        throws = true;
        error_message = _build_error_message(function, field, " is not sorted.\n");
    }
    return _er_create(throws, error_message, suppress);
}

ExceptionResponse *f6(char *function, char *field, long value, long max_index, bool suppress) {
    bool throws = false;
    char *error_message = "";
    if (value < 0 || value > max_index) {
        throws = true;
        error_message = _build_error_message(function, field, " is Out Of Bounds.\n");
    }
    return _er_create(throws, error_message, suppress);
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
