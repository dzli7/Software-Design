#include "vec_list.h"
#include "free_func.h"
#include "test_util.h"
#include <assert.h>
#include <stdlib.h>

void test_list_size0() {
    vec_list_t *l = vec_list_init(0);
    assert(vec_list_size(l) == 0);
    vec_list_free(l);
}

void test_list_size1() {
    vec_list_t *l = vec_list_init(1);
    assert(vec_list_size(l) == 0);
    // Add
    vector_t *v = malloc(sizeof(*v));
    *v = VEC_ZERO;
    vec_list_add(l, v);
    assert(vec_list_size(l) == 1);
    // Remove
    assert(vec_list_remove(l) == v);
    free(v);
    assert(vec_list_size(l) == 0);
    // Add again
    v = malloc(sizeof(*v));
    v->x = v->y = 1;
    vec_list_add(l, v);
    assert(vec_list_size(l) == 1);
    assert(vec_equal(*vec_list_get(l, 0), (vector_t) {1, 1}));
    // Modify
    *v = (vector_t) {1, 2};
    assert(vec_list_size(l) == 1);
    assert(vec_equal(*vec_list_get(l, 0), (vector_t) {1, 2}));
    vec_list_free(l);
}

void test_list_small() {
    vec_list_t *l = vec_list_init(5);
    assert(vec_list_size(l) == 0);
    // Fill partially
    vector_t *v = malloc(sizeof(*v));
    *v = VEC_ZERO;
    vec_list_add(l, v);
    v = malloc(sizeof(*v));
    v->x = v->y = 1;
    vec_list_add(l, v);
    v = malloc(sizeof(*v));
    v->x = v->y = 2;
    vec_list_add(l, v);
    assert(vec_list_size(l) == 3);
    assert(vec_equal(*vec_list_get(l, 0), VEC_ZERO));
    assert(vec_equal(*vec_list_get(l, 1), (vector_t) {1, 1}));
    assert(vec_equal(*vec_list_get(l, 2), (vector_t) {2, 2}));
    // Fill to capacity
    v = malloc(sizeof(*v));
    v->x = v->y = 3;
    vec_list_add(l, v);
    v = malloc(sizeof(*v));
    v->x = v->y = 4;
    vec_list_add(l, v);
    assert(vec_list_size(l) == 5);
    assert(vec_equal(*vec_list_get(l, 3), (vector_t) {3, 3}));
    assert(vec_equal(*vec_list_get(l, 4), (vector_t) {4, 4}));
    // Remove some
    v = vec_list_remove(l);
    assert(vec_equal(*v, (vector_t) {4, 4}));
    free(v);
    v = vec_list_remove(l);
    assert(vec_equal(*v, (vector_t) {3, 3}));
    free(v);
    assert(vec_list_size(l) == 3);
    // Add, replacing previous elements
    v = malloc(sizeof(*v));
    v->x = v->y = 5;
    vec_list_add(l, v);
    v = malloc(sizeof(*v));
    v->x = v->y = 6;
    vec_list_add(l, v);
    assert(vec_list_size(l) == 5);
    assert(vec_equal(*vec_list_get(l, 0), (vector_t) {0, 0}));
    assert(vec_equal(*vec_list_get(l, 1), (vector_t) {1, 1}));
    assert(vec_equal(*vec_list_get(l, 2), (vector_t) {2, 2}));
    assert(vec_equal(*vec_list_get(l, 3), (vector_t) {5, 5}));
    assert(vec_equal(*vec_list_get(l, 4), (vector_t) {6, 6}));
    // Overwrite added elements
    *vec_list_get(l, 3) = (vector_t) {7, 7};
    *vec_list_get(l, 4) = (vector_t) {8, 8};
    assert(vec_equal(*vec_list_get(l, 0), (vector_t) {0, 0}));
    assert(vec_equal(*vec_list_get(l, 1), (vector_t) {1, 1}));
    assert(vec_equal(*vec_list_get(l, 2), (vector_t) {2, 2}));
    assert(vec_equal(*vec_list_get(l, 3), (vector_t) {7, 7}));
    assert(vec_equal(*vec_list_get(l, 4), (vector_t) {8, 8}));
    vec_list_free(l);
}

#define LARGE_SIZE 1000000

// Get/set elements in large list
void test_list_large_get_set() {
    vec_list_t *l = vec_list_init(LARGE_SIZE);
    // Add to capacity
    for (size_t i = 0; i < LARGE_SIZE; i++) {
        vector_t *v = malloc(sizeof(*v));
        v->x = v->y = i;
        vec_list_add(l, v);
    }
    // Check
    for (size_t i = 0; i < LARGE_SIZE; i++) {
        assert(vec_equal(*vec_list_get(l, i), (vector_t) {i, i}));
    }
    // Set every 100th value
    for (size_t i = 0; i < LARGE_SIZE; i += 100) {
        vector_t *v = vec_list_get(l, i);
        v->x = v->y = i * 10;
    }
    // Check all values again
    for (size_t i = 0; i < LARGE_SIZE; i++) {
        assert(vec_equal(
            *vec_list_get(l, i),
            i % 100 == 0 ? (vector_t) {i * 10, i * 10} : (vector_t) {i, i}
        ));
    }
    vec_list_free(l);
}

