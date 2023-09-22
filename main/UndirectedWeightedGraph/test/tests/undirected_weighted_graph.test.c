#include "../../main/include/unity.h"
#include "../../main/include/undirected_weighted_graph.h"
#include <stdio.h>

#define TYPE int
#define POSITIVE_MAX_OF_VERTICES 5
#define NEGATIVE_MAX_OF_VERTICES -1
#define NULL_UWG_CAPACITY -1

void setUp(){

}

void tearDown(){}

void test_UWG_create_1() {
    TEST_MESSAGE("Case 1 --> Positive max_of_vertices:");
    UWG *uwg = NULL;
    TEST_ASSERT_EQUAL(NULL, uwg);

    uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    TEST_ASSERT_NOT_EQUAL(NULL, uwg);

    long capacity = UWG_get_capacity(uwg);
    TEST_ASSERT_EQUAL(POSITIVE_MAX_OF_VERTICES, capacity);

    long size = UWG_get_size(uwg);
    TEST_ASSERT_EQUAL(0, size);
}

void test_UWG_create_2() {
    TEST_MESSAGE("Case 2 --> Negative max_of_vertices:");
    UWG *uwg = NULL;
    TEST_ASSERT_EQUAL(NULL, uwg);

    uwg = UWG_create(NEGATIVE_MAX_OF_VERTICES);
    TEST_ASSERT_EQUAL(NULL, uwg);
}

void test_UWG_clean_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    bool cleaned = UWG_clean(uwg);
    TEST_ASSERT_EQUAL(true, cleaned);
}

void test_UWG_clean_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UWG *uwg = NULL;
    TEST_ASSERT_EQUAL(NULL, uwg);
    bool cleaned = UWG_clean(uwg);
    TEST_ASSERT_EQUAL(false, cleaned);
}

void test_UWG_destroy_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    bool destroyed = UWG_destroy(&uwg);
    TEST_ASSERT_EQUAL(true, destroyed);
}

void test_UWG_destroy_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UWG *uwg = NULL;
    bool destroyed = UWG_destroy(&uwg);
    TEST_ASSERT_EQUAL(false, destroyed);
}

