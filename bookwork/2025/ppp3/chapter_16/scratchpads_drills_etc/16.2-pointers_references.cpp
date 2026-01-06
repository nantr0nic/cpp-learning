//$ ----- 16.2 Pointers and references ----- //

#include <cstring>
#include <iostream>
void ptr_examples()
{
   int x = 10;
   int* p = &x;         // &x to get a pointer (memory address of x) 
   // p = x;            // ! type error (assigning to int* from int)
   *p = 7;              // write to the object pointed to
   // p = 7;            // ! type error (assigning to int* from int)
   int x2 = *p;         // read the value of the object pointed to
   int* p2 = p;         // make p2 point to the object pointed to by p
   p = nullptr;         // "clear" p
   p = &x2;             // make p point to x2
}

void ref_examples()
{
    int x = 10;
    int& r = x;
    // r = &x           // type error (assigning to int from int*)
    r = 7;              // write to the object referred to
    // *r = 7;          // ! type error
    int x2 = r;         // read the value of the object referred to
    int& r2 = r;        // make r2 refer to the object referred to by r
    // r = "nullref"    // ! there is no nullref
    r = x2;             // assign x2 to the object referred to by r
}

//$ --- 16.2.1 Pointer and reference parameters --- //

// three choices:
int incr_v(int x) { return x + 1; }     // compute a new value and return it
void incr_p(int* p) { ++*p; }           // pass a pointer (dereference it and increment the result)
void incr_r(int& r) { ++r; }            // pass a reference

/*
 * For tiny objects (ints, 2 doubles, char, etc.), prefer pass-by-value.
 * For functions where "no object" (represented by nullptr) is a valid argument,
 *      use a pointer parameter (and remember to test for nullptr) [p.698]
 * Otherwise, use a reference parameter.
*/

// Pointers = possible range errors, memory leaks, etc. Can use span (covered later).