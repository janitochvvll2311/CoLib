#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/FrameLayout.hpp>
#include <CoLib/UI/LinearLayout.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    co::Rectangle rect(100, 100);

    co::Graph graph;
    // graph.setText("It Works", font, 50);
    // graph.setOrigin({0, -50});
    // graph.setPosition({0, 50});
    graph.setPrimitiveType(sf::PrimitiveType::TriangleFan);
    graph.setPoints(rect);
    graph.setColor(sf::Color::Red);

    auto span = std::make_shared<co::Span>();
    span->setString("It Works");
    span->setFont(font);
    span->setBackground(graph);
    span->setMaxWidth(100);
    span->setMaxHeight(100);
    span->setHorizontalAlignment(co::Span::Center);
    span->setVerticalAlignment(co::Span::Center);
    span->setMargin(10);

    co::FrameLayout layout;
    layout.attach(span);
    graph.setColor(sf::Color::Blue);
    layout.setBackground(graph);
    layout.setMargin(10);
    layout.setPadding(10);

    layout.compact({0, 0});
    layout.inflate({wsize.x, wsize.y});
    layout.invalidate();

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
                layout.compact({0, 0});
                layout.inflate({wsize.x, wsize.y});
                layout.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
                layout.compact({0, 0});
                layout.inflate({cursor.x, cursor.y});
                layout.invalidate();
                break;
            }
        }

        window.clear();
        // window.draw(graph);
        // window.draw(text);
        window.draw(layout);
        window.display();
    }

    return 0;
}