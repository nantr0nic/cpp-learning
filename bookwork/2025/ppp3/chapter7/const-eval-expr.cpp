#include <iostream>
#include "cee.cpp"

using std::cout;

int main()
{
    int result1 = square(10);               // ? (Depends on compiler...)
    constexpr int result2 = square(5);      // Compile-time evaluation <-- FORCED to be evaluated at compile time
    cout << result2 << "\n";

    int value = 5;
    int result3 = square(value);            // Runtime evaluation
    cout << result3 << "\n";
    
    int result4 = cube(3);
    constexpr int result5 = cube(2);        // Compile-time evaluation

    cout << result5 << "\n";

    // int result6 = cube(value);  // Error: "call to consteval function 'cube' did not produce a valid constant expression"
    int value2 = square_add(value);
    cout << "Square of 5 is " << value2 << std::endl;

    return 0;
}   