void test_UWG_index_of_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2, d3, d4, d5;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);

    UWG_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(1, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(0, UWG_index_of(uwg, &d1));

    UWG_insert_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(2, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(1, UWG_index_of(uwg, &d2));

    UWG_insert_vertex(uwg, &d3);
    TEST_ASSERT_EQUAL(3, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(2, UWG_index_of(uwg, &d3));

    UWG_insert_vertex(uwg, &d4);
    TEST_ASSERT_EQUAL(4, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(3, UWG_index_of(uwg, &d4));

    UWG_insert_vertex(uwg, &d5);
    TEST_ASSERT_EQUAL(5, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(4, UWG_index_of(uwg, &d5));
}

void test_UWG_index_of_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1;
    UWG *uwg = NULL;
    TEST_ASSERT_EQUAL(-1, UWG_index_of(uwg, &d1));
}

void test_UWG_index_of_3() {
    TEST_MESSAGE("Case 3 --> All okay but null vertex:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(-1, UWG_index_of(uwg, NULL));
}

void test_UWG_index_of_4() {
    TEST_MESSAGE("Case 4 --> Empty Undirected Weighted Graph:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    TEST_ASSERT_EQUAL(-1, UWG_index_of(uwg, &d1));
}

void test_UWG_is_empty_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(true, UWG_is_empty(uwg));

    UWG_insert_vertex(uwg, &d);
    TEST_ASSERT_EQUAL(1, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(false, UWG_is_empty(uwg));

    UWG_remove_vertex(uwg, &d);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(true, UWG_is_empty(uwg));
}

void test_UWG_is_empty_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UWG *uwg = NULL;
    TEST_ASSERT_EQUAL(true, UWG_is_empty(uwg));
}

void test_UWG_is_full_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2, d3, d4, d5;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(false, UWG_is_full(uwg));

    UWG_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(1, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(false, UWG_is_full(uwg));
    UWG_insert_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(2, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(false, UWG_is_full(uwg));
    UWG_insert_vertex(uwg, &d3);
    TEST_ASSERT_EQUAL(3, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(false, UWG_is_full(uwg));
    UWG_insert_vertex(uwg, &d4);
    TEST_ASSERT_EQUAL(4, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(false, UWG_is_full(uwg));
    UWG_insert_vertex(uwg, &d5);
    TEST_ASSERT_EQUAL(5, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(true, UWG_is_full(uwg));

    UWG_remove_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(4, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(false, UWG_is_full(uwg));
}

void test_UWG_is_full_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UWG *uwg = NULL;
    TEST_ASSERT_EQUAL(false, UWG_is_full(uwg));
}

void test_UWG_insert_vertex_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);

    bool inserted = UWG_insert_vertex(uwg, &d);
    TEST_ASSERT_EQUAL(true, inserted);
}

void test_UWG_insert_vertex_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d;
    UWG *uwg = NULL;

    bool inserted = UWG_insert_vertex(uwg, &d);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_UWG_insert_vertex_3() {
    TEST_MESSAGE("Case 3 --> Non Null Undirected Weighted Graph but Null Data:");
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);

    bool inserted = UWG_insert_vertex(uwg, NULL);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_UWG_insert_vertex_4() {
    TEST_MESSAGE("Case 4 --> Full Undirected Weighted Graph:");
    TYPE d;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));

    UWG_insert_vertex(uwg, &d);
    UWG_insert_vertex(uwg, &d);
    UWG_insert_vertex(uwg, &d);
    UWG_insert_vertex(uwg, &d);
    UWG_insert_vertex(uwg, &d);
    bool inserted = UWG_insert_vertex(uwg, &d);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_UWG_insert_edge_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);

    bool inserted = UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(true, inserted);
}

void test_UWG_insert_edge_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = NULL;

    bool inserted = UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_UWG_insert_edge_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);

    bool inserted = UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_UWG_insert_edge_4() {
    TEST_MESSAGE("Case 4 --> Null Exit Vertex:");
    TYPE d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d2);

    bool inserted = UWG_insert_edge(uwg, NULL, &d2, 1.1f);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_UWG_insert_edge_5() {
    TEST_MESSAGE("Case 5 --> Null Entry Vertex:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);

    bool inserted = UWG_insert_edge(uwg, &d1, NULL, 1.1f);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_UWG_insert_edge_6() {
    TEST_MESSAGE("Case 6 --> Exit Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d2);

    bool inserted = UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_UWG_insert_edge_7() {
    TEST_MESSAGE("Case 7 --> Entry Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);

    bool inserted = UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(false, inserted);
}

void test_UWG_change_weight_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_edge(uwg, &d1, &d2, 1.1f);

    bool weight_changed = UWG_change_weight(uwg, &d1, &d2, 9.9f);
    TEST_ASSERT_EQUAL(true, weight_changed);
}

void test_UWG_change_weight_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = NULL;

    bool weight_changed = UWG_change_weight(uwg, &d1, &d2, 9.9f);
    TEST_ASSERT_EQUAL(false, weight_changed);
}

void test_UWG_change_weight_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);

    bool weight_changed = UWG_change_weight(uwg, &d1, &d2, 9.9f);
    TEST_ASSERT_EQUAL(false, weight_changed);
}

void test_UWG_change_weight_4() {
    TEST_MESSAGE("Case 4 --> Null Exit Vertex:");
    TYPE d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d2);

    bool weight_changed = UWG_change_weight(uwg, NULL, &d2, 9.9f);
    TEST_ASSERT_EQUAL(false, weight_changed);
}

void test_UWG_change_weight_5() {
    TEST_MESSAGE("Case 5 --> Null Entry Vertex:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);

    bool weight_changed = UWG_change_weight(uwg, &d1, NULL, 9.9f);
    TEST_ASSERT_EQUAL(false, weight_changed);
}

void test_UWG_change_weight_6() {
    TEST_MESSAGE("Case 6 --> Exit Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d2);

    bool weight_changed = UWG_change_weight(uwg, &d1, &d2, 9.9f);
    TEST_ASSERT_EQUAL(false, weight_changed);
}

void test_UWG_change_weight_7() {
    TEST_MESSAGE("Case 7 --> Entry Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);

    bool weight_changed = UWG_change_weight(uwg, &d1, &d2, 9.9f);
    TEST_ASSERT_EQUAL(false, weight_changed);
}

void test_UWG_change_data_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);

    bool data_changed = UWG_change_data(uwg, &d1, &d2);
    TEST_ASSERT_EQUAL(true, data_changed);
}

void test_UWG_change_data_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = NULL;

    bool data_changed = UWG_change_data(uwg, &d1, &d2);
    TEST_ASSERT_EQUAL(false, data_changed);
}

void test_UWG_change_data_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);

    bool data_changed = UWG_change_data(uwg, &d1, &d2);
    TEST_ASSERT_EQUAL(false, data_changed);
}

