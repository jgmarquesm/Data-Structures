#include "../include/circular_doubly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/node.h"
#include "../include/exception_handler.h"
//#--ADD_TO_INCLUDE

#define UNSORTED 0
#define ASC 1
#define DESC -1

typedef struct _circular_linked_list {
    Node *begin;
    Node *end;
    size_t size;
    int sort_order;
} CircularLinkedList;

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

bool _cll_merge_sort(Node **CLL_begin_ref, int (*type_compare_function)(void *data1, void *data2), int order) {
    Node *CLL_begin = *CLL_begin_ref, *left, *right;

    if (CLL_begin == NULL || Node_get_next(CLL_begin) == CLL_begin) {
        return false;
    }

    if (order != ASC && order != DESC) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_sort_*'.\n");
        fprintf(stderr, "ERROR: Invalid sort order.\n");
        return false;
    }

    _cll_left_right_split(CLL_begin, &left, &right);
    _cll_merge_sort(&left, type_compare_function, order);
    _cll_merge_sort(&right, type_compare_function, order);

    *CLL_begin_ref = _cll_sorted_merge(left, right, type_compare_function, order);
    return true;
}

Node *_get_node(const CircularLinkedList *CLL, size_t index) {
    Node *node = CLL->begin;
    for (size_t i = 0; i < index; i++) {
        node = Node_get_next(node);
    }
    return node;
}

CircularLinkedList *CircularLinkedList_create() {
    CircularLinkedList *CLL = (CircularLinkedList *) calloc(1, sizeof(CircularLinkedList));
    CLL->begin = NULL;
    CLL->end = NULL;
    CLL->size = 0;
    CLL->sort_order = 0;

    return CLL;
}

void CircularLinkedList_clean(CircularLinkedList *CLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularLinkedList_clean", "Circular Linked List", ((void *) CLL))
        )
    ) return;
    Node *node = CLL->begin;
    while (node != CLL->end) {
        Node *node_next = Node_get_next(node);
        Node_destroy(&node);
        node = node_next;
    }
    Node_destroy(&node);
    CLL->begin = NULL;
    CLL->end = NULL;
    CLL->size = 0;
    CLL->sort_order = UNSORTED;
}

void CircularLinkedList_destroy(CircularLinkedList **CLL_ref) {
    CircularLinkedList *CLL = *CLL_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularLinkedList_destroy", "Circular Linked List", ((void *) CLL))
        )
    ) return;
    CircularLinkedList_clean(CLL);
    free(CLL);
    *CLL_ref = NULL;
}

bool CircularLinkedList_is_empty(void *CLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularLinkedList_is_empty", "Circular Linked List", ((void *) CLL))
        )
    ) return true;
    return ((CircularLinkedList *) CLL)->size == 0;
}

bool CircularLinkedList_is_sorted(void *CLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularLinkedList_is_sorted", "Circular Linked List", ((void *) CLL))
        )
    ) return false;
    return ((CircularLinkedList *) CLL)->sort_order != UNSORTED;
}

int CircularLinkedList_sort_order(const CircularLinkedList *CLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_sort_order", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_sort_order", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return UNSORTED;
    return CLL->sort_order;
}

void CircularLinkedList_print(const CircularLinkedList *CLL, void (*type_print_function)(void *data)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_print", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_print", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return;
    Node *node = CLL->begin;
    printf("LAST NODE <- -> ");
    do {
        type_print_function(Node_get_data(node));
        printf(" <- -> ");
        node = Node_get_next(node);
    } while (node != CLL->begin);
    puts("FIRST NODE");
}

void CircularLinkedList_add_first(CircularLinkedList *CLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_add_first", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_null("CircularLinkedList_add_first", "Data", data)
        )
    ) return;
    Node *node = Node_create(data);

    if (CircularLinkedList_is_empty(CLL)) {
        CLL->end = node;
    } else {
        Node_set_next(node, CLL->begin);
        Node_set_prev(CLL->begin, node);
        Node_set_prev(node, CLL->end);
        Node_set_next(CLL->end, node);
    }

    CLL->begin = node;
    CLL->size++;
    CLL->sort_order = UNSORTED;
}

