#include "sdl_wrapper.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "free_func.h"
#include "vec_list.h"
#include "list.h"
#include "star.h"


#define WINDOW_TITLE "CS 3"

const size_t WINDOW_WIDTH = 1000;
const size_t WINDOW_HEIGHT = 500;
const vector_t MIN_POINT = {0, 0};
const vector_t MAX_POINT = {WINDOW_WIDTH, WINDOW_HEIGHT};

const vector_t GRAVITY = {0, -600};
const size_t X_VELOCITY = 200;
const size_t Y_VELOCITY = 100;

const double BOUNCE_FACTOR = 0.8;
const double SPAWN_RATE = 1.2;
const double ROTATION = 2;
const int RADIUS = 50;

//TODO: free shit, figure out what size to malloc, figure out if we can keep shit in polygon.c

list_t *make_star(int points, int radius, vector_t center)
{
    list_t *star = list_init(2 * points, (free_func_t) free);
    double angle = 2 * M_PI / points;

    //find the first point on the outside (point above centroid)
    vector_t outside_first = {.x = center.x, .y = center.y + radius};

    //find the first point on the inside (point to right of centroid)
    double inner_angle_start = (M_PI / points) + (M_PI / 2);
    double inner_radius = RADIUS / 2;

    vector_t inside_first = {.x = inner_radius * cos(inner_angle_start), .y = inner_radius * sin(inner_angle_start)};
    inside_first = vec_add(inside_first, center);

    //given the first point, add each vector rotated into star
    for (size_t i = 0; i < points; i++)
    {
        double angle_rot = angle * i;
        vector_t *outside = malloc(sizeof(vector_t));
        *outside = vec_subtract(outside_first, center);
        *outside = vec_rotate(*outside, angle_rot);
        *outside = vec_add(*outside, center);

        vector_t *inside = malloc(sizeof(vector_t));
        *inside = vec_subtract(inside_first, center);
        *inside = vec_rotate(*inside, angle_rot);
        *inside = vec_add(*inside, center);

        list_add(star, outside);
        list_add(star, inside);
    }
    return star;
}



vector_t update_position(vector_t velocity, double dt, double radius, list_t *polygon)
{
    vector_t center = polygon_centroid(polygon);
    velocity = vec_add(velocity, vec_multiply(dt, GRAVITY));
    vector_t dxy = vec_multiply(dt, velocity);
    double dx = dxy.x;
    double dy = dxy.y;

    if (dxy.y > 0 && center.y + dxy.y + radius >= WINDOW_HEIGHT)
    {
        velocity.y *= -1 * BOUNCE_FACTOR;
        dy = WINDOW_HEIGHT - center.y - radius - dxy.y;
    }
    else if (dxy.y < 0 && center.y + dxy.y - radius <= 0)
    {
        velocity.y *= -1 * BOUNCE_FACTOR;
        dy = radius - center.y - dxy.y;
    }

    vector_t displacement = {.x = dx, .y = dy};
    polygon_translate(polygon, displacement);
    polygon_rotate(polygon, ROTATION * dt, center);
    return velocity;
}

int main()
{
    double time = 0;
    int points = 2; //initial numbers of the points for the first polygon
    int num_stars = 0;
    int max_stars = WINDOW_WIDTH / X_VELOCITY / SPAWN_RATE;
    vector_t initial_velocity = {.x = X_VELOCITY, .y = Y_VELOCITY};
    vector_t spawn = {.x = RADIUS, .y = WINDOW_HEIGHT - RADIUS};
    sdl_init(MIN_POINT, MAX_POINT);
    list_t *stars = list_init(max_stars, (free_func_t) star_free);
    while (!sdl_is_done())
    {
        double dt = time_since_last_tick();
        time += dt;
        if (time > SPAWN_RATE || num_stars == 0)
        {
            star_t *star = star_init(make_star(points, RADIUS, spawn), choose_rand_color(), initial_velocity);
            time = 0;
            list_add(stars, star);
            points++;
            num_stars++;
        }
        sdl_clear();
        for (size_t i = 0; i < num_stars; i++)
        {
            star_t *star_i = list_get(stars, i);
            if (polygon_centroid(star_get_points(star_i)).x - RADIUS > WINDOW_WIDTH)
            {
                star_free(list_remove_front(stars));
                num_stars--;
                assert(num_stars >= 0);
            }
            else
            {
                colors_t *color = star_get_color(star_i);
                star_set_velocity(star_i, update_position(star_get_velocity(star_i), dt, RADIUS, star_get_points(star_i)));
                sdl_draw_polygon(star_get_points(star_i), get_R_color(color), get_G_color(color), get_B_color(color));
            }
        }
        sdl_show();
    }
    list_free(stars);
    return 0;
}
