#include "match.h"
#include <string.h>
#include <stdio.h>

bool help_match(char *pattern, char *text) {
    if (strlen(pattern) == 0 && strlen(text) == 0) {return true;}
    else if (strlen(pattern) == 0 && strlen(text) != 0) {return false;}
    else if (pattern[1] == '*') {
        if (pattern[0] == text[0] || (pattern[0] == '.' && text[0] != '\0')) {
            return (help_match(pattern, text+1) || help_match(pattern+2, text));
        }
        return help_match(pattern+2, text);
    }
    else if(pattern[0] == text[0] || (pattern[0] == '.' && text[0] != '\0')) {
        return help_match(pattern+1, text+1);
    }
    return false;
}

bool match(char *pattern, char *text) {
    return help_match(pattern, text);
}
