#include "libmx.h"

char *mx_strcat(char *restricts1, const char *restricts2) {
	int len1 = mx_strlen(restricts1);
	int len2 = mx_strlen(restricts2);
	int i = len1;
	int j = 0;
	while (i<=(len1+len2))
	{
		restricts1[i] = restricts2[j];
		i++;
		j++;
	}
	restricts1[++i] ='\0';
	return restricts1;
}
