#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

// Exercise 1
struct Arrow : Shape
{
    Arrow(Point p1, Point p2);
    void draw_specifics(Painter& painter) const override;

    // Points to draw lines to for the arrowhead
    Point arrowhead1;
    Point arrowhead2;
};

// Exercise 2
struct Exercise2
{
    Exercise2();

    // Point 0 is top-left corner.
    Point n(const Rectangle& rect)
    {
        return Point((rect.point(0).x + rect.width() / 2), rect.point(0).y);
    }
    Point s(const Rectangle& rect)
    {
        return Point((rect.point(0).x + rect.width() / 2), (rect.point(0).y + rect.height()));
    }
    Point e(const Rectangle& rect)
    {
        return Point((rect.point(0).x + rect.width()), (rect.point(0).y + rect.height() / 2));
    }
    Point w(const Rectangle& rect)
    {
        return Point((rect.point(0).x), (rect.point(0).y + rect.height() / 2));
    }
    Point center(const Rectangle& rect)
    {
        return Point((rect.point(0).x + rect.width() / 2), (rect.point(0).y + rect.height() / 2));
    }
    Point ne(const Rectangle& rect)
    {
        return Point((rect.point(0).x + rect.width()), (rect.point(0).y));
    }
    Point se(const Rectangle& rect)
    {
        return Point((rect.point(0).x + rect.width()), (rect.point(0).y + rect.height()));
    }
    Point sw(const Rectangle& rect)
    {
        return Point((rect.point(0).x), (rect.point(0).y + rect.height()));
    }
    Point nw(const Rectangle& rect)
    {
        return Point((rect.point(0).x), (rect.point(0).y));
    }
};

// Exercise 3
// Same as exercise 2 but for Circles
struct Exercise3Circle
{
    Exercise3Circle();

    // Point 0 is top-left corner.
    Point n(const Circle& cir)
    {
        return Point((cir.center().x), (cir.center().y - cir.radius()));
    }
    Point s(const Circle& cir)
    {
        return Point((cir.center().x), (cir.center().y + cir.radius()));
    }
    Point e(const Circle& cir)
    {
        return Point((cir.center().x + cir.radius()), (cir.center().y));
    }
    Point w(const Circle& cir)
    {
        return Point((cir.center().x - cir.radius()), (cir.center().y));
    }
    Point center(const Circle& cir)
    {
        return Point((cir.center().x), (cir.center().y));
    }
    Point ne(const Circle& cir)
    {
        return Point((cir.center().x + (cir.radius() / 1.4)), (cir.center().y - (cir.radius() / 1.4)));
    }
    Point se(const Circle& cir)
    {
        return Point((cir.center().x + (cir.radius() / 1.4)), (cir.center().y + (cir.radius() / 1.4)));
    }
    Point sw(const Circle& cir)
    {
        return Point((cir.center().x - (cir.radius() / 1.4)), (cir.center().y + (cir.radius() / 1.4)));
    }
    Point nw(const Circle& cir)
    {
        return Point((cir.center().x - (cir.radius() / 1.4)), (cir.center().y - (cir.radius() / 1.4)));
    }
};

// Exercise 4

class Box : public Shape
{
public:
    // Constructors / Draw
    Box(Point xy, int ww, int hh, const std::string label);
    Box(Point x, Point y, const std::string label);
    void draw_specifics(Painter& painter) const override;

    // Getters
    int height() const { return h; }
    int width() const { return w; }
    std::string label() const { return l; }

    // Setters
    void set_font_sz(int sz) { fnt_sz = sz; }

    // Font stuff for Painter
    Font font() const { return fnt; }
    int font_size() const { return fnt_sz; }

private:
    int w {};
    int h {};
    std::string l;

    Font fnt = Font::courier;
    int fnt_sz = 14;
};

// Exercise 6
struct Regular_hexagon : Closed_polyline
{
    Regular_hexagon(Point center, int radius);
    void draw_specifics(Painter& painter) const override;
};

// Exercise 12
struct rTriangle : Closed_polyline
{
    rTriangle(Point origin, int size, int dir);

    double adjusted_side {};
    int cardinal_side {};
};

