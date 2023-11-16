#include "libmx.h"

int mx_get_char_index(const char* str, char c)
{
  if (str)
  {
    int len = mx_strlen(str);
    for (int i = 0; i<len; i++)
    {
      if (str[i] == c)
      {
        return i;
      }
    }
    return -1;
  }
  else
    return -2;
}
