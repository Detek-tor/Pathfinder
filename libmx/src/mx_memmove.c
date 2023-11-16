#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len)
{
  unsigned char *str = malloc(len);
  str = mx_memcpy(str, src, len);
  dst = mx_memcpy(dst, str, len);
  free(str);

  return dst;
}
