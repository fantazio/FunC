#include <assert.h>

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



/// Testing reverse
#define TEST_LIST_REV(type)\
  void test_##type##_list_rev(void)\
{\
  LIST_TYPE(type) *list = build_##type##_list();\
  assert(LIST_FUN(type, rev)(LIST_FUN(type, rev)(list)) == list);\
  assert(LIST_FUN(type, length)(list = LIST_FUN(type, rev)(list))\
      == LIST_FUN(type, length)(list));\
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


/// Testing cons
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



/// Tests definitions
#define TEST_LIST_DEF(type, elt)\
  LIST_DECLARE(type)\
LIST_DEFINE(type)\
BUILD_LIST(type, elt)\
TEST_LIST_CONS(type)\
TEST_LIST_LENGTH(type)\
TEST_LIST_REV(type)

  TEST_LIST_DEF(int, 0)
TEST_LIST_DEF(double, 0.)
  TEST_LIST_DEF(char, '0')
TEST_LIST_DEF(unsigned, 0)

  /// Launch all tests
#define TEST_LIST(type, elt)\
    LIST_CONS(type, elt)\
  LIST_LENGTH(type, 5)\
  LIST_REV(type)


int main(int argc, char *argv[])
{
  TEST_LIST(int, 4);
  TEST_LIST(double, 4.);
  TEST_LIST(char, '4');
  TEST_LIST(unsigned, 4);
  return 0;
}
