#include <iostream>

using namespace std;

class HasPtr
{
public:
    // 构造函数分配新的string和新的计数器，将计数器置为1
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
    // 拷贝构造函数拷贝所有三个数据成员，并递增计数器
    HasPtr(const HasPtr& p) : ps(p.ps), i(p.i), use(p.use) { ++*use; }
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();
private:
    std::string *ps;
    int i;
    std::size_t *use;   // 用来记录有多少个对象共享*ps的成员
};
inline HasPtr::~HasPtr()
{
    if (--*use == 0)    // 若引用计数变为0
    {
        cout << "~HasPtr析构函数被启动了。。。" << endl;
        delete ps;  // 释放string的内存
        delete use; // 释放计数器的内存
    }
}
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    ++*rhs.use; // 递增右侧运算对象的引用计数
    if (--*use == 0)
    {
        cout << "拷贝赋值运算符被启动了。。。" << endl;
        delete ps;
        delete use;
    }
    ps = rhs.ps;
    use = rhs.use;
    i = rhs.i;
    return *this;
}

int main()
{
    HasPtr p1 = string("a an the");
    {
        HasPtr p2 = p1;
    }
    HasPtr p3("about");
    p3 = p1;
    return 0;
}
