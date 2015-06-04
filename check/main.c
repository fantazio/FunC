#include "test_fun.h"

  TEST_LIST_DEF(int, 0)
TEST_LIST_DEF(double, 0.)
  TEST_LIST_DEF(char, '0')
TEST_LIST_DEF(unsigned, 0)

  TEST_FUNC_DEF(int, int)
  TEST_FUNC_DEF(int, double)
  TEST_FUNC_DEF(int, char)
  TEST_FUNC_DEF(int, unsigned)
  TEST_FUNC_DEF(double, int)
  TEST_FUNC_DEF(double, double)
  TEST_FUNC_DEF(double, char)
  TEST_FUNC_DEF(double, unsigned)
  TEST_FUNC_DEF(char, int)
  TEST_FUNC_DEF(char, double)
  TEST_FUNC_DEF(char, char)
  TEST_FUNC_DEF(char, unsigned)
  TEST_FUNC_DEF(unsigned, int)
  TEST_FUNC_DEF(unsigned, double)
  TEST_FUNC_DEF(unsigned, char)
TEST_FUNC_DEF(unsigned, unsigned)


int main(void)
{
  TEST_LIST(int, 4);
  TEST_LIST(double, 4.);
  TEST_LIST(char, '4');
  TEST_LIST(unsigned, 4);
  TEST_FUNC(int, int)
    TEST_FUNC(int, double)
    TEST_FUNC(int, char)
    TEST_FUNC(int, unsigned)
    TEST_FUNC(double, int)
    TEST_FUNC(double, double)
    TEST_FUNC(double, char)
    TEST_FUNC(double, unsigned)
    TEST_FUNC(char, int)
    TEST_FUNC(char, double)
    TEST_FUNC(char, char)
    TEST_FUNC(char, unsigned)
    TEST_FUNC(unsigned, int)
    TEST_FUNC(unsigned, double)
    TEST_FUNC(unsigned, char)
    TEST_FUNC(unsigned, unsigned)
    return 0;
}
