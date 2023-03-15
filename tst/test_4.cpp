#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Block.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    co::Rectangle rectangle(100, 100);
    auto background = std::make_shared<co::Background>();

    co::Block block;
    block.setBackground(background);
    block.setMargin(10);
    block.setPadding(10);
    // block.setMinWidth(100);
    // block.setMinHeight(100);
    // block.setMaxWidth(0);
    // block.setMaxHeight(0);

    block.compact();
    block.inflate(wsize);
    block.invalidate();

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
                block.compact();
                block.inflate(wsize);
                block.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
                block.compact();
                block.inflate(cursor);
                block.invalidate();
                break;
            }
        }

        window.clear();
        window.draw(block);
        window.display();
    }

    return 0;
}