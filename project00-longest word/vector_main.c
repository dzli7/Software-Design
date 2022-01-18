#include "vector.h"

void test_vec_init() {
    vector_t *v = vec_init(1,2);
    double x = get_x(v);
    double y = get_y(v);
    printf("x: %f y: %f", x, y);
}

void test_vec_add() {
    vector_t *v1 = vec_init(1,2);
    vector_t *v2 = vec_init(2,3);
    vector_t *v = vec_add(v1,v2);
    printf("%f %f\n", get_x(v), get_y(v));
}

int main () {
    test_vec_add();
    test_vec_init();
    return 0;
}