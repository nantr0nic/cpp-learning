//$ ----- Drill from page 758 ----- //

#include <iostream>
#include <print>

class Ptr 
{
public:
    //$ Constructors
    Ptr() { p = nullptr; }      
    Ptr(double d) {
        p = new double;
        *p = d;
    }

    // Copy Constructor and Assignment Operator
    Ptr(const Ptr& orig);
    Ptr& operator=(const Ptr& orig);

    // Move Constructor and Assignment Operator
    Ptr(Ptr&& orig);
    Ptr& operator=(Ptr&& orig);

    // Destructor
    ~Ptr() { 
        std::cout << "Deleting 'p' at: " << p << '\n'; 
        delete p;
        std::cout << "Destructing this at: " << this << '\n'; 
    }

    // Access
    double* get_p() { return p; }

    // * operator
    double& operator*() {
        return *p;
    }

private:
    double* p;
};

// Copy Constructor
Ptr::Ptr(const Ptr& orig)
{
    if (orig.p != nullptr)
    {
        p = new double{*orig.p};
        std::cout << "Copy constructor called!\n";
    }
    else
        p = nullptr;
}

// Copy assignment operator
Ptr& Ptr::operator=(const Ptr& orig)
{
    if (this == &orig)
    {
        return *this;
    }
    delete p;
    if (orig.p != nullptr)
    {
        p = new double{*orig.p};
        std::cout << "Copy assignment operator called!\n";
    }
    else 
    {
        p = nullptr;
    }
    return *this;
}

// Move constructor
Ptr::Ptr(Ptr&& orig)
{
    p = orig.p;
    orig.p = nullptr;
    std::cout << "Move constructor called!\n";
}

// Move assignment operator
Ptr& Ptr::operator=(Ptr&& orig)
{
    if (this == &orig)
    {
        return *this;
    }

    delete p;
    p = orig.p;
    orig.p = nullptr;

    std::cout << "Move assignment operator called!\n";
    return *this;
}

Ptr copy_and_inc(Ptr& ptr)
{
    Ptr temp = ptr;
    *temp += 1;
    return temp;
}

Ptr move_and_inc(Ptr& ptr)
{
    *ptr += 1;
    return ptr;
}

int main()
{
    Ptr ptr_test(3.14);
    std::cout << *ptr_test.get_p() << '\n';
    std::cout << *ptr_test << '\n';
    *ptr_test = 6.28;
    std::cout << *ptr_test << "\n\n";

    Ptr ptr_test_copy{ ptr_test };
    std::cout << *ptr_test_copy << '\n';
    Ptr ptr_test_copy2(0.01);
    ptr_test_copy = ptr_test_copy2;
    std::cout << *ptr_test_copy << '\n';

    Ptr returned_ptr = copy_and_inc(ptr_test_copy);
    std::cout << *returned_ptr << '\n';

    returned_ptr = move_and_inc(returned_ptr);
    std::println("{}", *returned_ptr);

    returned_ptr = copy_and_inc(returned_ptr);
    std::println("{}", *returned_ptr);

    Ptr move_con_test{ std::move(returned_ptr) };
    std::println("{}", *move_con_test);
    

    return 0;
}