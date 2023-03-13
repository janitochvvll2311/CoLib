#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Span.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    co::Rectangle rectangle(100, 100);

    co::Span span;
    span.setString("It Works");
    span.setFont(font);
    span.setCharacterSize(50);
    // span.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::StrikeThrough | sf::Text::Underlined);
    span.setFillColor(sf::Color::Green);
    span.setOutlineThickness(10);
    span.setOutlineColor(sf::Color::Blue);
    span.compact();
    span.inflate(wsize);
    span.setLeft(100);
    span.setTop(100);
    span.invalidate();

    co::Background background;
    background.setColor(sf::Color::Red);
    background.compact();
    background.inflate({span.getWidth(), span.getHeight()});
    background.setLeft(100);
    background.setTop(100);
    background.invalidate();

    while (window.isOpen())
    {
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
                span.compact();
                span.inflate(wsize);
                span.setLeft(100);
                span.setTop(100);
                span.invalidate();
                background.compact();
                background.inflate({span.getWidth(), span.getHeight()});
                background.setLeft(100);
                background.setTop(100);
                background.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
                span.compact();
                span.inflate(cursor);
                span.setLeft(100);
                span.setTop(100);
                span.invalidate();
                background.compact();
                background.inflate({span.getWidth(), span.getHeight()});
                background.setLeft(100);
                background.setTop(100);
                background.invalidate();
                break;
            }
        }

        window.clear();
        window.draw(background);
        window.draw(span);
        window.display();
    }

    return 0;
}