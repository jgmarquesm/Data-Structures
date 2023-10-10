#include "../../main/include/unity.h"
#include "../../main/include/undirected_weighted_graph.h"
#include <stdio.h>

#define TYPE int
#define POSITIVE_MAX_OF_VERTICES 5
#define NEGATIVE_MAX_OF_VERTICES -1
#define NULL_UndirectedWeightedGraph_CAPACITY -1
#define NEW_UWG UndirectedWeightedGraph_create(POSITIVE_MAX_OF_VERTICES)

void setUp(){

}

void tearDown(){}

void test_UndirectedWeightedGraph_create_1() {
    TEST_MESSAGE("Case 1 --> Positive max_of_vertices:");
    UndirectedWeightedGraph *uwg = NULL;
    TEST_ASSERT_NULL(uwg);

    uwg = NEW_UWG;
    TEST_ASSERT_NOT_NULL(uwg);

    long capacity = UndirectedWeightedGraph_get_capacity(uwg);
    TEST_ASSERT_EQUAL(POSITIVE_MAX_OF_VERTICES, capacity);

    long size = UndirectedWeightedGraph_get_size(uwg);
    TEST_ASSERT_EQUAL(0, size);
}

void test_UndirectedWeightedGraph_create_2() {
    TEST_MESSAGE("Case 2 --> Negative max_of_vertices:");
    UndirectedWeightedGraph *uwg = NULL;
    TEST_ASSERT_NULL(uwg);

    uwg = UndirectedWeightedGraph_create(NEGATIVE_MAX_OF_VERTICES);
    TEST_ASSERT_NULL(uwg);
}

void test_UndirectedWeightedGraph_clean_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    UndirectedWeightedGraph *uwg = NEW_UWG;
    bool cleaned = UndirectedWeightedGraph_clean(uwg);
    TEST_ASSERT_TRUE(cleaned);
}

void test_UndirectedWeightedGraph_clean_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UndirectedWeightedGraph *uwg = NULL;
    TEST_ASSERT_NULL(uwg);
    bool cleaned = UndirectedWeightedGraph_clean(uwg);
    TEST_ASSERT_FALSE(cleaned);
}

void test_UndirectedWeightedGraph_destroy_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    UndirectedWeightedGraph *uwg = NEW_UWG;
    bool destroyed = UndirectedWeightedGraph_destroy(&uwg);
    TEST_ASSERT_TRUE(destroyed);
}

void test_UndirectedWeightedGraph_destroy_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UndirectedWeightedGraph *uwg = NULL;
    bool destroyed = UndirectedWeightedGraph_destroy(&uwg);
    TEST_ASSERT_FALSE(destroyed);
}

