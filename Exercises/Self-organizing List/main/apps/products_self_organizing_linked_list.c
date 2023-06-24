#include "../include/product.h"
#include "../include/self_organizing_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    List *list = List_create();
    char command[12];
    scanf("%s", command);

    while (strcmp(command, "stop") != 0) {
        if (strcmp(command, "add") == 0) {
            int serial;
            char name[64];
            float price;
            scanf("%d %s %f", &serial, name, &price);
            List_add_product(list, serial, name, price);
        } else if (strcmp(command, "access") == 0) {
            int serial;
            scanf("%d", &serial);
            const Product *product = List_get_product_with_serial(list, serial);
            if (product == NULL) {
                printf("Product %d not found!\n\n", serial);
            } else {
                Product_print(product);
            }
        } else if (strcmp(command, "view") == 0) {
            List_print(list);
            List_print_summary(list);
        } else {
            fprintf(stderr, "Not Allowed!\n");
        }
        scanf("%s", command);
    }

    List_print_summary(list);
    List_destroy(&list);

    return EXIT_SUCCESS;
}