#include <stdlib.h>
#include <stdio.h>
#include "../include/node.h"
//#--ADD_TO_INCLUDE
#include "../include/circular_doubly_linked_list.h"

#define UNSORTED 0
#define ASC 1
#define DESC -1

typedef struct _circular_doubly_linked_list {
    Node *begin;
    Node *end;
    size_t size;
    int sort_order;
} CircularDoublyLinkedList;

const size_t size_of_circular_doubly_linked_list_type = sizeof(CircularDoublyLinkedList);

void _cll_left_right_split(Node *node, Node **left_ref, Node **right_ref) {
    Node *slow = node;
    Node *fast = node;

    if(node == NULL) {
        return;
    }

    while(Node_get_next(fast) != node && Node_get_next(Node_get_next(fast)) != node) {
        fast = Node_get_next(Node_get_next(fast));
        slow = Node_get_next(slow);
    }

    if(Node_get_next(Node_get_next(fast)) == node) {
        fast = Node_get_next(fast);
    }

    *left_ref = node;
    Node_set_prev(node, slow);

    if(Node_get_next(node) != node) {
        *right_ref = Node_get_next(slow);
    }

    Node_set_prev(Node_get_next(slow), fast);
    Node_set_next(fast, Node_get_next(slow));
    Node_set_next(slow, node);
}

Node *_cll_sorted_merge_aux(Node *left, Node *right, int (*type_compare_function)(void *data1, void *data2), int order) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    if (order == ASC) {
        if (type_compare_function(Node_get_data(left), Node_get_data(right)) >= 0) {
            Node_set_next(left, _cll_sorted_merge_aux(Node_get_next(left), right, type_compare_function, order));
            Node_set_prev(Node_get_next(left), left);
            Node_set_prev(left, NULL);
            return left;
        } else {
            Node_set_next(right, _cll_sorted_merge_aux(left, Node_get_next(right), type_compare_function, order));
            Node_set_prev(Node_get_next(right), right);
            Node_set_prev(right, NULL);
            return right;
        }
    } else {
        if (type_compare_function(Node_get_data(left), Node_get_data(right)) <= 0) {
            Node_set_next(left, _cll_sorted_merge_aux(Node_get_next(left), right, type_compare_function, order));
            Node_set_prev(Node_get_next(left), left);
            Node_set_prev(left, NULL);
            return left;
        } else {
            Node_set_next(right, _cll_sorted_merge_aux(left, Node_get_next(right), type_compare_function, order));
            Node_set_prev(Node_get_next(right), right);
            Node_set_prev(right, NULL);
            return right;
        }
    }
}

Node *_cll_sorted_merge(Node *left, Node *right, int (*type_compare_function)(void *data1, void *data2), int order) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    Node *last_node;

    if (order == ASC) {
        if (type_compare_function(Node_get_data(Node_get_prev(left)), Node_get_data(Node_get_prev(right))) >= 0) {
            last_node = Node_get_prev(right);
        } else {
            last_node = Node_get_prev(left);
        }
    } else {
        if (type_compare_function(Node_get_data(Node_get_next(left)), Node_get_data(Node_get_next(right))) >= 0) {
            last_node = Node_get_prev(left);
        } else {
            last_node = Node_get_prev(right);
        }
    }

    Node_set_next(Node_get_prev(left), NULL);
    Node_set_next(Node_get_prev(right), NULL);

    Node *result = _cll_sorted_merge_aux(left, right, type_compare_function, order);
    Node_set_prev(result, last_node);
    Node_set_next(last_node, result);

    return result;
}

bool _cll_merge_sort(Node **CDLL_begin_ref, int (*type_compare_function)(void *data1, void *data2), int order) {
    Node *CDLL_begin = *CDLL_begin_ref, *left, *right;

    if (CDLL_begin == NULL || Node_get_next(CDLL_begin) == CDLL_begin) {
        return false;
    }

    if (order != ASC && order != DESC) {
        fprintf(stderr, "\nERROR: on function 'CircularDoublyLinkedList_sort_*'.\n");
        fprintf(stderr, "ERROR: Invalid sort order.\n");
        return false;
    }

    _cll_left_right_split(CDLL_begin, &left, &right);
    _cll_merge_sort(&left, type_compare_function, order);
    _cll_merge_sort(&right, type_compare_function, order);

    *CDLL_begin_ref = _cll_sorted_merge(left, right, type_compare_function, order);
    return true;
}

