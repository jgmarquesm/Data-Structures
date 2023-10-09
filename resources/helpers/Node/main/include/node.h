#ifndef NODE_H
#define NODE_H
#include "exception_handler.h"
//#--ADD_TO_INCLUDE

#define __DEFAULT_BOOL__ false
#define __NOT_DEFAULT_BOOL__ true
#define __DEFAULT_PTR__ NULL

#define SIZE_OF_NODE_TYPE size_of_node_type

extern const size_t size_of_node_type;

typedef struct _node Node;

Node *Node_create(void *data);

bool Node_destroy(Node **node_ref);

Node *Node_get_next(Node* node);

bool Node_set_next(Node *node, Node *next);

Node *Node_get_prev(Node* node);

bool Node_set_prev(Node *node, Node *prev);

void *Node_get_data(Node* node);

bool Node_set_data(Node *node, void *data);

#endif
