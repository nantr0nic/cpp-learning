#include <iostream>

class A
{
public:
    virtual void f() const { std::cout << "This is A's f()\n"; }
    void g() const { std::cout << "This is A's g()\n"; }
    virtual void h() = 0;
};

class B : public A 
{
public:
    void f() const override { std::cout << "This is B's f()\n"; }
    void g() const { std::cout << "This is B's g()\n"; }
    void h() override { std::cout << "This is a PVF from A to B\n"; }
};

void call(A& a)
{
    a.f();
    a.g();
    a.h();
}

int main()
{
    B b;
    A& c {b}; // indrection - static type is A, dynamic type is B

    call(b);
    std::cout << "---------\n";
    c.g();  // static dispatch of A::g() -- determined at compile time, not in vtbl
    //call(c);

    return 0;
}
