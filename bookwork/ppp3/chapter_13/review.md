# Review Questions
1. What is a function of one argument?
2. When would you use a (continuous) line to represent data? When do you use (discrete) points?
3. What function (mathematical formula) defines a slope?
4. What is a parabola?
5. How do you make an x axis? A y axis?
6. What is a default argument and when would you use one?
7. How do you add functions together?
8. How do you color and label a graphed function?
9. What do we mean when we say that a series approximates a function?
10. Why would you sketch out the layout of a graph before writing the code to draw it?
11. How would you scale your graph so that the input will fit?
12. How would you scale the input without trial and error?
13. Why would you format your input rather than just having the file contain "the numbers"?
14. How do you plan the general layout of a graph? How do you reflect that layout in your code?
---
# My Answers
1. I think this question is asking about functions that take a single type of argument? So, any function with a single argument type satisfies this question. Here are a few examples:
```cpp
double one(double) { return -1; }
double square(double x) { return x * x; }
double divide_by_itself(double x) { return x / x; }
```
But, I guess, simple member setter functions would also count? Like:
```cpp
class myClass
{
private:
    std::string name {};
public:
    std::string set_name(const string& n) { name = n; }
}
```
2. You would use a continuous line to represent data when the two dimensions (x and y) are directly related; for example, population change over time where X represents time in decades and Y represents population in millions (of people). You would use discrete points where the two dimensions are not directly related; for example, number of billionaires and unregistered cars in Oregon where X represents the former and Y the latter -- since these two data sets are unrelated (yet can still be graphically represented) we would use marks to show the pair of those data points over some scale (X could be scaled by a factor of 1 and Y could be scaled by a factor of 100).
3. The mathematical formula that defines a line is y = mx + b and the 'm' in that formula is the slope. You can represent the slope 0.5 as ```double slope(double x) { return 0.5 * x; }
4. A parabola is a U-shaped graph that represents y = x^2 or the function ```double square(double x) { return x * x }``` -- it faces "up" unless you negate the result of the function: -(square(x))
5. You make an X and Y axis using the Axis class where you must initialize it with its orientation, its left/bottom point of origin, the length of the axis, the number of notches, and a label. Here's an example of axes from our exercises:
```cpp
constexpr int xmax = 600;
constexpr int ymax = 600;
Axis x {Axis::x, Point{100, ymax / 2}, 400, 20, "1 == 20 pixels"};
Axis y {Axis::y, Point{xmax / 2, 500}, 400, 20, "1 == 20 pixels"};
```
6. A default argument is the value that a parameter is passed with if the caller does not specify a value. This can be true of functions as well as constructors. An example of the former might be 
```cpp
int add_a_number(int x, int y = 1) { return x + y; }
```
And an example of the latter might be
```cpp
class Tree
{
public:
    Tree(const string& leaf_color = "green") { /* ... */ } 
};
```
You would use a default argument if there is a default value that is reasonable and usually does not need to be specified unless the user requires it to. An example might be a Tree class with a default value ```string leaf_color = "green"``` because most trees have green leaves but if the user is instantiating a Japanese Maple then they can change the leaf_color to dark_red or whatever is appropriate. 
    
7. Perhaps a deceptively simple question? You add functions together by writing a third function that returns their sum? For example:
```cpp
double add_five(double x) { return x + 5; }
double square(double x) { return x * x; }
double third_function(double x) { return square(x) + add_five(x) }
```
8. You color it by using ```function.set_color(Col_type)``` and you label it by creating a Text object and setting its string to the desired label and its point to where along the function you want the label to be (function.point(0) is its starting point -- a convenient place for a label).
9. A series approximates a function when its graph matches an increasing number of points along the function when its series is repeated.
10.   Sketching out the layout of a graph prior to writing the code for it can provide an outline of the surrounding space and the calcualtions you'll require for placing the graph according to your expectations.
11.   You scale your graph to the range of the X and Y axes. There are parameters in the Function constructor for the range of the function that should match the range your axes represent and there are x and y scale parameters that will help scale the function to match the notch spacing of the two axes.
12.   I would scale the input to the notch spacing of my axes.
13.   Because in the real world there might be variance in the file that our program should account for rather than require those who input the numbers into our file to be infallible.
14.   You decide on a window size and how your graph axes should be laid out within the window (x and y meeting at (0,0) in the center of the window? or X from 0 to 100 along the bottom of the window and Y from 0 to 100 along the left side of the window?). You decide on the scale of X and Y based on the values of the function you want to represent.