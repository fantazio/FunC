#include "func.h"

#define FUNC_DEFINE(t_in, t_out)\
  \
LIST_DEFINE(t_in)\
LIST_DEFINE(t_out)\
\
LIST_TYPE(t_out) *##t_in##_##t_out##_map(t_out (*fun)(t_in),\
    LIST_TYPE(t_in) *list)\
{\
  return null;\
}\
\
void ##t_in##_##t_out##_iter(void (*fun)(t_in), LIST_TYPE(t_in)* list)\
{\
}\
\
t_out ##t_in##_##t_out##_fold_left(t_out (*fun)(t_out, t_in),\
    t_out init, LIST_TYPE(t_in)* list)\
{\
  return fun(init, LIST_FUN(t_in, head)(list));\
}\
\
t_out ##t_in##_##t_out##_fold_left(t_out (*fun)(t_in, t_out),\
    LIST_TYPE(t_in)* list, t_out end)\
{\
    return fun(LIST_FUN(t_in, head)(list), end);\
}\
