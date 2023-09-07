#include "../include/circular_doubly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>
//#--ADD_TO_INCLUDE

#define UNSORTED 0
#define ASC 1
#define DESC -1

typedef struct _circular_node {
    void *data;
    struct _circular_node *prev;
    struct _circular_node *next;
} CircularNode;

CircularNode *CircularNode_create(void *data) {
    CircularNode *cnode = (CircularNode *) calloc(1, sizeof(CircularNode));
    cnode->data = data;
    cnode->prev = cnode;
    cnode->next = cnode;
    return cnode;
}

typedef struct _circular_linked_list {
    CircularNode *begin;
    CircularNode *end;
    size_t size;
    int sort_order;
} CircularLinkedList;

void _cll_left_right_split(CircularNode *cnode, CircularNode **left_ref, CircularNode **right_ref) {
    CircularNode *slow = cnode;
    CircularNode *fast = cnode;

    if(cnode == NULL) {
        return;
    }

    while(fast->next != cnode && fast->next->next != cnode) {
        fast = fast->next->next;
        slow = slow->next;
    }

    if(fast->next->next == cnode) {
        fast = fast->next;
    }

    *left_ref = cnode;
    cnode->prev = slow;

    if(cnode->next != cnode) {
        *right_ref = slow->next;
    }

    slow->next->prev = fast;
    fast->next = slow->next;

    slow->next = cnode;
}

CircularNode *_cll_sorted_merge_aux(CircularNode *left, CircularNode *right, int (*type_compare_function)(void *data1, void *data2), int order) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    if (order == ASC) {
        if (type_compare_function(left->data, right->data) >= 0) {
            left->next = _cll_sorted_merge_aux(left->next, right, type_compare_function, order);
            left->next->prev = left;
            left->prev = NULL;
            return left;
        } else {
            right->next = _cll_sorted_merge_aux(left, right->next, type_compare_function, order);
            right->next->prev = right;
            right->prev = NULL;
            return right;
        }
    } else {
        if (type_compare_function(left->data, right->data) <= 0) {
            left->next = _cll_sorted_merge_aux(left->next, right, type_compare_function, order);
            left->next->prev = left;
            left->prev = NULL;
            return left;
        } else {
            right->next = _cll_sorted_merge_aux(left, right->next, type_compare_function, order);
            right->next->prev = right;
            right->prev = NULL;
            return right;
        }
    }
}

CircularNode *_cll_sorted_merge(CircularNode *left, CircularNode *right, int (*type_compare_function)(void *data1, void *data2), int order) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    CircularNode *last_node;

    if (order == ASC) {
        if (type_compare_function(left->prev->data, right->prev->data) >= 0) {
            last_node = right->prev;
        } else {
            last_node = left->prev;
        }
    } else {
        if (type_compare_function(left->next->data, right->next->data) >= 0) {
            last_node = left->prev;
        } else {
            last_node = right->prev;
        }
    }

    left->prev->next = right->prev->next = NULL;

    CircularNode *result = _cll_sorted_merge_aux(left, right, type_compare_function, order);
    result->prev = last_node;
    last_node->next = result;

    return result;
}

void _cll_merge_sort(CircularNode **CLL_begin_ref, int (*type_compare_function)(void *data1, void *data2), int order) {
    CircularNode *CLL_begin = *CLL_begin_ref, *left, *right;

    if (CLL_begin == NULL || CLL_begin->next == CLL_begin) {
        return;
    }

    if (order != ASC && order != DESC) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_sort_*'.\n");
        fprintf(stderr, "ERROR: Invalid sort order.\n");
        exit(EXIT_FAILURE);
    }

    _cll_left_right_split(CLL_begin, &left, &right);
    _cll_merge_sort(&left, type_compare_function, order);
    _cll_merge_sort(&right, type_compare_function, order);

    *CLL_begin_ref = _cll_sorted_merge(left, right, type_compare_function, order);
}

CircularNode *_get_cnode(const CircularLinkedList *CLL, size_t index) {
    CircularNode *cnode = CLL->begin;
    for (size_t i = 0; i != index; i++) {
        cnode = cnode->next;
    }
    return cnode;
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
    CircularNode *cnode = CLL->begin;
    while (cnode != CLL->end) {
        CircularNode *cnode_next = cnode->next;
        // Usar Node_delete()
        free(cnode);
        cnode = cnode_next;
    }
    free(cnode);
    CLL->begin = NULL;
    CLL->end = NULL;
    CLL->size = 0;
    CLL->sort_order = UNSORTED;
}

