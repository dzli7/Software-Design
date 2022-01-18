#include <math.h>
#include "polygon.h"


double polygon_area(vec_list_t *polygon) {
    double area = 0;
    for (size_t i = 0; i < vec_list_size(polygon); i++) {
        vector_t *v1 = vec_list_get(polygon, i);
        vector_t *v2 = vec_list_get(polygon, (i+1) % vec_list_size(polygon));
        area += (v1->x*v2->y);
        area -= (v2->x*v1->y);
    }
    return fabs(area)/2.0;
}


vector_t polygon_centroid(vec_list_t *polygon) {
    double area = polygon_area(polygon);
    vector_t centroid;
    centroid.x = 0;
    centroid.y = 0;
    for (size_t i = 0; i < vec_list_size(polygon); i++) {
        vector_t *v1 = vec_list_get(polygon, i);
        vector_t *v2 = vec_list_get(polygon, (i+1) % vec_list_size(polygon));
        centroid.x += (v1->x + v2->x)*(vec_cross(*v1, *v2));
        centroid.y += (v1->y + v2->y)*(vec_cross(*v1, *v2));
    }
    centroid.x = centroid.x / (6*area);
    centroid.y = centroid.y / (6*area);
    return centroid;
}


void polygon_translate(vec_list_t *polygon, vector_t translation) {
    for (size_t i = 0; i < vec_list_size(polygon); i++) {
        vector_t *v = vec_list_get(polygon, i);
        v->x += translation.x;
        v->y += translation.y;
    }
}


void polygon_rotate(vec_list_t *polygon, double angle, vector_t point) {
    for (size_t i = 0; i < vec_list_size(polygon); i++) {
        vector_t *v = vec_list_get(polygon, i);
        *v = vec_subtract(*v, point);
        *v = vec_rotate(*v, angle);
        *v = vec_add(*v, point);
    }
}