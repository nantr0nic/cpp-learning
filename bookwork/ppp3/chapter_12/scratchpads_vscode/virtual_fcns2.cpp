#include <iostream>

struct B
{
    virtual void f() const { std::cout << "B::f "; }
    virtual void g() { std::cout << "B::g "; }    // not virtual
};

struct D : B
{
    void f() const override { std::cout << "D::f "; }    // This will override B's f()
    void g() override { std::cout << "D::g "; }
};

struct DD : D
{
    void f() const override { std::cout << "DD::f "; }         // This will not because not const
    void g() const { std::cout << "DD::g "; }   // (must be the same as base)
};

void call(B& b)
// a D is a kind of B, so call() can accept a D
// a DD is a kind of D and a D is a kind of B, so call() can accept a DD
{
    b.f();
    b.g();
    std::cout << " | ";
}

int main()
{
    B b;
    D d;
    DD dd;
    const DD dd2;
    std::cout << "Trying const first\n";
    dd2.f();
    dd2.g();
    call(dd2); // look at the instructive compiler error!

    call(b);
    call(d);
    call(dd);
    std::cout << " | ";
    b.f();
    b.g();
    std::cout << " | ";
    d.f();
    d.g();
    std::cout << " | ";
    dd.f();
    dd.g();
}