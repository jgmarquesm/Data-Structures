#include "../include/doubly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

#define UNSORTED 0
#define ASC 1
#define DESC -1

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

typedef struct _linked_list {
    Node *begin;
    Node *end;
    size_t size;
    int sort_order;
} LinkedList;

void _left_right_split(Node *node, Node **left_ref, Node **right_ref) {
    Node *slow = node, *fast = node->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *left_ref = node;
    *right_ref = slow->next;
    slow->next = NULL;
}

Node *_sorted_merge(Node *left, Node *right, int (*type_compare_function)(void *data1, void *data2), int order) {
    Node *LL_begin_result = NULL;

    if (left == NULL) {
        return right;
    } else if (right == NULL) {
        return left;
    }

    if (order == ASC) {
        if (type_compare_function(left->data, right->data) >= 0) {
            LL_begin_result = left;
            LL_begin_result->next = _sorted_merge(left->next, right, type_compare_function, order);
        } else {
            LL_begin_result = right;
            LL_begin_result->next = _sorted_merge(left, right->next, type_compare_function, order);
        }
    } else {
        if (type_compare_function(left->data, right->data) <= 0) {
            LL_begin_result = left;
            LL_begin_result->next = _sorted_merge(left->next, right, type_compare_function, order);
        } else {
            LL_begin_result = right;
            LL_begin_result->next = _sorted_merge(left, right->next, type_compare_function, order);
        }
    }

    return LL_begin_result;
}

void _merge_sort(Node **LL_begin_ref, int (*type_compare_function)(void *data1, void *data2), int order) {
    Node *LL_begin = *LL_begin_ref, *left, *right;

    if ((LL_begin == NULL) || (LL_begin->next == NULL)) {
        return;
    }

    if (order != ASC && order != DESC) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_sort_*'.\n");
        fprintf(stderr, "ERROR: Invalid sort order.\n");
        exit(EXIT_FAILURE);
    }

    _left_right_split(LL_begin, &left, &right);
    _merge_sort(&left, type_compare_function, order);
    _merge_sort(&right, type_compare_function, order);

    *LL_begin_ref = _sorted_merge(left, right, type_compare_function, order);
}

Node *_get_node(const LinkedList *LL, const size_t index) {
    Node *node = LL->begin;
    for (size_t i = 0; i != index; i++) {
        node = node->next;
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
    Node *node = LL->begin;
    while (node != NULL) {
        Node *node_next = node->next;
        free(node);
        node = node_next;
    }
    LL->begin = NULL;
    LL->end = NULL;
    LL->size = 0;
    LL->sort_order = UNSORTED;
}

void LinkedList_destroy(LinkedList **LL_ref) {
    LinkedList *LL = *LL_ref;
    LinkedList_clean(LL);
    free(LL);
    *LL_ref = NULL;
}

bool LinkedList_is_empty(const LinkedList *LL) {
    return LL->size == 0;
}

bool LinkedList_is_sorted(const LinkedList *LL) {
    return LL->sort_order != UNSORTED;
}

int LinkedList_sort_order(const LinkedList *LL) {
    return LL->sort_order;
}

void LinkedList_print(const LinkedList *LL, void (*type_print_function)(void *data)) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_print'.\n");
        fprintf(stderr, "ERROR: DoublyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (LinkedList_is_empty(LL)) {
        printf("It's empty!\n");
    } else {
        Node *node = LL->begin;
        printf("NULL <- ");
        while (node->next != NULL) {
            type_print_function(node->data);
            printf(" <- -> ");
            node = node->next;
        }
        type_print_function(LL->end->data);
        printf(" -> ");
        puts("NULL");
    }
}

void LinkedList_add_first(LinkedList *LL, void *data) {
    Node *node = Node_create(data);
    node->next = LL->begin;
    if (LinkedList_is_empty(LL)) LL->end = node;
    else LL->begin->prev = node;
    LL->begin = node;
    LL->size++;
    LL->sort_order = UNSORTED;
}

void LinkedList_add_last(LinkedList *LL, void *data) {
    Node *node = Node_create(data);
    node->prev = LL->end;
    if (LinkedList_is_empty(LL)) LL->begin = node;
    else LL->end->next = node;
    LL->end = node;
    LL->size++;
    LL->sort_order = UNSORTED;
}

void *LinkedList_remove_first(LinkedList *LL) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_remove_first'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (LinkedList_is_empty(LL)) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_remove_first'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    Node *node = LL->begin;
    void *data = node->data;
    if (LL->begin == LL->end) {
        LL->begin = LL->end = NULL;
    } else {
        LL->begin = node->next;
        LL->begin->prev = NULL;
    }
    free(node);
    LL->size--;
    return data;
}

