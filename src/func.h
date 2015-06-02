#ifndef FUNC_H
 #define FUNC_H
 #include "list.h"

 #define FUNC_DECLARE(t_in, t_out)\
\
LIST_DECLARE(t_in)\
LIST_DECLARE(t_out)\
\
LIST_TYPE(t_out) *##t_in##_##t_out##_map(t_out (*fun)(t_in), LIST_TYPE(t_in)*);\
\
void ##t_in##_##t_out##_iter(void (*fun)(t_in), LIST_TYPE(t_in)*);\
\
t_out ##t_in##_##t_out##_fold_left(t_out (*fun)(t_out, t_in), t_out, LIST_TYPE(t_in)*);\
\
t_out ##t_in##_##t_out##_fold_left(t_out (*fun)(t_in, t_out), LIST_TYPE(t_in)*, t_out);\


#endif /* ! FUNC_H */
