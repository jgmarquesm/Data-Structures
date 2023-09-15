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
typedef struct _dynamic_queue Queue;
/**
 *
 * @return A new Queue
 */
Queue *Queue_create();
/**
 * When calling this function it will clean all data from Queue
 * @param queue -> The Queue to be clean
 */
void Queue_clean(Queue *queue);
/**
 * When calling this function, it will clean all data from Queue and it will be deallocated
 * @param queue_ref -> The pointer of the Queue to be deleted
 */
void Queue_destroy(Queue **queue_ref);
/**
 *
 * @param queue -> Queue to check emptiness
 * @return true if: Queue is empty;\n false if: Array not empty.
 */
bool Queue_is_empty(void *queue);
/**
 * When calling this function it will add the data at tail of the Queue
 * @param queue -> Queue to add data
 * @param data -> Data to be add in Queue
 */
void Queue_enqueue(Queue *queue, void *data);
/**
 *
 * @param queue -> Queue to get data from the head
 * @return The data (void *) on head of the Queue
 */
void *Queue_peek(const Queue *queue);
/**
 * When calling this function it will remove data from head of the Queue;
 * @param queue -> Queue to remove last element;
 */
void Queue_dequeue(Queue *queue);
/**
 *
 * @param queue -> Queue to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void Queue_print(const Queue *queue, void (*type_print_function)(void * data));
/**
 *
 * @param queue -> Queue to check size
 * @return Number of elements that are allocated in Queue.
 */
size_t Queue_size(const Queue *queue);

#endif