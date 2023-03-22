#define COLIB_GRAPHICS_EXPORTS
#include <math.h>
#include <limits>
#include <CoLib/Graphics/Geometry.hpp>

namespace co
{

    sf::FloatRect Geometry::getBounds(szt precision) const
    {
        sf::Vector2f min(std::numeric_limits<f32t>::infinity(), std::numeric_limits<f32t>::infinity());
        sf::Vector2f max(-std::numeric_limits<f32t>::infinity(), -std::numeric_limits<f32t>::infinity());
        auto pCount = getPointCount() * precision;
        for (szt i = 0; i < pCount; i++)
        {
            auto point = getPoint(i, precision);
            min.x = std::min(min.x, point.x);
            min.y = std::min(min.y, point.y);
            max.x = std::max(max.x, point.x);
            max.y = std::max(max.y, point.y);
        }
        return sf::FloatRect(min, sf::Vector2f(max.x - min.x, max.y - min.y));
    }

}