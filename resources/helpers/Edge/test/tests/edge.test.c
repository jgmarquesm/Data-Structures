#include "../../main/include/unity.h"
#include "../../main/include/edge.h"

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

