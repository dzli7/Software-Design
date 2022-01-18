#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "star.h"

typedef struct star{
    list_t *points;
    colors_t *color;
    vector_t velocity;
} star_t;

colors_t *star_get_color(star_t * polygon) {
    return polygon->color;
}

star_t * star_init(list_t * points, colors_t *color, vector_t velocity) {
    star_t *polygon = malloc(sizeof(star_t));
    polygon->points = points;
    polygon->color = color;
    polygon->velocity = velocity;
    return polygon;
}

list_t *star_get_points(star_t * polygon) {
    return polygon->points;
}

vector_t star_get_velocity(star_t * polygon) {
    return polygon->velocity;
}

void star_set_points(star_t * polygon, list_t *points) {
    polygon->points = points;
}

void star_set_velocity(star_t * polygon, vector_t velocity) {
    polygon->velocity = velocity;
}

void star_free(star_t *polygon){
    list_free(star_get_points(polygon));
    free(star_get_color(polygon));
    free(polygon);
}