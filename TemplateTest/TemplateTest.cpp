#include "TemplateTest.h"

#include <iostream>

using namespace std;

template <class T>
void print(T t)
{
  cout << typeid(t).name() << endl;
}

int main()
{
  A a;
  a.print(a);
  return 0;
}