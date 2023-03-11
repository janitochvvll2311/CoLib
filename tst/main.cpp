#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/FrameLayout.hpp>
#include <CoLib/UI/LinearLayout.hpp>

auto makeWidget(const sf::Font &font, const co::Graph &background)
{
    auto widget = std::make_shared<co::Widget>();
    widget->setBackground(background);
    widget->setMinWidth(100);
    widget->setMinHeight(100);
    widget->setMargin(10);
    return widget;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    co::Rectangle rect(100, 100);

    co::Graph graph;
    graph.setPrimitiveType(sf::PrimitiveType::TriangleFan);
    graph.setPoints(rect);

    co::LinearLayout layout;
    layout.setBackground(graph);
    layout.setMargin(10);
    layout.setPadding(10);
    layout.setMaxWidth(0);
    layout.setMaxHeight(0);

    //////////////////////////////////////////////

    graph.setColor(sf::Color::Red);
    layout.attach(makeWidget(font, graph));

    graph.setColor(sf::Color::Green);
    layout.attach(makeWidget(font, graph));

    graph.setColor(sf::Color::Blue);
    layout.attach(makeWidget(font, graph));

    //////////////////////////////////////////////

    layout.compact();
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
                layout.compact();
                layout.inflate({wsize.x, wsize.y});
                layout.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
                layout.compact();
                layout.inflate({cursor.x, cursor.y});
                layout.invalidate();
                break;
            }
        }

        window.clear();
        window.draw(layout);
        window.display();
    }

    return 0;
}