# Review Questions
1. What is the default meaning of copying for class objects?
2. When is the default meaning of copying of class objects appropriate? Inappropriate?
3. What is a copy constructor?
4. What is a copy assignment?
5. What is a move constructor?
6. What is a move assignment?
7. What is a default constructor?
8. What is the difference between a copy constructor and a move constructor?
9. What is the difference between a copy constructor and a copy assignment?
10. What is shallow copy? What is deep copy?
11. How does the copy of a vector compare to its source?
12. What is the point of copy elision?
13. What are the essential operations for a class?
14. What is an explicit constructor?
15. When would you prefer a constructor not to be explicit?
16. How do you define traversal for a container?
17. What operations may be invoked implicitly for a class object?
18. What operators are often user-defined?
19. What is the rule of zero?
20. What is the rule of all?
21. Why don't we just always define a vector with a large enough size for all eventualities?
22. Which vector operations can change the size of a vector after construction?
23. What is the difference between reserve() and resize()?
24. How much spare space do we allocate for a new vector?
25. When must we copy vector elements to a new location?
26. What is the value of a vector after a copy?
---
# My Answers
1. The default meaning of copying for class objects produces a **shallow copy** where data members are simply copied surface level. So if a class object has a data member like ```int value = 50``` then the new/copied-to object will also have ```int value = 50```. This shallow-depth copy of a class object becomes problematic with dynamically-allocated resources.
2. This default meaning is appropriate for "simple" classes that do not acquire resources that need to be released (e.g. open files, thread locks, heap memory, etc.). An example of an appropriate use of default copying is a simple enemy class in a video game. Say you use an RNG for determining how many alien spacecraft should spawn at a location and they all have the same attributes and are "simple" in that they just have locally-stored health values -- in this case you can use default copying to produce the number determined by the RNG. Default copying is _inappropriate_ in the case of classes that **do** acquire the aforementioned resources because producing shallow copies of such resources will produce either dangerous copies (in the case of pointers to memory or file streams) or other undefined behavior (duplicated thread locks).
3. A copy constructor is called when a new class object is constructed out of another pre-existing object of the same class. It can be identified by the declaration ```MyClass(const MyClass& copied-from)```.
4. A copy assignment (operator=) is called when using ```=``` as an assignment operator where the lvalue and rvalue are both pre-existing objects of the same class. It can be identified by the declaration ```MyClass& operator=(const MyClass& copied-from)```.
5. A move constructor is called when a new class object is being constructed out of another pre-existing object of the same class **but** the pre-existing object is an **rvalue** such as a temporary object returned by a function (or, it can be the call std::move(MyClass)). "Move semantics" transfer ownership of data from the rvalue to the constructed object and leave the rvalue in an "unspecified but valid state." For example, the ownership of pointers are transferred and the pointers in the temporary object can be set to ```nullptr```, making them safe and ready for destruction. Move constructors can be identified by the declaration ```MyClass(MyClass&& moved-from)```. The ```&&``` is unique to move semantics and it is called an **rvalue reference**.
   1. Move construction calls (and copy construction calls for that matter) are often optimized away (eliminated) by compilers due to **copy elision** techniques (e.g. RVO, NVRO) where instead of constructing a temporary object then transferring ownership of the data from that temporary object to the new object, those data members are constructed directly at their final destination. Thus, the compiler omits the unnecessary object by constructing the values directly in the new object.
