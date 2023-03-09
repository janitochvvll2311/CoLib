#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/Widget.hpp>
#include <CoLib/UI/Thickness.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    co::Widget widget;
    widget.setColor(sf::Color::Red);
    widget.setMargin(10);
    widget.setMaxWidth(300);
    widget.setMaxHeight(300);
    widget.setHorizontalGravity(co::Widget::Center);
    widget.setVerticalGravity(co::Widget::Start);

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
                widget.compact();
                widget.inflate({wsize.x, wsize.y});
                widget.invalidate();
                break;
            }
        }

        window.clear();
        window.draw(widget);
        window.display();
    }

    return 0;
}