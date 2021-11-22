#include <iostream>

using namespace std;

int main()
{
  std::string s("01234567890123456789012");
  std::string s2("0123456789012345678901");
  std::string s3(s);
  cout << "s: size:" << s.size() << " ";
  cout << "distance:" << ((long)s.c_str() - (long)(&s)) << endl;
  cout << "s2: size:" << s2.size() << " ";
  cout << "distance:" << ((long)s2.c_str() - (long)(&s2)) << endl;
  cout << "s s2:" << ((long)s.c_str() - (long)s3.c_str()) << endl;
}