6. A move assignment (operator) is called when using ```=``` as an assignment operator where the lvalue is a pre-existing class object and the rvalue is a temporary object (such as one returned by a function) or the call std::move(MyClass). It can be identified by the declaration ```MyClass& operator=(MyClass&& moved-from)```.
7. A default constructor is called when a class object is instantiated without any provided initialization data. If we have MyClass with a single int data member that can be constructed with ```MyClass(int v) : value{ v } {}``` where the int value passed (e.g. ```MyClass object(5);```) initializes its data member, we can provide a default constructor that is called when a class object is instantiated without any provided value (e.g. ```MyClass object;```) by providing a non-parameterized constructor that sets the int value to a default value: ```MyClass() { value = 0; }```. Default constructors can be identified by a constructor declaration that has no parameters: ```MyClass()```.
8. The difference between a copy and move constructor is that a copy constructor leaves the copied-from object as-is (indeed it is passed by const reference) whereas a move-constructor transfers ownership of the data in the moved-from object to the constructed object and leaves the moved-from object in a "valid but unspecified state" (for example, int values can be set to 0, pointers are set to nullptr, strings are made empty, etc.).
9. Differences between a copy constructor and assignment are:
   1.  in a constructor call, the copied-to object is being initialized for the first time (i.e. constructed) using data from a pre-existing object of the same class, whereas in an assignment call both objects pre-exist
   2.  the syntax where the class type is declared for a constructor call (e.g. ```MyClass new_object = copied_from_object;```) whereas it is **not** declared for copy assignment because the copied-to object already exists meaning its type has already been declared (e.g. ```copied_to_object = copied_from_object```).
       1.  Copy assignment is idiomatically defined by overloading the assignment operator ```=``` where copy assignment always uses ```=``` whereas copy construction can use other syntax such as ```MyClass new_object(copied_from_object);```, ```MyClass new_object{ copied_from_object };```, or ```MyClass new_object = { copied_from_object };```. The difference remains that the ```new_object```'s type is declared in each of these instances because it is being constructed for the first time.
   3.  in copy construction, the new object's values can usually be directly initialized using the copied-from object's values: ```MyClass(const MyClass& copied_from) : value{ copied_from.value } {}```, whereas for copy assignment the copying must be done in the body of the copy assignment operator definition: ```MyClass& operator=(const MyClass& copied_from) { value = copied_from.value; }```. Please note that copies of pointers must be handled carefully by providing deep copies, if MyClass has a pointer to a double as a data member: ```MyClass(const MyClass& copied_from) : value{ new double{*copied_from.value} } { /* empty body */ }```.
