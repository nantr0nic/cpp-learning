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

        /// Polylines ///

        // // Open_polyline
        // Open_polyline opl = {
        //     { 100, 100 }, { 150, 200 }, { 250, 250 }, { 300, 200 }
        // };
        // win.attach(opl);

        // // Closed_polyline
        // Closed_polyline cpl = {
        //     { 100, 100 }, { 150, 200 }, { 250, 250 }, { 300, 200 }
        // };
        // win.attach(cpl);

        // // Marked_polyline
        // Marked_polyline mpl = {
        //     "1234", {{ 100, 100 }, { 150, 200 }, { 250, 250 }, { 300, 200 }}
        // };
        // win.attach(mpl);

        // // Marks
        // Marks pp {"x", {{ 100, 100 }, { 150, 200 }, { 250, 250 }, { 300, 200 }}};
        // win.attach(pp);

        //// ----------------- ////

        /// Closed Shapes ///

        // // Polygon
        // Polygon poly {{ 100, 100 }, { 150, 200 }, { 250, 250 }, { 300, 200 }};
        // win.attach(poly);

        // // Rectangle
        // Rectangle rect00 {Point{ 150,100 }, 200, 100};          // small yellow rect
        // Rectangle rect11 {Point{ 50, 50 }, Point{ 250, 150 }};  // blue, top left rect
        // Rectangle rect12 {Point{ 50,150 }, Point{ 250, 250 }};  // just below rect 11
        // Rectangle rect21 {Point{ 250, 50 }, 200, 100};          // just to right of rect 11
        // Rectangle rect22 {Point{ 250, 150 }, 200, 100};         // just below rect21
        // rect00.set_fill_color(Color::yellow);
        // rect11.set_fill_color(Color::blue);
        // rect12.set_fill_color(Color::red);
        // rect21.set_fill_color(Color::green);
        // win.attach(rect00);
        // win.attach(rect11);
        // win.attach(rect12);
        // win.attach(rect21);
        // win.attach(rect22);

        // win.wait_for_button();      // hit 'next' to following things take effect

        // rect11.move(400,0);
        // rect11.set_fill_color(Color::white);

        // win.wait_for_button();

        // win.put_on_top(rect00);

        // win.wait_for_button();

        // rect00.set_fill_color(Color::invisible);
        // rect11.set_fill_color(Color::invisible);
        // rect12.set_fill_color(Color::invisible);
        // rect21.set_fill_color(Color::invisible);
        // rect22.set_fill_color(Color::invisible);


        /// "Managing unnamed objects" // (Interlude...)

        // // Vector_ref introduced

        // Vector_ref<Rectangle> rect;
        // Rectangle x {Point{ 100, 200 }, Point{ 200, 300}};
        // // make_unique is explained in chapters 15 and 18
        // rect.push_back(make_unique<Rectangle>(Point{ 50, 60 }, Point{ 80, 90 }));
        // rect.push_back(x);
        // // vvv is not in the text vvv
        // for (const auto& m : rect)
        //     win.attach(*m);         // must use a pointer for attach() in range-for loop

        // win.wait_for_button();

        // // vvv IS in the text vvv
        // for (int i {0}; i < rect.size(); ++i)
        //     rect[i].move(10,10);

        // win.wait_for_button();

        // Color palette squares
        Vector_ref<Rectangle> vr;

        const int max = 32;     // number of columns
        const int side = 32;    // size of color rectangle
        const int left = 10;    // left edge
        const int top = 100;    // top edge
        int color_index = 0;

        for (int i = 0; i < max; ++i)       // all columns
        {
            for (int j = 0; j < 8; ++j)     // 8 rows in each column
            {
                vr.push_back(make_unique<Rectangle>(Point{ i*side+left, j*side+top }, side, side));
                vr[vr.size()-1].set_fill_color(color_index);
                ++color_index;
                win.attach(vr[vr.size()-1]);
            }
        }

        // // Circle
        // Circle c1 {Point{ 100, 200 }, 50};
        // Circle c2 {Point{ 150, 200 }, 100};
        // Circle c3 {Point{ 200, 200 }, 150};
        // win.attach(c1);
        // win.attach(c2);
        // win.attach(c3);
        // win.wait_for_button();
        // win.detach(c1);
        // win.detach(c2);
        // win.detach(c3);
        // Circle c11 {Point{ 0, 0 }, 100};
        // Circle c21 {Point{ x_max(), y_max() }, 100};
        // Circle c31 {Point{ 200, 200 }, 100};
        // c11.set_color(Color::red);
        // c21.set_color(Color::blue);
        // win.attach(c11);
        // win.attach(c21);
        // win.attach(c31);

        // // Ellipse
        // Ellipse e3 {Point{ 200, 200 }, 100, 150};
        // Ellipse e2 {Point{ 200, 200 }, 100, 50};
        // Ellipse e1 {Point{ 200, 200 }, 50, 50};
        // e1.set_fill_color(Color::black);
        // e2.set_fill_color(Color::white);
        // e3.set_fill_color(Color::yellow);
        // // Layers are in order that they're attached, not declared
        // win.attach(e3);
        // win.attach(e2);
        // win.attach(e1);

        //// ----------------- ////

        /// Text ///

        // // Text (11.8)
        // Closed_polyline cpl = {
        //     { 100, 100 }, { 150, 200 }, { 250, 250 }, { 300, 200 },
        //     { 100, 250 }    // the point that closes the polyline (non-polygon) 'shape'
        // };
        // Text t {Point{ 150, 200 }, "A closed polyline that isn't a polygon"};
        // t.set_color(Color::red);
        // t.set_font(Font::helvetica_bold_italic);
        // win.attach(cpl);
        // win.attach(t);

        // // Marks (11.9)
        // Circle c1 {Point{ 100, 200 }, 50};
        // Circle c2 {Point{ 150, 200 }, 100};
        // Circle c3 {Point{ 200, 200 }, 150};
        // c1.set_color(Color::blue);
        // c2.set_color(Color::red);
        // c3.set_color(Color::green);
        // win.attach(c1);
        // win.attach(c2);
        // win.attach(c3);

        // Mark m1 {Point{ 100, 200 }, 'x'};
        // Mark m2 {Point{ 150, 200 }, 'y'};
        // Mark m3 {Point{ 200, 200 }, 'z'};
        // m1.set_mark_color(Color::blue);
        // m2.set_mark_color(Color::red);
        // m3.set_mark_color(Color::green);
        // win.attach(m1);
        // win.attach(m2);
        // win.attach(m3);

        //// ----------------- ////

        /// Images ///

        // 11.10 -- "Try this"
        Image image {Point{ 100, 100 }, "/home/nantr0nic/Pictures/Screenshots/Screenshot_20241214_215136.png"};

        win.attach(image);
        win.wait_for_button();
        win.detach(image);

        Image image2 {Point{ 0, 0 }, "/home/nantr0nic/Pictures/Screenshots/Screenshot_20241214_150937.png"};
        // image2.set_mask(Point{ 250, 150 }, 800, 600);
        image2.scale(x_max(), y_max());
        win.attach(image2);


        win.wait_for_button();
    }
    catch (...)
    {
        std::cout << "Something went wrong.\n";
    }
}

