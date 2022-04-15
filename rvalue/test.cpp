#include <iostream>

using namespace std;

class A
{
 public:
  A()
  {
    cout << "construct" << endl;
  }
  A(const A& a)
  {
    cout << "copy" << endl;
  }
  A(A&& a)
  {
    cout << "move" << endl;
  }
};

void func1(const A a)
{
  cout << "==== const A ====" << endl;
}

void func2(const A&& a)
{
  cout << "==== const A&& ====" << endl;
}

int main()
{
  A a;
  func1(a);
  func1(std::move(a));
  return 0;
}