using namespace Graph_lib;
int main(int /*argc*/, char * /*argv*/[])
{
    /*
     * Below are the 5 drills. The exercises from the end of the chapter begin
     * on line 80 and continue beneath.
     */

    // Application app;
    // Simple_window win {Point{ 150, 150 }, 800, 1000, "Chapter 11 Drills"};

    // // Drill #2
    // int x_max = 800;
    // int y_max = 800;
    // int grid_x = 100;
    // int grid_y = 100;
    // Lines grid;
    // for (int i {0}; i <= x_max; i += grid_x)
    // {
    //     grid.add(Point{ i, 0 }, Point{ i, 800 });
    // }
    // for (int i {0}; i <= y_max; i += grid_y)
    // {
    //     grid.add(Point{ 0, i }, Point{ 800, i });
    // }
    // win.attach(grid);
    // win.wait_for_button();

    // // Drill 3
    // Vector_ref<Rectangle> red_squares {};
    // for (int i {0}; i < 8; ++i)
    // {
    //     int top_left = (i * 100);
    //     int bottom_right = (top_left + 100);
    //     red_squares.push_back(make_unique<Rectangle>(Point{ top_left, top_left }, Point{ bottom_right, bottom_right}));
    // }
    // for (int i {0}; i < red_squares.size(); ++i)
    // {
    //     red_squares[i].set_fill_color(Color::red);
    // }
    // for (const auto& square : red_squares)
    // {
    //     win.attach(*square);
    // }

    // win.wait_for_button();

    // // Drill 4
    // std::string image_file = "/home/nantr0nic/code/cpp-learning/bookwork/ppp3/chapter_11/drills_and_exercises/ProgrammingPrinciplesAndPracticeUsingQt/cpp.jpg";
    // Image cpp1 {Point{ 600, 0 }, image_file};
    // Image cpp2 {Point{ 0, 600 }, image_file};
    // Image cpp3 {Point{ 200, 0 }, image_file};
    // cpp1.scale(200, 200);
    // cpp2.scale(200, 200);
    // cpp3.scale(200, 200);
    // win.attach(cpp1);
    // win.attach(cpp2);
    // win.attach(cpp3);
    // win.wait_for_button();

    // // Drill 5
    // std::string image_file2 = "/home/nantr0nic/code/cpp-learning/bookwork/ppp3/chapter_11/drills_and_exercises/ProgrammingPrinciplesAndPracticeUsingQt/qtlogo.jpg";
    // Image qtlogo {Point{ 0, 0 }, image_file2};
    // win.attach(qtlogo);
    // win.put_on_top(qtlogo);
    // win.wait_for_button();
    // int move_x = grid_x;
    // int move_y = 0;
    // for (int i {0}; i < 7; ++i)
    // {
    //     qtlogo.move(move_x, move_y);
    //     win.wait_for_button();
    // }
    // win.wait_for_button();


    //////// ---------------- Exercises ------------------ ////////

    Application app;
    Simple_window win {Point{ 150, 150 }, 1024, 768, "Chapter 11 Exercises"};


    // // Exercise 1

    // Arrow left {{ 250, 150 }, { 50, 150 }};
    // Arrow right {{ 50, 100 }, { 250, 100 }};
    // Arrow up {{ 100, 200 }, { 100, 50 }};
    // Arrow down {{ 200, 50 }, { 200, 200 }};
    // win.attach(left);
    // win.attach(right);
    // win.attach(up);
    // win.attach(down);


    // // Exercise 2

    // Exercise2 ex2;
    // Rectangle rect1 {{ 100, 100}, 150, 150};
    // win.attach(rect1);

    // Marks compass1 = {
    //     "NESWCPQRS", {ex2.n(rect1), ex2.e(rect1), ex2.s(rect1), ex2.w(rect1),
    //                   ex2.center(rect1), ex2.nw(rect1), ex2.ne(rect1),
    //                   ex2.se(rect1), ex2.sw(rect1)}
    // };
    // compass1.set_color(Color::red);
    // win.attach(compass1);


    // // Exercise 3

    // Exercise3Circle ex3;
    // Circle cir1 {{ 350, 350 }, 100};
    // win.attach(cir1);

    // Marks compass2 = {
    //     "NESWCPQRS", {ex3.n(cir1), ex3.e(cir1), ex3.s(cir1), ex3.w(cir1), ex3.center(cir1),
    //                   ex3.nw(cir1), ex3.ne(cir1), ex3.se(cir1), ex3.sw(cir1) }
    // };
    // compass2.set_color(Color::green);
    // win.attach(compass2);

    // Circle cir2 {{ 350, 150 }, 50};
    // win.attach(cir2);

    // Marks compass3 = {
    //     "NESWCPQRS", {ex3.n(cir2), ex3.e(cir2), ex3.s(cir2), ex3.w(cir2), ex3.center(cir2),
    //      ex3.nw(cir2), ex3.ne(cir2), ex3.se(cir2), ex3.sw(cir2) }
    // };
    // compass3.set_color(Color::cyan);
    // win.attach(compass3);


    // // Exercise 4

    // Box window {{ 45, 15 }, 150, 50, "Window"};
    // Box simple_w {{ 45, 125 }, 150, 50, "Simple_window"};
    // simple_w.set_font_sz(10);
    // Arrow first {{ 120, 125 }, { 120, 65 }};
    // Box line_s {{ 355, 15 }, 150, 50, "Line_style"};
    // line_s.set_font_sz(11);
    // Box color {{ 665, 15 }, 150, 50, "Color"};
    // Box shape {{ 355, 125 }, 150, 50, "Shape"};
    // Box point {{ 665, 125 }, 150, 50, "Point"};

    // Box line {{ 5, 235 }, 100, 50, "Line"};
    // Box lines {{ 125, 235 }, 100, 50, "Lines"};
    // Box polygon {{ 245, 235 }, 100, 50, "Polygon"};
    // polygon.set_font_sz(12);
    // Box axis {{ 365, 235 }, 100, 50, "Axis"};
    // Arrow second {{ 415, 235 }, { 415, 175 }};
    // Box rectangle {{ 485, 235 }, 100, 50, "Rectangle"};
    // rectangle.set_font_sz(10);
    // Box text {{ 605, 235 }, 100, 50, "Text"};
    // Box image {{ 725, 235 }, 100, 50, "Image"};
    // // I'm being lazy and the arrowheads on Arrow only work on vertical ad horizontal lines
    // // So I'm going to use regular lines for the angled lines
    // // Also, I'd use the exercise 2 s() function but I don't know how to
    // // Write a conversion from Box to Rectangle.
    // // Connect to { 415, 175 }
    // Lines etc;
    // etc.add({ 55, 235 }, { 415, 175 });     // line
    // etc.add({ 175, 235 }, { 415, 175 });    // lines
    // etc.add({ 295, 235 }, { 415, 175 });    // polygon
    // etc.add({ 535, 235}, { 415, 175 });     // rectangle
    // etc.add({ 655, 235 }, { 415, 175 });    // text
    // etc.add({ 775, 235 }, { 415, 175 });    // image
    // win.attach(window);
    // win.attach(simple_w);
    // win.attach(first);
    // win.attach(line_s);
    // win.attach(color);
    // win.attach(shape);
    // win.attach(point);
    // win.attach(line);
    // win.attach(lines);
    // win.attach(polygon);
    // win.attach(axis);
    // win.attach(second);
    // win.attach(rectangle);
    // win.attach(text);
    // win.attach(image);
    // win.attach(etc);


    // // Exercise 5

    // // Make the color boxes first
    // Vector_ref<Rectangle> color_boxes;
    // for (int i {}; i < 24; ++i)
    // {
    //     color_boxes.push_back(make_unique<Rectangle>(Point{(10), (i * 32)}, 64, 32));
    //     color_boxes[color_boxes.size() - 1].set_fill_color(Color{(i * 3), (i * 11), (i * 4)});
    //     win.attach(color_boxes[color_boxes.size() - 1]);
    // }

    // // Draw the arrows from the color boxes
    // Vector_ref<Arrow> color_arrows;
    // for (const auto& box : color_boxes)
    // {
    //     // Arrowhead start
    //     Point arrow_start { (box->point(0).x + box->width()), (box->point(0).y + (box->height()/2)) };
    //     Point arrow_end   { (arrow_start.x + 50), (arrow_start.y) };
    //     color_arrows.push_back(make_unique<Arrow>(arrow_start, arrow_end));
    // }
    // for (const auto& arrow : color_arrows)
    // {
    //     win.attach(*arrow);
    // }

    // // Draw the boxes that will have the RGB values
    // Vector_ref<Box> box_color_values;
    // for (int i {}; i < 24; ++i)
    // {
    //     std::string red {to_string(color_boxes[i].fill_color().red_component())};
    //     std::string green {to_string(color_boxes[i].fill_color().green_component())};
    //     std::string blue {to_string(color_boxes[i].fill_color().blue_component())};
    //     std::string rgb = red + '/' + green + '/' + blue;
    //     box_color_values.push_back(make_unique<Box>(Point { 124, (i * 32) }, 200, 32, rgb));
    //     win.attach(box_color_values[i]);
    // }


    // // Exercise 6 and 7
    // Vector_ref<Regular_hexagon> hex_tiles;
    // for (int i {}; i < 8; ++i)
    // {
    //     for (int j {}; j < 8; ++j)
    //     {
    //         int radius = 50;
    //         // Not gonna get into the trig to figure out how to tile and
    //         // stagger them :(
    //         hex_tiles.push_back(make_unique<Regular_hexagon>(Point{ (radius*i)*2, (radius*j)*2 }, radius));
    //         win.attach(hex_tiles[hex_tiles.size() - 1]);
    //     }
    // }


    // // Exercise 10
    // Circle cir {{ 150, 150 }, 50};
    // cir.set_color(Color::white);
    // Exercise3Circle comp;
    // Mark e10 {{ comp.n(cir).x, comp.n(cir).y }, 'X'};
    // e10.set_color(Color::red);
    // win.attach(cir);
    // win.attach(e10);
    // win.wait_for_button();
    // // Rather than calculate the travel along a circle, I added
    // // "shiftMark" to Shape to move to a new coordinate rather than
    // // increment x and y by ints
    // e10.shiftMark(comp.ne(cir));
    // win.wait_for_button();
    // e10.shiftMark(comp.e(cir));
    // win.wait_for_button();
    // e10.shiftMark(comp.se(cir));
    // win.wait_for_button();
    // e10.shiftMark(comp.s(cir));
    // win.wait_for_button();
    // e10.shiftMark(comp.sw(cir));
    // win.wait_for_button();
    // e10.shiftMark(comp.w(cir));
    // win.wait_for_button();
    // e10.shiftMark(comp.nw(cir));


    // // Exercise 11
    // Vector_ref<Rectangle> vr;

    // const int max = 32;     // number of columns
    // const int side = 32;    // size of color rectangle
    // const int left = 10;    // left edge
    // const int top = 100;    // top edge
    // int color_index = 0;

    // for (int i = 0; i < max; ++i)       // all columns
    // {
    //     for (int j = 0; j < 8; ++j)     // 8 rows in each column
    //     {
    //         vr.push_back(make_unique<Rectangle>(Point{ i*side+left, j*side+top }, side, side));
    //         vr[vr.size()-1].set_fill_color(color_index);
    //         vr[vr.size()-1].set_style(Line_style::none);    // this removes the borders
    //         ++color_index;
    //         win.attach(vr[vr.size()-1]);
    //     }
    // }


    // // Exercise 12

    // // Vector_ref<rTriangle> triangles;
    // // for (int i {1}; i <= 8; ++i)
    // // {
    // //     triangles.push_back(make_unique<rTriangle>(Point{ 100 * i, 100 * i}, 50, i));
    // //     win.attach(triangles[triangles.size() - 1]);
    // // }

    // rTriangle one {{ 400, 200 }, 100, 1};
    // one.set_fill_color(Color::white);
    // win.attach(one);
    // rTriangle two {{one.point(2).x, one.point(2).y}, 100, 5};
    // two.set_fill_color(Color::red);
    // win.attach(two);
    // rTriangle three {{two.point(1).x, two.point(1).y}, 100, 6};
    // three.set_fill_color(Color::green);
    // win.attach(three);
    // rTriangle four {{three.point(2).x, three.point(2).y}, 100, 7};
    // four.set_fill_color(Color::blue);
    // win.attach(four);
    // // rTriangle five {{four.point(2).x, four.point(2).y}, 100, 5};
    // // five.set_fill_color(Color::yellow);
    // // win.attach(five);
    // rTriangle five {{one.point(1).x, one.point(1).y}, 100, 5};
    // five.set_fill_color(Color::yellow);
    // win.attach(five);
    // // God damn it I'm giving up. Got halfway there.
    // // Drawing an octogon out of right triangles is harder
    // // than I thought it would be


    // Exercise 13




    win.wait_for_button();
}




