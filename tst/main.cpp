#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/Graphics/Ellipse.hpp>
#include <CoLib/Graphics/Triangle.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/UI/Box.hpp>
#include <CoLib/UI/Thickness.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    sf::VertexArray array(sf::PrimitiveType::TriangleFan);
    co::Rectangle rect({10, 10, 100, 100});
    co::Ellipse elli(250, 50, 100, 50);
    co::Triangle trian({400, 0}, {500, 50}, {450, 100});

    sf::Texture texture;
    auto _ = texture.loadFromFile("./res/avatar.jpg");

    auto wsize = sf::Vector2f(window.getSize());
    co::Box wbox(wsize.x, wsize.y);

    co::Box box(wbox);
    box.shrink(10);
    box.setWidth(100, co::Box::Center);

    sf::RectangleShape shape({box.getWidth(), box.getHeight()});
    shape.setPosition({box.getLeft(), box.getTop()});

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

        auto tsize = sf::Vector2f(texture.getSize());
        auto tpart = tsize / 2.f;

        co::setPoints(array, rect);
        co::setTexCoords(array, sf::FloatRect(tpart, tpart));
        co::fitPoints(array, {{10, 10}, {100, 100}});
        // co::setColors(array, sf::Color::Red);
        window.draw(array, &texture);

        co::setPoints(array, elli);
        co::setTexCoords(array, sf::FloatRect(tpart, tpart));
        co::fitPoints(array, {{10, 120}, {100, 100}});
        // co::setColors(array, sf::Color::Magenta);
        window.draw(array, &texture);

        co::setPoints(array, trian);
        co::setTexCoords(array, sf::FloatRect(tpart, tpart));
        co::fitPoints(array, {{10, 230}, {100, 100}});
        // co::setColors(array, sf::Color::Blue);
        window.draw(array, &texture);

        window.draw(shape);

        window.display();
    }

    return 0;
}