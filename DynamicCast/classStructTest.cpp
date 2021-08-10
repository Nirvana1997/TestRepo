#include <iostream>

using namespace std;

class X
{
    public:
        X()
        {
            mX = 101;
        }
	virtual void vfunc()
        {
            cout << "X::vfunc()" << endl;
        }

    private:
        int mX;
};
 
class XX : public X
{
    public:
        XX(): X()
        {
            mXX = 1001;
        }
	virtual void vfunc()
        {
            cout << "XX::vfunc()" << endl;
        }

    private:
        int mXX;
};

typedef void (*FuncPtr)();
int main()
{
    XX xx;
    FuncPtr func;
    char *p = (char*)&xx;// 此处声明为char*的原因主要是为了+sizeof(xx)时加对应n个字节，从而方便获取n个字节后的地址
    // 获得虚函数表的地址
    int **vtbl = (int**)*(int**)p;
    // 输出虚函数表的地址，即vptr的值
    cout << vtbl << endl;
    // 获得type_info对象的指针，并调用其name成员函数
    cout << "\t[-1]: " << (vtbl[-1]) << " -> "
        << ((type_info*)(vtbl[-1]))->name() << endl;
    // 调用第一个virtual函数
    cout << "\t[0]: " << vtbl[0] << " -> ";
    func = (FuncPtr)vtbl[0];
    func();
    // 输出基类的成员变量的值
    p += sizeof(int**);
    cout << *(int*)p << endl;
    // 输出派生类的成员变量的值
    p += sizeof(int);
    cout << *(int*)p << endl;
    return 0;
}