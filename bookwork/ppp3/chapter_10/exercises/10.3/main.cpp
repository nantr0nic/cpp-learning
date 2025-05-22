#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <sstream>

double dsin(double d) { return sin(d); }

int main()
{
    using namespace Graph_lib;

    Application app;

    Point tl { 900, 500 };

    Simple_window win {tl, 600, 400, "Canvas"};

    // Exercise code is beneath

    // X axis stuff
    Axis xa {Axis::x, Point{ 20, 300 }, 280, 10, "x axis"}; // make an Axis
        // an Axis is a kind of Shape
        // Axis::x means horizontal
        // starting at (20, 300)
        // 280 pixels long
        // with 10 notches
        // label the axis "x axis"
    win.attach(xa);

    // Y axis stuff
    Axis ya {Axis::y, Point{ 20, 300 }, 280, 10, "y axis"};
    ya.set_color(Color::cyan);
    ya.label.set_color(Color::dark_red);
    win.attach(ya);

    // Graphing a function stuff beneath
    Function sine {dsin, 0, 100, Point{ 20, 150 }, 1000, 50, 50}; // sine curve
        // plot sin() in the range [0:100) with (0,0) at (20,150)
        // using 1000 points; scale x values *50, scale y values *50

    win.attach(sine);
    sine.set_color(Color::blue);

    // Draw a polygon
    Polygon poly;
    poly.add(Point{ 300, 200 });
    poly.add(Point{ 350, 100 });
    poly.add(Point{ 400, 200 });
    poly.set_color(Color::red);
    win.attach(poly);

    // Draw a rectangle
    Rectangle r {Point{ 200, 200 }, 100, 50};
    win.attach(r);

    // A polyline with 4 points is NOT a rectangle...
    Closed_polyline poly_rect;
    poly_rect.add(Point{ 100, 50 });
    poly_rect.add(Point{ 200, 50 });
    poly_rect.add(Point{ 200, 100 });
    poly_rect.add(Point{ 100, 100 });
    poly_rect.add(Point{ 50, 75 });
    win.attach(poly_rect);

    // Changing fills and line styles
    r.set_fill_color(Color::yellow);
    poly.set_style(Line_style(Line_style::dash, 4));
    poly_rect.set_style(Line_style(Line_style::dash, 2));
    poly_rect.set_fill_color(Color::green);

    // Adding text
    Text t {Point{ 150, 150 }, "Hello, graphical world!"};
    t.set_font(Font::times_bold);
    t.set_font_size(20);
    win.attach(t);

    // Add an image
    Image copter {Point{ 100, 50 }, "/home/nantr0nic/code/cpp-learning/bookwork/ppp3/chapter_10/exercises/10.3/mars_copter.jpg"};
    copter.move(100, 250);
    win.attach(copter);

    // Etc.
    Circle c {Point{ 100, 200 }, 50};

    Ellipse e {Point{ 100, 200 }, 75, 25};
    e.set_color(Color::dark_red);

    Mark m {Point{ 100, 200}, 'x'};
    m.set_color(Color::red);

    std::ostringstream oss;
    oss << "screen size: " << x_max() << "*" << y_max() << "; window size: " << win.x_max() << "*" << win.y_max();
    Text sizes {Point{ 100, 20 }, oss.str()};

    win.attach(c);
    win.attach(e);
    win.attach(m);
    win.attach(sizes);

    win.set_label("Malarky lulz");
    win.wait_for_button();
}
