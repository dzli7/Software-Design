#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "forces.h"

typedef struct aux {
    body_t *body1;
    body_t *body2;
    double c;
} aux_t;

aux_t *aux_init(body_t *body1, body_t *body2, double c) {
    aux_t *aux = malloc(sizeof(aux_t));
    aux->body1 = body1;
    aux->body2 = body2;
    aux->c = c;
    return aux;
}
void force_creator_spring(void *aux) {
    aux_t *a = (aux_t*) aux;
    body_t *body1 = a->body1;
    body_t *body2 = a->body2;
    double c = a->c;
    vector_t displacement = vec_subtract(body_get_centroid(body1) , body_get_centroid(body2));
    double distance = vec_magnitude(displacement);
    double F = c * distance;
    vector_t direction = vec_multiply(1/distance, displacement);
    body_add_force(body1, vec_multiply(-F, direction));
    body_add_force(body2, vec_multiply(F, direction));
}

void force_creator_drag(void *aux) {
    aux_t *a = (aux_t*) aux;
    body_t *body = a->body1;
    double c = a->c;
    vector_t velocity = body_get_velocity(body);
    body_add_force(body, vec_multiply(-c, velocity));
}

void force_creator_destructive_collision(void *aux) {
    aux_t *a = (aux_t*) aux;
    body_t *body1 = a->body1;
    body_t *body2 = a->body2;
    if (find_collision(body_get_shape(body1), body_get_shape(body2))) {
        body_remove(body1);
        body_remove(body2);
    }
}

void force_creator_gravity(void *aux) {
    aux_t *a = (aux_t*) aux;
    body_t *body1 = a->body1;
    body_t *body2 = a->body2;
    double c = a->c;

    vector_t displacement = vec_subtract(body_get_centroid(body1) , body_get_centroid(body2));
    double distance = vec_magnitude(displacement);
    if (distance < 2) { distance = 2; } 
    double F = c * body_get_mass(body1) * body_get_mass(body2) / pow(distance, 2);
    vector_t direction = vec_multiply(1/distance, displacement);
    body_add_force(body1, vec_multiply(-F, direction));
    body_add_force(body2, vec_multiply(F, direction));
}

void create_newtonian_gravity(scene_t *scene, double G, body_t *body1, body_t *body2) {
    aux_t *aux = aux_init(body1, body2, G);
    list_t *bodies = list_init(2, (free_func_t) free);
    list_add(bodies, body1);
    list_add(bodies, body2);
    scene_add_bodies_force_creator(scene, force_creator_gravity, aux, bodies, NULL);
}

void create_spring(scene_t *scene, double k, body_t *body1, body_t *body2) {
    aux_t *aux = aux_init(body1, body2, k);
    list_t *bodies = list_init(2, (free_func_t) free);
    list_add(bodies, body1);
    list_add(bodies, body2);
    scene_add_bodies_force_creator(scene, force_creator_spring, aux, bodies, NULL);
}

void create_drag(scene_t *scene, double gamma, body_t *body) {
    aux_t *aux = aux_init(body, NULL, gamma);
    list_t *bodies = list_init(2, (free_func_t) free);
    list_add(bodies, body);
    scene_add_bodies_force_creator(scene, force_creator_drag, aux, bodies, NULL);
}

void create_destructive_collision(scene_t *scene, body_t *body1, body_t *body2) {
    aux_t *aux = aux_init(body1, body2, 0);
    list_t *bodies = list_init(2, (free_func_t) free);
    list_add(bodies, body1);
    list_add(bodies, body2);
    scene_add_bodies_force_creator(scene, force_creator_destructive_collision, aux, bodies, NULL);
}