void test_UWG_change_data_4() {
    TEST_MESSAGE("Case 4 --> Old Data is NullL:");
    TYPE d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);

    bool data_changed = UWG_change_data(uwg, NULL, &d2);
    TEST_ASSERT_EQUAL(false, data_changed);
}

void test_UWG_change_data_5() {
    TEST_MESSAGE("Case 5 --> New Data is Null:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);

    bool data_changed = UWG_change_data(uwg, &d1, NULL);
    TEST_ASSERT_EQUAL(false, data_changed);
}

void test_UWG_get_capacity_1() {
    TEST_MESSAGE("Case 1 --> Non Null Undirected Weighted Graph:");
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    long capacity = UWG_get_capacity(uwg);
    TEST_ASSERT_EQUAL(POSITIVE_MAX_OF_VERTICES, capacity);
}

void test_UWG_get_capacity_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UWG *uwg = NULL;
    long capacity = UWG_get_capacity(uwg);
    TEST_ASSERT_EQUAL(NULL_UWG_CAPACITY, capacity);
}

void test_UWG_get_size_1() {
    TEST_MESSAGE("Case 1 --> Non Null Undirected Weighted Graph:");
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    long size = UWG_get_size(uwg);
    TEST_ASSERT_EQUAL(0, size);
}

void test_UWG_get_size_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UWG *uwg = NULL;
    long size = UWG_get_size(uwg);
    TEST_ASSERT_EQUAL(NULL_UWG_CAPACITY, size);
}

void test_UWG_get_weight_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(1.1f, UWG_get_weight(uwg, &d1, &d2));
    TEST_ASSERT_EQUAL(1.1f, UWG_get_weight(uwg, &d2, &d1));
}

void test_UWG_get_weight_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = NULL;
    TEST_ASSERT_EQUAL(0, UWG_get_weight(uwg, &d1, &d2));
    TEST_ASSERT_EQUAL(0, UWG_get_weight(uwg, &d2, &d1));
}

void test_UWG_get_weight_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    TEST_ASSERT_EQUAL(0, UWG_get_weight(uwg, &d1, &d2));
    TEST_ASSERT_EQUAL(0, UWG_get_weight(uwg, &d2, &d1));
}

void test_UWG_get_weight_4() {
    TEST_MESSAGE("Case 4 --> Null Exit Vertex:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);

    TEST_ASSERT_EQUAL(0, UWG_get_weight(uwg, NULL, &d2));
    TEST_ASSERT_EQUAL(0, UWG_get_weight(uwg, NULL, &d1));
}

void test_UWG_get_weight_5() {
    TEST_MESSAGE("Case 5 --> Null Entry Vertex:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);

    TEST_ASSERT_EQUAL(0, UWG_get_weight(uwg, &d1, NULL));
    TEST_ASSERT_EQUAL(0, UWG_get_weight(uwg, &d2, NULL));
}

void test_UWG_get_weight_6() {
    TEST_MESSAGE("Case 6 --> Exit Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d2);

    TEST_ASSERT_EQUAL(0, UWG_get_weight(uwg, &d1, &d2));
}

void test_UWG_get_weight_7() {
    TEST_MESSAGE("Case 7 --> Entry Vertex not in the Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);

    TEST_ASSERT_EQUAL(0, UWG_get_weight(uwg, &d1, &d2));
}

void test_UWG_get_data_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2, d3;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d3);
    TYPE *data_index_2 = (TYPE *) UWG_get_data(uwg, 2);
    TEST_ASSERT_EQUAL(&d3, data_index_2);
}

void test_UWG_get_data_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    UWG *uwg = NULL;
    TYPE *data_index_2 = (TYPE *) UWG_get_data(uwg, 2);
    TEST_ASSERT_EQUAL(NULL, data_index_2);
}

void test_UWG_get_data_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    TYPE *data_index_2 = (TYPE *) UWG_get_data(uwg, 2);
    TEST_ASSERT_EQUAL(NULL, data_index_2);
}

