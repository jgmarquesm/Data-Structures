#include <stdlib.h>
#include <stdio.h>
#include "../include/node.h"
//#--ADD_TO_INCLUDE
#include "../include/doubly_linked_list.h"

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
    Node_set_next(slow, __DEFAULT_PTR__);
}

Node *_dll_sorted_merge(Node *left, Node *right, __TYPE_COMPARE_FUNCTION_SIGNATURE__, int order) {
    Node *DLL_begin_result = __DEFAULT_PTR__;

    if (left == NULL) {
        return right;
    } else if (right == NULL) {
        return left;
    }

    if (order == __ASC__) {
        if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(left), Node_get_data(right)) >= 0) {
            DLL_begin_result = left;
            Node_set_next(DLL_begin_result, _dll_sorted_merge(Node_get_next(left), right, __TYPE_COMPARE_FUNCTION_NAME__, order));
        } else {
            DLL_begin_result = right;
            Node_set_next(DLL_begin_result, _dll_sorted_merge(left, Node_get_next(right), __TYPE_COMPARE_FUNCTION_NAME__, order));
        }
    } else {
        if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(left), Node_get_data(right)) <= 0) {
            DLL_begin_result = left;
            Node_set_next(DLL_begin_result, _dll_sorted_merge(Node_get_next(left), right, __TYPE_COMPARE_FUNCTION_NAME__, order));
        } else {
            DLL_begin_result = right;
            Node_set_next(DLL_begin_result, _dll_sorted_merge(left, Node_get_next(right), __TYPE_COMPARE_FUNCTION_NAME__, order));
        }
    }

    return DLL_begin_result;
}

void _dll_merge_sort(Node **DLL_begin_ref, __TYPE_COMPARE_FUNCTION_SIGNATURE__, int order) {
    Node *DLL_begin = *DLL_begin_ref, *left, *right;

    if ((DLL_begin == NULL) || (Node_get_next(DLL_begin) == NULL)) {
        return;
    }

    if (order != __ASC__ && order != __DESC__) {
        fprintf(stderr, "\nERROR: on function 'DoublyLinkedList_sort_*'.\n");
        fprintf(stderr, "ERROR: Invalid sort order.\n");
        return;
    }

    _dll_left_right_split(DLL_begin, &left, &right);
    _dll_merge_sort(&left, __TYPE_COMPARE_FUNCTION_NAME__, order);
    _dll_merge_sort(&right, __TYPE_COMPARE_FUNCTION_NAME__, order);

    *DLL_begin_ref = _dll_sorted_merge(left, right, __TYPE_COMPARE_FUNCTION_NAME__, order);
}

Node *_get_node(const DoublyLinkedList *DLL, const size_t index) {
    Node *node = DLL->begin;
    for (size_t i = 0; i != index; i++) {
        node = Node_get_next(node);
    }
    return node;
}

DoublyLinkedList *DoublyLinkedList_create() {
    DoublyLinkedList *DLL = (DoublyLinkedList *) calloc(1, sizeof(DoublyLinkedList));
    DLL->begin = __DEFAULT_PTR__;
    DLL->end = __DEFAULT_PTR__;
    DLL->size = __DEFAULT_SIZE_T__;
    DLL->sort_order = __UNSORTED__;

    return DLL;
}

bool DoublyLinkedList_clean(DoublyLinkedList *DLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DoublyLinkedList_clean", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Node *node = DLL->begin;
    while (node != __DEFAULT_PTR__) {
        Node *node_next = Node_get_next(node);
        Node_destroy(&node);
        node = node_next;
    }
    Node_destroy(&node);
    DLL->begin = __DEFAULT_PTR__;
    DLL->end = __DEFAULT_PTR__;
    DLL->size = __DEFAULT_SIZE_T__;
    DLL->sort_order = __UNSORTED__;
    return __NOT_DEFAULT_BOOL__;
}

bool DoublyLinkedList_destroy(DoublyLinkedList **DLL_ref) {
    DoublyLinkedList *DLL = *DLL_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DoublyLinkedList_destroy", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    DoublyLinkedList_clean(DLL);
    free(DLL);
    *DLL_ref = __DEFAULT_PTR__;
    return __NOT_DEFAULT_BOOL__;
}

