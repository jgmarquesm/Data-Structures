#include <stdlib.h>
#include <stdio.h>
#include "../include/undirected_weighted_graph.h"

#define TYPE int
#define PRINT_TYPE "%d"

TYPE _convert(void *data) {
    return *((TYPE *) data);
}

void _print(void *data) {
    printf(PRINT_TYPE, _convert(data));
}

TYPE _compare(void *data1, void *data2) {
    TYPE d1 = _convert(data1), d2 = _convert(data2);
    return d2 - d1;
}

int main() {

//    char *command = "make run_tests";
//    int executed = system(command);
//    if (executed != 0) return EXIT_FAILURE;

    UWG *uwg = UWG_create(10);

    TYPE d1 = 77, d2 = 42, d3 = 97, d4 = 88;

//    printf("Valency of d1: %ld\n", UWG_get_valency(uwg, &d1));
//    UWG_get_weight(uwg, &d1, &d2);

    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d3);

    UWG_print_full_graph(uwg, _print);
    printf("Valency of d1: %ld\n", UWG_get_valency(uwg, &d1));
    printf("Valency of d2: %ld\n", UWG_get_valency(uwg, &d2));
    printf("Valency of d3: %ld\n", UWG_get_valency(uwg, &d3));

    UWG_insert_edge(uwg, &d1, &d2, 1.5);

    UWG_print_full_graph(uwg, _print);
    printf("Valency of d1: %ld\n", UWG_get_valency(uwg, &d1));
    printf("Valency of d2: %ld\n", UWG_get_valency(uwg, &d2));
    printf("Valency of d3: %ld\n", UWG_get_valency(uwg, &d3));

    UWG_insert_edge(uwg, &d2, &d3, 5.5);
    UWG_insert_edge(uwg, &d2, &d3, 99.9);

    UWG_print_full_graph(uwg, _print);
    printf("Valency of d1: %ld\n", UWG_get_valency(uwg, &d1));
    printf("Valency of d2: %ld\n", UWG_get_valency(uwg, &d2));
    printf("Valency of d3: %ld\n", UWG_get_valency(uwg, &d3));

    UWG_insert_edge(uwg, &d3, &d3, -0.89);
    UWG_insert_edge(uwg, &d1, &d3, 99.9);

    UWG_print_full_graph(uwg, _print);

    UWG_insert_vertex(uwg, &d4);
    UWG_insert_edge(uwg, &d4, &d1, -1.1);
    UWG_insert_edge(uwg, &d4, &d2, 2.2);
    UWG_insert_edge(uwg, &d4, &d3, -3.3);
    UWG_insert_edge(uwg, &d4, &d4, 4.4);
    printf("Valency of d1: %ld\n", UWG_get_valency(uwg, &d1));
    printf("Valency of d2: %ld\n", UWG_get_valency(uwg, &d2));
    printf("Valency of d3: %ld\n", UWG_get_valency(uwg, &d3));
    printf("Valency of d4: %ld\n", UWG_get_valency(uwg, &d4));
    UWG_print_full_graph(uwg, _print);

    puts("REMOVING...");
    UWG_remove_vertex(uwg, &d4);
    UWG_print_full_graph(uwg, _print);
    printf("Valency of d1: %ld\n", UWG_get_valency(uwg, &d1));
    printf("Valency of d2: %ld\n", UWG_get_valency(uwg, &d2));
    printf("Valency of d3: %ld\n", UWG_get_valency(uwg, &d3));
    printf("Valency of d4: %ld\n", UWG_get_valency(uwg, &d4));

    UWG_remove_vertex(uwg, &d4);

//    puts("REMOVING...");
//    UWG_remove_edge(uwg, &d3, &d3);
//    UWG_print_full_graph(uwg, _print);
//
//    long index = UWG_index_of(uwg, &d3);
//    printf("\n\nindex d3: %ld\n\n", index);
//
//    UWG_clean(uwg);
//    UWG_print_full_graph(uwg, _print);
//
//    UWG_insert_vertex(uwg, &d3);
//    UWG_insert_edge(uwg, &d3, &d3, -0.89);
//    UWG_print_full_graph(uwg, _print);
//
//    UWG_change_weight(uwg, &d3, &d3, 9.8);
//    UWG_print_full_graph(uwg, _print);
//
//    UWG_change_data(uwg, &d3, &d2);
//    UWG_print_full_graph(uwg, _print);

//    UWG_insert_edge(uwg, &d3, &d2, -0.89);
//    UWG_print_full_graph(uwg, _print);

    UWG_destroy(&uwg);
//    UWG_clean(uwg);
//    UWG_insert_vertex(uwg, &d3);

    return EXIT_SUCCESS;
}
