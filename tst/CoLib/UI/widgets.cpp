#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/Surface.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Block.hpp>

sf::Image image;
sf::Texture texture;
sf::Font font;
bool _;

auto makeBackground(const sf::Color &color)
{
    auto texture = std::make_shared<sf::Texture>();
    _ = texture->loadFromFile("./res/avatar.jpg");
    auto surface = std::make_shared<co::Surface>();
    surface->setColor(color);
    // surface->setTexture(texture);
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
    return block;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    window.setFramerateLimit(30);
    auto wsize = sf::Vector2f(window.getSize());
    _ = image.loadFromFile("./res/avatar.jpg");
    _ = texture.loadFromImage(image);
    _ = font.loadFromFile("./res/grandview.ttf");

    auto block = makeBlock(sf::Color::White);

    auto &root = *block;

    root.compact();
    root.inflate(wsize);
    root.place({0, 0});
    root.invalidate();

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
                root.compact();
                root.inflate(wsize);
                root.place({0, 0});
                root.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                root.compact();
                root.inflate(cursor);
                root.place({0, 0});
                root.invalidate();
                break;
            }
        }
        window.clear();
        window.draw(root);
        window.display();
    }

    return 0;
}