bool DoublyLinkedList_is_empty(void *DLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DoublyLinkedList_is_empty", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __NOT_DEFAULT_BOOL__;
    return ((DoublyLinkedList *) DLL)->size == __DEFAULT_SIZE_T__;
}

bool DoublyLinkedList_is_sorted(void *DLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("DoublyLinkedList_is_sorted", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    return ((DoublyLinkedList *) DLL)->sort_order != __UNSORTED__;
}

int DoublyLinkedList_sort_order(const DoublyLinkedList *DLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_sort_order", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_sort_order", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __UNSORTED__;
    return DLL->sort_order;
}

void DoublyLinkedList_print(const DoublyLinkedList *DLL, __TYPE_PRINT_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_print", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_print", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return;
    Node *node = DLL->begin;
    printf("__DEFAULT_PTR__ <- ");
    while (Node_get_next(node) != __DEFAULT_PTR__) {
        __TYPE_PRINT_FUNCTION_NAME__(Node_get_data(node));
        printf(" <- -> ");
        node = Node_get_next(node);
    }
    __TYPE_PRINT_FUNCTION_NAME__(Node_get_data(DLL->end));
    printf(" -> ");
    puts("__DEFAULT_PTR__");
}

bool DoublyLinkedList_add_first(DoublyLinkedList *DLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_add_first", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DoublyLinkedList_add_first", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Node *node = Node_create(data);
    Node_set_next(node, DLL->begin);
    if (DoublyLinkedList_is_empty(DLL)) DLL->end = node;
    else Node_set_prev(DLL->begin, node);
    DLL->begin = node;
    DLL->size++;
    DLL->sort_order = __UNSORTED__;
    return __NOT_DEFAULT_BOOL__;
}

bool DoublyLinkedList_add_last(DoublyLinkedList *DLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_add_last", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DoublyLinkedList_add_last", "Data", data, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Node *node = Node_create(data);
    Node_set_prev(node, DLL->end);
    if (DoublyLinkedList_is_empty(DLL)) DLL->begin = node;
    else Node_set_next(DLL->end, node);
    DLL->end = node;
    DLL->size++;
    DLL->sort_order = __UNSORTED__;
    return __NOT_DEFAULT_BOOL__;
}

void *DoublyLinkedList_remove_first(DoublyLinkedList *DLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_remove_first", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_remove_first", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Node *node = DLL->begin;
    void *data = Node_get_data(node);
    if (DLL->begin == DLL->end) {
        DLL->begin = DLL->end = __DEFAULT_PTR__;
    } else {
        DLL->begin = Node_get_next(node);
        Node_set_prev(DLL->begin, __DEFAULT_PTR__);
    }
    free(node);
    DLL->size--;
    return data;
}

void *DoublyLinkedList_remove_last(DoublyLinkedList *DLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_remove_last", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_remove_last", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Node *node = DLL->end;
    void *data = Node_get_data(node);
    if (DLL->begin == DLL->end) {
        DLL->begin = DLL->end = __DEFAULT_PTR__;
    } else {
        Node_set_next(Node_get_prev(node), __DEFAULT_PTR__);
        DLL->end = Node_get_prev(node);
    }
    free(node);
    DLL->size--;
    return data;
}

void *DoublyLinkedList_remove_at(DoublyLinkedList *DLL, const size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_remove_at", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_remove_at", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("DoublyLinkedList_remove_at", "Index", index, DLL->size-1, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    if (index == 0) {
        return DoublyLinkedList_remove_first(DLL);
    }
    if (index == DLL->size) {
        return DoublyLinkedList_remove_last(DLL);
    }
    Node *node = DLL->begin;
    void *data;
    for (size_t i = 0; i < index; i++) {
        node = Node_get_next(node);
    }
    Node_set_next(Node_get_prev(node), Node_get_next(node));
    Node_set_prev(Node_get_next(node), Node_get_prev(node));
    data = Node_get_data(node);
    Node_destroy(&node);
    DLL->size--;
    return data;
}

bool DoublyLinkedList_remove(DoublyLinkedList *DLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("DoublyLinkedList_remove", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DoublyLinkedList_remove", "Data", data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_remove", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Node *node = DLL->begin;
    while (node != __DEFAULT_PTR__ && __TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(node), data) != 0) {
        node = Node_get_next(node);
    }
    if (node != __DEFAULT_PTR__) {
        if (DLL->begin == node) {
            if (DLL->begin == DLL->end) {
                DLL->begin = DLL->end = __DEFAULT_PTR__;
            } else {
                DLL->begin = Node_get_next(node);
                Node_set_prev(Node_get_next(node), __DEFAULT_PTR__);
            }
        } else {
            if (DLL->end == node) {
                Node_set_next(Node_get_prev(node), __DEFAULT_PTR__);
                DLL->end = Node_get_prev(node);
            } else {
                Node_set_next(Node_get_prev(node), Node_get_next(node));
                Node_set_prev(Node_get_next(node), Node_get_prev(node));
            }
        }
        Node_destroy(&node);
        DLL->size--;
        return __NOT_DEFAULT_BOOL__;
    }
    return __DEFAULT_BOOL__;
}

size_t DoublyLinkedList_remove_all(DoublyLinkedList *DLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("DoublyLinkedList_remove_all", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DoublyLinkedList_remove_all", "Data", data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_remove_all", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_SIZE_T__;
    Node *node = DLL->begin;
    size_t count = 0;
    while (node != __DEFAULT_PTR__) {
        Node *aux_node = Node_get_next(node);
        if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(node), data) == 0) {
            if (DLL->begin == node) {
                if (DLL->begin == DLL->end) {
                    DLL->begin = DLL->end = __DEFAULT_PTR__;
                } else {
                    DLL->begin = Node_get_next(node);
                    Node_set_prev(Node_get_next(node), __DEFAULT_PTR__);
                }
            } else {
                if (DLL->end == node) {
                    DLL->end = Node_get_prev(node);
                    Node_set_next(Node_get_prev(node), __DEFAULT_PTR__);
                } else {
                    Node_set_next(Node_get_prev(node), Node_get_next(node));
                    Node_set_prev(Node_get_next(node), Node_get_prev(node));
                }
            }
            Node_destroy(&node);
            node = aux_node;
            DLL->size--;
            count++;
        } else {
            node = aux_node;
        }
    }
    return count;
}

size_t DoublyLinkedList_size(const DoublyLinkedList *DLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_size", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_size", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_SIZE_T__;
    return DLL->size;
}

void *DoublyLinkedList_first_element(const DoublyLinkedList *DLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_first_element", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_first_element", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return Node_get_data(DLL->begin);
}

void *DoublyLinkedList_last_element(const DoublyLinkedList *DLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_last_element", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_last_element", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    return Node_get_data(DLL->end);
}

void *DoublyLinkedList_get(const DoublyLinkedList *DLL, const size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_get", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_get", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("DoublyLinkedList_get", "Index", index, DLL->size-1, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    Node *node = _get_node(DLL, index);
    return Node_get_data(node);
}

size_t DoublyLinkedList_count(const DoublyLinkedList *DLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_count", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_count", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_SIZE_T__;
    Node *node = DLL->begin;
    int count = 0;
    while (node != __DEFAULT_PTR__) {
        if (Node_get_data(node) == data) {
            count++;
        }
        node = Node_get_next(node);
    }
    return count;
}

bool DoublyLinkedList_contains(const DoublyLinkedList *DLL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_contains", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_contains", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Node *node = DLL->begin;
    while (node != __DEFAULT_PTR__) {
        if (Node_get_data(node) == data) {
            return __NOT_DEFAULT_BOOL__;
        }
        node = Node_get_next(node);
    }
    return __DEFAULT_BOOL__;
}

bool DoublyLinkedList_insert_at(DoublyLinkedList *DLL, void *data, const size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_insert_at", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DoublyLinkedList_insert_at", "Data", data, __SUPPRESS_PRINT_ERROR__)
        ) ||
        anyThrows(
            1,
            ExceptionHandler_is_out_of_bounds("DoublyLinkedList_insert_at", "Index", index, DLL->size, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    if (index == 0) {
        return DoublyLinkedList_add_first(DLL, data);
    } else if (index == DLL->size) {
        return DoublyLinkedList_add_last(DLL, data);
    }
    Node *node_new = Node_create(data);
    Node *node = DLL->begin;
    for (size_t i = 0; i < index-1; i++) {
        node = Node_get_next(node);
    }
    Node_set_next(node_new, Node_get_next(node));
    Node_set_prev(Node_get_next(node), node_new);
    Node_set_next(node, node_new);
    Node_set_prev(node_new, node);
    DLL->size++;
    DLL->sort_order = __UNSORTED__;
    return __NOT_DEFAULT_BOOL__;
}

DoublyLinkedList *DoublyLinkedList_clone(const DoublyLinkedList *DLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_clone", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_clone", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    DoublyLinkedList *clone = DoublyLinkedList_create();
    Node *node = Node_get_next(DLL->begin);
    DoublyLinkedList_add_first(clone, Node_get_data(DLL->begin));
    int count = 1;
    while (node != __DEFAULT_PTR__) {
        DoublyLinkedList_insert_at(clone, Node_get_data(node), count);
        count++;
        node = Node_get_next(node);
    }
    clone->sort_order = DLL->sort_order;
    return clone;
}

DoublyLinkedList *DoublyLinkedList_concat(DoublyLinkedList *DLL1, DoublyLinkedList *DLL2) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_concat", "Linked List 1", (void *) DLL1, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DoublyLinkedList_concat", "Linked List 2", (void *) DLL2, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    if (DoublyLinkedList_is_empty((void *) DLL1)) {
        return DoublyLinkedList_clone(DLL2);
    } else if (DoublyLinkedList_is_empty((void *) DLL2)) {
        return DoublyLinkedList_clone(DLL1);
    }
    DoublyLinkedList *DLL_new = DoublyLinkedList_clone(DLL1);
    Node *node = DLL2->begin;
    while (node != __DEFAULT_PTR__) {
        DoublyLinkedList_add_last(DLL_new, Node_get_data(node));
        node = Node_get_next(node);
    }
    DLL_new->sort_order = __UNSORTED__;
    return DLL_new;
}

DoublyLinkedList *DoublyLinkedList_reverse(DoublyLinkedList *DLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_reverse", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_reverse", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;
    DoublyLinkedList *DLL_new = DoublyLinkedList_clone(DLL);
    Node *node = DLL_new->begin;
    DLL_new->end = DLL_new->begin;
    Node *node_prev = __DEFAULT_PTR__, *node_next = __DEFAULT_PTR__;
    while (node != __DEFAULT_PTR__) {
        node_next = Node_get_next(node);
        Node_set_next(node, node_prev);
        Node_set_prev(node, node_next);
        node_prev = node;
        node = node_next;
    }
    DLL_new->begin = node_prev;
    DLL_new->sort_order = (-1)*DLL->sort_order;
    return DLL_new;
}

bool DoublyLinkedList_is_equals_strict(const DoublyLinkedList *DLL1, const DoublyLinkedList *DLL2) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("DoublyLinkedList_is_equals_strict", "Linked List 1", (void *) DLL1, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DoublyLinkedList_is_equals_strict", "Linked List 2", (void *) DLL2, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_is_equals_strict", "Linked List 1", (void *) DLL1, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_is_equals_strict", "Linked List 2", (void *) DLL2, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        ) || DLL1->size != DLL2->size
    ) return __DEFAULT_BOOL__;
    Node *node1 = DLL1->begin;
    Node *node2 = DLL2->begin;
    while (node1 != __DEFAULT_PTR__) {
        if (Node_get_data(node1) != Node_get_data(node2)) {
            return __DEFAULT_BOOL__;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return DLL1->sort_order == DLL2->sort_order;
}

bool DoublyLinkedList_is_equals(const DoublyLinkedList *DLL1, const DoublyLinkedList *DLL2, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("DoublyLinkedList_is_equals", "Linked List 1", (void *) DLL1, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DoublyLinkedList_is_equals", "Linked List 2", (void *) DLL2, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_is_equals", "Linked List 1", (void *) DLL1, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_is_equals", "Linked List 2", (void *) DLL2, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        ) || DLL1->size != DLL2->size
    ) return __DEFAULT_BOOL__;
    Node *node1 = DLL1->begin;
    Node *node2 = DLL2->begin;
    while (node1 != __DEFAULT_PTR__) {
        if (__TYPE_COMPARE_FUNCTION_NAME__(Node_get_data(node1), Node_get_data(node2)) != 0) {
            return __DEFAULT_BOOL__;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return DLL1->sort_order == DLL2->sort_order;
}

bool DoublyLinkedList_sort_asc(DoublyLinkedList *DLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_sort_asc", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_sort_asc", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    _dll_merge_sort(&DLL->begin, __TYPE_COMPARE_FUNCTION_NAME__, 1);
    DLL->sort_order = __ASC__;
    DLL->end = _get_node(DLL, DLL->size-1);
    return __NOT_DEFAULT_BOOL__;
}

bool DoublyLinkedList_sort_desc(DoublyLinkedList *DLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_sort_desc", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_sort_desc", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    _dll_merge_sort(&DLL->begin, __TYPE_COMPARE_FUNCTION_NAME__, -1);
    DLL->sort_order = __DESC__;
    DLL->end = _get_node(DLL, DLL->size-1);
    return __NOT_DEFAULT_BOOL__;
}

bool DoublyLinkedList_sorted_insert(DoublyLinkedList *DLL, void *data, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("DoublyLinkedList_sorted_insert", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_null("DoublyLinkedList_sorted_insert", "Data", data, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_sorted_insert", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_not_sorted("DoublyLinkedList_sorted_insert", "Doubly Linked List", (void*) DLL, DoublyLinkedList_is_sorted, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_BOOL__;
    Node *node = DLL->begin, *node_prev = __DEFAULT_PTR__, *node_new = Node_create(data);
    if (DLL->sort_order == __ASC__) {
        while (node != __DEFAULT_PTR__ && __TYPE_COMPARE_FUNCTION_NAME__(data, Node_get_data(node)) <=  0) {
            node_prev = node;
            node = Node_get_next(node);
        }
    } else {
        while (node != __DEFAULT_PTR__ && __TYPE_COMPARE_FUNCTION_NAME__(data, Node_get_data(node)) >= 0) {
            node_prev = node;
            node = Node_get_next(node);
        }
    }

    if (node == DLL->begin) {
        Node_set_next(node_new, DLL->begin);
        DLL->begin = node_new;
    } else {
        Node_set_next(node_new, Node_get_next(node_prev));
        Node_set_next(node_prev, node_new);
    }
    DLL->size++;
    return __NOT_DEFAULT_BOOL__;
}

void *DoublyLinkedList_min(const DoublyLinkedList *DLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_min", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_min", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;

    if (DoublyLinkedList_is_sorted((void *) DLL)) {
        if (DLL->sort_order == __ASC__) {
            return Node_get_data(DLL->begin);
        } else {
            return Node_get_data(DLL->end);
        }
    }

    DoublyLinkedList *clone = DoublyLinkedList_clone(DLL);
    DoublyLinkedList_sort_asc(clone, __TYPE_COMPARE_FUNCTION_NAME__);
    void *data = Node_get_data(clone->begin);
    DoublyLinkedList_destroy(&clone);
    return data;
}

void *DoublyLinkedList_max(const DoublyLinkedList *DLL, __TYPE_COMPARE_FUNCTION_SIGNATURE__) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("DoublyLinkedList_max", "Doubly Linked List", (void *) DLL, __SUPPRESS_PRINT_ERROR__),
            ExceptionHandler_is_empty("DoublyLinkedList_max", "Doubly Linked List", (void *) DLL, DoublyLinkedList_is_empty, __SUPPRESS_PRINT_ERROR__)
        )
    ) return __DEFAULT_PTR__;

    if (DoublyLinkedList_is_sorted((void *) DLL)) {
        if (DLL->sort_order == __ASC__) {
            return Node_get_data(DLL->end);
        } else {
            return Node_get_data(DLL->begin);
        }
    }

    DoublyLinkedList *clone = DoublyLinkedList_clone(DLL);
    DoublyLinkedList_sort_desc(clone, __TYPE_COMPARE_FUNCTION_NAME__);
    void *data = Node_get_data(clone->begin);
    DoublyLinkedList_destroy(&clone);
    return data;
}
