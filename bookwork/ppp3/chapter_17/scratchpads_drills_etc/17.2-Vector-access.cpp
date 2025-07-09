//$ ----- 17 Essential Operations (Vector) ----- //

#include <initializer_list>
#include <print>
#include <iostream>

class Vector {                  // a very simplified vector of doubles
public:
    Vector() : sz{ 0 }, elem{ nullptr } { };    // empty constructor
    explicit Vector(int s);              // constructor: allocate elements to the heap and initialize them
    Vector(std::initializer_list<double> lst);  // initializer-list constructor

    ~Vector();                  // destructor: return elements to free store (heap)

    Vector(const Vector& arg);                                // copy constructor
    Vector& operator=(const Vector& a);                       // copy assignment

    Vector(Vector&& arg);                                     // move constructor
    Vector& operator=(Vector&& arg);                          // move assignment
    
    int size() const { return sz; }                           // the current size

    double get(int n) const { return elem[n]; }               // access: read
    void set(int n, double v) { elem[n] = v; }                // access: write
    double& operator[](int n) { return elem[n]; }             // return element
    const double& operator[](int n) const { return elem[n]; } // return element (const)

    void printv() { 
        for (int i = 0; i < sz; ++i)
            std::println("{}", elem[i]);
    }

private:
    int sz;                     // the size
    double* elem;               // a pointer to the elements
};

// This will fail without a proper copy constructor.
void f(int n)
{
    Vector v(3);
    v[2] = n;
    Vector v2 = v;  // copy constructed
    v.printv();
    v2.printv();
    // Without proper c.c. we get a double delete
}

// This will fail without a proper copy assignment
void f2(int n)
{
    Vector v(3);
    v[2] = n;
    Vector v2(4);
    v2 = v;         // copy assigned
    v.printv();
    v2.printv();
    // Without proper c.a. we (still) get a double delete
    // Also, we lose access to v2's original 4 elements (memory leak!)
}



int main()
{
    Vector v1 {3};
    Vector v2(3);

    v1.printv();
    v2.printv();
    std::println("-------");

    f(9);
    f2(66);

    return 0;
}


// Constructor (int)
Vector::Vector(int s)           // constructor
    : sz { s }                  // initialize sz
    , elem { new double[static_cast<unsigned long>(s)] }    // initialize elem to elements on the free store
{
    for (int i = 0; i < sz; ++i) // initialize elements
    {
        elem[i] = 0.0;
    }
}

// Constructor (initializer_list)
Vector::Vector(std::initializer_list<double> lst)
    : sz {static_cast<int>(lst.size())}
    , elem {new double[static_cast<unsigned long>(sz)]}
{
    std::copy(lst.begin(), lst.end(), elem);
}

// Destructor
Vector::~Vector()               // destructor
{
    delete[] elem;              // return elements to free store (heap)
}

// Copy constructor
Vector::Vector(const Vector& arg)           // allocate elements, then initialize them by copying
    : sz { arg.sz }
    , elem { new double[static_cast<unsigned long>(arg.sz)] }
{
    std::copy(arg.elem, arg.elem+sz, elem); // copy elements [0:sz) from arg.elem into elem]
}

// Copy assignment
Vector& Vector::operator=(const Vector& a)  // make this Vector a copy of a
{
    double* p = new double[static_cast<unsigned long>(a.sz)]; // allocate new space
    std::copy(a.elem, a.elem+a.sz, p);                        // copy elements from a.elem into p
    delete[] elem;                                            // deallocate old space
    elem = p;                                                 // now we can reset elem
    sz = a.sz;
    return *this;                                             // return a self-reference
}

// Move constructor
Vector::Vector(Vector&& arg)
    : sz { arg.sz }
    , elem { arg.elem }         // copy arg's elem and sz
{
    arg.sz = 0;                 // make arg the empty Vector
    arg.elem = nullptr;
}

// Move assignment
Vector& Vector::operator=(Vector&& arg)     // move arg to this Vector
{
    if (this != &arg)                       // protect against self-assignment (v=v)
    {
        delete[] elem;                      // deallocate old space
        elem = arg.elem;                    // copy arg's elem and sz
        sz = arg.sz;
        arg.elem = nullptr;                 // make arg the empty Vector
        arg.sz = 0;
    }
    return *this;                           // return a self-reference
}