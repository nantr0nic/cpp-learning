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
    X loc{ 4 };             // local variable           
    X loc2{ loc };          // copy construction    
    //$ cast X{ 5 } to actually copy assign   
    loc = X{ 5 };           // copy assignment <-- from the textbook but it actually move assigns 
    loc2 = copy(loc);       // call by value and return
    loc2 = copy2(loc);
    X loc3{ 6 };                                        
    X& r = ref_to(loc);     // call by reference and return
    delete make(7);         // make(7) then delete
    delete make(8);         // same but int 8
    std::vector<X> v(4);    // default values
    XX loc4;                                            
    X* p = new X{ 9 };      // an X on the free store (heap)  
    delete p;                                           
    X* pp = new X[5];       // an array of Xs on the free store
    delete[] pp;

    return 0;
}
