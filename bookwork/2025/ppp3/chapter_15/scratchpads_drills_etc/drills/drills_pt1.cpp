/*
* This drill has two parts. The first exercises/builds your understanding of free-
*   store-allocated arrays and contrasts arrays with vectors.
*/

#include <iostream>
#include <vector>

// #4
std::ostream& print_array(std::ostream& os, int* a, int n)
{
    os << "{"; 
    for (int i = 0; i < n; ++i)
    {
        os << "[" << i << "]->" << a[i];
        if (i < n - 1)
        {
            os << ", ";
        }
    }
    os << "}\n";
    return os;
}

// #9
std::ostream& print_vector(std::ostream& os, std::vector<int> v)
{
    os << "{";
    for (size_t i = 0; i < v.size(); ++i)
    {
        os << "[" << i << "]->" << v[i];
        if (i < v.size() - 1)
        {
            os << ", ";
        }
    }
    os << "}\n";
    return os;
}

int main()
{
    // #1
    int* d = new int[10];
    // for (unsigned long i = 0; i < 10; ++i)
    // {
    //     std::cout << d[i] << '\n';
    // }
    // print_array(std::cout, d, 10);

    // #5 - 9
    // These initialize the arrays with said values
    // int* d5 = new int[10] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
    // int* d6 = new int[11] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
    // int* d7 = new int[20] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110,
    //                         111, 112, 113, 114, 115, 116, 117, 118, 119};

    // these initialize empty (not good) but then are immediately assigned
    // I know the 'precision loss' from unsigned long to int here is irrelevant
    // but those conversion warning messages drive me crazy
    int* d5 = new int[10];
    for (unsigned long i = 0; i < 10; ++i)
        d5[i] = 100 + static_cast<int>(i);

    int* d6 = new int[11];
    for (unsigned long i = 0; i < 11; ++i)
        d6[i] = 100 + static_cast<int>(i);

    int* d7 = new int[20];
    for (unsigned long i = 0; i < 20; ++i)
        d7[i] = 100 + static_cast<int>(i);

    print_array(std::cout, d5, 10);
    print_array(std::cout, d6, 11);
    print_array(std::cout, d7, 20);

    delete[] d;
    delete[] d5;
    delete[] d6;
    delete[] d7;

    std::cout << "\nArrays are deleted, let's repeat now with vectors:\n";

    // these are default initialized to 0 but we can reserve the space since we
    // know exactly how much will go in each :)
    std::vector<int> v5(10);
    std::vector<int> v6(11);
    std::vector<int> v7(20);
    // now we'll assign them values
    for (size_t i = 0; i < v5.size(); ++i)
        v5[i] = 100 + static_cast<int>(i);
    for (size_t i = 0; i < v6.size(); ++i)
        v6[i] = 100 + static_cast<int>(i);
    for (size_t i = 0; i < v7.size(); ++i)
        v7[i] = 100 + static_cast<int>(i);
    print_vector(std::cout, v5);
    print_vector(std::cout, v6);
    print_vector(std::cout, v7);

    return 0;
}