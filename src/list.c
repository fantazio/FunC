#include "list.h"

#define LIST_DEFINE(type)\
void type##_list_cons(type##_list *list, type elt)\
{\
  struct type##_list *res = malloc(sizeof (type##list));\
  res->data = elt;\
  res->next = list;\
  return res;\
}\
\
int type##_list_length(type##_list *list)\
{\
  type##list *tmp = list;\
  uint length = 0;\
  while (tmp)\
  {\
    tmp = tmp->next;\
    ++length;\
  }\
  return length;\
}\
\
type type##_list_head(type##_list *list)\
{\
  return list->data;\
}\
\
type##_list *type##_list_tail(type##_list *list)\
{\
  return list->next;\
}\
\
type##_list *type##_list_concat(type##_list *l1, type##_list *l2)\
{\
  if (!l1)\
    return l2;\
  type##_list *tmp = l1;\
  while (tmp->next)\
    tmp = tmp->next;\
  tmp->next = l2;\
  return l1;\
}\
\
type type##_list_nth(type##_list *list, int pos)\
{\
  while (pos > 0)\
    list = list->next;\
  return list->data;\
}\
\
int type##_list_pos(type##_list *list, type elt)\
{\
  uint pos = 0;\
  while (list && list->data != elt)\
  {\
    list = list->next;\
    ++pos;\
  }\
  return list ? pos : -1;\
}\
