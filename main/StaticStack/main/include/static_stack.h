#ifndef STATIC_STACK
#define STATIC_STACK
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

/**
* As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
* 1 - Type printing function: To print data correctly.\n
* 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
* 3 - Type comparison function: To compare correctly data.
 */
typedef struct _static_stack StaticStack;
/**
 *
 * @param capacity -> max number of elements to be allocated
 * @param size_of_type -> size of data type to be allocated
 * @return A new StaticStack of type and max number of elements equals to capacity
 */
StaticStack *StaticStack_create(const long capacity, unsigned int size_of_type);
/**
 * When calling this function it will clean all data from Stack
 * @param SS -> The array to be clean
 */
void StaticStack_clean(StaticStack *SS);
/**
 * When calling this function, it will clean all data from StaticStack and it will be deallocated
 * @param SS_ref -> The pointer of the StaticStack to be deleted
 */
void StaticStack_destroy(StaticStack **SS_ref);
/**
 *
 * @param SS -> Stack to check emptiness
 * @return true if: StaticStack is empty;\n false if: Array not empty.
 */
bool StaticStack_is_empty(const StaticStack *SS);
/**
 *
 * @param SS -> Stack to check fullness
 * @return true if: StaticStack is full;\n false if: Array not full.
 */
bool StaticStack_is_full(const StaticStack *SS);
/**
 * When calling this function it will add the data on top of StaticStack
 * @param SS -> StaticStack to add data
 * @param data -> Data to be add in StaticStack
 */
void StaticStack_push(StaticStack *SS, void *data);
/**
 *
 * @param SS -> StaticStack to get data from top
 * @return The data (void *) on top of the StaticStack
 */
void *StaticStack_peek(const StaticStack *SS);
/**
 * When calling this function it will remove data from top of the StaticStack;
 * @param SS -> StaticStack to remove last element;
 */
void StaticStack_pop(StaticStack *SS);
/**
 *
 * @param SS -> StaticStack to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void StaticStack_print(const StaticStack *SS, void (*type_print_function)(void * data));
/**
 *
 * @param SS -> StaticStack to check size
 * @return Number of elements that are allocated in StaticStack.
 */
long StaticStack_size(const StaticStack *SS);

#endif