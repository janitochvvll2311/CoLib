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
#include <CoLib/UI/Image.hpp>
#include <CoLib/UI/Input.hpp>
#include <CoLib/UI/VirtualLayout.hpp>

sf::Font font;
sf::Texture texture;

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

auto makeLabel(const sf::String &text)
{
    auto label = std::make_shared<co::Label>();
    label->setBackground(makeBackground(sf::Color::Red));
    label->getSpan()->getText().setFont(font);
    label->getSpan()->getText().setString(text);
    return label;
}

auto makeButton(const sf::String &text)
{
    auto button = std::make_shared<co::Button>();
    button->setBackground(makeBackground(sf::Color(200, 200, 200, 255)));
    button->getSpan()->getText().setFont(font);
    button->getSpan()->getText().setString(text);
    button->setMaxWidth(0);
    button->setMaxHeight(0);
    button->setPadding({20, 10});
    return button;
}

auto makeSpan(const sf::String &text)
{
    auto span = std::make_shared<co::Span>();
    span->getText().setFont(font);
    span->getText().setString(text);
    span->getText().setFillColor(sf::Color::Red);
    return span;
}

auto makeImage()
{
    auto image = std::make_shared<co::Image>();
    image->setBackground(makeBackground(sf::Color::Red));
    image->setPadding(10);
    image->setMinWidth(100);
    image->setMinHeight(100);
    image->setMaxWidth(0);
    image->setMaxHeight(0);
    image->getImage()->getGraph().setTexture(&texture);
    return image;
}

auto makeInput()
{
    auto input = std::make_shared<co::Input>();
    input->setBackground(makeBackground(sf::Color::Yellow));
    input->getSpan()->getText().setFont(font);
    input->getSpan()->getText().setFillColor(sf::Color::Black);
    input->getSpan()->getText().setString("Prevent space");
    input->setMaxWidth(0);
    return input;
}

auto makeInterface()
{
    auto layout = std::make_shared<co::LinearLayout>();
    layout->setBackground(makeBackground(sf::Color::White));
    layout->setOritentation(co::LinearLayout::Vertical);
    layout->setContentAnchor(co::LinearLayout::Center);

    auto image = makeImage();
    layout->attach(image);
    layout->setAnchor(image, co::LinearLayout::Center);

    auto input1 = makeInput();
    layout->attach(input1);
    layout->setAnchor(input1, co::LinearLayout::Center);

    auto input2 = makeInput();
    layout->attach(input2);
    layout->setAnchor(input2, co::LinearLayout::Center);

    auto button = makeButton("Change");
    button->setOnClickListener(
        [=](auto &widget, auto &event)
        {
            image->setMinWidth(image->getMinWidth() + 10);
            image->invalidate();
        });
    layout->attach(button);
    layout->setAnchor(button, co::LinearLayout::Center);
    return layout;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    window.setFramerateLimit(60);
    auto wsize = sf::Vector2f(window.getSize());

    auto _ = font.loadFromFile("./res/grandview.ttf");
    _ = texture.loadFromFile("./res/avatar.jpg");

    co::VirtualLayout layout;
    layout.attach(makeInterface());

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
                layout.invalidate();
                break;
            case sf::Event::MouseWheelScrolled:
                transformable.move({0, event.mouseWheelScroll.delta});
                layout.setInnerTransform(transformable.getTransform());
                break;
            }
        }

        if (!layout.isValid())
        {
            layout.compact();
            layout.inflate(wsize);
        }

        window.clear();
        window.draw(layout);
        window.display();
    }

    return 0;
}