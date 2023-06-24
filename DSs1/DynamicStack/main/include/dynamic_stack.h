#ifndef DYNAMIC_STACK
#define DYNAMIC_STACK

#include <stdbool.h>
#include <stddef.h>

/**
* As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
* 1 - Type printing function: To print data correctly.\n
* 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
* 3 - Type comparison function: To compare correctly data.
 */
typedef struct _dynamic_stack Stack;
/**
 *
 * @return A new Stack
 */
Stack *Stack_create();
/**
 * When calling this function it will clean all data from Stack
 * @param S -> The Stack to be clean
 */
void Stack_clean(Stack *S);
/**
 * When calling this function, it will clean all data from Stack and it will be deallocated
 * @param S_ref -> The pointer of the Stack to be deleted
 */
void Stack_destroy(Stack **S_ref);
/**
 *
 * @param S -> Stack to check emptiness
 * @return true if: Stack is empty;\n false if: Array not empty.
 */
bool Stack_is_empty(const Stack *S);
/**
 * When calling this function it will add the data on top of Stack
 * @param S -> Stack to add data
 * @param data -> Data to be add in Stack
 */
void Stack_push(Stack *S, void *data);
/**
 *
 * @param S -> Stack to get data from top
 * @return The data (void *) on top of the Stack
 */
void *Stack_peek(const Stack *S);
/**
 * When calling this function it will remove data from top of the Stack;
 * @param S -> Stack to remove last element;
 */
void Stack_pop(Stack *S);
/**
 *
 * @param S -> Stack to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void Stack_print(const Stack *S, void (*type_print_function)(void * data));
/**
 *
 * @param S -> Stack to check size
 * @return Number of elements that are allocated in Stack.
 */
size_t Stack_size(const Stack *S);

#endif