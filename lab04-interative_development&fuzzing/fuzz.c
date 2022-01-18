#include "match.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

void check(bool actual, char *pattern, char *text) {
    char *buffer = malloc(sizeof(char) * (strlen(pattern) + strlen(text) + 50));
    buffer[0] = '\0';
    strcat(buffer, "echo \"");
    strcat(buffer, text);
    strcat(buffer, "\" | grep -c \"^");
    strcat(buffer, pattern);
    strcat(buffer, "$\"");
    FILE *file = popen(buffer, "r");
    char *b = malloc(sizeof(char));
    b[0] = fgetc(file);
    assert((b[0] == '1' && actual) || (b[0] == '0' && !actual));
    pclose(file);
    free(buffer);
    free(b);
}

bool is_valid(char *text, size_t len) {
    char curr = '\0';
    if (text[0] == '*') {return false;}
    for (size_t i = 0; i < len; i++) {
        if (!isalpha(text[i]) && !(text[i] == '*' || text[i] == '.')) {return false;}
        if (curr == text[i] && curr == '*') {return false;}
        curr = text[i];
    }
    return true;
}

int LLVMFuzzerTestOneInput(uint8_t *data, size_t size) {
    size_t intsize = size / sizeof(int8_t);
    uint8_t *intdata = (uint8_t *)data;
    if (intsize >= 2) {
        size_t len1 = intdata[0];
        if (size >= sizeof(uint8_t) + len1) {
            size_t len2 = size - sizeof(uint8_t) - len1;
            char *str = ( (char *)intdata ) + 1;
            char *str1 = calloc(len1 + 1, sizeof(char));
            char *str2 = calloc(len2 + 1, sizeof(char));
            strncpy(str1, str, len1);
            strncpy(str2, str + len1, len2);
            if (is_valid(str1, len1) && is_valid(str2, len2))  {
                printf("s1=%s, s2=%s\n", str1, str2);
                bool result = match(str1, str2);
                check(result, str1, str2);
                free(str1);
                free(str2);
                return result;
            }
            free(str1);
            free(str2);
        }
    }
    return 0;
}