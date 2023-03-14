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

    bool Button::handleEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (m_onClick && getBlock().contains({f32t(event.mouseButton.x), f32t(event.mouseButton.y)}))
            {
                m_onClick(*this);
            }
        }
        return Label::handleEvent(event);
    }

    Button::Button()
        : m_onClick() {}

    Button::~Button() {}

}