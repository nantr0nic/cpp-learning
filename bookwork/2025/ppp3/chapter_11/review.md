### Review Questions
1. Why don't we "just" use a commercial or open-source graphics library
directly?
2. About how many classes from our graphics interface library do you need
to do simple graphics output?
3. What are the header files needed to use the graphics interface library?
4. What classes define closed shapes?
5. Why don't we just use Line for every shape?
6. What do the arguments to Point indicate?
7. What are the components of Line_style?
8. What are the components of Color?
9. What is RGB?
10. What are the differences between two Lines and a Lines containing two
lines?
11. What properties can you set for every Shape?
12. How many sides does a Closed_polyline defined by five Points have?
13. What do you see if you define a Shape but don't attach it to a Window?
14. How does a Rectangle differ from a Polygon with four Points (corners)?
15. How does a Polygon differ from a Closed_polyline?
16. What's on top: fill or outline?
17. Why didn't we bother defining a Triangle class (after all, we did define
Rectangle)?
18. How do you move a Shape to another place in a Window?
19. How do you label a Shape with a line of text?
20. What properties can you set for a text string in a Text?
21. What is a font and why do we care?
22. What is Vector_ref for and how do we use it?
23. What is the difference between a Circle and an Ellipse?
24. What happens if you try to display an Image given a file name that
doesn't refer to a file containing an image?
25. How do you display part of an Image?
26. How do you scale an Image?
---
### My Answers
1. We don't "just" use a commerical or open-source graphics library directly because such libraries are incredibly complex and too cumbersome for our purposes in this chapter. They also offer way more than we need for the work in this chapter. Lastly, by using the simple graphics library provided, the author/maintainers of the code used for the book can easily migrate from one underlying library (e.g. from FLTK to Qt) without much change or impact to the reader of the book and the already existing code.
2. You need "Application" for Qt to work, "Simple_window" to draw a window, and then at least one visible class such as Rectangle or Text. Therefore, you can produce simple graphics output with a minimum of three classes. I should mention that Rectangle is a derived class of "Shape" that also calls the struct "Point", so one *might* consider the answer 5 classes instead of 3. But from the point of view of the user the number of classes is 3.
3. They are "Graph.h" and "Simple_window.h" -- or "Window.h".
4. If we exclude "Closed_polyline" from the definition of a geometric shape, then the classes that define closed shapes are Shape and Point. If you are asking which classes are classes OF closed shapes, then that would be Polygon, Rectangle, Circle, and Ellipse.
5. We don't use Line for every shape because that is overly complex, especially if we want to respect the definition of "shape" that doesn't allow for lines to intersect in its construction. Also, things like rectangles and circles are so common that it is desirable to provide the user with directly accessible classes to use those shapes.
6. The arguments to Point are x and y coordinates. Point is its own struct where the x and y are stored (publicly) as integers.
7. Line_style has the components of Line_style_type that enumerates dotted, dashed, solid lines and so on -- and it has the component of 'width' that defaults to 1 pixel but can be changed by the user.
8. The components of Color are: the enumeration Color_type which contains a list of basic colors as well as "palette_index" and "rgb"; the enumeration Transparency which has the two values "invisible" and "visible"; functions to return color values as red, green, blue or as an integer (i.e. as_int()); and privately it contains RGB values in several formats (e.g. struct Rgb with each as its own int, or rgb_color where {0, 0, 0} stores rgb values).
9. RGB is "red green blue" where a color is represented as a ratio of red/green/blue and each is defined on a scale of 0-255. 0,0,0 is black and 255,255,255 is white, red is 255,0,0, and so on.
10. Two Line's are independent lines whereas two lines as part of a single instantiation of "Lines" are considered together. For example, if two draw two independent Line objects and want both of them to be red, you'd have to set the Line_style of each independently. Whereas, if they are both contained by "Lines" then you set that "Lines" object to red and the two lines will be red -- as well as any line you add to that Lines object will also consequently be red.
11. You can set the point where it is drawn, the Line_style of its outline, and its fill color (in addition to it being either visible or invisible).
12. It depends if any of the lines intersect, but it would have at least five but up to nine (I think...). 
13. If you define a shape but don't attach it to a Window you will not see the shape.
14. A Polygon differs from Rectangle in how it is initialized, where a Polygon requires four Points and a Rectangle requires either a single Point and a width + height or two Points (the top-left and bottom-right corners). Also, most graphics libraries (Qt included) treat rectangles differently because of how common/useful the shape is and therefore many operations are optimized when they work with rectangles. Also, a Rectangle guaruntees that the corresponding sides are lined up on the same axis whereas a Polygon with 4 points *could* make a diamond. 
15. A Polygon has a function that checks to make sure no lines intersect whereas a Closed_polyline can draw a shape given a set of points where the lines *do* intersect.
16. The outline is on top.
17. You didn't bother defining a triangle class because it is easy and simple to draw one using Polygon and three points.
18. You use ```shape.move(int dx, int dy)``` 
19. You would create a Text object and set the origin point beneath the shape.
20. You can set its Font_type (e.g. helvetica, times) and its size.
21. A Font is a string object drawn onto the window by the underlying graphics library. We care because we often needs to draw text on a window thus it is important to know what kind of object it is and what properties can be set for that text.
22. Vector_ref is a template of std::vector written for this graphics library and we used it in this chapter to add unnamed Shape objects into the same "vector" -- really the same Vector_ref.
23. A Circle only needs on point and a radius whereas as Ellipse is a Point and the major and minor axis defined as lengths in pixels.
24. Instead of the image itself, the "system" will print an error string in its place in the window declaring that the file could not be accessed.
25. You display only a part of an image using ```image.set_mask(Point xy, int ww, int hh)``` and you scale an image using ```image.scale(int ww, int hh)```