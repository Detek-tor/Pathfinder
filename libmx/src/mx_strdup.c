#include "libmx.h"

char *mx_strdup(const char *s1) {
	if (s1 == NULL) return NULL;
	char *dst = mx_strnew(mx_strlen(s1));
	dst = mx_strcpy(dst, s1);
	return dst;

}
