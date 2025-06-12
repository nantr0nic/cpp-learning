#include <iostream>

class A 
{
public:
    virtual void func1() = 0;
    virtual void func2() const { std::cout << "This is A's func2()\n"; }
    virtual void func3() const { std::cout << "This is A's func3()\n"; }
    virtual void func4() const { std::cout << "This is A's func4()\n"; }
};

class B : public A 
{
public:
    void func1() override { std::cout << "This is B's override of func1()\n"; }
    // let's inherit func2 from A
    void func3() const override { std::cout << "This is B's override of A's func3()\n"; }
};

class C : public B 
{
public:
    // let's inherit func1 from B
    // let's inherit func2 from A
    void func3() const override { std::cout << "This is C's override of B's func3()\n"; }
    virtual void func4() const { std::cout << "This is C's func4()\n"; }    // not in A or B
};

class D : public C
{
public:
    // let's inherit func1 from C which is inheriting from B ( so vtbl will point to B::func1() )
    // let's inherit func2 from A 
    // let's inherit func3 from B
    void func4() const override { std::cout << "This is D's override of C's func4()\n"; }
};

int main()
{
    D d;
    d.func1();
    d.func2();
    d.func3();
    d.func4();

    /*
    In this example, D's vtbl has pointers to functions in A, B, C, and D (itself).
    */

    return 0;
}