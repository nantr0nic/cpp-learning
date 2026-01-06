#include <iostream>

int absolute(int a)
{
    return (a>=0) ? a : -a;   // this is called "arithmetic if" or "conditional expression"
}

int main()
{
    bool running = true;
    while (running)
    {
        int num = 99;
        std::cout << "Enter a number or '0' to quit >> ";
        std::cin >> num;
        if (num == 0)
        {
            running = false;
        }
        else
        {
            std::cout << absolute(num) << "\n";
        }
    }
    return 0;
}
