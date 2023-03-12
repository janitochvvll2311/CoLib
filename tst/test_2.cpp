#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/Graphics/Ellipse.hpp>
#include <CoLib/Graphics/Triangle.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/UI/Box.hpp>
#include <CoLib/UI/Thickness.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    co::Graph graph;
    graph.setPrimitiveType(sf::PrimitiveType::TriangleFan);

    co::Rectangle rect({10, 10, 100, 100});
    co::Ellipse elli(250, 50, 100, 50);
    co::Triangle trian({400, 0}, {500, 50}, {450, 100});

    sf::Texture texture;
    auto _ = texture.loadFromFile("./res/avatar.jpg");

    auto wsize = sf::Vector2f(window.getSize());
    co::Box wbox(wsize.x, wsize.y);
    wbox.shrink(10);

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
                wbox = {wsize.x, wsize.y};
                wbox.shrink(10);
                window.setView(sf::View(sf::FloatRect({0, 0}, wsize)));
                break;
            case sf::Event::MouseButtonPressed:
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
                wbox = {cursor.x, cursor.y};
                wbox.shrink(10);
                break;
            }
        }

        sf::Vector2f cursor(sf::Mouse::getPosition(window));

        if (rect.contains(cursor) || elli.contains(cursor) || trian.contains(cursor))
        {
            window.clear(sf::Color::Green);
        }
        else
        {
            window.clear();
        }

        sf::RectangleShape shape({wbox.getWidth(), wbox.getHeight()});
        shape.setPosition({wbox.getLeft(), wbox.getTop()});
        window.draw(shape);

        auto tsize = sf::Vector2f(texture.getSize());
        auto tpart = tsize / 2.f;
        graph.setTexture(&texture);

        graph.setPoints(rect);
        graph.setTextureRect(sf::FloatRect(tpart, tpart));
        graph.fitPoints({{10, 10}, {100, 100}});
        graph.setColor(sf::Color::Red);
        window.draw(graph);

        graph.setPoints(elli);
        graph.setTextureRect(sf::FloatRect(tpart, tpart));
        graph.fitPoints({{10, 120}, {100, 100}});
        graph.setColor(sf::Color::Magenta);
        window.draw(graph);

        graph.setPoints(trian);
        graph.setTextureRect(sf::FloatRect(tpart, tpart));
        graph.fitPoints({{10, 230}, {100, 100}});
        graph.setColor(sf::Color::Blue);
        window.draw(graph);

        window.display();
    }

    return 0;
}