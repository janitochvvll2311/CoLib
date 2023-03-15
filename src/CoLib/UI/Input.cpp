#include <SFML/Window/Event.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Input.hpp>

namespace co
{

    bool Input::handleEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::TextEntered)
        {
            auto &text = getSpan()->getText();
            auto &string = text.getString();
            switch (event.text.unicode)
            {
            case '\b':
                text.setString(string.substring(0, string.getSize() - 1));
                break;
            default:
                text.setString(string + event.text.unicode);
                break;
            }
            invalidate();
            return true;
        }
        return Label::handleEvent(event);
    }

    Input::Input() {}
    Input::~Input() {}

}