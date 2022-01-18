#include "color.h"
#include "test_util.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

void test_choose_rand_color() {
    colors_t *color = choose_rand_color();
    assert(get_R_color(color) <= 1 && get_R_color(color) >= 0);
    assert(get_G_color(color)<= 1 && get_G_color(color) >= 0);
    assert(get_B_color(color)<= 1 && get_B_color(color) >= 0);
    free(color);
}

int main(int argc, char *argv[]) {
    // Run all tests? True if there are no command-line arguments
    bool all_tests = argc == 1;
    // Read test name from file
    char testname[100];
    if (!all_tests) {
        read_testname(argv[1], testname, sizeof(testname));
    }

    DO_TEST(test_choose_rand_color)

    puts("color_test PASS");
}