// Exercise 1
Arrow::Arrow(Point p1, Point p2)
{
    // Add main line
    add(p1);
    add(p2);
    // Figure out which direction to make arrow head point
    // Arrow head always starts on p2
    // Horizontal lines (left or right)
    if (p1.y == p2.y)
    {
        if (p1.x > p2.x)
        {
            // pointing left
            arrowhead1 = { (p2.x + 10), (p2.y - 10) };
            arrowhead2 = { (p2.x + 10), (p2.y + 10) };
        }
        else if (p1.x < p2.x)
        {
            // pointing right
            arrowhead1 = { (p2.x - 10), (p2.y - 10) };
            arrowhead2 = { (p2.x - 10), (p2.y + 10) };
        }
    }
    // Vertical lines (up or down)
    if (p1.x == p2.x)
    {
        if (p1.y > p2.y)
        {
            // pointing up
            arrowhead1 = { (p2.x - 10), (p2.y + 10) };
            arrowhead2 = { (p2.x + 10), (p2.y + 10) };
        }
        else if (p1.y < p2.y)
        {
            // pointing down
            arrowhead1 = { (p2.x - 10), (p2.y - 10) };
            arrowhead2 = { (p2.x + 10), (p2.y - 10) };
        }
    }
}
void Arrow::draw_specifics(Painter &painter) const
{
    painter.draw_line(point(0), point(1));
    painter.draw_line(point(1), arrowhead1);
    painter.draw_line(point(1), arrowhead2);
}

