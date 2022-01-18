#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "body.h"

typedef struct body {
    list_t *shape;
    rgb_color_t color;
    double mass;
    vector_t velocity;
    vector_t centroid;
    double angle;
    double rotation;
} body_t;

body_t *body_init(list_t *shape, double mass, rgb_color_t color, double rotation) {
    body_t *body = malloc(sizeof(body_t));
    body->shape = shape;
    body->color = color;
    body->mass = mass;
    body->velocity = VEC_ZERO;
    body->centroid = polygon_centroid(shape);
    body->angle = 0;
    body->rotation = rotation;
    return body;
}

void body_free(body_t *body){
    list_free(body->shape);
    free(body);
}

list_t *body_get_shape(body_t *body) {
    list_t *new_list = list_init(list_size(body->shape), (free_func_t) free);
    for (size_t i = 0; i < list_size(body->shape); i++) {
        vector_t *v = malloc(sizeof(vector_t));
        *v = *(vector_t *)list_get(body->shape, i);
        list_add(new_list, v);
    }
    return new_list;
}

vector_t body_get_centroid(body_t *body) {
    return body->centroid;
}

vector_t body_get_velocity(body_t *body) {
    return body->velocity;
}

rgb_color_t body_get_color(body_t *body) {
    return body->color;
}

double body_get_mass(body_t *body) {
    return body->mass;
}

void body_set_centroid(body_t *body, vector_t x) {
    vector_t old_centroid = body->centroid;
    body->centroid = x;
    list_t *shape = body->shape;
    polygon_translate(shape, vec_subtract(x, old_centroid));
}

void body_set_velocity(body_t * body, vector_t velocity) {
    body->velocity = velocity;
}

void body_set_rotation(body_t *body, double angle) {
    list_t *shape = body->shape;
    double rotation = body->angle - angle;
    polygon_rotate(shape, rotation, body->centroid);
    body->angle = angle;
}

void body_set_mass(body_t *body, double mass) {
    body->mass = mass;
}

void body_tick(body_t *body, double dt) {
    list_t *shape = body->shape;
    vector_t velocity = body->velocity;
    polygon_translate(shape, vec_multiply(dt, velocity));
    polygon_rotate(shape, body->rotation * dt, body->centroid);
    body->centroid = vec_add(body_get_centroid(body), vec_multiply(dt, velocity));
}