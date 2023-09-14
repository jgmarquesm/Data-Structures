#include "../include/doubly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/node.h"
#include "../include/exception_handler.h"
//#--ADD_TO_INCLUDE

#define UNSORTED 0
#define ASC 1
#define DESC -1

typedef struct _linked_list {
    Node *begin;
    Node *end;
    size_t size;
    int sort_order;
} LinkedList;

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
        fprintf(stderr, "\nERROR: on function 'LinkedList_sort_*'.\n");
        fprintf(stderr, "ERROR: Invalid sort order.\n");
        return;
    }

    _dll_left_right_split(LL_begin, &left, &right);
    _dll_merge_sort(&left, type_compare_function, order);
    _dll_merge_sort(&right, type_compare_function, order);

    *LL_begin_ref = _dll_sorted_merge(left, right, type_compare_function, order);
}

Node *_get_node(const LinkedList *LL, const size_t index) {
    Node *node = LL->begin;
    for (size_t i = 0; i != index; i++) {
        node = Node_get_next(node);
    }
    return node;
}

LinkedList *LinkedList_create() {
    LinkedList *LL = (LinkedList *) calloc(1, sizeof(LinkedList));
    LL->begin = NULL;
    LL->end = NULL;
    LL->size = 0;
    LL->sort_order = UNSORTED;

    return LL;
}

void LinkedList_clean(LinkedList *LL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("LinkedList_clean", "Linked List", ((void *) LL))
        )
    ) return;
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
}

void LinkedList_destroy(LinkedList **LL_ref) {
    LinkedList *LL = *LL_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("LinkedList_destroy", "Linked List", ((void *) LL))
        )
    ) return;
    LinkedList_clean(LL);
    free(LL);
    *LL_ref = NULL;
}

bool LinkedList_is_empty(void *LL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("LinkedList_is_empty", "Linked List", ((void *) LL))
        )
    ) return true;
    return ((LinkedList *) LL)->size == 0;
}

bool LinkedList_is_sorted(void *LL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("LinkedList_is_sorted", "Linked List", ((void *) LL))
        )
    ) return true;
    return ((LinkedList *) LL)->sort_order != UNSORTED;
}

int LinkedList_sort_order(const LinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_sort_order", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_sort_order", "Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return UNSORTED;
    return LL->sort_order;
}

void LinkedList_print(const LinkedList *LL, void (*type_print_function)(void *data)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_print", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_print", "Linked List", ((void *) LL), LinkedList_is_empty)
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

void LinkedList_add_first(LinkedList *LL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_add_first", "Linked List", ((void *) LL)),
            ExceptionHandler_is_null("LinkedList_add_first", "Data", data)
        )
    ) return;
    Node *node = Node_create(data);
    Node_set_next(node, LL->begin);
    if (LinkedList_is_empty(LL)) LL->end = node;
    else Node_set_prev(LL->begin, node);
    printf("data: %d\n", *((int *) Node_get_data(LL->end)));
    LL->begin = node;
    LL->size++;
    LL->sort_order = UNSORTED;
}

void LinkedList_add_last(LinkedList *LL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_add_last", "Linked List", ((void *) LL)),
            ExceptionHandler_is_null("LinkedList_add_last", "Data", data)
        )
    ) return;
    Node *node = Node_create(data);
    Node_set_prev(node, LL->end);
    if (LinkedList_is_empty(LL)) LL->begin = node;
    else Node_set_next(LL->end, node);
    LL->end = node;
    LL->size++;
    LL->sort_order = UNSORTED;
}

void *LinkedList_remove_first(LinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_remove_first", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_remove_first", "Linked List", ((void *) LL), LinkedList_is_empty)
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

void *LinkedList_remove_last(LinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_remove_last", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_remove_last", "Linked List", ((void *) LL), LinkedList_is_empty)
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

void *LinkedList_remove_at(LinkedList *LL, const size_t index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("LinkedList_remove_at", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_remove_at", "Linked List", ((void *) LL), LinkedList_is_empty),
            ExceptionHandler_is_out_of_bounds("LinkedList_remove_at", "Index", index, LL->size-1)
        )
    ) return NULL;
    if (index == 0) {
        return LinkedList_remove_first(LL);
    }
    if (index == LL->size) {
        return LinkedList_remove_last(LL);
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

void LinkedList_remove(LinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_remove", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_remove", "Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return;
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
    }
}

void LinkedList_remove_all(LinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_remove_all", " Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_remove_all", " Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return;
    Node *node = LL->begin;
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
        } else {
            node = aux_node;
        }
    }
}

size_t LinkedList_size(const LinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_size", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_size", "Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return 0;
    return LL->size;
}

void *LinkedList_first_element(const LinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_first_element", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_first_element", "Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return NULL;
    return Node_get_data(LL->begin);
}

void *LinkedList_last_element(const LinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_last_element", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_last_element", "Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return NULL;
    return Node_get_data(LL->end);
}

void *LinkedList_get(const LinkedList *LL, const size_t index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("LinkedList_get", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_get", "Linked List", ((void *) LL), LinkedList_is_empty),
            ExceptionHandler_is_out_of_bounds("LinkedList_get", "Index", index, LL->size-1)
        )
    ) return NULL;
    Node *node = _get_node(LL, index);
    return Node_get_data(node);
}

int LinkedList_count(const LinkedList *LL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_count", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_count", "Linked List", ((void *) LL), LinkedList_is_empty)
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

bool LinkedList_contains(const LinkedList *LL, void *data) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_contains", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_contains", "Linked List", ((void *) LL), LinkedList_is_empty)
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

