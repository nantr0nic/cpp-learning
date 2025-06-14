#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/*
 * Exercise 1
 * I originally used Function to draw actually parabolic lips for
 * each face but had too much difficulty scaling the x and y axes
 * to the radius of the overall head so decided to go with the easier
 * but dumb looking 2-line mouths...
*/

class Smiley : public Circle
{
public:
    Smiley(Point p, int rr);
    void draw_specifics(Painter& painter) const override;

private:
    // These are used to place the eyes and mouth
    Point left_eye;
    Point right_eye;
    Point left_cheek;
    Point right_cheek;
    Point chin;
};

class Frowny : public Circle
{
public:
    Frowny(Point p, int rr);
    void draw_specifics(Painter& painter) const override;

private:
    // These are used to place the eyes and mouth
    Point left_eye;
    Point right_eye;
    Point left_cheek;
    Point right_cheek;
    Point chin;
};

class Smiley_hat : public Smiley
{
public:
    using Smiley::Smiley;
    void draw_specifics(Painter& painter) const override;
};

class Frowny_hat : public Frowny
{
public:
    using Frowny::Frowny;
    void draw_specifics(Painter& painter) const override;
};

// Exercise 4
class Immobile_circle : public Circle
{
public:
    using Circle::Circle;

    void move(int dx, int dy) override
    {
        // I'd just print a simple error message but the compiler on Qt keeps giving
        // unused parameter warnings which are annoying so...
        std::cout << "Sorry, I can't move this circle " << dx << " on x nor " << dy << " on y!\n";
    }
};

// Exercise 5
class Striped_rectangle : public Rectangle
{
public:
    using Rectangle::Rectangle;
    void draw_specifics(Painter& painter) const override;
    void set_stripe_distance(int pixels) { stripe_distance = pixels; }

private:
    int stripe_distance { 4 };
};

// Exercise 6
class Striped_circle : public Circle
{
public:
    using Circle::Circle;

    void draw_specifics(Painter& painter) const override;
    void set_stripe_distance(int pixels) { stripe_distance = pixels; }

private:
    int stripe_distance { 4 };
};


// Exercise 8
class Octagon : public Polygon
{
public:
    Octagon(Point center, int radius);

    Point center() const { return m_center; }
    int radius() const { return r; }

    void draw_specifics(Painter& painter) const;

private:
    Point m_center;
    int r;

};

using namespace Graph_lib;
int main(int /*argc*/, char * /*argv*/[])
{
    Application app;
    Simple_window win {{ 300, 150 }, 1280, 720, "Chapter 12 Exercises"};

    // // Exercise 1
    // Smiley_hat smiley_hat {{ 200, 200 }, 100};
    // smiley_hat.set_color(Color::red);
    // win.attach(smiley_hat);

    // Frowny_hat frowny_hat {{ 400, 400 }, 150};
    // frowny_hat.set_color(Color::cyan);
    // win.attach(frowny_hat);

    // Exercise 2
    // Frowny_hat frowny_hat2 = frowny_hat;
    // The error is.. "main.cpp:72: error: Call to implicitly-deleted copy constructor of 'Frowny_hat'

    // Exercise 3
    // The compiler says it cannot instantiate an abstract class

    // // Exercise 4
    // Immobile_circle dont_move_me {{ 100, 100 }, 100};
    // win.attach(dont_move_me);
    // win.wait_for_button();
    // dont_move_me.move(50, 50);

    // // Exercise 5
    // Striped_rectangle sr {{ 100, 100 }, 200, 500};
    // sr.set_stripe_distance(2);
    // win.attach(sr);

    // // Exercise 6
    // Striped_circle sc {{ 100, 100 }, 100};
    // win.attach(sc);

    // Exercise 8
    Octagon oct {{ 150, 150 }, 100};
    oct.set_fill_color(Color::cyan);
    oct.set_style(Line_style(Line_style::dashdot, 6));
    win.attach(oct);


    win.wait_for_button();
}

// Exercise 1
// Smiley
Smiley::Smiley(Point p, int rr)
    : Circle {p, rr}
{
    // Define points for eyes and smile
    right_eye.x = center().x + (radius() / 2);
    right_eye.y = center().y - (radius() / 2);
    left_eye.x = center().x - (radius() / 2);
    left_eye.y = center().y - (radius() / 2);
    left_cheek.x = center().x - (radius() / 1.5);
    left_cheek.y = center().y;
    right_cheek.x = center().x + (radius() / 1.5);
    right_cheek.y = center().y;
    chin.x = center().x;
    chin.y = center().y + (radius() / 1.2);
};

void Smiley::draw_specifics(Painter& painter) const
{
    // Draw main circle/head
    int r = radius();
    painter.draw_ellipse(center(), r, r);

    // Draw the eyes
    painter.draw_ellipse(left_eye, r/8, r/8);
    painter.draw_ellipse(right_eye, r/8, r/8);

    // Draw the mouth
    painter.draw_line(left_cheek, chin);
    painter.draw_line(chin, right_cheek);
};