void test_UndirectedWeightedGraph_index_of_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2, d3, d4, d5;
    UndirectedWeightedGraph *uwg = NEW_UWG;

    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(1, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_EQUAL(0, UndirectedWeightedGraph_index_of(uwg, &d1));

    UndirectedWeightedGraph_insert_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(2, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_EQUAL(1, UndirectedWeightedGraph_index_of(uwg, &d2));

    UndirectedWeightedGraph_insert_vertex(uwg, &d3);
    TEST_ASSERT_EQUAL(3, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_EQUAL(2, UndirectedWeightedGraph_index_of(uwg, &d3));

    UndirectedWeightedGraph_insert_vertex(uwg, &d4);
    TEST_ASSERT_EQUAL(4, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_EQUAL(3, UndirectedWeightedGraph_index_of(uwg, &d4));

    UndirectedWeightedGraph_insert_vertex(uwg, &d5);
    TEST_ASSERT_EQUAL(5, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_EQUAL(4, UndirectedWeightedGraph_index_of(uwg, &d5));
}

void test_UndirectedWeightedGraph_index_of_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NULL;
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, UndirectedWeightedGraph_index_of(uwg, &d1));
}

void test_UndirectedWeightedGraph_index_of_3() {
    TEST_MESSAGE("Case 3 --> All okay but null vertex:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, UndirectedWeightedGraph_index_of(uwg, NULL));
}

void test_UndirectedWeightedGraph_index_of_4() {
    TEST_MESSAGE("Case 4 --> Empty Undirected Weighted Graph:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, UndirectedWeightedGraph_index_of(uwg, &d1));
}

void test_UndirectedWeightedGraph_is_empty_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    TEST_ASSERT_EQUAL(0, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_TRUE(UndirectedWeightedGraph_is_empty(uwg));

    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(1, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_FALSE(UndirectedWeightedGraph_is_empty(uwg));

    UndirectedWeightedGraph_remove_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(0, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_TRUE(UndirectedWeightedGraph_is_empty(uwg));
}

void test_UndirectedWeightedGraph_is_empty_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UndirectedWeightedGraph *uwg = NULL;
    TEST_ASSERT_TRUE(UndirectedWeightedGraph_is_empty(uwg));
}

void test_UndirectedWeightedGraph_is_full_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2, d3, d4, d5;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    TEST_ASSERT_EQUAL(0, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_FALSE(UndirectedWeightedGraph_is_full(uwg));

    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(1, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_FALSE(UndirectedWeightedGraph_is_full(uwg));
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(2, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_FALSE(UndirectedWeightedGraph_is_full(uwg));
    UndirectedWeightedGraph_insert_vertex(uwg, &d3);
    TEST_ASSERT_EQUAL(3, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_FALSE(UndirectedWeightedGraph_is_full(uwg));
    UndirectedWeightedGraph_insert_vertex(uwg, &d4);
    TEST_ASSERT_EQUAL(4, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_FALSE(UndirectedWeightedGraph_is_full(uwg));
    UndirectedWeightedGraph_insert_vertex(uwg, &d5);
    TEST_ASSERT_EQUAL(5, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_TRUE(UndirectedWeightedGraph_is_full(uwg));

    UndirectedWeightedGraph_remove_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(4, UndirectedWeightedGraph_get_size(uwg));
    TEST_ASSERT_FALSE(UndirectedWeightedGraph_is_full(uwg));
}

void test_UndirectedWeightedGraph_is_full_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UndirectedWeightedGraph *uwg = NULL;
    TEST_ASSERT_FALSE(UndirectedWeightedGraph_is_full(uwg));
}

void test_UndirectedWeightedGraph_insert_vertex_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;

    bool inserted = UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    TEST_ASSERT_TRUE(inserted);
}

void test_UndirectedWeightedGraph_insert_vertex_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NULL;

    bool inserted = UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    TEST_ASSERT_FALSE(inserted);
}

void test_UndirectedWeightedGraph_insert_vertex_3() {
    TEST_MESSAGE("Case 3 --> Non Null Undirected Weighted Graph but Null Data:");
    UndirectedWeightedGraph *uwg = NEW_UWG;

    bool inserted = UndirectedWeightedGraph_insert_vertex(uwg, NULL);
    TEST_ASSERT_FALSE(inserted);
}

void test_UndirectedWeightedGraph_insert_vertex_4() {
    TEST_MESSAGE("Case 4 --> Full Undirected Weighted Graph:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    TEST_ASSERT_EQUAL(0, UndirectedWeightedGraph_get_size(uwg));

    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    bool inserted = UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    TEST_ASSERT_FALSE(inserted);
}

void test_UndirectedWeightedGraph_insert_edge_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);

    bool inserted = UndirectedWeightedGraph_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_TRUE(inserted);
}

void test_UndirectedWeightedGraph_insert_edge_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NULL;

    bool inserted = UndirectedWeightedGraph_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_FALSE(inserted);
}

void test_UndirectedWeightedGraph_insert_edge_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;

    bool inserted = UndirectedWeightedGraph_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_FALSE(inserted);
}

void test_UndirectedWeightedGraph_insert_edge_4() {
    TEST_MESSAGE("Case 4 --> Null Exit Vertex:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);

    bool inserted = UndirectedWeightedGraph_insert_edge(uwg, NULL, &d1, 1.1f);
    TEST_ASSERT_FALSE(inserted);
}

void test_UndirectedWeightedGraph_insert_edge_5() {
    TEST_MESSAGE("Case 5 --> Null Entry Vertex:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);

    bool inserted = UndirectedWeightedGraph_insert_edge(uwg, &d1, NULL, 1.1f);
    TEST_ASSERT_FALSE(inserted);
}

void test_UndirectedWeightedGraph_insert_edge_6() {
    TEST_MESSAGE("Case 6 --> Exit Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);

    bool inserted = UndirectedWeightedGraph_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_FALSE(inserted);
}

void test_UndirectedWeightedGraph_insert_edge_7() {
    TEST_MESSAGE("Case 7 --> Entry Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);

    bool inserted = UndirectedWeightedGraph_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_FALSE(inserted);
}

void test_UndirectedWeightedGraph_change_weight_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);
    UndirectedWeightedGraph_insert_edge(uwg, &d1, &d2, 1.1f);

    bool weight_changed = UndirectedWeightedGraph_change_weight(uwg, &d1, &d2, 9.9f);
    TEST_ASSERT_TRUE(weight_changed);
}

void test_UndirectedWeightedGraph_change_weight_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NULL;

    bool weight_changed = UndirectedWeightedGraph_change_weight(uwg, &d1, &d2, 9.9f);
    TEST_ASSERT_FALSE(weight_changed);
}

void test_UndirectedWeightedGraph_change_weight_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;

    bool weight_changed = UndirectedWeightedGraph_change_weight(uwg, &d1, &d2, 9.9f);
    TEST_ASSERT_FALSE(weight_changed);
}

void test_UndirectedWeightedGraph_change_weight_4() {
    TEST_MESSAGE("Case 4 --> Null Exit Vertex:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);

    bool weight_changed = UndirectedWeightedGraph_change_weight(uwg, NULL, &d1, 9.9f);
    TEST_ASSERT_FALSE(weight_changed);
}

void test_UndirectedWeightedGraph_change_weight_5() {
    TEST_MESSAGE("Case 5 --> Null Entry Vertex:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);

    bool weight_changed = UndirectedWeightedGraph_change_weight(uwg, &d1, NULL, 9.9f);
    TEST_ASSERT_FALSE(weight_changed);
}

void test_UndirectedWeightedGraph_change_weight_6() {
    TEST_MESSAGE("Case 6 --> Exit Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);

    bool weight_changed = UndirectedWeightedGraph_change_weight(uwg, &d1, &d2, 9.9f);
    TEST_ASSERT_FALSE(weight_changed);
}

void test_UndirectedWeightedGraph_change_weight_7() {
    TEST_MESSAGE("Case 7 --> Entry Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);

    bool weight_changed = UndirectedWeightedGraph_change_weight(uwg, &d1, &d2, 9.9f);
    TEST_ASSERT_FALSE(weight_changed);
}

void test_UndirectedWeightedGraph_change_data_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);

    bool data_changed = UndirectedWeightedGraph_change_data(uwg, &d1, &d2);
    TEST_ASSERT_TRUE(data_changed);
}

void test_UndirectedWeightedGraph_change_data_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NULL;

    bool data_changed = UndirectedWeightedGraph_change_data(uwg, &d1, &d2);
    TEST_ASSERT_FALSE(data_changed);
}

void test_UndirectedWeightedGraph_change_data_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;

    bool data_changed = UndirectedWeightedGraph_change_data(uwg, &d1, &d2);
    TEST_ASSERT_FALSE(data_changed);
}

void test_UndirectedWeightedGraph_change_data_4() {
    TEST_MESSAGE("Case 4 --> Old Data is NullL:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;

    bool data_changed = UndirectedWeightedGraph_change_data(uwg, NULL, &d1);
    TEST_ASSERT_FALSE(data_changed);
}

void test_UndirectedWeightedGraph_change_data_5() {
    TEST_MESSAGE("Case 5 --> New Data is Null:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;

    bool data_changed = UndirectedWeightedGraph_change_data(uwg, &d1, NULL);
    TEST_ASSERT_FALSE(data_changed);
}

void test_UndirectedWeightedGraph_get_capacity_1() {
    TEST_MESSAGE("Case 1 --> Non Null Undirected Weighted Graph:");
    UndirectedWeightedGraph *uwg = NEW_UWG;
    long capacity = UndirectedWeightedGraph_get_capacity(uwg);
    TEST_ASSERT_EQUAL(POSITIVE_MAX_OF_VERTICES, capacity);
}

void test_UndirectedWeightedGraph_get_capacity_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UndirectedWeightedGraph *uwg = NULL;
    long capacity = UndirectedWeightedGraph_get_capacity(uwg);
    TEST_ASSERT_EQUAL(NULL_UndirectedWeightedGraph_CAPACITY, capacity);
}

void test_UndirectedWeightedGraph_get_size_1() {
    TEST_MESSAGE("Case 1 --> Non Null Undirected Weighted Graph:");
    UndirectedWeightedGraph *uwg = NEW_UWG;
    long size = UndirectedWeightedGraph_get_size(uwg);
    TEST_ASSERT_EQUAL(0, size);
}

void test_UndirectedWeightedGraph_get_size_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UndirectedWeightedGraph *uwg = NULL;
    long size = UndirectedWeightedGraph_get_size(uwg);
    TEST_ASSERT_EQUAL(NULL_UndirectedWeightedGraph_CAPACITY, size);
}

void test_UndirectedWeightedGraph_get_weight_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);
    UndirectedWeightedGraph_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(1.1f, UndirectedWeightedGraph_get_weight(uwg, &d1, &d2));
    TEST_ASSERT_EQUAL(1.1f, UndirectedWeightedGraph_get_weight(uwg, &d2, &d1));
}

void test_UndirectedWeightedGraph_get_weight_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NULL;
    TEST_ASSERT_EQUAL(__DEFAULT_INITIAL_WEIGHT__, UndirectedWeightedGraph_get_weight(uwg, &d1, &d2));
    TEST_ASSERT_EQUAL(__DEFAULT_INITIAL_WEIGHT__, UndirectedWeightedGraph_get_weight(uwg, &d2, &d1));
}

void test_UndirectedWeightedGraph_get_weight_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    TEST_ASSERT_EQUAL(__DEFAULT_INITIAL_WEIGHT__, UndirectedWeightedGraph_get_weight(uwg, &d1, &d2));
    TEST_ASSERT_EQUAL(__DEFAULT_INITIAL_WEIGHT__, UndirectedWeightedGraph_get_weight(uwg, &d2, &d1));
}

