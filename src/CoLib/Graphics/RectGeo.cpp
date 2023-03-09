#include <CoLib/System/Exception.hpp>
#include <CoLib/Graphics/RectGeo.hpp>

namespace co
{

    szt RectGeo::getPointCount() const
    {
        return 4;
    }

    sf::Vector2f RectGeo::getPoint(szt index, szt precision) const
    {
        if (precision == 0)
        {
            precision = 1;
        }
        index %= getPointCount() * precision;
        if (index < precision)
        {
            return sf::Vector2f(m_start.x + index * m_size.x / precision, m_start.y);
        }
        index -= precision;
        if (index < precision)
        {
            return sf::Vector2f(m_end.x, m_start.y + index * m_size.y / precision);
        }
        index -= precision;
        if (index < precision)
        {
            return sf::Vector2f(m_end.x - index * m_size.x / precision, m_end.y);
        }
        index -= precision;
        if (index < precision)
        {
            return sf::Vector2f(m_start.x, m_end.y - index * m_size.y / precision);
        }
        throw Exception();
    }

    bool RectGeo::contains(const sf::Vector2f &point) const
    {
        return (point.x >= m_start.x && point.x <= m_end.x && point.y >= m_start.y && point.y <= m_end.y);
    }

    RectGeo::RectGeo(const sf::FloatRect &rect)
        : m_start(rect.left, rect.top),
          m_end(rect.left + rect.width, rect.top + rect.height),
          m_size(rect.width, rect.height) {}

    RectGeo::RectGeo(const sf::Vector2f &size)
        : m_start(0, 0),
          m_end(size.x, size.y),
          m_size(size.x, size.y) {}

}