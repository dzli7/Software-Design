#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct vector {
    double x;
    double y;
} vector_t;

vector_t *vec_init(double x, double y) {
    vector_t *vec = malloc(sizeof(vector_t));
    vec->x = x;
    vec->y = y;
    return vec;
}

void vec_free(vector_t *vec) {
    free(vec);
}

vector_t *vec_add(vector_t *v1, vector_t *v2) {
    vector_t *vec = malloc(sizeof(vector_t));
    vec->x = v1->x + v2->x;
    vec->y = v1->y + v2->y;
    return vec;
}

double get_x(vector_t *v) {
    return  v->x;
}

double get_y(vector_t *v) {
    return v->y;
}