void CircularLinkedList_destroy(CircularLinkedList **CLL_ref) {
    CircularLinkedList *CLL = *CLL_ref;
    CircularLinkedList_clean(CLL);
    free(CLL);
    *CLL_ref = NULL;
}

bool CircularLinkedList_is_empty(const CircularLinkedList *CLL) {
    return CLL->size == 0;
}

bool CircularLinkedList_is_sorted(const CircularLinkedList *CLL) {
    return CLL->sort_order != UNSORTED;
}

int CircularLinkedList_sort_order(const CircularLinkedList *CLL) {
    return CLL->sort_order;
}

void CircularLinkedList_print(const CircularLinkedList *CLL, void (*type_print_function)(void *data)) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_print'.\n");
        fprintf(stderr, "ERROR: CircularLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (CircularLinkedList_is_empty(CLL)) {
        printf("It's empty!\n");
    } else {
        CircularNode *cnode = CLL->begin;
        printf("LAST NODE <- -> ");
        do {
            type_print_function(cnode->data);
            printf(" <- -> ");
            cnode = cnode->next;
        } while (cnode != CLL->begin);
        puts("FIRST NODE");
    }
}

void CircularLinkedList_add_first(CircularLinkedList *CLL, void *data) {
    CircularNode *cnode = CircularNode_create(data);

    if (CircularLinkedList_is_empty(CLL)) {
        CLL->end = cnode;
    } else {
        cnode->next = CLL->begin;
        CLL->begin->prev = cnode;
        cnode->prev = CLL->end;
        CLL->end->next = cnode;
    }

    CLL->begin = cnode;
    CLL->size++;
    CLL->sort_order = UNSORTED;
}

void CircularLinkedList_add_last(CircularLinkedList *CLL, void *data) {
    CircularNode *cnode = CircularNode_create(data);
    if (CircularLinkedList_is_empty(CLL)) CLL->begin = cnode;
    else {
        CLL->end->next = cnode;
        cnode->prev = CLL->end;
        CLL->begin->prev = cnode;
        cnode->next = CLL->begin;
    }
    CLL->end = cnode;
    CLL->size++;
    CLL->sort_order = UNSORTED;
}

void _cll_sorted_insert_asc(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (type_compare_function(CLL->begin->data, data) <= 0) {
        CircularLinkedList_add_first(CLL, data);
        CLL->sort_order = ASC;
        return;
    } else if (type_compare_function(CLL->end->data, data) >= 0) {
        CircularLinkedList_add_last(CLL, data);
        CLL->sort_order = ASC;
        return;
    } else {
        CircularNode *cnode = CLL->begin, *cnode_new = CircularNode_create(data);
        while (cnode != CLL->end && type_compare_function(data, cnode->data) < 0) {
            cnode = cnode->next;
        }
        cnode_new->next = cnode;
        cnode_new->prev = cnode->prev;
        cnode->prev->next = cnode_new;
        cnode->prev = cnode_new;
        CLL->size++;
    }
}

void _cll_sorted_insert_desc(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (type_compare_function(CLL->begin->data, data) >= 0) {
        CircularLinkedList_add_first(CLL, data);
        CLL->sort_order = DESC;
        return;
    } else if (type_compare_function(CLL->end->data, data) <= 0) {
        CircularLinkedList_add_last(CLL, data);
        CLL->sort_order = DESC;
    } else {
        CircularNode *cnode = CLL->begin, *cnode_new = CircularNode_create(data);
        while (cnode != CLL->end && type_compare_function(data, cnode->data) > 0) {
            cnode = cnode->next;
        }
        cnode_new->next = cnode;
        cnode_new->prev = cnode->prev;
        cnode->prev->next = cnode_new;
        cnode->prev = cnode_new;
        CLL->size++;
    }
}

void *CircularLinkedList_remove_first(CircularLinkedList *CLL) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_remove_first'.\n");
        fprintf(stderr, "ERROR: Circular Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CircularLinkedList_is_empty(CLL)) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_remove_first'.\n");
        fprintf(stderr, "ERROR: Circular Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    CircularNode *cnode = CLL->begin;
    void *data = cnode->data;
    if (CLL->begin == CLL->end) {
        CLL->begin = CLL->end = NULL;
    } else {
        CLL->begin = cnode->next;
        CLL->begin->prev = CLL->end;
        CLL->end->next = CLL->begin;
    }
    free(cnode);
    CLL->size--;
    return data;
}

