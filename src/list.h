#ifndef LIST_H
#define LIST_H

 #define LIST_DECLARE(type)                                                 \
                                                                            \
/** type t_list */                                                          \
typedef struct type##_list_s                                                \
{                                                                           \
  type head;                                                                \
  struct type##_list_s *tail;                                               \
} type##_list;                                                              \
                                                                            \
/** Creates a new t_list with old t_list as tail and new element as head */ \
type##_list *type##_list_cons(type, type##_list *);                         \
                                                                            \
/** Returns the length of the given t_list */                               \
int type##_list_length(type##_list *);                                      \
                                                                            \  
/** Gives first element                                                     \
 ** Risk of Segfault if given null */                                       \
type type##_list_head(type##_list *);                                       \
                                                                            \
/** Gives t_list without its first element                                  \
 ** Risk of Segfault if given null */                                       \
type##_list *type##_list_tail(type##_list *);                               \
                                                                            \
/** Appends two t_lists */                                                  \
type##_list *type##_list_append(type##_list *, type##_list *);              \
                                                                            \
/** Gives element at the asked position.                                    \
 ** Risk of Segfault if position >= length */                               \
type type##_list_nth(type##_list *, int);                                   \
                                                                            \
/** Reverses a list */                                                      \
type##_list *type##_list_rev(type##_list *);                                \
                                                                            \
/** Gives position of asked element if it exists (starting at zero).        \
 ** Returns -1 if the element is not found */                               \
int type##_list_pos(type##_list *, type);                                   \


 #define LIST_TYPE(type) type##_list
 #define LIST_FUN(type, fun) type##_list_##fun
 #include "list.c"

#endif /* !LIST_H */
