#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Surface.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Label.hpp>

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

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    window.setFramerateLimit(30);
    auto wsize = sf::Vector2f(window.getSize());
    _ = image.loadFromFile("./res/avatar.jpg");
    _ = texture.loadFromImage(image);
    _ = font.loadFromFile("./res/grandview.ttf");

    co::Label label;
    label.setHorizontalContentAnchor(co::Label::Anchor::Center);
    label.setVerticalContentAnchor(co::Label::Anchor::Center);
    label.getBlock().setBackground(makeBackground(sf::Color::White));
    label.getBlock().setMargin(10);
    label.getBlock().setPadding(10);
    label.getSpan().setFont(font);
    label.getSpan().setString("It Works");
    label.getSpan().setFillColor(sf::Color::Red);

    label.compact();
    label.inflate(wsize);
    label.place({0, 0});

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
                label.compact();
                label.inflate(wsize);
                label.place({0, 0});
                break;
            case sf::Event::MouseButtonPressed:
                label.compact();
                label.inflate(cursor);
                label.place({0, 0});
                break;
            }
        }
        window.clear();
        window.draw(label);
        window.display();
    }

    return 0;
}