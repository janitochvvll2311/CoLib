#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/Graphics/Ellipse.hpp>
#include <CoLib/Graphics/Triangle.hpp>

sf::Image image;
sf::Texture texture;
sf::Font font;
bool _;

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    _ = image.loadFromFile("./res/avatar.jpg");
    _ = texture.loadFromImage(image);
    _ = font.loadFromFile("./res/grandview.ttf");

    co::Rectangle rectangle(10, 10, 100, 100);
    co::Ellipse ellipse(170, 60, 50, 50);
    co::Triangle triangle({230, 10}, {330, 50}, {290, 100});
    sf::VertexArray array;
    array.setPrimitiveType(sf::PrimitiveType::TriangleFan);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        sf::Vector2f cursor(sf::Mouse::getPosition(window));
        if (rectangle.contains(cursor) || ellipse.contains(cursor) || triangle.contains(cursor))
        {
            window.clear(sf::Color::White);
        }
        else
        {
            window.clear(sf::Color::Black);
        }

        co::setPoints(array, rectangle);
        co::setColors(array, sf::Color::Red);
        window.draw(array);

        co::setPoints(array, ellipse);
        co::setColors(array, sf::Color::Green);
        window.draw(array);

        co::setPoints(array, triangle);
        co::setColors(array, sf::Color::Blue);
        window.draw(array);

        window.display();
    }

    return 0;
}