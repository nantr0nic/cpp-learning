//$ ----- 17 Essential Operations (Vector) ----- //

#include <initializer_list>
#include <print>
#include <iostream>

class Vector {                  // a very simplified vector of doubles
    /*
     * invariant:
     * if 0 <= n < sz, elem[n] is element n
     * sz <= space;
     * if sz < space there is space for (space - sz) doubles after elem[sz - 1]
    */
public:
    // Constructors
    Vector() : sz{ 0 }, elem{ nullptr }, space{ 0 } { };      // empty constructor
    explicit Vector(int s);                                   // int constructor (allocates s slots on heap)
    Vector(std::initializer_list<double> lst);                // initializer-list constructor
    Vector& operator=(std::initializer_list<double> lst);     // list assignment

    // Copy and Move operations
    Vector(const Vector& arg);                                // copy constructor
    Vector& operator=(const Vector& a);                       // copy assignment
    Vector(Vector&& arg);                                     // move constructor
    Vector& operator=(Vector&& arg);                          // move assignment
    
    // Destructor
    ~Vector();                  // destructor: return elements to free store (heap)

    // Operator assignments
    double& operator[](int n) { return elem[n]; }             // return element
    const double& operator[](int n) const { return elem[n]; } // return element (const)

    // Size and capacity getters
    int size() const { return sz; }                           // the current size
    int capacity() const { return space; }                    // return space

    // Element getter/setter
    double get(int n) const { return elem[n]; }               // access: read
    void set(int n, double v) { elem[n] = v; }                // access: write

    // Memory/capacity functions
    void reserve(int newalloc);                               // reserve memory (abs value)
    void resize(int newsize);
    void push_back(double d);

    // Iteration support
    double* begin() const { return elem; }                    // return position of first element
    double* end() const { return elem + sz; }                 // return position of one past last element

    // Not in the book, but for logging / making sure stuff works
    void printv() { 
        for (int i = 0; i < sz; ++i)
            std::print("[{}] = {} / ", i, elem[i]);
        std::println("");
    }

private:
    int sz;                     // the size
    double* elem;               // a pointer to the elements
    int space;                  // number of elements plus "free space"/slots" for new elements
};

//$ Overloaded operators for Vector class
bool operator==(const Vector& v1, const Vector& v2) 
{
    if (v1.size() != v2.size())
        return false;
    for (int i = 0; i < v1.size(); ++i)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

bool operator!=(const Vector& v1, const Vector& v2)
{
    return !(v1==v2);
}

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
    Vector size_test{ 33, 44, 55, 66, 77, 88 };
    size_test.printv();

    size_test.resize(3);

    size_test.printv();

    size_test.resize(8);

    size_test.printv();

    return 0;
}


// Constructor (int)
Vector::Vector(int s)           // constructor
    : sz { s }                  // initialize sz
    , elem { new double[static_cast<unsigned long>(s)] }    // initialize elem to elements on the free store
    , space { s }
{
    for (int i = 0; i < sz; ++i) // initialize elements
    {
        elem[i] = 0;
    }
}

// Constructor (initializer_list)
Vector::Vector(std::initializer_list<double> lst)
    : sz {static_cast<int>(lst.size())}
    , elem {new double[static_cast<unsigned long>(sz)]}
    , space {static_cast<int>(lst.size())}
{
    std::copy(lst.begin(), lst.end(), elem);
}

// Initializer_list assignment operator
Vector& Vector::operator=(std::initializer_list<double> lst)
{ 
    int new_size{static_cast<int>(lst.size())};
    reserve(new_size);                        // This handles space management
    std::copy(lst.begin(), lst.end(), elem);
    sz = new_size;
    return *this;                             // No need to touch space!
}

// Copy constructor
Vector::Vector(const Vector& arg)           // allocate elements, then initialize them by copying
    : sz { arg.sz }
    , elem { new double[static_cast<unsigned long>(arg.sz)] }
    , space { arg.space }
{
    std::copy(arg.elem, arg.elem+sz, elem); // copy elements [0:sz) from arg.elem into elem]
}

// Copy assignment
Vector& Vector::operator=(const Vector& a)  // make 'this' Vector a copy of 'a'
{
    if (this == &a)                     // self-assignment check
        return *this;
        
    if (a.sz <= space)                  // enough space, don't need new allocation
    {
        for (int i = 0; i < a.sz; ++i)  // copy elements
            elem[i] = a.elem[i];
        sz = a.sz;
        return *this;
    }
    
    double* p = new double[static_cast<size_t>(a.sz)]; // allocate new space
    for (int i = 0; i < a.sz; ++i)      // copy elements
        p[i] = a.elem[i];
    delete[] elem;                      // deallocate old space

    space = sz = a.sz;                  // set new size
    elem = p;                           // set new elements
    return *this;                       // return a self-reference
}

// Move constructor
Vector::Vector(Vector&& arg)
    : sz { arg.sz }
    , elem { arg.elem }         // copy arg's elem and sz
    , space { arg.space }
{
    arg.space = 0;
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
        space = arg.space;
        arg.elem = nullptr;                 // make arg the empty Vector
        arg.sz = 0;
        arg.space = 0;
    }
    return *this;                           // return a self-reference
}

// Destructor
Vector::~Vector()               // destructor
{
    delete[] elem;              // return elements to free store (heap)
}

// Memory/capacity functions
void Vector::reserve(int newalloc)
// reserve space for Vector
{
    if (newalloc <= space)                  // never decrease allocation
        return;
    double* p = new double[static_cast<size_t>(newalloc)]; // allocate new space
    for (int i = 0; i < sz; ++i)            // copy old elements
        p[i] = elem[i];
    delete[] elem;                          // deallocate old space
    elem = p;                               // make elem point to new memory
    space = newalloc;
    // p goes out of scope 
}

void Vector::resize(int newsize)
// make the vector have newsize elements
// initialize each new element with the default value 0.0
{
    reserve(newsize);
    for (int i = sz; i < newsize; ++i)      // initialize new elements
    {
        std::cout << " // " << elem[i] << " @ " << &elem[i];
        elem[i] = 0.0;
        std::cout << " // " << elem[i] << " @ " << &elem[i];
    }
    sz = newsize;
}

void Vector::push_back(double d)
// increase Vector size by one; initialize the new element with d
{
    if (space == 0)
        reserve(8);
    else if (sz == space)
        reserve(2 * space);
    elem[sz] = d;
    ++sz;
}