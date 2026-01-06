#include <iostream>

namespace X
{
    int var = 0;
    void print()
    {
        std::cout << var << "\n";
    }
}

namespace Y
{
    int var = 0;
    void print()
    {
        std::cout << var << "\n";
    }
}

namespace Z
{
    int var = 0;
    void print()
    {
        std::cout << var << "\n";
    }
}

int main()
{
    X::var = 7;
    X::print();
    // print X’s var
    using namespace Y;  // can only do this once
    var = 9;
    print();
    // print Y’s var
    {
        using Z::var;
        using Z::print;
        var = 11;
        print();
        // print Z’s var
    }
    print();
    // print Y’s var
    X::print(); // print X’s var
    /* This doesn't compile because var and print() are ambiguous
    {
        using namespace X;
        var = 5;
        print();
    }
    */
    var = 5; // modifies Y::var
    print();
    Y::print();
}