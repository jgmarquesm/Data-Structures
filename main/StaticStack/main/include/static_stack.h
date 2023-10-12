#ifndef STATIC_STACK_H
#define STATIC_STACK_H
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
#define __TYPE_PRINT_FUNCTION_NAME__ type_print_func
#define __TYPE_PRINT_FUNCTION_SIGNATURE__ void (*__TYPE_PRINT_FUNCTION_NAME__)(void *data)

#define SIZE_OF_STATIC_STACK_TYPE size_of_static_stack_type

extern const size_t size_of_static_stack_type;

/**
 * @remark
 * As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
 *
 * 1 - Type printing function: To print data correctly.\n
 * @example void (*type_print_function)(void *data)
 *
 * 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type.\n
 * @example type (*type_convert_function)(void * data)
 *
 * 3 - Type comparison function: To compare data correctly.\n
 * @example int (*type_compare_function)(void *data1, void *data2)
 */
typedef struct _static_stack StaticStack;
/**
 *
 * @param capacity -> max number of elements to be allocated
 * @param size_of_type -> size of data type to be allocated
 * @return If capacity > 0, a new StaticStack of type and max number of elements equals to capacity.\n NULL: Otherwise.
 */
StaticStack *StaticStack_create(const long capacity, unsigned int size_of_type);
/**
 * When calling this function it will clean all data from Stack
 * @param stack -> The array to be clean
 * @return true if: Static Stack was successfully cleaned;\n false if (stack == NULL).
 */
bool StaticStack_clean(StaticStack *stack);
/**
 * When calling this function, it will clean all data from StaticStack and it will be deallocated
 * @param stack_ref -> The pointer of the StaticStack to be deleted
 * @return true if: Static Stack was successfully destroyed;\n false if (stack == NULL).
 */
bool StaticStack_destroy(StaticStack **stack_ref);
/**
 *
 * @param stack -> Stack to check emptiness
 * @return true if: stack is empty (size == 0) or stack == NULL;\n false if: stack not empty (size > 0).
 */
bool StaticStack_is_empty(void *stack);
/**
 *
 * @param stack -> Stack to check fullness
 * @return true if: stack is full (size == capacity);\n false if: stack is not full (size <= capacity) or stack == NULL.
 */
bool StaticStack_is_full(void *stack);
/**
 * When calling this function it will add the data on top of StaticStack
 * @param stack -> StaticStack to add data
 * @param data -> Data to be add in StaticStack
 * @return true if: Data was successfully pushed;\n false if (stack == NULL || Data == NULL || stack is not full).
 */
bool StaticStack_push(StaticStack *stack, void *data);
/**
 *
 * @param stack -> StaticStack to get data from top
 * @return The data (void *) on top of the StaticStack;\n NULL if (stack == NULL || stack is empty).
 */
void *StaticStack_peek(const StaticStack *stack);
/**
 * When calling this function it will remove data from top of the StaticStack;
 * @param stack -> StaticStack to remove last element;
 * @return The data (void *) on top of the StaticStack if it was successfully popped;\n NULL if (stack == NULL || stack is empty).
 */
void *StaticStack_pop(StaticStack *stack);
/**
 *
 * @param stack -> StaticStack to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void StaticStack_print(const StaticStack *stack, __TYPE_PRINT_FUNCTION_SIGNATURE__);
/**
 *
 * @param stack -> StaticStack to check size
 * @return Number of elements in the stack;\n 0 if (stack == NULL or stack is empty).
 */
long StaticStack_size(const StaticStack *stack);

#endif