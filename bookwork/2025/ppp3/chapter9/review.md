# Review Questions
1. Why is I/O tricky for a programmer?
2. What does the notation ```<< hex``` do?
3. What are hexadecimal numbers used for in computer science? Why?
4. Name some of the options you may want to implement for formatting integer output.
5. What is a manipulator?
6. What is the default output format for floating-point values?
7. Explain what **setprecision()** and **setw()** do.
8. Which of the following manipulators do not "stick": **hex**, **scientific**, **setprecision()**, **setw()**?
9. In **format()**, how do you specify where an argument is placed on output?
10. Give two examples where a **stringstream** can be useful.
11. When would you prefer line-oriented input to type-specific input?
12. What does **isalnum(c)** do?
13. When dealing with input and output, how is the variety of devices dealt with in most modern computers?
14. What, fundamentally, does an **istream** do?
15. What, fundamentally, does an **ostream** do?
16. What, fundamentally, is a file?
17. What is a file format?
18. Name four different types of devices that can require I/O for a program.
19. What are the four steps for reading a file?
20. What are the four steps for writing a file?
21. Name and define the four stream states.
22. Discuss how the following input problems can be resolved:
a. The user typing an out-of-range value
b. Getting no value (end-of-file)
c. The user typing something of the wrong type
23. In what way is input usually harder than output?
24. In what way is output usually harder than input?
25. Why do we (often) want to separate input and output from computation?
26. What are the two most common uses of the **istream** member function **clear()**?
27. What are the usual function declarations for ```<<``` and ```>>```
28. How do you specify where an argument is inserted into a format string in **format()**?
29. What is the notation for bases of decimal values in **format()**?
30. How do you specify the precision of floating-point values in **format()**?
---
### My Answers
1. I/O is tricky for a programmer for many reasons. While the stream functions of C++ provide a level of abstraction that eases the design of input/output streams, the inevitable variance of real-world data, end-user behavior, and technical implementations of devices/files/etc. creates opportunity for bugs and errors at every stage of an I/O stream. For example, real-world data may be formatted in a confusing and inconvenient way for a programmer who must work around the format; and, even within that confusing format there may be formatting errors a programmer must try to anticipate and handle. End-users make mistakes or may purposefully try to break a program; as well as our programs may be used on a variety of hardware which may introduce bugs if unaccounted for by the programmer.
2. It signals to the output stream to modify/format the stream as a hexadecimal value. So, if you write ``` cout << hex <<< 41 ``` the stream will output '29' instead of 41.
3. Hexadecimal numbers are used for representing memory locations in computer science because it is a base-16 number system that represents modern memory storage effectively. (Each hex digit represents exactly 4 bits)
4. One option I'd want to implement for formatting integer output is its precision level -- rounding to the hundredths for financial applications, thousandths for game statistics, and beyond for scientific applications.
5. A manipulator is something that manipulates the state of a stream -- "<< hex", "<< dec", and "<< oct" are the examples we've covered. They do not change the value of the integer being streamed but manipulate its ouput accordingly (i.e., as hexadecimal for << hex).
6. The default output format is precision 6. (Full answer: it uses general format (choosing between fixed and scientific notation based on the value) with 6 digits of precision).
7. setprecision() sets the precision output format of a number value, setw() sets the character-width of an output stream.
8. ~~setprecision() and~~ setw() do not stick. (Wrong: **setprecision() DOES stick,** but setw() indeed does NOT stick :))
9. Using format() you specify where an argument is placed using curly brackets. For example: ```format("Hello, {}!", string_var);``` where "string_var" can be defined as "World"
10. stringstream can be useful for extracting values from a formatted string or when trying to construct strings by concatenation. These are examples of "separat(ing) actual I/O from processing."
11. You would prefer line-oriented input to type-specific when reading through lines of a text file or when you need to deal with whitespaces effectively. Bjarne does state that many uses of getline() can be handled as type-specific input and that that is preferable because your code will then handle the input in a more robust way.
12. isalnum(c) returns "true" or "false" contingent on c being composed only of letters and numbers (no symbols or punctuation).
13. They are dealt with by the operating system through device drivers that then interface with the I/O libraries in C++.
14. An istream captures data from the buffer between the program and a "somewhere" on the system (where the "somewhere" could be a file, a keyboard stroke, or the click of a button in a GUI).
15. An ostream puts data into the buffer from the program that is then sent "somewhere" on the system (to a file, to the screen, to another program, etc.).
16. A file is a storage of bytes in memory -- be it locally or remotely.
17. A file format specifies how those bytes in memory are meant to be processed.
18. Four different types of device that can require I/O for a program are mouse, keyboard, screen, and local data storage.
19. The four steps for reading a file are: knowing the name of the file, opening the file, reading in the file, then closing the file.
20. The four steps of writing to a file are: knowing the name of the file, opening the file, writing data into the file, then closing the file.
21. Four stream states: bad() signals a corrupted stream (such as a corrupted file) that cannot usually be fixed by the program, fail() signals an error in a stream (such as the wrong type of input given into a stream), eof() signals a successful end of a stream, ~~badbit() signals an inappropriate value being provided to a stream~~. **(badbit() is not a stream state function!)** *The fourth stream state is good() which indicates that no errors have occured.*
22. 
    1.  [a] This can be resolved by checking the validity of provided values then returning to input if an invalid value is provided.
    2.  [b] Resolving end-of-file can be done by clear()-ing the stream and then executing the anticipated code following a successful EOF state or handling instead an unintended EOF state (by, for example, prompting the user to provide the next action)
    3.  [c] If the user types in a letter where a number is expected (say you're prompting input for an 'int' type and they enter the letter 'f') this can be handled with "isnum(c)" -- if "isnum()" returns false then you can provide an error message and prompt the user for the correct input.
23. Input is usually harder than ouput because of: input requirements being broken by user error, needing to process input and following formatting requirements, and working with various types of input while accounting for the previously mentioned issues in those various types.
24. Output is usually harder than input because of: formatting issues, quirks of input streams like whitespaces, checking the validity of the data being output, and needing to overload operators for whatever the stdl doesn't handle natively.
25. Separating I/O from computation simplifies the logic of a program. We want to isolate input and output so if there are errors we can handle them where they happen; likewise for computation -- if we keep computation logically distinct from I/O then not only is the code easier to read and understand, but computational errors can be isolated from errors in I/O.
26. We use clear() to reset istream errors (for example, if the stream state is bad()) and ~~to clear input buffers of whitespaces (for example, if using getline() before/after cin).~~ (That's wrong, we use ignore() for that)
27. ```cpp
    std::istream& operator>>(std::istream& is, X xx)
    std::ostream& operator<<(std::ostream& os, X xx)
    ```
28. ```format("Message: {:argument}", variable);```
29. ``` format("Decimal: {:dec}", number);```
30. You can use :a, :e, :f, :g, or specify the number with :.# (e.g. :.8) -- all within curly brackets.