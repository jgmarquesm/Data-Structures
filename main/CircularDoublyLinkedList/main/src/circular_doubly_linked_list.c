#include <stdlib.h>
#include <stdio.h>
#include "../include/node.h"
//#--ADD_TO_INCLUDE
#include "../include/circular_doubly_linked_list.h"

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

    if(node == NULL) return;

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

Node *_cll_sorted_merge_aux(Node *left, Node *right, __TYPE_COMPARE_FUNCTION_SIGNATURE__, int order) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    if (order == __ASC__) {
        if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(left), Node_get_data(right)) >= 0) {
            Node_set_next(left, _cll_sorted_merge_aux(Node_get_next(left), right, __TYPE_COMPARE_FUNCTION_NAME__, order));
            Node_set_prev(Node_get_next(left), left);
            Node_set_prev(left, __DEFAULT_PTR__);
            return left;
        } else {
            Node_set_next(right, _cll_sorted_merge_aux(left, Node_get_next(right), __TYPE_COMPARE_FUNCTION_NAME__, order));
            Node_set_prev(Node_get_next(right), right);
            Node_set_prev(right, __DEFAULT_PTR__);
            return right;
        }
    } else {
        if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(left), Node_get_data(right)) <= 0) {
            Node_set_next(left, _cll_sorted_merge_aux(Node_get_next(left), right, __TYPE_COMPARE_FUNCTION_NAME__, order));
            Node_set_prev(Node_get_next(left), left);
            Node_set_prev(left, __DEFAULT_PTR__);
            return left;
        } else {
            Node_set_next(right, _cll_sorted_merge_aux(left, Node_get_next(right), __TYPE_COMPARE_FUNCTION_NAME__, order));
            Node_set_prev(Node_get_next(right), right);
            Node_set_prev(right, __DEFAULT_PTR__);
            return right;
        }
    }
}

Node *_cll_sorted_merge(Node *left, Node *right, __TYPE_COMPARE_FUNCTION_SIGNATURE__, int order) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    Node *last_node;

    if (order == __ASC__) {
        if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(Node_get_prev(left)), Node_get_data(Node_get_prev(right))) >= 0) {
            last_node = Node_get_prev(right);
        } else {
            last_node = Node_get_prev(left);
        }
    } else {
        if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(Node_get_next(left)), Node_get_data(Node_get_next(right))) >= 0) {
            last_node = Node_get_prev(left);
        } else {
            last_node = Node_get_prev(right);
        }
    }

    Node_set_next(Node_get_prev(left), __DEFAULT_PTR__);
    Node_set_next(Node_get_prev(right), __DEFAULT_PTR__);

    Node *result = _cll_sorted_merge_aux(left, right, __TYPE_COMPARE_FUNCTION_NAME__, order);
    Node_set_prev(result, last_node);
    Node_set_next(last_node, result);

    return result;
}

bool _cll_merge_sort(Node **CDLL_begin_ref, __TYPE_COMPARE_FUNCTION_SIGNATURE__, int order) {
    Node *CDLL_begin = *CDLL_begin_ref, *left, *right;

    if (CDLL_begin == NULL || Node_get_next(CDLL_begin) == CDLL_begin) {
        return __DEFAULT_BOOL__;
    }

    if (order != __ASC__ && order != __DESC__) {
        fprintf(stderr, "\nERROR: on function 'CircularDoublyLinkedList_sort_*'.\n");
        fprintf(stderr, "ERROR: Invalid sort order.\n");
        return __DEFAULT_BOOL__;
    }

    _cll_left_right_split(CDLL_begin, &left, &right);
    _cll_merge_sort(&left, __TYPE_COMPARE_FUNCTION_NAME__, order);
    _cll_merge_sort(&right, __TYPE_COMPARE_FUNCTION_NAME__, order);

    *CDLL_begin_ref = _cll_sorted_merge(left, right, __TYPE_COMPARE_FUNCTION_NAME__, order);
    return __NOT_DEFAULT_BOOL__;
}

