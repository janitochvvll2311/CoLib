#define COLIB_UI_EXPORTS
#include <SFML/Graphics/RenderTarget.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Surface.hpp>

namespace co
{

    const sf::Color &Surface::getColor() const
    {
        return m_color;
    }

    void Surface::setColor(const sf::Color &value)
    {
        m_color = value;
    }

    Surface::Surface()
        : m_array(sf::PrimitiveType::TriangleFan), m_color(sf::Color::White)
    {
        co::Rectangle rectangle(1, 1);
        setPoints(m_array, rectangle);
    }

    Surface::~Surface() {}

    ////////////////////////////////////////////////////////////

    void Surface::onUpdate() const
    {
        auto width = getWidth();
        auto height = getHeight();
        if (width > 0 && height > 0)
        {
            fitPoints(m_array, sf::FloatRect({0, 0}, {width, height}));
            setColors(m_array, m_color);
        }
    }

    void Surface::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (getWidth() > 0 && getHeight() > 0)
        {
            target.draw(m_array, states);
        }
    }

}