#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char *string_reverse(char *s) {
    char *r = malloc(strlen(s) + 1);
    for (int i = 0; i < strlen(s); i++) {
        r[strlen(s) - i - 1] = s[i];
    }
    r[strlen(s)] = '\0';
    return r;
}

int main(int argc, char *argv[]) {
    char *rev1 = string_reverse("aaaaaaaaaa");
    printf("%s\n", rev1);
    free(rev1);
    char *rev2 = string_reverse("bbbbbbbbb");
    printf("%s\n", rev2);
    free(rev2);
}