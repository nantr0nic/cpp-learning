# Review Questions
1. Why would we want to have different element types for different vectors?
2. What is a template?
3. What is generic programming?
4. How does generic programming differ from object-oriented programming?
5. What is a concept?
6. What benefits do we get from the use of concepts?
7. Name four standard-library concepts.
8. How does resize() differ from reserve()?
9. What is a resource? Define and give examples.
10. What is a resource leak?
11. List the three resource-management guarantees.
12. How can the use of a built-in pointer lead to a resource leak? Give examples.
13. What is RAII? What problem does it address?
14. What is unique_ptr good for?
15. What is shared_ptr good for?
---
# My Answers
1. This is what makes vector the useful generalized container that it is. Users want a container for a variety of element types to hold the various forms of data in their programs. What we could do is write a "vector" for each built-in or standard library type -- e.g. IntVector, DoubleVector, StringVector, etc. This would be not only repetitive but also difficult to maintain because if we wanted to update a member function we would have to update that function in each implementation, thus creating an opportunity to introduce errors, etc. The technique that could be used to generalize our solution is called **generic programming**, which C++ supports through the use of **templates**, where we can write the container once and generalize it across all types (constrained by concepts, if needed). This includes _user-defined types_ that would otherwise be unsupported by the container without templatizing our solution.
2. A template is a C++ language feature that is used with the keyword ```template``` and requires that we define **type variables** in angle brackets (e.g. ```template<typename T, typename S>``` which are used in the templatized code to represent the possible types to be used in that code (whether a class data member, a function call's arguments, etc.). Or, in Bjarne's words: they are a "mechanism that allows a programmer to use types as parameters for a class or a function" (pg. 764). Templates allow us to write code like ```Vector<T>``` or ```void print(const T& val)``` where T can be any type (or any type that has the properties of the concepts we require) -- thus allowing Vector to be instantiated with any type, and print() to print any type -- be it an int, string, or some user-defined type.
> Templatized code is not compiled into the binary and instead is used by the compiler to generate the appropriate code where it is called. This means if we write a templatized ```void print(const T& val)``` function but never call it in our code, that templatized code is ignored when the binary is being compiled. If we call ```print(some_string)``` then the compiler will generate a ```void print(const std::string val)``` function and pass ```some_string``` to that function where it is called. Thus, templates are a zero-overhead feature.
3. Generic programming is a programming technique (also sometimes called "algorithm-oriented programming", perhaps in other, non-OOP-oriented languages) of writing code that works with a "variety of types presented as arguments [...] as long as those argument types meet specific syntactic and semantic requirements" (p. 768). Perhaps one way to think of generic programming, as mentioned before, is it is a technique that allows programmers to write code that generalizes solutions to a variety of data types. Algorithms and iterator functions are good examples of generic programming. If we want a function that rearranges data from "least" to "greatest" (where a set of numbers are ordered by their numeric value and a set of strings are ordered by the number of characters they hold) we can write such a generalized solution using the generic programming technique and in C++ this requires using templates.
4. In C++, generic programming is: 
   1. a technique supported by templates that relies on compile-time resolution (i.e. templates are resolved when the code is compiled)
   2. allows types to be used as parameters in functions and as variables in classes

    Whereas, object-oriented programming is:
    1. a technique supported in C++ that allows for users to define data types and is supported by class hierarchies with virtual functions, inheritance, and polymorphism. 
    2. allows run-time resolution when calling virtual functions that use vtbls to determine calls within class hierarchies
   
>The two techniques can be combined, as we have in the templatized Vector class we built in this chapter.

5. A concept constrains the types that a template accepts by requiring those types to have certain properties such as "being copyable", "being divisible", "being order-able", etc. For example, if we want to write a function template that only accepts numeric types (note: ```bool``` and ```char``` are 'numeric' too!), we can constrain the type like so:
    ```cpp
    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    T& add_then_divide_etc(T& val) {
        // Ignoring errors and checks for brevity here...
        val += 1024;
        val /= (val * (1 / val));
        return val;
    }
    ```
    A concept can also be defined and used throughout templatized code (using ```std::is_arithmetic``` which includes integral and floating_point):
    ```cpp
    template<typename T>
        concept Numeric = std::is_arithmetic;

    template<Numeric T>
    T& add_then_divide_etc(T& val) {
        // Ignoring errors and checks for brevity here...
        val += 1024;
        val /= (val * (1 / val));
        return val;
    }

    template<Numeric T>
    T& another_function_template(T& val) {
        val += 2048;
        return val;
    }
    ```

6. The "benefits" of using concepts in templates is the ability to constrain the variety of types that our templatized code can accept and this narrows the focus of our code reducing chances for bugs and undefined behavior. We didn't cover the concepts in the STL in very much depth, but looking through the list I see (for example) ```std::equality_comparable<T>``` that guarantees two ```T```'s can be compared for equality using ```==``` to produce a Boolean result. I can imagine using this perhaps with a Shapes library where we have Circle, Rectangle, Triangle, and so on and wanting to write a function template that requires comparing instantiated shapes. Assuming we have overloaded ```operator==``` for each class, we can write a function template:
    ```cpp
    template<typename T>
        requires std::equality_comparable;
    void differentiate(const T& shape1, const T& shape2)
    {
        if (shape1 == shape2)   // assume this means they have the same area
        {
            shape1.set_fill(Color::Red);
        }
    }
    ```

And this would work if we wanted to color one of two identical Circle objects, Rectangle objects, or Triangle objects, etc.

7. Look at that! I already named four standard library concepts! But, here are a few more important ones:
   1. std::semiregular<T> -- "A T can be copied, moved, and swapped"
   2. std::regular<T> -- "T is semiregular and also equality_comparable"
   3. std::derived_from<D, B> -- requires that type D is publicly derived from type B. The example I came up with for this one is: a game where you have an abstract ```Enemies``` class that is the base class to particular bad guy classes (e.g. fighter, archer, etc.) and you want to templatize a function that only accepts user-defined types derived from ```Enemies```:
    ```cpp
    template<typename T>
        requires std::derived_from<T, Enemies>
    void attack(T& bad_guy) 
    {
        // bad_guy can be Fighter, Archer, Mage, Wolf class -- but only ones derived from Enemies class
        bad_guy.health -= 10;
    }
    ```
8. ```resize()``` can deallocate memory, truncating elements that are in a Vector -- meaning, if Vector has space for 16 ints and currently has 10 int-elements, you can call resize(8) which will shrink Vector to house 8 int-elements, freeing the elements in indices 8 and 9. ```reserve()``` never deallocates memory and instead, if reserving more than the current capacity, will request a new allocation, copy the existing elements to that new allocation, then free the old allocation.
9. A resource is anything that the program must request from the system and then "give back" when finished: memory, files, threads, input streams, etc. All forms of memory are resources, but particularly we must manage heap/free store memory manually where resources must be explicitly given back (handled by the programmer or by a standard template library function, etc.). Files must be requested from the system and then handled by the program, usually in the form of a file stream. A single stream cannot open two files, but the same file can be opened in multiple streams. The program must handle errors relating to that file -- such as it not existing, the system not giving us permission to either read or write to that file, etc. When the program is finished with the file, it must release that file back to the system. With an input stream we are requesting keyboard or mouse input from the system and the program must then handle that input itself.
10. A resource leak is when we fail to give back the aforementioned resources. A classic example is a memory leak, where we allocate memory then remove our access to that memory. File locks can be leaked where we lock a file in our program (stopping other programs from accessing that file!) and we may forget to release the lock when our program is done using that file. This results in that file being inaccessible until our program terminates.
11. The three guarantees are:
    1.  **The basic guarantee*: "A function either succeeds or throws an exception without having leaked any resources."
    2.  **The strong guarantee:* The basic guarantee + "all observable values (all values not local to the function) are the same after failure as they were when we called the function." This is the ideal but performance and maintainability issues may preclude our functions from providing the strong guarantee.
    3.  **The no-throw guarantee:* For simple operations where there is no risk of failing or throwing an exception, necessary for being able to write code that gives either the basic or strong guarantee.
12. I think we've beat this horse to death, but in any case:
    ```cpp
    int main()
    {
        double* p = new double[2048];
        double* q = new double{3.14};
        p = q;
        delete p;
        // don't delete q cuz that'd be a double delete (pun definitely not intended)
        // those 2048 8-byte memory blocks are lost to the abyss
    }
    ```
13. RAII stands for "Resource Acquisition Is Initialization". The problem it addresses is releasing resources when we are done using them. In C++, the technique relies on acquiring resources in a constructor and releasing them in a destructor so resources are acquired and released within the lifetime of an object and cannot outlive (thus be leaked) past an object or scope's lifetime. One alternative is handling resources through exceptions and this can quickly become cumbersome because if there are throws in an unexpected order then a resource can be leaked if the program goes back up the call stack before the program reaches the code where that resource is released. 
14. ```std::unique_ptr``` is an object that holds an un-re-assignable pointer and "represents ownership of what that pointer points to." Consequently, multiple ```unique_ptr```s cannot point to the same object, ensuring that the object has only one unique pointer pointing to it -- this prevents double deletes. ```unique_ptr``` is "a kind of pointer, [thus] inheritance works correctly. [...] You can use ```->``` and ```*``` on a ```unique_ptr``` exactly like a built-in pointer." (p.800) ```std::unique_ptr``` is also an example of RAII: because it _owns_ the object it points to, when it is destroyed, it destroys the object it points to -- thus preventing memory leaks. ```unique_ptr```s are made using ```std::make_unique```. Here are some examples of what has been described:
    ```cpp
    void this_is_impossible()
    {
        std::unique_ptr<double> p = std::make_unique<double>(1024);
        std::unique_ptr<double> q = p;  // this will not compile! 
    } // p and q (if it were legal) go out of scope here and delete the doubles

    double* raw_ptr(double value)
    {
        double* temp = new double(value);
        *temp *= *temp;
        return temp;  // release() gives up ownership, returning a raw pointer here
    }

    std::unique_ptr<double> smart_unique_ptr(double value)
    {
        double temp = value;
        temp *= temp;
        return std::make_unique<double>(temp);
    }

    int main()
    {
        double* p = raw_ptr(42);
        double* r = p;
        std::unique_ptr<double> q = smart_unique_ptr(42);

        delete p;   // need to manually delete
        delete r;   // Nope! this will result in undefined behavior (a crash!)

        return 0; // q doesn't need to be explicitly deleted, it is destroyed here
    }
    ```
15. ```std::shared_ptr``` is a "smart pointer" similar to ```unique_ptr``` with the major difference that it allows many copies -- that is, multiple ```shared_ptr```s can point to the same object and those pointers can be deleted in any order. ```shared_ptr``` keeps count of the number of ```shared_ptr```s pointing "to a given object and when that use count goes to zero, the ```shared_ptr```'s destructor deletes the object pointed to." (p. 802). Here is an example:
    ```cpp
    std::shared_ptr<std::string> smart_shared(const std::string& value)
    {
        return std::make_shared<std::string>(value);
    }
    int main()
    {
        std::string cat{"Meow meow!"};
        std::shared_ptr<std::string> one = smart_shared(cat);
        std::shared_ptr<std::string> two = one; // this is allowed (unlike unique_ptr)
        // one.use_count() would return 2 here

        std::shared_ptr<std::string> dog = std::make_shared<std::string>("Woof woof!");
        two = dog;
        // dog.use_count() would return 2 here, one.use_count() would now return 1


        return 0;   // one, two, and dog would be deleted here
    }
    ```
    This isn't a very good example because shared_ptr becomes most useful when dealing with (for example) functions that accept base class pointers and return derived class pointers. I'm too tired to make up my own example, so here's a slightly modified example from the book (p. 802):
    ```cpp
    std::shared_ptr<Shape> read_shape(std::istream& is)
    {
        // will return any derived class as Shape*
        if (reading_circle)
            return std::make_shared<Circle>(center, radius);
        if (reading_rectangle)
            return std::make_shared<Rectangle>(width, height);
        // caller gets shared ownership regardless of actual type
    }
    ```