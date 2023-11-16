#include "libmx.h"

static void swap(void **s1, void **s2)
{
    void *tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

t_list *mx_sort_list(t_list *list, bool (*cmp)(void *, void *))
{
    if (list && cmp)
    {
      for (t_list *tmp1 = list; tmp1; tmp1 = tmp1->next)
          for (t_list *tmp2 = list; tmp2->next; tmp2 = tmp2->next)
              if (cmp(tmp2->data, tmp2->next->data))
                  swap(&tmp2->data, &tmp2->next->data);
    }

    return list;
}
