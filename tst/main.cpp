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

    sf::String text = "It Works";
    std::vector<sf::Glyph> glyphs;
    for (auto &c : text)
    {
        glyphs.push_back(font.getGlyph(c, 50, false));
    }

    sf::VertexArray array;
    co::setGlyphs(array, &glyphs.front(), glyphs.size());

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
        sf::RenderStates states;
        states.transform.translate({0, 50});
        states.texture = &font.getTexture(50);

        window.draw(array, states);
        window.display();
    }

    return 0;
}