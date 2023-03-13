#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/FrameLayout.hpp>

auto makeBackground(const sf::Color &color)
{
    auto background = std::make_shared<co::Background>();
    background->setColor(color);
    return background;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    co::Rectangle rectangle(100, 100);

    co::FrameLayout frame;
    frame.setBackground(makeBackground(sf::Color::White));
    frame.setPadding(10);
    frame.setMargin(10);
    frame.setMinWidth(200);
    frame.setMinHeight(200);

    auto block = std::make_shared<co::Block>();
    block->setBackground(makeBackground(sf::Color::Red));
    // block->setMargin(10);
    block->setMinWidth(100);
    block->setMinHeight(100);
    block->setMaxWidth(0);
    block->setMaxHeight(0);

    frame.attach(block);
    frame.setHorizontalAlignment(block, co::FrameLayout::Center);
    frame.setVerticalAlignment(block, co::FrameLayout::Center);

    frame.compact();
    frame.inflate(wsize);
    frame.invalidate();

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
                frame.compact();
                frame.inflate(wsize);
                frame.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
                frame.compact();
                frame.inflate(cursor);
                frame.invalidate();
                break;
            }
        }

        window.clear();
        window.draw(frame);
        window.display();
    }

    return 0;
}