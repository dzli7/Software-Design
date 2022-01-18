#include <stdio.h>
#include <stdlib.h> 

void check_usage(int argc, char *argv[], FILE *f) {
    if (f==NULL) {
        printf("wc: %s: No such file or directory\n", argv[1]);
        exit(1);
    }
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    
    check_usage(argc, argv, f);

    int num_lines = 0;
    char c = fgetc(f);
    while (c != EOF) {
        if (c == '\n') {
            num_lines++;
        }
        c = fgetc(f);
    }
    printf("%i %s\n", num_lines, argv[1]);
    return fclose(f);
}