Frowny::Frowny(Point p, int rr)
    : Circle {p, rr}
{
    // Define points for eyes and frown
    right_eye.x = center().x + (radius() / 2);
    right_eye.y = center().y - (radius() / 2);
    left_eye.x = center().x - (radius() / 2);
    left_eye.y = center().y - (radius() / 2);
    // These aren't the "cheeks" but inverse of them...
    left_cheek.x = center().x - (radius() / 1.8);
    left_cheek.y = center().y + (radius() / 1.8);
    right_cheek.x = center().x + (radius() / 1.8);
    right_cheek.y = center().y + (radius() / 1.8);
    // This isn't the "chin" but the inverse under the nose
    chin.x = center().x;
    chin.y = center().y + (radius() / 8);
}

void Frowny::draw_specifics(Painter& painter) const
{
    // Draw main circle/head
    int r = radius();
    painter.draw_ellipse(center(), r, r);

    // Draw the eyes
    painter.draw_ellipse(left_eye, r/8, r/8);
    painter.draw_ellipse(right_eye, r/8, r/8);

    // Draw the mouth
    painter.draw_line(left_cheek, chin);
    painter.draw_line(chin, right_cheek);
};

void Smiley_hat::draw_specifics(Painter& painter) const
{
    // Draw the smiley first
    Smiley::draw_specifics(painter);

    // Now lets add the hat
    int r { radius() };
    int d { r*2 };
    Point c { center() };

    // Brim
    Point left_side { this->point(0) };
    Point right_side { (left_side.x + d), left_side.y };
    painter.draw_line(left_side, right_side);

    // The top part
    // I was going to use a rectangle but didn't want overlapping lines
    // so I'm just going to draw 3 lines instead
    // Using the left and right eyes for X coordinates
    // then deriving Y relative to the radius
    Point hat_top_left { (c.x - (r / 2)), ((this->point(0).y) - (r / 2)) };
    Point hat_bottom_left { (hat_top_left.x), (this->point(0).y) };
    Point hat_top_right { (c.x + (r / 2)), (hat_top_left.y) };
    Point hat_bottom_right { (hat_top_right.x), (this->point(0).y) };

    painter.draw_line(hat_bottom_left, hat_top_left);
    painter.draw_line(hat_top_left, hat_top_right);
    painter.draw_line(hat_top_right, hat_bottom_right);
}

void Frowny_hat::draw_specifics(Painter& painter) const
{
    // Draw the frowny first... Gonna be the same things as for Smiley_hat.
    Frowny::draw_specifics(painter);

    // Add the hat...
    int r { radius() };
    int d { r*2 };
    Point c { center() };

    // Brim
    Point left_side { this->point(0) };
    Point right_side { (left_side.x + d), left_side.y };
    painter.draw_line(left_side, right_side);

    // The top part
    Point hat_top_left { (c.x - (r / 2)), ((this->point(0).y) - (r / 2)) };
    Point hat_bottom_left { (hat_top_left.x), (this->point(0).y) };
    Point hat_top_right { (c.x + (r / 2)), (hat_top_left.y) };
    Point hat_bottom_right { (hat_top_right.x), (this->point(0).y) };

    painter.draw_line(hat_bottom_left, hat_top_left);
    painter.draw_line(hat_top_left, hat_top_right);
    painter.draw_line(hat_top_right, hat_bottom_right);
}

void Striped_rectangle::draw_specifics(Painter& painter) const
{
    Rectangle::draw_specifics(painter);

    // X for left and right sides
    const int left_side_x { this->point(0).x };
    const int right_side_x { left_side_x + this->width() };

    // Y for the top and bottom
    const int top_y { this->point(0).y };
    const int bottom_y { this->point(0).y + this->height()};

    // Number of pixels between stripes on Y axis comes from stripe_distance
    // Will also determine how many stripes there are

    for (int y {top_y + stripe_distance}; y < bottom_y; y += stripe_distance)
    {
        Point left_side { left_side_x, y };
        Point right_side { right_side_x, y };
        painter.draw_line(left_side, right_side);
    }
}

void Striped_circle::draw_specifics(Painter& painter) const
{
    Circle::draw_specifics(painter);

    const Point center_point { center() };
    const int r { radius() };

    // Draw horizontal stripes from top to bottom of the circle
    for (int y { center_point.y - r + stripe_distance };
         y < center_point.y + r;
         y += stripe_distance)
    {
        // Calculate how far this y-coordinate is from the center
        int dy { y - center_point.y };

        // Use Pythagorean theorem to find x-intersection points
        // x² + dy² = r²  =>  x = ±√(r² - dy²)
        int dx_squared { r * r - dy * dy };

        if (dx_squared >= 0)  // Make sure we're inside the circle
        {
            int dx { static_cast<int>(std::sqrt(dx_squared)) };

            Point left_point { center_point.x - dx, y };
            Point right_point { center_point.x + dx, y };

            painter.draw_line(left_point, right_point);
        }
    }
}

// Exercise 8 class
Octagon::Octagon(Point center, int radius)
    : m_center{ center }, r{ radius }
{
    const double pi { 3.14159265359 };
    const double angle_step { (2.0 * pi) / 8.0 }; // 2pi / # of sides
    const double start_angle { 90 * (pi / 180) }; // degrees * (pi / 180)

    for (int i {0}; i < 8; ++i)
    {
        double angle { start_angle + i * angle_step };
        int x { m_center.x + static_cast<int>(r * std::cos(angle)) };
        int y { m_center.y - static_cast<int>(r * std::sin(angle)) };

        add(Point{ x, y });
    }

}

void Octagon::draw_specifics(Painter& painter) const
{
    Polygon::draw_specifics(painter);
}
