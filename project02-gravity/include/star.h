#ifndef __STAR_H__
#define __STAR_H__

#include "polygon.h"
#include "color.h"
#include "list.h"


typedef struct star star_t;

star_t * star_init(list_t * points, colors_t *color, vector_t velocity);

list_t *star_get_points(star_t * polygon);

colors_t *star_get_color(star_t * polygon);

vector_t star_get_velocity(star_t * polygon);

void star_set_points(star_t * polygon, list_t *points);

void star_set_velocity(star_t * polygon, vector_t velocity);

void star_free(star_t * polygon);

#endif // #ifndef __STAR_H__