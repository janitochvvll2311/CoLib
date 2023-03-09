#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/RectGeo.hpp>
#include <CoLib/Graphics/Utils.hpp>

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    sf::VertexArray array(sf::PrimitiveType::TriangleFan);
    co::RectGeo geo({{10, 10}, {100, 100}});
    co::setPoints(array, geo);
    auto& vx1 = array[0];
    auto& vx2 = array[1];
    auto& vx3 = array[2];
    auto& vx4 = array[3];

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(array);
        window.display();
    }

    return 0;
}