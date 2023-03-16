#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/LinearLayout.hpp>

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
    block->setMinHeight(100);
    block->setMaxHeight(0);
    block->setMargin(10);
    return block;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    co::Rectangle rectangle(100, 100);

    co::LinearLayout linear;
    linear.setBackground(makeBackground(sf::Color::White));
    linear.setPadding(10);
    linear.setMargin(10);
    // linear.setOrientation(co::LinearLayout::Vertical);
    linear.setReverse();
    linear.setContentAnchor(co::LinearLayout::Center);
    // linear.setMinWidth(200);
    // linear.setMinHeight(200);

    auto b1 = makeBlock(sf::Color::Red);
    linear.append(b1);
    linear.setAnchor(b1, co::LinearLayout::Start);
    linear.setWeight(b1, 0.5);

    auto b2 = makeBlock(sf::Color::Green);
    linear.append(b2);
    linear.setAnchor(b2, co::LinearLayout::Center);
    linear.setWeight(b2, 0.25);

    auto b3 = makeBlock(sf::Color::Blue);
    linear.append(b3);
    linear.setAnchor(b3, co::LinearLayout::End);
    linear.setWeight(b3, 0.25);

    linear.compact();
    linear.inflate(wsize);
    linear.invalidate();

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
                linear.compact();
                linear.inflate(wsize);
                linear.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
                linear.compact();
                linear.inflate(cursor);
                linear.invalidate();
                break;
            }
        }

        window.clear();
        window.draw(linear);
        window.display();
    }

    return 0;
}