void test_UndirectedWeightedGraph_get_weight_4() {
    TEST_MESSAGE("Case 4 --> Null Exit Vertex:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);

    TEST_ASSERT_EQUAL(__DEFAULT_INITIAL_WEIGHT__, UndirectedWeightedGraph_get_weight(uwg, NULL, &d2));
    TEST_ASSERT_EQUAL(__DEFAULT_INITIAL_WEIGHT__, UndirectedWeightedGraph_get_weight(uwg, NULL, &d1));
}

void test_UndirectedWeightedGraph_get_weight_5() {
    TEST_MESSAGE("Case 5 --> Null Entry Vertex:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);

    TEST_ASSERT_EQUAL(__DEFAULT_INITIAL_WEIGHT__, UndirectedWeightedGraph_get_weight(uwg, &d1, NULL));
    TEST_ASSERT_EQUAL(__DEFAULT_INITIAL_WEIGHT__, UndirectedWeightedGraph_get_weight(uwg, &d2, NULL));
}

void test_UndirectedWeightedGraph_get_weight_6() {
    TEST_MESSAGE("Case 6 --> Exit Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);

    TEST_ASSERT_EQUAL(__DEFAULT_INITIAL_WEIGHT__, UndirectedWeightedGraph_get_weight(uwg, &d1, &d2));
}

void test_UndirectedWeightedGraph_get_weight_7() {
    TEST_MESSAGE("Case 7 --> Entry Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);

    TEST_ASSERT_EQUAL(__DEFAULT_INITIAL_WEIGHT__, UndirectedWeightedGraph_get_weight(uwg, &d1, &d2));
}

void test_UndirectedWeightedGraph_get_data_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2, d3;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);
    UndirectedWeightedGraph_insert_vertex(uwg, &d3);
    TYPE *data_index_2 = (TYPE *) UndirectedWeightedGraph_get_data(uwg, 2);
    TEST_ASSERT_EQUAL(&d3, data_index_2);
}

void test_UndirectedWeightedGraph_get_data_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UndirectedWeightedGraph *uwg = NULL;
    TYPE *data_index_2 = (TYPE *) UndirectedWeightedGraph_get_data(uwg, 2);
    TEST_ASSERT_NULL(data_index_2);
}

void test_UndirectedWeightedGraph_get_data_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    UndirectedWeightedGraph *uwg = NEW_UWG;
    TYPE *data_index_2 = (TYPE *) UndirectedWeightedGraph_get_data(uwg, 2);
    TEST_ASSERT_NULL(data_index_2);
}

