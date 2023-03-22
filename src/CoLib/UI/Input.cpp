#define COLIB_UI_EXPORTS
#include <SFML/Window/Event.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Input.hpp>

namespace co
{

    bool Input::handleEvent(Node *target, const sf::Event &event)
    {

        switch (event.type)
        {
        case sf::Event::MouseButtonReleased:
            if (!target && getBlock().contains({f32t(event.mouseButton.x), f32t(event.mouseButton.y)}))
            {
                focus();
                return true;
            }
            break;
        case sf::Event::GainedFocus:
            m_focused = target == this;
            break;
        case sf::Event::TextEntered:
            if (m_focused)
            {
                auto &span = getSpan();
                auto &string = getSpan().getString();
                switch (event.text.unicode)
                {
                case '\b':
                    span.setString(string.substring(0, string.getSize() - 1));
                    break;
                default:
                    span.setString(string + event.text.unicode);
                    break;
                }
                return true;
            }
            break;
        }
        return false;
    }

    Input::Input()
        : m_focused(false) {}

    Input::~Input() {}

    ///////////////////////////////////////////////////////////////////////

    void Input::onFocus(const sf::Event &event)
    {
        spreadEvent(this, event);
    }

}