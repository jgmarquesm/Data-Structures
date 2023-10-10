#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H
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

#define __DEFAULT_SIZE_T__ 0
#define __DEFAULT_BOOL__ false
#define __NOT_DEFAULT_BOOL__ true
#define __DEFAULT_PTR__ NULL
#define __TYPE_PRINT_FUNCTION_NAME__ type_print_func
#define __TYPE_PRINT_FUNCTION_SIGNATURE__ void (*__TYPE_PRINT_FUNCTION_NAME__)(void *data)

#define SIZE_OF_DYNAMIC_STACK_TYPE size_of_dynamic_stack_type

extern const size_t size_of_dynamic_stack_type;

/**
* As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
* 1 - Type printing function: To print data correctly.\n
* 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
* 3 - Type comparison function: To compare correctly data.
 */
typedef struct _dynamic_stack DynamicStack;
/**
 *
 * @return A new DynamicStack
 */
DynamicStack *DynamicStack_create();
/**
 * When calling this function it will clean all data from DynamicStack
 * @param S -> The DynamicStack to be clean
 */
bool DynamicStack_clean(DynamicStack *stack);
/**
 * When calling this function, it will clean all data from DynamicStack and it will be deallocated
 * @param S_ref -> The pointer of the DynamicStack to be deleted
 */
bool DynamicStack_destroy(DynamicStack **stack_ref);
/**
 *
 * @param S -> DynamicStack to check emptiness
 * @return true if: DynamicStack is empty;\n false if: Array not empty.
 */
bool DynamicStack_is_empty(void *stack);
/**
 * When calling this function it will add the data on top of DynamicStack
 * @param S -> DynamicStack to add data
 * @param data -> Data to be add in DynamicStack
 */
bool DynamicStack_push(DynamicStack *stack, void *data);
/**
 *
 * @param S -> DynamicStack to get data from top
 * @return The data (void *) on top of the DynamicStack
 */
void *DynamicStack_peek(const DynamicStack *stack);
/**
 * When calling this function it will remove data from top of the DynamicStack;
 * @param S -> DynamicStack to remove last element;
 */
void *DynamicStack_pop(DynamicStack *stack);
/**
 *
 * @param S -> DynamicStack to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void DynamicStack_print(const DynamicStack *stack, __TYPE_PRINT_FUNCTION_SIGNATURE__);
/**
 *
 * @param S -> DynamicStack to check size
 * @return Number of elements that are allocated in DynamicStack.
 */
size_t DynamicStack_size(const DynamicStack *stack);

#endif