void test_UndirectedWeightedGraph_get_data_4() {
    TEST_MESSAGE("Case 4 --> Negative index:");
    UndirectedWeightedGraph *uwg = NEW_UWG;
    TYPE *data = (TYPE *) UndirectedWeightedGraph_get_data(uwg, -1);
    TEST_ASSERT_NULL(data);
}

void test_UndirectedWeightedGraph_get_data_5() {
    TEST_MESSAGE("Case 5 --> Index greater than UndirectedWeightedGraph::Size:");
    UndirectedWeightedGraph *uwg = NEW_UWG;
    TYPE *data = (TYPE *) UndirectedWeightedGraph_get_data(uwg, 1);
    TEST_ASSERT_NULL(data);
}

void test_UndirectedWeightedGraph_get_valency_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(0, UndirectedWeightedGraph_get_valency(uwg, &d1));
    UndirectedWeightedGraph_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(1, UndirectedWeightedGraph_get_valency(uwg, &d1));
}

void test_UndirectedWeightedGraph_get_valency_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NULL;
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, UndirectedWeightedGraph_get_valency(uwg, &d1));
}

void test_UndirectedWeightedGraph_get_valency_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, UndirectedWeightedGraph_get_valency(uwg, &d1));
}

void test_UndirectedWeightedGraph_get_valency_4() {
    TEST_MESSAGE("Case 4 --> Null Vertex:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, UndirectedWeightedGraph_get_valency(uwg, NULL));
}

void test_UndirectedWeightedGraph_get_valency_5() {
    TEST_MESSAGE("Case 5 --> Vertex not in Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(__DEFAULT_LONG__, UndirectedWeightedGraph_get_valency(uwg, &d2));
}

void test_UndirectedWeightedGraph_remove_edge_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);

    TEST_ASSERT_EQUAL(0, UndirectedWeightedGraph_get_valency(uwg, &d1));

    UndirectedWeightedGraph_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(1, UndirectedWeightedGraph_get_valency(uwg, &d1));

    bool removed = UndirectedWeightedGraph_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_TRUE(removed);
    TEST_ASSERT_EQUAL(0, UndirectedWeightedGraph_get_valency(uwg, &d1));
}

