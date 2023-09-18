#include "../include/singly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/node.h"
//#--ADD_TO_INCLUDE

#define UNSORTED 0
#define ASC 1
#define DESC -1

typedef struct _singly_linked_list {
    Node *begin;
    Node *end;
    size_t size;
    int sort_order;
} SinglyLinkedList;

void _sll_left_right_split(Node *node, Node **left_ref, Node **right_ref) {
    Node *slow = node, *fast = Node_get_next(node);

    while (fast != NULL && Node_get_next(fast) != NULL) {
        slow = Node_get_next(slow);
        fast = Node_get_next(Node_get_next(fast));
    }

    *left_ref = node;
    *right_ref = Node_get_next(slow);
    Node_set_next(slow, NULL);
}

Node *_sll_sorted_merge(Node *left, Node *right, int (*type_compare_function)(void *data1, void *data2), int order) {
    Node *SLL_begin_result = NULL;

    if (left == NULL) {
        return right;
    } else if (right == NULL) {
        return left;
    }

    if (order == ASC) {
        if (type_compare_function(Node_get_data(left), Node_get_data(right)) >= 0) {
            SLL_begin_result = left;
            Node_set_next(SLL_begin_result, _sll_sorted_merge(Node_get_next(left), right, type_compare_function, order));
        } else {
            SLL_begin_result = right;
            Node_set_next(SLL_begin_result, _sll_sorted_merge(left, Node_get_next(right), type_compare_function, order));
        }
    } else {
        if (type_compare_function(Node_get_data(left), Node_get_data(right)) <= 0) {
            SLL_begin_result = left;
            Node_set_next(SLL_begin_result, _sll_sorted_merge(Node_get_next(left), right, type_compare_function, order));
        } else {
            SLL_begin_result = right;
            Node_set_next(SLL_begin_result, _sll_sorted_merge(left, Node_get_next(right), type_compare_function, order));
        }
    }

    return SLL_begin_result;
}

void _sll_merge_sort(Node **SLL_begin_ref, int (*type_compare_function)(void *data1, void *data2), int order) {
    Node *SLL_begin = *SLL_begin_ref, *left, *right;

    if ((SLL_begin == NULL) || (Node_get_next(SLL_begin) == NULL)) {
        return;
    }

    if (order != ASC && order != DESC) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_sort_*'.\n");
        fprintf(stderr, "ERROR: Invalid sort order.\n");
        exit(EXIT_FAILURE);
    }

    _sll_left_right_split(SLL_begin, &left, &right);
    _sll_merge_sort(&left, type_compare_function, order);
    _sll_merge_sort(&right, type_compare_function, order);

    *SLL_begin_ref = _sll_sorted_merge(left, right, type_compare_function, order);
}

Node *_get_node(const SinglyLinkedList *SLL, const size_t index) {
    Node *node = SLL->begin;
    for (size_t i = 0; i < index; i++) {
        node = Node_get_next(node);
    }
    return node;
}

SinglyLinkedList *SinglyLinkedList_create() {
    SinglyLinkedList *SLL = (SinglyLinkedList *) calloc(1, sizeof(SinglyLinkedList));
    SLL->end = SLL->begin = NULL;
    SLL->size = 0;
    SLL->sort_order = UNSORTED;
    return  SLL;
}

void SinglyLinkedList_clean(SinglyLinkedList *SLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("SinglyLinkedList_clean", "Singly Linked List", (void *) SLL)
        )
    ) return;
    Node *node = SLL->begin;
    while (node != NULL) {
        Node *node_next = Node_get_next(node);
        Node_destroy(&node);
        node = node_next;
    }
    SLL->begin = NULL;
    SLL->end = NULL;
    SLL->size = 0;
    SLL->sort_order = UNSORTED;
}

void SinglyLinkedList_destroy(SinglyLinkedList **SLL_ref) {
    SinglyLinkedList *SLL = *SLL_ref;
    if (anyThrows(
            1,
            ExceptionHandler_is_null("SinglyLinkedList_destroy", "Singly Linked List", (void *) SLL)
        )
    ) return;
    SinglyLinkedList_clean(SLL);
    free(SLL);
    *SLL_ref = NULL;
}

