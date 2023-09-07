#include "../include/singly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>
//#--ADD_TO_INCLUDE

#define UNSORTED 0
#define ASC 1
#define DESC -1

typedef struct _simple_node {
    void *data;
    struct _simple_node *next;
} SimpleNode;

SimpleNode *SimpleNode_create(void *data) {
    SimpleNode *SN = (SimpleNode *) calloc(1, sizeof(SimpleNode));
    SN->data = data;
    SN->next = NULL;
    return SN;
}

typedef struct _singly_linked_list {
    SimpleNode *begin;
    SimpleNode *end;
    size_t size;
    int sort_order;
} SinglyLinkedList;

void _sll_left_right_split(SimpleNode *SN, SimpleNode **left_ref, SimpleNode **right_ref) {
    SimpleNode *slow = SN, *fast = SN->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *left_ref = SN;
    *right_ref = slow->next;
    slow->next = NULL;
}

SimpleNode *_sll_sorted_merge(SimpleNode *left, SimpleNode *right, int (*type_compare_function)(void *data1, void *data2), int order) {
    SimpleNode *SLL_begin_result = NULL;

    if (left == NULL) {
        return right;
    } else if (right == NULL) {
        return left;
    }

    if (order == ASC) {
        if (type_compare_function(left->data, right->data) >= 0) {
            SLL_begin_result = left;
            SLL_begin_result->next = _sll_sorted_merge(left->next, right, type_compare_function, order);
        } else {
            SLL_begin_result = right;
            SLL_begin_result->next = _sll_sorted_merge(left, right->next, type_compare_function, order);
        }
    } else {
        if (type_compare_function(left->data, right->data) <= 0) {
            SLL_begin_result = left;
            SLL_begin_result->next = _sll_sorted_merge(left->next, right, type_compare_function, order);
        } else {
            SLL_begin_result = right;
            SLL_begin_result->next = _sll_sorted_merge(left, right->next, type_compare_function, order);
        }
    }

    return SLL_begin_result;
}

void _sll_merge_sort(SimpleNode **SLL_begin_ref, int (*type_compare_function)(void *data1, void *data2), int order) {
    SimpleNode *SLL_begin = *SLL_begin_ref, *left, *right;

    if ((SLL_begin == NULL) || (SLL_begin->next == NULL)) {
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

SimpleNode *_get_node(const SinglyLinkedList *SLL, const size_t index) {
    SimpleNode *SN = SLL->begin;
    for (size_t i = 0; i != index; i++) {
        SN = SN->next;
    }
    return SN;
}

SinglyLinkedList *SinglyLinkedList_create() {
    SinglyLinkedList *SLL = (SinglyLinkedList *) calloc(1, sizeof(SinglyLinkedList));
    SLL->begin = NULL;
    SLL->end = SLL->begin;
    SLL->size = 0;
    SLL->sort_order = UNSORTED;
    return  SLL;
}

void SinglyLinkedList_clean(SinglyLinkedList *SLL) {
    SimpleNode *SN = SLL->begin;
    while (SN != NULL) {
        SimpleNode *SN_next = SN->next;
        free(SN);
        SN = SN_next;
    }
    SLL->begin = NULL;
    SLL->end = NULL;
    SLL->size = 0;
    SLL->sort_order = UNSORTED;
}

void SinglyLinkedList_destroy(SinglyLinkedList **SLL_ref) {
    SinglyLinkedList *SLL = *SLL_ref;
    SinglyLinkedList_clean(SLL);
    free(SLL);
    *SLL_ref = NULL;
}

bool SinglyLinkedList_is_empty(const SinglyLinkedList *SLL) {
    return (SLL->begin == NULL && SLL->end == NULL);
}

bool SinglyLinkedList_is_sorted(const SinglyLinkedList *SLL) {
    return SLL->sort_order != UNSORTED;
}

int SinglyLinkedList_sort_order(const SinglyLinkedList *SLL) {
    return SLL->sort_order;
}

void SinglyLinkedList_print(const SinglyLinkedList *SLL, void (*type_print_function)(void *data)) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_print'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    }
    SimpleNode *SN = SLL->begin;
    printf("SLL -> ");
    while (SN != NULL) {
        type_print_function(SN->data);
        printf(" -> ");
        SN = SN->next;
    }
    puts("NULL");
}

void SinglyLinkedList_add_first(SinglyLinkedList *SLL, void *data) {
    SimpleNode *SN_new = SimpleNode_create(data);
    SN_new->next = SLL->begin;
    if (SinglyLinkedList_is_empty(SLL)) {
        SLL->end = SN_new;
    }
    SLL->begin = SN_new;
    SLL->size++;
    SLL->sort_order = UNSORTED;
}

void SinglyLinkedList_add_last(SinglyLinkedList *SLL, void *data) {
    SimpleNode *SN_new = SimpleNode_create(data);
    if (SinglyLinkedList_is_empty(SLL)) {
        SLL->begin = SLL->end = SN_new;
    } else {
        SLL->end->next = SN_new;
        SLL->end = SLL->end->next;
    }
    SLL->size++;
    SLL->sort_order = UNSORTED;
}

void *SinglyLinkedList_remove_first(SinglyLinkedList *SLL) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_remove_first'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (SinglyLinkedList_is_empty(SLL)) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_remove_first'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is empty.\n");
        exit(EXIT_FAILURE);
    }
    SimpleNode *SN = SLL->begin;
    void *data = SN->data;
    SLL->begin = SN->next;
    free(SN);
    SLL->size--;
    return data;
}

