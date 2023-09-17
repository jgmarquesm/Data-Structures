#ifndef STATIC_QUEUE
#define STATIC_QUEUE
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

/**
* As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
* 1 - Type printing function: To print data correctly.\n
* 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
* 3 - Type comparison function: To compare correctly data.
 */
typedef struct _static_queue StaticQueue;
/**
 *
 * @param capacity -> max number of elements to be allocated
 * @param size_of_type -> size of data type to be allocated
 * @return A new Static Queue of type and max number of elements equals to capacity
 */
StaticQueue *StaticQueue_create(const long capacity, unsigned int size_of_type);
/**
 * When calling this function it will clean all data from Queue
 * @param SQ -> The Queue to be clean
 */
void StaticQueue_clean(StaticQueue *SQ);
/**
 * When calling this function, it will clean all data from Static Queue and it will be deallocated
 * @param SQ_ref -> The pointer of the Static Queue to be deleted
 */
void StaticQueue_destroy(StaticQueue **SQ_ref);
/**
 *
 * @param SQ -> Queue to check emptiness
 * @return true if: Static Queue is empty;\n false if: Static Queue not empty.
 */
bool StaticQueue_is_empty(const StaticQueue *SQ);
/**
 *
 * @param SQ -> Queue to check fullness
 * @return true if: Static Queue is full;\n false if: Queue not full.
 */
bool StaticQueue_is_full(const StaticQueue *SQ);
/**
 * When calling this function it will add the data on tail of Static Queue
 * @param SQ -> Static Queue to add data
 * @param data -> Data to be add in Static Queue
 */
void StaticQueue_enqueue(StaticQueue *SQ, void *data);
/**
 *
 * @param SQ -> Static Queue to get data from head
 * @return The data (void *) on top of the Static Queue
 */
void *StaticQueue_peek(const StaticQueue *SQ);
/**
 * When calling this function it will remove data from head of the Static Queue;
 * @param SQ -> Static Queue to remove last element;
 */
void StaticQueue_dequeue(StaticQueue *SQ);
/**
 *
 * @param SQ -> Static Queue to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void StaticQueue_print(const StaticQueue *SQ, void (*type_print_function)(void * data));
/**
 *
 * @param SQ -> Static Queue to check size
 * @return Number of elements that are allocated in Static Queue.
 */
long StaticQueue_size(const StaticQueue *SQ);

#endif