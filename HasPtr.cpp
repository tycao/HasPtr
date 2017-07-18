#include <iostream>
#include <string>

using namespace std;

class HasPtr
{
public:
    HasPtr() = default;
    HasPtr(const HasPtr& p) : ps(new std::string(*p.ps)), i(0) { }
    HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr& operator=(const HasPtr&);
    HasPtr& operator=(const string&);
    std::string& operator*();
    ~HasPtr();
private:
    std::string *ps;
    int i = 0;
};

inline
HasPtr::~HasPtr() { delete ps; }
inline
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    std::string *newps = new std::string(*rhs.ps);
    delete this->ps;
    ps = newps;
    this->i = rhs.i;
    return *this;
}
inline
HasPtr& HasPtr::operator=(const std::string& str)
{
    *this->ps = str;
    return *this;
}
inline
std::string& HasPtr::operator*()
{
    return *ps;
}
int main()
{
    HasPtr h("hi, Mom!");
    HasPtr h2(h);

    HasPtr h3 = h;
    h2 = "hi dad!";
    h3 = "hi son!";
    cout << "h: " << *h << endl;
    cout << "h2: " << *h2 << endl;
    cout << "h3: " << *h3 << endl;

    return 0;
}
