# Review Questions
1. What is an application domain?
2. What are ideals for naming?
3. What can we name?
4. What services does a Shape offer?
5. How does an abstract class differ from a class that is not abstract?
6. How can you make a class abstract?
7. What is controlled by access control?
8. What good can it do to make a data member private?
9. What is a virtual function and how does it differ from a non-virtual function?
10. What is a base class?
11. What makes a class derived?
12. What do we mean by object layout?
13. What can you do to make a class easier to test?
14. What is an inheritance diagram?
15. What is the difference between a protected member and a private one?
16. What members of a class can be accessed from a class derived from it?
17. How does a pure virtual function differ from other virtual functions?
18. Why would you make a member function virtual?
19. Why would you not make a member function virtual?
20. Why would you make a virtual member function pure?
21. What does overriding mean?
22. Why should you always suppress copy operations for a class in a class hierarchy?
23. How does interface inheritance differ from implementation inheritance?
24. What is object-oriented programming
---
### My Answers
1. Broadly speaking, an application domain is the kind of program we're trying to make. Knowing what kind of program we're trying to make helps us to determine the design principles of the program's code base; those principles end up being the fundamental application concepts and facilities for programmers. If we're trying to make a medical database program, then our design principles might focus on searching through large datasets, adding/removing data from those sets, presenting the data in a reasonable and useful way, and performing all of those functions efficiently (in a performance sense). We would then focus on implementing the relevant concepts of this medical database (e.g. names, ID's, dates, locations, symptoms, etc.) and the facilities for performing the aforementioned functions (organizing the data by aforementioned concept, or sorting relevant data chronologically, alphabetically, etc -- or, creating functions to output organized data into charts, tables, or JSON files, etc.). We should also consider the limits of the domain in conjunction with the purpose of our application. Our goal should be for an application to fulfill a specific role (rather than "do it all") then design our class hierarchies to reflect the application's functions within the limits of our goal(s).
2. The ideal for naming should be self-documentation. If you name something then write a comment explaining the name, then there is perhaps a more clear name that might be better. For example, "sortByLastName" rather than "sortBLN" or "sort2". Or, for variables, "diameter" rather than "r2". Our naming conventions should reflect the logic of operations -- for example, Shape's "add" versus "attach". 
3. We can name classes/structs/enums, functions, variables, and constant expressions. 
4. Shape is an abstract class that offers services necessary for derived classes such as setting color, fill color, line styles, it keeps the 'points' of shapes, it provides the pure virtual functions for draw_specifics, etc. It also handles the interaction between our graphics library and the underlying Qt library that's working with our operating system to draw windows and the elements within.
5. An abstract class cannot be instantiated as its own object whereas a non-abstract class can. Abstract classes help structure common facilities for their derived classes and help organize the hierarchy of our library. 
6. You can make a class abstract by giving it at least one pure virtual function.
7. Members of a class are controlled by access control -- whether they by member functions or data members. I think anything you can put into a class can be made public, private, or protected. You can put structs into the private part of a class and have functions in that struct as well.
8. Making a data member private is (usually) necessary to respect the principle of encapsulation. We want encapsulation as a design principle because it helps to document what data is internal to a class' purpose as opposed to what a user of that class should have access to. It also helps to prevent accidental modification of those data members by outside functions/code.
9. A virtual function is a function that can be overriden by a derived class. When a virtual function is called the program uses a vtbl to keep track of which function is to be used (starting at the most derived class to the base). ~~When a function is called through a pointer or a reference, the program determines (at runtime) whether to use the actual object's type (dynamic) or the type of the pointer or reference (static).~~  