void *SinglyLinkedList_remove_last(SinglyLinkedList *SLL) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_remove_last'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (SinglyLinkedList_is_empty(SLL)) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_remove_last'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is empty.\n");
        exit(EXIT_FAILURE);
    }
    void *data = SinglyLinkedList_remove_at(SLL, SLL->size-1);
    return data;
}

void *SinglyLinkedList_remove_at(SinglyLinkedList *SLL, const size_t index) {
    SimpleNode *SN_prev = NULL;
    SimpleNode *SN = SLL->begin;
    for (size_t i = 0; i < index; i++) {
        SN_prev = SN;
        SN = SN->next;
    }
    SN_prev->next = SN->next;
    void *data = SN->data;
    free(SN);
    SLL->size--;
    return data;
}

void SinglyLinkedList_remove(SinglyLinkedList *SLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (!SinglyLinkedList_is_empty(SLL)) {
        SimpleNode *SN_prev = NULL;
        SimpleNode *SN = SLL->begin;
        while (SN != NULL && type_compare_function(SN->data, data) != 0) {
            SN_prev = SN;
            SN = SN->next;
        }
        if (SN != NULL) {
            if (SLL->end == SN) {
                SLL->end = SN_prev;
            }
            if (SLL->begin == SN) {
                SLL->begin = SN->next;
            } else {
                SN_prev->next = SN->next;
            }
            free(SN);
            SLL->size--;
        }
    }
}

void SinglyLinkedList_remove_all(SinglyLinkedList *SLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (!SinglyLinkedList_is_empty(SLL)) {
        SimpleNode *SN_prev = SLL->begin;
        SimpleNode *SN = SLL->begin->next;
        while (SN != NULL) {
            if (type_compare_function(SLL->begin->data, data) == 0) {
                SLL->begin = SN_prev->next;
                free(SN_prev);
                SN_prev = SLL->begin;
                SN = SN->next;
                SLL->size--;
            }
            if (type_compare_function(SN->data, data) == 0) {
                SN_prev->next = SN->next;
                if (SLL->end == SN) {
                    SLL->end = SN_prev;
                }
                free(SN);
                SN = SN_prev->next;
                SLL->size--;
            } else {
                SN_prev = SN;
                SN = SN->next;
            }
        }
    }
}

size_t SinglyLinkedList_size(const SinglyLinkedList *SLL) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_size'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    }
    return SLL->size;
}

void *SinglyLinkedList_first_element(const SinglyLinkedList *SLL) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (SinglyLinkedList_is_empty(SLL)) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is empty.\n");
        exit(EXIT_FAILURE);
    }
    return SLL->begin->data;
}

void *SinglyLinkedList_last_element(const SinglyLinkedList *SLL) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (SinglyLinkedList_is_empty(SLL)) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_first_element'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is empty.\n");
        exit(EXIT_FAILURE);
    }
    return SLL->end->data;
}

