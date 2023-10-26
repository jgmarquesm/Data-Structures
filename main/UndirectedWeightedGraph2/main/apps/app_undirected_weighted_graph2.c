#include <stdlib.h>
#include <stdio.h>
#include "../include/undirected_weighted_graph2.h"

int main() {

//    char *command = "make run_tests";
//    int executed = system(command);
//    if (executed != 0) return EXIT_FAILURE;

    UndirectedWeightedGraph2 *uwg = UndirectedWeightedGraph2_create();
    int a = 1, b = 2, c = 3;
    UndirectedWeightedGraph2_insert_Vertex(uwg, &a);
    UndirectedWeightedGraph2_insert_Vertex(uwg, &b);
    UndirectedWeightedGraph2_insert_Vertex(uwg, &c);

    UndirectedWeightedGraph2_add_Edge(uwg, 0, 1, 1.1);
    UndirectedWeightedGraph2_add_Edge(uwg, 0, 2, 2.2);
    UndirectedWeightedGraph2_add_Edge(uwg, 1, 2, 3.3);

    float edge_0_1 = UndirectedWeightedGraph2_get_weight(uwg, 0, 1);
    float edge_0_2 = UndirectedWeightedGraph2_get_weight(uwg, 0, 2);
    float edge_1_2 = UndirectedWeightedGraph2_get_weight(uwg, 1, 2);

    printf("Edge(0, 1): %f\n", edge_0_1);
    printf("Edge(0, 2): %f\n", edge_0_2);
    printf("Edge(1, 2): %f\n", edge_1_2);

    int d = 4, e = 5;
    UndirectedWeightedGraph2_insert_Vertex(uwg, &d);
    UndirectedWeightedGraph2_insert_Vertex(uwg, &e);
    UndirectedWeightedGraph2_add_Edge(uwg, 3, 0, 4.4);
    UndirectedWeightedGraph2_add_Edge(uwg, 3, 1, 4.4);
    UndirectedWeightedGraph2_add_Edge(uwg, 3, 2, 4.4);

    float edge_0_1_p = UndirectedWeightedGraph2_get_weight(uwg, 0, 1);
    float edge_0_2_p = UndirectedWeightedGraph2_get_weight(uwg, 0, 2);
    float edge_1_2_p = UndirectedWeightedGraph2_get_weight(uwg, 1, 2);
    float edge_0_3 = UndirectedWeightedGraph2_get_weight(uwg, 3, 0);
    float edge_1_3 = UndirectedWeightedGraph2_get_weight(uwg, 3, 1);
    float edge_2_3 = UndirectedWeightedGraph2_get_weight(uwg, 3, 2);

    printf("Edge(0, 1): %f\n", edge_0_1_p);
    printf("Edge(0, 2): %f\n", edge_0_2_p);
    printf("Edge(1, 2): %f\n", edge_1_2_p);
    printf("Edge(0, 3): %f\n", edge_0_3);
    printf("Edge(1, 3): %f\n", edge_1_3);
    printf("Edge(2, 3): %f\n", edge_2_3);

    UndirectedWeightedGraph2_add_Edge(uwg, 3, 2, 4.4);

    UndirectedWeightedGraph2_set_weight(uwg, 3, 2, 99.99);
    float edge_2_3_p = UndirectedWeightedGraph2_get_weight(uwg, 3, 2);
    printf("Edge(2, 3): %f\n", edge_2_3_p);

    float edge_0_2_p_p = UndirectedWeightedGraph2_get_weight(uwg, 2, 0);
    printf("Edge(0, 2): %f\n", edge_0_2_p_p);

    UndirectedWeightedGraph2_remove_Edge(uwg, 0, 2);
    float edge_0_2_p_p_p = UndirectedWeightedGraph2_get_weight(uwg, 0, 2);
    printf("Edge(0, 2): %f\n", edge_0_2_p_p_p);

    float edge_0_1_p_ = UndirectedWeightedGraph2_get_weight(uwg, 0, 1);
    float edge_0_2_p_ = UndirectedWeightedGraph2_get_weight(uwg, 0, 2);
    float edge_0_3_p_ = UndirectedWeightedGraph2_get_weight(uwg, 0, 3);
    printf("Edge(0, 1): %f\n", edge_0_1_p_);
    printf("Edge(0, 2): %f\n", edge_0_2_p_);
    printf("Edge(0, 3): %f\n", edge_0_3_p_);
    UndirectedWeightedGraph2_remove_Vertex(uwg, 0);
    float edge_0_1_p__ = UndirectedWeightedGraph2_get_weight(uwg, 0, 1);
    float edge_0_2_p__ = UndirectedWeightedGraph2_get_weight(uwg, 0, 2);
    float edge_0_3_p__ = UndirectedWeightedGraph2_get_weight(uwg, 0, 3);
    printf("Edge(0, 1): %f\n", edge_0_1_p__);
    printf("Edge(0, 2): %f\n", edge_0_2_p__);
    printf("Edge(0, 3): %f\n", edge_0_3_p__);

    return EXIT_SUCCESS;
}
