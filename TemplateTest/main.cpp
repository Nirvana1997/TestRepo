#include "TemplateTest.h"

extern template void print<int>(int);

int main()
{
  int i = 0;
  print(i);
  return 0;
}