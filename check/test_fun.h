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

 #define BUILD_TO_VOID(type)\
   void type##_to_void(type elt)\
   {\
     if (elt == elt)\
       return;\
   }\

 #define TO_VOID(type) type##_to_void

/// Testing rev
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



/// Tests definitions
 #define TEST_FUNC_DEF(type1, type2)\
FUNC_DECLARE(type1, type2)\
FUNC_DEFINE(type1, type2)\
BUILD_CAST(type1, type2)\
TEST_MAP_DEF(type1, type2)\


/// Launch all tests
 #define TEST_FUNC(type1, type2)\
TEST_MAP(type1, type2)

#endif /* !TEST_FUN_H */
