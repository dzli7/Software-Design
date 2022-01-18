#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int max_word_length = 100;

void check_usage(int argc, char *argv[], FILE *f) {
    if (f==NULL) {
        printf("longest: %s: No such file or directory\n", argv[1]);
        exit(1);
    }
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
}

char* str_init() {
    char *str = malloc(sizeof(char) * (max_word_length + 1)); 
    str[0] = '\0';
    return str;
}

int main(int argc, char *argv[]) {

    FILE *f = fopen(argv[1], "r");
    check_usage(argc, argv, f);

    char *longest = str_init();
    char *curr = str_init();
    int curr_index = 0;

    char c = fgetc(f);
    while (c != EOF) {
        if (c == '\n' || c == ' ') {
            curr[curr_index] = '\0';  //reached end of the word
            if (strlen(curr) > strlen(longest)) {
                strcpy(longest, curr);
            }
            curr[0] = '\0';
            curr_index = 0;
        }
        else {
            curr[curr_index] = c;
            curr_index++;
        }
        c = fgetc(f);
    }
    if (strlen(longest) != 0) {
        printf("%s\n", longest);
    }
    free(longest);
    free(curr);
    return fclose(f);
}