Node *_get_node(const CircularDoublyLinkedList *CDLL, size_t index) {
    Node *node = CDLL->begin;
    for (size_t i = 0; i < index; i++) {
        node = Node_get_next(node);
    }
    return node;
}

CircularDoublyLinkedList *CircularDoublyLinkedList_create() {
    CircularDoublyLinkedList *CDLL = (CircularDoublyLinkedList *) calloc(1, sizeof(CircularDoublyLinkedList));
    CDLL->begin = NULL;
    CDLL->end = NULL;
    CDLL->size = 0;
    CDLL->sort_order = 0;

    return CDLL;
}

bool CircularDoublyLinkedList_clean(CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularDoublyLinkedList_clean", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Node *node = CDLL->begin;
    while (node != CDLL->end) {
        Node *node_next = Node_get_next(node);
        Node_destroy(&node);
        node = node_next;
    }
    Node_destroy(&node);
    CDLL->begin = NULL;
    CDLL->end = NULL;
    CDLL->size = 0;
    CDLL->sort_order = UNSORTED;
    return true;
}

bool CircularDoublyLinkedList_destroy(CircularDoublyLinkedList **CDLL_ref) {
    CircularDoublyLinkedList *CDLL = *CDLL_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularDoublyLinkedList_destroy", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    CircularDoublyLinkedList_clean(CDLL);
    free(CDLL);
    *CDLL_ref = NULL;
    return true;
}

bool CircularDoublyLinkedList_is_empty(void *CDLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_empty", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR)
        )
    ) return true;
    return ((CircularDoublyLinkedList *) CDLL)->size == 0;
}

bool CircularDoublyLinkedList_is_sorted(void *CDLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_sorted", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    return ((CircularDoublyLinkedList *) CDLL)->sort_order != UNSORTED;
}

int CircularDoublyLinkedList_sort_order(const CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_sort_order", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_sort_order", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return UNSORTED;
    return CDLL->sort_order;
}

void CircularDoublyLinkedList_print(const CircularDoublyLinkedList *CDLL, void (*type_print_function)(void *data)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_print", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_print", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    Node *node = CDLL->begin;
    printf("LAST NODE <- -> ");
    do {
        type_print_function(Node_get_data(node));
        printf(" <- -> ");
        node = Node_get_next(node);
    } while (node != CDLL->begin);
    puts("FIRST NODE");
}

bool CircularDoublyLinkedList_add_first(CircularDoublyLinkedList *CDLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_add_first", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_add_first", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Node *node = Node_create(data);

    if (CircularDoublyLinkedList_is_empty(CDLL)) {
        CDLL->end = node;
    } else {
        Node_set_next(node, CDLL->begin);
        Node_set_prev(CDLL->begin, node);
    }
    Node_set_prev(node, CDLL->end);
    Node_set_next(CDLL->end, node);
    CDLL->begin = node;
    CDLL->size++;
    CDLL->sort_order = UNSORTED;
    return true;
}

bool CircularDoublyLinkedList_add_last(CircularDoublyLinkedList *CDLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_add_last", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_add_last", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Node *node = Node_create(data);
    if (CircularDoublyLinkedList_is_empty((void *) CDLL)) CDLL->begin = node;
    else {
        Node_set_next(CDLL->end, node);
        Node_set_prev(node, CDLL->end);
    }
    Node_set_prev(CDLL->begin, node);
    Node_set_next(node, CDLL->begin);
    CDLL->end = node;
    CDLL->size++;
    CDLL->sort_order = UNSORTED;
    return true;
}

