#include <iostream>

// ----- 16.1 Arrays ----- //

int ai[4];              // static array of 4 ints

void fct()
{
    char ac[8];         // on-stack array of 8 chars
}

// This is an example of range error / buffer overflow
void use(double* pd)
{
    pd[2] = 2.2;
    pd[3] = 3.3;    // out of range, but compiler doesn't keep track
    pd[-2] = -2.2;  // same -- this is 2 doubles-space before pd[0] (16 bytes)
}

void test()
{
    double a[3];
    use(a);     // a converts to a pointer to a[0] when used as an argument
}

void p690()
{
    double* p = new double;         // allocate a double
    double* q = new double[1000];   // allocate a 1000 doubles

    q[700] = 7.7;                   // fine: q points to 1000 doubles
    q = p;                          // let q point to the same object as p does
    double d = q[700];              // bad: q points to a single double, out-of-range access!
}

// ----- 16.1.1 Pointer arithmetic ----- //

void p691()
{
    // These are all stack allocated
    double ad[8] {0, 0, 0, 0, 0, 0, 0, 0};
    double* p = &ad[4];     // point to ad[4]; the 5th element of ad
                            // &ad[4] returns the memory address -- which is what p needs
    // Now we can subscript and dereference that pointer
    *p = 7;
    p[2] = 6;
    p[-2] = 9;
    // Now ad[4] = 7, ad[2] = 9, and ad[6] = 6

    // We can use arithmetic to shift the pointer
    p += 2;     // shift 2 to the right
    p -= 4;     // move p 4 elements to the left (now pointing to '9')

    // We could print the value of ad's elements like this
    const int max = sizeof(ad) / sizeof(*ad);   // one way to determine the # of elements of ad
    for (double* p = &ad[0]; p < &ad[max]; ++p)
        std::cout << *p << '\n';
    std::cout << " // ---------- // \n";
    // Backwards:
    for (double* p = &ad[max - 1]; p >= &ad[0]; --p)
        std::cout << *p << '\n';
}

int main()
{
    p691();

    return 0;
}