#include "../../main/include/unity.h"
#include "../../main/include/vertex.h"

#define TYPE char
#define INITIAL_VALENCY 0
#define VALENCY_42 42
#define VALENCY_99 99
#define VALENCY_0 INITIAL_VALENCY
#define NON_VALID_VALENCY -1
#define VALENCY_NEGATIVE_1 NON_VALID_VALENCY

void setUp(){}

void tearDown(){}

void test_Vertex_create_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Data:");
    TYPE d1;
    Vertex *vertex = NULL;

    TEST_ASSERT_EQUAL(NULL, vertex);

    vertex = Vertex_create(&d1);
    TEST_ASSERT_NOT_EQUAL(NULL, vertex);

    TYPE *got = Vertex_get_data(vertex);
    TEST_ASSERT_EQUAL(&d1, got);

    long valency_ = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(INITIAL_VALENCY, valency_);
}

void test_Vertex_create_2() {
    TEST_MESSAGE("Case 2 --> NULL Data:");
    Vertex *vertex = NULL;
    TEST_ASSERT_EQUAL(NULL, vertex);

    vertex = Vertex_create(NULL);
    TEST_ASSERT_EQUAL(NULL, vertex);
}

void test_Vertex_destroy_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Vertex:");
    TYPE d1;
    Vertex *vertex = Vertex_create(&d1);
    TEST_ASSERT_NOT_NULL(vertex);

    bool destroyed = Vertex_destroy(&vertex);
    TEST_ASSERT_TRUE(destroyed);
    TEST_ASSERT_NULL(vertex);
}

void test_Vertex_destroy_2() {
    TEST_MESSAGE("Case 2 --> NULL Vertex:");
    Vertex *vertex = NULL;
    TEST_ASSERT_NULL(vertex);

    bool destroyed = Vertex_destroy(&vertex);
    TEST_ASSERT_FALSE(destroyed);
}

void test_Vertex_data_getter_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Vertex:");
    TYPE d1;
    Vertex *vertex = Vertex_create(&d1);

    void *got = Vertex_get_data(vertex);
    TEST_ASSERT_EQUAL(&d1, got);
}

void test_Vertex_data_getter_2() {
    TEST_MESSAGE("Case 2 --> NULL Vertex:");
    Vertex *vertex = NULL;

    void *got = Vertex_get_data(vertex);
    TEST_ASSERT_NULL(got);
}

void test_Vertex_data_setter_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Vertex and Non NULL New Data:");
    TYPE d1, d2;
    Vertex *vertex = Vertex_create(&d1);

    bool set = Vertex_set_data(vertex, &d2);
    TEST_ASSERT_TRUE(set);

    void *got = Vertex_get_data(vertex);
    TEST_ASSERT_EQUAL(&d2, got);
}

void test_Vertex_data_setter_2() {
    TEST_MESSAGE("Case 2 --> NULL Vertex:");
    TYPE d1;
    Vertex *vertex = NULL;

    bool set = Vertex_set_data(vertex, &d1);
    TEST_ASSERT_FALSE(set);

    void *got = Vertex_get_data(vertex);
    TEST_ASSERT_NULL(got);
}

void test_Vertex_data_setter_3() {
    TEST_MESSAGE("Case 3 --> NULL New Data:");
    TYPE d1;
    Vertex *vertex = Vertex_create(&d1);

    bool set = Vertex_set_data(vertex, NULL);
    TEST_ASSERT_FALSE(set);

    void *got = Vertex_get_data(vertex);
    TEST_ASSERT_EQUAL(&d1, got);
}

void test_Vertex_valency_getter_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Vertex:");
    TYPE d1;
    Vertex *vertex = Vertex_create(&d1);

    long valency = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(INITIAL_VALENCY, valency);
}

void test_Vertex_valency_getter_2() {
    TEST_MESSAGE("Case 2 --> NULL Vertex:");
    Vertex *vertex = NULL;

    long valency = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(NON_VALID_VALENCY, valency);
}

void test_Vertex_valency_setter_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Vertex and Positive Valency:");
    TYPE d1;
    Vertex *vertex = Vertex_create(&d1);

    long set = Vertex_set_valency(vertex, VALENCY_99);
    long positive_valency = Vertex_get_valency(vertex);

    TEST_ASSERT_EQUAL(VALENCY_99, set);
    TEST_ASSERT_NOT_EQUAL(INITIAL_VALENCY, positive_valency);
    TEST_ASSERT_EQUAL(VALENCY_99, positive_valency);
}

void test_Vertex_valency_setter_2() {
    TEST_MESSAGE("Case 2 --> NULL Vertex:");
    Vertex *vertex = NULL;

    long set = Vertex_set_valency(vertex, VALENCY_99);
    TEST_ASSERT_EQUAL(NON_VALID_VALENCY, set);
}

void test_Vertex_valency_setter_3() {
    TEST_MESSAGE("Case 3 --> Valency == 0:");
    TYPE d1;
    Vertex *vertex = Vertex_create(&d1);
    Vertex_set_valency(vertex, VALENCY_99);

    long set = Vertex_set_valency(vertex, VALENCY_0);
    long valency_zero = Vertex_get_valency(vertex);

    TEST_ASSERT_EQUAL(VALENCY_0, set);
    TEST_ASSERT_NOT_EQUAL(VALENCY_99, valency_zero);
    TEST_ASSERT_EQUAL(VALENCY_0, valency_zero);
}