void test_UWG_get_data_4() {
    TEST_MESSAGE("Case 4 --> Negative index:");
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    TYPE *data = (TYPE *) UWG_get_data(uwg, -1);
    TEST_ASSERT_EQUAL(NULL, data);
}

void test_UWG_get_data_5() {
    TEST_MESSAGE("Case 5 --> Index greater than UWG::Size:");
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    TYPE *data = (TYPE *) UWG_get_data(uwg, 1);
    TEST_ASSERT_EQUAL(NULL, data);
}

void test_UWG_get_valency_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(0, UWG_get_valency(uwg, &d1));
    UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(1, UWG_get_valency(uwg, &d1));
}

void test_UWG_get_valency_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1;
    UWG *uwg = NULL;
    TEST_ASSERT_EQUAL(-1, UWG_get_valency(uwg, &d1));
}

void test_UWG_get_valency_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    TEST_ASSERT_EQUAL(-1, UWG_get_valency(uwg, &d1));
}

void test_UWG_get_valency_4() {
    TEST_MESSAGE("Case 4 --> Null Vertex:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(-1, UWG_get_valency(uwg, NULL));
}

void test_UWG_get_valency_5() {
    TEST_MESSAGE("Case 5 --> Vertex not in Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(-1, UWG_get_valency(uwg, &d2));
}

void test_UWG_remove_edge_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);

    TEST_ASSERT_EQUAL(0, UWG_get_valency(uwg, &d1));

    UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(1, UWG_get_valency(uwg, &d1));

    bool removed = UWG_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_EQUAL(true, removed);
    TEST_ASSERT_EQUAL(0, UWG_get_valency(uwg, &d1));
}