Node *_get_node(const CircularDoublyLinkedList *CDLL, size_t index) {
    Node *node = CDLL->begin;
    for (size_t i = 0; i < index; i++) {
        node = Node_get_next(node);
    }
    return node;
}

CircularDoublyLinkedList *CircularDoublyLinkedList_create() {
    CircularDoublyLinkedList *CDLL = (CircularDoublyLinkedList *) calloc(1, size_of_circular_doubly_linked_list_type);
    CDLL->begin = __DEFAULT_PTR__;
    CDLL->end = __DEFAULT_PTR__;
    CDLL->size = 0;
    CDLL->sort_order = 0;

    return CDLL;
}

bool CircularDoublyLinkedList_clean(CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularDoublyLinkedList_clean", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Node *node = CDLL->begin;
    while (node != CDLL->end) {
        Node *node_next = Node_get_next(node);
        Node_destroy(&node);
        node = node_next;
    }
    Node_destroy(&node);
    CDLL->begin = __DEFAULT_PTR__;
    CDLL->end = __DEFAULT_PTR__;
    CDLL->size = 0;
    CDLL->sort_order = __UNSORTED__;
    return __NOT_DEFAULT_BOOL__;
}

bool CircularDoublyLinkedList_destroy(CircularDoublyLinkedList **CDLL_ref) {
    CircularDoublyLinkedList *CDLL = *CDLL_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularDoublyLinkedList_destroy", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    CircularDoublyLinkedList_clean(CDLL);
    free(CDLL);
    *CDLL_ref = __DEFAULT_PTR__;
    return __NOT_DEFAULT_BOOL__;
}

bool CircularDoublyLinkedList_is_empty(void *CDLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_empty", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __NOT_DEFAULT_BOOL__;
    return ((CircularDoublyLinkedList *) CDLL)->size == 0;
}

bool CircularDoublyLinkedList_is_sorted(void *CDLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_sorted", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    return ((CircularDoublyLinkedList *) CDLL)->sort_order != __UNSORTED__;
}

int CircularDoublyLinkedList_sort_order(const CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_sort_order", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_sort_order", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __UNSORTED__;
    return CDLL->sort_order;
}

void CircularDoublyLinkedList_print(const CircularDoublyLinkedList *CDLL, __TYPE_PRINT_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_print", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_print", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return;
    Node *node = CDLL->begin;
    printf("LAST NODE <- -> ");
    do {
        __TYPE_PRINT_FUNCTION_NAME__(Node_get_data(node));
        printf(" <- -> ");
        node = Node_get_next(node);
    } while (node != CDLL->begin);
    puts("FIRST NODE");
}

bool CircularDoublyLinkedList_add_first(CircularDoublyLinkedList *CDLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_add_first", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_add_first", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
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
    CDLL->sort_order = __UNSORTED__;
    return __NOT_DEFAULT_BOOL__;
}

bool CircularDoublyLinkedList_add_last(CircularDoublyLinkedList *CDLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_add_last", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_add_last", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
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
    CDLL->sort_order = __UNSORTED__;
    return __NOT_DEFAULT_BOOL__;
}

void _cll_sorted_insert_asc(CircularDoublyLinkedList *CDLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(CDLL->begin), data) <= 0) {
        CircularDoublyLinkedList_add_first(CDLL, data);
        CDLL->sort_order = __ASC__;
        return;
    } else if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(CDLL->end), data) >= 0) {
        CircularDoublyLinkedList_add_last(CDLL, data);
        CDLL->sort_order = __ASC__;
        return;
    } else {
        Node *node = CDLL->begin, *node_new = Node_create(data);
        while (node != CDLL->end && __TYPE_COMPARE_FUNCTION_NAME__(data, Node_get_data(node)) < 0) {
            node = Node_get_next(node);
        }
        Node_set_next(node_new, node);
        Node_set_prev(node_new, Node_get_prev(node));
        Node_set_next(Node_get_prev(node), node_new);
        Node_set_prev(node, node_new);
        CDLL->size++;
    }
}

