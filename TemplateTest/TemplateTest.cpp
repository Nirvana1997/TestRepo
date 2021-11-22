#include "TemplateTest.h"

#include <iostream>

template <class T>
void print(T t)
{
  std::cout << typeid(t).name() << std::endl;
}
