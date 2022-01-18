#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "color.h"

typedef struct color {
    double R;
    double G;
    double B;
} colors_t;

double get_R_color(colors_t *color){
    return color->R;
}
double get_G_color(colors_t *color){
    return color->G;
}
double get_B_color(colors_t *color){
    return color->B;
}

colors_t *choose_rand_color() {
    colors_t *color = malloc(sizeof(colors_t));
    color->R = (float)((rand() % 100) / 100.0);
    color->G = (float)((rand() % 100) / 100.0);
    color->B= (float)((rand() % 100) / 100.0);
    return color;
}