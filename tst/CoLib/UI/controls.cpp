#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Surface.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Label.hpp>
#include <CoLib/UI/Button.hpp>
#include <CoLib/UI/Input.hpp>
#include <CoLib/UI/AnchorLayout.hpp>

sf::Image image;
sf::Texture texture;
sf::Font font;
bool _;

auto makeBackground(const sf::Color &color)
{
    auto surface = std::make_shared<co::Surface>();
    surface->setColor(color);
    return surface;
}

auto makeSpan(const sf::String &string, const sf::Color &color)
{
    auto span = std::make_shared<co::Span>();
    span->setFont(font);
    span->setString(string);
    span->setFillColor(color);
    return span;
}

auto makeBlock(const sf::Color &color)
{
    auto block = std::make_shared<co::Block>();
    block->setBackground(makeBackground(color));
    block->setMargin(10);
    block->setPadding(10);
    block->setMinWidth(100);
    block->setMinHeight(100);
    block->setMaxWidth(0);
    block->setMaxHeight(0);
    return block;
}

auto makeFrame(const sf::Color &color, const co::SharedNode &child = nullptr)
{
    auto frame = std::make_shared<co::FrameLayout>();
    frame->setBackground(makeBackground(color));
    frame->setMargin(10);
    frame->setPadding(10);
    frame->setMaxWidth(0);
    frame->setMaxHeight(0);
    if (child)
    {
        frame->append(child);
    }
    return frame;
}

auto makeInput()
{
    auto input = std::make_shared<co::Input>();
    input->setHorizontalContentAnchor(co::Label::Anchor::Center);
    input->setVerticalContentAnchor(co::Label::Anchor::Center);
    input->getBlock().setBackground(makeBackground(sf::Color::Yellow));
    input->getBlock().setMargin(10);
    input->getBlock().setPadding(10);
    input->getBlock().setMaxWidth(0);
    input->getBlock().setMaxHeight(0);
    input->getSpan().setFont(font);
    input->getSpan().setString("It Works");
    input->getSpan().setFillColor(sf::Color::Red);
    return input;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    window.setFramerateLimit(30);
    auto wsize = sf::Vector2f(window.getSize());
    _ = image.loadFromFile("./res/avatar.jpg");
    _ = texture.loadFromImage(image);
    _ = font.loadFromFile("./res/grandview.ttf");

    co::AnchorLayout layout;
    layout.setBackground(makeBackground(sf::Color::White));
    layout.setMargin(10);
    layout.setPadding(10);

    auto input1 = makeInput();
    layout.append(input1);
    layout.setHorizontalAnchor(input1, co::AnchorLayout::Start);
    layout.setVerticalAnchor(input1, co::AnchorLayout::Start);

    auto input2 = makeInput();
    layout.append(input2);
    layout.setHorizontalAnchor(input2, co::AnchorLayout::End);
    layout.setVerticalAnchor(input2, co::AnchorLayout::End);

    auto input3 = makeInput();
    layout.append(input3);
    layout.setHorizontalAnchor(input3, co::AnchorLayout::Center);
    layout.setVerticalAnchor(input3, co::AnchorLayout::Center);

    layout.compact();
    layout.inflate(wsize);
    layout.place({0, 0});

    while (window.isOpen())
    {
        auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (layout.dispatchEvent(nullptr, event))
            {
                layout.compact();
                layout.inflate(wsize);
                layout.place({0, 0});
            }
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
                layout.place({0, 0});
                break;
            }
        }
        window.clear();
        window.draw(layout);
        window.display();
    }

    return 0;
}