void CircularLinkedList_add_last(CircularLinkedList *CLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_add_last", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_null("CircularLinkedList_add_last", "Data", data)
        )
    ) return;
    Node *node = Node_create(data);
    if (CircularLinkedList_is_empty((void *) CLL)) CLL->begin = node;
    else {
        Node_set_next(CLL->end, node);
        Node_set_prev(node, CLL->end);
        Node_set_prev(CLL->begin, node);
        Node_set_next(node, CLL->begin);
    }
    CLL->end = node;
    CLL->size++;
    CLL->sort_order = UNSORTED;
}

void _cll_sorted_insert_asc(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (type_compare_function(Node_get_data(CLL->begin), data) <= 0) {
        CircularLinkedList_add_first(CLL, data);
        CLL->sort_order = ASC;
        return;
    } else if (type_compare_function(Node_get_data(CLL->end), data) >= 0) {
        CircularLinkedList_add_last(CLL, data);
        CLL->sort_order = ASC;
        return;
    } else {
        Node *node = CLL->begin, *node_new = Node_create(data);
        while (node != CLL->end && type_compare_function(data, Node_get_data(node)) < 0) {
            node = Node_get_next(node);
        }
        Node_set_next(node_new, node);
        Node_set_prev(node_new, Node_get_prev(node));
        Node_set_next(Node_get_prev(node), node_new);
        Node_set_prev(node, node_new);
        CLL->size++;
    }
}

void _cll_sorted_insert_desc(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (type_compare_function(Node_get_data(CLL->begin), data) >= 0) {
        CircularLinkedList_add_first(CLL, data);
        CLL->sort_order = DESC;
        return;
    } else if (type_compare_function(Node_get_data(CLL->end), data) <= 0) {
        CircularLinkedList_add_last(CLL, data);
        CLL->sort_order = DESC;
    } else {
        Node *node = CLL->begin, *node_new = Node_create(data);
        while (node != CLL->end && type_compare_function(data, Node_get_data(node)) > 0) {
            node = Node_get_next(node);
        }
        Node_set_next(node_new, node);
        Node_set_prev(node_new, Node_get_prev(node));
        Node_set_next(Node_get_prev(node), node_new);
        Node_set_prev(node, node_new);
        CLL->size++;
    }
}

void *CircularLinkedList_remove_first(CircularLinkedList *CLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_remove_first", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_remove_first", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return NULL;
    Node *node = CLL->begin;
    void *data = Node_get_data(node);
    if (CLL->begin == CLL->end) {
        CLL->begin = CLL->end = NULL;
    } else {
        CLL->begin = Node_get_next(node);
        Node_set_prev(CLL->begin, CLL->end);
        Node_set_next(CLL->end, CLL->begin);
    }
    free(node);
    CLL->size--;
    return data;
}

void *CircularLinkedList_remove_last(CircularLinkedList *CLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_remove_last", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_remove_last", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return NULL;
    Node *node = CLL->end;
    void *data = Node_get_data(node);
    if (CLL->begin == CLL->end) {
        CLL->begin = CLL->end = NULL;
    } else {
        CLL->end = Node_get_prev(node);
        Node_set_next(Node_get_prev(node), Node_get_next(node));
        Node_set_prev(Node_get_next(node), Node_get_prev(node));
    }
    Node_destroy(&node);
    CLL->size--;
    return data;
}

void *CircularLinkedList_remove_at(CircularLinkedList *CLL, size_t index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularLinkedList_remove_at", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_remove_at", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty),
            ExceptionHandler_is_out_of_bounds("CircularLinkedList_remove_at", "Index", index, CLL->size-1)
        )
    ) return NULL;
    if (index == 0) {
        return CircularLinkedList_remove_first(CLL);
    }
    if (index == CLL->size-1) {
        return CircularLinkedList_remove_last(CLL);
    }
    Node *node = CLL->begin;
    void *data;
    for (size_t i = 0; i < index; i++) {
        node = Node_get_next(node);
    }
    Node_set_next(Node_get_prev(node), Node_get_next(node));
    Node_set_prev(Node_get_next(node), Node_get_prev(node));
    data = Node_get_data(node);
    Node_destroy(&node);
    CLL->size--;
    return data;
}

