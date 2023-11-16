#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len)
{
if (len != 0) {
		char *ds = dst;
		const char *s = src;
		do
		{
			if ((*ds++ = *s++) == 0)
			{
				while (--len != 0)
					*ds++ = 0;
				break;
			}
		} while (--len != 0);
	}

	return (dst);
}
