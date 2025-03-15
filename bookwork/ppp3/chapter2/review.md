# Review (selection)
Questions:

3. What notations can you use to initialize an object?
9. What is an object?
10. What is a literal?
11. What kinds of literals are there?
12. What is a variable?
13. What are typical sizes for a char, an int, and a double?
14. What measures do we use for the size of small entities in memory, such as ints and strings?
16. What is a definition?
17. What is an initialization and how does it differ from an assignment?
23. What is type safety and why is it important?
24. Why can conversion from double to int be a bad thing?
25. Define a rule to help decide if a conversion from one type to another is
safe or unsafe.
26. How can we avoid undesirable conversions?
27. What are the uses of auto?
---
Answers:
3. You can use:
```cpp
int x0 = 1;
int x1 = {1};
int x2 {1};
int x3 (1);
```
4. An object is a chunk of memory -- it is the "place" in which we store data.
5. A literal is the same thing as a fixed value defined by the code at run-time. It cannot be changed.
11. There are integer, character, string, float, boolean, and other types of literals.
12. A variable is a named object. A "place" in memory that we give a name which we can use to assign values to.
13. A char is 8-bits (1 byte), an int is 4-bytes, and a double is 8-bytes.
14. ...bytes?
16. A definition is a statement that defines a variable -- it can (and usually should) provide an initial value.
17. An initialization gives a value to a variable at its declaration -- its initial value. Assignment is simply giving a variable a new value. They are logically distinct. Assignments clear out previous values, initializations always encounter empty values.
23. Type-safety is observing the rules and norms for each type that you are using. That all objects are used only according to the rules for their type.
24. Because it could be a "narrow" conversion where data is lost going from 'double' to 'int'. The range of 'double' exceeds the upper limit of 'int'.
25. If the range of one type exceeds the range of another, you should not (it is unsafe to...) convert the first type into the second (e.g. double to int).
26. We can avoid undesirable conversions by knowing the life-cycle of an object and accounting for its range of possible values in the type we use to define it.
27. We can use 'auto' when the type is obvious at a variable's definition/initialization. It can be useful also for saving space for more complex definitions (which I currently do not understand.)