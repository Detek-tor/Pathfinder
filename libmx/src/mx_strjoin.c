#include "libmx.h"

char *mx_strjoin(char const *s1, char const *s2) {
	char *str = NULL;
	if (s1 != NULL || s2 != NULL) {
		if (s1 != NULL && s2 != NULL) {
			str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
			str = mx_strcpy(str, s1);
			str = mx_strcat(str, s2);
		}
		else if (s1 == NULL && s2 != NULL) {
			return mx_strdup(s2);
		}
		else if (s1 != NULL && s2 == NULL) {
			return mx_strdup(s1);
		}
	return str;
	}
	else return NULL;
}