bool SinglyLinkedList_is_empty(void *SLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("SinglyLinkedList_is_empty", "Singly Linked List", (void *) SLL)
        )
    ) return false;
    return (((SinglyLinkedList *) SLL)->begin == NULL && ((SinglyLinkedList *) SLL)->end == NULL);
}

bool SinglyLinkedList_is_sorted(void *SLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("SinglyLinkedList_is_sorted", "Singly Linked List", (void *) SLL)
        )
    ) return false;
    return ((SinglyLinkedList *) SLL)->sort_order != UNSORTED;
}

int SinglyLinkedList_sort_order(const SinglyLinkedList *SLL) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("SinglyLinkedList_sort_order", "Singly Linked List", (void *) SLL)
        )
    ) return 0;
    return SLL->sort_order;
}

void SinglyLinkedList_print(const SinglyLinkedList *SLL, void (*type_print_function)(void *data)) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("SinglyLinkedList_print", "Singly Linked List", (void *) SLL)
        )
    ) return;
    Node *node = SLL->begin;
    printf("SLL -> ");
    while (node != NULL) {
        type_print_function(Node_get_data(node));
        printf(" -> ");
        node = Node_get_next(node);
    }
    puts("NULL");
}

void SinglyLinkedList_add_first(SinglyLinkedList *SLL, void *data) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("SinglyLinkedList_add_first", "Singly Linked List", (void *) SLL)
        )
    ) return;
    Node *node_new = Node_create(data);
    Node_set_next(node_new, SLL->begin);
    if (SinglyLinkedList_is_empty(SLL)) {
        SLL->end = node_new;
    }
    SLL->begin = node_new;
    SLL->size++;
    SLL->sort_order = UNSORTED;
}

void SinglyLinkedList_add_last(SinglyLinkedList *SLL, void *data) {
    if (anyThrows(
            1,
            ExceptionHandler_is_null("SinglyLinkedList_add_last", "Singly Linked List", (void *) SLL)
        )
    ) return;
    Node *node_new = Node_create(data);
    if (SinglyLinkedList_is_empty(SLL)) {
        SLL->begin = SLL->end = node_new;
    } else {
        Node_set_next(SLL->end, node_new);
        SLL->end = Node_get_next(SLL->end);
    }
    SLL->size++;
    SLL->sort_order = UNSORTED;
}

