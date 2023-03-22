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

class Button
    : public co::Label
{

public:
    bool handleEvent(Node *target, const sf::Event &event)
    {
        if (!target && event.type == sf::Event::MouseButtonReleased)
        {
            if (getBlock().contains({float(event.mouseButton.x), float(event.mouseButton.y)}))
            {
                std::cout << "Clicked\n";
            }
        }
        return false;
    }
};

auto makeButton()
{
    auto button = std::make_shared<Button>();
    button->setHorizontalContentAnchor(co::Label::Anchor::Center);
    button->setVerticalContentAnchor(co::Label::Anchor::Center);
    button->getBlock().setBackground(makeBackground(sf::Color::White));
    button->getBlock().setMargin(10);
    button->getBlock().setPadding(10);
    button->getSpan().setFont(font);
    button->getSpan().setString("It Works");
    button->getSpan().setFillColor(sf::Color::Red);
    return button;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    window.setFramerateLimit(30);
    auto wsize = sf::Vector2f(window.getSize());
    _ = image.loadFromFile("./res/avatar.jpg");
    _ = texture.loadFromImage(image);
    _ = font.loadFromFile("./res/grandview.ttf");

    co::FrameLayout layout;
    layout.setBackground(makeBackground(sf::Color::White));
    layout.append(makeFrame(sf::Color::Red, makeFrame(sf::Color::Green, makeFrame(sf::Color::Blue, makeButton()))));

    layout.compact();
    layout.inflate(wsize);
    layout.place({0, 0});

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