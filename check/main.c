#include "test_list.h"

TEST_LIST_DEF(int, 0)
TEST_LIST_DEF(double, 0.)
  TEST_LIST_DEF(char, '0')
TEST_LIST_DEF(unsigned, 0)


int main(void)
{
  TEST_LIST(int, 4);
  TEST_LIST(double, 4.);
  TEST_LIST(char, '4');
  TEST_LIST(unsigned, 4);
  return 0;
}
