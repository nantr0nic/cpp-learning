#include <vector>
#include <iostream>

/*
Physical memory layout:
-----------------
|               |
|  Code Storage | <--- memory for your code (also called text storage)
|               |
-----------------
|  Static Data  | <--- global variables
-----------------
|               |
| Heap / Dynamic| <--- available for program, "free" memory (use 'new')
| (Free Store)  |
-----------------
|   Stack       | <--- when call functions, their args and local variables
-----------------
*/

int main()
{
    // This allocates four doubles on the heap/free store
    // the 'new' will return a pointer to the first double
    // p will be set to the pointer that new returns
    // note: arrays are contiguous sequences of elements (of a given type...)
    double* p = new double[4];
    // A pointer value is the address of the first byte of the memory.

    int* pi = new int;          // allocate one int
    int* qi = new int[4];       // allocate an array of 4 ints
    unsigned long n = 2;
    double* pd = new double;    // allocate one double
    double* qd = new double[n]; // allocate n doubles (an array of n doubles)

    // double* p = new double[4];
    // we can use subscript operator [] to read and write objects
    double x = *p;      // read the (first) object pointed to by p (same as p[0])
    double y = p[0];    // read the 1st object pointed to by p     (same as *p)
    double z = p[2];    // read the 3rd object pointed to by p

    *p = 7.7;           // write to the (first) object pointed to by p
    p[2] = 9.9;         // write to the 3rd object pointed to by p
    
    std::vector<int>* v = new std::vector<int>{7,8,9};
    std::cout << v->size() << '\n';     // access using ->
    std::cout << (*v).size() << '\n';   // access using . (requires dereferencing)
    // Use the arrow! (Its rare to need the . style)

    // ------- Initialization ---------- //
    //double* p0;                 // uninitialized: likely trouble!
    // p0 was set to memory address 0xAFAEADACABAAA9A8 (bad)
    double* p1 = new double;    // allocate an uninitialized double
    double* p2 = new double{5}; // get a double initialized to 5
    double* p3 = new double[5]; // get (allocate) 5 uninitialized doubles
    //*p0 = 7.0;

    double* p4 = new double[5] {0,1,2,3,4}; // member list initialization
    double* p5 = new double[] {0,1,2,3,4};  // don't need to specify n in array

    /*
    With user-defined types, default-initialized / default constructor is necessary
    X* px1 = new X;     // one default-initialized X
    X* px2 = new X[17]; // 17 default-initialized Xs

    Y* py1 = new Y;     // error: no default constructor
    Y* py2 = new Y{13}; // OK: initialized to Y{13};
    Y* py3 = new Y[17]  // error: no default constructor
    */

    // If you have no other pointer to use for initializing a pointer, use the null pointer, nullptr:
    double* q0 = nullptr;

    // Make a delete for every new but DON'T DELETE TWICE (bad bad bad)
    delete[] p;     // p pointed to an array, so delete[]
    delete pi;
    delete[] qi;
    delete pd;
    delete[] qd;
    delete v;   // delete the vector
    delete p1;
    delete p2;
    delete[] p3;
    delete[] p4;
    delete[] p5;
    delete q0;  // safe to delete nullptrs

    // If we have two pointers to the same address...
    int* num_p1 = new int{8};
    int* num_p2 = num_p1;
    delete num_p1;
    // delete num_p2; <-- bad!
    // set to null then delete
    num_p2 = nullptr;
    delete num_p2;

    // ----- random dereferencing test ------- //
    int num2 {8};
    int* num2_p1 = &num2;
    int* num2_p2 = &num2;
    int** num2_pp1 = &num2_p1;
    int* num2_np1 = new int{9};
    std::cout << "num2 is " << num2 << "\n";            // int value 8
    std::cout << "*num doesn't exist...\n";
    std::cout << "&num2 is " << &num2 << "\n\n";        // memory address of num2
    std::cout << "num2_p1 is " << num2_p1 << '\n';      // pointing to memory address of num2
    std::cout << "*num2_p1 is " << *num2_p1 << '\n';    // de-referenced, int value 8
    std::cout << "&num2_p1 is " << &num2_p1 << "\n\n";  // memory address of itself
    std::cout << "num2_p2 is " << num2_p2 << '\n';      // memory address of num2
    std::cout << "*num2_p2 is " << *num2_p2 << '\n';    // de-referenced, int value 8
    std::cout << "&num2_p2 is " << &num2_p2 << "\n\n";  // memory address of itself
    std::cout << "num2_pp1 is " << num2_pp1 << '\n';    // memory address of num2_p1
    std::cout << "*num2_pp1 is " << *num2_pp1 << '\n';  // de-referenced, memory address of num2 
    std::cout << "&num2_pp1 is " << &num2_pp1 << "\n\n";// memory address of itself
    std::cout << "num2_np1 is " << num2_np1 << '\n';    // pointer to heap memory
    std::cout << "*num2_np1 is " << *num2_np1 << '\n';  // de-referenced, int value 9
    std::cout << "&num2_np1 is " << &num2_np1 << "\n\n";// (stack) memory of itself
    delete num2_np1;
    int* ipa = new int[4] {6, 7, 8, 9};
    std::cout << "ipa is " << ipa << '\n';
    std::cout << "&ipa is " << &ipa << '\n';
    std::cout << "*ipa is " << *ipa << "\n\n";
    std::cout << "now printing the subscript-accessed 'elements' of ipa:\n";
    for (int i = 0; i < 4; ++i)
    {
        std::cout << "ipa[" << i << "] is " << ipa[i] << '\n';
        std::cout << "&ipa[" << i << "] is " << &ipa[i] << '\n';
        std::cout << "*ipa[" << i << "] requires indirection. \n\n";
    }

    delete[] ipa;
    return 0;
}