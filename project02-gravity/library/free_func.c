#include "free_func.h"
#include "vec_list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// void star_free(star_t *polygon){
//     vec_list_free(star_get_points(polygon));
//     free(star_get_color(polygon));
//     free(polygon);
// }

// void vec_list_free(vec_list_t *list){
//     vector_t **vectors = vec_list_get_vectors(list);
//     for (int i = 0; i < vec_list_get_size(); i++) {
//         free(vectors[i]);
//     }
//     free(vectors);
//     free(list);
// }