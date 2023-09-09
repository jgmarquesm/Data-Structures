#include "../../main/include/unity.h"
#include "../../main/include/undirected_weighted_graph.h"
#include <stdio.h>

#define TYPE int
#define MAX 5

void setUp(){}

void tearDown(){}

void test_UWG_create() {
    UWG *uwg = NULL;
    TEST_ASSERT_EQUAL(NULL, uwg);

    uwg = UWG_create(MAX);
    TEST_ASSERT_NOT_EQUAL(NULL, uwg);

    long capacity = UWG_get_capacity(uwg);
    TEST_ASSERT_EQUAL(MAX, capacity);

    long size = UWG_get_size(uwg);
    TEST_ASSERT_EQUAL(0, size);
}

void test_UWG_clean() {
    TYPE d1, d2, d3, d4, d5;
    UWG *uwg = UWG_create(MAX);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d3);
    UWG_insert_vertex(uwg, &d4);
    UWG_insert_vertex(uwg, &d5);
    TEST_ASSERT_EQUAL(5, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(1, UWG_is_full(uwg));

    UWG_clean(uwg);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(0, UWG_is_full(uwg));
    TEST_ASSERT_EQUAL(1, UWG_is_empty(uwg));
}

void test_UWG_destroy() {
    UWG *uwg = NULL;
    TEST_ASSERT_EQUAL(NULL, uwg);

    uwg = UWG_create(MAX);
    TEST_ASSERT_NOT_EQUAL(NULL, uwg);

    UWG_destroy(&uwg);
    TEST_ASSERT_EQUAL(NULL, uwg);
}

void test_UWG_index_of() {
    TYPE d1, d2, d3, d4, d5;
    UWG *uwg = UWG_create(MAX);

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

void test_UWG_is_empty() {
    TYPE d;
    UWG *uwg = UWG_create(MAX);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(1, UWG_is_empty(uwg));

    UWG_insert_vertex(uwg, &d);
    TEST_ASSERT_EQUAL(1, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(0, UWG_is_empty(uwg));

    UWG_remove_vertex(uwg, &d);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(1, UWG_is_empty(uwg));
}

void test_UWG_is_full() {
    TYPE d1, d2, d3, d4, d5;
    UWG *uwg = UWG_create(MAX);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(0, UWG_is_full(uwg));

    UWG_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(1, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(0, UWG_is_full(uwg));
    UWG_insert_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(2, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(0, UWG_is_full(uwg));
    UWG_insert_vertex(uwg, &d3);
    TEST_ASSERT_EQUAL(3, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(0, UWG_is_full(uwg));
    UWG_insert_vertex(uwg, &d4);
    TEST_ASSERT_EQUAL(4, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(0, UWG_is_full(uwg));
    UWG_insert_vertex(uwg, &d5);
    TEST_ASSERT_EQUAL(5, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(1, UWG_is_full(uwg));

    UWG_remove_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(4, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(0, UWG_is_full(uwg));
}

void test_UWG_insert_vertex() {
    TYPE d;
    UWG *uwg = UWG_create(MAX);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));

    UWG_insert_vertex(uwg, &d);
    TEST_ASSERT_EQUAL(1, UWG_get_size(uwg));
}

void test_UWG_insert_edge() {
    TYPE d1, d2;
    UWG *uwg = UWG_create(MAX);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(0, UWG_get_valency(uwg, &d1));
    TEST_ASSERT_EQUAL(0, UWG_get_valency(uwg, &d2));
    UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(1, UWG_get_valency(uwg, &d1));
    TEST_ASSERT_EQUAL(1, UWG_get_valency(uwg, &d2));
}

void test_UWG_change_weight() {
    TYPE d1, d2, d3;
    UWG *uwg = UWG_create(MAX);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d3);
    UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    UWG_insert_edge(uwg, &d1, &d3, 1.2f);
    TEST_ASSERT_EQUAL(1.1f, UWG_get_weight(uwg, &d1, &d2));
    TEST_ASSERT_EQUAL(1.2f, UWG_get_weight(uwg, &d1, &d3));
    TEST_ASSERT_EQUAL(0.0f, UWG_get_weight(uwg, &d2, &d3));

    UWG_change_weight(uwg, &d1, &d2, 0.9f);
    UWG_change_weight(uwg, &d1, &d3, 1.5f);
    UWG_change_weight(uwg, &d2, &d3, 1.1f);

    TEST_ASSERT_EQUAL(0.9f, UWG_get_weight(uwg, &d1, &d2));
    TEST_ASSERT_EQUAL(1.5f, UWG_get_weight(uwg, &d1, &d3));
    TEST_ASSERT_EQUAL(0.0f, UWG_get_weight(uwg, &d2, &d3));
}

void test_UWG_change_data() {
    TYPE d1, d2;
    UWG *uwg = UWG_create(MAX);
    UWG_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(&d1, (TYPE *) UWG_get_data(uwg, 0));
    UWG_change_data(uwg, &d1, &d2);
    TEST_ASSERT_NOT_EQUAL(&d1, (TYPE *) UWG_get_data(uwg, 0));
    TEST_ASSERT_EQUAL(&d2, (TYPE *) UWG_get_data(uwg, 0));
}

void test_UWG_get_capacity() {
    UWG *uwg1 = UWG_create(MAX);
    UWG *uwg2 = UWG_create(MAX+1);
    TEST_ASSERT_EQUAL(MAX, UWG_get_capacity(uwg1));
    TEST_ASSERT_NOT_EQUAL(MAX-1, UWG_get_capacity(uwg2));
    TEST_ASSERT_NOT_EQUAL(MAX, UWG_get_capacity(uwg2));
    TEST_ASSERT_EQUAL(MAX+1, UWG_get_capacity(uwg2));
}

void test_UWG_get_size() {
    TYPE d1, d2, d3, d4, d5;
    UWG *uwg = UWG_create(MAX);

    UWG_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(1, UWG_get_size(uwg));

    UWG_insert_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(2, UWG_get_size(uwg));

    UWG_insert_vertex(uwg, &d3);
    TEST_ASSERT_EQUAL(3, UWG_get_size(uwg));

    UWG_insert_vertex(uwg, &d4);
    TEST_ASSERT_EQUAL(4, UWG_get_size(uwg));

    UWG_insert_vertex(uwg, &d5);
    TEST_ASSERT_EQUAL(5, UWG_get_size(uwg));

    UWG_remove_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(4, UWG_get_size(uwg));

    UWG_clean(uwg);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));
    TEST_ASSERT_EQUAL(1, UWG_is_empty(uwg));
}

void test_UWG_get_weight() {
    TYPE d1, d2, d3;
    UWG *uwg = UWG_create(MAX);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d3);
    UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    UWG_insert_edge(uwg, &d1, &d3, 1.2f);
    TEST_ASSERT_EQUAL(1.1f, UWG_get_weight(uwg, &d1, &d2));
    TEST_ASSERT_EQUAL(1.1f, UWG_get_weight(uwg, &d2, &d1));
    TEST_ASSERT_EQUAL(1.2f, UWG_get_weight(uwg, &d1, &d3));
    TEST_ASSERT_EQUAL(1.2f, UWG_get_weight(uwg, &d3, &d1));
    TEST_ASSERT_EQUAL(0.0f, UWG_get_weight(uwg, &d2, &d3));
}

void test_UWG_get_data() {
    TYPE d1, d2, d3;
    UWG *uwg = UWG_create(MAX);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d3);
    TEST_ASSERT_EQUAL(&d1, (TYPE *) UWG_get_data(uwg, 0));
    TEST_ASSERT_EQUAL(&d2, (TYPE *) UWG_get_data(uwg, 1));
    TEST_ASSERT_EQUAL(&d3, (TYPE *) UWG_get_data(uwg, 2));
}

void test_UWG_get_valency() {
    TYPE d1, d2, d3;
    UWG *uwg = UWG_create(MAX);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d3);
    TEST_ASSERT_EQUAL(0, UWG_get_valency(uwg, &d1));
    UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(1, UWG_get_valency(uwg, &d1));
    UWG_insert_edge(uwg, &d1, &d3, 1.2f);
    TEST_ASSERT_EQUAL(2, UWG_get_valency(uwg, &d1));
}

