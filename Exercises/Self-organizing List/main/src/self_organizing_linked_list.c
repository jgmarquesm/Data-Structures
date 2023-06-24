#include "../include/self_organizing_linked_list.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node {
    struct _node *prev;
    struct _node *next;
    int count;
    Product *product;
} Node;

Node *Node_create(const int serial, const char *name, const float price) {
    Node *node = (Node *) calloc(1, sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    node->product = Product_create(serial, name, price);
    node->count = 0;

    return node;
}

void Node_destroy(Node **node_ref) {
    Node *node = *node_ref;
    Product_destroy(&node->product);
    free(node);
    *node_ref = NULL;
}

int _get_serial(Product *product) {
    return Product_get_serial(product);
}

typedef struct _list {
    Node *begin;
    Node *end;
    size_t size;
    int total_cost;
} List;

bool _is_empty(List *list) {
    return list->size == 0;
}

List *List_create() {
    List *list = (List *) calloc(1, sizeof(List));
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
    list->total_cost = 0;
    return list;
}

void List_destroy(List **list_ref) {
    List *list = *list_ref;
    Node *node = list->begin;
    Node *aux_node = NULL;

    while (node != NULL) {
        aux_node = node;
        node = node->next;
        Node_destroy(&aux_node);
    }
    free(list);
    *list_ref = NULL;
}

void List_add_product(List *list, const int serial, const char *name, const float price) {
    Node *node = Node_create(serial, name, price);
    node->prev = list->end;
    if (_is_empty(list)) {
        list->begin = node;
    } else {
        list->end->next = node;
    }
    list->end = node;
    list->size++;
}

void List_print(List *list) {
    if (_is_empty(list)) {
        puts( "No Products yet.");
    }
    Node *node = list->begin;
    printf("NULL <- ");
    while (node != NULL) {
        if (list->size == 1 || node == list->end) {
            printf("%d (%d)", _get_serial(node->product), node->count);
        } else {
            printf("%d (%d) <- -> ", _get_serial(node->product), node->count);
        }
        node = node->next;
    }
    printf(" -> NULL\n\n");
}

const Product *List_get_product_with_serial(List *list, int serial) {
    Product *product = NULL;

    if (!_is_empty(list)) {
        Node *node = list->begin;
        int cost = 1;

        while (node != NULL && _get_serial(node->product) != serial) {
            cost++;
            node = node->next;
        }

        if (node != NULL) {
            node->count++;
            list->total_cost += cost;
            product = node->product;

            if (list->begin != node) {
                Node *aux_node = node->prev;
                while (aux_node != NULL && aux_node->count <= node->count) {
                    node->prev = aux_node->prev;
                    aux_node->prev = node;
                    aux_node->next = node->next;
                    node->next = aux_node;

                    if (node->prev == NULL) {
                        list->begin = node;
                    } else {
                        node->prev->next = node;
                    }

                    if (aux_node->next == NULL) {
                        list->end = aux_node;
                    } else {
                        aux_node->next->prev = aux_node;
                    }
                    aux_node = node->prev;
                }
            }
        }
    }

    return product;
}

void List_print_summary(const List *list) {
    Node *node = list->begin;
    printf("List = (");
    while (node != NULL) {
        if (list->size == 1 || list->end == node) {
            printf("%d", _get_serial(node->product));
        } else {
            printf("%d, ", _get_serial(node->product));
        }
        node = node->next;
    }
    printf(")\nTotal Cost: %d\n", list->total_cost);
}