void _cll_sorted_insert_asc(CircularDoublyLinkedList *CDLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (type_compare_function(Node_get_data(CDLL->begin), data) <= 0) {
        CircularDoublyLinkedList_add_first(CDLL, data);
        CDLL->sort_order = ASC;
        return;
    } else if (type_compare_function(Node_get_data(CDLL->end), data) >= 0) {
        CircularDoublyLinkedList_add_last(CDLL, data);
        CDLL->sort_order = ASC;
        return;
    } else {
        Node *node = CDLL->begin, *node_new = Node_create(data);
        while (node != CDLL->end && type_compare_function(data, Node_get_data(node)) < 0) {
            node = Node_get_next(node);
        }
        Node_set_next(node_new, node);
        Node_set_prev(node_new, Node_get_prev(node));
        Node_set_next(Node_get_prev(node), node_new);
        Node_set_prev(node, node_new);
        CDLL->size++;
    }
}

void _cll_sorted_insert_desc(CircularDoublyLinkedList *CDLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (type_compare_function(Node_get_data(CDLL->begin), data) >= 0) {
        CircularDoublyLinkedList_add_first(CDLL, data);
        CDLL->sort_order = DESC;
        return;
    } else if (type_compare_function(Node_get_data(CDLL->end), data) <= 0) {
        CircularDoublyLinkedList_add_last(CDLL, data);
        CDLL->sort_order = DESC;
    } else {
        Node *node = CDLL->begin, *node_new = Node_create(data);
        while (node != CDLL->end && type_compare_function(data, Node_get_data(node)) > 0) {
            node = Node_get_next(node);
        }
        Node_set_next(node_new, node);
        Node_set_prev(node_new, Node_get_prev(node));
        Node_set_next(Node_get_prev(node), node_new);
        Node_set_prev(node, node_new);
        CDLL->size++;
    }
}

void *CircularDoublyLinkedList_remove_first(CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove_first", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_remove_first", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Node *node = CDLL->begin;
    void *data = Node_get_data(node);
    if (CDLL->begin == CDLL->end) {
        CDLL->begin = CDLL->end = NULL;
    } else {
        CDLL->begin = Node_get_next(node);
        Node_set_prev(CDLL->begin, CDLL->end);
        Node_set_next(CDLL->end, CDLL->begin);
    }
    free(node);
    CDLL->size--;
    return data;
}

void *CircularDoublyLinkedList_remove_last(CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove_last", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_remove_last", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Node *node = CDLL->end;
    void *data = Node_get_data(node);
    if (CDLL->begin == CDLL->end) {
        CDLL->begin = CDLL->end = NULL;
    } else {
        CDLL->end = Node_get_prev(node);
        Node_set_next(Node_get_prev(node), Node_get_next(node));
        Node_set_prev(Node_get_next(node), Node_get_prev(node));
    }
    Node_destroy(&node);
    CDLL->size--;
    return data;
}