void CircularLinkedList_remove(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_remove", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_remove", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return;

    Node *node = CLL->begin;
    if (type_compare_function(Node_get_data(CLL->begin), data) == 0) {
        if (CLL->begin == CLL->end) {
            CLL->begin = CLL->end = NULL;
        } else {
            CLL->begin = Node_get_next(node);
            Node_set_prev(CLL->begin, CLL->end);
            Node_set_next(CLL->end, CLL->begin);
        }
        Node_destroy(&node);
        CLL->size--;
    } else {
        node = Node_get_next(node);
        while (node != CLL->begin && type_compare_function(Node_get_data(node), data) != 0) {
            node = Node_get_next(node);
        }
        if (node != NULL) {
            if (CLL->end == node) {
                CLL->end = Node_get_prev(node);
            }
            Node_set_next(Node_get_prev(node), Node_get_next(node));
            Node_set_prev(Node_get_next(node), Node_get_prev(node));
            Node_destroy(&node);
            CLL->size--;
        }
    }
}

void CircularLinkedList_remove_all(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_remove_all", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_remove_all", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return;

    Node *node = CLL->begin;
    while (true) {
        Node *aux_node = Node_get_next(node);
        if (type_compare_function(Node_get_data(node), data) == 0) {
            if (CLL->begin == node) {
                if (CLL->begin == CLL->end) {
                    CLL->begin = CLL->end = NULL;
                } else {
                    CLL->begin = Node_get_next(node);
                    Node_set_prev(CLL->begin, CLL->end);
                    Node_set_next(CLL->end, CLL->begin);
                }
            } else {
                if (node == CLL->end) {
                    CLL->end = Node_get_prev(node);
                }
                Node_set_next(Node_get_prev(node), Node_get_next(node));
                Node_set_prev(Node_get_next(node), Node_get_prev(node));
            }
            Node_destroy(&node);
            node = aux_node;
            CLL->size--;
        } else {
            if (CircularLinkedList_contains(CLL, data)) {
                node = aux_node;
            } else {
                break;
            }
        }
    }
}

size_t CircularLinkedList_size(const CircularLinkedList *CLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_size", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_size", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return 0;
    return CLL->size;
}

void *CircularLinkedList_first_element(const CircularLinkedList *CLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_first_element", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_first_element", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return NULL;
    return Node_get_data(CLL->begin);
}

void *CircularLinkedList_last_element(const CircularLinkedList *CLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_last_element", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_last_element", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return NULL;
    return Node_get_data(CLL->end);
}

void *CircularLinkedList_get(const CircularLinkedList *CLL, size_t index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularLinkedList_get", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_get", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty),
            ExceptionHandler_is_out_of_bounds("CircularLinkedList_get", "Index", index, CLL->size-1)
        )
    ) return NULL;
    Node *node = _get_node(CLL, index);
    return Node_get_data(node);
}

int CircularLinkedList_count(const CircularLinkedList *CLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_count", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_count", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return 0;
    int count = 0;
    if (Node_get_data(CLL->begin) == data) {
        count++;
    }
    Node *node = Node_get_next(CLL->begin);
    while (node != CLL->begin) {
        if (Node_get_data(node) == data) {
            count++;
        }
        node = Node_get_next(node);
    }
    return count;
}

bool CircularLinkedList_contains(const CircularLinkedList *CLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_contains", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_contains", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return false;
    if (Node_get_data(CLL->begin) == data) {
        return true;
    }
    Node *node = Node_get_next(CLL->begin);
    while (node != CLL->begin) {
        if (Node_get_data(node) == data) {
            return true;
        }
        node = Node_get_next(node);
    }
    return false;
}

void CircularLinkedList_insert_at(CircularLinkedList *CLL, void *data, size_t index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularLinkedList_insert_at", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_insert_at", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty),
            ExceptionHandler_is_out_of_bounds("CircularLinkedList_insert_at", "Index", index, CLL->size)
        )
    ) return;
    if (index == 0) {
        CircularLinkedList_add_first(CLL, data);
    } else if (index == CLL->size) {
        CircularLinkedList_add_last(CLL, data);
    } else {
        Node *node_new = Node_create(data);
        Node *node = CLL->begin;
        for (size_t i = 0; i < index-1; i++) {
            node = Node_get_next(node);
        }
        Node_set_next(node_new, Node_get_next(node));
        Node_set_prev(Node_get_next(node), node_new);
        Node_set_next(node, node_new);
        Node_set_prev(node_new, node);
        CLL->size++;
        CLL->sort_order = UNSORTED;
    }
}

