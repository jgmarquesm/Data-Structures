#include "../../main/include/unity.h"
#include "../../main/include/vertex.h"

#define TYPE char
#define INITIAL_VALENCY 0
#define VALENCY_42 42
#define VALENCY_99 99
#define VALENCY_0 INITIAL_VALENCY
#define VALENCY_NEGATIVE_1 -1

void setUp(){}

void tearDown(){}

void test_Vertex_create() {
    Vertex *vertex = NULL;
    TYPE d;

    TEST_ASSERT_EQUAL(NULL, vertex);

    vertex = Vertex_create(&d);
    TEST_ASSERT_NOT_EQUAL(NULL, vertex);

    TYPE *data_ = Vertex_get_data(vertex);
    TEST_ASSERT_EQUAL(&d, data_);
    TEST_ASSERT_EQUAL(d, *data_);

    long valency_ = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(INITIAL_VALENCY, valency_);
}

void test_Vertex_destroy() {
    TYPE d;
    Vertex *vertex = Vertex_create(&d);

    Vertex_destroy(&vertex);
    TEST_ASSERT_EQUAL(NULL, vertex);
}

void test_Vertex_data_getter() {
    TYPE d;
    Vertex *vertex = Vertex_create(&d);

    TYPE *data_ = Vertex_get_data(vertex);
    TEST_ASSERT_EQUAL(&d, data_);
    TEST_ASSERT_EQUAL(d, *data_);
}

void test_Vertex_data_setter() {
    TYPE d1, d2;
    Vertex *vertex = Vertex_create(&d1);

    Vertex_set_data(vertex, &d2);
    TYPE *data_ = Vertex_get_data(vertex);
    TEST_ASSERT_EQUAL(&d2, data_);
    TEST_ASSERT_EQUAL(d2, *data_);
}

void test_Vertex_valency_getter() {
    TYPE d;
    Vertex *vertex = Vertex_create(&d);

    long valency = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(INITIAL_VALENCY, valency);
}

void test_Vertex_valency_setter() {
    TYPE d;
    Vertex *vertex = Vertex_create(&d);

    long last_valid_valency = INITIAL_VALENCY;
    Vertex_set_valency(vertex, VALENCY_99);
    long positive_valency = Vertex_get_valency(vertex);

    TEST_ASSERT_NOT_EQUAL(last_valid_valency, positive_valency);
    TEST_ASSERT_EQUAL(VALENCY_99, positive_valency);

    last_valid_valency = positive_valency;
    Vertex_set_valency(vertex, VALENCY_0);
    long valency_zero = Vertex_get_valency(vertex);

    TEST_ASSERT_NOT_EQUAL(last_valid_valency, valency_zero);
    TEST_ASSERT_EQUAL(VALENCY_0, valency_zero);

    last_valid_valency = valency_zero;
    Vertex_set_valency(vertex, VALENCY_NEGATIVE_1);
    long try_negative_valency = Vertex_get_valency(vertex);

    TEST_ASSERT_NOT_EQUAL(VALENCY_NEGATIVE_1, try_negative_valency);
    TEST_ASSERT_EQUAL(last_valid_valency, try_negative_valency);
}

void test_Vertex_valency_up() {
    TYPE d;
    Vertex *vertex = Vertex_create(&d);
    long initial_valency = Vertex_get_valency(vertex), valency1, valency100, valency43;

    TEST_ASSERT_EQUAL(INITIAL_VALENCY, initial_valency);

    Vertex_valency_up(vertex);
    valency1 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(INITIAL_VALENCY+1, valency1);

    Vertex_set_valency(vertex, VALENCY_99);
    Vertex_valency_up(vertex);
    valency100 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(VALENCY_99+1, valency100);

    Vertex_set_valency(vertex, VALENCY_42);
    Vertex_valency_up(vertex);
    valency43 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(VALENCY_42+1, valency43);
}

void test_Vertex_valency_down() {
    TYPE d;
    Vertex *vertex = Vertex_create(&d);
    long initial_valency = Vertex_get_valency(vertex), valency0, valency98, valency41;

    TEST_ASSERT_EQUAL(INITIAL_VALENCY, initial_valency);

    Vertex_valency_down(vertex);
    valency0 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(initial_valency, valency0);

    Vertex_set_valency(vertex, VALENCY_99);
    Vertex_valency_down(vertex);
    valency98 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(VALENCY_99-1, valency98);

    Vertex_set_valency(vertex, VALENCY_42);
    Vertex_valency_down(vertex);
    valency41 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(VALENCY_42-1, valency41);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_Vertex_create);
    RUN_TEST(test_Vertex_destroy);
    RUN_TEST(test_Vertex_data_getter);
    RUN_TEST(test_Vertex_data_setter);
    RUN_TEST(test_Vertex_valency_getter);
    RUN_TEST(test_Vertex_valency_setter);
    RUN_TEST(test_Vertex_valency_up);
    RUN_TEST(test_Vertex_valency_down);
    // ...
    return UNITY_END();
}

