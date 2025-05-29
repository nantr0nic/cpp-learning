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

