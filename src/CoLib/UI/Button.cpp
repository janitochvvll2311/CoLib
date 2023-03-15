#include <SFML/Window/Event.hpp>
#include <CoLib/UI/Button.hpp>

namespace co
{

    const Button::OnClickListener &Button::getOnClickListener() const
    {
        return m_onClick;
    }

    void Button::setOnClickListener(const OnClickListener &value)
    {
        m_onClick = value;
    }

    bool Button::handleEvent(Widget *target, const sf::Event &event)
    {
        if (!target && event.type == sf::Event::MouseButtonReleased)
        {
            if (contains({f32t(event.mouseButton.x), f32t(event.mouseButton.y)}))
            {
                if (m_onClick)
                {
                    m_onClick(*this);
                }
                else
                {
                    bubbleEvent(this, event);
                }
                return true;
            }
        }
        return Label::handleEvent(target, event);
    }

    Button::Button()
        : m_onClick() {}

    Button::~Button() {}

}