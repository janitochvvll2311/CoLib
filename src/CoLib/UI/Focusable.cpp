#define COLIB_UI_EXPORTS
#include <SFML/Window/Event.hpp>
#include <CoLib/UI/Focusable.hpp>

namespace co
{

    void Focusable::focus()
    {
        sf::Event event;
        event.type = sf::Event::GainedFocus;
        onFocus(event);
    }

    Focusable::Focusable() {}
    Focusable::~Focusable() {}

}