void *SinglyLinkedList_get(const SinglyLinkedList *SLL, const size_t index) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_get'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (SinglyLinkedList_is_empty(SLL) && index != 0) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_get'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is empty.\n");
        exit(EXIT_FAILURE);
    } else if (index >= SLL->size) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_get'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %lu. Try an index within [0, %lu].\n", index, SLL->size - 1);
        exit(EXIT_FAILURE);
    } else {
        SimpleNode *SN = _get_node(SLL, index);
        return SN->data;
    }
}

int SinglyLinkedList_count(const SinglyLinkedList *SLL, void *data) {
    if (SinglyLinkedList_is_empty(SLL)) {
        return 0;
    }
    SimpleNode *SN = SLL->begin;
    int count = 0;
    while (SN != NULL) {
        if (SN->data == data) {
            count++;
        }
        SN = SN->next;
    }
    return count;
}

bool SinglyLinkedList_contains(const SinglyLinkedList *SLL, void *data) {
    if (SinglyLinkedList_is_empty(SLL)) {
        return false;
    }
    SimpleNode *SN = SLL->begin;
    while (SN != NULL) {
        if (SN->data == data) {
            return true;
        }
        SN = SN->next;
    }
    return false;
}

void SinglyLinkedList_insert_at(SinglyLinkedList *SLL, void *data, const size_t index) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_insert_at'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (SinglyLinkedList_is_empty(SLL) && index != 0) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_insert_at'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is empty.\n");
        exit(EXIT_FAILURE);
    } else if (index > SLL->size) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_insert_at'.\n");
        fprintf(stderr, "ERROR MESSAGE: Invalid index: %lu. Try an index within [0, %lu].\n", index, SLL->size - 1);
        exit(EXIT_FAILURE);
    } else {
        if (index == 0) {
            SinglyLinkedList_add_first(SLL, data);
        } else if (index == SLL->size) {
            SinglyLinkedList_add_last(SLL, data);
        } else {
            SimpleNode *SN_new = SimpleNode_create(data);
            SimpleNode *SN_prev = NULL;
            SimpleNode *SN = SLL->begin;
            for (size_t i = 0; i != index; i++) {
                SN_prev = SN;
                SN = SN->next;
            }
            SN_new->next = SN_prev->next;
            SN_prev->next = SN_new;
            SLL->size++;
            SLL->sort_order = UNSORTED;
        }
    }
}

SinglyLinkedList *SinglyLinkedList_clone(const SinglyLinkedList *SLL) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_clone'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    }
    SinglyLinkedList *clone = SinglyLinkedList_create();
    SimpleNode *SN = SLL->begin;
    int count = 0;
    while (SN != NULL) {
        SinglyLinkedList_insert_at(clone, SN->data, count);
        count++;
        SN = SN->next;
    }
    clone->sort_order = SLL->sort_order;
    return clone;
}

SinglyLinkedList *SinglyLinkedList_concat(SinglyLinkedList *SLL1, SinglyLinkedList *SLL2) {
    if (SLL1 == NULL || SLL2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_concat'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    }  else if (SinglyLinkedList_is_empty(SLL1)) {
        return SinglyLinkedList_clone(SLL2);
    } else if (SinglyLinkedList_is_empty(SLL2)) {
        return SinglyLinkedList_clone(SLL1);
    }
    SinglyLinkedList *SLL_new = SinglyLinkedList_clone(SLL1);
    SimpleNode *SN = SLL2->begin;
    while (SN != NULL) {
        SinglyLinkedList_add_last(SLL_new, SN->data);
        SN = SN->next;
    }
    SLL_new->sort_order = UNSORTED;
    return SLL_new;
}

SinglyLinkedList *SinglyLinkedList_reverse(SinglyLinkedList *SLL) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_reverse'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (SinglyLinkedList_is_empty(SLL)) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_reverse'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is empty.\n");
        exit(EXIT_FAILURE);
    }
    SinglyLinkedList *SLL_new = SinglyLinkedList_clone(SLL);
    SimpleNode *SN = SLL_new->begin;
    SLL_new->end = SLL_new->begin;
    SimpleNode *SN_prev = NULL, *SN_next = NULL;
    while (SN != NULL) {
        SN_next = SN->next;
        SN->next = SN_prev;
        SN_prev = SN;
        SN = SN_next;
    }
    SLL_new->begin = SN_prev;
    SLL_new->sort_order = (-1)*SLL->sort_order;
    return SLL_new;
}

