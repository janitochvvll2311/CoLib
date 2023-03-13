#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/FrameLayout.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    co::Rectangle rectangle(100, 100);
    co::Background background;

    auto block = std::make_shared<co::Block>();
    background.setColor(sf::Color::Red);
    block->setBackground(std::make_shared<co::Background>(background));
    // block->setMargin(10);
    block->setMinWidth(100);
    block->setMinHeight(100);
    block->setMaxWidth(0);
    block->setMaxHeight(0);

    co::FrameLayout frame;
    frame.setPadding(1);
    background.setColor(sf::Color::White);
    frame.setMargin(10);
    frame.setMinWidth(200);
    frame.setMinHeight(200);
    frame.setBackground(std::make_shared<co::Background>(background));
    frame.attach(block);

    frame.compact();
    frame.inflate(wsize, nullptr);
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
                frame.inflate(wsize, nullptr);
                frame.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
                frame.compact();
                frame.inflate(cursor, nullptr);
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