void *SinglyLinkedList_remove_first(SinglyLinkedList *SLL) {
    if (anyThrows(
         2,
         ExceptionHandler_is_null("SinglyLinkedList_remove_first", "SinglyLinkedList", (void *) SLL),
         ExceptionHandler_is_empty("SinglyLinkedList_remove_first", "SinglyLinkedList", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return NULL;
    Node *node = SLL->begin;
    void *data = Node_get_data(node);
    SLL->begin = Node_get_next(node);
    Node_destroy(&node);
    SLL->size--;
    return data;
}

void *SinglyLinkedList_remove_last(SinglyLinkedList *SLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_remove_last", "SinglyLinkedList", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_remove_last", "SinglyLinkedList", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return NULL;
    void *data = SinglyLinkedList_remove_at(SLL, SLL->size-1);
    return data;
}

void *SinglyLinkedList_remove_at(SinglyLinkedList *SLL, const size_t index) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_remove_at", "SinglyLinkedList", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_remove_at", "SinglyLinkedList", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return NULL;
    Node *node_prev = NULL;
    Node *node = SLL->begin;
    for (size_t i = 0; i < index; i++) {
        node_prev = node;
        node = Node_get_next(node);
    }
    Node_set_next(node_prev, Node_get_next(node));
    void *data = Node_get_data(node);
    Node_destroy(&node);
    SLL->size--;
    return data;
}

void SinglyLinkedList_remove(SinglyLinkedList *SLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_remove", "SinglyLinkedList", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_remove", "SinglyLinkedList", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return;
    Node *node_prev = NULL;
    Node *node = SLL->begin;
    while (node != NULL && type_compare_function(Node_get_data(node), data) != 0) {
        node_prev = node;
        node = Node_get_next(node);
    }
    if (node != NULL) {
        if (SLL->end == node) {
            SLL->end = node_prev;
        }
        if (SLL->begin == node) {
            SLL->begin = Node_get_next(node);
        } else {
            Node_set_next(node_prev, Node_get_next(node));
        }
        Node_destroy(&node);
        SLL->size--;
    }
}

void SinglyLinkedList_remove_all(SinglyLinkedList *SLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_remove_all", "SinglyLinkedList", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_remove_all", "SinglyLinkedList", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return;
    Node *node_prev = SLL->begin;
    Node *node = Node_get_next(SLL->begin);
    while (node != NULL) {
        if (type_compare_function(Node_get_data(SLL->begin), data) == 0) {
            SLL->begin = Node_get_next(node_prev);
            Node_destroy(&node_prev);
            node_prev = SLL->begin;
            node = Node_get_next(node);
            SLL->size--;
        }
        if (type_compare_function(Node_get_data(node), data) == 0) {
            Node_set_next(node_prev, Node_get_next(node));
            if (SLL->end == node) {
                SLL->end = node_prev;
            }
            Node_destroy(&node);
            node = Node_get_next(node_prev);
            SLL->size--;
        } else {
            node_prev = node;
            node = Node_get_next(node);
        }
    }
}

size_t SinglyLinkedList_size(const SinglyLinkedList *SLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_size", "SinglyLinkedList", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_size", "SinglyLinkedList", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return 0;
    return SLL->size;
}

void *SinglyLinkedList_first_element(const SinglyLinkedList *SLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_first_element", "SinglyLinkedList", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_first_element", "SinglyLinkedList", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return NULL;
    return Node_get_data(SLL->begin);
}

void *SinglyLinkedList_last_element(const SinglyLinkedList *SLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_last_element", "SinglyLinkedList", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_last_element", "SinglyLinkedList", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return NULL;
    return Node_get_data(SLL->end);
}

void *SinglyLinkedList_get(const SinglyLinkedList *SLL, const size_t index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("SinglyLinkedList_get", "Singly Linked List", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_get", "Singly Linked List", (void *) SLL, SinglyLinkedList_is_empty),
            ExceptionHandler_is_out_of_bounds("SinglyLinkedList_get", "Index", index, SLL->size-1)
        )
    ) return NULL;
    Node *node = _get_node(SLL, index);
    return Node_get_data(node);
}

int SinglyLinkedList_count(const SinglyLinkedList *SLL, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("SinglyLinkedList_count", "Singly Linked List", (void *) SLL),
            ExceptionHandler_is_null("SinglyLinkedList_count", "Data", data),
            ExceptionHandler_is_empty("SinglyLinkedList_count", "Singly Linked List", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return 0;
    Node *node = SLL->begin;
    int count = 0;
    while (node != NULL) {
        if (Node_get_data(node) == data) {
            count++;
        }
        node = Node_get_next(node);
    }
    return count;
}

bool SinglyLinkedList_contains(const SinglyLinkedList *SLL, void *data) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("SinglyLinkedList_contains", "Singly Linked List", (void *) SLL),
            ExceptionHandler_is_null("SinglyLinkedList_contains", "Data", data),
            ExceptionHandler_is_empty("SinglyLinkedList_contains", "Singly Linked List", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return false;
    Node *node = SLL->begin;
    while (node != NULL) {
        if (Node_get_data(node) == data) {
            return true;
        }
        node = Node_get_next(node);
    }
    return false;
}

void SinglyLinkedList_insert_at(SinglyLinkedList *SLL, void *data, const size_t index) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("SinglyLinkedList_insert_at", "Singly Linked List", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_insert_at", "Singly Linked List", (void *) SLL, SinglyLinkedList_is_empty),
            ExceptionHandler_is_out_of_bounds("SinglyLinkedList_insert_at", "Index", index, SLL->size)
        )
    ) return;
    if (index == 0) {
        SinglyLinkedList_add_first(SLL, data);
    } else if (index == SLL->size) {
        SinglyLinkedList_add_last(SLL, data);
    } else {
        Node *node_new = Node_create(data);
        Node *node_prev = NULL;
        Node *node = SLL->begin;
        for (size_t i = 0; i != index; i++) {
            node_prev = node;
            node = Node_get_next(node);
        }
        Node_set_next(node_new, Node_get_next(node_prev));
        Node_set_next(node_prev, node_new);
        SLL->size++;
        SLL->sort_order = UNSORTED;
    }
}