CircularLinkedList *CircularLinkedList_clone(const CircularLinkedList *CLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("CircularLinkedList_clone", "Circular Linked List", ((void *) CLL))
        )
    ) return NULL;
    CircularLinkedList *clone = CircularLinkedList_create();
    Node *node = Node_get_next(CLL->begin);
    CircularLinkedList_add_first(clone, Node_get_data(CLL->begin));
    int count = 1;
    while (node != CLL->begin) {
        CircularLinkedList_insert_at(clone, Node_get_data(node), count);
        count++;
        node = Node_get_next(node);
    }
    clone->sort_order = CLL->sort_order;
    return clone;
}

CircularLinkedList *CircularLinkedList_concat(CircularLinkedList *CLL1, CircularLinkedList *CLL2) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_concat", "Circular Linked List 1", ((void *) CLL1)),
            ExceptionHandler_is_null("CircularLinkedList_concat", "Circular Linked List 2", ((void *) CLL2))
        )
    ) return NULL;
    if (CircularLinkedList_is_empty((void *) CLL1)) {
        return CircularLinkedList_clone(CLL2);
    } else if (CircularLinkedList_is_empty((void *) CLL2)) {
        return CircularLinkedList_clone(CLL1);
    }
    CircularLinkedList *CLL_new = CircularLinkedList_clone(CLL1);
    Node *node = CLL2->begin;
    while (Node_get_next(node) != CLL2->begin) {
        CircularLinkedList_add_last(CLL_new, Node_get_data(node));
        node = Node_get_next(node);
    }
    CircularLinkedList_add_last(CLL_new, Node_get_data(node));
    CLL_new->sort_order = UNSORTED;
    return CLL_new;
}

CircularLinkedList *CircularLinkedList_reverse(CircularLinkedList *CLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_clone", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_clone", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return NULL;
    CircularLinkedList *CLL_new = CircularLinkedList_clone(CLL);
    Node *node = CLL->begin, *node_prev = NULL, *node_next = NULL;
    CLL_new->begin = CLL->end;
    for (size_t i = 0; i < CLL->size; i++) {
        node_next = Node_get_next(node);
        node_prev = Node_get_prev(node);
        Node_set_next(node, node_prev);
        Node_set_prev(node, node_next);
        node = node_next;
    }
    CLL_new->end = CLL->begin;
    CLL_new->sort_order = (-1)*CLL->sort_order;
    return CLL_new;
}

