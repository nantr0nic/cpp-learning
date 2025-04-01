// File2.cpp
#include <iostream>
extern int globalVar; // Declaration of the variable
void printGlobalVar()
{
    std::cout << globalVar << std::endl; // Accessing the variable
}

int main()
{
    printGlobalVar();
    return 0;
}