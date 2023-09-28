#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#ifdef SUPPRESS_PRINT_ERROR
    #undef SUPPRESS_PRINT_ERROR
#endif
#define SUPPRESS_PRINT_ERROR false
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
void DynamicStack_clean(DynamicStack *S);
/**
 * When calling this function, it will clean all data from DynamicStack and it will be deallocated
 * @param S_ref -> The pointer of the DynamicStack to be deleted
 */
void DynamicStack_destroy(DynamicStack **S_ref);
/**
 *
 * @param S -> DynamicStack to check emptiness
 * @return true if: DynamicStack is empty;\n false if: Array not empty.
 */
bool DynamicStack_is_empty(void *S);
/**
 * When calling this function it will add the data on top of DynamicStack
 * @param S -> DynamicStack to add data
 * @param data -> Data to be add in DynamicStack
 */
void DynamicStack_push(DynamicStack *S, void *data);
/**
 *
 * @param S -> DynamicStack to get data from top
 * @return The data (void *) on top of the DynamicStack
 */
void *DynamicStack_peek(const DynamicStack *S);
/**
 * When calling this function it will remove data from top of the DynamicStack;
 * @param S -> DynamicStack to remove last element;
 */
void DynamicStack_pop(DynamicStack *S);
/**
 *
 * @param S -> DynamicStack to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void DynamicStack_print(const DynamicStack *S, void (*type_print_function)(void * data));
/**
 *
 * @param S -> DynamicStack to check size
 * @return Number of elements that are allocated in DynamicStack.
 */
size_t DynamicStack_size(const DynamicStack *S);

#endif