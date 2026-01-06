#include <iostream>
#include <string>

int main()
{
    int i = 0;
    int j = 9;
    while (i<10)
        ++j;
    if (j>i)
        std::cout << "Success!\n";

    return 0;
}