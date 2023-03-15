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

    bool Button::handleEvent(Widget *target, const sf::Event &event)
    {
        if (!target && event.type == sf::Event::MouseButtonReleased)
        {
            if (contains({f32t(event.mouseButton.x), f32t(event.mouseButton.y)}))
            {
                onClick(event);
                return true;
            }
        }
        return Label::handleEvent(target, event);
    }

    void Button::click(sf::Mouse::Button button, f32t x, f32t y)
    {
        sf::Event event;
        event.type = sf::Event::MouseButtonReleased;
        event.mouseButton.button = button;
        event.mouseButton.x = x;
        event.mouseButton.y = y;
        onClick(event);
    }

    Button::Button()
        : m_onClick() {}

    Button::~Button() {}

    ///////////////////////////////////////////////////////////////////////

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