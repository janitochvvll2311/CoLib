#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/Widget.hpp>
#include <CoLib/UI/Thickness.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = window.getSize();

    co::Widget widget(wsize.x, wsize.y);
    widget.shrink(10);
    widget.setColor(sf::Color::Red);

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

        window.clear();
        window.draw(widget);
        window.display();
    }

    return 0;
}