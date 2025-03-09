#include <iostream>

int main()
{
    double val1 = 0;
    double val2 = 0;
    std::cout << "Enter value 1: ";
    std::cin >> val1;
    std::cout << "Enter value 2: ";
    std::cin >> val2;
    std::cout << std::endl;
    if (val1 > val2)
    {
        std::cout << val1 << " is greater than " << val2;
    }
    if (val1 < val2)
    {
        std::cout << val1 << " is lesser than " << val2;
    }
    if (val1 == val2)
    {
        std::cout << val1 << " is equal to " << val2;
    }
    std::cout << "\nThe sum of the two values is: " << val1 + val2;
    std::cout << "\nThe difference between the first and second value is: " << val1 - val2;
    std::cout << "\nThe product of the two values is: " << val1 * val2;
    std::cout << "\nThe ratio of the first to the second value is: " << val1 / val2;
    std::cout << std::endl;
    return 0;
}