#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/Graphics/Utils.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    co::Graph graph;
    graph.setText("It Works", font, 50);
    graph.setOrigin({0, -50});

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
            }
        }

        window.clear();
        window.draw(graph);
        window.display();
    }

    return 0;
}