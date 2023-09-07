#include "../../main/include/unity.h"
#include "../../main/include/undirected_weighted_graph.h"

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

void setUp(){}

void tearDown(){}

void test_1() {
    TEST_MESSAGE("Please, write the tests.");
    TEST_ASSERT_EQUAL(1, 1);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_1);
    // ...
    return UNITY_END();
}

