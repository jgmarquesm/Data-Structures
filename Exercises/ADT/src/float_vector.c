#include <stdio.h>
#include "../include/float_vector.h"
#include <stdlib.h>
#include <stdbool.h>

// ******************** "Declaração da "classe" e métodos privados" **********************

// Tudo que é definido somente no arquivo de implementação .c e não for declarado no header (.h),
// Será considerado uma "função privada" disponível somente para uso dentro do arquivo de implementação.
// Um exemplo: Uma função que verifica se o índice está fora range do vetor:

struct _float_vector{
    float *data;
    int capacity;
    int size;
};

bool _float_vector_isOutOfRange(const FloatVector *vec, unsigned int index){
    bool isOutOfRange = index >= vec->size;
    if(isOutOfRange){
        fprintf(stderr, "\nLOG DO ERRO: O index está fora do range.\n");
        return true;
    }
    return false;
}

bool _float_vector_isFull(FloatVector *vec){
    bool isFull = vec->size == vec->capacity;
    if(isFull){
        fprintf(stderr, "\nLOG DO ERRO: O Vetor já está cheio.\n");
        return true;
    }
    return false;
}

// ********************************** Métodos públicas **********************************

FloatVector *float_vector_create(const int capacity){
    FloatVector *floatVector = (FloatVector *) calloc(1, sizeof(FloatVector));
    float *vec = (float *) calloc(capacity, sizeof(float));

    floatVector->data = vec;
    floatVector->capacity = capacity;
    floatVector->size = 0;

    return floatVector;
}

void float_vector_delete(FloatVector **vec_ref){
    free((*vec_ref)->data);
    (*vec_ref)->data = NULL;
    free(*vec_ref);
    *vec_ref = NULL;
}

int float_vector_size(const FloatVector *vec){
    return vec->size;
}

int float_vector_capcaity(const FloatVector *vec) {
    return vec->capacity;
}

float float_vector_at(const FloatVector *vec, const unsigned int index) {
    if(_float_vector_isOutOfRange(vec, index)){
        fprintf(stderr, "ERRO: na função 'float_vector_at'.\n");
        exit(EXIT_FAILURE);
    }
    return vec->data[index];
}

float float_vector_get(const FloatVector *vec, const unsigned int index) {
    return vec->data[index];
}

void float_vector_append(FloatVector *vec, const float num) {
    if(_float_vector_isFull(vec)){
        fprintf(stderr, "ERRO: na função 'float_vector_append'.\n");
        exit(EXIT_FAILURE);
    }
    vec->data[vec->size++] = num;
}

void float_vector_set(FloatVector *vec, const unsigned int index, const float num) {
    if(_float_vector_isOutOfRange(vec, index)){
        fprintf(stderr, "ERRO: na função 'float_vector_set'.\n");
        exit(EXIT_FAILURE);
    }
    vec->data[index] = num;
}

void float_vector_print(const FloatVector *vec){
    for(int i = 0; i < vec->size; i++){
        printf("data: %f\n", vec->data[i]);
    }
}

void float_vector_remove(FloatVector *vec, unsigned int index) {
    for(int i = index; i < vec->size; i++){
        if(i == vec->size-1){
            vec->data[i] = 0;
        } else {
            vec->data[i] = vec->data[i+1];
        }
    }
}

void float_vector_erase(FloatVector *vec) {
    free(vec->data);
    vec->data = (float *) calloc(vec->capacity, sizeof(float));
    vec->size = 0;
}

FloatVector *float_vector_clone(FloatVector *vec) {
    FloatVector *clone = (FloatVector *) calloc(1, sizeof(FloatVector));
    clone->data = vec->data;
    clone->capacity = vec->capacity;
    clone->size = vec->size;
    return clone;
}
