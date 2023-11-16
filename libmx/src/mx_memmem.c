#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {

	unsigned char *st1 = NULL;
	unsigned char *st2 = NULL;

	if (big_len >= little_len && big_len > 0 && little_len > 0)
	{
		st1 = (unsigned char *)big;
		st2 = (unsigned char *)little;
		while (*st1)
		{
			if (mx_memcmp(st1, st2, little_len - 1) == 0)
				return st1;
			st1++;
		}
	}
	return NULL;
}
