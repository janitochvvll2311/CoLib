#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/UI/Widget.hpp>
#include <CoLib/UI/Thickness.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    auto texture = std::make_shared<sf::Texture>();
    auto _ = texture->loadFromFile("./res/avatar.jpg");

    co::Widget widget;
    widget.setMargin(50);
    widget.setMaxWidth(300);
    widget.setMaxHeight(300);
    widget.setHorizontalAlignment(co::Widget::Center);
    widget.setVerticalAlignment(co::Widget::Center);
    // widget.setRotation(sf::degrees(45));

    co::Rectangle rect(100, 100);
    co::Graph background;
    background.setPrimitiveType(sf::PrimitiveType::TriangleFan);
    background.setPoints(rect);
    background.setTexture(texture);
    widget.setBackground(background);

    widget.compact({0, 0});
    widget.inflate({wsize.x, wsize.y});
    widget.invalidate();

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
                widget.compact({0, 0});
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