void *LinkedList_remove_last(LinkedList *LL) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_remove_last'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (LinkedList_is_empty(LL)) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_remove_last'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    Node *node = LL->end;
    void *data = node->data;
    if (LL->begin == LL->end) {
        LL->begin = LL->end = NULL;
    } else {
        node->prev->next = NULL;
        LL->end = node->prev;
    }
    free(node);
    LL->size--;
    return data;
}

void *LinkedList_remove_at(LinkedList *LL, const size_t index) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_remove_at'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (LinkedList_is_empty(LL)) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_remove_at'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (index == 0) {
        return LinkedList_remove_first(LL);
    }
    if (index == LL->size) {
        return LinkedList_remove_last(LL);
    }
    Node *node = LL->begin;
    void *data;
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    data = node->data;
    free(node);
    LL->size--;
    return data;
}

void LinkedList_remove(LinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (!LinkedList_is_empty(LL)) {
        Node *node = LL->begin;
        while (node != NULL && type_compare_function(node->data, data) != 0) {
            node = node->next;
        }
        if (node != NULL) {
            if (LL->begin == node) {
                if (LL->begin == LL->end) {
                    LL->begin = LL->end = NULL;
                } else {
                    LL->begin = node->next;
                    node->next->prev = NULL;
                }
            } else {
                if (LL->end == node) {
                    node->prev->next = NULL;
                    LL->end = node->prev;
                } else {
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                }
            }
            free(node);
            LL->size--;
        }
    }
}

void LinkedList_remove_all(LinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (!LinkedList_is_empty(LL)) {
        Node *node = LL->begin;
        while (node != NULL) {
            Node *aux_node = node->next;
            if (type_compare_function(node->data, data) == 0) {
                if (LL->begin == node) {
                    if (LL->begin == LL->end) {
                        LL->begin = LL->end = NULL;
                    } else {
                        LL->begin = node->next;
                        node->next->prev = NULL;
                    }
                } else {
                    if (LL->end == node) {
                        LL->end = node->prev;
                        node->prev->next = NULL;
                    } else {
                        node->prev->next = node->next;
                        node->next->prev = node->prev;
                    }
                }
                free(node);
                node = aux_node;
                LL->size--;
            } else {
                node = aux_node;
            }
        }
    }
}

size_t LinkedList_size(const LinkedList *LL) {
    return LL->size;
}

void *LinkedList_first_element(const LinkedList *LL) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (LinkedList_is_empty(LL)) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    return LL->begin->data;
}

void *LinkedList_last_element(const LinkedList *LL) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (LinkedList_is_empty(LL)) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    return LL->end->data;
}

void *LinkedList_get(const LinkedList *LL, const size_t index) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_get'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (LinkedList_is_empty(LL) && index != 0) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_get'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    } else if (index >= LL->size) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_get'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %lu. Try an index within [0, %lu].\n", index, LL->size - 1);
        exit(EXIT_FAILURE);
    } else {
        Node *node = _get_node(LL, index);
        return node->data;
    }
}

int LinkedList_count(const LinkedList *LL, void *data) {
    if (LinkedList_is_empty(LL)) {
        return 0;
    }
    Node *node = LL->begin;
    int count = 0;
    while (node != NULL) {
        if (node->data == data) {
            count++;
        }
        node = node->next;
    }
    return count;
}

bool LinkedList_contains(const LinkedList *LL, void *data) {
    if (LinkedList_is_empty(LL)) {
        return false;
    }
    Node *node = LL->begin;
    while (node != NULL) {
        if (node->data == data) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void LinkedList_insert_at(LinkedList *LL, void *data, const size_t index) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_insert_at'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (index > LL->size  || index < 0) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_insert_at'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %lu. Try an index within [0, %lu].\n", index, LL->size);
        exit(EXIT_FAILURE);
    } else {
        if (index == 0) {
            LinkedList_add_first(LL, data);
        } else if (index == LL->size) {
            LinkedList_add_last(LL, data);
        } else {
            Node *node_new = Node_create(data);
            Node *node = LL->begin;
            for (size_t i = 0; i < index-1; i++) {
                node = node->next;
            }
            node_new->next = node->next;
            node->next->prev = node_new;
            node->next = node_new;
            node_new->prev = node;
            LL->size++;
            LL->sort_order = UNSORTED;
        }
    }
}

LinkedList *LinkedList_clone(const LinkedList *LL) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_clone'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    }
    LinkedList *clone = LinkedList_create();
    Node *node = LL->begin;
    int count = 0;
    while (node != NULL) {
        LinkedList_insert_at(clone, node->data, count);
        count++;
        node = node->next;
    }
    clone->sort_order = LL->sort_order;
    return clone;
}

