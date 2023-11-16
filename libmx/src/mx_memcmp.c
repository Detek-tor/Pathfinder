#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {

    const unsigned char *string1 = s1;
    const unsigned char *string2 = s2;
    unsigned int j = 0;
    if (n == 0)
        return 0;
    else
    {
        while (string1[j] == string2[j] && j != n)
        {
            if (string1[j] == '\0' && string2[j] == '\0')
                return 0;
            j++;
        }
        return string1[j] - string2[j];
    }
}