void test_UndirectedWeightedGraph_remove_edge_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NULL;
    bool removed = UndirectedWeightedGraph_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_FALSE(removed);
}

void test_UndirectedWeightedGraph_remove_edge_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    bool removed = UndirectedWeightedGraph_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_FALSE(removed);
}

void test_UndirectedWeightedGraph_remove_edge_4() {
    TEST_MESSAGE("Case 4 --> Null Exit Vertex:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    bool removed = UndirectedWeightedGraph_remove_edge(uwg, NULL, &d2);
    TEST_ASSERT_FALSE(removed);
}

void test_UndirectedWeightedGraph_remove_edge_5() {
    TEST_MESSAGE("Case 4 --> Null Entry Vertex:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    bool removed = UndirectedWeightedGraph_remove_edge(uwg, &d1, NULL);
    TEST_ASSERT_FALSE(removed);
}

void test_UndirectedWeightedGraph_remove_edge_6() {
    TEST_MESSAGE("Case 6 --> Exit Vertex not in Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d2);
    bool removed = UndirectedWeightedGraph_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_FALSE(removed);
}

void test_UndirectedWeightedGraph_remove_edge_7() {
    TEST_MESSAGE("Case 7 --> Entry Vertex not in Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    bool removed = UndirectedWeightedGraph_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_FALSE(removed);
}

void test_UndirectedWeightedGraph_remove_vertex_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);

    bool removed = UndirectedWeightedGraph_remove_vertex(uwg, &d1);
    TEST_ASSERT_TRUE(removed);
}

void test_UndirectedWeightedGraph_remove_vertex_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NULL;
    bool removed = UndirectedWeightedGraph_remove_vertex(uwg, &d1);
    TEST_ASSERT_FALSE(removed);
}

void test_UndirectedWeightedGraph_remove_vertex_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    bool removed = UndirectedWeightedGraph_remove_vertex(uwg, &d1);
    TEST_ASSERT_FALSE(removed);
}

