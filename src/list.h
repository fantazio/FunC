#ifndef LIST_H
#define LIST_H

#define LIST_DECLARE(type)
typedef struct list_##type##_s
{
    type data;
    struct list_##type##_s *next;
} list_##type##;

/// Creates a new t_list with old t_list as tail and new element as head
void list_##type##_cons(list_##type##*, t);

/// Returns the length of the given t_list
int list_##type##_length(list_##type##*);

/// Gives first element
/// Risk of Segfault if given null
t list_##type##_head(list_##type##*);

/// Gives t_list without its first element
/// Risk of Segfault if given null
list_##type## *list_##type##_tail(list_##type##*);

/// Concatenates two t_lists
list_##type## *list_##type##_concat(list_##type##*, list_##type##*);

/// Gives element at the asked position.
/// Risk of Segfault if position >= length
t list_##type##_nth(list_##type##*, int);

/// Gives position of asked element if it exists (starting at zero).
/// Returns -1 if the element is not found
int list_##type##_pos(list_##type##*, t);

#endif /* !LIST_H */
