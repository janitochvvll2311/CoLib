#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/LinearLayout.hpp>
#include <CoLib/UI/VirtualLayout.hpp>
#include <CoLib/UI/Button.hpp>

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

auto makeFrame(const sf::Color &color)
{
    auto frame = std::make_shared<co::FrameLayout>();
    frame->setBackground(makeBackground(color));
    frame->setMargin(10);
    frame->setPadding(10);
    frame->attach(makeBlock(sf::Color::Red));
    return frame;
}

auto makeLabel(const sf::String &text, const sf::Font &font)
{
    auto label = std::make_shared<co::Label>();
    label->getBlock().setBackground(makeBackground(sf::Color::Red));
    label->getSpan().getText().setFont(font);
    label->getSpan().getText().setString(text);
    return label;
}

auto makeSpan(const sf::String &text, const sf::Font &font)
{
    auto span = std::make_shared<co::Span>();
    span->getText().setFont(font);
    span->getText().setString(text);
    span->getText().setFillColor(sf::Color::Red);
    return span;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    co::LinearLayout layout;
    layout.setBackground(makeBackground(sf::Color::White));
    layout.setOritentation(co::LinearLayout::Vertical);

    auto label = std::make_shared<co::Label>();
    label->getSpan().getText().setFont(font);
    label->getSpan().getText().setString("My Title");
    label->getSpan().getText().setFillColor(sf::Color::Black);
    label->getSpan().getText().setStyle(sf::Text::Bold);
    label->setHorizontalContentAlignment(co::Label::Center);
    layout.attach(label);

    layout.attach(makeLinear(sf::Color::Yellow));

    auto button = std::make_shared<co::Button>();
    button->getBlock().setBackground(makeBackground(sf::Color(200, 200, 200, 255)));
    button->getSpan().getText().setFont(font);
    button->getSpan().getText().setString("Action");
    button->getSpan().getText().setFillColor(sf::Color::Black);
    button->setHorizontalContentAlignment(co::Label::Center);
    button->getBlock().setMaxWidth(0);
    button->getBlock().setPadding({20, 10});
    layout.attach(button);
    layout.setAlignment(button, co::LinearLayout::Center);

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
            layout.handleEvent(event);
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
            }
        }

        window.clear();
        window.draw(layout);
        window.display();
    }

    return 0;
}