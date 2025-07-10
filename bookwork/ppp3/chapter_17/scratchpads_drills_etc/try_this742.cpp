//$ ----- "This this!" on page 742 ----- //
#include <string>
#include <iostream>
#include <vector>

struct X 
{
    int val;

    void out(const std::string& s, int nv) {
        std::cout << this << "->" << s << ": " << val << " (" << nv << ")\n";
    }

    X() { out("X() ", 0); val = 0; }                                        // default constructor
    X(int x) { out("X(int) ", x); val = x; }
    X(const X& x) { out ("X(X&) ", x.val); val = x.val; }                   // copy constructor
    X(X&& x) { out("X(X&&) ", x.val); val = x.val; x.val = 0; }             // move constructor
    X& operator=(const X& x) {                                              // copy assignment
        out("X copy assignment ", x.val); val = x.val; return *this; 
    }
    X& operator=(X&& x) {                                                   // move assignment
        out("X move assignment ", x.val); val = x.val; x.val = 0; return *this; 
    }
    ~X() { out("~X() ", 0); }                                               // destructor
};

X glob { 2 };               // a global variable        

X copy(X a) { std::cout << "copy()\n"; return a; }
X copy2(X a) { std::cout << "copy2()\n"; X aa = a; return aa; }
X& ref_to(X& a) { std::cout << "ref_to()\n"; return a; }
X* make(int i) { std::cout << "make()\n"; X a(i); return new X(a); }

struct XX { X a; X b; };    // members

int main()
{
    X loc{ 4 };             // local variable           //$ 0x7ffd05a233ac->X(int) : 0 (4)
    X loc2{ loc };          // copy construction        //$ 0x7ffd05a233a8->X(X&) : 0 (4)
    loc = X{ 5 };  // copy assignment  //$ cast to actually copy assign (when move is ops uncommented)
    loc2 = copy(loc);       // call by value and return
    loc2 = copy2(loc);
    X loc3{ 6 };                                        //$ 0x7ffd05a2339c->X(int) : 0 (6)
    X& r = ref_to(loc);     // call by reference and return
    delete make(7);
    delete make(8);
    std::vector<X> v(4);    // default values
    XX loc4;                                            //$ 0x7ffd05a23378->X() : 0 (0) and same for 337c
    X* p = new X{ 9 };      // an X on the free store   //$ 0x55a96d4696e0->X(int) : 0 (9)
    delete p;                                           //$ 0x55a96d4696e0->~X() : 9 (0)
    X* pp = new X[5];       // an array of Xs on the free store
    delete[] pp;

    return 0;
}
