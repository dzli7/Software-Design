#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **string_blanks(char *s) {
    char **array = malloc(sizeof(char *) * strlen(s));
    for (int i = 0; i < strlen(s); i++) {
        array[i] = malloc(strlen(s) + 1);
        array[i][strlen(s)] = '\0';
        for (int j = 0; j < strlen(s); j++) {
            if (j == i) {
                array[i][j] = '_';
            }
            else {
                array[i][j] = s[j];
            }
        }
    }
    return array;
}

int main(int argc, char *argv[]) {
    char **blanks = string_blanks("Adam");
    for (int i = 0; i < strlen("Adam"); i++) {
        printf("%s ", blanks[i]);
        free(blanks[i]);
    }
    printf("\n");
    free(blanks);
}