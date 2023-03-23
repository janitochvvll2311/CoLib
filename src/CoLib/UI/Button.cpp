#define COLIB_UI_EXPORTS
#include <SFML/Window/Event.hpp>
#include <CoLib/UI/Button.hpp>

namespace co
{

    const Button::EventListener &Button::getOnClickListener() const
    {
        return m_onClick;
    }

    void Button::setOnClickListener(const EventListener &value)
    {
        m_onClick = value;
    }

    bool Button::handleEvent(Node *target, const sf::Event &event)
    {
        Label::handleEvent(target, event);
        switch (event.type)
        {
        case sf::Event::MouseButtonReleased:
            if (!target && getBlock().contains({f32t(event.mouseButton.x), f32t(event.mouseButton.y)}))
            {
                focus();
                onClick(event);
                return true;
            }
            break;
        case sf::Event::GainedFocus:
            m_focused = target == this;
            break;
        }
        return false;
    }

    Button::Button()
        : m_focused(false), m_onClick() {}

    Button::~Button() {}

    ///////////////////////////////////////////////////////////////////////

    void Button::onFocus(const sf::Event &event)
    {
        spreadEvent(this, event);
    }

    void Button::onClick(const sf::Event &event)
    {
        if (m_onClick)
        {
            m_onClick(*this, event);
        }
        else
        {
            bubbleEvent(this, event);
        }
    }

}