void *CircularLinkedList_remove_last(CircularLinkedList *CLL) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_remove_last'.\n");
        fprintf(stderr, "ERROR: Circular Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CircularLinkedList_is_empty(CLL)) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_remove_last'.\n");
        fprintf(stderr, "ERROR: Circular Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    CircularNode *cnode = CLL->end;
    void *data = cnode->data;
    if (CLL->begin == CLL->end) {
        CLL->begin = CLL->end = NULL;
    } else {
        CLL->end = cnode->prev;
        cnode->prev->next = cnode->next;
        cnode->next->prev = cnode->prev;
    }
    free(cnode);
    CLL->size--;
    return data;
}

void *CircularLinkedList_remove_at(CircularLinkedList *CLL, size_t index) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_remove_at'.\n");
        fprintf(stderr, "ERROR: Circular Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CircularLinkedList_is_empty(CLL)) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_remove_at'.\n");
        fprintf(stderr, "ERROR: Circular Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (index == 0) {
        return CircularLinkedList_remove_first(CLL);
    }
    if (index == CLL->size) {
        return CircularLinkedList_remove_last(CLL);
    }
    CircularNode *cnode = CLL->begin;
    void *data;
    for (size_t i = 0; i < index; i++) {
        cnode = cnode->next;
    }
    cnode->prev->next = cnode->next;
    cnode->next->prev = cnode->prev;
    data = cnode->data;
    free(cnode);
    CLL->size--;
    return data;
}

void CircularLinkedList_remove(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (!CircularLinkedList_is_empty(CLL)) {
        CircularNode *cnode = CLL->begin;
        if (type_compare_function(CLL->begin->data, data) == 0) {
            if (CLL->begin == CLL->end) {
                CLL->begin = CLL->end = NULL;
            } else {
                CLL->begin = cnode->next;
                CLL->begin->prev = CLL->end;
                CLL->end->next = CLL->begin;
            }
            free(cnode);
            CLL->size--;
        } else {
            cnode = cnode->next;
            while (cnode != CLL->begin && type_compare_function(cnode->data, data) != 0) {
                cnode = cnode->next;
            }
            if (cnode != NULL) {
                if (CLL->end == cnode) {
                    CLL->end = cnode->prev;
                }
                cnode->prev->next = cnode->next;
                cnode->next->prev = cnode->prev;
                free(cnode);
                CLL->size--;
            }
        }
    }
}

void CircularLinkedList_remove_all(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (!CircularLinkedList_is_empty(CLL)) {
        CircularNode *cnode = CLL->begin;
        while (true) {
            CircularNode *aux_cnode = cnode->next;
            if (type_compare_function(cnode->data, data) == 0) {
                if (CLL->begin == cnode) {
                    if (CLL->begin == CLL->end) {
                        CLL->begin = CLL->end = NULL;
                    } else {
                        CLL->begin = cnode->next;
                        CLL->begin->prev = CLL->end;
                        CLL->end->next = CLL->begin;
                    }
                } else {
                    if (cnode == CLL->end) {
                        CLL->end = cnode->prev;
                    }
                    cnode->prev->next = cnode->next;
                    cnode->next->prev = cnode->prev;
                }
                free(cnode);
                cnode = aux_cnode;
                CLL->size--;
            } else {
                if (CircularLinkedList_contains(CLL, data)) {
                    cnode = aux_cnode;
                } else {
                    break;
                }
            }
        }
    }
}

size_t CircularLinkedList_size(const CircularLinkedList *CLL) {
    return CLL->size;
}

void *CircularLinkedList_first_element(const CircularLinkedList *CLL) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CircularLinkedList_is_empty(CLL)) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    return CLL->begin->data;
}

void *CircularLinkedList_last_element(const CircularLinkedList *CLL) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CircularLinkedList_is_empty(CLL)) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    return CLL->end->data;
}

void *CircularLinkedList_get(const CircularLinkedList *CLL, size_t index) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_get'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CircularLinkedList_is_empty(CLL) && index != 0) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_get'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    } else if (index >= CLL->size) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_get'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %lu. Try an index within [0, %lu].\n", index, CLL->size - 1);
        exit(EXIT_FAILURE);
    } else {
        CircularNode *cnode = _get_cnode(CLL, index);
        return cnode->data;
    }
}

