As for many functional languages such as Lisp, Haskell and OCaml, I chose linked lists as main data structure. This choice is based on both my knowledge of functional programming in some specific languages but also on the logic used by their creator that a recursive type is more prone to the paradigm.

# The Foundations #
The entire library is macro based for genericity, starting by the linked list which is as simple as possible:
```C
  #define LIST_DECLARE(type)                                                  \
                                                                              \
  /** type t_list */                                                          \
  typedef struct type##_list_s                                                \
  {                                                                           \
    type head;                                                                \
    struct type##_list_s *tail;                                               \
  } type##_list;                                                              \
```
This gives us a way to access the current element of the node using `head`, and the next node using `tail`.
The biggest issue with this macro is that you cannot have a list of pointers as `type` would be replaced by your type followed by * . It would give us something like `struct your_type*_list_s` which is not allowed in C. A way to get around it is using a defindintion as `typedef LIST_TYPE(t_in)* listptr;`
Having a data structure by its own is not really interesting, it needs at least a basic set of functions to use it, its own library.
_All the following functions will be added in the LIST\_DEFINE macro._


# No Need for Bob #
The first thing needed is a way to build lists. It would be possible of course to do something like:
```C
  LIST_DECLARE(int)
  // ...
  int_list *my_list = malloc (sizeof (int_list));
  my_list->head = 0;
  my_list->tail = malloc(sizeof (int_list));
  my_list->tail->head = 1;
  my_list->tail->tail = NULL;
  //...
```
Here 5 lines are needed to properly create a list of two integers. We can simplify the task of adding elements and creating lists with a simple function called `cons`.
```C
  type##_list *type##_list_cons(type elt, type##_list *list)          \
  {                                                                   \
    type##_list *res = malloc(sizeof (type##_list));                  \
    res->head = elt;                                                  \
    res->tail = list;                                                 \
    return res;                                                       \
  }                                                                   \
```
Okay, it looks like four lines to add one element and it is. Now we can create a two integers list the following way:
```C
  LIST_DECLARE(int)
  LIST_DEFINE(int)
  // ...
  int_list *my_list = int_list_cons(0, NULL);
  my_list->tail = int_list_cons(1, NULL);
  //...
```
This time, only two lines have been needed.
It has to be noticed that one should prefer adding elements to the head of the list instead of the tail. Always adding to the tail implies either writing something such as `list->tail->tail->/*...*/->tail->tail` and knowing the number of nodes yourself to access the last node or having a **O(n)** complexity every time an element is added with n the number of nodes in the list. On the other hand adding to the head does not need you to memorize the number of nodes and has a **O(1)** complexity.

If we can create a new list from another one and an element, we might also want to build one from a list and a set of element. This set of element will be a list to simplify things.
this is what concatenation is about: given two lists of element of the same type, it will create a new one with the second list put after the first one.
To `append` the two lists we will create the funtion as follow:
```C
  type##_list *type##_list_append(type##_list *l1, type##_list *l2)   \
  {                                                                   \
    if (!l1)                                                          \
      return l2;                                                      \
    type##_list *tmp = l1;                                            \
    while (tmp->tail)                                                 \
      tmp = tmp->tail;                                                \
    tmp->tail = l2;                                                   \
    return l1;                                                        \
  }                                                                   \
```
Concatenating two lists will have **O(n1)** complexity with n1 the number of nodes in the first list.

# Let it go #
As you should know, when memory is allocated, it must be freed when not needed anymore. As we created a constructing function adding one element to the head, we will write a destructing function freeing the node at the head:
```C
  type##_list *type##_list_dest(type##_list *list)                    \
  {                                                                   \
    type##_list *res = list->tail;                                    \
    free(list);                                                       \
    return res;                                                       \
  }                                                                   \
```
You may think "Urg, freeing each elements one after the other by hand, what a pain!!". This is true. Having to do that yourself is tiring, but we will see in the next article that it can be done easily on the whole list.

