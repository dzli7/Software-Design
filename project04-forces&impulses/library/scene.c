#include "scene.h"

const int guess = 13;

typedef struct scene{
    list_t *bodies;
    size_t size;
    size_t capacity;
    list_t *force_creator_list;
} scene_t;

typedef struct forcer {
    force_creator_t force;
    void *aux;
    free_func_t freer;
} forcer_t;

scene_t *scene_init(void) {
    scene_t *scene = malloc(sizeof(scene_t));
    scene->bodies = list_init(guess, (free_func_t) body_free);
    scene->size = 0;
    scene->capacity = guess;
    scene->force_creator_list = list_init(1, free);

    assert(scene != NULL);
    assert(scene->bodies != NULL);
    return scene;
}

void scene_free(scene_t *scene) {
    for(size_t i = 0; i < list_size(scene->force_creator_list); i++){
        list_t *new_force_creator_list = (list_t *) scene->force_creator_list;
        forcer_t *forcers = list_get(new_force_creator_list, i);
        if(forcers->freer != NULL){
            forcers->freer(forcers->aux);
        }
    }
    list_free(scene->force_creator_list);
    list_free(scene->bodies);
    free(scene);
}


size_t scene_bodies(scene_t *scene) {
    return scene->size;
}

body_t *scene_get_body(scene_t *scene, size_t index) {
    assert(index < scene->size);
    return (body_t *) list_get(scene->bodies, index);
}

void scene_add_body(scene_t *scene, body_t *body) {
    assert(body != NULL);
    if (scene->size >= scene->capacity) {
        scene->bodies = (list_t*) realloc(scene->bodies, scene->capacity * 2 * sizeof(body_t*));
        scene->capacity *= 2;
    }
    list_add(scene->bodies, body);
    scene->size++;
}


void scene_remove_body(scene_t *scene, size_t index) {
    assert(index < scene->size);
    body_free(list_remove(scene->bodies, index));
    scene->size--;
}


void scene_tick(scene_t *scene, double dt) {
    for (size_t i = 0; i < list_size(scene->force_creator_list); i++) {
        forcer_t *force = (forcer_t*) list_get(scene->force_creator_list, i);
        force_creator_t force_creator = force->force;
        force_creator(force->aux);
    }
    for (size_t i = 0; i < scene->size; i++) {
        body_t *body = list_get(scene->bodies, i);
        body_tick(body, dt);
    }
}

forcer_t *forcer_t_init(force_creator_t forcer, void*aux, free_func_t freer) {
    forcer_t *force = malloc(sizeof(forcer_t));
    force->force = forcer;
    force->aux = aux;
    force->freer = freer;
    return force;
}

void scene_add_force_creator(scene_t *scene, force_creator_t forcer, void *aux, free_func_t freer) {
    forcer_t *force = forcer_t_init(forcer, aux, freer);
    list_add(scene->force_creator_list, force);
}