void test_Vertex_valency_setter_4() {
    TEST_MESSAGE("Case 4 --> Negative Valency:");
    TYPE d1;
    Vertex *vertex = Vertex_create(&d1);

    long set = Vertex_set_valency(vertex, VALENCY_NEGATIVE_1);
    long try_negative_valency = Vertex_get_valency(vertex);

    TEST_ASSERT_EQUAL(NON_VALID_VALENCY, set);
    TEST_ASSERT_NOT_EQUAL(VALENCY_NEGATIVE_1, try_negative_valency);
    TEST_ASSERT_EQUAL(INITIAL_VALENCY, try_negative_valency);
}

void test_Vertex_valency_up_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Vertex:");
    TYPE d1;
    Vertex *vertex = Vertex_create(&d1);
    long initial_valency = Vertex_get_valency(vertex), valency1, valency100, valency43;
    bool valency_upped;

    TEST_ASSERT_EQUAL(INITIAL_VALENCY, initial_valency);

    valency_upped = Vertex_valency_up(vertex);
    TEST_ASSERT_TRUE(valency_upped);

    valency1 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(INITIAL_VALENCY+1, valency1);

    Vertex_set_valency(vertex, VALENCY_99);

    valency_upped = Vertex_valency_up(vertex);
    TEST_ASSERT_TRUE(valency_upped);

    valency100 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(VALENCY_99+1, valency100);

    Vertex_set_valency(vertex, VALENCY_42);

    valency_upped = Vertex_valency_up(vertex);
    TEST_ASSERT_TRUE(valency_upped);

    valency43 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(VALENCY_42+1, valency43);
}

void test_Vertex_valency_up_2() {
    TEST_MESSAGE("Case 2 --> NULL Vertex:");
    Vertex *vertex = NULL;

    bool valency_upped = Vertex_valency_up(vertex);
    TEST_ASSERT_FALSE(valency_upped);
}

void test_Vertex_valency_down_1() {
    TEST_MESSAGE("Case 1 --> Non NULL Vertex and Vertex::Valency > 0:");
    TYPE d1;
    Vertex *vertex = Vertex_create(&d1);
    long initial_valency = Vertex_get_valency(vertex), valency98;

    TEST_ASSERT_EQUAL(INITIAL_VALENCY, initial_valency);
    Vertex_set_valency(vertex, VALENCY_99);

    bool valency_downed = Vertex_valency_down(vertex);
    TEST_ASSERT_TRUE(valency_downed);

    valency98 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(VALENCY_99-1, valency98);
}

void test_Vertex_valency_down_2() {
    TEST_MESSAGE("Case 2 --> NULL Vertex:");
    Vertex *vertex = NULL;
    long initial_valency = Vertex_get_valency(vertex);

    TEST_ASSERT_EQUAL(NON_VALID_VALENCY, initial_valency);
    Vertex_set_valency(vertex, VALENCY_99);

    bool valency_downed = Vertex_valency_down(vertex);
    TEST_ASSERT_FALSE(valency_downed);
}

void test_Vertex_valency_down_3() {
    TEST_MESSAGE("Case 3 --> Vertex::Valency == 0:");
    TYPE d1;
    Vertex *vertex = Vertex_create(&d1);
    long initial_valency = Vertex_get_valency(vertex), valency0;

    TEST_ASSERT_EQUAL(INITIAL_VALENCY, initial_valency);

    bool valency_downed = Vertex_valency_down(vertex);
    TEST_ASSERT_FALSE(valency_downed);

    valency0 = Vertex_get_valency(vertex);
    TEST_ASSERT_EQUAL(initial_valency, valency0);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_Vertex_create_1);
    RUN_TEST(test_Vertex_create_2);
    RUN_TEST(test_Vertex_destroy_1);
    RUN_TEST(test_Vertex_destroy_2);
    RUN_TEST(test_Vertex_data_getter_1);
    RUN_TEST(test_Vertex_data_getter_2);
    RUN_TEST(test_Vertex_data_setter_1);
    RUN_TEST(test_Vertex_data_setter_2);
    RUN_TEST(test_Vertex_data_setter_3);
    RUN_TEST(test_Vertex_valency_getter_1);
    RUN_TEST(test_Vertex_valency_getter_2);
    RUN_TEST(test_Vertex_valency_setter_1);
    RUN_TEST(test_Vertex_valency_setter_2);
    RUN_TEST(test_Vertex_valency_setter_3);
    RUN_TEST(test_Vertex_valency_setter_4);
    RUN_TEST(test_Vertex_valency_up_1);
    RUN_TEST(test_Vertex_valency_up_2);
    RUN_TEST(test_Vertex_valency_down_1);
    RUN_TEST(test_Vertex_valency_down_2);
    RUN_TEST(test_Vertex_valency_down_3);
    return UNITY_END();
}

