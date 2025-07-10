# Explanation of "Try This" on Page 742
![alt text](snap1.png)

+ **Line 3:** This is a value that will help us keep track of constructions/copies/movement/etc.

+ **Line 5:** This will print and provide the memory address, operations, current value and new value (in parentheses) for each operation.

+ **Line 9:** ```X() { /* code */ }``` is the **default constructor** -- it is 'default' because it is takes no parameters. If X is instantiated with only a name and no value, the default value of 0 will be assigned to int val. Example: ```X a;``` <-- an X object 'a' will be default constructed with int val = 0 and out() will print X().

+ **Line 10:** This is a constructor that takes an int type as a parameter. If X is instantiated with an int, ```X a(3)```, then an X object 'a' will be constructed with int val = 3 and out() will print X(int).

+ **Line 11:** ```X(const X& x)``` is a special constructor called a **copy constructor** that is called when X is instantiated with a pre-existing X object as a parameter. The X object to be copied is passed as a constant reference, thus ensuring the original object is unmodified and is passed directly (via reference) to the constructor without an additional (in this case a third(!)) copy being made. Example:
```cpp
X x1(3)     // First object
X x2{ x1 }; // x2 is copy constructed
```
In this code, out() will print X(X&), 0 (the current value of this), x.val's int value in parantheses (this will be repeated the all out() prints). The val of ```this``` (the object being constructed) will be assigned the value of x's val.

+ **Line 12:** ```X(X&& x)``` is a special constructor called a **move constructor** that is called when a temporary X object (rvalue [such as an X object being created then returned by a function]) or an object explicitly moved with std::move() is used to construct to a new X object. The `&&` notation is called **rvalue reference** -- so named because historically it denoted the value on the right side of an assignment. Example:
```cpp
X function(int n) 
{
    X temp(n);
    temp.val += 1;
    return temp;
}
int main()
{
    X local_x = function(4);
    // local_x.val will be 5
}
```
The move constructor will move val from 'temp' directly to local_x as opposed to creating a complete X object temp, then copy temp to local_x, then delete temp. Instead of creating the unnecessary copy of temp, it 'moves' the values of temp to the caller (in this case local_x). While seemingly not a heavy operation in this example, the same would be applied to (for example) a vector of 100 elements of >16 character strings where the consequences of an unnecessary copy are more severe.
> **_Note =>_** Modern compilers (mine included: Clang 20.1.7) often apply **Return Value Optimization (RVO)** and can "eliminate the move constructor call entirely and instead construct the object directly in the caller's memory". 
In our code, this constructor will have out() print X(X&&), set val (of ```this`) to x's val, then set x's val to zero after copying is complete (preparing it for deletion).

+ **Line 13:** ```X& operator=(const X& x)``` 