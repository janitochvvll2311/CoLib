#define COLIB_GRAPHICS_EXPORTS
#include <math.h>
#include <CoLib/System/Exception.hpp>
#include <CoLib/Graphics/Ellipse.hpp>

#define CO_PI 3.14159265358979323846

namespace co
{

    std::size_t Ellipse::getPointCount() const
    {
        return 12;
    }

    sf::Vector2f Ellipse::getPoint(std::size_t index, std::size_t precision) const
    {
        auto count = 12 * precision;
        return sf::Vector2f(
            m_centerX + m_radiusX * cosf((index * 2 * CO_PI) / count),
            m_centerY + m_radiusY * sinf((index * 2 * CO_PI) / count));
    }

    bool Ellipse::contains(const sf::Vector2f &point) const
    {
        if (
            point.x >= m_left && point.x <= m_right &&
            point.y >= m_top && point.y <= m_bottom)
        {
            auto dx = point.x - m_centerX;
            auto dy = point.y - m_centerY;
            return ((dx * dx) / (m_radiusX * m_radiusX) +
                        (dy * dy) / (m_radiusY * m_radiusY) <=
                    1);
        }
        return false;
    }

    Ellipse::Ellipse(f32t radiusX, f32t radiusY)
        : m_centerX(0), m_centerY(0),
          m_radiusX(radiusX), m_radiusY(radiusY),
          m_left(-radiusX), m_top(-radiusY),
          m_right(radiusX), m_bottom(radiusY) {}

    Ellipse::Ellipse(f32t centerX, f32t centerY, f32t radiusX, f32t radiusY)
        : m_centerX(centerX), m_centerY(centerY),
          m_radiusX(radiusX), m_radiusY(radiusY),
          m_left(centerX - radiusX), m_top(centerY - radiusY),
          m_right(centerX + radiusX), m_bottom(centerY + radiusY) {}

    Ellipse::~Ellipse() {}

} // co