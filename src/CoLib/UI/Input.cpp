#define COLIB_UI_EXPORTS
#include <SFML/Window/Event.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Input.hpp>

namespace co
{

    const Input::EventListener &Input::getOnTextEnteredListener() const
    {
        return m_onTextEntered;
    }

    void Input::setOnTextEnteredListener(const EventListener &value)
    {
        m_onTextEntered = value;
    }

    bool Input::handleEvent(Node *target, const sf::Event &event)
    {
        Label::handleEvent(target, event);
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
                getBlock().invalidate();
                onTextEntered(event);
                return true;
            }
            break;
        }
        return false;
    }

    void Input::enterText(sf::Uint32 unicode)
    {
        sf::Event event;
        event.type = sf::Event::TextEntered;
        event.text.unicode = unicode;
        onTextEntered(event);
    }

    Input::Input()
        : m_focused(false) {}

    Input::~Input() {}

    ///////////////////////////////////////////////////////////////////////

    void Input::onFocus(const sf::Event &event)
    {
        spreadEvent(this, event);
    }

    void Input::onTextEntered(const sf::Event &event)
    {
        if (m_onTextEntered)
        {
            m_onTextEntered(*this, event);
        }
        else
        {
            bubbleEvent(this, event);
        }
    }

}