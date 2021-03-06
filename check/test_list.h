#ifndef TEST_LIST_H
#define TEST_LIST_H

 #include <assert.h>
 #include <stdlib.h>

 #include "../func/list.h"


/// Lists creation
 #define BUILD_LIST(type, elt)\
  LIST_TYPE(type) *build_##type##_list(void)\
{\
  LIST_TYPE(type) *list = LIST_FUN(type, cons)(elt, NULL);\
  list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  return list;\
}



/// Testing rev
 #define TEST_LIST_REV(type)\
  void test_##type##_list_rev(void)\
{\
  LIST_TYPE(type) *list = build_##type##_list();\
  assert(LIST_FUN(type, rev)(LIST_FUN(type, rev)(list)) == list);\
  assert(LIST_FUN(type, length)(list)\
      == LIST_FUN(type, length)(LIST_FUN(type, rev)(list)));\
}


 #define LIST_REV(type)\
  assert(!LIST_FUN(type, rev)(NULL));\
test_##type##_list_rev();


/// Testing cons
 #define TEST_LIST_CONS(type)\
  void test_##type##_list_cons(LIST_TYPE(type) *list, type elt)\
{\
  LIST_TYPE(type) *l = LIST_FUN(type, cons)(elt, list);\
  assert(l->tail == list);\
  assert(l->head == elt);\
  if (list)\
  {\
    assert(l->tail->head == list->head);\
    assert(l->tail->tail == list->tail);\
  }\
  assert(LIST_FUN(type, length)(l) == LIST_FUN(type, length)(list) + 1);\
}

 #define LIST_CONS(type, elt)\
  test_##type##_list_cons(NULL, elt);\
test_##type##_list_cons(build_##type##_list(), elt);


/// Testing length
 #define TEST_LIST_LENGTH(type)\
  void test_##type##_list_length(LIST_TYPE(type) *list, int size)\
{\
  if (list)\
  {\
    LIST_TYPE(type) *l = LIST_FUN(type, cons)(list->head, list);\
    assert(LIST_FUN(type, length)(l) == LIST_FUN(type, length)(list) + 1);\
    assert(LIST_FUN(type, length)(list)\
        == LIST_FUN(type, length)(list->tail) + 1);\
    assert(LIST_FUN(type, length)(list) == size);\
  }\
  else\
  assert(LIST_FUN(type, length)(list) == 0);\
}\

 #define LIST_LENGTH(type, elt)\
  test_##type##_list_length(NULL, elt);\
test_##type##_list_length(build_##type##_list(), elt);


/// Testing head
 #define TEST_LIST_HEAD(type)\
  void test_##type##_list_head(LIST_TYPE(type) *list)\
{\
  if (list)\
  {\
    LIST_TYPE(type) *l = LIST_FUN(type, cons)(list->head, list);\
    assert(LIST_FUN(type, head)(l) == l->head);\
    assert(LIST_FUN(type, head)(l) == list->head);\
    assert(LIST_FUN(type, head)(l) == LIST_FUN(type, head)(list));\
    assert(LIST_FUN(type, head)(l->tail) == LIST_FUN(type, head)(list));\
  }\
}\

 #define LIST_HEAD(type)\
  test_##type##_list_head(NULL);\
test_##type##_list_head(build_##type##_list());


/// Testing tail
 #define TEST_LIST_TAIL(type)\
  void test_##type##_list_tail(LIST_TYPE(type) *list)\
{\
  if (list)\
  {\
    LIST_TYPE(type) *l = LIST_FUN(type, cons)(list->head, list);\
    assert(LIST_FUN(type, tail)(l) == l->tail);\
    assert(LIST_FUN(type, tail) (LIST_FUN(type, tail)(l)) == list->tail);\
    assert(LIST_FUN(type, tail) (l->tail) == list->tail);\
    assert(LIST_FUN(type, tail) (l->tail) == LIST_FUN(type, tail)(list));\
    assert(LIST_FUN(type, tail)(l) == list);\
    assert(LIST_FUN(type, tail)(list) == list->tail);\
  }\
}\

 #define LIST_TAIL(type)\
  test_##type##_list_tail(NULL);\
