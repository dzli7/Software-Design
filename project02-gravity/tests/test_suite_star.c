#include "star.h"
#include "test_util.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "free_func.h"

star_t *make_star() {
    list_t *points = list_init(2, (free_func_t) star_free);
    vector_t *point_1 = malloc(sizeof(vector_t));
    point_1->x = 0; point_1->y = 0;
    vector_t *point_2 = malloc(sizeof(vector_t));
    point_2->x = 100; point_2->y = 100;
    list_add(points, point_1);
    list_add(points, point_2);
    vector_t velocity = {.x = 2, .y = 2};
    star_t *star = star_init(points, choose_rand_color(), velocity);
    return star;
}

// void test_star_get_points() {
//     star_t *star = make_star();
//     assert(vec_list_get(star_get_points(star), 0)->x == 0);
//     assert(vec_list_get(star_get_points(star), 0)->y == 0);
//     assert(vec_list_get(star_get_points(star), 1)->x == 100);
//     assert(vec_list_get(star_get_points(star), 1)->y == 100);
//     star_free(star);
// }

void test_star_get_velocity() {
    star_t *star = make_star();
    assert(star_get_velocity(star).x == 2);
    assert(star_get_velocity(star).y == 2);
    star_free(star);
}

void test_star_get_color() {
    star_t *star = make_star();
    colors_t *color = star_get_color(star);
    assert(get_R_color(color) <= 1 && get_R_color(color) >= 0);
    assert(get_G_color(color)<= 1 && get_G_color(color) >= 0);
    assert(get_B_color(color)<= 1 && get_B_color(color) >= 0);
    star_free(star);
}

void test_star_set_points() {
    star_t *star = make_star();
    list_t *new_points = list_init(2, (free_func_t) star_free);
    vector_t *point_1 = malloc(sizeof(vector_t));
    point_1->x = 420; point_1->y = 420;
    vector_t *point_2 = malloc(sizeof(vector_t));
    point_2->x = 69; point_2->y = 69;
    list_add(new_points, point_1);
    list_add(new_points, point_2);
    star_set_points(star, new_points);
    assert(new_points == star_get_points(star));
    star_free(star);
}

void test_star_set_velocity() {
    star_t *star = make_star();
    vector_t *velocity = malloc(sizeof(vector_t));
    velocity->x = 42069; velocity->y = 42069;
    star_set_velocity(star, *velocity);
    assert(star_get_velocity(star).x == 42069);
    assert(star_get_velocity(star).y == 42069);
    star_free(star);
}

int main(int argc, char *argv[]) {
    // Run all tests? True if there are no command-line arguments
    bool all_tests = argc == 1;
    // Read test name from file
    char testname[100];
    if (!all_tests) {
        read_testname(argv[1], testname, sizeof(testname));
    }

    // DO_TEST(test_star_get_points)
    DO_TEST(test_star_get_velocity)
    DO_TEST(test_star_get_color)
    DO_TEST(test_star_set_points)
    DO_TEST(test_star_set_velocity)

    puts("star_test PASS");
}