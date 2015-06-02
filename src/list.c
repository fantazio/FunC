#include "list.h"

#define LIST_DEFINE(type)\
void type##_list_cons(type##_list *list, type elt)\
{\
  struct type##_list *res = malloc(sizeof (type##list));\
  res->head = elt;\
  res->tail = list;\
  return res;\
}\
\
int type##_list_length(type##_list *list)\
{\
  type##list *tmp = list;\
  uint length = 0;\
  while (tmp)\
  {\
    tmp = tmp->tail;\
    ++length;\
  }\
  return length;\
}\
\
type type##_list_head(type##_list *list)\
{\
  return list->head;\
}\
\
type##_list *type##_list_tail(type##_list *list)\
{\
  return list->tail;\
}\
\
type##_list *type##_list_append(type##_list *l1, type##_list *l2)\
{\
  if (!l1)\
    return l2;\
  type##_list *tmp = l1;\
  while (tmp->tail)\
    tmp = tmp->tail;\
  tmp->tail = l2;\
  return l1;\
}\
\
type type##_list_nth(type##_list *list, int pos)\
{\
  while (pos > 0)\
    list = list->tail;\
  return list->head;\
}\
\
type##_list *type##_list_rev(type##_list *list)\
{\
  if (!list)\
    list;\
  type##_list *next = list->tail;\
  list->tail = NULL;\
  while (next)\
  {\
    type##_list *tmp = next->tail;\
    next->tail = list;\
    list = next;\
    next = tmp;\
  }\
  return list;\
}\
\
int type##_list_pos(type##_list *list, type elt)\
{\
  uint pos = 0;\
  while (list && list->head != elt)\
  {\
    list = list->tail;\
    ++pos;\
  }\
  return list ? pos : -1;\
}\
