#include <__new/global_new_delete.h>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <stdlib.h>
import std;

// int delete_count{};
// int new_count{};

// void operator delete(void* ptr)
// {
//     ++delete_count;
//     std::cout << "[" << delete_count << "] Raw delete called\n";
//     free(ptr);
// }

// void* operator new(std::size_t size)
// {
//     ++new_count;
//     std::cout << "[" << new_count << "] Raw new called\n";
//     return malloc(size);
// }

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
    // The real unique_ptr I think DOES have move semantics but Bjarne said to not
    // implement them for this exercise
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
        if (!ptr)
        {
            throw std::runtime_error{"Dereferenced a nullptr!"};
        }
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

private:
    T* ptr;

};

/*========================================================================*
*                               Exercise 11                               *
*                                                                         *
*    Design and implement a Counted_ptr<T> that is a type that holds a    *
* pointer to an object of type T and a pointer to a “use count” (an int)  *
*  shared by all counted pointers to the same object of type T. The use   *
*  count should hold the number of counted pointers pointing to a given   *
*T. Let the Counted_ptr’s constructor allocate a T object and a use count *
* on the free store. Let Counted_ptr’s constructor take an argument to be *
* used as the initial value of the T elements. When the last Counted_ptr  *
*for a T is destroyed, Counted_ptr’s destructor should delete the T. Give *
*the Counted_ptr operations that allow us to use it as a pointer. This is *
*  an example of a “smart pointer” used to ensure that an object doesn’t  *
*get destroyed until after its last user has stopped using it. Write a set*
*of test cases for Counted_ptr using it as an argument in calls, container*
*                             elements, etc.                              *
 *========================================================================*/

template<typename T>
class Counted_ptr
{
private:
    T* object_ptr{ nullptr };
    int* ptr_count{ nullptr };

public:
    Counted_ptr() = delete;
    explicit Counted_ptr(const T& object) 
        : object_ptr{ new T{ object } }
        , ptr_count{ new int{ 1 } }
    { 
        std::println("[!!!] New Counted_ptr constructed.");
    }
    
    // copy constructors, for this simple version of shared_ptr, is where
    // the magic happens
    Counted_ptr(const Counted_ptr<T>& cptr)
        : object_ptr{ cptr.object_ptr }
        , ptr_count{ cptr.ptr_count }
    {
        std::println("[!] Copy constructor called.");
        if (ptr_count)
        {
            ++(*ptr_count);
            std::println("[!!!] Pointer count increased! Currently: {}", *ptr_count);
        }
    }
    Counted_ptr& operator=(const Counted_ptr<T>& cptr) {
        std::println("[!] Copy assignment called.");
        if (this == &cptr)
        {
            return *this;
        }

        if (ptr_count && --(*ptr_count) == 0)
        {
            std::println("[!!] delete being called by copied-from object. (last owner)");
            delete object_ptr;
            delete ptr_count;
        }
        else if (ptr_count)
        {
            std::println("[!!] releasing current object, - {} owners remain", *ptr_count);
        }

        object_ptr = cptr.object_ptr;
        ptr_count = cptr.ptr_count;
        if (ptr_count)
        {
            ++(*ptr_count);
            std::println("[!!!] Pointer count increased! Currently: {}", *ptr_count);
        }
        return *this;
    }

    // Destructor must keep track of count to only delete heap object if last
    ~Counted_ptr() {
        if (ptr_count && --(*ptr_count) == 0)
        {
            std::println("[!!!] Last Counted_ptr! Deleting object.");
            delete object_ptr;
            delete ptr_count;
        }
        else if (ptr_count)
        {
            std::println("[!!!] Pointer count decreased! Currently: {}", *ptr_count);
        }
    }

public:
    T& operator*() const {
        if (!object_ptr)
        {
            throw std::runtime_error{"Dereferencing nullptr!"};
        }
        return *object_ptr;
    }

    T* operator->() const {
        return object_ptr;
    }

    int count() const {
        return ptr_count ? *ptr_count : 0;
    }

};

int main()
{
    {
    //$ ----- Exercise 10 ----- //
    std::println("<===== Exercise 10 =====>");
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
    std::shared_ptr<std::string> meow = std::make_shared<std::string>("Meow");
    delete raw_ptr_string;
    }
    {
    //$ ----- Exercise 11 ----- //
    std::println("\n<===== Exercise 11 =====>");
    std::vector<std::string> string_vec{ "This is", " a vector of", " strings." };
    Counted_ptr c_ptr1{ string_vec };
    std::println("First Counted_ptr constructed. Counter at: {}", c_ptr1.count());
    std::println("c_ptr1: {}", *c_ptr1);
    Counted_ptr c_ptr2{ c_ptr1 };
    std::println("c_ptr2: {}", *c_ptr2);
    Counted_ptr c_ptr3{ c_ptr2 };
    std::println("c_ptr3: {}", *c_ptr3);
        {
            Counted_ptr c_ptr4{ c_ptr1 };
            std::println("\nInstantiating #4 inside block.");
            std::println("Count on #1: {}", c_ptr1.count());
            {
                std::println("\nAnother inner block! Trying copy assignment.");
                std::vector<std::string> string_copy_as1{"Throw away string.", "Another throw away!"};
                std::vector<std::string> string_copy_as2{ "a", "b" };
                Counted_ptr copy_as_cptr1{ string_copy_as1 };
                Counted_ptr copy_as_cptr2{ string_copy_as2 };
                Counted_ptr copy_as_cptr3{ copy_as_cptr2 };
                copy_as_cptr1 = c_ptr1;
                copy_as_cptr2 = c_ptr1;
                copy_as_cptr3 = c_ptr1;
            }
        }
    std::println("Block ended. Count on #1: {}\n", c_ptr1.count());
    }

    return 0;
}