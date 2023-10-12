#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H
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

#define SIZE_OF_STATIC_QUEUE_TYPE size_of_static_queue_type

extern const size_t size_of_static_queue_type;

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
typedef struct _static_queue StaticQueue;
/**
 *
 * @param capacity -> max number of elements to be allocated
 * @param size_of_type -> size of data type to be allocated
 * @return If capacity > 0, a new StaticQueue of type and max number of elements equals to capacity.\n NULL: Otherwise.
 */
StaticQueue *StaticQueue_create(const long capacity, unsigned int size_of_type);
/**
 * When calling this function it will clean all data from Queue
 * @param queue -> The Queue to be clean
 * @return true if: Static Queue was successfully cleaned;\n false if (queue == NULL).
 */
bool StaticQueue_clean(StaticQueue *queue);
/**
 * When calling this function, it will clean all data from Static Queue and it will be deallocated
 * @param queue_ref -> The pointer of the Static Queue to be deleted
 * @return true if: Static Queue was successfully destroyed;\n false if (queue == NULL).
 */
bool StaticQueue_destroy(StaticQueue **queue_ref);
/**
 *
 * @param queue -> Queue to check emptiness
 * @return true if: queue is empty (size == 0) or queue == NULL;\n false if: queue not empty (size > 0).
 */
bool StaticQueue_is_empty(void *queue);
/**
 *
 * @param queue -> Queue to check fullness
 * @return true if: queue is full (size == capacity);\n false if: queue is not full (size \<= capacity) or queue == NULL.
 */
bool StaticQueue_is_full(void *queue);
/**
 * When calling this function it will add the data on tail of Static Queue
 * @param queue -> Static Queue to add data
 * @param data -> Data to be add in Static Queue
 * @return true if: Data was successfully enqueued;\n false if (queue == NULL || Data == NULL || queue is not full).
 */
bool StaticQueue_enqueue(StaticQueue *queue, void *data);
/**
 *
 * @param queue -> Static Queue to get data from head
 * @return The data (void *) on head of the StaticQueue;\n NULL if (queue == NULL || queue is empty).
 */
void *StaticQueue_peek(const StaticQueue *queue);
/**
 * When calling this function it will remove data from head of the Static Queue;
 * @param queue -> Static Queue to remove last element;
 * @return true if Data was successfully dequeued;\n false if (queue == NULL || queue is empty).
 */
bool StaticQueue_dequeue(StaticQueue *queue);
/**
 *
 * @param queue -> Static Queue to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void StaticQueue_print(const StaticQueue *queue, __TYPE_PRINT_FUNCTION_SIGNATURE__);
/**
 *
 * @param queue -> Static Queue to check size
 * @return Number of elements in the queue;\n 0 if (queue == NULL or queue is empty).
 */
long StaticQueue_size(const StaticQueue *queue);

#endif