// Add/remove elements from a large list
void test_list_large_add_remove() {
    vec_list_t *l = vec_list_init(LARGE_SIZE);
    // Add to capacity
    for (size_t i = 0; i < LARGE_SIZE; i++) {
        vector_t *v = malloc(sizeof(*v));
        v->x = v->y = i;
        vec_list_add(l, v);
    }
    // Remove all
    for (size_t i = 1; i <= LARGE_SIZE; i++) {
        size_t value = LARGE_SIZE - i;
        vector_t *v = vec_list_remove(l);
        assert(vec_equal(*v, (vector_t) {value, value}));
        free(v);
    }
    // Add to capacity again
    for (size_t i = 0; i < LARGE_SIZE; i++) {
        vector_t *v = malloc(sizeof(*v));
        v->x = v->y = i + 1;
        vec_list_add(l, v);
    }
    // Check all
    for (size_t i = 0; i < LARGE_SIZE; i++) {
        assert(vec_equal(*vec_list_get(l, i), (vector_t) {i + 1, i + 1}));
    }
    vec_list_free(l);
}

typedef struct {
    vec_list_t *list;
    size_t index;
} list_access_t;
void get_out_of_bounds(void *aux) {
    list_access_t *access = (list_access_t *) aux;
    vec_list_get(access->list, access->index);
}
void test_out_of_bounds_access() {
    const size_t max_size = 5;
    list_access_t *access = malloc(sizeof(*access));
    access->list = vec_list_init(max_size);
    // This test takes several seconds to run
    fputs("test_out_of_bounds_access running...\n", stderr);

    // Try list with 0 elements, 1 element, ..., up to max_size elements
    for (size_t size = 0; size <= max_size; size++) {
        // Make sure negative indices report as out of bounds
        for (access->index = -3; (int) access->index < 0; access->index++) {
            assert(test_assert_fail(get_out_of_bounds, access));
        }

        // Make sure indices 0 through size - 1 are valid
        for (access->index = 0; access->index < size; access->index++) {
            // Store and retrieve an arbitrary vector
            vector_t new_vector = {size + access->index, size * access->index};
            *vec_list_get(access->list, access->index) = new_vector;
            assert(vec_equal(*vec_list_get(access->list, access->index), new_vector));
        }

        // Assert indices greater than or equal to size are invalid
        for (access->index = size; access->index < size + 3; access->index++) {
            assert(test_assert_fail(get_out_of_bounds, access));
        }

        // Increase the size of the list by 1
        if (size < max_size) {
            vec_list_add(access->list, malloc(sizeof(vector_t)));
        }
    }
    vec_list_free(access->list);
    free(access);
}

void add_past_end(void *l) {
    vec_list_add((vec_list_t *) l, malloc(sizeof(vector_t)));
}
void test_full_add() {
    const size_t size = 3;
    vec_list_t *l = vec_list_init(size);

    // Fill list
    for (size_t i = 0; i < size; i++) {
        vec_list_add(l, malloc(sizeof(vector_t)));
    }

    // Try adding to the full list -- should fail an assertion
    assert(test_assert_fail(add_past_end, l));

    vec_list_free(l);
}

void remove_from_empty(void *l) {
    vec_list_remove((vec_list_t *) l);
}
void test_empty_remove() {
    const size_t size = 100;
    vec_list_t *l = vec_list_init(size);

    // Fill list with copies of v, then remove them all
    vector_t v = {.x = 1, .y = -2};
    for (size_t i = 0; i < size; i++) {
        vector_t *list_v = malloc(sizeof(*list_v));
        *list_v = v;
        vec_list_add(l, list_v);
    }
    for (size_t i = 0; i < size; i++) {
        vector_t *list_v = vec_list_remove(l);
        assert(vec_equal(*list_v, v));
        free(list_v);
    }

    // Try removing from the empty list -- should fail an assertion
    assert(test_assert_fail(remove_from_empty, l));

    vec_list_free(l);
}

void add_null(void *l) {
    vec_list_add(l, NULL);
}
void test_null_values() {
    vec_list_t *l = vec_list_init(1);
    assert(test_assert_fail(add_null, l));
    vec_list_free(l);
}

int main(int argc, char *argv[]) {
    // Run all tests if there are no command-line arguments
    bool all_tests = argc == 1;
    // Read test name from file
    char testname[100];
    if (!all_tests) {
        read_testname(argv[1], testname, sizeof(testname));
    }

    DO_TEST(test_list_size0)
    DO_TEST(test_list_size1)
    DO_TEST(test_list_small)
    DO_TEST(test_list_large_get_set)
    DO_TEST(test_list_large_add_remove)
    DO_TEST(test_out_of_bounds_access)
    DO_TEST(test_full_add)
    DO_TEST(test_empty_remove)
    DO_TEST(test_null_values)

    puts("list_test PASS");
}