# Who is there? #
Now we are able to construct lists. What if one wants to access an element? There already are, `head` and `tail` in our structure. There is no need to explain that accessing the 42nd element would become tiring, and one would not want to try to access the 6785th one writing by himself all the `tail`s necessary.
To do this frequent task, the function `nth` will do the thing.
```C
  type type##_list_nth(type##_list *list, int pos)                    \
  {                                                                   \
    while (pos-- > 0)                                                 \
      list = list->tail;                                              \
    return list->head;                                                \
  }                                                                   \
```
Consistency leads us to create functions to access the head and the tail also
```C
  type type##_list_head(type##_list *list)                            \
  {                                                                   \
    return list->head;                                                \
  }                                                                   \
                                                                      \
  type##_list *type##_list_tail(type##_list *list)                    \
  {                                                                   \
    return list->tail;                                                \
  }                                                                   \
```
These three functions will have undefined behaviour if used with an invalid list.
Then `nth` function will also have undefined behaviours when used with a value less than 0 or more than the length of the list. Accessing the nth element of a list has **O(n)** complexity.


# The tip of the tail #
Being able to access any element of a list is a great thing. What if we want to access the last one? Currently we have no other mean than knowing the number of elements in a list in advance or looking for it by going through a list until meeting our "end sentinel" that is the NULL pointer.
As it is used often, the function computing the number of elements in a list should be written.
```C
  int type##_list_length(type##_list *list)                           \
  {                                                                   \
    type##_list *tmp = list;                                          \
    unsigned length = 0;                                              \
    while (tmp)                                                       \
    {                                                                 \
      tmp = tmp->tail;                                                \
      ++length;                                                       \
    }                                                                 \
    return length;                                                    \
  }                                                                   \
```
Here is the `length` function, doing just what it is intended to: returning the number of element in a list. As you can notice, the list should be NULL terminated in order to be properly processed, otherwise undefined behaviour will knock at the door.
It is to be noted that if the length of a list will often be needed, recording it in a variable would be more worthy than calling the **O(n)** function `length` over and over again with n the number of elements.

# Where is it at? #
Knowing there can be something somewhere in a list and what it is can be helpful, the opposite also. Some times we may need to know if an element is in a list and where it is.
An easy way to do that is to use the `pos` function.
```C
  int type##_list_pos(type##_list *list, type elt)                    \
  {                                                                   \
    unsigned pos = 0;                                                 \
    while (list && list->head != elt)                                 \
    {                                                                 \
      list = list->tail;                                              \
      ++pos;                                                          \
    }                                                                 \
    return list ? (int) pos : -1;                                     \
  }                                                                   \
```
Again, this function will need a NULL pointer at the end of the list to work properly.
If the element exists, th position of its first occurence only is given, otherwise -1 is returned.


# Turn around #
At the beginning we said that one should build a list by pushing the elements to the head as it is easier and faster to do. If you ever need to add to the tail, instead of looking for the last node there still is a solution: adding to the head. It is possible to add to the head after reversing the list. That way, the process of adding does not change.
Here is how `rev` works:
```C
  type##_list *type##_list_rev(type##_list *list)                     \
  {                                                                   \
    if (!list)                                                        \
      return list;                                                    \
    type##_list *next = list->tail;                                   \
    list->tail = NULL;                                                \
    while (next)                                                      \
    {                                                                 \
      type##_list *tmp = next->tail;                                  \
      next->tail = list;                                              \
      list = next;                                                    \
      next = tmp;                                                     \
    }                                                                 \
    return list;                                                      \
  }                                                                   \
```
This reverse the list in place which means the previous pointer the the head is now a pointer to the last node.
If you started building your list by adding the element at the tail, it can be useful to rethink it by adding them to the head and then reversing the list. Instead of **O(n)** complexity each time an element is added with n the number of nodes in the list, it gives us this complexity once and only once when the list is reversed with **O(1)** complexity at each insertion.


# To be continued #

To conclude this project's first step, we will have to ensure there is no major issue about using it. Consistency has been kept suring the whole process of writing, with names following the same pattern: *type*\_list\_*function\_name*. The functions are all basically tested to check if the expected behaviour is followed. The last thing is organising code and for that we will simply separate the structure definition and functions declarations from the functions definitions.
Two little helpers will be defined:
+ the macro `LIST_TYPE` that takes a type as parameter and is replaced by `type##_list`
+ the macro `LIST_FUN` that takes a type and a function name (as fun) and is replaced by `type##_list_##fun`
