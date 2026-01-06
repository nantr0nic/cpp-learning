#include <vector>
#include <iostream>
// trying out print
#include <print>

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

int main()
{
    int* p1 = new int { 7 };
    std::cout << "value of p1 (address it points to) -> " << p1;
    std::cout << "\nvalue of the int p1 points to -> " << *p1 << "\n\n";

    int* p2 = new int[7] {1, 2, 4, 8, 16, 32, 64};
    std::cout << "value of p2 (address it points to) -> " << p2;
    std::cout << "\nvalue of the array('s first element) it points to -> " << *p2 << '\n';
    std::cout << "The drill is a little ambiguous, so in case Bjarne meant ALL of the values...\n";
    print_array(std::cout, p2, 7);

    std::println("\nInitializing p3 with p2, assigning p1 to p2, assigning p2 to p3");
    int* p3{ p2 };
    p2 = p1;
    p2 = p3;
    std::cout << "value of p1 (address it points to) -> " << p1;
    std::cout << "\nvalue of the int p1 points to -> " << *p1 << "\n";
    std::cout << "value of p2 (address it points to) -> " << p2;
    std::cout << "\nvalue of the array('s first element) it points to -> " << *p2 << '\n';
    std::cout << "The drill is a little ambiguous (again), so in case Bjarne meant ALL of the values...\n";
    print_array(std::cout, p2, 7);

    std::cout << "\nDeleting p1 and p2 (NOT p3 cuz p2 and p3 point to same address)\n";
    delete p1;
    p1 = nullptr;
    delete[] p2;
    // delete p3; <-- MISTAKE! This is a double delete because p3 and p2 were pointing to the same address.

    std::cout << "Reassigning p1 to array of 10 ints, making a p2 and copying p1 to p2\n";
    p1 = new int[10] {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    p2 = new int[10]{};
    for (unsigned long i = 0; i < 10; ++i)
        p2[i] = p1[i];
    std::cout << "p2's values:";
    print_array(std::cout, p2, 10);

    delete[] p1;    // ignore warning because its based off of first declaration
    delete[] p2;

    // ----- drill 13 ----- //

    std::println("Now doing the same thing but with two vectors:");
    std::vector<int>* v1 = new std::vector<int>{1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    std::vector<int>* v2 = new std::vector<int>{};
    v2->reserve(v1->size());    // good practice
    for (size_t i = 0; i < v1->size(); ++i)
        v2->push_back((*v1)[i]);

    // For fun... here are 3 ways to print elements *v2[i]
    
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

    delete v1;
    delete v2;

    return 0;
}