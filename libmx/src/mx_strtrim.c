#include "libmx.h"

char *mx_strtrim(const char *str) {
    if (!str)
        return NULL;
    while (mx_isspace(*str))
        str++;
    int length = mx_strlen(str);
    while (mx_isspace(str[length - 1]))
        length--;
    return mx_strndup(str, length);
}
