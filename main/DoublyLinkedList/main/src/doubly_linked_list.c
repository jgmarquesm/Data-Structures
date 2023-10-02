#include <stdlib.h>
#include <stdio.h>
#include "../include/node.h"
//#--ADD_TO_INCLUDE
#include "../include/doubly_linked_list.h"

#define UNSORTED 0
#define ASC 1
#define DESC -1

typedef struct _doubly_linked_list {
    Node *begin;
    Node *end;
    size_t size;
    int sort_order;
} DoublyLinkedList;

const size_t size_of_doubly_linked_list_type = sizeof(DoublyLinkedList);

void _dll_left_right_split(Node *node, Node **left_ref, Node **right_ref) {
    Node *slow = node, *fast = Node_get_next(node);

    while (fast != NULL && Node_get_next(fast) != NULL) {
        slow = Node_get_next(slow);
        fast = Node_get_next(Node_get_next(fast));
    }

    *left_ref = node;
    *right_ref = Node_get_next(slow);
    Node_set_next(slow, NULL);
}

Node *_dll_sorted_merge(Node *left, Node *right, int (*type_compare_function)(void *data1, void *data2), int order) {
    Node *LL_begin_result = NULL;

    if (left == NULL) {
        return right;
    } else if (right == NULL) {
        return left;
    }

    if (order == ASC) {
        if (type_compare_function(Node_get_data(left), Node_get_data(right)) >= 0) {
            LL_begin_result = left;
            Node_set_next(LL_begin_result, _dll_sorted_merge(Node_get_next(left), right, type_compare_function, order));
        } else {
            LL_begin_result = right;
            Node_set_next(LL_begin_result, _dll_sorted_merge(left, Node_get_next(right), type_compare_function, order));
        }
    } else {
        if (type_compare_function(Node_get_data(left), Node_get_data(right)) <= 0) {
            LL_begin_result = left;
            Node_set_next(LL_begin_result, _dll_sorted_merge(Node_get_next(left), right, type_compare_function, order));
        } else {
            LL_begin_result = right;
            Node_set_next(LL_begin_result, _dll_sorted_merge(left, Node_get_next(right), type_compare_function, order));
        }
    }

    return LL_begin_result;
}

void _dll_merge_sort(Node **LL_begin_ref, int (*type_compare_function)(void *data1, void *data2), int order) {
    Node *LL_begin = *LL_begin_ref, *left, *right;

    if ((LL_begin == NULL) || (Node_get_next(LL_begin) == NULL)) {
        return;
    }

    if (order != ASC && order != DESC) {
        fprintf(stderr, "\nERROR: on function 'DoublyLinkedList_sort_*'.\n");
        fprintf(stderr, "ERROR: Invalid sort order.\n");
        return;
    }

    _dll_left_right_split(LL_begin, &left, &right);
    _dll_merge_sort(&left, type_compare_function, order);
    _dll_merge_sort(&right, type_compare_function, order);

    *LL_begin_ref = _dll_sorted_merge(left, right, type_compare_function, order);
}

Node *_get_node(const DoublyLinkedList *LL, const size_t index) {
    Node *node = LL->begin;
    for (size_t i = 0; i != index; i++) {
        node = Node_get_next(node);
    }
    return node;
}

DoublyLinkedList *DoublyLinkedList_create() {
    DoublyLinkedList *LL = (DoublyLinkedList *) calloc(1, sizeof(DoublyLinkedList));
    LL->begin = NULL;
    LL->end = NULL;
    LL->size = 0;
    LL->sort_order = UNSORTED;

    return LL;
}

bool DoublyLinkedList_clean(DoublyLinkedList *LL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DoublyLinkedList_clean", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Node *node = LL->begin;
    while (node != NULL) {
        Node *node_next = Node_get_next(node);
        Node_destroy(&node);
        node = node_next;
    }
    Node_destroy(&node);
    LL->begin = NULL;
    LL->end = NULL;
    LL->size = 0;
    LL->sort_order = UNSORTED;
    return true;
}

bool DoublyLinkedList_destroy(DoublyLinkedList **LL_ref) {
    DoublyLinkedList *LL = *LL_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DoublyLinkedList_destroy", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    DoublyLinkedList_clean(LL);
    free(LL);
    *LL_ref = NULL;
    return true;
}

bool DoublyLinkedList_is_empty(void *LL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DoublyLinkedList_is_empty", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR)
        )
    ) return true;
    return ((DoublyLinkedList *) LL)->size == 0;
}

bool DoublyLinkedList_is_sorted(void *LL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DoublyLinkedList_is_sorted", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    return ((DoublyLinkedList *) LL)->sort_order != UNSORTED;
}

