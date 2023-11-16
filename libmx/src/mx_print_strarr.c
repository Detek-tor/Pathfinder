#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim)
{
  int count = 0;
  if (arr!=NULL && delim!=NULL)
  {
    while (true)
    {
      if (arr[count] == NULL)
      {
        write(1, "\n", 1);
        break;
      }
      mx_printstr(arr[count]);
      if (arr[count+1] != NULL)
        mx_printstr(delim);
      count++;
    }
  }
}