bool CircularLinkedList_is_equals_strict(const CircularLinkedList *CLL1, const CircularLinkedList *CLL2) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("CircularLinkedList_is_equals_strict", "Circular Linked List 1", ((void *) CLL1)),
            ExceptionHandler_is_null("CircularLinkedList_is_equals_strict", "Circular Linked List 2", ((void *) CLL2)),
            ExceptionHandler_is_empty("CircularLinkedList_is_equals_strict", "Circular Linked List 1", ((void *) CLL1), CircularLinkedList_is_empty),
            ExceptionHandler_is_empty("CircularLinkedList_is_equals_strict", "Circular Linked List 2", ((void *) CLL2), CircularLinkedList_is_empty)
        ) || CLL1->size != CLL2->size
    ) return false;
    Node *node1 = CLL1->begin;
    Node *node2 = CLL2->begin;
    for (size_t i = 0; i < CLL1->size; i++) {
        if (Node_get_data(node1) != Node_get_data(node2)) {
            return false;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return CLL1->sort_order == CLL2->sort_order;
}

bool CircularLinkedList_is_equals(const CircularLinkedList *CLL1, const CircularLinkedList *CLL2, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("CircularLinkedList_is_equals", "Circular Linked List 1", ((void *) CLL1)),
            ExceptionHandler_is_null("CircularLinkedList_is_equals", "Circular Linked List 2", ((void *) CLL2)),
            ExceptionHandler_is_empty("CircularLinkedList_is_equals", "Circular Linked List 1", ((void *) CLL1), CircularLinkedList_is_empty),
            ExceptionHandler_is_empty("CircularLinkedList_is_equals", "Circular Linked List 2", ((void *) CLL2), CircularLinkedList_is_empty)
        ) || CLL1->size != CLL2->size
    ) return false;
    Node *node1 = CLL1->begin;
    Node *node2 = CLL2->begin;
    for (size_t i = 0; i < CLL1->size; i++) {
        if (type_compare_function(Node_get_data(node1), Node_get_data(node2)) != 0) {
            return false;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return CLL1->sort_order == CLL2->sort_order;
}

void CircularLinkedList_sort_asc(CircularLinkedList **CLL_ref, int (*type_compare_function)(void *data1, void *data2)) {
    CircularLinkedList *CLL = *CLL_ref;
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_sort_asc", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_sort_asc", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return;

    if (CLL->sort_order == ASC) {
        return;
    } else if (CLL->sort_order == DESC) {
        *CLL_ref = CircularLinkedList_reverse(CLL);
    } else {
        bool is_sorted = _cll_merge_sort(&CLL->begin, type_compare_function, ASC);
        if (!is_sorted) return;
        CLL->sort_order = ASC;
        CLL->end = _get_node(CLL, CLL->size - 1);
        Node_set_next(CLL->end, CLL->begin);
        Node_set_prev(CLL->begin, CLL->end);
    }
}

void CircularLinkedList_sort_desc(CircularLinkedList **CLL_ref, int (*type_compare_function)(void *data1, void *data2)) {
    CircularLinkedList *CLL = *CLL_ref;
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_sort_desc", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_sort_desc", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return;

    if (CLL->sort_order == DESC) {
        return;
    } else if (CLL->sort_order == ASC) {
        *CLL_ref = CircularLinkedList_reverse(CLL);
    } else {
        bool is_sorted = _cll_merge_sort(&CLL->begin, type_compare_function, DESC);
        if (!is_sorted) return;
        CLL->sort_order = DESC;
        CLL->end = _get_node(CLL, CLL->size-1);
        Node_set_next(CLL->end, CLL->begin);
        Node_set_prev(CLL->begin, CLL->end);
    }
}

void CircularLinkedList_sorted_insert(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("CircularLinkedList_sorted_insert", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_sorted_insert", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty),
            ExceptionHandler_is_not_sorted("CircularLinkedList_sorted_insert", "Circular Linked List", (void*) CLL, CircularLinkedList_is_sorted)
        )
    ) return;

    if (CLL->sort_order == ASC) {
        _cll_sorted_insert_asc(CLL, data, type_compare_function);
    } else {
        _cll_sorted_insert_desc(CLL, data, type_compare_function);
    }
}

void *CircularLinkedList_min(const CircularLinkedList *CLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_min", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_min", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return NULL;

    if (CircularLinkedList_is_sorted((void *) CLL)) {
        if (CLL->sort_order == ASC) {
            return Node_get_data(CLL->begin);
        } else {
            return Node_get_data(CLL->end);
        }
    }

    CircularLinkedList *clone = CircularLinkedList_clone(CLL);
    CircularLinkedList_sort_asc(&clone, type_compare_function);
    void *data = Node_get_data(clone->begin);
    CircularLinkedList_destroy(&clone);
    return data;
}

void *CircularLinkedList_max(const CircularLinkedList *CLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("CircularLinkedList_max", "Circular Linked List", ((void *) CLL)),
            ExceptionHandler_is_empty("CircularLinkedList_max", "Circular Linked List", ((void *) CLL), CircularLinkedList_is_empty)
        )
    ) return NULL;

    if (CircularLinkedList_is_sorted((void *) CLL)) {
        if (CLL->sort_order == ASC) {
            return Node_get_data(CLL->end);
        } else {
            return Node_get_data(CLL->begin);
        }
    }

    CircularLinkedList *clone = CircularLinkedList_clone(CLL);
    CircularLinkedList_sort_desc(&clone, type_compare_function);
    void *data = Node_get_data(clone->begin);
    CircularLinkedList_destroy(&clone);
    return data;
}
