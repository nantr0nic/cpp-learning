# Review Questions
1. What does "Caveat emptor!" mean?
2. What is an array?
3. How do you copy an array?
4. How do you initialize an array?
5. When should you prefer a pointer argument over a reference argument? Why?
6. When should you prefer a span over a pointer? Why?
7. How does std::array differ from a built-in array?
8. What good is range checking?
9. What information do you need to do range checking?
10. What good can a not_null do?
11. What is a C-style string?
12. What is a palindrome?
---
# My Answers
1. "Caveat emptor" means -- "Let the buyer beware!" In the context of this chapter I believe Bjarne is referring to the dangers of using raw pointers and arrays where it is easy to encounter range-bound errors and other mistakes that result in undefined behavior.
2. An array is a set of contiguous memory locations (can be static, stack, or heap ) defined a type's size (e.g. int, double, char). So, an array of 4 ints will start at one memory location, then assign an additional three memory locations of 4 bytes each. You can access those ints using subscripting like array_variable[0] for the first element, array_variable[2] for the third and so on. It is up to the programmer to manage and keep track of the elements in the array (if they are not using a container from the STL).
3. You copy an array with a for loop that uses subscripting to copy each element from one to the other, however, it is up to the programmer to avoid range-errors. One common technique is to write a function that takes the array size as an argument -- the impetus then falls on callee since if an incorrect size if provided the function will use those memory addresses anyway and possibly result in undefined behavior.
4. You initialize an array using curly brackets after the array is declared: ```int x[4] {1, 2, 4, 8};```
5. You should prefer a pointer argument over a reference argument when "'no object' (represented by nullptr) is a valid argument" (p. 698) -- remembering, of course, to test for nullptr. Bjarne writes, "the choice depends on the nature of the function" and while each has "attractions and problems" the validity of null arguments can act as a crucial deciding factor.
6. You would choose a span argument over a pointer argument when the argument consists of a range of elements. Since a pointer doesn't "know" how many elements it is meant to represent the functions that operate on pointers of varying elements can easily result in errors and undefined behavior. Instead, std::span can be used because it "remembers" the number of elements it represents. This inhibits the usual errors that result from pointers to ranges of elements.
7. The STL array does not "implicitly produce a pointer" (p. 704) unlike the built-in array that "converts to a pointer at the slightest provocation" (ibid). It "remembers" its own size by deduction from the type that is used to initialize the std::array -- that is, if initialized as ```std::array<int, 4>``` then it initializes 4 sizeof(int). Another difference is when initializing the elements of an std::array, it can default initialize elements that are not explicitly initialized in its definition: in ```std::array<string, 3> example{"Hello,", "world!"};```, example[3] is default initialized to the empty string "".
8. Range checking is imperative because a failure to remain within the bounds of an array's range can produce anything from inaccurate results to "disastrous" undefined behaviors like run-time crashes.
9. To do range checking you need to know the type of the array (e.g. int, double, char, etc.), the number of elements an array represents, and the location/address of the first element (or, alternatively, the location/address of one of the elements and the position of that element in the array).
10. not_null handles checks for nullptr in a safer way that inhibits program crashes. I actually couldn't get not_null to work, nor do I want to install and link Microsoft's GSL library so I couldn't test it.
11. A C-style string is an array of char's that is "zero-terminated" (or, more properly, "null-terminated") -- the C-style string ```char meow[] = "Meow"``` has a '0' at position meow[4] that signals the end of the string. If you modify it thus: ```meow[2] = 0;``` the string will then read "Me". It is how "strings" were accessed prior to C++ and still serves as the foundation of std::string.
12. A few (non-mutually exclusive) ways to define a palindrome are:
    1.  that is spelled the same backwards (including the one-letter words 'a' and 'I'),
    2.  a word where the first and last letter are the same and each letter after/before those letters also match
    3.  (recursive definition:) "a word is a palindrome if the first and last characters are the same and if the substring you get by removing the first and last characters is a palindrome"