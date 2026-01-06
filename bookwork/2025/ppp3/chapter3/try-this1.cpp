#include <iostream>

int main()
{
    char temp = 'a';
    int temp2 = temp;
    while (temp2 <= 122)
    {
        std::cout << temp << "  " << temp2 << "\n";
        ++temp;
        ++temp2;
    }
    return 0;
}