// Exercise 2
Exercise2::Exercise2()
    { }

// Exercise 3
Exercise3Circle::Exercise3Circle()
    { }

// Exercise 4
Box::Box(Point xy, int ww, int hh, const std::string label)
    : w{ ww }, h{ hh }, l{ label }
{
    // Draw the rectangle
    if (h<=0 || w<=0) error("Bad rectangle: non-positive side");
    add(xy);
}
Box::Box(Point x, Point y, const std::string label)
    : w{ y.x - x.x }, h{ y.y - x.y }, l{ label }
{
    // Draw the rectangle
    if (h<=0 || w<=0) error("Bad rectangle: non-positive side");
    add(x);
}

void Box::draw_specifics(Painter& painter) const
{
    // Get label position
    Point sw { (point(0).x + (w / 4)), (point(0).y + (h / 3)) };
    painter.draw_rectangle(point(0), w, h);
    painter.set_font(font());
    painter.set_font_size(font_size());
    painter.draw_text(sw, l);

}


// Exercise 6
Regular_hexagon::Regular_hexagon(Point center, int radius)
{
    // I guess the best way to draw a hexagon is using trig so I had to use
    // AI to help me with the correct calculation :(
    const double pi = 3.14159265359;

    for (int i = 0; i < 6; ++i)
    {
        double angle = i * pi / 3.0;  // 60 degrees in radians
        int x = center.x + static_cast<int>(radius * cos(angle));
        int y = center.y + static_cast<int>(radius * sin(angle));
        Closed_polyline::add(Point{x, y});
    }

    // // This was my erroneous attempt:
    // Point tl {(center.x - radius), (center.y - radius)};
    // Point tr {(tl.x + radius), (tl.y)};
    // Point r {(tr.x + radius), (tr.y + radius)};
    // Point lr {(r.x - radius), (r.y + radius)};
    // Point ll {(lr.x - radius), (lr.y)};
    // Point l {(ll.x - radius), (ll.y - radius)};
    // Closed_polyline::add(tl);
    // Closed_polyline::add(tr);
    // Closed_polyline::add(r);
    // Closed_polyline::add(lr);
    // Closed_polyline::add(ll);
    // Closed_polyline::add(l);
}

