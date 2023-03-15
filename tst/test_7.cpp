#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/LinearLayout.hpp>
#include <CoLib/UI/VirtualLayout.hpp>

auto makeBackground(const sf::Color &color)
{
    auto background = std::make_shared<co::Background>();
    background->getGraph().setColor(color);
    return background;
}

auto makeBlock(const sf::Color &color)
{
    auto block = std::make_shared<co::Block>();
    block->setBackground(makeBackground(color));
    block->setMinWidth(100);
    block->setMinHeight(100);
    block->setMaxWidth(0);
    block->setMaxHeight(0);
    block->setMargin(10);
    return block;
}

auto makeLinear(const sf::Color &color)
{
    auto linear = std::make_shared<co::LinearLayout>();
    linear->setBackground(makeBackground(color));
    linear->setMargin(10);
    linear->setPadding(10);
    linear->attach(makeBlock(sf::Color::Red));
    linear->attach(makeBlock(sf::Color::Green));
    linear->attach(makeBlock(sf::Color::Blue));
    linear->setMaxWidth(0);
    linear->setMaxHeight(0);
    return linear;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    co::VirtualLayout layout;
    layout.setBackground(makeBackground(sf::Color::White));
    layout.setMargin(10);
    layout.setPadding(10);
    // layout.setMinWidth(100);
    // layout.setMinHeight(100);

    auto linear = makeLinear(sf::Color::Yellow);
    layout.attach(linear);
    layout.setHorizontalAlignment(linear, co::FrameLayout::Center);
    layout.setVerticalAlignment(linear, co::FrameLayout::Center);

    layout.compact();
    layout.inflate(wsize);
    layout.invalidate();

    sf::Transformable transformable;

    while (window.isOpen())
    {
        auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
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
                layout.compact();
                layout.inflate(wsize);
                layout.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                layout.compact();
                layout.inflate(cursor);
                layout.invalidate();
                break;
            case sf::Event::MouseWheelScrolled:
            {
                transformable.move({event.mouseWheelScroll.delta * 10, 0});
                layout.setInnterTransform(transformable.getTransform());
                layout.invalidate();
            }
            break;
            }
        }

        window.clear();
        window.draw(layout);
        window.display();
    }

    return 0;
}