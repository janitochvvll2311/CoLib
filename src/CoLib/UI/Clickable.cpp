#include <SFML/Window/Event.hpp>
#include <CoLib/UI/Clickable.hpp>

namespace co
{

    void Clickable::click(sf::Mouse::Button button, f32t x, f32t y)
    {
        sf::Event event;
        event.type = sf::Event::MouseButtonReleased;
        event.mouseButton.button = button;
        event.mouseButton.x = x;
        event.mouseButton.y = y;
        onClick(event);
    }

    Clickable::Clickable() {}
    Clickable::~Clickable() {}

}