int DoublyLinkedList_sort_order(const DoublyLinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_sort_order", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_sort_order", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return UNSORTED;
    return LL->sort_order;
}

void DoublyLinkedList_print(const DoublyLinkedList *LL, void (*type_print_function)(void *data)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_print", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_print", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return;
    Node *node = LL->begin;
    printf("NULL <- ");
    while (Node_get_next(node) != NULL) {
        type_print_function(Node_get_data(node));
        printf(" <- -> ");
        node = Node_get_next(node);
    }
    type_print_function(Node_get_data(LL->end));
    printf(" -> ");
    puts("NULL");
}

bool DoublyLinkedList_add_first(DoublyLinkedList *LL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_add_first", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DoublyLinkedList_add_first", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Node *node = Node_create(data);
    Node_set_next(node, LL->begin);
    if (DoublyLinkedList_is_empty(LL)) LL->end = node;
    else Node_set_prev(LL->begin, node);
    LL->begin = node;
    LL->size++;
    LL->sort_order = UNSORTED;
    return true;
}

bool DoublyLinkedList_add_last(DoublyLinkedList *LL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_add_last", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DoublyLinkedList_add_last", "Data", data, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Node *node = Node_create(data);
    Node_set_prev(node, LL->end);
    if (DoublyLinkedList_is_empty(LL)) LL->begin = node;
    else Node_set_next(LL->end, node);
    LL->end = node;
    LL->size++;
    LL->sort_order = UNSORTED;
    return true;
}

void *DoublyLinkedList_remove_first(DoublyLinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_remove_first", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_remove_first", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Node *node = LL->begin;
    void *data = Node_get_data(node);
    if (LL->begin == LL->end) {
        LL->begin = LL->end = NULL;
    } else {
        LL->begin = Node_get_next(node);
        Node_set_prev(LL->begin, NULL);
    }
    free(node);
    LL->size--;
    return data;
}

void *DoublyLinkedList_remove_last(DoublyLinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_remove_last", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_remove_last", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Node *node = LL->end;
    void *data = Node_get_data(node);
    if (LL->begin == LL->end) {
        LL->begin = LL->end = NULL;
    } else {
        Node_set_next(Node_get_prev(node), NULL);
        LL->end = Node_get_prev(node);
    }
    free(node);
    LL->size--;
    return data;
}

