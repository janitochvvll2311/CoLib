#include <SFML/Window/Event.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Input.hpp>

namespace co
{

    bool Input::handleEvent(Widget *target, const sf::Event &event)
    {
        if (!target)
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonReleased:
                if (contains({f32t(event.mouseButton.x), f32t(event.mouseButton.y)}))
                {
                    focus();
                    return true;
                }
                break;
            case sf::Event::TextEntered:
                if (false)
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
                break;
            }
        }
        return false;
    }

    Input::Input() {}
    Input::~Input() {}

    ///////////////////////////////////////////////////////////////////////

    void Input::onFocus(const sf::Event &event)
    {
        bubbleEvent(this, event);
    }

}