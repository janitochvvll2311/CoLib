#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Surface.hpp>

sf::Image image;
sf::Texture texture;
sf::Font font;
bool _;

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

    co::Surface surface;
    surface.compact();
    surface.inflate(wsize);
    surface.update();

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
                surface.compact();
                surface.inflate(wsize);
                surface.update();
                break;
            case sf::Event::MouseButtonPressed:
                surface.compact();
                surface.inflate(cursor);
                surface.update();
                break;
            }
        }
        window.clear();
        window.draw(surface);
        window.draw(span);
        window.display();
    }

    return 0;
}