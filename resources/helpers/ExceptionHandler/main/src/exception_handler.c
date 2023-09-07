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

ExceptionResponse *_er_create(bool throws, char *error_message) {
    ExceptionResponse *exceptionResponse = (ExceptionResponse *) calloc(1, sizeof(ExceptionResponse));
    exceptionResponse->throws = throws;
    exceptionResponse->error_message = error_message;
    return exceptionResponse;
}

ExceptionResponse *ExceptionHandler_is_non_positive(char *function, char *field, long value, bool includesZero) {
    bool throws = false;
    char *error_message = "";
    if ((value <= 0 && !includesZero) || (value < 0 && includesZero)) {
        throws = true;
        error_message = _build_error_message(function, field, " must be positive.\n");
    }
    return _er_create(throws, error_message);
}

ExceptionResponse *ExceptionHandler_is_null(char *function, char *field, void *value) {
    bool throws = false;
    char *error_message = "";
    if (value == NULL) {
        throws = true;
        error_message = _build_error_message(function, field, " is NULL.\n");
    }
    return _er_create(throws, error_message);
}

ExceptionResponse *ExceptionHandler_is_empty(char *function, char *field, void *value, bool (*is_empty_function)(void *data)) {
    bool throws = false;
    char *error_message = "";
    if (is_empty_function(value))  {
        throws = true;
        error_message = _build_error_message(function, field, " is empty.\n");
    }
    return _er_create(throws, error_message);
}

ExceptionResponse *ExceptionHandler_is_full(char *function, char *field, void *value, bool (*is_full_function)(void *data)) {
    bool throws = false;
    char *error_message = "";
    if (is_full_function(value)) {
        throws = true;
        error_message = _build_error_message(function, field, " is full.\n");
    }
    return _er_create(throws, error_message);
}

bool anyThrows(int argc, ExceptionResponse *er, ...) {
    if (er->throws) {
        fprintf(stderr, "%s", er->error_message);
        return true;
    } else {
        if (argc == 1) return false;
        va_list args;
        va_start(args, er);
        ExceptionResponse *e;
        for (int i = 1; i < argc; i++) {
            e = va_arg(args, ExceptionResponse *);
            if (e->throws) {
                fprintf(stderr, "%s", e->error_message);
                return true;
            }
        }
        va_end(args);
    }
    return false;
}
