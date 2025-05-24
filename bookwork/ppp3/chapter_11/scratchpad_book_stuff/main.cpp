#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main()
{
    try
    {
        Application app;    // necessary for QApplication

        Simple_window win {Point { x_max() / 2, y_max() / 2 }, 1024, 768, " -= Chapter 11 Stuff =- "};

        // // Line Objects
        // constexpr Point x { 100, 100 };
        // Line horizontal {x, Point{ 200, 100 }};
        // Line vertical {Point{ 150, 50 }, Point{ 150, 150 }};
        // win.attach(horizontal);
        // win.attach(vertical);

        //// ----------------- ////

        // // Lines objects
        // Lines y;
        // y.add(Point{ 100, 100 }, Point{ 200, 100 });
        // y.add(Point{ 150, 50 }, Point{ 150, 150});
        // win.attach(y);

        //// ----------------- ////

        // // An example of Lines to make a grid
        // int x_size = win.x_max();
        // int y_size = win.y_max();
        // int x_grid = 80;
        // int y_grid = 40;

        // Lines grid;
        // for (int x = x_grid; x < x_size; x += x_grid)
        //     grid.add(Point{ x, 0 }, Point{ x, y_size }); // each iteration adds a vertical line (along x-axis)
        // for (int y = y_grid; y < y_size; y += y_grid)
        //     grid.add(Point{ 0, y }, Point{ x_size, y }); // each iteration adds a horizontal line (along y-axis)
        // win.attach(grid);
        // // An additional initialization format
        // Lines x = {
        //     {{ 100, 100 }, { 200, 100 }},
        //     {{ 150, 50 }, { 150, 150 }}
        // };
        // win.attach(x);

        //// ----------------- ////

        // // The "Try This" exercise (but I made 2 Lines objects for the x and y)
        // int x_size = win.x_max();
        // int y_size = win.y_max();
        // int x_grid = 60;
        // int y_grid = 30;

        // Lines grid2_x;
        // for (int x = x_grid; x < x_size; x += x_grid)
        //     grid2_x.add(Point{ x, 0 }, Point{ x, y_size });

        // grid2_x.set_color(Color::cyan);
        // grid2_x.set_style(Line_style{Line_style::dash,2});

        // Lines grid2_y;
        // for (int y = y_grid; y < y_size; y += y_grid)
        //     grid2_y.add(Point{ 0, y }, Point{ x_size, y });

        // grid2_y.set_color(Color::magenta);
        // grid2_y.set_style(Line_style{Line_style::dot,2});

        // win.attach(grid2_x);
        // win.attach(grid2_y);

        //// ----------------- ////

        // Polylines

        // Open_polyline
        Open_polyline opl = {
            { 100, 100 }, { 150, 200 }, { 250, 250 }, { 300, 200 }
        };
        win.attach(opl);




        win.wait_for_button();
    }
    catch (...)
    {
        std::cout << "Something went wrong.\n";
    }
}

