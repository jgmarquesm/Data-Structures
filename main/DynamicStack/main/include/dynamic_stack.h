#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#ifdef __DEFAULT_SIZE_T__
    #undef __DEFAULT_SIZE_T__
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
typedef struct _dynamic_stack DynamicStack;
/**
 *
 * @return A new DynamicStack
 */
DynamicStack *DynamicStack_create();
/**
 * When calling this function it will clean all data from DynamicStack
 * @param stack -> The DynamicStack to be clean
 * @return true if: Dynamic Stack was successfully cleaned;\n false if (stack == NULL).
 */
bool DynamicStack_clean(DynamicStack *stack);
/**
 * When calling this function, it will clean all data from DynamicStack and it will be deallocated
 * @param stack_ref -> The pointer of the DynamicStack to be deleted
 * @return true if: Dynamic Stack was successfully destroyed;\n false if (stack == NULL).
 */
bool DynamicStack_destroy(DynamicStack **stack_ref);
/**
 *
 * @param stack -> DynamicStack to check emptiness
 * @return true if: stack is empty (size == 0) or stack == NULL;\n false if: stack not empty (size > 0).
 */
bool DynamicStack_is_empty(void *stack);
/**
 * When calling this function it will add the data on top of DynamicStack
 * @param stack -> DynamicStack to add data
 * @return true if: Data was successfully pushed;\n false if (stack == NULL || Data == NULL).
 */
bool DynamicStack_push(DynamicStack *stack, void *data);
/**
 *
 * @param stack -> DynamicStack to get data from top
 * @return The data (void *) on top of the DynamicStack;\n NULL if (stack == NULL || stack is empty).
 */
void *DynamicStack_peek(const DynamicStack *stack);
/**
 * When calling this function it will remove data from top of the DynamicStack;
 * @param stack -> DynamicStack to remove last element;
 * @return The data (void *) on top of the DynamicStack if it was successfully popped;\n NULL if (stack == NULL || stack is empty).
 */
void *DynamicStack_pop(DynamicStack *stack);
/**
 *
 * @param stack -> DynamicStack to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void DynamicStack_print(const DynamicStack *stack, __TYPE_PRINT_FUNCTION_SIGNATURE__);
/**
 *
 * @param stack -> DynamicStack to check size
 * @return Number of elements in the stack;\n 0 if (stack == NULL or stack is empty).
 */
size_t DynamicStack_size(const DynamicStack *stack);

#endif