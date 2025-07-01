# Review Questions
1. Why do we need data structures with varying numbers of elements?
2. What four kinds of storage do we have for a typical program?
3. What is the free store? What other name is commonly used for it? What operators support it?
4. What is a pointer?
5. What is a dereference operator and why do we need one?
6. What is an address? How are memory addresses manipulated in C++?
7. What information about a pointed-to object does a pointer have? What useful information does it lack?
8. What can a pointer point to?
9. What is a leak?
10. What is a resource?
11. What is another term for "free store"?
12. How can we initialize a pointer?
13. What is a null pointer? When do we need to use one?
14. When do we need a pointer (instead of a reference or a named object)?
15. What is a destructor? When do we want one?
16. When do we want a virtual destructor?
17. How are destructors for members called?
18. How do we access a member of a class through a pointer?
19. What is a doubly-linked list?
20. What is this and when do we need to use it?
---
# My Answers
1. We need data structures with varying numbers of elements because -- it seems -- this is a most useful and desirable requirement for manipulating data. I can't picture being very happy with any program that restricts me to a specific number of elements in a data structure I'm working with; nor one that doesn't allow me to add or remove elements to that structure. The example we went through in the chapter was (doubly-) linked lists: they would be incredibly less useful without the ability to add, remove, shift, or copy (to other **empty** lists) elements -- all which makes such lists one of "varying number." On a more granular level, as a programmer I want to give the end-user the freedom to determine how many elements they want in their data structure so I must anticipate this by providing data structures that can have varying numbers of elements.
2. The four kinds of storage are: 
   1. Code Storage (aka Text Storage) -- This is the memory for your code itself
   2. Static Data -- This is the memory for global variables
   3. Free Store (aka the Heap or Dynamic Memory) -- this is "free" memory available to the program
   4. Stack -- This holds (generally) non-heap runtime memory like called functions and their arguments, local variables
3. The free store is "free memory" on the RAM reserved for the program. Data needs to be explicitly allocated to the 'free store' (I prefer the more general, other name: heap) by using operators like 'new' (and, consequently removed with 'delete') and '[]'. Besides these operators it is also the case that certain facilities like std::vector allocate their data to the heap (the vector object is on the stack but it allocates its elements to the heap); std::string is also (automatically) allocated to the heap past a certain length of characters (i.e. when it exceeds what the compiler determines is the limit of 'small string optimization' (SSO)).
4. A pointer is a local variable that stores a memory address. A pointer is a variable that *points to* a different memory address, often the memory address of another variable or a memory location on the heap such as the first element of an array.
5. A de-reference operator is used with pointers to access the value of the memory address that the pointer is pointing to; we need them in order to have access to that value (reading, writing, manipulating, etc.). So
   ```cpp
   int* p = new int { 8 };
   std::cout << "p (the memory address p points to (on the heap...)) is: " << p << '\n';
   std::cout << "&p (the memory address of p itself (on the stack...)) is: " << &p << '\n';
   // dereferenced p (below) will return the int value '8'
   std::cout << "*p (dereferenced, the value of the memory address p is pointing to) is: " << *p << '\n';
   // Also, we can manipulate the value as expected...
   *p += 5 // result: 13
   *p = some_function(*p);
   ```
6. An address is (usually seen as) a hexadecimal value that represents a location in memory (usually in RAM). Memory addresses are manipulated -- in the material we've so far covered -- with pointers and arrays. If we assign an array of 10 int elements to the heap they will be contiguously assigned in the order they're declared. If you inspect the memory you will see the 10 elements (4 bytes each) spanning a 40-byte section of memory.
7. The information that a pointer has about the object it points to is whatever is the address of that object's first element. The useful information it lacks is the address list of that object's constituent elements -- meaning, if you make an array of 10 int elements, the pointer will point to the first element but lack the information about the following 9 elements.
8. A pointer can point to the memory address of any type (or 'no type' with void*). Or, states another way: a pointer is an object that holds an address value. Bjarne writes that a pointer must be specified with a type so the pointer can expect the data it will be pointing to; however, a different reputable source has said that a pointer is simply a variable that stores a memory address and that is all -- the 'type' you give a pointer is a requirement of the compiler to know how to interpret any further access/manipulation of that pointer but not a requirement of the pointer itself as such. Regardless, a pointer "can point to" any type -- built-in or user-defined.
9. A leak is when memory is allocated but not de-allocated -- the access to that memory is lost and cannot be retrieved (during the lifetime of the program). This can be done by ```double* n = new double[5] {1, 2, 3, 4, 5}; /* some code, but whoops never a delete[] n; */ ``` A possibly innocuous issue on a small pedagogical level but if done with large data types with more complex programs the result can be severe. Some recently released video games were suffering a memory leak that became apparent in the render performance when played for >60 minutes causing users to stop playing that game and wait for a fix.
10. A resource can be any data that the program utilizes for its function such as "files, threads, locks" -- also, as we've seen, memory stored on the heap. Resource management is important to mitigate issues such as memory leaks, but also when we structure constructors and destructors. Any class that utilizes resources must acquire them (e.g. in their constructor) and release them when appropriate (e.g. in their destructor).
11. Is this a repeat of question #3? A couple other common terms for "free store" is 'the heap' and 'dynamic memory'.
12. We can initialize a pointer by assigning it a non-null value like ```int* p { new int{ 5 } }```, by assigning it another pointer like ```int* q { new int{ 5 }}; int* p { q };```, by initializing it with "nullptr" to avoid unanticipated behavior ``` int* p { nullptr };```, or if we're assigning a pointer to an array we can initialize the array immediately: ```int* p { new int[5] { 1, 2, 3, 4, 5 } };```
13. A nullptr is a "null" or "0" value assigned to a pointer to 'clear' the pointer of its address, reserve the pointer variable for subsequent use, or to clear it prior to deletion to inhibit undefined behavior.
14.  
