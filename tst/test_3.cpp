#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Background.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    co::Rectangle rectangle(100, 100);
    co::Background background;

    background.compact();
    background.setColor(sf::Color::Red);
    background.inflate(wsize);
    background.shrink(10);
    background.invalidate();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                wsize = sf::Vector2f(window.getSize());
                window.setView(sf::View(sf::FloatRect({0, 0}, wsize)));
                background.compact();
                background.inflate(wsize);
                background.shrink(10);
                background.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
                background.compact();
                background.inflate(cursor);
                background.shrink(10);
                background.invalidate();
                break;
            }
        }

        window.clear();
        window.draw(background);
        window.display();
    }

    return 0;
}