SinglyLinkedList *SinglyLinkedList_clone(const SinglyLinkedList *SLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_clone", "Singly Linked List", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_clone", "Singly Linked List", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return NULL;
    SinglyLinkedList *clone = SinglyLinkedList_create();
    Node *node = Node_get_next(SLL->begin);
    SinglyLinkedList_add_first(clone, Node_get_data(SLL->begin));
    int count = 1;
    while (node != NULL) {
        SinglyLinkedList_insert_at(clone, Node_get_data(node), count);
        count++;
        node = Node_get_next(node);
    }
    clone->sort_order = SLL->sort_order;
    return clone;
}

SinglyLinkedList *SinglyLinkedList_concat(SinglyLinkedList *SLL1, SinglyLinkedList *SLL2) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_concat", "Singly Linked List 1", (void *) SLL1),
            ExceptionHandler_is_null("SinglyLinkedList_concat", "Singly Linked List 2", (void *) SLL2)
        )
    ) return NULL;
    if (SinglyLinkedList_is_empty(SLL1)) {
        return SinglyLinkedList_clone(SLL2);
    } else if (SinglyLinkedList_is_empty(SLL2)) {
        return SinglyLinkedList_clone(SLL1);
    }
    SinglyLinkedList *SLL_new = SinglyLinkedList_clone(SLL1);
    Node *node = SLL2->begin;
    while (node != NULL) {
        SinglyLinkedList_add_last(SLL_new, Node_get_data(node));
        node = Node_get_next(node);
    }
    SLL_new->sort_order = UNSORTED;
    return SLL_new;
}

SinglyLinkedList *SinglyLinkedList_reverse(SinglyLinkedList *SLL) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_concat", "Singly Linked List", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_concat", "Singly Linked List", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return NULL;
    SinglyLinkedList *SLL_new = SinglyLinkedList_clone(SLL);
    Node *node = SLL_new->begin;
    SLL_new->end = SLL_new->begin;
    Node *node_prev = NULL, *node_next = NULL;
    while (node != NULL) {
        node_next = Node_get_next(node);
        Node_set_next(node, node_prev);
        node_prev = node;
        node = node_next;
    }
    SLL_new->begin = node_prev;
    SLL_new->sort_order = (-1)*SLL->sort_order;
    return SLL_new;
}

bool SinglyLinkedList_is_equals_strict(const SinglyLinkedList *SLL1, const SinglyLinkedList *SLL2) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("SinglyLinkedList_is_equals_strict", "Singly Linked List 1", (void *) SLL1),
            ExceptionHandler_is_null("SinglyLinkedList_is_equals_strict", "Singly Linked List 2", (void *) SLL2),
            ExceptionHandler_is_empty("SinglyLinkedList_is_equals_strict", "Singly Linked List 1", (void *) SLL1, SinglyLinkedList_is_empty),
            ExceptionHandler_is_empty("SinglyLinkedList_is_equals_strict", "Singly Linked List 2", (void *) SLL2, SinglyLinkedList_is_empty)
        ) || SLL1->size != SLL2->size
    ) return false;
    Node *node1 = SLL1->begin;
    Node *node2 = SLL2->begin;
    while (node1 != NULL) {
        if (Node_get_data(node1) != Node_get_data(node2)) {
            return false;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return SLL1->sort_order == SLL2->sort_order;
}

bool SinglyLinkedList_is_equals(const SinglyLinkedList *SLL1, const SinglyLinkedList *SLL2, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            4,
            ExceptionHandler_is_null("SinglyLinkedList_is_equals'", "Singly Linked List 1", (void *) SLL1),
            ExceptionHandler_is_null("SinglyLinkedList_is_equals", "Singly Linked List 2", (void *) SLL2),
            ExceptionHandler_is_empty("SinglyLinkedList_is_equals", "Singly Linked List 1", (void *) SLL1, SinglyLinkedList_is_empty),
            ExceptionHandler_is_empty("SinglyLinkedList_is_equals", "Singly Linked List 2", (void *) SLL2, SinglyLinkedList_is_empty)
        ) || SLL1->size != SLL2->size
    ) return false;
    Node *node1 = SLL1->begin;
    Node *node2 = SLL2->begin;
    while (node1 != NULL) {
        if (type_compare_function(Node_get_data(node1), Node_get_data(node2)) != 0) {
            return false;
        }
        node1 = Node_get_next(node1);
        node2 = Node_get_next(node2);
    }
    return SLL1->sort_order == SLL2->sort_order;
}

