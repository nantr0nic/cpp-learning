# Review Questions
1. Why does code written by different people look different? Give examples.
2. What are simple questions we ask of data?
3. What are a few different ways of storing data?
4. What basic operations can we do to a collection of data items?
5. What are some ideals for the way we store our data?
6. What is an STL sequence?
7. What is an STL iterator? What operations does it support?
8. How do you move an iterator to the next element?
9. How do you move an iterator to the previous element?
10. What happens if you try to move an iterator past the end of a sequence?
11. What kinds of iterators can you move to the previous element?
12. Why is it useful to separate data from algorithms?
13. What is the STL?
14. What is a linked list? How does it fundamentally differ from a vector?
15. What is a link (in a linked list)?
16. What does insert() do? What does erase() do?
17. How do you know if a sequence is empty?
18. What operations does an iterator for a list provide?
19. How do you iterate over a container using the STL?
20. When would you use a string rather than a vector?
21. When would you use a list rather than a vector?
22. What is a container?
23. What should begin() and end() do for a container?
---
# My Answers
1. This is a hard question to answer but I'll give it a go: 
   1. There are the various syntax styles that different people use when programming in C++. Two popular styles are K&R and Allman (I prefer the latter) -- this results in the first obvious difference. In conjunction with this superficial difference there are also personal preferences and common application conventions. Some personally prefer camelCase to snake_case, some list constructor member initializers on the same line, some (like myself) prefer them on separate lines, some edit their code to not exceed 79 characters wide, some go as far as 110, etc. Certain conventions exist within application domains, like I've noticed game development C++ is usually in Allman style and uses m_name for class data members. Oh, and not to mention the infamous spaces vs tab :)
   2. There are "versions" of C++ where new features are introduced with each consecutive release (meaning C++98, C++11, C++20, the upcoming C++26, etc.). Type deduction using 'auto' has been extended a few times, for example C++20 introduced "abbreviated" function templates using auto. Move semantics were introduced in C++11. These features can make code look quite different -- some individuals and organizations choose to stick with a set of features and so may produce new code in 2025 but restrict their code to features up to C++17, for example. The variety of features available also engender various coding conventions that might be particular to a "style" of programming. 
   3. There are four "paradigms" of programming, we have covered three of them and their application in C++: procedural, functional, object-oriented, and generic programming. Sometimes the same problem can be solved in each of these paradigms but the solution will look very different between these paradigms.
   4. More pertinent to this chapter, there are a variety of implementations that can be used for solutions to the same problem even within a paradigm. Point in case: for a text editor, one can use ```std::vector```, ```std::list```, ```std::array```, ```std::string``` to implement the same feature (e.g. storing a line of text) or use all of these implementations in varying combinations for different features (e.g. a vector of strings for a page of lines, a list of character arrays for an editing buffer) -- or, ultimately, if one really wanted to (or was sticking with C programming) all of the same features could be implemented with only arrays and pointers. This wide variety of possible solutions to the same problems results -- inevitably -- in different looking code from different people.
   5. Lastly, there are differences in approach to things like memory managment and exception handling. This might vary for a number of reasons: where the software is to be used and by whom impacts our approach; if an exception being thrown is it impacting a critical system (e.g. hospital equipment or public infrastructure); if we are writing code for a tiny embedded device we might prefer manual memory management over code that might perfectly exemplify RAII, etc.
2. This is a vague question. To answer vaguely, we ask simple questions like: what kind of data is it (what data types does it contain); how is (or should) this data be organized; is this data mutable or should is it just for "reading"; how should this data be stored (in relation to our code, not physically).
3. In this chapter we saw that we can store data in STL containers like ```std::array```, ```std::vector```, ```std::list```, but there are more containers available to us from the STL.