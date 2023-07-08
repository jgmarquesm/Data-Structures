#include "../../main/include/unity.h"
#include "../../main/include/matrix.h"

void setUp(){}

void tearDown(){}

// define a print function like: void (*type_print_function)(void * data)
// define a conversion function like: type (*type_convert_function)(void * data)
// define a comparison function like: int (*type_compare_function)(void *data1, void *data2)

void test_1() {
    TEST_MESSAGE("Please, write the tests.");
    TEST_ASSERT_EQUAL(1, 0);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_1);
    // ...
    return UNITY_END();
}

