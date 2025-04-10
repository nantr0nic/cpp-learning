# Review Questions
---
1. What is the difference between a declaration and a definition?
2. How do we syntactically distinguish between a function declaration and a function definition?
3. How do we syntactically distinguish between a variable declaration and a variable definition?
4. Why can’t you use the functions in the calculator program from Chapter 5 without declaring one or more of them first?
5. Is int a; a definition or just a declaration?
6. Why is it a good idea to initialize variables as they are declared?
7. What can a function declaration consist of?
8. What is the suffix return type notation, and why might you use it?
9. What good does indentation do?
10. What is the scope of a declaration?
11. What kinds of scope are there? Give an example of each.
12. What is the difference between a class scope and local scope?
13. Why should a programmer minimize the number of global variables?
14. What is the difference between pass-by-value and pass-by-reference?
15. What is the difference between pass-by-reference and pass-by-const-reference?
16. What is a swap()?
17. Would you ever define a function with a vector<double> as a by-value parameter?
18. Give an example of undefined order of evaluation. Why can undefined order of evaluation be a problem?
19. What do x&&y and x||y, respectively, mean?
20. Which of the following is standard-conforming C++: functions within functions, functions within classes, classes within classes, classes within functions?
21. What goes into an activation record?
22. What is a call stack and why do we need one?
23. What is the purpose of a namespace?
24. How does a namespace differ from a class?
25. What is a using declaration?
26. Why should you avoid using directives in a header?
27. What is namespace std?
---
### My Answers
---
1. For a variable: a declaration defines a type and a name without any value/object being initialized for that variable. A definition of that variable defines the type, name, and also initializes that variable with a value or object. For a function: a declaration declares a function's name, its type (and what it does/doesn't return) and the types of arguments it takes (if any). A definition of that function provides the function body: the actual code that is executed when that function is called.
2. A function declaration contains a type, a function name, and the parameters/formal arguments contained in parentheses with a semi-colon on the end. A function definition contains the aforementioned elements but does NOT end in a semi-colon and instead contains a code block enclosed within curly braces.
3. A variable declaration contains a type and variable name with a semi-colon on the end; whereas a variable definition contains a type, name, and a value/object after an '=' sign, within curly braces, parentheses, or a combination of '=' and curly braces.
4. Because they all call each other and a function can only be used/called *after* it is declared. 'The compiler needs to know their signatures (name, return type, and parameters) to resolve calls'.
5. "int a;" is a declaration.
6. It is a good idea to initialize variables as they're declared to ensure type safety and help prevent memory issues that can result from uninitialized variables.
7. A function declaration can consist of a type, name, and the function's parameter / formal argument list. 
8. "Suffix return type" notation looks like: `auto function_name(int x, int y) --> int;` and it might be used when writing functions with user-defined types that can look confusing if written traditionally.
9. Indentation organizes code by aligns code blocks within their corresponding parts (e.g. while, for, if-else, etc.). This provides clarity to the code making it more readable and thereby also helping to avoid common mistakes.
10. The scope of a declaration is the code block within which it is declared -- it falls out of scope as soon as the code block is finished executing. For example, anything declared within a 'for-loop' falls out of scope (ceases to exist) as soon as the for-loop ends. Declarations made in the global scope come into existence at the time the program is executed and are destroyed when the program finishes its execution.
11. There are the following scopes: global scope, a function's scope (including the main() function), a class scope, a loop scope (while and for), and an if-else block scope. For brevity I will not provide an example of each.
12. A class scope is what is accessible to all the elements within a class (e.g. the private data members of a class). A local scope is what is accessible within a specific code block such as within loops, functions, and if-else blocks (e.g. `for (int x : vector<int> scores) { code }`)
13. Global variables are bad practice because, being in global scope, they are vulnerable to be manipulated by any function within the code, potentionally resulting in unintended modification and therefore bugs. It can be difficult to debug code that uses global variables. Relying on global variables can mean that your code is unfocused and should be further refactored and improved.
14. Pass-by-value is when you pass a variable as a function's formal argument that is then copied in memory and used in the code block of that function. Pass-by-reference is when you pass a reference to an existing variable as a function's formal argument. Rather than making a copy of the data used as an argument in that function, the reference acts as an alias to the already existing, stored memory of that variable. When you pass a variable as an argument to a function (pass-by-value) the copied variable falls out of scope at the conclusion of the function; whereas, when you pass a reference to a variable as an argument to a function (pass-by-reference), however the function may manipulate the variable (via the reference) persists after the conclusion of the function (e.g. a 'swap' function).
15. Pass-by-reference is mutable, whereas pass-by-const-reference is immutable. Meaning, the variables being referenced and designated 'const' can *not* be manipulated by the function they're passed to. A 'swap' function would not work if the two variables passed to it were declared as constant references.
16. Swap() swaps the value of two variables. So if int x = 0 and int y = 1, swap() would make int x = 1 and int y = 0. 
17. You could, but a vector of double data type could be very large in which case it would be preferable and more resource efficient to define the parameter as by-reference.
18. Undefined order of evaluation refers to "situations where the language standard does not specify the sequence in which sub-expressions of an expression are evaluated." If writing overly complicated code or manipulating the value of a variable more than once in a single expression, then the undefined order of evaluation in sub-expressions can lead to unpredictable outcomes. Compilers and linkers each have their own set of rules for interpreting and optimizing code, so they might interpret such sub-expressions in an unanticipated way. Beyond that, even if the compiler *you* are using behaves as you would expect, the same code compiled by a different compiler or on a different system might produce a drastically different outcome -- this renders the code *non*-portable.
19. x&&y mean x and y -- if passed as an argument then it is necessary for x and y to both be true. x||y means x or y -- if passed as an argument it is necessary that either (1) x and y are both true, or (2) one of x or y are true (while the other is false) -- x||y only fails when x and y are *both* false. Also, these operands follow an order of execution where the first (left-hand) operand can execute or halt the evaluation. For &&, the evaluation is halted if the first operand is false -- for || the evaluation is executed if the first operand is true. This is sometimes called "short-circuit evaluation."
20. "Functions within functions" and "classes within functions" do NOT follow standard-conforming C++. "Functions within classes" and "classes within classes" DO follow standard-conforming C++.
21. The activation record stores (on the 'stack') the execution (calls) of functions and their arguments (variables) in the order they are called. At the end of each record is also the 'implementation stuff' that is the "information that the function needs to return to its caller and to return a value to its caller." As functions complete their execution, they are taken off the stack / out of the record in the reverse order of how they were called ("Last in, first out."). Once a function completes and returns a value to its caller, it is taken off of the stack. 
22. A call stack is the processor-bound memory that stores functions' implementation data and their arguments. I don't know how to answer the question "why do we need one"... I suppose a call stack is needed because when a function is called the program needs to reserve memory for its arguments (ones determined at runtime) and implementation data. The ordering of the call stack is necessary because a function can call another function with the same arguments and a series of returns must be executed before the first function can return to the original caller. Ordering this data in "last in, first out" order seems to me the only logical way to organize this data. (A.I. Added: 'It ensured proper execution flow when nested or recusive functions are used.')
23. A namespace can separate off and group classes, functions and variables together under a common name. So if you want to write a class called "Shape" but don't want it to interfere with the many other classes named "Shape" in the various libraries that exist, you can create a namespace for your "Shape" class to distinguish it from the others. (e.g. myNamespace::Shape)
24. A namespace groups classes, functions, and variables under its alias; a class is a user-defined type that creates an object when its called.
25. A 'using' declaration specifies the namespaces or fully-qualified names that are being used in a code file -- after declaring the fully qualified name with 'using', the class/function/variable can be called directly or by shorthand. (e.g. `using std::cout;` allows us to simply use `cout` throughout the rest of the code.)
26. You should avoid "using" directives in a header to keep the code portable and to prevent potential conflicts with other namespaces down the line.
27. "std" is the standard namespace that contains the C++ standard library.