void _cll_sorted_insert_desc(CircularDoublyLinkedList *CDLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(CDLL->begin), data) >= 0) {
        CircularDoublyLinkedList_add_first(CDLL, data);
        CDLL->sort_order = __DESC__;
        return;
    } else if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(CDLL->end), data) <= 0) {
        CircularDoublyLinkedList_add_last(CDLL, data);
        CDLL->sort_order = __DESC__;
    } else {
        Node *node = CDLL->begin, *node_new = Node_create(data);
        while (node != CDLL->end && __TYPE_COMPARE_FUNCTION_NAME__(data, Node_get_data(node)) > 0) {
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
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove_first", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_remove_first", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Node *node = CDLL->begin;
    void *data = Node_get_data(node);
    if (CDLL->begin == CDLL->end) {
        CDLL->begin = CDLL->end = __DEFAULT_PTR__;
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
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove_last", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_remove_last", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Node *node = CDLL->end;
    void *data = Node_get_data(node);
    if (CDLL->begin == CDLL->end) {
        CDLL->begin = CDLL->end = __DEFAULT_PTR__;
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
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove_at", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_remove_at", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("CircularDoublyLinkedList_remove_at", "Index", index, CDLL->size-1, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
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

bool CircularDoublyLinkedList_remove(CircularDoublyLinkedList *CDLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove", "Data", data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_remove", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    Node *node = CDLL->begin;
    if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(CDLL->begin), data) == 0) {
        if (CDLL->begin == CDLL->end) {
            CDLL->begin = CDLL->end = __DEFAULT_PTR__;
        } else {
            CDLL->begin = Node_get_next(node);
            Node_set_prev(CDLL->begin, CDLL->end);
            Node_set_next(CDLL->end, CDLL->begin);
        }
        Node_destroy(&node);
        CDLL->size--;
        return __NOT_DEFAULT_BOOL__;
    } else {
        node = Node_get_next(node);
        while (node != CDLL->begin && __TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(node), data) != 0) {
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
            return __NOT_DEFAULT_BOOL__;
        }
    }
    return __DEFAULT_BOOL__;
}

size_t CircularDoublyLinkedList_remove_all(CircularDoublyLinkedList *CDLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove_all", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_remove_all", "Data", data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_remove_all", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_SIZE_T__;

    Node *node = CDLL->begin;
    size_t count = 0;
    while (true) {
        Node *aux_node = Node_get_next(node);
        if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(node), data) == 0) {
            if (CDLL->begin == node) {
                if (CDLL->begin == CDLL->end) {
                    CDLL->begin = CDLL->end = __DEFAULT_PTR__;
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
            ExceptionHandler_is_null("CircularDoublyLinkedList_size", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_size", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_SIZE_T__;
    return CDLL->size;
}

void *CircularDoublyLinkedList_first_element(const CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_first_element", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_first_element", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return Node_get_data(CDLL->begin);
}

void *CircularDoublyLinkedList_last_element(const CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_last_element", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_last_element", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return Node_get_data(CDLL->end);
}

void *CircularDoublyLinkedList_get(const CircularDoublyLinkedList *CDLL, size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_get", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_get", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("CircularDoublyLinkedList_get", "Index", index, CDLL->size-1, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Node *node = _get_node(CDLL, index);
    return Node_get_data(node);
}

size_t CircularDoublyLinkedList_count(const CircularDoublyLinkedList *CDLL, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularDoublyLinkedList_count", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_count", "Data", data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_count", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_SIZE_T__;
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
            ExceptionHandler_is_null("CircularDoublyLinkedList_contains", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_contains", "Data", data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_contains", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    if (Node_get_data(CDLL->begin) == data) {
        return __NOT_DEFAULT_BOOL__;
    }
    Node *node = Node_get_next(CDLL->begin);
    while (node != CDLL->begin) {
        if (Node_get_data(node) == data) {
            return __NOT_DEFAULT_BOOL__;
        }
        node = Node_get_next(node);
    }
    return __DEFAULT_BOOL__;
}

bool CircularDoublyLinkedList_insert_at(CircularDoublyLinkedList *CDLL, void *data, size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_insert_at", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_insert_at", "Data", data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("CircularDoublyLinkedList_insert_at", "Index", index, CDLL->size, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
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
    CDLL->sort_order = __UNSORTED__;
    return __NOT_DEFAULT_BOOL__;
}

CircularDoublyLinkedList *CircularDoublyLinkedList_clone(const CircularDoublyLinkedList *CDLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_clone", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_clone", "Circular Doubly Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
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
            ExceptionHandler_is_null("CircularDoublyLinkedList_concat", "Circular Linked List 1", (void *) CDLL1, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_concat", "Circular Linked List 2", (void *) CDLL2, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
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
    CDLL_new->sort_order = __UNSORTED__;
    return CDLL_new;
}

bool CircularDoublyLinkedList_reverse(CircularDoublyLinkedList **CDLL_ref) {
    CircularDoublyLinkedList *reversed = *CDLL_ref;
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_clone", "Circular Linked List", (void *) reversed, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_clone", "Circular Linked List", (void *) reversed, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    CircularDoublyLinkedList *clone = CircularDoublyLinkedList_clone(reversed);
    Node *node = clone->begin, *next = __DEFAULT_PTR__, *prev = __DEFAULT_PTR__;
    for (size_t i = 0; i < reversed->size; i++) {
        next = Node_get_next(node);
        prev = Node_get_prev(node);
        Node_set_prev(node, next);
        Node_set_next(node, prev);
        node = Node_get_next(node);
    }
    reversed->sort_order = (-1)*reversed->sort_order;
    return __NOT_DEFAULT_BOOL__;
}

bool CircularDoublyLinkedList_is_equals_strict(const CircularDoublyLinkedList *CDLL1, const CircularDoublyLinkedList *CDLL2) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_equals_strict", "Circular Linked List 1", (void *) CDLL1, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_equals_strict", "Circular Linked List 2", (void *) CDLL2, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_is_equals_strict", "Circular Linked List 1", (void *) CDLL1, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_is_equals_strict", "Circular Linked List 2", (void *) CDLL2, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        ) || CDLL1->size != CDLL2->size
    ) return __DEFAULT_BOOL__;
    Node *node1 = CDLL1->begin;
    Node *node2 = CDLL2->begin;
    for (size_t i = 0; i < CDLL1->size; i++) {
        if (Node_get_data(node1) != Node_get_data(node2)) {
            return __DEFAULT_BOOL__;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return CDLL1->sort_order == CDLL2->sort_order;
}

bool CircularDoublyLinkedList_is_equals(const CircularDoublyLinkedList *CDLL1, const CircularDoublyLinkedList *CDLL2, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_equals", "Circular Linked List 1", (void *) CDLL1, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_is_equals", "Circular Linked List 2", (void *) CDLL2, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_is_equals", "Circular Linked List 1", (void *) CDLL1, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_is_equals", "Circular Linked List 2", (void *) CDLL2, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        ) || CDLL1->size != CDLL2->size
    ) return __DEFAULT_BOOL__;
    Node *node1 = CDLL1->begin;
    Node *node2 = CDLL2->begin;
    for (size_t i = 0; i < CDLL1->size; i++) {
        if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(node1), Node_get_data(node2)) != 0) {
            return __DEFAULT_BOOL__;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return CDLL1->sort_order == CDLL2->sort_order;
}

bool CircularDoublyLinkedList_sort_asc(CircularDoublyLinkedList **CDLL_ref, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    CircularDoublyLinkedList *CDLL = *CDLL_ref;
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_sort_asc", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_sort_asc", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    if (CDLL->sort_order == __ASC__) {
        return __NOT_DEFAULT_BOOL__;
    }
    bool is_sorted = _cll_merge_sort(&CDLL->begin, __TYPE_COMPARE_FUNCTION_NAME__, __ASC__);
    if (!is_sorted) return __DEFAULT_BOOL__;
    CDLL->sort_order = __ASC__;
    CDLL->end = _get_node(CDLL, CDLL->size - 1);
    Node_set_next(CDLL->end, CDLL->begin);
    Node_set_prev(CDLL->begin, CDLL->end);
    return __NOT_DEFAULT_BOOL__;
}

bool CircularDoublyLinkedList_sort_desc(CircularDoublyLinkedList **CDLL_ref, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    CircularDoublyLinkedList *CDLL = *CDLL_ref;
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_sort_desc", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_sort_desc", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    if (CDLL->sort_order == __DESC__) {
        return __NOT_DEFAULT_BOOL__;
    }
    bool is_sorted = _cll_merge_sort(&CDLL->begin, __TYPE_COMPARE_FUNCTION_NAME__, __DESC__);
    if (!is_sorted) return __DEFAULT_BOOL__;
    CDLL->sort_order = __DESC__;
    CDLL->end = _get_node(CDLL, CDLL->size-1);
    Node_set_next(CDLL->end, CDLL->begin);
    Node_set_prev(CDLL->begin, CDLL->end);
    return __NOT_DEFAULT_BOOL__;
}

bool CircularDoublyLinkedList_sorted_insert(CircularDoublyLinkedList *CDLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("CircularDoublyLinkedList_sorted_insert", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("CircularDoublyLinkedList_sorted_insert", "data", data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_sorted_insert", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_not_sorted("CircularDoublyLinkedList_sorted_insert", "Circular Linked List", (void*) CDLL, CircularDoublyLinkedList_is_sorted, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;

    if (CDLL->sort_order == __ASC__) {
        _cll_sorted_insert_asc(CDLL, data, __TYPE_COMPARE_FUNCTION_NAME__);
    } else {
        _cll_sorted_insert_desc(CDLL, data, __TYPE_COMPARE_FUNCTION_NAME__);
    }
    return __NOT_DEFAULT_BOOL__;
}

void *CircularDoublyLinkedList_min(const CircularDoublyLinkedList *CDLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_min", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_min", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;

    if (CircularDoublyLinkedList_is_sorted((void *) CDLL)) {
        if (CDLL->sort_order == __ASC__) {
            return Node_get_data(CDLL->begin);
        } else {
            return Node_get_data(CDLL->end);
        }
    }

    CircularDoublyLinkedList *clone = CircularDoublyLinkedList_clone(CDLL);
    CircularDoublyLinkedList_sort_asc(&clone, __TYPE_COMPARE_FUNCTION_NAME__);
    void *data = Node_get_data(clone->begin);
    CircularDoublyLinkedList_destroy(&clone);
    return data;
}

void *CircularDoublyLinkedList_max(const CircularDoublyLinkedList *CDLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularDoublyLinkedList_max", "Circular Linked List", (void *) CDLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("CircularDoublyLinkedList_max", "Circular Linked List", (void *) CDLL, CircularDoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;

    if (CircularDoublyLinkedList_is_sorted((void *) CDLL)) {
        if (CDLL->sort_order == __ASC__) {
            return Node_get_data(CDLL->end);
        } else {
            return Node_get_data(CDLL->begin);
        }
    }

    CircularDoublyLinkedList *clone = CircularDoublyLinkedList_clone(CDLL);
    CircularDoublyLinkedList_sort_desc(&clone, __TYPE_COMPARE_FUNCTION_NAME__);
    void *data = Node_get_data(clone->begin);
    CircularDoublyLinkedList_destroy(&clone);
    return data;
}
