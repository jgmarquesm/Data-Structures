#ifndef NODE_H
#define NODE_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#include <stddef.h>
#include <stdbool.h>

#ifdef __DEFAULT_BOOL__
    #undef __DEFAULT_BOOL__
#endif
#ifdef __NOT_DEFAULT_BOOL__
    #undef __NOT_DEFAULT_BOOL__
#endif
#ifdef __DEFAULT_PTR__
    #undef __DEFAULT_PTR__
#endif

#define __DEFAULT_BOOL__ false
#define __NOT_DEFAULT_BOOL__ true
#define __DEFAULT_PTR__ NULL

#define SIZE_OF_NODE_TYPE size_of_node_type

extern const size_t size_of_node_type;

typedef struct _node Node;
/**
 *
 * @param data -> Data to create a Node with;
 * @return If Data != NULL, a new Node with data.\n NULL: Otherwise.
 */
Node *Node_create(void *data);
/**
 *
 * @param node_ref -> The pointer of the Node to be destroyed;
 * @return true if: Node was successfully destroyed;\n false if (Node == NULL).
 */
bool Node_destroy(Node **node_ref);
/**
 *
 * @param node -> Node to get Next Node.
 * @return Node::Next;\n NULL if (Node == NULL || Node::Next == NULL).
 */
Node *Node_get_next(Node* node);
/**
 *
 * @param node -> Node to set Next.
 * @param next -> Node to be set as Next.
 * @return true if Node::Next was successfully set;\n false if Node == NULL.
 */
bool Node_set_next(Node *node, Node *next);
/**
 *
 * @param node -> Node to get Prev Node.
 * @return Node::Prev;\n NULL if (Node == NULL || Node::Prev == NULL).
 */
Node *Node_get_prev(Node* node);
/**
 *
 * @param node -> Node to set Prev.
 * @param prev -> Node to be set as Prev.
 * @return true if Node::Prev was successfully set;\n false if Node == NULL.
 */
bool Node_set_prev(Node *node, Node *prev);
/**
 *
 * @param node -> Node to get Data.
 * @return Data (void *) of Node;\n NULL if Node == NULL.
 */
void *Node_get_data(Node* node);
/**
 *
 * @param node -> Node to set Data.
 * @param data -> Data to be set.
 * @return true if Data was successfully set;\n false if (Node == NULL || Data == NULL).
 */
bool Node_set_data(Node *node, void *data);

#endif
