#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/Graphics/Ellipse.hpp>
#include <CoLib/Graphics/Triangle.hpp>
#include <CoLib/Graphics/Utils.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    sf::VertexArray array(sf::PrimitiveType::TriangleFan);
    co::Rectangle rect({10, 10, 100, 100});
    co::Ellipse elli(250, 50, 100, 50);
    co::Triangle trian({400, 0}, {500, 50}, {450, 100});

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

        if (rect.contains(cursor) || elli.contains(cursor) || trian.contains(cursor))
        {
            window.clear(sf::Color::Green);
        }
        else
        {
            window.clear();
        }

        co::setPoints(array, rect);
        co::fitPoints(array, {{10, 10}, {50, 50}});
        window.draw(array);

        co::setPoints(array, elli);
        co::fitPoints(array, {{10, 110}, {50, 50}});
        window.draw(array);

        co::setPoints(array, trian);
        co::fitPoints(array, {{10, 210}, {50, 50}});
        window.draw(array);

        window.display();
    }

    return 0;
}