#include "list.h"

void list_##type##_cons(list_##type## *list, t elt)
{
  struct list_##type## *res = malloc(sizeof (type##list));
  res->data = elt;
  res->next = list;
  return res;
}

int list_##type##_length(list_##type## *list)
{
  type##list *tmp = list;
  uint length = 0;
  while (tmp)
  {
    tmp = tmp->next;
    ++length;
  }
  return length;
}

t list_##type##_head(list_##type## *list)
{
  return list->data;
}

list_##type## *list_##type##_tail(list_##type## *list)
{
  return list->next;
}

list_##type## *list_##type##_concat(list_##type## *l1, list_##type## *l2)
{
  if (!l1)
    return l2;
  list_##type## *tmp = l1;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = l2;
  return l1;
}

t list_##type##_nth(list_##type## *list, int pos)
{
  while (pos > 0)
    list = list->next;
  return list->data;
}

int list_##type##_pos(list_##type## *list, t elt)
{
  uint pos = 0;
  while (list && list->data != elt)
  {
    list = list->next;
    ++pos;
  }
  return list ? pos : -1;
}
