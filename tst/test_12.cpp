#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/Node.hpp>

sf::Font font;
sf::Texture texture;

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    window.setFramerateLimit(60);
    auto wsize = sf::Vector2f(window.getSize());

    auto _ = font.loadFromFile("./res/grandview.ttf");
    _ = texture.loadFromFile("./res/avatar.jpg");

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
                break;
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}