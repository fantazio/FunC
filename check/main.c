#include <assert.h>

#include "../func/func.h"
#include "../func/list.c"

#define TEST_LIST_REV(type, elt)\
void test_list(void)\
{\
  LIST_DEFINE(type)\
  LIST_TYPE(type) *list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  list = LIST_FUN(type, cons)(elt, list);\
  assert(LIST_FUN(type, rev)(LIST_FUN(type, rev)(list)) == list);\
  assert(LIST_FUN(type, length)(LIST_FUN(type, rev)(list)) == list);\
}\

void test_list_rev(void)
{
  LIST_DEFINE(char);
  assert(LIST_FUN(char, rev)(NULL) == NULL);
  TEST_LIST_REV(int, 0);
  TEST_LIST_REV(char, ' ');
  TEST_LIST_REV(double, 0.);
  TEST_LIST_REV(uint, 0);
}

int main(int argc, char *argv[])
{
  test_list_rev();
  return 0;
}