bool SinglyLinkedList_is_equals_strict(const SinglyLinkedList *SLL1, const SinglyLinkedList *SLL2) {
    if (SLL1 == NULL || SLL2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_is_equals'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (SLL1->size != SLL2->size || SinglyLinkedList_is_empty(SLL1) || SinglyLinkedList_is_empty(SLL2)) {
        return false;
    }
    SimpleNode *SN1 = SLL1->begin;
    SimpleNode *SN2 = SLL2->begin;
    while (SN1 != NULL) {
        if (SN1->data != SN2->data) {
            return false;
        }
        SN1 = SN1->next;
        SN2 = SN2->next;
    }
    return SLL1->sort_order == SLL2->sort_order;
}

bool SinglyLinkedList_is_equals(const SinglyLinkedList *SLL1, const SinglyLinkedList *SLL2, int (*type_compare_function)(void *data1, void *data2)) {
    if (SLL1 == NULL || SLL2 == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_is_equals'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    } else if (SLL1->size != SLL2->size || SinglyLinkedList_is_empty(SLL1) || SinglyLinkedList_is_empty(SLL2)) {
        return false;
    }
    SimpleNode *SN1 = SLL1->begin;
    SimpleNode *SN2 = SLL2->begin;
    while (SN1 != NULL) {
        if (type_compare_function(SN1->data, SN2->data) != 0) {
            return false;
        }
        SN1 = SN1->next;
        SN2 = SN2->next;
    }
    return SLL1->sort_order == SLL2->sort_order;
}

void SinglyLinkedList_sort_asc(SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2)) {
    _sll_merge_sort(&SLL->begin, type_compare_function, 1);
    SLL->sort_order = ASC;
    SLL->end = _get_node(SLL, SLL->size-1);
}

void SinglyLinkedList_sort_desc(SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2)) {
    _sll_merge_sort(&SLL->begin, type_compare_function, -1);
    SLL->sort_order = DESC;
    SLL->end = _get_node(SLL, SLL->size-1);
}

void SinglyLinkedList_sorted_insert(SinglyLinkedList *SLL, void *data, int (*type_compare_function)(void *data1, void *data2)) {
    if (!SinglyLinkedList_is_sorted(SLL)) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_sorted_insert'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList must be sorted.\n");
        exit(EXIT_FAILURE);
    }

    SimpleNode *SN = SLL->begin, *SN_prev = NULL, *SN_new = SimpleNode_create(data);

    if (SLL->sort_order == ASC) {
        while (SN != NULL && type_compare_function(data, SN->data) <=  0) {
            SN_prev = SN;
            SN = SN->next;
        }
    } else {
        while (SN != NULL && type_compare_function(data, SN->data) >= 0) {
            SN_prev = SN;
            SN = SN->next;
        }
    }

    if (SN == SLL->begin) {
        SN_new->next = SLL->begin;
        SLL->begin = SN_new;
    } else {
        SN_new->next = SN_prev-> next;
        SN_prev->next = SN_new;
    }
    SLL->size++;
}

void *SinglyLinkedList_min(const SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_min'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    }

    if (SinglyLinkedList_is_sorted(SLL)) {
        if (SLL->sort_order == ASC) {
            return SLL->begin->data;
        } else {
            return SLL->end->data;
        }
    }

    SinglyLinkedList *clone = SinglyLinkedList_clone(SLL);
    SinglyLinkedList_sort_asc(clone, type_compare_function);
    void *data = clone->begin->data;
    SinglyLinkedList_destroy(&clone);
    return data;
}

void *SinglyLinkedList_max(const SinglyLinkedList *SLL, int (*type_compare_function)(void *data1, void *data2)) {
    if (SLL == NULL) {
        fprintf(stderr, "\nERROR: on function 'SinglyLinkedList_max'.\n");
        fprintf(stderr, "ERROR: SinglyLinkedList is NULL.\n");
        exit(EXIT_FAILURE);
    }

    if (SinglyLinkedList_is_sorted(SLL)) {
        if (SLL->sort_order == ASC) {
            return SLL->end->data;
        } else {
            return SLL->begin->data;
        }
    }

    SinglyLinkedList *clone = SinglyLinkedList_clone(SLL);
    SinglyLinkedList_sort_desc(clone, type_compare_function);
    void *data = clone->begin->data;
    SinglyLinkedList_destroy(&clone);
    return data;
}
