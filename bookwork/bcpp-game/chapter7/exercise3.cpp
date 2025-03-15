#include <iostream>
using namespace std;

int main()
{
    int a = 10;
    int& b = a;
    int* c = &b;
    cout << &a << endl;
    cout << &b << endl;
    cout << &(*c) << endl;

    return 0;
}

/* They do return all the same memory address.
int a declares an integer which reserves the memory address and assigns the value 
    10 to it.
    
int& b declares a reference that points to a. A reference is an alias and it does not
    itself occupy any memory location. When the compiler compiles the code, it will replace
    'b' with 'a' wherever it is used. Internally, a modern C++ compiler might keep the referenced
    value in a CPU register instead of allocating it to memory.
    This is why &b is equal to &a.

int* c = &b declares a pointer c that points to the memory address of b which is the same
    as a. Printing &(*c) prints the memory address of the dereferenced c object which is b which is a.
    Internally, first c is dereferenced (to b which is equivalent to a) and then returns the
    memory address of that dereferenced object (which is a).

*/