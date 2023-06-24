#ifndef FLOAT_VECTOR_H // Evita múltiplos includes
#define FLOAT_VECTOR_H

typedef struct _float_vector FloatVector;

FloatVector *float_vector_create(int capacity);
void float_vector_delete(FloatVector **vec_ref);
int float_vector_size(const FloatVector *vec);
int float_vector_capcaity(const FloatVector *vec);
float float_vector_at(const FloatVector *vec, unsigned int index);
float float_vector_get(const FloatVector *vec, unsigned int index);
void float_vector_append(FloatVector *vec, float num);
void float_vector_set(FloatVector *vec, unsigned int index, float num);
void float_vector_print(const FloatVector *vec);
void float_vector_remove(FloatVector *vec, unsigned int index);
void float_vector_erase(FloatVector *vec);
FloatVector *float_vector_clone(FloatVector *vec);

#endif //FLOAT_VECTOR_H
