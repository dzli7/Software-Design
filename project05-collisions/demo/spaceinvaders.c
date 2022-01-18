#include "sdl_wrapper.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"
#include "body.h"
#include "forces.h"
#include "polygon.h"
#include "SDL2/SDL.h"

#define WINDOW_TITLE "CS 3"
#define CIRC_NPOINTS 1000
 
const size_t WINDOW_WIDTH_ = 1000;
const size_t WINDOW_HEIGHT_ = 500;
const vector_t MIN_POINT = {0, 0};
const vector_t MAX_POINT = {WINDOW_WIDTH_, WINDOW_HEIGHT_};
const vector_t INVADER_SPAWN = {500, 250};
const vector_t FIGHTER_SPAWN = {500, 10};
const vector_t RIGHT_VELOCITY = {500, 0};
const vector_t LEFT_VELOCITY = {-500, 0};
const int INVADER_RADIUS = 40;
const int ROWS = 3;
const int COLS = 7;
const int TOTAL_INVADERS = ROWS * COLS;
const int PELLET_RADIUS = 10;
const double INITIAL_INVADER_MASS = 1;
const double CIRCLE_MASS = 1;
const rgb_color_t INVADER_COLOR = {0, 0, 0};
const rgb_color_t FIGHTER_COLOR = {1, 1, 0};
const rgb_color_t BULLET_COLOR = {0, 1, 0};
const double THETA = 4*M_PI / 3;
const double SPAWN_RATE = 3;
const double ACCELERATION = 300;
const size_t INITIAL_PELLETS = 10;
const double BULLET_MASS = 1;
const double BULLET_VELOCITY = 200;
const double SHOOT_RATE = 1.5;
const double LENGTH = 1;
const double HEIGHT = 4;
const double SPACE_BETWEEN = 10;
const double INVADER_VEL = 70;


body_t *make_invaders() {
    list_t *shape = list_init(CIRC_NPOINTS + 1, (free_func_t) free);
    for (size_t i = 0; i < CIRC_NPOINTS; i++) {
        double angle = THETA + 2 * (M_PI - THETA) * i / CIRC_NPOINTS;
        vector_t *v = malloc(sizeof(*v));
        *v = (vector_t) {INVADER_RADIUS * sin(angle), INVADER_RADIUS * cos(angle)};
        *v = vec_add(*v, INVADER_SPAWN);
        list_add(shape, v);
    }
    vector_t *SPAWN = malloc(sizeof(vector_t));
    *SPAWN = INVADER_SPAWN;
    list_add(shape, SPAWN);
    body_t *bod = body_init(shape, INITIAL_INVADER_MASS, INVADER_COLOR);
    body_set_rotation(bod, M_PI);
    return bod;
}

list_t *make_rectangle(){
    list_t *rectangle = list_init(4, free);
    vector_t *v = malloc(sizeof(*v));
    *v = (vector_t) {-LENGTH, -HEIGHT};
    list_add(rectangle, v);
    v = malloc(sizeof(*v));
    *v = (vector_t) {+LENGTH, -HEIGHT};
    list_add(rectangle, v);
    v = malloc(sizeof(*v));
    *v = (vector_t) {+LENGTH, +HEIGHT};
    list_add(rectangle, v);
    v = malloc(sizeof(*v));
    *v = (vector_t) {-LENGTH, +HEIGHT};
    list_add(rectangle, v);
    return rectangle;
}

body_t *make_ellipse() {
    vector_t spawn = FIGHTER_SPAWN;
    list_t *c = list_init(CIRC_NPOINTS, (free_func_t) free);
    for (size_t i = 0; i < CIRC_NPOINTS; i++) {
        double angle = 2 * M_PI * i / CIRC_NPOINTS;
        vector_t *v = malloc(sizeof(*v));
        *v = (vector_t) {3 * PELLET_RADIUS * cos(angle), PELLET_RADIUS * sin(angle)};
        *v = vec_add(*v, spawn);
        list_add(c, v);
    }
    return body_init(c, CIRCLE_MASS, choose_rand_color());
}

