#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <stdbool.h>
#include "list.h"
#include "vector.h"

void calculate_slope(list_t *shape, list_t *slopes);
vector_t find_projection(list_t *shape, vector_t *slope);
bool intersecting_projections(vector_t s1, vector_t s2);

/**
 * Determines whether two convex polygons intersect.
 * The polygons are given as lists of vertices in counterclockwise order.
 * There is an edge between each pair of consecutive vertices,
 * and one between the first vertex and the last vertex.
 *
 * @param shape1 the first shape
 * @param shape2 the second shape
 * @return whether the shapes are colliding
 */
bool find_collision(list_t *shape1, list_t *shape2);

#endif // #ifndef __COLLISION_H__
