#include "libmx.h"

void mx_str_reverse(char *s) {
	int len = 0;
	while(s[len] != '\0') {
		len++;
	}
	if (s) {
		for (int i = 0, j = len - 1; i<j; i++, j--) {
			char char1 = s[i];
			s[i] = s[len - i - 1];
			s[len - i - 1] = char1;
		}
	}
}
