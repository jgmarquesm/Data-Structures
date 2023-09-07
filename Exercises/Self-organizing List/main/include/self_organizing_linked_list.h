#ifndef SELF_ORGANIZING_LINKED_LIST_H
#define SELF_ORGANIZING_LINKED_LIST_H

#include "product.h"

typedef struct _list List;

List *List_create();

void List_destroy(List **list_ref);

void List_add_product(List *list, const int serial, const char *name, const float price);

void List_print(List *list);

const Product *List_get_product_with_serial(List *list, int serial);

void List_print_summary(const List *list);

#endif
