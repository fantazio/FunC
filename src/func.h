#ifndef FUNC_H
 #define FUNC_H
 #include "list.h"

 #define FUNC_DECLARE2(t_in, t_out)                                                     \
                                                                                        \
/** Creates a new list from the given one by applying the given function
 ** on all its elements*/                                                               \
LIST_TYPE(t_out) * t_in##_##t_out##_map(t_out (*fun)(t_in), LIST_TYPE(t_in)*);          \
                                                                                        \
t_out t_in##_##t_out##_fold_left(t_out (*fun)(t_out, t_in), t_out, LIST_TYPE(t_in)*);   \
                                                                                        \
t_out t_in##_##t_out##_fold_right(t_out (*fun)(t_in, t_out), LIST_TYPE(t_in)*, t_out);

#define FUNC_DECLARE(t_in)                                              \
/** Applies the given function on all the elements of the given list */ \
void t_in##_iter(void (*fun)(t_in), LIST_TYPE(t_in)*);

 #define FUNC_MAP(t_in, t_out) t_in##_##t_out##_map
 #define FUNC_ITER(t_in) t_in##_iter
 #define FUNC_FOLD_LEFT(t_in, t_out) t_in##_##t_out##_fold_left
 #define FUNC_FOLD_RIGHT(t_in, t_out) t_in##_##t_out##_fold_right

 #include "func.c"
#endif /* ! FUNC_H */