test_##type##_list_tail(build_##type##_list());


/// Testing append
 #define TEST_LIST_APPEND(type)\
  void test_##type##_list_append(LIST_TYPE(type) *l1, LIST_TYPE(type) *l2)\
{\
  const int length1 = LIST_FUN(type, length)(l1);\
  const int length2 = LIST_FUN(type, length)(l2);\
  assert(length1 + length2\
      == LIST_FUN(type, length)(LIST_FUN(type, append) (l1, l2)));\
  if (l1)\
  assert(LIST_FUN(type, append)(l1, l2) == l1);\
  else\
  assert(LIST_FUN(type, append)(l1, l2) == l2);\
}\

 #define LIST_APPEND(type)\
  test_##type##_list_append(NULL, NULL);\
test_##type##_list_append(build_##type##_list(), NULL);\
test_##type##_list_append(NULL, build_##type##_list());\
test_##type##_list_append(build_##type##_list(), build_##type##_list());


/// Testing nth
 #define TEST_LIST_NTH(type)\
  void test_##type##_list_nth(LIST_TYPE(type) *l, type e)\
{\
  assert(e == LIST_FUN(type, nth)(LIST_FUN(type, cons) (e, l), 0));\
  if (l)\
  {\
    assert(l->head == LIST_FUN(type, nth)(l, 0));\
    assert(l->head == LIST_FUN(type, nth)(LIST_FUN(type, cons) (e, l), 1));\
    assert(LIST_FUN(type, nth)\
        (LIST_FUN(type, cons)(e, LIST_FUN(type, cons(e, l))), 1)\
        == LIST_FUN(type, nth)(LIST_FUN(type, cons) (e, l), 0));\
  }\
}\

 #define LIST_NTH(type, elt)\
  test_##type##_list_nth(NULL, elt);\
test_##type##_list_nth(build_##type##_list(), elt);\


/// Testing pos
 #define TEST_LIST_POS(type)\
  void test_##type##_list_pos(LIST_TYPE(type) *l, type e)\
{\
  assert(0 == LIST_FUN(type, pos)(LIST_FUN(type, cons) (e, l), e));\
  if (l)\
  {\
    assert(0 == LIST_FUN(type, pos)(l, l->head));\
    assert(1 == LIST_FUN(type, pos)(LIST_FUN(type, cons) (e, l), l->head));\
    assert(LIST_FUN(type, pos)\
        (LIST_FUN(type, cons)(e, LIST_FUN(type, cons(e, l))), e)\
        == LIST_FUN(type, pos)(LIST_FUN(type, cons) (e, l), e));\
    l = LIST_FUN(type, cons)(e, l);\
    assert(1 >= LIST_FUN(type, pos)(l, LIST_FUN(type, nth)(l, 1)));\
  }\
}\

 #define LIST_POS(type, elt)\
  test_##type##_list_pos(NULL, elt);\
test_##type##_list_pos(build_##type##_list(), elt);\



/// Tests definitions
 #define TEST_LIST_DEF(type, elt)\
  LIST_DECLARE(type)\
LIST_DEFINE(type)\
BUILD_LIST(type, elt)\
TEST_LIST_CONS(type)\
TEST_LIST_LENGTH(type)\
TEST_LIST_HEAD(type)\
TEST_LIST_TAIL(type)\
TEST_LIST_REV(type)\
TEST_LIST_APPEND(type)\
TEST_LIST_NTH(type)\
TEST_LIST_POS(type)\


/// Launch all tests
 #define TEST_LIST(type, elt)\
  LIST_CONS(type, elt)\
LIST_LENGTH(type, 5)\
LIST_HEAD(type)\
LIST_TAIL(type)\
LIST_REV(type)\
LIST_APPEND(type)\
LIST_NTH(type, elt)\
LIST_POS(type, elt)

#endif /* !TEST_LIST_H */
