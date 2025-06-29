#include <iostream>
#include <string>

class A {
public:
    A() { std::cout << "A's constructor called!\n"; }
    virtual ~A() { std::cout << "A's destructor called!\n"; }
    void set_string(const std::string& s) { A_string = s;  std::cout << "&A_string is " << &A_string << '\n'; }
    
private:
    std::string A_string {};
};

class B : public A {
public:
    B() { std::cout << "B's constructor called!\n"; }
    ~B() { std::cout << "B's destructor called!\n"; }
    void set_int(int* q) {
        std::cout << "set_int called!\n";
        p = q;
        std::cout << "q is: " << q << "\n&q is: " << &q << '\n'; 
        std::cout << "p is: " << p << "\n&p is: " << &p << '\n'; 
    }
    void set_int_ref(int*& q) {
        std::cout << "set_int_ref called!\n";
        p = q;
        std::cout << "q is: " << q << "\n&q is: " << &q << '\n';
        std::cout << "^^^ &q will be the same as &qq ^^^\n"; 
        std::cout << "p is: " << p << "\n&p is: " << &p << '\n'; 
    }

private:
    int* p;
};

class C : public B {
public:
    C() { std::cout << "C's constructor called!\n"; }
    ~C() { std::cout << "C's destructor called!\n"; }
    void set_ulongs(unsigned long n) {
        numbers = new unsigned long[n];
        for (unsigned long i = 0; i < n; ++i)
        {
            numbers[i] = n;
            std::cout << "numbers[" << i << "] address is " << &numbers[i] << '\n';
        }
    }

private:
    unsigned long* numbers;
};

int main()
{
    A a;
    B b;
    C c;
    std::cout << "A, B, and C are made. Let's call some functions.\n";
    c.set_ulongs(5);
    int* qq = new int {6};
    std::cout << "qq points to heap address: " << qq << "\n";
    std::cout << "qq is a pointer variable that's itself on the stack so...\n";
    std::cout << "&qq (pointer on stack) is: " << &qq << "\n";
    int qqq = 5;
    std::cout << "&qqq (integer on stack) is: " << &qqq << "\n";
    std::cout << "calling b.set_int(qq)\n";
    b.set_int(qq);
    std::cout << "calling b.set_int_ref(qq)\n";
    b.set_int_ref(qq);
    a.set_string("This is a string");
    c.set_string("This is C's a string lol");

    // ------------------ //
    std::cout << "Doing 'A* aa = new C \n";
    A* aa = new C;
    std::cout << "Doing 'B* bb = new C \n";
    B* bb = new C;
    std::cout << "Doing C* cc = new C \n";
    C* cc = new C;
    
    std::cout << "Going to delete cc then let the rest run its own course... let's see what's deleted.\n";
    delete cc;
    std::cout << "bb and aa need to be manually deleted!\ndelete bb: \n";
    delete bb;
    std::cout << "delete aa:\n";
    delete aa;
    std::cout << "When A's destructor is virtual, it is called when deleting bb and aa (otherwise it's not)\n";
    
    std::cout << "Let's do some destruction! Implicit calls at end of program:\n";
    return 0;
}