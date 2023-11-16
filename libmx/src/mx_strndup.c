#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    char *dupl = NULL;
    size_t length = mx_strlen(s1);

    if (n < length)
        length = n;

    dupl = mx_strnew(length);
    mx_strncpy(dupl, s1, length);
    return dupl;
}