10. If described in terms of how pointers are copied, as was done in the textbook (whereas I'm unsure if but suspect that indeed shallow/deep copies also differ for other more complex resources), then **shallow** copies copy a pointer where the copied pointer and original pointer now both point to the same object/memory, whereas **deep** copies copy what a pointer points to where there are now two distinct objects that are pointed to separately. For example, using our MyClass from the previous answer, a shallow copy would be: ```MyClass(const MyClass& copied_from) : value{ copied_from.value } { /* empty body */ }``` where our new object's ```value``` and the ```copied_from``` object's ```value``` now point to the same object/memory address! This is bad because if either object is destructed, the other object's destruction will call ```delete``` on an already-deleted memory address thus resulting in undefined behavior. A **deep** copy is one like in the previous answer, where a new allocation is called and initialized to the value of the object we're copying.
11. A copy of a vector differs from its source by:
    1.  name
    2.  the elements are copied to new memory locations
    3.  the capacity of the new vector is shrunk to fit the number of elements it contains (its size)
12. I seem to answer questions ahead of time, which may not be a bad thing. I'll provide a shorter and more general answer to this question here. Copy elision is a form of optimization provided by compilers when it determines that copy and move operations can be eliminated by directly constructing objects at their final destination. The point of copy elision is to eliminate (omit) the construction of unnecessary objects thus reducing the number of CPU instructions and minimizing the amount of memory allocations/deallocations.
13. The _essential operations_ of a class are: default constructors (if appropriate), constructors from one or more arguments, copy constructors and assignment, move constructors and assignment, and destructors. 
    1.  A default constructor may be appropriate if we have a class where it makes sense to instantiate an object with default values when an initializer is not specified. ```std::vector``` is a perfect example of this, where the user might want to instantiate an empty vector that might come into use later.
    2.  Constructors that take one or more arguments are appropriate according to the nature of our class. If we have a ```Patron``` class for a library system, we might want constructors that take only the patron's name as arguments and set something like ```bool senior_citizen = false``` by default unless provided at time of construction. This might look like a pair of constructors such as: ```Patron(std::string first_name, std::string last_name) : fn{ first_name }, ln{ last_name }, senior_citizen{ false } { /* empty body */ }``` and ```Patron(std::string first_name, std::string last_name, bool senior) : fn{ first_name }, ln{ last_name }, senior_citizen{ senior } { /* empty body */ }```. This isn't a great example but it provides an interface where the user could call ```Patron 0021("Jane", "Smith")``` for a non-senior and if the patron is a senior the user could call ```Patron 0022("Sammy", "Doe", true)```. 
    3.  Copy constructors and assignments ought to be specified if we want specified behavior when a copy of an object is created. The behavior can be something as simple as incrementing a global variable that tracks the number of enemies spawned in a game, or something necessary like providing deep copies of heap-allocated memory and their corresponding pointers.
    4.  Move constructors and assignments ought to be specified to provide mechanisms for efficient resource transfer, especially if we have complex resources being transferred such as file streams, heap-allocated objects, network connections or thread locks etc. These mechanisms can be used by the compiler to handle cases such as returned temporary objects being assigned to pre-existing objects or constructing new objects; they are also used by the compiler in explicit move operations like std::move(). Move semantics are described as enabling code to clarify "intent" -- I don't fully understand what this means but I think it means that when code transfers ownership of objects are can be explicit in how that transfer is handled. I think it this type of clarification might be more important in complex cases like handling network connections -- if we move a user object from a waiting room into a live server (like in MMO games) then it might be necessary to specify minutiae of network connection specifics between those two states. It is also the case that move semantics help clarify intent for more "simple" objects like vector and string.
    5.  A (non-default) destructor ought to be provided if our class acquires resources that require handling (deleting dynamically-allocated memory, closing files, etc.).
14. To describe what an explicit constructor is, I'll first explain _implicit conversion_. Stroustrup writes that "A constructor that takes a single argument defines a conversion from its argument type to its class" (pg. 738) which can be useful (as in the example he provides, I won't provide it for brevity's sake) but only if used "with caution". This statement means if we have a single-argument constructor such as ```MyClass(int x)``` then it **also** defines _how to convert int-types into MyClass objects_. This "how" is used by the compiler to interpret statements such as ```MyClass object = 10;``` where the compiler sees a new object being constructed with the operator ```=``` and so expects a MyClass object on the right side of ```=```. What we have instead is an int-type, however the compiler was provided instructions on how to convert int-types into MyClass-types by our constructor! Thus, because it has this instruction available to it, it **implicitly converts** ```10``` into a (temporary) MyClass object then uses that to initialize ```object```. (This is called **copy initialization**.) The process looks like this (assuming we prohibit copy elision):
    1.  Compiler sees ```MyClass obj = 10;``` and expects a MyClass object as the rvalue but encounters an int-type instead
    2.  Compiler sees MyClass has an int-constructor, so implicitly converts ```10``` into a temporary MyClass object using that constructor
    3.  Move constructs ```obj``` from the temporary object it created in step 2.
    
    While this might be of little consequence in our example, implicit conversion can create unintended consequences for classes like Vector from the textbook where ```Vector(int x)``` uses ```x``` to initialize the size of Vector (the number doubles contained in the Vector). In this case, a user might write ```Vector v = 10;``` expecting ```v``` to be constructed where ```v[0]``` is initialized to the value 10. Instead what happens is the compiler _implicitly converts_ 10 into a Vector object (using the int-constructor we provided) which instead constructs a Vector of 10 (empty) doubles. Another place where such conversion could happen is in function calls. If we have ```void print_v(const MyClass& obj) { std::println("Value: {}", obj.value); }``` and then call ```print_v(6);``` in main(), the compiler will implicitly convert '6' into a temporary MyClass object -- possibly an unintended and undesired outcome.

    What the ```explicit``` keyword does is prohibit the compiler from implicitly converting type conversions in instances like the example above. By specifying ```explicit MyClass(int x)``` the statements ```MyClass obj = 10;``` and ```print_v(6);``` will result in compiling errors because there is no implicit int-to-MyClass conversion available to the compiler -- that is, ```10``` and ```6``` will **not** be implicitly converted to MyClass objects using the int-constructor because that constructor was declared ```explicit```. What can be called, instead, is: ```MyClass obj = MyClass(10);``` and ```print_v(MyClass(6));```.

    It is now commonly considered good practice to declare all single-argument constructors ```explicit``` because requiring direct-initialization of objects in calls helps clarify intent.
15. You might prefer a constructor not to be explicit when the class has a single argument constructor that default-initializes parameters that are available to be set in other, multi-argument constructors. For example:
```cpp
class Account
{
public:
    Account(double c) : checking{ c }, savings{ 0 } { /* empty body */ }
    Account(double c, double s) : checking{ c }, savings{ s } { /* empty body */}
private:
    double checking;
    double savings;
};

int main()
{
    Account account00512 = 5000;           // okay, will convert '5000' into an account with 0 in savings
    
    return 0;
}
```
16. You define traversal (functions required for iterators and range-for loops to work) for a container by defining ```begin()``` and ```end()``` for a container. For example:
```cpp
class Container
{
public:
    Container(size_t s) : size{ s } { p = new double[s]; }

    double& operator[](size_t i) { return p[i]; }
    const double& operator[](size_t i) { return p[i]; }

    // Skipping all the (very necessary!) copy/move semantics

    ~Container() { delete[] p; }

    // Traversal requirements below!
    double* begin() { return p; }        // will return the first element
    double* end() { return p + size; }   // will return the address one past the last element
    // And, the const versions
    const double* begin() { return p; }
    const double* end() { return p + size; }

private:
    size_t size;
    double* p;
}

void print_container(const Container& c)
{
    for (const auto& i : c)
        std::cout << i << '\n';
}

int main()
{
    Container c(6);
    
    for (auto& i : c)   // will set each element in c to 0.0
        i = 0.0;

    print_container(c); // this will use the const version of begin() and end()

    return 0;
}
```
17. Without explicit declarations, I believe the compiler provides by default/implicitly: default constructor, copy constructor, and destructor.
18. Operators that are often user-defined are: assignment operators and comparison operators (e.g. ==, <, >, !=) -- however arithmetic operators, the subscripting operator, and the iostream operators (e.g. <<, >>) are also common user-defined operators.
19. The "rule of zero" is one of two popular rules of thumb regarding providing what Bjarne calls 'essential operations' for a class: "If you don't need to, don't define any essential operation" (p. 738).
20. The "rule of all" (also often called 'the rule of three' or 'five' -- because "people don't agree on how to count operations" (p. 738)) is the _other_ rule of thumb that states: "if you need to define any essential operation, define them all" (p. 738).
21. Defining a vector with a large enough space "for all eventualities" is inefficient and a waste of space! While one might want a vector containing a phone's entire contact list (which might include names, emails, phone numbers, time zones, etc.) which might utilize the space provided but one might also want a second vector containing just the user's phone's own number, email, time zone, and a few phone specifications which would highly under utilize the large space provided.
22. The vector operations that can change the size of a vector after construction (that we covered) are ```reserve()```, ```push_back()```, and ```resize()```. ```std::vector``` implementations often have other operations like ```shrink_to_fit()``` but we didn't cover those extensively in this chapter.
23. The difference between ```reserve()``` and ```resize()``` is primarily that ```reserve()``` only allocates memory if the argument provided exceeds the vector's existing allocation, whereas ```resize()``` can shrink a vector's capacity -- thereby (potentially) losing elements. 
24. In our implementation of Vector, we initially allocate enough space for 8 doubles. We then double the space every time we fill it: 8 -> 16 -> 32 -> 64, etc.
25. We must copy vector elements to a new location when we make a copy of that vector; because vector stores its elements on the heap we must provide the mechanism for a deep copy instead of a shallow one.
26. This question is a little vague so I'll provide several answers.
    1.  The value(s) of a vector's elements that has been produced by copying an existing vector match the original vector's, except for the pointer to that vector in this instance is unique (assuming we made a deep copy!).
    2.  The value of a vector's size does NOT match the origin vector's -- the size of the copy-constructed vector is shrunk to fit the number of elements.
    3.  If we are not literally 'copying' a vector but 'moving' one vector to another (possibly new) one, the value(s) of the moved-from vector are left in a valid but unspecified state (i.e. the elements are set to default values and the pointers are nullified) that is ready for destruction.