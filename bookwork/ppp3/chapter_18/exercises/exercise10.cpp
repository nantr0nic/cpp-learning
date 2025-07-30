#include <__new/global_new_delete.h>
#include <cstdlib>
#include <stdlib.h>
import std;

int delete_count{};
int new_count{};

void operator delete(void* ptr)
{
    ++delete_count;
    std::cout << "[" << delete_count << "] Raw delete called\n";
    free(ptr);
}

void* operator new(std::size_t size)
{
    ++new_count;
    std::cout << "[" << new_count << "] Raw new called\n";
    return malloc(size);
}

/*===============================================================*
*                          Exercise 10                           *
*                                                                *
*  Implement a simple unique_ptr supporting only a constructor,  *
*destructor, −>, *, and release(). Delete the assignment and copy*
*                         constructors.                          *
 *===============================================================*/

template<typename T>
class Uniq_ptr 
{
public:
    Uniq_ptr() : ptr{ new T{ T{} } } { std::println("Default constructor called"); }
    Uniq_ptr(T object) : ptr{ new T{ object } } { std::println("Constructor called"); }

    Uniq_ptr(const Uniq_ptr<T>& orig) = delete;
    Uniq_ptr<T>& operator=(const Uniq_ptr<T>& orig) = delete;
    Uniq_ptr(Uniq_ptr<T>&& orig) = delete;
    Uniq_ptr<T>& operator=(Uniq_ptr<T>&& orig) = delete;

    ~Uniq_ptr<T>() {
        std::println("Destructor called");
        delete ptr;
        ptr = nullptr;
    }

public:
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

private:
    T* ptr;

};

int main()
{
    Uniq_ptr<std::string> u_string{"This is a string on the heap"};
    std::cout << "u_string is: " << *u_string << "\n";

    Uniq_ptr<std::vector<std::string>> u_string_vec{};
    std::string string_1{ "string stuff woo" };
    u_string_vec->push_back(string_1);
    u_string_vec->push_back("second element I think");
    u_string_vec->push_back(*u_string);
    std::println("{}", *u_string_vec);
    std::string* raw_ptr_string = u_string.release();
    u_string_vec->push_back(*raw_ptr_string);
    std::println("{}", *u_string_vec);

    delete raw_ptr_string;

    return 0;
}