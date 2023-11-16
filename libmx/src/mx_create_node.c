#include "libmx.h"

t_list *mx_create_node(void *data) {
  t_list *newNode = NULL;
  if (!data)
    return NULL;
  else {
    newNode = (t_list*)malloc(sizeof(t_list));
    if (!newNode)
      return NULL;
    newNode -> next = NULL;
    newNode -> data = data;
    return newNode;
  }
}
