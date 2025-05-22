/*
 * Cloning the repo and making a new project for each exercise is umbersome so
 * I'm going to minimize the number of project files by reusing as much as
 * makes sense.
*/

#include "PPP/Simple_window.h"

using namespace Graph_lib;
int main(int /*argc*/, char * /*argv*/[])
{
    Application app;
    Simple_window win { { (x_max() / 2), (y_max() / 2) }, 1024, 768, "Exercises" };

    // ------------------ Exercise 1 and 2 ------------- //
    // Rectangle
    // x = 50 - 150
    // y = 30 - 80
    Rectangle rect {Point{ 50, 50 }, 100, 30};
    rect.set_color(Color::blue);
    win.attach(rect);

    // Polygon
    Polygon poly1;
    poly1.add(Point{ 160, 50 });
    poly1.add(Point{ 160, 80 });
    poly1.add(Point{ 260, 80 });
    poly1.add(Point{ 260, 50 });
    poly1.set_color(Color::red);
    win.attach(poly1);

    // Text inside rect
    Text t {Point { 65, 50}, "Howdy!"};
    win.attach(t);

    // ---------------- Exercise 3 ------------------ //
    // Draw initials 150 pixels high with thick lines, different colors

    // This is the "A" in "AK"
    Line a1 {Point{ 300, 150 }, Point{ 400, 0 }};
    Line a2 {Point{ 400, 0 }, Point{ 500, 150 }};
    Line a3 {Point{ 350, 75 }, Point{ 450, 75 }};
    a1.set_color(Color::green);
    a2.set_color(Color::green);
    a3.set_color(Color::green);
    a1.set_style(Line_style(Line_style::solid, 4));
    a2.set_style(Line_style(Line_style::solid, 4));
    a3.set_style(Line_style(Line_style::solid, 4));
    win.attach(a1);
    win.attach(a2);
    win.attach(a3);

    // This is the "K" in "AK"
    Line k1 {Point{ 505, 0 }, Point{ 505, 150 }};
    Line k2 {Point{ 505, 55 }, Point{ 575, 0 }};
    Line k3 {Point{ 505, 55 }, Point{ 575, 150 }};
    k1.set_color(Color::magenta);
    k2.set_color(Color::magenta);
    k3.set_color(Color::magenta);
    k1.set_style(Line_style(Line_style::solid, 4));
    k2.set_style(Line_style(Line_style::solid, 4));
    k3.set_style(Line_style(Line_style::solid, 4));
    win.attach(k1);
    win.attach(k2);
    win.attach(k3);

    // ------------------- Exercise 4 ------------------- //
    // tic-tac-toe board, alternating white/red squares
    // start at 600x
    // 1 = 600,0 - 650,50 / 2 = 650,0 - 700,50 / 3 = 700,0 - 750,50
    // 4 = 600,50 - 650,100 / 5 = 650,50 - 700,100 / 6 = 700,50 - 750,100
    // 7 = 600,100 - 650,150 / 8 = 650,100 - 700,150 / 9 = 700,100 - 750,150
    // Each square will start at first coordinate and be 50x50
    // red squares = 1, 3, 5, 7, 9
    // white squares = 2, 4, 6, 8
    Rectangle ttt1 {Point{ 600, 0 }, 50, 50};
    Rectangle ttt2 {Point{ 650, 0 }, 50, 50};
    Rectangle ttt3 {Point{ 700, 0 }, 50, 50};
    Rectangle ttt4 {Point{ 600, 50 }, 50, 50};
    Rectangle ttt5 {Point{ 650, 50 }, 50, 50};
    Rectangle ttt6 {Point{ 700, 50 }, 50, 50};
    Rectangle ttt7 {Point{ 600, 100 }, 50, 50};
    Rectangle ttt8 {Point{ 650, 100 }, 50, 50};
    Rectangle ttt9 {Point{ 700, 100 }, 50, 50};
    ttt1.set_fill_color(Color::red);
    ttt3.set_fill_color(Color::red);
    ttt5.set_fill_color(Color::red);
    ttt7.set_fill_color(Color::red);
    ttt9.set_fill_color(Color::red);
    ttt2.set_fill_color(Color::white);
    ttt4.set_fill_color(Color::white);
    ttt6.set_fill_color(Color::white);
    ttt8.set_fill_color(Color::white);
    win.attach(ttt1);
    win.attach(ttt2);
    win.attach(ttt3);
    win.attach(ttt4);
    win.attach(ttt5);
    win.attach(ttt6);
    win.attach(ttt7);
    win.attach(ttt8);
    win.attach(ttt9);


    // ---------- Exercise 8 ------------ //
    // Start circles at 100x, 200y - radius 50
    // Top row: blue 100,200  / black 200, 200 / red 300, 200
    // Bottom row: yellow 150, 250 / green 250, 250
    Circle c1 {Point{ 100, 200 }, 48};
    Circle c2 {Point{ 205, 200 }, 48};
    Circle c3 {Point{ 310, 200 }, 48};
    Circle c4 {Point{ 150, 250 }, 48};
    Circle c5 {Point{ 255, 250 }, 48};
    c1.set_color(Color::blue);
    c2.set_color(Color::black);
    c3.set_color(Color::red);
    c4.set_color(Color::yellow);
    c5.set_color(Color::green);
    c1.set_style(Line_style(Line_style::solid, 3));
    c2.set_style(Line_style(Line_style::solid, 3));
    c3.set_style(Line_style(Line_style::solid, 3));
    c4.set_style(Line_style(Line_style::solid, 3));
    c5.set_style(Line_style(Line_style::solid, 3));
    win.attach(c1);
    win.attach(c2);
    win.attach(c3);
    win.attach(c4);
    win.attach(c5);


    win.wait_for_button();
}