void *CircularDoublyLinkedList_remove_at(CircularDoublyLinkedList *CDLL, size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove_at", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_remove_at", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("CircularDoublyLinkedList_remove_at", "Index", index, CDLL->size-1, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    if (index == 0) {
        return CircularDoublyLinkedList_remove_first(CDLL);
    }
    if (index == CDLL->size-1) {
        return CircularDoublyLinkedList_remove_last(CDLL);
    }
    Node *node = CDLL->begin;
    void *data;
    for (size_t i = 0; i < index; i++) {
        node = Node_get_next(node);
    }
    Node_set_next(Node_get_prev(node), Node_get_next(node));
    Node_set_prev(Node_get_next(node), Node_get_prev(node));
    data = Node_get_data(node);
    Node_destroy(&node);
    CDLL->size--;
    return data;
}

bool CircularDoublyLinkedList_remove(CircularDoublyLinkedList *CDLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_remove", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    Node *node = CDLL->begin;
    if (type_compare_function(Node_get_data(CDLL->begin), data) == 0) {
        if (CDLL->begin == CDLL->end) {
            CDLL->begin = CDLL->end = NULL;
        } else {
            CDLL->begin = Node_get_next(node);
            Node_set_prev(CDLL->begin, CDLL->end);
            Node_set_next(CDLL->end, CDLL->begin);
        }
        Node_destroy(&node);
        CDLL->size--;
        return true;
    } else {
        node = Node_get_next(node);
        while (node != CDLL->begin && type_compare_function(Node_get_data(node), data) != 0) {
            node = Node_get_next(node);
        }
        if (node != CDLL->begin) {
            if (CDLL->end == node) {
                CDLL->end = Node_get_prev(node);
            }
            Node_set_next(Node_get_prev(node), Node_get_next(node));
            Node_set_prev(Node_get_next(node), Node_get_prev(node));
            Node_destroy(&node);
            CDLL->size--;
            return true;
        }
    }
    return false;
}

size_t CircularDoublyLinkedList_remove_all(CircularDoublyLinkedList *CDLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove_all", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove_all", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_remove_all", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;

    Node *node = CDLL->begin;
    size_t count = 0;
    while (true) {
        Node *aux_node = Node_get_next(node);
        if (type_compare_function(Node_get_data(node), data) == 0) {
            if (CDLL->begin == node) {
                if (CDLL->begin == CDLL->end) {
                    CDLL->begin = CDLL->end = NULL;
                } else {
                    CDLL->begin = Node_get_next(node);
                    Node_set_prev(CDLL->begin, CDLL->end);
                    Node_set_next(CDLL->end, CDLL->begin);
                }
            } else {
                if (node == CDLL->end) {
                    CDLL->end = Node_get_prev(node);
                }
                Node_set_next(Node_get_prev(node), Node_get_next(node));
                Node_set_prev(Node_get_next(node), Node_get_prev(node));
            }
            Node_destroy(&node);
            node = aux_node;
            CDLL->size--;
            count++;
        } else {
            if (CircularDoublyLinkedList_contains(CDLL, data)) {
                node = aux_node;
            } else {
                break;
            }
        }
    }
    return count;
}

size_t CircularDoublyLinkedList_size(const CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_size", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_size", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    return CDLL->size;
}

void *CircularDoublyLinkedList_first_element(const CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_first_element", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_first_element", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return Node_get_data(CDLL->begin);
}

void *CircularDoublyLinkedList_last_element(const CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_last_element", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_last_element", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return Node_get_data(CDLL->end);
}

void *CircularDoublyLinkedList_get(const CircularDoublyLinkedList *CDLL, size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_get", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_get", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("CircularDoublyLinkedList_get", "Index", index, CDLL->size-1, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Node *node = _get_node(CDLL, index);
    return Node_get_data(node);
}

int CircularDoublyLinkedList_count(const CircularDoublyLinkedList *CDLL, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularDoublyLinkedList_count", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_count", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_count", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    int count = 0;
    if (Node_get_data(CDLL->begin) == data) {
        count++;
    }
    Node *node = Node_get_next(CDLL->begin);
    while (node != CDLL->begin) {
        if (Node_get_data(node) == data) {
            count++;
        }
        node = Node_get_next(node);
    }
    return count;
}

bool CircularDoublyLinkedList_contains(const CircularDoublyLinkedList *CDLL, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularDoublyLinkedList_contains", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_contains", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_contains", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    if (Node_get_data(CDLL->begin) == data) {
        return true;
    }
    Node *node = Node_get_next(CDLL->begin);
    while (node != CDLL->begin) {
        if (Node_get_data(node) == data) {
            return true;
        }
        node = Node_get_next(node);
    }
    return false;
}

bool CircularDoublyLinkedList_insert_at(CircularDoublyLinkedList *CDLL, void *data, size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_insert_at", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_insert_at", "Data", data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("CircularDoublyLinkedList_insert_at", "Index", index, CDLL->size, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    if (index == 0) {
        return CircularDoublyLinkedList_add_first(CDLL, data);
    } else if (index == CDLL->size) {
        return CircularDoublyLinkedList_add_last(CDLL, data);
    }
    Node *node_new = Node_create(data);
    Node *node = CDLL->begin;
    for (size_t i = 0; i < index-1; i++) {
        node = Node_get_next(node);
    }
    Node_set_next(node_new, Node_get_next(node));
    Node_set_prev(Node_get_next(node), node_new);
    Node_set_next(node, node_new);
    Node_set_prev(node_new, node);
    CDLL->size++;
    CDLL->sort_order = UNSORTED;
    return true;
}

CircularDoublyLinkedList *CircularDoublyLinkedList_clone(const CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_clone", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_clone", "Circular Doubly Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    CircularDoublyLinkedList *clone = CircularDoublyLinkedList_create();
    Node *node = Node_get_next(CDLL->begin);
    CircularDoublyLinkedList_add_first(clone, Node_get_data(CDLL->begin));
    int count = 1;
    while (node != CDLL->begin) {
        CircularDoublyLinkedList_insert_at(clone, Node_get_data(node), count);
        count++;
        node = Node_get_next(node);
    }
    clone->sort_order = CDLL->sort_order;
    return clone;
}

CircularDoublyLinkedList *CircularDoublyLinkedList_concat(CircularDoublyLinkedList *CDLL1, CircularDoublyLinkedList *CDLL2) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_concat", "Circular Linked List 1", (void *) CDLL1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_concat", "Circular Linked List 2", (void *) CDLL2, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    if (CircularDoublyLinkedList_is_empty((void *) CDLL1)) {
        return CircularDoublyLinkedList_clone(CDLL2);
    } else if (CircularDoublyLinkedList_is_empty((void *) CDLL2)) {
        return CircularDoublyLinkedList_clone(CDLL1);
    }
    CircularDoublyLinkedList *CDLL_new = CircularDoublyLinkedList_clone(CDLL1);
    Node *node = CDLL2->begin;
    while (Node_get_next(node) != CDLL2->begin) {
        CircularDoublyLinkedList_add_last(CDLL_new, Node_get_data(node));
        node = Node_get_next(node);
    }
    CircularDoublyLinkedList_add_last(CDLL_new, Node_get_data(node));
    CDLL_new->sort_order = UNSORTED;
    return CDLL_new;
}

bool CircularDoublyLinkedList_reverse(CircularDoublyLinkedList **CDLL_ref) {
    CircularDoublyLinkedList *reversed = *CDLL_ref;
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_clone", "Circular Linked List", (void *) reversed, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_clone", "Circular Linked List", (void *) reversed, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    CircularDoublyLinkedList *clone = CircularDoublyLinkedList_clone(reversed);
    Node *node = clone->begin, *next = NULL, *prev = NULL;
    for (size_t i = 0; i < reversed->size; i++) {
        next = Node_get_next(node);
        prev = Node_get_prev(node);
        Node_set_prev(node, next);
        Node_set_next(node, prev);
        node = Node_get_next(node);
    }
    reversed->sort_order = (-1)*reversed->sort_order;
    return true;
}

bool CircularDoublyLinkedList_is_equals_strict(const CircularDoublyLinkedList *CDLL1, const CircularDoublyLinkedList *CDLL2) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_equals_strict", "Circular Linked List 1", (void *) CDLL1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_equals_strict", "Circular Linked List 2", (void *) CDLL2, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_is_equals_strict", "Circular Linked List 1", (void *) CDLL1, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_is_equals_strict", "Circular Linked List 2", (void *) CDLL2, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        ) || CDLL1->size != CDLL2->size
    ) return false;
    Node *node1 = CDLL1->begin;
    Node *node2 = CDLL2->begin;
    for (size_t i = 0; i < CDLL1->size; i++) {
        if (Node_get_data(node1) != Node_get_data(node2)) {
            return false;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return CDLL1->sort_order == CDLL2->sort_order;
}

bool CircularDoublyLinkedList_is_equals(const CircularDoublyLinkedList *CDLL1, const CircularDoublyLinkedList *CDLL2, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_equals", "Circular Linked List 1", (void *) CDLL1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_equals", "Circular Linked List 2", (void *) CDLL2, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_is_equals", "Circular Linked List 1", (void *) CDLL1, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_is_equals", "Circular Linked List 2", (void *) CDLL2, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        ) || CDLL1->size != CDLL2->size
    ) return false;
    Node *node1 = CDLL1->begin;
    Node *node2 = CDLL2->begin;
    for (size_t i = 0; i < CDLL1->size; i++) {
        if (type_compare_function(Node_get_data(node1), Node_get_data(node2)) != 0) {
            return false;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return CDLL1->sort_order == CDLL2->sort_order;
}

bool CircularDoublyLinkedList_sort_asc(CircularDoublyLinkedList **CDLL_ref, int (*type_compare_function)(void *data1, void *data2)) {
    CircularDoublyLinkedList *CDLL = *CDLL_ref;
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_sort_asc", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_sort_asc", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    if (CDLL->sort_order == ASC) {
        return true;
    }
    bool is_sorted = _cll_merge_sort(&CDLL->begin, type_compare_function, ASC);
    if (!is_sorted) return false;
    CDLL->sort_order = ASC;
    CDLL->end = _get_node(CDLL, CDLL->size - 1);
    Node_set_next(CDLL->end, CDLL->begin);
    Node_set_prev(CDLL->begin, CDLL->end);
    return true;
}

bool CircularDoublyLinkedList_sort_desc(CircularDoublyLinkedList **CDLL_ref, int (*type_compare_function)(void *data1, void *data2)) {
    CircularDoublyLinkedList *CDLL = *CDLL_ref;
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_sort_desc", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_sort_desc", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    if (CDLL->sort_order == DESC) {
        return true;
    }
    bool is_sorted = _cll_merge_sort(&CDLL->begin, type_compare_function, DESC);
    if (!is_sorted) return false;
    CDLL->sort_order = DESC;
    CDLL->end = _get_node(CDLL, CDLL->size-1);
    Node_set_next(CDLL->end, CDLL->begin);
    Node_set_prev(CDLL->begin, CDLL->end);
    return true;
}

bool CircularDoublyLinkedList_sorted_insert(CircularDoublyLinkedList *CDLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("CircularDoublyLinkedList_sorted_insert", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("CircularDoublyLinkedList_sorted_insert", "data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_sorted_insert", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_not_sorted("CircularDoublyLinkedList_sorted_insert", "Circular Linked List", (void*) CDLL, CircularDoublyLinkedList_is_sorted, SUPPRESS_PRINT_ERROR)
        )
    ) return false;

    if (CDLL->sort_order == ASC) {
        _cll_sorted_insert_asc(CDLL, data, type_compare_function);
    } else {
        _cll_sorted_insert_desc(CDLL, data, type_compare_function);
    }
    return true;
}

void *CircularDoublyLinkedList_min(const CircularDoublyLinkedList *CDLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_min", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_min", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;

    if (CircularDoublyLinkedList_is_sorted((void *) CDLL)) {
        if (CDLL->sort_order == ASC) {
            return Node_get_data(CDLL->begin);
        } else {
            return Node_get_data(CDLL->end);
        }
    }

    CircularDoublyLinkedList *clone = CircularDoublyLinkedList_clone(CDLL);
    CircularDoublyLinkedList_sort_asc(&clone, type_compare_function);
    void *data = Node_get_data(clone->begin);
    CircularDoublyLinkedList_destroy(&clone);
    return data;
}

void *CircularDoublyLinkedList_max(const CircularDoublyLinkedList *CDLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_max", "Circular Linked List", (void *) CDLL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_max", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;

    if (CircularDoublyLinkedList_is_sorted((void *) CDLL)) {
        if (CDLL->sort_order == ASC) {
            return Node_get_data(CDLL->end);
        } else {
            return Node_get_data(CDLL->begin);
        }
    }

    CircularDoublyLinkedList *clone = CircularDoublyLinkedList_clone(CDLL);
    CircularDoublyLinkedList_sort_desc(&clone, type_compare_function);
    void *data = Node_get_data(clone->begin);
    CircularDoublyLinkedList_destroy(&clone);
    return data;
}
