#ifndef TEST_FUN_H
#define TEST_FUN_H

 #include <assert.h>

 #include "test_list.h"
 #include "../func/func.h"


 #define BUILD_CAST(type1, type2)\
   type2 type1##_##type2##_cast(type1 elt)\
   {\
     return (type2) elt;\
   }\

 #define MY_CAST(type1, type2) type1##_##type2##_cast
 
 #define BUILD_ADDR(type1, type2)\
   LIST_TYPE(long) * type1##_##type2##_addr(LIST_TYPE(type1) *list)\
   {\
  if (!list)\
    return NULL;\
  LIST_TYPE(long) *res= malloc(sizeof (LIST_TYPE(long)));\
  LIST_TYPE(long) *tmp = res;\
  do\
  {\
    tmp->head = (long) &(list->head);\
    tmp = list->tail ? (tmp->tail = malloc(sizeof (LIST_TYPE(long)))) : tmp;\
  } while ((list = list->tail));\
  \
  return res;\
   }\


 #define BUILD_INC(type1, type2)\
   void type1##_##type2##_inc(long elt)\
   {\
     type1 *tmp = (type1*)elt;\
     *tmp = *tmp + 1;\
   }\

 #define INC(type1, type2) type1##_##type2##_inc

/// Testing map
 #define TEST_MAP_DEF(type1, type2)\
  void test_##type1##_##type2##_map(void)\
{\
  LIST_TYPE(type1) *list = build_##type1##_list();\
  LIST_TYPE(type2) *mapped =\
    FUNC_MAP(type1, type2)(type1##_##type2##_cast, list);\
  int length1 = LIST_FUN(type1, length)(list);\
  assert(length1 == LIST_FUN(type2, length)(mapped));\
  for (int i = 0; i < length1; ++i)\
    assert(MY_CAST(type1, type2)(LIST_FUN(type1, nth)(list, i))\
      == LIST_FUN(type2, nth)(mapped, i));\
  assert(FUNC_MAP(type1, type2)(type1##_##type2##_cast, NULL) == NULL);\
}\


 #define TEST_MAP(type1, type2)\
  test_##type1##_##type2##_map();


/// Testing iter
 #define TEST_ITER_DEF(type1, type2)\
  void test_##type1##_##type2##_iter(void)\
{\
  LIST_TYPE(type1) *list = build_##type1##_list();\
  LIST_TYPE(type1) *copy =\
    FUNC_MAP(type1, type1)(type1##_##type1##_cast, list);\
  LIST_TYPE(long) *point_copy = type1##_##type2##_addr(list);\
  FUNC_ITER(long)(INC(type1, long), point_copy);\
  int length1 = LIST_FUN(type1, length)(list);\
  assert(length1 == LIST_FUN(type1, length)(copy));\
  for (int i = 0; i < length1; ++i)\
    assert(LIST_FUN(type1, nth)(list, i) - 1\
      == LIST_FUN(type1, nth)(copy, i));\
}\


 #define TEST_ITER(type1, type2)\
  test_##type1##_##type2##_iter();

/// Tests definitions
 #define TEST_FUNC_DEF(type1, type2)\
FUNC_DECLARE2(type1, type2)\
FUNC_DEFINE2(type1, type2)\
BUILD_CAST(type1, type2)\
TEST_MAP_DEF(type1, type2)\
BUILD_INC(type1, type2)\
BUILD_ADDR(type1, type2)\
TEST_ITER_DEF(type1, type2)\

 #define TEST_FUNC_DEF1(type)\
FUNC_DECLARE(type)\
FUNC_DEFINE(type)\
FUNC_DECLARE2(type, type)\
FUNC_DEFINE2(type, type)\
BUILD_CAST(type, type)\
TEST_MAP_DEF(type, type)\
BUILD_INC(type, type)\
BUILD_ADDR(type, type)\

/// Launch all tests
 #define TEST_FUNC(type1, type2)\
TEST_MAP(type1, type2)\
TEST_ITER(type1, type2)\

 #define TEST_FUNC1(type)\
TEST_MAP(type, type)\

#endif /* !TEST_FUN_H */
