#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#ifdef SUPPRESS_PRINT_ERROR
    #undef SUPPRESS_PRINT_ERROR
#endif
#define SUPPRESS_PRINT_ERROR
#define SIZE_OF_DYNAMIC_QUEUE_TYPE size_of_dynamic_queue_type

extern const size_t size_of_dynamic_queue_type;

/**
* As it is a generic Data Structure, to use some of its features, one must implement three auxiliary functions:\n
* 1 - Type printing function: To print data correctly.\n
* 2 - Type convert function: As some functions returns void*, one must use a function to convert void* to type*.\n
* 3 - Type comparison function: To compare correctly data.
 */
typedef struct _dynamic_queue DynamicQueue;
/**
 *
 * @return A new DynamicQueue
 */
DynamicQueue *DynamicQueue_create();
/**
 * When calling this function it will clean all data from DynamicQueue
 * @param queue -> The DynamicQueue to be clean
 */
void DynamicQueue_clean(DynamicQueue *queue);
/**
 * When calling this function, it will clean all data from DynamicQueue and it will be deallocated
 * @param queue_ref -> The pointer of the DynamicQueue to be deleted
 */
void DynamicQueue_destroy(DynamicQueue **queue_ref);
/**
 *
 * @param queue -> DynamicQueue to check emptiness
 * @return true if: DynamicQueue is empty;\n false if: Array not empty.
 */
bool DynamicQueue_is_empty(void *queue);
/**
 * When calling this function it will add the data at tail of the DynamicQueue
 * @param queue -> DynamicQueue to add data
 * @param data -> Data to be add in DynamicQueue
 */
void DynamicQueue_enqueue(DynamicQueue *queue, void *data);
/**
 *
 * @param queue -> DynamicQueue to get data from the head
 * @return The data (void *) on head of the DynamicQueue
 */
void *DynamicQueue_peek(const DynamicQueue *queue);
/**
 * When calling this function it will remove data from head of the DynamicQueue;
 * @param queue -> DynamicQueue to remove last element;
 */
void DynamicQueue_dequeue(DynamicQueue *queue);
/**
 *
 * @param queue -> DynamicQueue to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void DynamicQueue_print(const DynamicQueue *queue, void (*type_print_function)(void * data));
/**
 *
 * @param queue -> DynamicQueue to check size
 * @return Number of elements that are allocated in DynamicQueue.
 */
size_t DynamicQueue_size(const DynamicQueue *queue);

#endif