LinkedList *LinkedList_concat(LinkedList *LL1, LinkedList *LL2) {
    if (LL1 == NULL || LL2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_concat'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    }  else if (LinkedList_is_empty(LL1)) {
        return LinkedList_clone(LL2);
    } else if (LinkedList_is_empty(LL2)) {
        return LinkedList_clone(LL1);
    }
    LinkedList *LL_new = LinkedList_clone(LL1);
    Node *node = LL2->begin;
    while (node != NULL) {
        LinkedList_add_last(LL_new, node->data);
        node = node->next;
    }
    LL_new->sort_order = UNSORTED;
    return LL_new;
}

LinkedList *LinkedList_reverse(LinkedList *LL) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_reverse'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (LinkedList_is_empty(LL)) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_reverse'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    LinkedList *LL_new = LinkedList_clone(LL);
    Node *node = LL_new->begin;
    LL_new->end = LL_new->begin;
    Node *node_prev = NULL, *node_next = NULL;
    while (node != NULL) {
        node_next = node->next;
        node->next = node_prev;
        node_prev = node;
        node = node_next;
    }
    LL_new->begin = node_prev;
    LL_new->sort_order = (-1)*LL->sort_order;
    return LL_new;
}

bool LinkedList_is_equals_strict(const LinkedList *LL1, const LinkedList *LL2) {
    if (LL1 == NULL || LL2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_is_equals_strict'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (LL1->size != LL2->size || LinkedList_is_empty(LL1) || LinkedList_is_empty(LL2)) {
        return false;
    }
    Node *node1 = LL1->begin;
    Node *node2 = LL2->begin;
    while (node1 != NULL) {
        if (node1->data != node2->data) {
            return false;
        }
        node1 = node1->next;
        node2 = node2->next;
    }
    return LL1->sort_order == LL2->sort_order;
}

bool LinkedList_is_equals(const LinkedList *LL1, const LinkedList *LL2, int (*type_compare_function)(void *data1, void *data2)) {
    if (LL1 == NULL || LL2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_is_equals_strict'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (LL1->size != LL2->size || LinkedList_is_empty(LL1) || LinkedList_is_empty(LL2)) {
        return false;
    }
    Node *node1 = LL1->begin;
    Node *node2 = LL2->begin;
    while (node1 != NULL) {
        if (type_compare_function(node1->data, node2->data) != 0) {
            return false;
        }
        node1 = node1->next;
        node2 = node2->next;
    }
    return LL1->sort_order == LL2->sort_order;
}

void LinkedList_sort_asc(LinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    _merge_sort(&LL->begin, type_compare_function, 1);
    LL->sort_order = ASC;
    LL->end = _get_node(LL, LL->size-1);
}

void LinkedList_sort_desc(LinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    _merge_sort(&LL->begin, type_compare_function, -1);
    LL->sort_order = DESC;
    LL->end = _get_node(LL, LL->size-1);
}

void LinkedList_sorted_insert(LinkedList *LL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (!LinkedList_is_sorted(LL)) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_sorted_insert'.\n");
        fprintf(stderr, "ERROR: Linked List must be sorted.\n");
        exit(EXIT_FAILURE);
    }

    Node *node = LL->begin, *node_prev = NULL, *node_new = Node_create(data);

    if (LL->sort_order == ASC) {
        while (node != NULL && type_compare_function(data, node->data) <=  0) {
            node_prev = node;
            node = node->next;
        }
    } else {
        while (node != NULL && type_compare_function(data, node->data) >= 0) {
            node_prev = node;
            node = node->next;
        }
    }

    if (node == LL->begin) {
        node_new->next = LL->begin;
        LL->begin = node_new;
    } else {
        node_new->next = node_prev-> next;
        node_prev->next = node_new;
    }
    LL->size++;
}

void *LinkedList_min(const LinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_min'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    }

    if (LinkedList_is_sorted(LL)) {
        if (LL->sort_order == ASC) {
            return LL->begin->data;
        } else {
            return LL->end->data;
        }
    }

    LinkedList *clone = LinkedList_clone(LL);
    LinkedList_sort_asc(clone, type_compare_function);
    void *data = clone->begin->data;
    LinkedList_destroy(&clone);
    return data;
}

void *LinkedList_max(const LinkedList *LL, int (*type_compare_function)(void *data1, void *data2)) {
    if (LL == NULL) {
        fprintf(stderr, "\nERROR: on function 'LinkedList_max'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    }

    if (LinkedList_is_sorted(LL)) {
        if (LL->sort_order == ASC) {
            return LL->end->data;
        } else {
            return LL->begin->data;
        }
    }

    LinkedList *clone = LinkedList_clone(LL);
    LinkedList_sort_desc(clone, type_compare_function);
    void *data = clone->begin->data;
    LinkedList_destroy(&clone);
    return data;
}
