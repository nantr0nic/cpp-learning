//$ ----- 16.4 Alternatives to pointer use ----- //

/*
Pointers can be used for essentially anything. That’s why we try to avoid
their use: looking at pointer-heavy code we cannot reliably determine the
intent of the programmer. That makes many uses of pointers error prone.
Consider alternatives. (p702)
-----
 * To hold a collection of values, STL containers: //$ vector, set, map, unordered_map, array.
 * To hold a string of characters: //$ string
 * To point to an object you own (i.e. must delete) use STL //$ unique/shared_ptr
 * To point to a contiguous sequence of elements that you don't own use STL //$ span
 * To systematically avoid dereferencing a null pointer, use //$ not_null
*/

#include <cstring>
#include <exception>
#include <iostream>
#include <span>

//$ --- span --- //

// span keeps track of the number of elements in an array
void first_span()
{
    int arr[8];
    std::span spn{ arr };   // a span<int> that points to 8 ints (int was deduced)

    // note we can also select a part of an array
    const int max = 1024;
    int buf[max];
    std::span<int> sp{ buf, max/2 };
}

// With span, we can get range checking and range-for
void test(std::span<int> s)
{
    std::cout << "size: " << s.size() << '\n';

    for (int x : s)
        std::cout << x << '\n';
    
    try 
    {
        int y = s[s.size()];
    } 
    catch (...) 
    {
        std::cout << "we have range checking\n";
        return;
    }
    std::cout << "no range checking! Boo Hoo!\n";
    std::terminate();
}

//$ --- array --- //
/*
 * For good and bad, like the built-in array, array is a simpler and less flexible
type than vector. Its size is not stored in memory, but remembered by the type
system. An array doesn’t use the free store unless you create it using new.
Instead, an array uses only the kind of memory (e.g., stack or static) in which
you create it, and that can be important.
    Unfortunately, the number of elements of an array is never deduced, so it
must be explicitly stated. On the other hand, if there are more elements than
initializers, the remainder is default initialized. 
*/

void int_array()
{
    std::array<int,8> arr {0, 1, 2, 3, 4, 5, 6, 7};
    // int* p = arr;           // ! error (and that's good)

    std::array<std::string,4> as {"Hello", "", "World!"};   // as[3] default initialized to empty
}

//$ --- not_null --- //

// not_null is not in the STL, though it is in GSL from Microsoft. I don't have that
// installed so I'm not going to use it. 

int cstrlen(const char* p)
{
    if (p == nullptr)
        return 0;
    int n = 0;
    while (*p++)
        ++n;
    return n;
}

void try_this()
{
    char* p = nullptr;
    size_t x = cstrlen(p);
    std::cout << "cstrlen(p): " << x << '\n';
}

int main()
{
    // try_this();
}