void *DoublyLinkedList_remove_at(DoublyLinkedList *LL, const size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_remove_at", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_remove_at", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("DoublyLinkedList_remove_at", "Index", index, LL->size-1, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    if (index == 0) {
        return DoublyLinkedList_remove_first(LL);
    }
    if (index == LL->size) {
        return DoublyLinkedList_remove_last(LL);
    }
    Node *node = LL->begin;
    void *data;
    for (size_t i = 0; i < index; i++) {
        node = Node_get_next(node);
    }
    Node_set_next(Node_get_prev(node), Node_get_next(node));
    Node_set_prev(Node_get_next(node), Node_get_prev(node));
    data = Node_get_data(node);
    Node_destroy(&node);
    LL->size--;
    return data;
}

bool DoublyLinkedList_remove(DoublyLinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("DoublyLinkedList_remove", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DoublyLinkedList_remove", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_remove", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Node *node = LL->begin;
    while (node != NULL && type_compare_function(Node_get_data(node), data) != 0) {
        node = Node_get_next(node);
    }
    if (node != NULL) {
        if (LL->begin == node) {
            if (LL->begin == LL->end) {
                LL->begin = LL->end = NULL;
            } else {
                LL->begin = Node_get_next(node);
                Node_set_prev(Node_get_next(node), NULL);
            }
        } else {
            if (LL->end == node) {
                Node_set_next(Node_get_prev(node), NULL);
                LL->end = Node_get_prev(node);
            } else {
                Node_set_next(Node_get_prev(node), Node_get_next(node));
                Node_set_prev(Node_get_next(node), Node_get_prev(node));
            }
        }
        Node_destroy(&node);
        LL->size--;
        return true;
    }
    return false;
}

size_t DoublyLinkedList_remove_all(DoublyLinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("DoublyLinkedList_remove_all", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DoublyLinkedList_remove_all", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_remove_all", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    Node *node = LL->begin;
    size_t count = 0;
    while (node != NULL) {
        Node *aux_node = Node_get_next(node);
        if (type_compare_function(Node_get_data(node), data) == 0) {
            if (LL->begin == node) {
                if (LL->begin == LL->end) {
                    LL->begin = LL->end = NULL;
                } else {
                    LL->begin = Node_get_next(node);
                    Node_set_prev(Node_get_next(node), NULL);
                }
            } else {
                if (LL->end == node) {
                    LL->end = Node_get_prev(node);
                    Node_set_next(Node_get_prev(node), NULL);
                } else {
                    Node_set_next(Node_get_prev(node), Node_get_next(node));
                    Node_set_prev(Node_get_next(node), Node_get_prev(node));
                }
            }
            Node_destroy(&node);
            node = aux_node;
            LL->size--;
            count++;
        } else {
            node = aux_node;
        }
    }
    return count;
}

size_t DoublyLinkedList_size(const DoublyLinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_size", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_size", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    return LL->size;
}

void *DoublyLinkedList_first_element(const DoublyLinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_first_element", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_first_element", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return Node_get_data(LL->begin);
}

void *DoublyLinkedList_last_element(const DoublyLinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_last_element", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_last_element", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    return Node_get_data(LL->end);
}

void *DoublyLinkedList_get(const DoublyLinkedList *LL, const size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_get", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_get", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("DoublyLinkedList_get", "Index", index, LL->size-1, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    Node *node = _get_node(LL, index);
    return Node_get_data(node);
}

int DoublyLinkedList_count(const DoublyLinkedList *LL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_count", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_count", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return 0;
    Node *node = LL->begin;
    int count = 0;
    while (node != NULL) {
        if (Node_get_data(node) == data) {
            count++;
        }
        node = Node_get_next(node);
    }
    return count;
}

bool DoublyLinkedList_contains(const DoublyLinkedList *LL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_contains", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_contains", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Node *node = LL->begin;
    while (node != NULL) {
        if (Node_get_data(node) == data) {
            return true;
        }
        node = Node_get_next(node);
    }
    return false;
}

bool DoublyLinkedList_insert_at(DoublyLinkedList *LL, void *data, const size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_insert_at", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DoublyLinkedList_insert_at", "Data", data, SUPPRESS_PRINT_ERROR)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("DoublyLinkedList_insert_at", "Index", index, LL->size, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    if (index == 0) {
        return DoublyLinkedList_add_first(LL, data);
    } else if (index == LL->size) {
        return DoublyLinkedList_add_last(LL, data);
    }
    Node *node_new = Node_create(data);
    Node *node = LL->begin;
    for (size_t i = 0; i < index-1; i++) {
        node = Node_get_next(node);
    }
    Node_set_next(node_new, Node_get_next(node));
    Node_set_prev(Node_get_next(node), node_new);
    Node_set_next(node, node_new);
    Node_set_prev(node_new, node);
    LL->size++;
    LL->sort_order = UNSORTED;
    return true;
}

DoublyLinkedList *DoublyLinkedList_clone(const DoublyLinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_clone", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_clone", "Doubly Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    DoublyLinkedList *clone = DoublyLinkedList_create();
    Node *node = Node_get_next(LL->begin);
    DoublyLinkedList_add_first(clone, Node_get_data(LL->begin));
    int count = 1;
    while (node != NULL) {
        DoublyLinkedList_insert_at(clone, Node_get_data(node), count);
        count++;
        node = Node_get_next(node);
    }
    clone->sort_order = LL->sort_order;
    return clone;
}

DoublyLinkedList *DoublyLinkedList_concat(DoublyLinkedList *LL1, DoublyLinkedList *LL2) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_concat", "Linked List 1", (void *) LL1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DoublyLinkedList_concat", "Linked List 2", (void *) LL2, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    if (DoublyLinkedList_is_empty((void *) LL1)) {
        return DoublyLinkedList_clone(LL2);
    } else if (DoublyLinkedList_is_empty((void *) LL2)) {
        return DoublyLinkedList_clone(LL1);
    }
    DoublyLinkedList *LL_new = DoublyLinkedList_clone(LL1);
    Node *node = LL2->begin;
    while (node != NULL) {
        DoublyLinkedList_add_last(LL_new, Node_get_data(node));
        node = Node_get_next(node);
    }
    LL_new->sort_order = UNSORTED;
    return LL_new;
}

DoublyLinkedList *DoublyLinkedList_reverse(DoublyLinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_reverse", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_reverse", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;
    DoublyLinkedList *LL_new = DoublyLinkedList_clone(LL);
    Node *node = LL_new->begin;
    LL_new->end = LL_new->begin;
    Node *node_prev = NULL, *node_next = NULL;
    while (node != NULL) {
        node_next = Node_get_next(node);
        Node_set_next(node, node_prev);
        Node_set_prev(node, node_next);
        node_prev = node;
        node = node_next;
    }
    LL_new->begin = node_prev;
    LL_new->sort_order = (-1)*LL->sort_order;
    return LL_new;
}

bool DoublyLinkedList_is_equals_strict(const DoublyLinkedList *LL1, const DoublyLinkedList *LL2) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("DoublyLinkedList_is_equals_strict", "Linked List 1", (void *) LL1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DoublyLinkedList_is_equals_strict", "Linked List 2", (void *) LL2, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_is_equals_strict", "Linked List 1", (void *) LL1, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_is_equals_strict", "Linked List 2", (void *) LL2, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        ) || LL1->size != LL2->size
    ) return false;
    Node *node1 = LL1->begin;
    Node *node2 = LL2->begin;
    while (node1 != NULL) {
        if (Node_get_data(node1) != Node_get_data(node2)) {
            return false;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return LL1->sort_order == LL2->sort_order;
}

bool DoublyLinkedList_is_equals(const DoublyLinkedList *LL1, const DoublyLinkedList *LL2, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("DoublyLinkedList_is_equals", "Linked List 1", (void *) LL1, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DoublyLinkedList_is_equals", "Linked List 2", (void *) LL2, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_is_equals", "Linked List 1", (void *) LL1, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_is_equals", "Linked List 2", (void *) LL2, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        ) || LL1->size != LL2->size
    ) return false;
    Node *node1 = LL1->begin;
    Node *node2 = LL2->begin;
    while (node1 != NULL) {
        if (type_compare_function(Node_get_data(node1), Node_get_data(node2)) != 0) {
            return false;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return LL1->sort_order == LL2->sort_order;
}

bool DoublyLinkedList_sort_asc(DoublyLinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_sort_asc", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_sort_asc", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    _dll_merge_sort(&LL->begin, type_compare_function, 1);
    LL->sort_order = ASC;
    LL->end = _get_node(LL, LL->size-1);
    return true;
}

bool DoublyLinkedList_sort_desc(DoublyLinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_sort_desc", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_sort_desc", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    _dll_merge_sort(&LL->begin, type_compare_function, -1);
    LL->sort_order = DESC;
    LL->end = _get_node(LL, LL->size-1);
    return true;
}

bool DoublyLinkedList_sorted_insert(DoublyLinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("DoublyLinkedList_sorted_insert", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_null("DoublyLinkedList_sorted_insert", "Data", data, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_sorted_insert", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_not_sorted("DoublyLinkedList_sorted_insert", "Linked List", (void*) LL, DoublyLinkedList_is_sorted, SUPPRESS_PRINT_ERROR)
        )
    ) return false;
    Node *node = LL->begin, *node_prev = NULL, *node_new = Node_create(data);
    if (LL->sort_order == ASC) {
        while (node != NULL && type_compare_function(data, Node_get_data(node)) <=  0) {
            node_prev = node;
            node = Node_get_next(node);
        }
    } else {
        while (node != NULL && type_compare_function(data, Node_get_data(node)) >= 0) {
            node_prev = node;
            node = Node_get_next(node);
        }
    }

    if (node == LL->begin) {
        Node_set_next(node_new, LL->begin);
        LL->begin = node_new;
    } else {
        Node_set_next(node_new, Node_get_next(node_prev));
        Node_set_next(node_prev, node_new);
    }
    LL->size++;
    return true;
}

void *DoublyLinkedList_min(const DoublyLinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_min", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_min", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;

    if (DoublyLinkedList_is_sorted((void *) LL)) {
        if (LL->sort_order == ASC) {
            return Node_get_data(LL->begin);
        } else {
            return Node_get_data(LL->end);
        }
    }

    DoublyLinkedList *clone = DoublyLinkedList_clone(LL);
    DoublyLinkedList_sort_asc(clone, type_compare_function);
    void *data = Node_get_data(clone->begin);
    DoublyLinkedList_destroy(&clone);
    return data;
}

void *DoublyLinkedList_max(const DoublyLinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_max", "Linked List", (void *) LL, SUPPRESS_PRINT_ERROR),
            ExceptionHandler_is_empty("DoublyLinkedList_max", "Linked List", (void *) LL, DoublyLinkedList_is_empty, SUPPRESS_PRINT_ERROR)
        )
    ) return NULL;

    if (DoublyLinkedList_is_sorted((void *) LL)) {
        if (LL->sort_order == ASC) {
            return Node_get_data(LL->end);
        } else {
            return Node_get_data(LL->begin);
        }
    }

    DoublyLinkedList *clone = DoublyLinkedList_clone(LL);
    DoublyLinkedList_sort_desc(clone, type_compare_function);
    void *data = Node_get_data(clone->begin);
    DoublyLinkedList_destroy(&clone);
    return data;
}