void SinglyLinkedList_sort_asc(SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_sort_asc", "Singly Linked List", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_sort_asc", "Singly Linked List", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return;
    _sll_merge_sort(&SLL->begin, type_compare_function, 1);
    SLL->sort_order = ASC;
    SLL->end = _get_node(SLL, SLL->size-1);
}

void SinglyLinkedList_sort_desc(SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_sort_desc", "Singly Linked List", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_sort_desc", "Singly Linked List", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return;
    _sll_merge_sort(&SLL->begin, type_compare_function, -1);
    SLL->sort_order = DESC;
    SLL->end = _get_node(SLL, SLL->size-1);
}

void SinglyLinkedList_sorted_insert(SinglyLinkedList *SLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            3,
            ExceptionHandler_is_null("SinglyLinkedList_sorted_insert", "Singly Linked List", ((void *) SLL)),
            ExceptionHandler_is_empty("SinglyLinkedList_sorted_insert", "Singly Linked List", ((void *) SLL), SinglyLinkedList_is_empty),
            ExceptionHandler_is_not_sorted("SinglyLinkedList_sorted_insert", "Singly Linked List", (void*) SLL, SinglyLinkedList_is_sorted)
        )
    ) return;

    Node *node = SLL->begin, *node_prev = NULL, *node_new = Node_create(data);

    if (SLL->sort_order == ASC) {
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

    if (node == SLL->begin) {
        Node_set_next(node_new, SLL->begin);
        SLL->begin = node_new;
    } else {
        Node_set_next(node_new, Node_get_next(node_prev));
        Node_set_next(node_prev, node_new);
    }
    SLL->size++;
}

void *SinglyLinkedList_min(const SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_min", "Singly Linked List", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_min", "Singly Linked List", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return NULL;

    if (SinglyLinkedList_is_sorted((void *) SLL)) {
        if (SLL->sort_order == ASC) {
            return Node_get_data(SLL->begin);
        } else {
            return Node_get_data(SLL->end);
        }
    }

    SinglyLinkedList *clone = SinglyLinkedList_clone(SLL);
    SinglyLinkedList_sort_asc(clone, type_compare_function);
    void *data = Node_get_data(clone->begin);
    SinglyLinkedList_destroy(&clone);
    return data;
}

void *SinglyLinkedList_max(const SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (anyThrows(
            2,
            ExceptionHandler_is_null("SinglyLinkedList_min", "Singly Linked List", (void *) SLL),
            ExceptionHandler_is_empty("SinglyLinkedList_min", "Singly Linked List", (void *) SLL, SinglyLinkedList_is_empty)
        )
    ) return NULL;

    if (SinglyLinkedList_is_sorted((void *) SLL)) {
        if (SLL->sort_order == ASC) {
            return Node_get_data(SLL->end);
        } else {
            return Node_get_data(SLL->begin);
        }
    }

    SinglyLinkedList *clone = SinglyLinkedList_clone(SLL);
    SinglyLinkedList_sort_desc(clone, type_compare_function);
    void *data = Node_get_data(clone->begin);
    SinglyLinkedList_destroy(&clone);
    return data;
}
