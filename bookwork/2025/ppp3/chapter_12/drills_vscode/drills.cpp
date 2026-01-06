#include <iostream>
#include <string>

class B1
{
    public:
    virtual void vf() const { std::cout << " B1::vf() \n"; }
    void f() const { std::cout << " B1::f() \n"; }
    virtual void pvf() const = 0;     // pure virtual function
};

class D1 : public B1
{
    public:
    void vf() const override { std::cout << " D1::vf() \n"; }
    void f() const { std::cout << " D1::f() \n"; }
    // void pvf() const override { std::cout << " D1::pvf() \n"; }
};

class D2 : public D1
{
    public:
    void pvf() const override { std::cout << " D2::pvf() \n"; }
};

class B2
{
    public:
    virtual void pvf() const = 0;
};

class D21 : public B2
{
    public:
    void pvf() const override { std::cout << s_value << "\n"; }

    private:
    std::string s_value {"D21 String!"};
};

class D22 : public B2
{
    public:
    void pvf() const override { std::cout << "D22 int is: " << i_value << "\n"; }

    private:
    int i_value {55};
};

void f(const B2& b2)
{
    b2.pvf();
}

/* Drill 4 explanation:

d1ish is a REFERENCE to B1 but it is BOUND to a D1 object (d1) therefore
d1ish's "static type" (the type specified in the declaration) is B1 but 
its "dynamic type" (the type of the actual object it refers to) is D1
Because vf() is virtual (in the vtbl) C++ uses the dynamic type to choose
    the function, whereas because f() is non-virtual (in B1), C++ uses the static
    type to choose the function (B1::f() in this case).

"This is because only virtual functions use dynamic dispatch (the actual 
object’s type). Non-virtual functions use the type of the reference or pointer."

*/

/* Drill 5 explanation:
Because a pure virtual function is declared in B1, it can no longer be 
instantiated as its own object but the virtual functions it defines can 
still be overriden / accessed by its derived classes. Because D1 is derived
from B1, B1 can still act as a static type for d1ish because there is still 
no "actual object" that is B1 (which would contradict it being an abstract class). 
So, d1ish.f() can still return B1::f() without instantiating an actual B1 object.
*/
int main()
{
    // vvv no longer works after drill 5
    // B1 b1;
    // b1.vf();
    // b1.f();

    // vvv no longer works after drill 6
    // D1 d1;
    // d1.vf();
    // d1.f();
    // B1& d1ish {d1};
    // // dynamic dispatch
    // d1ish.vf();     // virtual, uses dynamic type (D1 object) - the actual object it refers to
    // // static dispatch
    // d1ish.f();      // non-virtual, uses the static type (B1) - the type used in declaration

    D2 d2;
    d2.f();
    d2.vf();
    d2.pvf();

    B1& d2ish {d2};
    d2ish.f();
    d2ish.vf();
    d2ish.pvf();

    D21 d21;
    D22 d22;

    f(d21);
    f(d22);

    return 0;
}