#include "../include/float_vector.h"

int main(){

    FloatVector *vec = float_vector_create(3);
    float_vector_append(vec, 1);
    float_vector_append(vec, 2);
    float_vector_append(vec, 3);
    float_vector_print(vec);
    float_vector_set(vec, 1, 200);
    float_vector_print(vec);
    float_vector_append(vec, 4);

    return 0;
}