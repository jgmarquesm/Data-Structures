#include "../include/node.h"
#include "../include/exception_handler.h"
#include <stdlib.h>
#include <stdio.h>
//#--ADD_TO_INCLUDE

typedef struct _node {
    void *data;
    struct _node *prev;
    struct _node *next;
} Node;

Node *Node_create(void *data) {
    Node *node = (Node *) calloc(1, sizeof(Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void Node_destroy(Node **node_ref) {
    Node *node = *node_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_destroy", "node", node)
        )
    ) {
        return;
    }
    free(node);
    *node_ref = NULL;
}

Node *Node_get_next(Node* node) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Node_get_next", "node", node),
            ExceptionHandler_is_null("Node_get_next", "node.next", node->next)
        )
    ) {
        return NULL;
    }
    return node->next;
}

void Node_set_next(Node *node, Node *next) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_set_next", "node", node)
        )
    ) {
        return;
    }
    node->next = next;
}

Node *Node_get_prev(Node* node) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Node_get_prev", "node", node),
            ExceptionHandler_is_null("Node_get_prev", "node.prev", node->prev)
        )
    ) {
        return NULL;
    }
    return node->prev;
}

void Node_set_prev(Node *node, Node *prev) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_set_prev", "node", node)
        )
    ) {
        return;
    }
    node->prev = prev;
}

void *Node_get_data(Node* node) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("Node_get_data", "node", node),
            ExceptionHandler_is_null("Node_get_data", "node.data", node->data)
        )
    ) {
        return NULL;
    }
    return node->data;
}

void Node_set_data(Node *node, void *data) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("Node_set_data", "node", node)
        )
    ) {
        return;
    }
    node->data = data;
}
