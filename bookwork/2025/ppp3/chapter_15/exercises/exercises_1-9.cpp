// To try individual exercises, highlight the relevant code block and ctrl + /

/*
***** Chapter 15 Exercises 1-9 *****
The first few exercises are question/answer format, so I'll answer them here.
1. The output format of pointer values in my implementation is a hexadecimal 
64-bit memory address such as 0xAFAEADACABAAA9A8. They are usually 0x555555...
for heap memory on my system, 0x7FFFFFFde... for stack memory. The example I
provided was from uninitialized memory :)
2. There are 4 bytes in an int, 8 bytes in a double, and 1 byte in a bool.
3. Two ways pointers can be used in disastrous ways:
    1. double* p0; (uninitialized!)
    2. double* dd = new double[50];
        (never delete it...)
    and, for fun, #3 is like so:
    int* a = new int {5}
    int* b = a;
    delete a;
    delete b; <--- a double delete! undefined behavior that might result in a
    runtime "SIGABRT" error.

4. 
*/

#include <iostream>
// #include <chrono>
// #include <thread>
// #include <iomanip>

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

std::ostream& print_array(std::ostream& os, char* a, int n)
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

// NOTE: Global variable order is NOT guaranteed by C++ standard
// This particular output is implementation-specific
// however... at the time of writing on my specific system it happens to be that...
// global vars (static data) is allocated from lower addresses to higher addresses
// the memory address value increases with each allocation (just like heap memory)
// int global_1{ 1 }; // 0x555555558018   lower
// int global_2{ 2 }; // 0x55555555801c     V
// int global_3{ 3 }; // 0x555555558020     V
// int global_4{ 4 }; // 0x555555558024     V
// int global_5{ 5 }; // 0x555555558028  higher

int main()
{
// ----- Exercise 4 ----- //

    // // Stack variables
    // int a{ 1 }; // 0x7fffffffdf08
    // int b{ 2 }; // 0x7fffffffdf04
    // int c{ 3 }; // 0x7fffffffdf00
    // int d{ 4 }; // 0x7fffffffdefc
    // int e{ 5 }; // 0x7fffffffdef8
    // // The local ints are being allocated "downward" -- from higher to lower ones.
    // // The memory address value decreases with each allocation.
    
    // // Heap allocations
    // int* f = new int[5] {1, 2, 3, 4, 5};
    // // 1 = 0x55555556f4f0
    // // 2 = 0x55555556f4f4
    // // 3 = 0x55555556f4f8
    // // 4 = 0x55555556f4fc
    // // 5 = 0x55555556f500
    // // They're being allocated "upward" -- from lower to higher addresses.
    // // The memory address value increases with each allocation.

    // std::cout << "Global variable (static data) order if not guaranteed and depends\n";
    // std::cout << "on the implementation system -- the compiler can rearrange the order\n";
    // std::cout << "for optimization. However, it happened to be on my system at this time that...\n";
    // std::cout << "Static storage was allocated upward -- from lower to higher addresses.\n";
    // std::cout << "Here are the addresses of 5 global ints (declared/initialized from 1-5):\n";
    // std::cout << "[1] -> " << &global_1 << "\n";
    // std::cout << "[2] -> " << &global_2 << "\n";
    // std::cout << "[3] -> " << &global_3 << "\n";
    // std::cout << "[4] -> " << &global_4 << "\n";
    // std::cout << "[5] -> " << &global_5 << "\n\n";
    // std::cout << "Stack memory is allocated downward -- from higher to lower addresses.\n";
    // std::cout << "Here are the addresses of 5 local ints:\n";
    // std::cout << "[1] -> " << &a << "\n";
    // std::cout << "[2] -> " << &b << "\n";
    // std::cout << "[3] -> " << &c << "\n";
    // std::cout << "[4] -> " << &d << "\n";
    // std::cout << "[5] -> " << &e << "\n\n";
    // std::cout << "Heap memory is allocated upward -- from lower to higher addresses.\n";
    // std::cout << "Here are the addresses of 5 ints from an array allocated to the heap:\n";
    // for (unsigned long i = 0; i < 5; ++i)
    //     std::cout << "[" << i << "] -> " << &f[i] << "\n";

// ----- Exercise 5 ----- //

    // std::cout << "\nGoing to write a program with an infinite loop that allocated but never deallocates.\n";
    // std::cout << "Attempting to reach \"memory exhaustion\" and see what happens and when :)\n";
    // size_t count = 0;
    // while (true)
    // {
    //     int* p = new int[100000]; // about 400KB each iteration
    //     ++count;
    //     std::cout << "Iteration: " << count << ", allocated 100,000 ints at " << p << '\n';
    //     std::cout << std::fixed << std::setprecision(2)
    //         << "Total allocated: "
    //         << (count * 100000 * sizeof(int)) / (1024.0 * 1024.0)
    //         << " MB\n";
    //     // enable chrono, thread, and iomanip for this VVV
    //     //std::this_thread::sleep_for(std::chrono::milliseconds(5));  // Wait for 5 ms
    // }
    // // It didn't stop, my system got very slow after my 32GB of ram and 32GB of swap were filled
    // // but it didn't "fail" at any point :/ I tried reading about it but it seems because of
    // // stuff like 'zram' and virtual memory (swap) it becomes complex. My program reports that it
    // // requested 4324GB of memory but that's not possible on my system. The memory addresses stayed
    // // unique so IDK what happened. Will read about it more after completing other exercises.

// ----- Exercise 6 ----- //

    // char* ex6 = new char[1000000];
    // char cc;
    // int element = 0;

    // while (std::cin >> cc && cc != '!')
    // {
    //     ex6[element] = cc;
    //     ++element;
    // }

// ----- Exercise 7 ----- //

    // char cc {};
    // std::string input {};

    // while (std::cin >> cc && cc != '!')
    // {
    //     input += cc;
    //     std::cout << input << '\n';
    // }

// ----- Exercise 8 ----- //
// I did this in exercise 4 (above)

// ----- Exercise 9 ----- //

// The answer is: I can write past the bounds of the array like so
    char* ex6 = new char[1];
    char cc;
    int element = 0;

    while (std::cin >> cc && cc != '!')
    {
        ex6[element] = cc;
        ++element;
        print_array(std::cout, ex6, element);
    }
// However, I wrote 1522 elements past the bounds and the program didn't fail
// so evidently nothing critical was over-written or corrupted? So faults occurred.
// I'm not sure this is "reasonable" but nothing dramatic happened besides the leak.

    return 0;
}