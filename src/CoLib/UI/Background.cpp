#include <SFML/Graphics/RenderTarget.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Background.hpp>

namespace co
{

    const sf::Color &Background::getColor() const
    {
        return m_background.getColor();
    }

    void Background::setColor(const sf::Color &value)
    {
        m_background.setColor(value);
    }

    Background::Background()
        : m_background()
    {
        co::Rectangle rectangle(1, 1);
        m_background.setPrimitiveType(sf::PrimitiveType::TriangleFan);
        m_background.setPoints(rectangle);
    }

    Background::~Background() {}

    ///////////////////////////////////////////////////

    void Background::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (getWidth() > 0 && getHeight() > 0)
        {
            target.draw(m_background, states);
        }
    }

    void Background::onUpdate() const
    {
        if (getWidth() > 0 && getHeight() > 0)
        {
            m_background.fitPoints({{0, 0}, {getWidth(), getHeight()}});
        }
    }

}