body_t *shoot_bullet(body_t *shooter, bool direction, scene_t *scene){
    vector_t centroid = body_get_centroid(shooter);
    body_t *bullet = body_init(make_rectangle(), BULLET_MASS, BULLET_COLOR);
    if(direction){
        body_set_velocity(bullet, (vector_t){0, BULLET_VELOCITY});
        body_set_centroid(bullet, centroid);
        scene_add_body(scene, bullet);
    }
    else{
        body_set_velocity(bullet, (vector_t) {0, -BULLET_VELOCITY});
        body_set_centroid(bullet, centroid);
        scene_add_body(scene, bullet);
    }
    return bullet;
}

bool past_boundary(body_t *ellipse) {
    if ((polygon_centroid(body_get_shape(ellipse)).x) + 4*PELLET_RADIUS< WINDOW_WIDTH_ && (polygon_centroid(body_get_shape(ellipse)).x) - 4*PELLET_RADIUS> 0) {
        return false;
    }
    return true;
}

void on_key(char key, key_event_type_t type, double held_time, void *scene) {
    body_t *ellipse = scene_get_body((scene_t*)scene, 0);
    if (type == KEY_PRESSED) {
        switch (key) {
            case RIGHT_ARROW:
                body_set_velocity(ellipse, RIGHT_VELOCITY);
                break;
            case LEFT_ARROW:
                body_set_velocity(ellipse, LEFT_VELOCITY);
                break;
            case SDLK_SPACE:
                if (true == true) {
                    body_t *bullet = shoot_bullet(ellipse, true, (scene_t*)scene);
                    for (size_t i = 1; i < TOTAL_INVADERS+1; i++) {
                        create_destructive_collision((scene_t*)scene, scene_get_body((scene_t*)scene, i), bullet);
                    }
                    scene_add_body((scene_t*)scene, bullet);
                }
        }
    }
    else {
        body_set_velocity(ellipse, VEC_ZERO);
    }
}

bool hits_edge(body_t *body) { 
    if ((polygon_centroid(body_get_shape(body)).x) + INVADER_RADIUS < WINDOW_WIDTH_ && (polygon_centroid(body_get_shape(body)).x) - INVADER_RADIUS > 10) {
        return false;
    }
    return true;
}

void move_invaders(scene_t *scene) {
  double shift = (INVADER_RADIUS + SPACE_BETWEEN) * 3;
  for (int i = 1; i < TOTAL_INVADERS+1; i++) {
    vector_t centroid = body_get_centroid(scene_get_body(scene, i));
    if (hits_edge(scene_get_body(scene, i))) {
      vector_t new_centroid = vec_add(centroid, (vector_t){0, -shift});
      body_set_centroid(scene_get_body(scene, i), new_centroid);
      vector_t update_velocity = vec_negate(body_get_velocity(scene_get_body(scene, i)));
      body_set_velocity(scene_get_body(scene, i), update_velocity);
    }
  }
}

void init_make_invaders(scene_t *scene){
    double y_position = WINDOW_HEIGHT_ - INVADER_RADIUS;
    double x_position = INVADER_RADIUS + 10;
    double shift_down = INVADER_RADIUS + SPACE_BETWEEN;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            body_t *invaders = make_invaders();
            body_set_centroid(invaders, (vector_t) {x_position + 2 * INVADER_RADIUS * j, y_position});
            body_set_velocity(invaders, (vector_t) {INVADER_VEL, 0});
            scene_add_body(scene, invaders);
        }
        y_position -= shift_down;
    }
}

int main() {
    sdl_init(MIN_POINT, MAX_POINT);
    
    scene_t *scene = scene_init();
    body_t *fighter = make_ellipse();

    scene_add_body(scene, fighter);
    init_make_invaders(scene);
    sdl_on_key((key_handler_t) on_key);
    double time = 0;
    while (!sdl_is_done(scene)) {
        if (past_boundary(fighter)) { body_set_velocity(fighter, vec_negate(body_get_velocity(fighter))); }
        double dt = time_since_last_tick();
        if (time > SHOOT_RATE) {
            size_t shooter_num = rand() % TOTAL_INVADERS + 1;
            body_t *shooter = scene_get_body(scene, shooter_num);
            body_t *bullet = shoot_bullet(shooter, false, scene);
            create_destructive_collision(scene, scene_get_body(scene, 0), bullet);
            scene_add_body(scene, bullet);
            time = 0;
        }
        move_invaders(scene);
        scene_tick(scene, dt);
        sdl_render_scene(scene);
        time += 0;
    }
    scene_free(scene);
    return 0;
}
