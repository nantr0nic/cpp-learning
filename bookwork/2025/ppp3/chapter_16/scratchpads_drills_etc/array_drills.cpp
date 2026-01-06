//$ ----- Array drills ----- //
#include <iostream>


// #1
int ga[10] {1,2, 4, 8, 16, 32, 64, 128, 256, 512};

// #2 and #3
void f(int a[], int n)
{
    int la[10];

    for (int i = 0; i < 10; ++i)
        la[i] = ga[i];
    
    for (int i = 0; i < 10; ++i)
        std::cout << "la[" << i << "] = " << la[i] << '\n';

    int* p{ new int[static_cast<unsigned long>(n)] };

    for (int i = 0; i < n; ++i)
        p[i] = a[i];

    for (int i = 0; i < n; ++i)
        std::cout << "p[" << i << "] = " << p[i] << '\n';
    
    delete[] p;
}

//#4
int main()
{
    f(ga, 10);

    int aa[10]{1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

    f(aa, 10);

    return 0;
}