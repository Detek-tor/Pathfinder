#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n)
{
  unsigned char *str = (unsigned char *)s;
  while (n>0)
  {
    if (*str == (unsigned char)c)
      return str;
    str++;
    n--;
  }
  return NULL;
}