void test_UndirectedWeightedGraph_remove_vertex_4() {
    TEST_MESSAGE("Case 4 --> Null Vertex:");
    TYPE d1;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    bool removed = UndirectedWeightedGraph_remove_vertex(uwg, NULL);
    TEST_ASSERT_FALSE(removed);
}

void test_UndirectedWeightedGraph_remove_vertex_5() {
    TEST_MESSAGE("Case 5 --> Vertex not in Undirected Weighted Graph:");
    TYPE d1, d2;
    UndirectedWeightedGraph *uwg = NEW_UWG;
    UndirectedWeightedGraph_insert_vertex(uwg, &d1);
    bool removed = UndirectedWeightedGraph_remove_vertex(uwg, &d2);
    TEST_ASSERT_FALSE(removed);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_UndirectedWeightedGraph_create_1);
    RUN_TEST(test_UndirectedWeightedGraph_create_2);
    RUN_TEST(test_UndirectedWeightedGraph_clean_1);
    RUN_TEST(test_UndirectedWeightedGraph_clean_2);
    RUN_TEST(test_UndirectedWeightedGraph_destroy_1);
    RUN_TEST(test_UndirectedWeightedGraph_destroy_2);
    RUN_TEST(test_UndirectedWeightedGraph_index_of_1);
    RUN_TEST(test_UndirectedWeightedGraph_index_of_2);
    RUN_TEST(test_UndirectedWeightedGraph_index_of_3);
    RUN_TEST(test_UndirectedWeightedGraph_index_of_4);
    RUN_TEST(test_UndirectedWeightedGraph_is_empty_1);
    RUN_TEST(test_UndirectedWeightedGraph_is_empty_2);
    RUN_TEST(test_UndirectedWeightedGraph_is_full_1);
    RUN_TEST(test_UndirectedWeightedGraph_is_full_2);
    RUN_TEST(test_UndirectedWeightedGraph_insert_vertex_1);
    RUN_TEST(test_UndirectedWeightedGraph_insert_vertex_2);
    RUN_TEST(test_UndirectedWeightedGraph_insert_vertex_3);
    RUN_TEST(test_UndirectedWeightedGraph_insert_vertex_4);
    RUN_TEST(test_UndirectedWeightedGraph_insert_edge_1);
    RUN_TEST(test_UndirectedWeightedGraph_insert_edge_2);
    RUN_TEST(test_UndirectedWeightedGraph_insert_edge_3);
    RUN_TEST(test_UndirectedWeightedGraph_insert_edge_4);
    RUN_TEST(test_UndirectedWeightedGraph_insert_edge_5);
    RUN_TEST(test_UndirectedWeightedGraph_insert_edge_6);
    RUN_TEST(test_UndirectedWeightedGraph_insert_edge_7);
    RUN_TEST(test_UndirectedWeightedGraph_change_weight_1);
    RUN_TEST(test_UndirectedWeightedGraph_change_weight_2);
    RUN_TEST(test_UndirectedWeightedGraph_change_weight_3);
    RUN_TEST(test_UndirectedWeightedGraph_change_weight_4);
    RUN_TEST(test_UndirectedWeightedGraph_change_weight_5);
    RUN_TEST(test_UndirectedWeightedGraph_change_weight_6);
    RUN_TEST(test_UndirectedWeightedGraph_change_weight_7);
    RUN_TEST(test_UndirectedWeightedGraph_change_data_1);
    RUN_TEST(test_UndirectedWeightedGraph_change_data_2);
    RUN_TEST(test_UndirectedWeightedGraph_change_data_3);
    RUN_TEST(test_UndirectedWeightedGraph_change_data_4);
    RUN_TEST(test_UndirectedWeightedGraph_change_data_5);
    RUN_TEST(test_UndirectedWeightedGraph_get_capacity_1);
    RUN_TEST(test_UndirectedWeightedGraph_get_capacity_2);
    RUN_TEST(test_UndirectedWeightedGraph_get_size_1);
    RUN_TEST(test_UndirectedWeightedGraph_get_size_2);
    RUN_TEST(test_UndirectedWeightedGraph_get_weight_1);
    RUN_TEST(test_UndirectedWeightedGraph_get_weight_2);
    RUN_TEST(test_UndirectedWeightedGraph_get_weight_3);
    RUN_TEST(test_UndirectedWeightedGraph_get_weight_4);
    RUN_TEST(test_UndirectedWeightedGraph_get_weight_5);
    RUN_TEST(test_UndirectedWeightedGraph_get_weight_6);
    RUN_TEST(test_UndirectedWeightedGraph_get_weight_7);
    RUN_TEST(test_UndirectedWeightedGraph_get_data_1);
    RUN_TEST(test_UndirectedWeightedGraph_get_data_2);
    RUN_TEST(test_UndirectedWeightedGraph_get_data_3);
    RUN_TEST(test_UndirectedWeightedGraph_get_data_4);
    RUN_TEST(test_UndirectedWeightedGraph_get_data_5);
    RUN_TEST(test_UndirectedWeightedGraph_get_valency_1);
    RUN_TEST(test_UndirectedWeightedGraph_get_valency_2);
    RUN_TEST(test_UndirectedWeightedGraph_get_valency_3);
    RUN_TEST(test_UndirectedWeightedGraph_get_valency_4);
    RUN_TEST(test_UndirectedWeightedGraph_get_valency_5);
    RUN_TEST(test_UndirectedWeightedGraph_remove_edge_1);
    RUN_TEST(test_UndirectedWeightedGraph_remove_edge_2);
    RUN_TEST(test_UndirectedWeightedGraph_remove_edge_3);
    RUN_TEST(test_UndirectedWeightedGraph_remove_edge_4);
    RUN_TEST(test_UndirectedWeightedGraph_remove_edge_5);
    RUN_TEST(test_UndirectedWeightedGraph_remove_edge_6);
    RUN_TEST(test_UndirectedWeightedGraph_remove_edge_7);
    RUN_TEST(test_UndirectedWeightedGraph_remove_vertex_1);
    RUN_TEST(test_UndirectedWeightedGraph_remove_vertex_2);
    RUN_TEST(test_UndirectedWeightedGraph_remove_vertex_3);
    RUN_TEST(test_UndirectedWeightedGraph_remove_vertex_4);
    RUN_TEST(test_UndirectedWeightedGraph_remove_vertex_5);
    return UNITY_END();
}
