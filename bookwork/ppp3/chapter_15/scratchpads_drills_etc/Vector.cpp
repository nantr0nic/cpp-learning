#include <iostream>

class Vector {                  // a very simplified vector of doubles
public:
    Vector(int s);              // constructor: allocate elements to the heap and initialize them
    ~Vector();                  // destructor: return elements to free store (heap)
    
    int size() const { return sz; }     // the current size

    double get(int n) const { return elem[n]; } // access: read
    void set(int n, double v) { elem[n] = v; }  // access: write

private:
    int sz;                     // the size
    double* elem;               // a pointer to the elements
};

Vector::Vector(int s)           // constructor
    : sz { s }                  // initialize sz
    , elem { new double[s] }    // initialize elem to elements on the free store
{
    for (int i = 0; i < s; ++i) // initialize elements
    {
        elem[i] = 0;
    }
}

Vector::~Vector()               // destructor
{
    delete[] elem;              // return elements to free store (heap)
}

int main()
{
    Vector v(5);

    for (int i = 0; i < v.size(); ++i)
    {
        v.set(i, 1.1*i);
        std::cout << "v[" << i << "] == " << v.get(i) << '\n';
    }

    return 0;
}