void test_UWG_remove_edge_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = NULL;
    bool removed = UWG_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_UWG_remove_edge_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    bool removed = UWG_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_UWG_remove_edge_4() {
    TEST_MESSAGE("Case 4 --> Null Exit Vertex:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    bool removed = UWG_remove_edge(uwg, NULL, &d2);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_UWG_remove_edge_5() {
    TEST_MESSAGE("Case 4 --> Null Entry Vertex:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    bool removed = UWG_remove_edge(uwg, &d1, NULL);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_UWG_remove_edge_6() {
    TEST_MESSAGE("Case 6 --> Exit Vertex not in Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d2);
    bool removed = UWG_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_UWG_remove_edge_7() {
    TEST_MESSAGE("Case 7 --> Entry Vertex not in Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    bool removed = UWG_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_UWG_remove_vertex_1() {
    TEST_MESSAGE("Case 1 --> All okay:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);

    bool removed = UWG_remove_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(true, removed);
}

void test_UWG_remove_vertex_2() {
    TEST_MESSAGE("Case 2 --> Null Undirected Weighted Graph:");
    TYPE d1;
    UWG *uwg = NULL;
    bool removed = UWG_remove_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_UWG_remove_vertex_3() {
    TEST_MESSAGE("Case 3 --> Empty Undirected Weighted Graph:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    bool removed = UWG_remove_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_UWG_remove_vertex_4() {
    TEST_MESSAGE("Case 4 --> Null Vertex:");
    TYPE d1;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    bool removed = UWG_remove_vertex(uwg, NULL);
    TEST_ASSERT_EQUAL(false, removed);
}

void test_UWG_remove_vertex_5() {
    TEST_MESSAGE("Case 5 --> Vertex not in Undirected Weighted Graph:");
    TYPE d1, d2;
    UWG *uwg = UWG_create(POSITIVE_MAX_OF_VERTICES);
    UWG_insert_vertex(uwg, &d1);
    bool removed = UWG_remove_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(false, removed);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_UWG_create_1);
    RUN_TEST(test_UWG_create_2);
    RUN_TEST(test_UWG_clean_1);
    RUN_TEST(test_UWG_clean_2);
    RUN_TEST(test_UWG_destroy_1);
    RUN_TEST(test_UWG_destroy_2);
    RUN_TEST(test_UWG_index_of_1);
    RUN_TEST(test_UWG_index_of_2);
    RUN_TEST(test_UWG_index_of_3);
    RUN_TEST(test_UWG_index_of_4);
    RUN_TEST(test_UWG_is_empty_1);
    RUN_TEST(test_UWG_is_empty_2);
    RUN_TEST(test_UWG_is_full_1);
    RUN_TEST(test_UWG_is_full_2);
    RUN_TEST(test_UWG_insert_vertex_1);
    RUN_TEST(test_UWG_insert_vertex_2);
    RUN_TEST(test_UWG_insert_vertex_3);
    RUN_TEST(test_UWG_insert_vertex_4);
    RUN_TEST(test_UWG_insert_edge_1);
    RUN_TEST(test_UWG_insert_edge_2);
    RUN_TEST(test_UWG_insert_edge_3);
    RUN_TEST(test_UWG_insert_edge_4);
    RUN_TEST(test_UWG_insert_edge_5);
    RUN_TEST(test_UWG_insert_edge_6);
    RUN_TEST(test_UWG_insert_edge_7);
    RUN_TEST(test_UWG_change_weight_1);
    RUN_TEST(test_UWG_change_weight_2);
    RUN_TEST(test_UWG_change_weight_3);
    RUN_TEST(test_UWG_change_weight_4);
    RUN_TEST(test_UWG_change_weight_5);
    RUN_TEST(test_UWG_change_weight_6);
    RUN_TEST(test_UWG_change_weight_7);
    RUN_TEST(test_UWG_change_data_1);
    RUN_TEST(test_UWG_change_data_2);
    RUN_TEST(test_UWG_change_data_3);
    RUN_TEST(test_UWG_change_data_4);
    RUN_TEST(test_UWG_change_data_5);
    RUN_TEST(test_UWG_get_capacity_1);
    RUN_TEST(test_UWG_get_capacity_2);
    RUN_TEST(test_UWG_get_size_1);
    RUN_TEST(test_UWG_get_size_2);
    RUN_TEST(test_UWG_get_weight_1);
    RUN_TEST(test_UWG_get_weight_2);
    RUN_TEST(test_UWG_get_weight_3);
    RUN_TEST(test_UWG_get_weight_4);
    RUN_TEST(test_UWG_get_weight_5);
    RUN_TEST(test_UWG_get_weight_6);
    RUN_TEST(test_UWG_get_weight_7);
    RUN_TEST(test_UWG_get_data_1);
    RUN_TEST(test_UWG_get_data_2);
    RUN_TEST(test_UWG_get_data_3);
    RUN_TEST(test_UWG_get_data_4);
    RUN_TEST(test_UWG_get_data_5);
    RUN_TEST(test_UWG_get_valency_1);
    RUN_TEST(test_UWG_get_valency_2);
    RUN_TEST(test_UWG_get_valency_3);
    RUN_TEST(test_UWG_get_valency_4);
    RUN_TEST(test_UWG_get_valency_5);
    RUN_TEST(test_UWG_remove_edge_1);
    RUN_TEST(test_UWG_remove_edge_2);
    RUN_TEST(test_UWG_remove_edge_3);
    RUN_TEST(test_UWG_remove_edge_4);
    RUN_TEST(test_UWG_remove_edge_5);
    RUN_TEST(test_UWG_remove_edge_6);
    RUN_TEST(test_UWG_remove_edge_7);
    RUN_TEST(test_UWG_remove_vertex_1);
    RUN_TEST(test_UWG_remove_vertex_2);
    RUN_TEST(test_UWG_remove_vertex_3);
    RUN_TEST(test_UWG_remove_vertex_4);
    RUN_TEST(test_UWG_remove_vertex_5);
    return UNITY_END();
}
