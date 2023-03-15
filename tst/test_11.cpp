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

auto makeImage(const sf::Texture &texture)
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

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    sf::Texture texture;
    _ = texture.loadFromFile("./res/avatar.jpg");

    co::LinearLayout layout;
    layout.setBackground(makeBackground(sf::Color::White));
    layout.setOritentation(co::LinearLayout::Vertical);
    layout.setContentAlignment(co::LinearLayout::Center);

    auto image = makeImage(texture);
    layout.attach(image);
    layout.setAlignment(image, co::LinearLayout::Center);

    auto input = std::make_shared<co::Input>();
    input->setBackground(makeBackground(sf::Color::Yellow));
    input->getSpan()->getText().setFont(font);
    input->getSpan()->getText().setFillColor(sf::Color::Black);
    input->getSpan()->getText().setString("Prevent space");
    input->setMaxWidth(0);
    layout.attach(input);
    layout.setAlignment(input, co::LinearLayout::Center);

    input->compact();
    input->inflate(wsize);
    input->invalidate();

    sf::Transformable transformable;

    while (window.isOpen())
    {
        auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
        sf::Event event;
        while (window.pollEvent(event))
        {
            input->handleEvent(event);
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                wsize = sf::Vector2f(window.getSize());
                window.setView(sf::View(sf::FloatRect({0, 0}, wsize)));
                input->compact();
                input->inflate(wsize);
                input->invalidate();
                break;
            }
        }

        window.clear();
        window.draw(*input);
        window.display();
    }

    return 0;
}