int CircularLinkedList_count(const CircularLinkedList *CLL, void *data) {
    if (CircularLinkedList_is_empty(CLL)) {
        return 0;
    }
    int count = 0;
    if (CLL->begin->data == data) {
        count++;
    }
    CircularNode *cnode = CLL->begin->next;
    while (cnode != CLL->begin) {
        if (cnode->data == data) {
            count++;
        }
        cnode = cnode->next;
    }
    return count;
}

bool CircularLinkedList_contains(const CircularLinkedList *CLL, void *data) {
    if (CircularLinkedList_is_empty(CLL)) {
        return false;
    }
    if (CLL->begin->data == data) {
        return true;
    }
    CircularNode *cnode = CLL->begin->next;
    while (cnode != CLL->begin) {
        if (cnode->data == data) {
            return true;
        }
        cnode = cnode->next;
    }
    return false;
}

void CircularLinkedList_insert_at(CircularLinkedList *CLL, void *data, size_t index) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_insert_at'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (index > CLL->size || index < 0) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_insert_at'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %lu. Try an index within [0, %lu].\n", index, CLL->size);
        exit(EXIT_FAILURE);
    } else {
        if (index == 0) {
            CircularLinkedList_add_first(CLL, data);
        } else if (index == CLL->size) {
            CircularLinkedList_add_last(CLL, data);
        } else {
            CircularNode *cnode_new = CircularNode_create(data);
            CircularNode *cnode = CLL->begin;
            for (size_t i = 0; i < index-1; i++) {
                cnode = cnode->next;
            }
            cnode_new->next = cnode->next;
            cnode->next->prev = cnode_new;
            cnode->next = cnode_new;
            cnode_new->prev = cnode;
            CLL->size++;
            CLL->sort_order = UNSORTED;
        }
    }
}

CircularLinkedList *CircularLinkedList_clone(const CircularLinkedList *CLL) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_clone'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    }
    CircularLinkedList *clone = CircularLinkedList_create();
    CircularNode *cnode = CLL->begin->next;
    CircularLinkedList_add_first(clone, CLL->begin->data);
    int count = 1;
    while (cnode != CLL->begin) {
        CircularLinkedList_insert_at(clone, cnode->data, count);
        count++;
        cnode = cnode->next;
    }
    clone->sort_order = CLL->sort_order;
    return clone;
}

CircularLinkedList *CircularLinkedList_concat(CircularLinkedList *CLL1, CircularLinkedList *CLL2) {
    if (CLL1 == NULL || CLL2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_concat'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    }  else if (CircularLinkedList_is_empty(CLL1)) {
        return CircularLinkedList_clone(CLL2);
    } else if (CircularLinkedList_is_empty(CLL2)) {
        return CircularLinkedList_clone(CLL1);
    }
    CircularLinkedList *CLL_new = CircularLinkedList_clone(CLL1);
    CircularNode *cnode = CLL2->begin;
    while (cnode->next != CLL2->begin) {
        CircularLinkedList_add_last(CLL_new, cnode->data);
        cnode = cnode->next;
    }
    CircularLinkedList_add_last(CLL_new, cnode->data);
    CLL_new->sort_order = UNSORTED;
    return CLL_new;
}

CircularLinkedList *CircularLinkedList_reverse(CircularLinkedList *CLL) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_reverse'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CircularLinkedList_is_empty(CLL)) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_reverse'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }
    CircularLinkedList *CLL_new = CircularLinkedList_clone(CLL);
    CircularNode *cnode = CLL->begin, *cnode_prev = NULL, *cnode_next = NULL;
    CLL_new->begin = CLL->end;
    for (size_t i = 0; i < CLL->size; i++) {
        cnode_next = cnode->next;
        cnode_prev = cnode->prev;
        cnode->next = cnode_prev;
        cnode->prev = cnode_next;
        cnode = cnode_next;
    }
    CLL_new->end = CLL->begin;
    CLL_new->sort_order = (-1)*CLL->sort_order;
    return CLL_new;
}

bool CircularLinkedList_is_equals_strict(const CircularLinkedList *CLL1, const CircularLinkedList *CLL2) {
    if (CLL1 == NULL || CLL2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_is_equals_strict'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CLL1->size != CLL2->size || CircularLinkedList_is_empty(CLL1) || CircularLinkedList_is_empty(CLL2)) {
        return false;
    }
    CircularNode *cnode1 = CLL1->begin;
    CircularNode *cnode2 = CLL2->begin;
    for (size_t i = 0; i < CLL1->size; i++) {
        if (cnode1->data != cnode2->data) {
            return false;
        }
        cnode1 = cnode1->next;
        cnode2 = cnode2->next;
    }
    return CLL1->sort_order == CLL2->sort_order;
}

