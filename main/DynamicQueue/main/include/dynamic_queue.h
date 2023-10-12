#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H
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

#define SIZE_OF_DYNAMIC_QUEUE_TYPE size_of_dynamic_queue_type

extern const size_t size_of_dynamic_queue_type;

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
typedef struct _dynamic_queue DynamicQueue;
/**
 *
 * @return A new DynamicQueue
 */
DynamicQueue *DynamicQueue_create();
/**
 * When calling this function it will clean all data from DynamicQueue
 * @param queue -> The DynamicQueue to be clean
 * @return true if: Dynamic Queue was successfully cleaned;\n false if (queue == NULL).
 */
bool DynamicQueue_clean(DynamicQueue *queue);
/**
 * When calling this function, it will clean all data from DynamicQueue and it will be deallocated
 * @param queue_ref -> The pointer of the DynamicQueue to be deleted
 * @return true if: Dynamic Queue was successfully destroyed;\n false if (queue == NULL).
 */
bool DynamicQueue_destroy(DynamicQueue **queue_ref);
/**
 *
 * @param queue -> DynamicQueue to check emptiness
 * @return true if: queue is empty (size == 0) or queue == NULL;\n false if: queue not empty (size > 0).
 */
bool DynamicQueue_is_empty(void *queue);
/**
 * When calling this function it will add the data at tail of the DynamicQueue
 * @param queue -> DynamicQueue to add data
 * @param data -> Data to be add in DynamicQueue
 * @return true if: Data was successfully enqueued;\n false if (queue == NULL || Data == NULL).
 */
bool DynamicQueue_enqueue(DynamicQueue *queue, void *data);
/**
 *
 * @param queue -> DynamicQueue to get data from the head
 * @return The data (void *) on head of the DynamicQueue;\n NULL if (queue == NULL || queue is empty).
 */
void *DynamicQueue_peek(const DynamicQueue *queue);
/**
 * When calling this function it will remove data from head of the DynamicQueue;
 * @param queue -> DynamicQueue to remove last element;
 * @return The data (void *) on head of the DynamicQueue is it was successfully dequeued;\n NULL if (queue == NULL || queue is empty).
 */
void *DynamicQueue_dequeue(DynamicQueue *queue);
/**
 *
 * @param queue -> DynamicQueue to be printed
 * @param type_print_function -> like: void (*type_print_function)(void *data)
 */
void DynamicQueue_print(const DynamicQueue *queue, __TYPE_PRINT_FUNCTION_SIGNATURE__);
/**
 *
 * @param queue -> DynamicQueue to check size
 * @return Number of elements in the queue;\n 0 if (queue == NULL or queue is empty).
 */
size_t DynamicQueue_size(const DynamicQueue *queue);

#endif