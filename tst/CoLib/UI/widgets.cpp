#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Surface.hpp>
#include <CoLib/UI/Block.hpp>

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

    co::Block block;
    block.setBackground(makeBackground(sf::Color::Yellow));
    block.setMargin(10);
    block.setPadding(10);

    block.compact();
    block.inflate(wsize);

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
                block.compact();
                block.inflate(wsize);
                break;
            case sf::Event::MouseButtonPressed:
                block.compact();
                block.inflate(cursor);
                break;
            }
        }
        window.clear();
        window.draw(block);
        window.draw(span);
        window.display();
    }

    return 0;
}