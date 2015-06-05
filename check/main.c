#include "test_fun.h"

  TEST_LIST_DEF(long, 0)
  TEST_LIST_DEF(int, 0)
TEST_LIST_DEF(double, 0.)
  TEST_LIST_DEF(char, '0')
TEST_LIST_DEF(unsigned, 0)

  TEST_FUNC_DEF1(long)
  TEST_FUNC_DEF(long, int)
  TEST_FUNC_DEF(long, double)
  TEST_FUNC_DEF(long, char)
  TEST_FUNC_DEF(long, unsigned)
  TEST_FUNC_DEF1(int)
  TEST_FUNC_DEF(int, long)
  TEST_FUNC_DEF(int, double)
  TEST_FUNC_DEF(int, char)
  TEST_FUNC_DEF(int, unsigned)
  TEST_FUNC_DEF1(double)
  TEST_FUNC_DEF(double, long)
  TEST_FUNC_DEF(double, int)
  TEST_FUNC_DEF(double, char)
  TEST_FUNC_DEF(double, unsigned)
  TEST_FUNC_DEF1(char)
  TEST_FUNC_DEF(char, long)
  TEST_FUNC_DEF(char, int)
  TEST_FUNC_DEF(char, double)
  TEST_FUNC_DEF(char, unsigned)
TEST_FUNC_DEF1(unsigned)
  TEST_FUNC_DEF(unsigned, long)
  TEST_FUNC_DEF(unsigned, int)
  TEST_FUNC_DEF(unsigned, double)
  TEST_FUNC_DEF(unsigned, char)


int main(void)
{
  TEST_LIST(long, 4);
  TEST_LIST(int, 4);
  TEST_LIST(double, 4.);
  TEST_LIST(char, '4');
  TEST_LIST(unsigned, 4);
    TEST_FUNC1(long)
    TEST_FUNC(long, int)
    TEST_FUNC(long, double)
    TEST_FUNC(long, char)
    TEST_FUNC(long, unsigned)
  TEST_FUNC1(int)
    TEST_FUNC(int, long)
    TEST_FUNC(int, double)
    TEST_FUNC(int, char)
    TEST_FUNC(int, unsigned)
    TEST_FUNC1(double)
    TEST_FUNC(double, long)
    TEST_FUNC(double, int)
    TEST_FUNC(double, char)
    TEST_FUNC(double, unsigned)
    TEST_FUNC1(char)
    TEST_FUNC(char, long)
    TEST_FUNC(char, int)
    TEST_FUNC(char, double)
    TEST_FUNC(char, unsigned)
    TEST_FUNC1(unsigned)
    TEST_FUNC(unsigned, long)
    TEST_FUNC(unsigned, int)
    TEST_FUNC(unsigned, double)
    TEST_FUNC(unsigned, char)
    return 0;
}
