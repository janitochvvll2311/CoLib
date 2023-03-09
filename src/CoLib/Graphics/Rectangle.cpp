#include <CoLib/System/Exception.hpp>
#include <CoLib/Graphics/Rectangle.hpp>

namespace co
{

    std::size_t Rectangle::getPointCount() const
    {
        return 4;
    }

    sf::Vector2f Rectangle::getPoint(std::size_t index, std::size_t precision) const
    {
        if (precision == 0)
        {
            precision = 1;
        }
        index %= 4 * precision;
        if (index < precision)
        {
            return sf::Vector2f(m_left + (m_width / precision) * index, m_top);
        }
        index -= precision;
        if (index < precision)
        {
            return sf::Vector2f(m_rigth, m_top + (m_height / precision) * index);
        }
        index -= precision;
        if (index < precision)
        {
            return sf::Vector2f(m_rigth - (m_width / precision) * index, m_bottom);
        }
        index -= precision;
        if (index < precision)
        {
            return sf::Vector2f(m_left, m_bottom - (m_height / precision) * index);
        }
        throw Exception("Broken code");
    }

    bool Rectangle::contains(const sf::Vector2f &point) const
    {
        return (point.x >= m_left &&
                point.x <= m_rigth &&
                point.y >= m_top &&
                point.y <= m_bottom);
    }

    Rectangle::Rectangle(f32t width, f32t height)
        : m_left(0), m_top(0),
          m_width(width), m_height(height),
          m_rigth(width), m_bottom(height) {}

    Rectangle::Rectangle(f32t left, f32t top, f32t width, f32t height)
        : m_left(left), m_top(top),
          m_width(width), m_height(height),
          m_rigth(left + width), m_bottom(top + height) {}

    Rectangle::~Rectangle() {}

} // co