void test_UWG_remove_edge() {
    TYPE d1, d2, d3;
    UWG *uwg = UWG_create(MAX);
    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d3);
    TEST_ASSERT_EQUAL(0, UWG_get_valency(uwg, &d1));
    UWG_insert_edge(uwg, &d1, &d2, 1.1f);
    TEST_ASSERT_EQUAL(1, UWG_get_valency(uwg, &d1));
    UWG_insert_edge(uwg, &d1, &d3, 1.2f);
    TEST_ASSERT_EQUAL(2, UWG_get_valency(uwg, &d1));
    UWG_remove_edge(uwg, &d1, &d2);
    TEST_ASSERT_EQUAL(1, UWG_get_valency(uwg, &d1));
    UWG_remove_edge(uwg, &d1, &d3);
    TEST_ASSERT_EQUAL(0, UWG_get_valency(uwg, &d1));
}

void test_UWG_remove_vertex() {
    TYPE d1, d2, d3, d4, d5;
    UWG *uwg = UWG_create(MAX);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));

    UWG_insert_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(1, UWG_get_size(uwg));

    UWG_remove_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(0, UWG_get_size(uwg));

    UWG_insert_vertex(uwg, &d1);
    UWG_insert_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(2, UWG_get_size(uwg));

    UWG_remove_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(1, UWG_get_size(uwg));

    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d3);
    TEST_ASSERT_EQUAL(3, UWG_get_size(uwg));

    UWG_remove_vertex(uwg, &d2);
    TEST_ASSERT_EQUAL(2, UWG_get_size(uwg));

    UWG_insert_vertex(uwg, &d2);
    UWG_insert_vertex(uwg, &d4);
    UWG_insert_vertex(uwg, &d5);
    TEST_ASSERT_EQUAL(5, UWG_get_size(uwg));

    UWG_remove_vertex(uwg, &d1);
    TEST_ASSERT_EQUAL(4, UWG_get_size(uwg));
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_UWG_create);
    RUN_TEST(test_UWG_clean);
    RUN_TEST(test_UWG_destroy);
    RUN_TEST(test_UWG_index_of);
    RUN_TEST(test_UWG_is_empty);
    RUN_TEST(test_UWG_is_full);
    RUN_TEST(test_UWG_insert_vertex);
    RUN_TEST(test_UWG_insert_edge);
    RUN_TEST(test_UWG_change_weight);
    RUN_TEST(test_UWG_change_data);
    RUN_TEST(test_UWG_get_capacity);
    RUN_TEST(test_UWG_get_size);
    RUN_TEST(test_UWG_get_weight);
    RUN_TEST(test_UWG_get_data);
    RUN_TEST(test_UWG_get_valency);
    RUN_TEST(test_UWG_remove_edge);
    RUN_TEST(test_UWG_remove_vertex);
    return UNITY_END();
}

