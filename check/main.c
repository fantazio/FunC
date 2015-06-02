#include <assert.h>

#include "../func/func.h"
#include "../func/list.c"

#define TEST_LIST_REV(type, elt)\
    LIST_DEFINE(type)\
  void test_##type##_list_rev(void)\
{\
  LIST_TYPE(type) *list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  assert(LIST_FUN(type, rev)(LIST_FUN(type, rev)(list)) == list);\
  assert(LIST_FUN(type, length)(LIST_FUN(type, rev)(list))\
        == LIST_FUN(type, length)(list));\
}\

TEST_LIST_REV(int, 0)
TEST_LIST_REV(double, 0.)
TEST_LIST_REV(char, ' ')
TEST_LIST_REV(unsigned, 0)

void test_list_rev(void)
{
  //assert(LIST_FUN(char, rev)(NULL) == NULL);
  test_int_list_rev();
  test_double_list_rev();
  test_char_list_rev();
  test_unsigned_list_rev();
}

int main(int argc, char *argv[])
{
  test_list_rev();
  return 0;
}
