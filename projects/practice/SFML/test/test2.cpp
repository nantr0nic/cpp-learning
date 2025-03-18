#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    unsigned int width = 800;
    unsigned int height = 600;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({width, height}), "Tutorials");
    window->setFramerateLimit(60);

    sf::ConvexShape convex;
    convex.setPointCount(6);
    convex.setPoint(0, {13.0f, 17.0f});
    convex.setPoint(1, {3.5f, 1.6f});
    convex.setPoint(2, {0.25f, -12.0f});
    convex.setPoint(3, {-12.0f, -7.3f});
    convex.setPoint(4, {-12.5f, -1.6f});
    convex.setPoint(5, {-8.0f, 9.5f});
    convex.setOrigin(convex.getGeometricCenter());
    convex.setFillColor(sf::Color(0x3F00FFFF));
    convex.setOutlineThickness(2.4f);
    convex.setOutlineColor(sf::Color(0xFF8888FF));
    convex.setPosition({width / 2.0f, height / 2.0f});

    sf::CircleShape circle(64.0f);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition({width / 4.0f, height / 4.0f});
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineThickness(3.0f);
    circle.setOutlineColor(sf::Color::Magenta);
    circle.setPointCount(3); // can set to any # of sides/points

    sf::RectangleShape rectangle({50.0f, 80.0f});
    rectangle.setOrigin(rectangle.getSize() / 2.0f);
    rectangle.setPosition({width / 2.0f, height / 2.0f});
    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setOutlineThickness(5.0f);
    rectangle.setOutlineColor(sf::Color::Blue);


    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>()) 
            {
                window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window->close();
                }
            }
        }

        circle.rotate(sf::degrees(6));
        circle.move({0.2f, 0.2f});     // in SFML, y-axis is inverted
        rectangle.move({-0.2f, -0.2f});
        rectangle.rotate(sf::degrees(-2));
        convex.rotate(sf::degrees(1));
        convex.move({0.2f, -0.2f});

        circle.setFillColor(sf::Color::Green);
        rectangle.setFillColor(sf::Color::Yellow);

        if (circle.getGlobalBounds().findIntersection(rectangle.getGlobalBounds()))
        {
            circle.setFillColor(sf::Color::Red);
            rectangle.setFillColor(sf::Color::Red);
        }

        // Render
        window->clear();

        // Drawing
        window->draw(circle);
        window->draw(rectangle);
        window->draw(convex);

        window->display();
    }

    delete window;
    return 0;
}