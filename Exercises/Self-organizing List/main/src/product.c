#include "../include/product.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _product {
    int serial;
    char name[64];
    float price;
} Product;

Product *Product_create(const int serial, const char *name, const float price) {
    Product *product = (Product *) calloc(1, sizeof(Product));
    product->serial = serial;
    strcpy(product->name, name);
    product->price = price;

    return product;
}

void Product_destroy(Product **product_ref) {
    free(*product_ref);
    *product_ref = NULL;
}

void Product_print(const Product *product) {
    printf("Serial number: %d\nProduct Name: %s\nPrice: %.2f\n\n", product->serial, product->name, product->price);
}

int Product_get_serial(Product *product) {
    return product->serial;
}
