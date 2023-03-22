#ifndef COLIB_POINT_SOURCE_HPP
#define COLIB_POINT_SOURCE_HPP

#include <SFML/System/Vector2.hpp>
#include <CoLib/Config.hpp>

namespace co
{

    class PointSource
    {
    public:
        virtual szt getPointCount() const = 0;
        virtual sf::Vector2f getPoint(szt index, szt precision = 1) const = 0;
        PointSource() = default;
        virtual ~PointSource() = default;
    };

}

#endif // COLIB_POINT_SOURCE_HPP