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
    linear->append(makeBlock(sf::Color::Red));
    linear->append(makeBlock(sf::Color::Green));
    linear->append(makeBlock(sf::Color::Blue));
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
    frame->append(makeBlock(sf::Color::Red));
    return frame;
}

auto makeLabel(const sf::String &text, const sf::Font &font)
{
    auto label = std::make_shared<co::Label>();
    label->setBackground(makeBackground(sf::Color::Red));
    label->getSpan()->getText().setFont(font);
    label->getSpan()->getText().setString(text);
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
    layout.setMargin(10);
    layout.setPadding(10);
    layout.setBackground(makeBackground(sf::Color::White));
    layout.setOritentation(co::LinearLayout::Vertical);
    layout.setContentAnchor(co::LinearLayout::Center);

    auto label = std::make_shared<co::Label>();
    label->getSpan()->getText().setFont(font);
    label->getSpan()->getText().setString("My Title");
    label->getSpan()->getText().setFillColor(sf::Color::Black);
    label->getSpan()->getText().setStyle(sf::Text::Bold);
    label->setHorizontalContentAnchor(co::Label::Center);
    layout.append(label);

    auto content = makeLinear(sf::Color::Yellow);
    layout.append(content);
    layout.setAnchor(content, co::LinearLayout::Center);

    auto button = std::make_shared<co::Button>();
    button->setBackground(makeBackground(sf::Color(200, 200, 200, 255)));
    button->getSpan()->getText().setFont(font);
    button->getSpan()->getText().setString("Action");
    button->getSpan()->getText().setFillColor(sf::Color::Black);
    button->setHorizontalContentAnchor(co::Label::Center);
    button->setMaxWidth(0);
    button->setPadding({20, 10});
    button->setOnClickListener([](auto &node, auto &event)
                               { std::cout << "Clicked\n"; });
    layout.append(button);
    layout.setAnchor(button, co::LinearLayout::Center);

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
            layout.dispatchEvent(nullptr, event);
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
            }
        }

        window.clear();
        window.draw(layout);
        window.display();
    }

    return 0;
}