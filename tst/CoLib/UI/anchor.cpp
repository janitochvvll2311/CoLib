#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Surface.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/FrameLayout.hpp>
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

    co::Span span;
    span.setFont(font);
    span.setString("It Works");
    span.setFillColor(sf::Color::Red);

    co::AnchorLayout layout;
    layout.setBackground(makeBackground(sf::Color::White));
    layout.setMargin(10);
    layout.setPadding(10);

    auto b1 = makeBlock(sf::Color::Red);
    layout.append(b1);
    layout.setHorizontalAnchor(b1, co::AnchorLayout::Start);

    auto b2 = makeBlock(sf::Color::Green);
    layout.append(b2);
    layout.setHorizontalAnchor(b2, co::AnchorLayout::End);

    auto b3 = makeBlock(sf::Color::Blue);
    layout.append(b3);
    layout.setHorizontalAnchor(b3, co::AnchorLayout::Center);

    layout.compact();
    layout.inflate(wsize);
    layout.place({0, 0});

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
                layout.place({0, 0});
                break;
            case sf::Event::MouseButtonPressed:
                layout.compact();
                layout.inflate(cursor);
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