#include <iostream>


class B                     // abstract base class
{
    public:
    virtual void f() = 0;   // pure virtual functions
    virtual void g() = 0;
};

class D1 : public B
{
    public:
    void f() override { std::cout << "D1's f() overriding B's pure virtual function\n"; }
    void g() override { std::cout << "D1's g() overriding B's pure virtual function\n"; }
};

class D2 : public B
{
    public:
    void f() override;
    // no g()
};

class D3 : public D2
{
    public:
    void g() override;
};

int main()
{
    // B b;    // compiler error: "Object of abstract class type "B" is not allowed

    D1 d1;     // all good!
    d1.f();
    d1.g();

    // D2 d2;      // D2 is STILL abstract b/c all functions must be overridden

    D3 d3;      // all good because it finishes off overriding B's functions.

    return 0;
}