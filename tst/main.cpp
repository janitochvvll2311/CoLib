#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/UI/Widget.hpp>
#include <CoLib/UI/FrameLayout.hpp>
#include <CoLib/UI/Thickness.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    auto texture = std::make_shared<sf::Texture>();
    auto _ = texture->loadFromFile("./res/avatar.jpg");

    co::Rectangle rect(100, 100);
    co::Graph background;
    background.setPrimitiveType(sf::PrimitiveType::TriangleFan);
    background.setPoints(rect);

    co::FrameLayout layout;
    layout.setBackground(background);
    layout.setMargin(10);
    layout.setPadding(10);

    background.setColor(sf::Color::Red);
    auto subLayout = std::make_shared<co::FrameLayout>();
    subLayout->setBackground(background);
    subLayout->setMargin(10);
    subLayout->setPadding(10);
    subLayout->setMinWidth(300);
    subLayout->setMaxWidth(400);
    subLayout->setMaxHeight(400);
    subLayout->setHorizontalAlignment(co::Layout::Center);
    subLayout->setVerticalAlignment(co::Layout::Center);
    layout.attach(subLayout);

    background.setColor(sf::Color::Blue);
    auto widget = std::make_shared<co::Widget>();
    widget->setBackground(background);
    widget->setMargin(10);
    widget->setMinHeight(100);
    widget->setMaxWidth(200);
    widget->setMaxHeight(200);
    widget->setHorizontalAlignment(co::Widget::Center);
    widget->setVerticalAlignment(co::Widget::Center);
    subLayout->attach(widget);

    layout.compact({0, 0});
    layout.inflate({wsize.x, wsize.y});
    layout.invalidate();
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
                layout.compact({0, 0});
                layout.inflate({wsize.x, wsize.y});
                layout.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
                layout.compact({0, 0});
                layout.inflate({cursor.x, cursor.y});
                layout.invalidate();
                break;
            }
        }

        window.clear();
        window.draw(layout);
        window.display();
    }

    return 0;
}