#include <stdlib.h>
#include <stdio.h>
//#--ADD_TO_INCLUDE
#include "../include/node.h"

typedef struct _node {
    void *data;
    struct _node *prev;
    struct _node *next;
} Node;

const size_t size_of_node_type = sizeof(Node);

Node *Node_create(void *data) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_data", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Node *node = (Node *) calloc(1, size_of_node_type);
    node->data = data;
    node->prev = __DEFAULT_PTR__;
    node->next = __DEFAULT_PTR__;
    return node;
}

bool Node_destroy(Node **node_ref) {
    Node *node = *node_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_destroy", "Node", node, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    free(node);
    *node_ref = __DEFAULT_PTR__;
    return __NOT_DEFAULT_BOOL__;
}

Node *Node_get_next(Node* node) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_next", "Node", node, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_next", "Node::Next", node->next, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return node->next;
}

bool Node_set_next(Node *node, Node *next) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_set_next", "Node", node, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    node->next = next;
    return __NOT_DEFAULT_BOOL__;
}

Node *Node_get_prev(Node* node) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_prev", "Node", node, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_prev", "Node::Prev", node->prev, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return node->prev;
}

bool Node_set_prev(Node *node, Node *prev) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_set_prev", "Node", node, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    node->prev = prev;
    return __NOT_DEFAULT_BOOL__;
}

void *Node_get_data(Node* node) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_data", "Node", node, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return node->data;
}

bool Node_set_data(Node *node, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Node_set_data", "Node", node, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("Node_set_data", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    node->data = data;
    return __NOT_DEFAULT_BOOL__;
}
