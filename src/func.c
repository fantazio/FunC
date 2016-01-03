#ifndef FUNC_C
#define FUNC_C
 #include "func.h"

 #define FUNC_DEFINE2(t_in, t_out)                                            \
                                                                              \
LIST_TYPE(t_out) * t_in##_##t_out##_map(t_out (*fun)(t_in),                   \
    LIST_TYPE(t_in) *list)                                                    \
{                                                                             \
  if (!list)                                                                  \
    return NULL;                                                              \
  LIST_TYPE(t_out) *res= malloc(sizeof (LIST_TYPE(t_out)));                   \
  LIST_TYPE(t_out) *tmp = res;                                                \
  do                                                                          \
  {                                                                           \
    tmp->head = fun(list->head);                                              \
    tmp = list->tail ? (tmp->tail = malloc(sizeof (LIST_TYPE(t_out)))) : tmp; \
  } while ((list = list->tail));                                              \
                                                                              \
  return res;                                                                 \
}                                                                             \
                                                                              \
t_out t_in##_##t_out##_fold_left(t_out (*fun)(t_out, t_in),                   \
    t_out init, LIST_TYPE(t_in)* list)                                        \
{                                                                             \
  if (list)                                                                   \
    return t_in##_##t_out##_fold_left(fun, fun(init, list->head),             \
                                      list->tail);                            \
  return init;                                                                \
}                                                                             \
                                                                              \
t_out t_in##_##t_out##_fold_right(t_out (*fun)(t_in, t_out),                  \
    LIST_TYPE(t_in)* list, t_out end)                                         \
{                                                                             \
  if (list)                                                                   \
    return fun(list->head,                                                    \
                t_in##_##t_out##_fold_right(fun, list->tail, end));           \
  return end;                                                                 \
}

#define FUNC_DEFINE(t_in)                                   \
                                                            \
void t_in##_iter(void (*fun)(t_in), LIST_TYPE(t_in)* list)  \
{                                                           \
  while (list)                                              \
  {                                                         \
    fun(list->head);                                        \
    list = list->tail;                                      \
  }                                                         \
}

#endif /* !FUNC_C */
