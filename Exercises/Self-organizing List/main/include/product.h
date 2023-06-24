#ifndef PRODUCT_H
#define PRODUCT_H
#include <stdio.h>

typedef struct _product Product;

Product *Product_create(const int serial, const char *name, const float price);

void Product_destroy(Product **product_ref);

void Product_print(const Product *product);

int Product_get_serial(Product *product);

#endif