void LinkedList_insert_at(LinkedList *LL, void *data, const size_t index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("LinkedList_insert_at", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_insert_at", "Linked List", ((void *) LL), LinkedList_is_empty),
            ExceptionHandler_is_out_of_bounds("LinkedList_insert_at", "Index", index, LL->size)
        )
    ) return;
    if (index == 0) {
            LinkedList_add_first(LL, data);
    } else if (index == LL->size) {
        LinkedList_add_last(LL, data);
    } else {
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
    }
}

LinkedList *LinkedList_clone(const LinkedList *LL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("LinkedList_clone", "Linked List", ((void *) LL))
        )
    ) return NULL;
    LinkedList *clone = LinkedList_create();
    Node *node = Node_get_next(LL->begin);
    LinkedList_add_first(clone, Node_get_data(LL->begin));
    int count = 1;
    while (node != NULL) {
        LinkedList_insert_at(clone, Node_get_data(node), count);
        count++;
        node = Node_get_next(node);
    }
    clone->sort_order = LL->sort_order;
    return clone;
}

LinkedList *LinkedList_concat(LinkedList *LL1, LinkedList *LL2) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_concat", "Linked List 1", ((void *) LL1)),
            ExceptionHandler_is_null("LinkedList_concat", "Linked List 2", ((void *) LL2))
        )
    ) return NULL;
    if (LinkedList_is_empty((void *) LL1)) {
        return LinkedList_clone(LL2);
    } else if (LinkedList_is_empty((void *) LL2)) {
        return LinkedList_clone(LL1);
    }
    LinkedList *LL_new = LinkedList_clone(LL1);
    Node *node = LL2->begin;
    while (node != NULL) {
        LinkedList_add_last(LL_new, Node_get_data(node));
        node = Node_get_next(node);
    }
    LL_new->sort_order = UNSORTED;
    return LL_new;
}

LinkedList *LinkedList_reverse(LinkedList *LL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_reverse", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_reverse", "Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return NULL;
    LinkedList *LL_new = LinkedList_clone(LL);
    Node *node = LL_new->begin;
    LL_new->end = LL_new->begin;
    Node *node_prev = NULL, *node_next = NULL;
    while (node != NULL) {
        node_next = Node_get_next(node);
        Node_set_next(node, node_prev);
        node_prev = node;
        node = node_next;
    }
    LL_new->begin = node_prev;
    LL_new->sort_order = (-1)*LL->sort_order;
    return LL_new;
}

bool LinkedList_is_equals_strict(const LinkedList *LL1, const LinkedList *LL2) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("LinkedList_is_equals_strict", "Linked List 1", ((void *) LL1)),
            ExceptionHandler_is_null("LinkedList_is_equals_strict", "Linked List 2", ((void *) LL2)),
            ExceptionHandler_is_empty("LinkedList_is_equals_strict", "Linked List 1", ((void *) LL1), LinkedList_is_empty),
            ExceptionHandler_is_empty("LinkedList_is_equals_strict", "Linked List 2", ((void *) LL2), LinkedList_is_empty)
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

bool LinkedList_is_equals(const LinkedList *LL1, const LinkedList *LL2, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("LinkedList_is_equals", "Linked List 1", ((void *) LL1)),
            ExceptionHandler_is_null("LinkedList_is_equals", "Linked List 2", ((void *) LL2)),
            ExceptionHandler_is_empty("LinkedList_is_equals", "Linked List 1", ((void *) LL1), LinkedList_is_empty),
            ExceptionHandler_is_empty("LinkedList_is_equals", "Linked List 2", ((void *) LL2), LinkedList_is_empty)
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

void LinkedList_sort_asc(LinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_sort_asc", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_sort_asc", "Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return;
    _dll_merge_sort(&LL->begin, type_compare_function, 1);
    LL->sort_order = ASC;
    LL->end = _get_node(LL, LL->size-1);
}

void LinkedList_sort_desc(LinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_sort_desc", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_sort_desc", "Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return;
    _dll_merge_sort(&LL->begin, type_compare_function, -1);
    LL->sort_order = DESC;
    LL->end = _get_node(LL, LL->size-1);
}

void LinkedList_sorted_insert(LinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("LinkedList_sorted_insert", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_sorted_insert", "Linked List", ((void *) LL), LinkedList_is_empty),
            ExceptionHandler_is_not_sorted("LinkedList_sorted_insert", "Linked List", (void*) LL, LinkedList_is_sorted)
        )
    ) return;
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
}

void *LinkedList_min(const LinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_min", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_min", "Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return NULL;

    if (LinkedList_is_sorted((void *) LL)) {
        if (LL->sort_order == ASC) {
            return Node_get_data(LL->begin);
        } else {
            return Node_get_data(LL->end);
        }
    }

    LinkedList *clone = LinkedList_clone(LL);
    LinkedList_sort_asc(clone, type_compare_function);
    puts("IHA");
    void *data = Node_get_data(clone->begin);
    LinkedList_destroy(&clone);
    return data;
}

void *LinkedList_max(const LinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("LinkedList_max", "Linked List", ((void *) LL)),
            ExceptionHandler_is_empty("LinkedList_max", "Linked List", ((void *) LL), LinkedList_is_empty)
        )
    ) return NULL;

    if (LinkedList_is_sorted((void *) LL)) {
        if (LL->sort_order == ASC) {
            return Node_get_data(LL->end);
        } else {
            return Node_get_data(LL->begin);
        }
    }

    LinkedList *clone = LinkedList_clone(LL);
    LinkedList_sort_desc(clone, type_compare_function);
    void *data = Node_get_data(clone->begin);
    LinkedList_destroy(&clone);
    return data;
}
