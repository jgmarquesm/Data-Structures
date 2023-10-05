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
            ExceptionHandler_is_null("Node_get_data", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Node *node = (Node *) calloc(1, sizeof(Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

bool Node_destroy(Node **node_ref) {
    Node *node = *node_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_destroy", "Node", node, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    free(node);
    *node_ref = NULL;
    return true;
}

Node *Node_get_next(Node* node) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_next", "Node", node, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_next", "Node::Next", node->next, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return node->next;
}

bool Node_set_next(Node *node, Node *next) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_set_next", "Node", node, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    node->next = next;
    return true;
}

Node *Node_get_prev(Node* node) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_prev", "Node", node, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_prev", "Node::Prev", node->prev, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return node->prev;
}

bool Node_set_prev(Node *node, Node *prev) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_set_prev", "Node", node, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    node->prev = prev;
    return true;
}

void *Node_get_data(Node* node) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_get_data", "Node", node, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return node->data;
}

bool Node_set_data(Node *node, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Node_set_data", "Node", node, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("Node_set_data", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    node->data = data;
    return true;
}