bool CircularLinkedList_is_equals(const CircularLinkedList *CLL1, const CircularLinkedList *CLL2, int (*type_compare_function)(void *data1, void *data2)) {
    if (CLL1 == NULL || CLL2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_is_equals_strict'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CLL1->size != CLL2->size || CircularLinkedList_is_empty(CLL1) || CircularLinkedList_is_empty(CLL2)) {
        return false;
    }
    CircularNode *cnode1 = CLL1->begin;
    CircularNode *cnode2 = CLL2->begin;
    for (size_t i = 0; i < CLL1->size; i++) {
        if (type_compare_function(cnode1->data, cnode2->data) != 0) {
            return false;
        }
        cnode1 = cnode1->next;
        cnode2 = cnode2->next;
    }
    return CLL1->sort_order == CLL2->sort_order;
}

void CircularLinkedList_sort_asc(CircularLinkedList **CLL_ref, int (*type_compare_function)(void *data1, void *data2)) {
    CircularLinkedList *CLL = *CLL_ref;
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_sort_asc'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CircularLinkedList_is_empty(CLL)) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_sort_asc'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }

    if (CLL->sort_order == ASC) {
        return;
    } else if (CLL->sort_order == DESC) {
        *CLL_ref = CircularLinkedList_reverse(CLL);
    } else {
        _cll_merge_sort(&CLL->begin, type_compare_function, ASC);
        CLL->sort_order = ASC;
        CLL->end = _get_cnode(CLL, CLL->size - 1);
        CLL->end->next = CLL->begin;
        CLL->begin->prev = CLL->end;
    }
}

void CircularLinkedList_sort_desc(CircularLinkedList **CLL_ref, int (*type_compare_function)(void *data1, void *data2)) {
    CircularLinkedList *CLL = *CLL_ref;
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_sort_desc'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (CircularLinkedList_is_empty(CLL)) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_sort_desc'.\n");
        fprintf(stderr, "ERROR: Linked List is empty.\n");
        exit(EXIT_FAILURE);
    }

    if (CLL->sort_order == DESC) {
        return;
    } else if (CLL->sort_order == ASC) {
        *CLL_ref = CircularLinkedList_reverse(CLL);
    } else {
        _cll_merge_sort(&CLL->begin, type_compare_function, DESC);
        CLL->sort_order = DESC;
        CLL->end = _get_cnode(CLL, CLL->size-1);
        CLL->end->next = CLL->begin;
        CLL->begin->prev = CLL->end;
    }
}

void CircularLinkedList_sorted_insert(CircularLinkedList *CLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (!CircularLinkedList_is_sorted(CLL)) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_sorted_insert'.\n");
        fprintf(stderr, "ERROR: Linked List must be sorted.\n");
        exit(EXIT_FAILURE);
    }

    if (CLL->sort_order == ASC) {
        _cll_sorted_insert_asc(CLL, data, type_compare_function);
    } else {
        _cll_sorted_insert_desc(CLL, data, type_compare_function);
    }
}

void *CircularLinkedList_min(const CircularLinkedList *CLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_min'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    }

    if (CircularLinkedList_is_sorted(CLL)) {
        if (CLL->sort_order == ASC) {
            return CLL->begin->data;
        } else {
            return CLL->end->data;
        }
    }

    CircularLinkedList *clone = CircularLinkedList_clone(CLL);
    CircularLinkedList_sort_asc(&clone, type_compare_function);
    void *data = clone->begin->data;
    CircularLinkedList_destroy(&clone);
    return data;
}

void *CircularLinkedList_max(const CircularLinkedList *CLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (CLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'CircularLinkedList_max'.\n");
        fprintf(stderr, "ERROR: Linked List is NULL.\n");
        exit(EXIT_FAILURE);
    }

    if (CircularLinkedList_is_sorted(CLL)) {
        if (CLL->sort_order == ASC) {
            return CLL->end->data;
        } else {
            return CLL->begin->data;
        }
    }

    CircularLinkedList *clone = CircularLinkedList_clone(CLL);
    CircularLinkedList_sort_desc(&clone, type_compare_function);
    void *data = clone->begin->data;
    CircularLinkedList_destroy(&clone);
    return data;
}
