#ifndef __COLOR_H__
#define __COLOR_H__


typedef struct color colors_t;
colors_t *choose_rand_color();

double get_R_color(colors_t *color);
double get_G_color(colors_t *color);
double get_B_color(colors_t *color);


#endif // #ifndef __COLOR_H__