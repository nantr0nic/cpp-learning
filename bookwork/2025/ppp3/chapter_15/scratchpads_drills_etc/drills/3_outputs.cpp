#include <vector>
#include <iostream>
#include <print>

int main()
{
    // make two vectors on the heap/free store, 2nd vector is copy of the first
    std::vector<int>* v1 = new std::vector<int>{1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    std::vector<int>* v2 = new std::vector<int>{};

    v2->reserve(v1->size());    // good practice (shrink v2's size to the size of v1)

    // copy v1 to v2
    for (size_t i = 0; i < v1->size(); ++i)
        v2->push_back((*v1)[i]);

    // Here are 3 ways to print the elements in *v2
    
    // the "usual" way:
    std::cout << "*v2 is: [";
    for (size_t i = 0; i < v2->size(); ++i)
    {
        std::cout << (*v2)[i];
        if (i < v2->size() - 1)
            std::cout << ", ";
    }
    std::cout << "]\n";

    // using range-for loop:
    std::cout << "*v2 is: [";
    for (const auto& value : *v2)
        std::cout << value << ", ";
    std::cout << "]\n";

    // new C++23 print lib... much cleaner:
    std::println("*v2 is: {}", *v2);

    return 0;
}