void Regular_hexagon::draw_specifics(Painter& painter) const
{
    Closed_polyline::draw_specifics(painter);
}

rTriangle::rTriangle(Point origin, int side, int dir)
{
    // This is NOT a good way to define right triangle
    // but it suffices to complete this exercise
    // and it represents the fewest constructor arguments I could devise
    // Also, 'direction' will be the direction the apex points
    // 1 = N, 2 = NE, 3 = E, 4 = SE, etc.
    //// This is what I originally wrote but because of geometry details
    /// the N, E, S, W triangles end up with longer hypotenuses
    /// which works fine BUT to make an octagonal shape I need them
    /// to be visually identical...
    /// so to save time I had AI write the code beneath this one
    // if (dir == 1)
    // {
    //     // Apex pointing north
    //     // Bottom point (where the right angle is)
    //     add(origin);
    //     Point second {(origin.x - side), (origin.y - side)};
    //     add(second);
    //     Point third {(origin.x + side), (origin.y - side)};
    //     add(third);
    // }
    // else if (dir == 2)
    // {
    //     // Apex pointing north-east
    //     add(origin);
    //     Point second {(origin.x), (origin.y - side)};
    //     add(second);
    //     Point third {(origin.x + side), (origin.y)};
    //     add(third);
    // }
    // else if (dir == 3)
    // {
    //     // Apex pointing east
    //     add(origin);
    //     Point second {(origin.x + side), (origin.y - side)};
    //     add(second);
    //     Point third {(origin.x + side), (origin.y + side)};
    //     add(third);
    // }
    // else if (dir == 4)
    // {
    //     // Apex pointing south-east
    //     add(origin);
    //     Point second {(origin.x + side), (origin.y)};
    //     add(second);
    //     Point third {(origin.x), (origin.y + side)};
    //     add(third);
    // }
    // else if (dir == 5)
    // {
    //     // Apex pointing south
    //     add(origin);
    //     Point second {(origin.x + side), (origin.y + side)};
    //     add(second);
    //     Point third {(origin.x - side), (origin.y + side)};
    //     add(third);
    // }
    // else if (dir == 6)
    // {
    //     // Apex pointing south-west
    //     add(origin);
    //     Point second {(origin.x - side), (origin.y)};
    //     add(second);
    //     Point third {(origin.x), (origin.y + side)};
    //     add(third);
    // }
    // else if (dir == 7)
    // {
    //     // Apex pointing west
    //     add(origin);
    //     Point second {(origin.x - side), (origin.y - side)};
    //     add(second);
    //     Point third {(origin.x - side), (origin.y + side)};
    //     add(third);
    // }
    // else if (dir == 8)
    // {
    //     // Apex pointing north-west
    //     add(origin);
    //     Point second {(origin.x - side), (origin.y)};
    //     add(second);
    //     Point third {(origin.x), (origin.y - side)};
    //     add(third);
    // }
    // else {
    //     std::cout << "Poorly constructed";
    // }
    // For cardinal directions, adjust leg length to match diagonal triangle areas
    // Diagonal triangles have area = (side * side) / 2
    // Cardinal triangles (isosceles right) have area = (adjusted_side^2) / 2
    // To make areas equal: adjusted_side = side (no adjustment needed)
    // But for visual consistency, we want same "extent" so we use side/sqrt(2)
    adjusted_side = side / std::sqrt(2.0);
    cardinal_side = static_cast<int>(adjusted_side);

    if (dir == 1)
    {
        // Apex pointing north - isosceles right triangle
        add(origin);
        Point second{(origin.x - cardinal_side), (origin.y - cardinal_side)};
        add(second);
        Point third{(origin.x + cardinal_side), (origin.y - cardinal_side)};
        add(third);
    }
    else if (dir == 2)
    {
        // Apex pointing north-east - right triangle
        add(origin);
        Point second{(origin.x), (origin.y - side)};
        add(second);
        Point third{(origin.x + side), (origin.y)};
        add(third);
    }
    else if (dir == 3)
    {
        // Apex pointing east - isosceles right triangle
        add(origin);
        Point second{(origin.x + cardinal_side), (origin.y - cardinal_side)};
        add(second);
        Point third{(origin.x + cardinal_side), (origin.y + cardinal_side)};
        add(third);
    }
    else if (dir == 4)
    {
        // Apex pointing south-east - right triangle
        add(origin);
        Point second{(origin.x + side), (origin.y)};
        add(second);
        Point third{(origin.x), (origin.y + side)};
        add(third);
    }
    else if (dir == 5)
    {
        // Apex pointing south - isosceles right triangle
        add(origin);
        Point second{(origin.x + cardinal_side), (origin.y + cardinal_side)};
        add(second);
        Point third{(origin.x - cardinal_side), (origin.y + cardinal_side)};
        add(third);
    }
    else if (dir == 6)
    {
        // Apex pointing south-west - right triangle
        add(origin);
        Point second{(origin.x - side), (origin.y)};
        add(second);
        Point third{(origin.x), (origin.y + side)};
        add(third);
    }
    else if (dir == 7)
    {
        // Apex pointing west - isosceles right triangle
        add(origin);
        Point second{(origin.x - cardinal_side), (origin.y - cardinal_side)};
        add(second);
        Point third{(origin.x - cardinal_side), (origin.y + cardinal_side)};
        add(third);
    }
    else if (dir == 8)
    {
        // Apex pointing north-west - right triangle
        add(origin);
        Point second{(origin.x - side), (origin.y)};
        add(second);
        Point third{(origin.x), (origin.y - side)};
        add(third);
    }
    else
    {
        std::cout << "Poorly constructed" << std::endl;
    }
}
