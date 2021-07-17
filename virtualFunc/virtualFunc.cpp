#include <iostream>

using namespace std;

class Base
{
    public:
    Base()
    {
        cout << "base con" << endl;
    }
    virtual ~Base()
    {
        test();
    }
    
    void test()
    {
        virtualFunc();
    }

    virtual void virtualFunc() = 0;
};

class Derived : public Base
{
    public:
    Derived()
    {
        cout << "derive con" << endl;
    }
    virtual ~Derived() = default;

    virtual void virtualFunc() override
    {
        cout << "Derived destruct" << endl;
    }
};

int main()
{
    Derived* pClass = new Derived();
    delete pClass;
    return 0;
}